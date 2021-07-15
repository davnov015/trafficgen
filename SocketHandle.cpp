//
// Created by dbozh on 7/3/2018.
//

#include "SocketHandle.h"
#include "Common.h"

#ifdef LINUX
#include <unistd.h>
#endif

SocketHandle::SocketHandle(int domain, int type, int protocol)
{
	socketHandle = socket(domain, type, protocol);
	if (socketHandle == INVALID_SOCKET)
		systemError("SocketHandle::SocketHandle()", "Invalid Socket");
}

SocketHandle::SocketHandle(sock_t existing, bool ignoreInvalid)
{
	socketHandle = existing;
	if (!ignoreInvalid && socketHandle == INVALID_SOCKET)
		systemError("SocketHandle::SocketHandle()", "Existing Invalid Socket");
}

SocketHandle::SocketHandle(SocketHandle&& other) noexcept
{
	std::swap(socketHandle, other.socketHandle);
}

SocketHandle::~SocketHandle()
{
	close();
}

void SocketHandle::close() noexcept
{
	if (socketHandle != INVALID_SOCKET)
	{
		::close(socketHandle);
		socketHandle = INVALID_SOCKET;
	}
}

sock_t SocketHandle::getHandle() const noexcept
{
	return socketHandle;
}

SocketHandle& SocketHandle::operator=(SocketHandle&& other) noexcept
{
	std::swap(socketHandle, other.socketHandle);
	return *this;
}
