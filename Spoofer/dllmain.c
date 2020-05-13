#define WIN32_LEAN_AND_MEAN
#define _CRT_SECURE_NO_WARNINGS 

#include <Windows.h>
#include "MemoryScanning.h"

#include <stdio.h>

/*
    Function pointers
*/

typedef VOID( * our_function)(VOID);

/*
    Link
*/

extern simple_jump(PVOID address);
extern spoof_return(PVOID spoof_location, PVOID spoof_destination);
extern spoof_return_params(PVOID spoof_location, PVOID spoof_destination, ...);

extern PVOID get_image_base(VOID);

/*
    Patterns:

    If using sig scans.
*/


DWORD Main_Routine(IN LPVOID lpThreadParameter)
{
    /*
        Get our image base and size of image from the PEB
    */

    PBYTE image_base = get_image_base();


    /*
        Acquire the address of the function we are going to call
        and the address of our gadget.

        NOTE:
            Our gadget is just the empty_call function which
            simply returns.
    */

    PVOID our_function_address = (PVOID)(image_base + 0x1070);

    PVOID our_gadget_address = (PVOID)(image_base + 0x10D0);

    /*
        CASE: We didn't find our function
    */

    if (our_function_address == NULL)
    {
        return 1;
    }

    /*
        Set our function pointer to point to our functions address
    */

    our_function p_our_function = (our_function)our_function_address;

    /*
        Simple forever loop
    */

    for (;;)
    {
        /*
            Call our function without spoofing.
        */

        if (GetAsyncKeyState(VK_CONTROL) & 1)
        {
            p_our_function();
        }

        /*
            Call our function with spoofing
        */

        if (GetAsyncKeyState(VK_SHIFT) & 1)
        {
            spoof_return(our_gadget_address, p_our_function);
        }
    }

    return 0;
}

BOOL APIENTRY DllMain(IN HMODULE hModule, IN DWORD ul_reason_for_call, IN LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CreateThread(0, 0, Main_Routine, 0, 0, 0);
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

