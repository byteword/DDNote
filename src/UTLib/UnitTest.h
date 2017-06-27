#pragma once

#include <list>
#include <map>
#include <iostream>

#ifndef __DD_UTLIB_UNITTEST__H__INCLUDED__
#define __DD_UTLIB_UNITTEST__H__INCLUDED__

typedef void* TEST_CTX;
typedef bool(FN_TEST)(TEST_CTX);
typedef TEST_CTX (FN_TEST_INIT)();
typedef void (FN_TEST_CLEAN)(TEST_CTX);
typedef const char* TEST_NAME_KEY;
struct NameKeyCmp
{
	inline bool operator () (TEST_NAME_KEY const left, TEST_NAME_KEY  const right) const { return strcmp(left, right) < 0; }
};

class CUnitTest
{
protected:
	typedef std::list<FN_TEST*> testlist_t;
	enum TEST_STATE {NONE, INITED, RUN, READY, CLEANUP, ERROR};
	struct STestSet {
		TEST_NAME_KEY m_name;
		FN_TEST_INIT* m_pfnInit;
		testlist_t m_pfnTests;
		FN_TEST_CLEAN* m_pfnClean;
		bool m_bResult;
		TEST_CTX m_ctx;
		bool m_bContinueOnError;
		TEST_STATE m_state;
	};
	typedef std::map<TEST_NAME_KEY, STestSet, NameKeyCmp> tests_t;
	tests_t m_Tests;

	// loging stream
	// every aciton should be looged
	std::ostream* m_log;

	tests_t::iterator itTestCache;

	// Singleton instance
protected:
	static CUnitTest s_Instance;
	CUnitTest();
	virtual ~CUnitTest();

public:
	// for Singleton
	static void InitUniTest(std::ostream &log);
	static CUnitTest* GetUnitTest();

	// Test All registered tests
	// test set order is not specified
	// test runs in order of register
	// init -> test1 -> test2 -> ... -> testN  -> clean
	void TestAll();

	// Add new Test set
	bool AddTestSet(TEST_NAME_KEY name, bool bContinueOnError = false);

	// Add a test to a set
	void AddTest(TEST_NAME_KEY name, FN_TEST* pfnTest);

	// Set a test initializer to a set
	void SetInitTest(TEST_NAME_KEY name, FN_TEST_INIT* pfnInit);

	// Set a test clean up to a set
	void SetCleanTest(TEST_NAME_KEY name, FN_TEST_CLEAN* pfnClean);

protected:
	bool TestInit(TEST_NAME_KEY name, STestSet &ts);
	void TestRunAll(TEST_NAME_KEY name, STestSet &ts);
	void TestCleanup(TEST_NAME_KEY name, STestSet &ts);

protected:
	STestSet* GetTS(TEST_NAME_KEY name, bool bAutoAdd = true);

};

#endif // __DD_UTLIB_UNITTEST__H__INCLUDED__