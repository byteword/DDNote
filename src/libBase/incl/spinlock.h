#pragma once

#include <atomic>

#ifndef __DD_LIBBASE__SPINLOCK__H__INCLUDDED__
#define __DD_LIBBASE__SPINLOCK__H__INCLUDDED__

class spinlock
{
	std::atomic<bool> _flag;
public:
	spinlock(bool initial = false);

	void lock();
	bool trylock(int time);
	void free();
};

#endif //__DD_LIBBASE__SPINLOCK__H__INCLUDDED__