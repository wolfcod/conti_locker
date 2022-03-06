#pragma once
#include <string>
#include "MetaString.h"

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
	