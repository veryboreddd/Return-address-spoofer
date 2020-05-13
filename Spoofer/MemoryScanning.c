#include "MemoryScanning.h"

BOOLEAN Compare_bytes(IN PBYTE base, IN PBYTE pattern)
{
	for (; *pattern; pattern++, base++)
	{
		if (*pattern == 0xFF)
			continue;

		if (*base != *pattern)
		{
			return FALSE;
		}
	}

	return TRUE;
}

PBYTE Find_Pattern(IN PBYTE base, IN SIZE_T size, IN PBYTE pattern)
{
	PBYTE end_address = base + size;

	for (; base < end_address; base++)
	{
		if (*base != *pattern)
			continue;

		if (Compare_bytes(base, pattern))
		{
			return base;
		}
	}

	return NULL;
}