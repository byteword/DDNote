// UTLib.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <iostream>
#include "UnitTest.h"
#include <thread>
#include <atomic>
#include <assert.h>
#include <time.h>

class spinlock
{
	std::atomic<bool> _flag;
public:
	spinlock(bool initial = false)
	{
		_flag.store(initial);
	}

	void lock() {
		while (_flag.exchange(true));
	}

	bool trylock(int time) {
		clock_t time_inclock = ( time * 1000 ) / CLOCKS_PER_SEC;
		clock_t c = clock();
		while (_flag.exchange(true))
		{
			if (clock() - c > time_inclock)
				return false;
		}
		return true;
	}
	void free() {
		_flag.store(false);
	}
};

void test(int ptrlock)
{
	spinlock& lock = *(spinlock*)ptrlock;
	clock_t t = clock();
	while (clock() - t < CLOCKS_PER_SEC);
	std::cout << "freedom~" << std::endl;
	lock.free();
}

bool UnitTestTest(void* ctx)
{

	spinlock lock;
	lock.lock();
	std::thread t(test, (int) &lock);
	while (!lock.trylock(100)) std::cout << "waiting.." << std::endl;
	std::cout << "Hello, World!" << std::endl;
	lock.free();
	t.join();
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

