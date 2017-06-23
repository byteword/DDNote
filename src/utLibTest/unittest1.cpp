#include "stdafx.h"
#include "CppUnitTest.h"
#include "../headers/oscheck.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace utLibTest
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(LibBase_OSCheck)
		{
			printf(__OS__);
		}


	};
}