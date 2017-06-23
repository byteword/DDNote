// UTLib.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
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

