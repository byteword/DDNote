// UTLib.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include <iostream>
#include "UnitTest.h"


bool UnitTestTest(void* ctx)
{
	std::cout << "Hello, World!" << std::endl;
	return true;
}

int main()
{
	CUnitTest *pUT = CUnitTest::GetUnitTest();
	pUT->AddTestSet("UnitTest Test");
	pUT->AddTest("UnitTest Test", UnitTestTest);
	pUT->TestAll();
	return 0;
}

