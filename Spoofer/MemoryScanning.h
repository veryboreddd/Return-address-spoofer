#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

BOOLEAN Compare_bytes(IN PBYTE base, IN PBYTE pattern);
PBYTE Find_Pattern(IN PBYTE base, IN SIZE_T size, IN PBYTE pattern);

