//
// Created by dbozh on 7/3/2018.
//

#ifndef PIPLAYER_COMMON_H
#define PIPLAYER_COMMON_H

#if defined(_WINDOWS) || defined(_CONSOLE)
#include <WS2tcpip.h>
#include <WinSock2.h>
#else
#include <netdb.h>
#endif // _WINDOWS

#include <string>

void genericError(int error, const char* scope, const char* msg = "");
void genericError(int error, const char* scope, const std::string& msg);
void systemError(const char* scope, const char* msg = "");
void systemError(const char* scope, const std::string& msg);
void gaiError(const char* scope, int error);

std::string to_string(in_addr address);
std::string to_string(in6_addr address);

in_addr to_addr(const char* ipv4);
in6_addr to_addr6(const char* ipv6);


#endif //PIPLAYER_COMMON_H
