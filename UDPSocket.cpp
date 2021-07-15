//
// Created by dbozh on 7/5/2018.
//

#include "UDPSocket.h"
#include "Common.h"
#include <assert.h>

UDPSocket::UDPSocket(in_port_t port, in_addr intAddr) : socket(AF, SOCK_DGRAM, IPPROTO_UDP)
{
	this->port = port;
#ifdef DUAL_STACK
#error UDPSocket needs fixing.
	sockaddr_in6 sockAddr = {};
	sockAddr.sin6_family = AF_INET6;
	sockAddr.sin6_addr = in6addr_any;
	sockAddr.sin6_port = htons(port);
#else
	sockaddr_in sockAddr = {};
	sockAddr.sin_family = AF_INET;
	sockAddr.sin_addr = intAddr;
	sockAddr.sin_port = htons(port);
#endif
	
	int error;

#ifdef DUAL_STACK
	int v6Only = 0;
	error = setsockopt(socket.getHandle(), IPPROTO_IPV6, IPV6_V6ONLY, &v6Only, sizeof(v6Only));
	if (error)
		systemError("UDPSocket::UDPSocket()", "Failed to disable the IPV6_V6ONLY socket option");
#endif
	
	error = bind(socket.getHandle(), reinterpret_cast<const sockaddr*>(&sockAddr), sizeof(sockAddr));
	if (error)
		systemError("UDPSocket::UDPSocket()", "Failed to bind to port: " + std::to_string(port) + " on all interfaces");
}

UDPSocket::UDPSocket(UDPSocket&& other) noexcept : socket(INVALID_SOCKET, true)
{
	swap(other);
}

void UDPSocket::sendto(const byte* buf, size_t length, const sockaddr_in& dest) const
{
	ssize_t sent = ::sendto(socket.getHandle(), netbuf(buf), length, 0, reinterpret_cast<const sockaddr*>(&dest), sizeof(dest));
	if (sent == -1)
		systemError("UDPSocket::sendto()");
	assert(sent == length);
}

size_t UDPSocket::recvfrom(byte* buf, size_t length) const
{
	ssize_t received = ::recvfrom(socket.getHandle(), netbuf(buf), length, 0, nullptr, nullptr);
	if (received == -1)
		systemError("UDPSocket::recvfrom()");
	assert(received >= 0 && received <= length);
	return received;
}

void UDPSocket::shutdown() noexcept
{
	int err = ::shutdown(socket.getHandle(), SHUT_RDWR);
	if (err)
	{
		err = last_error;
		assert(err != EBADF && err != ENOTSOCK && err != EINVAL);
	}
}

in_port_t UDPSocket::getPort() const noexcept
{
	return port;
}

sock_t UDPSocket::getHandle() const noexcept
{
	return socket.getHandle();
}

void UDPSocket::swap(UDPSocket& other) noexcept
{
	using std::swap;
	swap(socket, other.socket);
	swap(port, other.port);
}
UDPSocket& UDPSocket::operator=(UDPSocket&& other) noexcept
{
	swap(other);
	return *this;
}
