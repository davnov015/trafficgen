//
// Created by dbozh on 5/16/2018.
//

#ifndef HOUSESHIELD_SMARTLOCK_H
#define HOUSESHIELD_SMARTLOCK_H

#include "SpinLock.h"

class SmartLock
{
public:
	explicit SmartLock(SpinLock&, bool shouldYield = true, bool shouldLock = true) noexcept;
	SmartLock(const SmartLock&) = delete;
	SmartLock(SmartLock&&) noexcept;
	~SmartLock() noexcept;
	
	void unlock() noexcept;
	void release() noexcept;
	
	SmartLock& operator=(const SmartLock&) = delete;
	SmartLock& operator=(SmartLock&&) = delete;

private:
	SpinLock& aLock;
	bool locked;
};


#endif //HOUSESHIELD_SMARTLOCK_H
