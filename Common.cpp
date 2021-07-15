//
// Created by dbozh on 7/3/2018.
//

#include "Common.h"
#include <system_error>
#include <assert.h>
#include "typedefs.h"
#include "SmartLock.h"
#ifdef LINUX
#include <arpa/inet.h>
#endif

using namespace std;

enum EType
{
	IAE,
	BAE,
	SEE
};

inline EType findEType(error_code& errorCode, int error)
{
	bool systemCat = error == 0;
	errorCode = error_code(systemCat? last_error : error, systemCat? system_category() : generic_category());
	switch (errorCode.value())
	{
		case EFAULT:
		case EINVAL:
		case EBADF:
		case EISCONN:
		case ENOTCONN:
		case ENOTSOCK:
		case EOPNOTSUPP:
		case EPIPE:
		case EMSGSIZE:
		case EDESTADDRREQ:
		case EACCES:
			return IAE;
		case ENOMEM:
			return BAE;
		default:
			return SEE;
	}
}

inline const string& getDelimiter()
{
	static const string delimiter = ": ";
	return delimiter;
}

void genericError(int error, const char* scope, const char* msg)
{
	assert(msg != nullptr);
	static const string& delimiter = getDelimiter();
	
	error_code errorCode;
	EType action = findEType(errorCode, error);
	switch (action)
	{
		case IAE:
			throw invalid_argument(scope + delimiter + msg + delimiter + errorCode.message());
		case BAE:
			throw bad_alloc();
		case SEE:
			throw system_error(errorCode, scope + delimiter + msg + delimiter + errorCode.message());
	}
}

void genericError(int error, const char* scope, const string& msg)
{
	static const string& delimiter = getDelimiter();
	
	error_code errorCode;
	EType action = findEType(errorCode, error);
	switch (action)
	{
		case IAE:
			throw invalid_argument(scope + delimiter + msg + delimiter + errorCode.message());
		case BAE:
			throw bad_alloc();
		case SEE:
			throw system_error(errorCode, scope + delimiter + msg + delimiter + errorCode.message());
	}
}

void systemError(const char* scope, const char* msg)
{
	genericError(0, scope, msg);
}

void systemError(const char* scope, const string& msg)
{
	genericError(0, scope, msg);
}

void gaiError(const char* scope, int error)
{
	static const string& delimiter = getDelimiter();
	static SpinLock gaiLock;
	SmartLock gaiSM(gaiLock);
	
	if (error != 0)
	{
		switch (error)
		{
			case EAI_NODATA:
			case EAI_FAIL:
			case EAI_AGAIN:
			case EAI_ADDRFAMILY:
			{
				error_code errorCode(error, system_category());
				throw system_error(errorCode, scope + delimiter + gai_strerror(error));
			}
			case EAI_SYSTEM:
				systemError(scope, gai_strerror(error));
			case EAI_SOCKTYPE:
			case EAI_SERVICE:
			case EAI_NONAME:
			case EAI_BADFLAGS:
			case EAI_FAMILY:
				throw invalid_argument(scope + delimiter + gai_strerror(error));
			case EAI_MEMORY:
				throw bad_alloc();
			default:
				systemError(scope, "Error not categorized");
		}
	}
}

string to_string(in_addr address)
{
	char converted[INET_ADDRSTRLEN + 1];
	converted[INET_ADDRSTRLEN] = 0;
	const char* success = inet_ntop(AF_INET, &address, converted, sizeof(converted));
	assert(success);
	return string(converted);
}

string to_string(in6_addr address)
{
	char converted[INET6_ADDRSTRLEN + 1];
	converted[INET6_ADDRSTRLEN] = 0;
	const char* success = inet_ntop(AF_INET6, &address, converted, sizeof(converted));
	assert(success);
	return string(converted);
}

in_addr to_addr(const char* ipv4)
{
	in_addr addr = {};
	int success = inet_pton(AF_INET, ipv4, &addr);
	assert(success != -1);
	if (!success)
		throw invalid_argument("Bad IPv4 parameter: " + string(ipv4));
	return addr;
}

in6_addr to_addr6(const char* ipv6)
{
	in6_addr addr = {};
	int success = inet_pton(AF_INET6, ipv6, &addr);
	assert(success != -1);
	if (!success)
		throw invalid_argument("Bad IPv6 parameter: " + string(ipv6));
	return addr;
}
