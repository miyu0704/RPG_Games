#pragma once
#include <Windows.h>

#define THROW(msg) _RPTF0(_CRT_ASSERT, msg)

inline void ERRMSG(const char* text, const char* caption)
{
	MessageBox(NULL, text, caption, MB_TOPMOST);
}