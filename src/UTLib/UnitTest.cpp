#include <time.h>

#include "UnitTest.h"

CUnitTest CUnitTest::s_Instance;
void CUnitTest::InitUniTest(std::ostream &log)
{
	s_Instance.m_log = &log;
}

CUnitTest* CUnitTest::GetUnitTest()
{
	return &s_Instance;
}


CUnitTest::CUnitTest()
{
	m_log = &(std::cerr);
	itTestCache = m_Tests.end();
}


CUnitTest::~CUnitTest()
{
	for (tests_t::iterator it = m_Tests.begin(); it != m_Tests.end(); it++)
	{
		if (it->second.m_state == TEST_STATE::READY &&
			it->second.m_pfnClean != NULL)
		{
			TestCleanup(it->first, it->second);
		}
	}
	m_Tests.clear();
}

void CUnitTest::TestAll()
{
	(*m_log) << "[UnitTest] Start All Test " << std::endl;
	tests_t::iterator it = m_Tests.begin();
	while (it != m_Tests.end())
	{
		bool res = TestInit(it->first, it->second);
		if (res)
		{
			TestRunAll(it->first, it->second);
			TestCleanup(it->first, it->second);
		}
		it++;
	}
	(*m_log) << "[UnitTest] End All Test" << std::endl;
}

// Add new Test set
bool CUnitTest::AddTestSet(TEST_NAME_KEY name, bool bContinueOnError /*= false */)
{
	STestSet *pTS = GetTS(name, false);
	if (pTS != NULL)
		return false;

	m_Tests[name].m_name = name;
	pTS = GetTS(name, false);
	pTS->m_bContinueOnError = bContinueOnError;
	pTS->m_state = TEST_STATE::NONE;
	(*m_log) << "[UnitTest] a Test Set added : " << name << std::endl;
	return true;
}

void CUnitTest::AddTest(TEST_NAME_KEY name, FN_TEST* pfnTest)
{
	STestSet *pTS = GetTS(name);
	if (pTS == NULL)
	{
		AddTestSet(name);
		pTS = GetTS(name);
	}
	pTS->m_pfnTests.push_back(pfnTest);
	(*m_log) << "[UnitTest] a Test added on " << name << std::endl;
}


void CUnitTest::SetInitTest(TEST_NAME_KEY name, FN_TEST_INIT* pfnInit)
{
	STestSet *pTS = GetTS(name);
	pTS->m_pfnInit = pfnInit;
	(*m_log) << "[UnitTest] Test Set [" << name << "] initializer setted" << std::endl;
}

void CUnitTest::SetCleanTest(TEST_NAME_KEY name, FN_TEST_CLEAN* pfnClean)
{
	STestSet *pTS = GetTS(name);
	pTS->m_pfnClean = pfnClean;
	(*m_log) << "[UnitTest] Test Set [" << name << "] clean up setted" << std::endl;
}

bool CUnitTest::TestInit(TEST_NAME_KEY name, STestSet &ts)
{
	if (ts.m_state != TEST_STATE::NONE)
		return false;
	try
	{
		(*m_log) << "[UnitTest] Test Set [" << name << "] is ready to init" << std::endl;
		if (ts.m_pfnInit != NULL)
			ts.m_ctx = ts.m_pfnInit();

		ts.m_state = TEST_STATE::READY;
		(*m_log) << "[UnitTest] Test Set [" << name << "] is inited" << std::endl;
		return true;
	}
	catch (...)
	{
		ts.m_state = TEST_STATE::ERROR;
		(*m_log) << "[UnitTest] Test Set [" << name << "]'s initialization failed with fatal error." << std::endl;
		return false;
	}
}

void CUnitTest::TestRunAll(TEST_NAME_KEY name, STestSet &ts)
{
	(*m_log) << "[UnitTest] Test Set [" << name << "] is starting test" << std::endl;
	if (ts.m_state != TEST_STATE::READY)
	{
		(*m_log) << "[UnitTest] Test Set [" << name << "] is not ready to run" << std::endl;
		return;
	}

	ts.m_state = TEST_STATE::RUN;
	int idx = 1;
	for (testlist_t::iterator it = ts.m_pfnTests.begin(); it != ts.m_pfnTests.end(); it++, idx++)
	{
		(*m_log) << "[UnitTest] Test Set [" << name << "]'s "<< idx <<" is begin" << std::endl;
		try {
			clock_t begin = clock(); // time check

			bool res = (*it)(ts.m_ctx); // run

			clock_t end = clock();
			double time_diff = (end - begin) / (double) CLOCKS_PER_SEC;

			(*m_log) << "[UnitTest] Test Set [" << name << "]'s " << idx << " is endded with " << (res ? "succeded" : "failed") << "in " << time_diff << "sec" << std::endl;
		}
		catch(...)
		{
			(*m_log) << "[UnitTest] Test Set [" << name << "]'s " << idx << " is endded with fatal error " << std::endl;
			if (ts.m_bContinueOnError == false)
			{
				ts.m_state = TEST_STATE::ERROR;
				(*m_log) << "[UnitTest] Test Set [" << name << "]'s is suspendded" << std::endl;
				break;
			}
		}
	}
	if( ts.m_state == TEST_STATE::RUN )
		ts.m_state = TEST_STATE::READY;
	(*m_log) << "[UnitTest] Test Set [" << name << "] is run out" << std::endl;
}

void CUnitTest::TestCleanup(TEST_NAME_KEY name, STestSet &ts)
{
	if (ts.m_state != TEST_STATE::READY &&
		ts.m_state != TEST_STATE::ERROR)
		return;

	try
	{

		(*m_log) << "[UnitTest] Test Set [" << name << "] is ready to clean up" << std::endl;

		if (ts.m_pfnClean != NULL)
			ts.m_pfnClean(ts.m_ctx);
		ts.m_ctx = NULL;
		ts.m_state = TEST_STATE::NONE;

		(*m_log) << "[UnitTest] Test Set [" << name << "] is cleaned up" << std::endl;
	}
	catch (...)
	{
		ts.m_state = TEST_STATE::ERROR;

		(*m_log) << "[UnitTest] Test Set [" << name << "]'s cleanup failed with fatal error." << std::endl;
	}
}


// Lookup TestSet
CUnitTest::STestSet* CUnitTest::GetTS(TEST_NAME_KEY name, bool bAutoAdd /* = true */)
{
	// first in cache
	if (itTestCache != m_Tests.end() &&
		strcmp(name, itTestCache->first) == 0)
		return &(itTestCache->second);

	// lookup map
	itTestCache = m_Tests.find(name);
	if (itTestCache != m_Tests.end())
		return &(itTestCache->second);

	// NULL when not found
	if (bAutoAdd == false)
		return NULL;


	// add if not exist by option
	AddTestSet(name);
	itTestCache = m_Tests.find(name);
	return &(itTestCache->second);
}