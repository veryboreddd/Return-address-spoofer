#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <stdio.h>

/*
	Disable optimization for our example
*/

#pragma optimize("", off)

/*
	Link
*/

extern unique_function();
extern unique_function_two();
extern unique_function_three();
extern unique_jump(IN PVOID jmp_dst, IN PVOID dst);
extern unique_mov(IN PVOID dst, IN UINT64 value);


extern unique_mov_format(IN PVOID dst);

/*
	Empty function that displays when it is called
*/

VOID empty_function(VOID)
{
	printf("Called empty_function \n");

	return;
}

int main()
{
	/*
		Setup our variables where we want to jump too and the address of our
		unique jump instruction.
	*/

	PVOID jmp_dst = &empty_function;
	PVOID dst = (PVOID)((UINT64)unique_function + 1);

	/*
		Jump to it by returning
	*/

	unique_jump(jmp_dst, dst);

	/*
		Simulate a mov instruction using the rbx register.
	*/

	dst = (PVOID)((UINT64)unique_function_two + 0x10);

	unique_mov(dst, 0x500);

	/*
		Simulate a call to printf
	*/

	dst = (PVOID)((UINT64)unique_function_three + 0x10);

	unique_mov_format(dst);


	return 0;
}

