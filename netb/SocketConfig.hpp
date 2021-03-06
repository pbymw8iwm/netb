/*
 * Copyright (C) 2010-2016, Maoxu Li. http://maoxuli.com/dev
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef NETB_SOCKET_CONFIG_HPP
#define NETB_SOCKET_CONFIG_HPP

// Include headers for some basic classes
#include "Config.hpp"
#include "Uncopyable.hpp"
#include "Error.hpp"
#include "Exception.hpp"
#include "ErrorCode.hpp"
#include "SocketError.hpp"

// Include headers for socket API
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <unistd.h>
#include <fcntl.h>
#include <netdb.h>

// According to POSIX.1-2001, POSIX.1-2008 
#include <sys/select.h>
// According to earlier standards 
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

NETB_BEGIN

// Socket type 
// and associated const values used in socke API
typedef int SOCKET;
const int INVALID_SOCKET = -1;
const int SOCKET_ERROR = -1;

const int RECEIVE_BUFFER_SIZE = 2048;

// Socket events
enum {
    SOCKET_EVENT_NONE = 0,
    SOCKET_EVENT_READ = 1,
    SOCKET_EVENT_WRITE = 2,
    SOCKET_EVENT_EXCEPT = 4
};

// FD_COPY is not POSIX 98 
#ifndef FD_COPY
#define FD_COPY(src, dst) do{ memcpy((dst), (src), sizeof *(dst)); } while(0) // no trailing ;
#endif

// Socket initializer
// Necessary for Windows and do nothing on linux or so
struct SocketInitializer
{
	SocketInitializer() 
    {
 	#if defined(WIN32)
		WSADATA wsadata;
		::WSAStartup(MAKEWORD(2, 0), &wsadata);
	#endif
    }

	~SocketInitializer() 
    { 
	#if defined(WIN32)
		::WSACleanup();
	#endif
    }
};

NETB_END

#endif
