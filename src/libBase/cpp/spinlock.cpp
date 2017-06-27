#include <assert.h>
#include <time.h>

#include "../incl/spinlock.h"

spinlock::spinlock(bool initial /*= false*/)
{
	_flag.store(initial);
	assert(_flag == false);
}

void spinlock::lock() {
	while (_flag.exchange(true));
	assert(_flag == true);
}

bool spinlock::trylock(int time) {
	clock_t time_inclock = (time * 1000) / CLOCKS_PER_SEC;
	clock_t c = clock();
	while (_flag.exchange(true))
	{
		if (clock() - c > time_inclock)
			return false;
	}
	return true;
}
void spinlock::free()
{
	assert(_flag == true);
	_flag.store(false);
}