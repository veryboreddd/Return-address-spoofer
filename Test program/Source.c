#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <stdio.h>
#include <intrin.h>
#include <Psapi.h>

/*
	Disable optimization as this is a test program.
*/

#pragma optimize("", off)

MODULEINFO module_information;

/*
	Tests the return address of the caller to check if it's within the range of our module.
*/


VOID test_return_address()
{
	/*
		Return address.
	*/

	UINT64 return_address = _ReturnAddress();

	/*
		CASE: The caller is within our module.
	*/

	if (return_address >= module_information.lpBaseOfDll && return_address <= ((UINT64)module_information.lpBaseOfDll + module_information.SizeOfImage))
	{
		printf("Called from within module. \n");
	}
	else
	{
		printf("Called from outisde of module. \n");
	}

	return;
}

/*
	A simple function with no parameters and no body.
*/

VOID empty_call()
{
	return;
}

/*
	A simple function with four parameters and no body
*/

VOID empty_call_with_parameters(PVOID param_1, PVOID param_2, PVOID param_3, PVOID param_4)
{
	return;
}


INT main()
{
	/*
		CASE: Acquiring module information failed.
	*/

	if (!GetModuleInformation(GetCurrentProcess(), GetModuleHandle(NULL), &module_information, sizeof(MODULEINFO)))
	{
		return 0;
	}

	/*
		Empty call
	*/

	empty_call();

	for (;;)
	{
		/*
			Call our function
		*/

		test_return_address();

		/*
			Keep our program open
		*/

		getchar();
	}

	return 0;
}
