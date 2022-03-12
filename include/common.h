#pragma once
#ifndef _WINDOWS_
#include <WinSock2.h>
#endif
#include <string>
#include <iostream>
#include "MetaString.h"

//#define DEBUG
#define STATIC static

inline PVOID m_malloc(SIZE_T Size)
{
	PVOID buf = malloc(Size);
	if (buf) {
		memset(buf, 0, Size);
	}

	return buf;
}

inline VOID m_free(PVOID Memory)
{
	free(Memory);
}
