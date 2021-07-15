//
// Created by dbozh on 4/9/2018.
//

#ifndef HOUSESHIELD_SPINLOCK_H
#define HOUSESHIELD_SPINLOCK_H

#include <thread>
#include <atomic>

class SpinLock {
public:
	SpinLock();
	SpinLock(const SpinLock&) = delete;
	SpinLock(SpinLock&&) = delete;
	
	void lock(bool yield = true) noexcept;
	/*
	 * Attempts to lock the lock.
	 * Returns true if it succeeded, otherwise it returns false.
	 */
	bool tryLock() noexcept;
	
	void unlock() noexcept;

private:
	std::atomic_flag locked = ATOMIC_FLAG_INIT;
};


#endif //HOUSESHIELD_SPINLOCK_H
