#ifndef __DDNOTE_SOCKET__H__INCLUDDED__
#define __DDNOTE_SOCKET__H__INCLUDDED__
#pragma once

#include <oscheck.h>
#include <errno.h>
#include <sys/types.h>

#if __WIN32__

#pragma comment(lib,"Ws2_32.lib")
#include <WinSock2.h>

#elif __WIN64__

#pragma comment(lib,"Ws2_32.lib")
#include <WinSock2.h>

#elif __IOS_SIM__
#elif __IOS__
#elif __MAC_OSX__
#elif __POSIX__
#endif

#include <stdio.h>
#include <stdlib.h>

#include "../header/libSocket.h"

struct _DDSocketCtx 
{
	int m_ref;
#ifdef __WIN32__
	SOCKET m_sock;
#endif
};

#endif //__DDNOTE_SOCKET__H__INCLUDDED__
