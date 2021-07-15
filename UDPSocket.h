//
// Created by dbozh on 7/5/2018.
//

#ifndef PIPLAYER_UDPSOCKET_H
#define PIPLAYER_UDPSOCKET_H

#include "SocketHandle.h"

class UDPSocket
{
public:
	explicit UDPSocket(in_port_t port, in_addr intAddr);
	UDPSocket(const UDPSocket&) = delete;
	UDPSocket(UDPSocket&&) noexcept;
	virtual ~UDPSocket() = default;
	
	void sendto(const byte* buf, size_t length, const sockaddr_in& dest) const;
	size_t recvfrom(byte* buf, size_t length) const;
	void shutdown() noexcept;
	
	in_port_t getPort() const noexcept;
	
	void swap(UDPSocket& other) noexcept;
	
	UDPSocket& operator=(const UDPSocket&) = delete;
	UDPSocket& operator=(UDPSocket&&) noexcept;

protected:
	sock_t getHandle() const noexcept;
	
private:
	SocketHandle socket;
	in_port_t port;
};


#endif //PIPLAYER_UDPSOCKET_H
