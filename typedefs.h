//
// Created by davidb on 7/14/21.
//

#ifndef TRAFFICGEN_TYPEDEFS_H
#define TRAFFICGEN_TYPEDEFS_H

typedef int sock_t;
typedef unsigned char byte;
typedef unsigned short word;
typedef unsigned int dword;
typedef unsigned long long qword;
typedef unsigned int uint;

typedef int sock_t;
#define netbuf(x) x
#define last_error errno
#define INVALID_SOCKET  ((sock_t)-1)
#define AF AF_INET
#define LINUX

#endif //TRAFFICGEN_TYPEDEFS_H
