//
// Created by dbozh on 7/3/2018.
//

#ifndef PIPLAYER_SOCKETHANDLE_H
#define PIPLAYER_SOCKETHANDLE_H

#if defined(_WINDOWS) || defined(_CONSOLE)
#include <WS2tcpip.h>
#include <WinSock2.h>
#else
#include <netdb.h>
#endif // _WINDOWS

#include "typedefs.h"

class SocketHandle
{
public:
	SocketHandle(int domain, int type, int protocol);
	SocketHandle(sock_t existing, bool ignoreInvalid = false);
	SocketHandle(const SocketHandle&) = delete;
	SocketHandle(SocketHandle&&) noexcept;
	~SocketHandle();
	
	void close() noexcept;
	sock_t getHandle() const noexcept;
	
	SocketHandle& operator=(const SocketHandle&) = delete;
	SocketHandle& operator=(SocketHandle&&) noexcept;
private:
	sock_t socketHandle;
};


#endif //PIPLAYER_SOCKETHANDLE_H
