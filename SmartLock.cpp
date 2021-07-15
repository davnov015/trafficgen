//
// Created by dbozh on 5/16/2018.
//

#include "SmartLock.h"

SmartLock::SmartLock(SpinLock& lockRef, bool yield, bool sLock) noexcept
		: aLock(lockRef)
{
	if (sLock)
		aLock.lock(yield);
	locked = sLock;
}

SmartLock::SmartLock(SmartLock&& other) noexcept : aLock(other.aLock)
{
	locked = other.locked;
	other.locked = false;
}

SmartLock::~SmartLock() noexcept
{
	if (locked)
		aLock.unlock();
}

void SmartLock::unlock() noexcept
{
	if (locked)
	{
		aLock.unlock();
		locked = false;
	}
}

void SmartLock::release() noexcept
{
	locked = false;
}
