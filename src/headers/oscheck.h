#pragma once
#ifndef __DDNOTE_OSCHECK__H__INCLUDDED__
#define __DDNOTE_OSCHECK__H__INCLUDDED__

#ifdef _WIN32

// WIN32 = Windows
#	ifdef _WIN64 // 64bit
#		define __OS__ "WIN64"
#		define __WIN64__ 1
#	else // 32bit only
#		define __OS__ "WIN32"
#		define __WIN32__ 1
#	endif

#elif __APPLE__

// apple's OS
#	if TARGET_IPHONE_SIMULATOR

// iOS Simulator
#		define __OS__ "IOS_SIM"
#		define __IOS_SIM__ 1
#	elif TARGET_OS_IPHONE

// iOS device
#		define __OS__ "IOS"
#		define __IOS__ 1
#	elif TARGET_OS_MAC

// Mac OSX
#		define __OS__ "MAC_OSX"
#		define __MAX_OSX__ 1

#	else
// Apple's unknown

#		error "Unknown Apple platform"
#		define __OS__ "MAC_UNK"
#		define __MAC_UNK__ 1
#	endif // end Apple's OS

#elif defined(__POSIX_VERSION)

// POSIX
#		define __OS__ "POSIX"
#		define __POSIX__ 1
#endif // OSs

#endif //__DDNOTE_OSCHECK__H__INCLUDDED__
