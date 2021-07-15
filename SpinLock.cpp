//
// Created by dbozh on 4/9/2018.
//

#include "SpinLock.h"

using namespace std;

SpinLock::SpinLock() {}

void SpinLock::lock(bool yield) noexcept
{
	while (locked.test_and_set())
		if (yield)
			this_thread::yield();
}

bool SpinLock::tryLock() noexcept
{
	return !locked.test_and_set();
}

void SpinLock::unlock() noexcept
{
	locked.clear();
}

