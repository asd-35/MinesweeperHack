// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include <Windows.h>
#include <iostream>

DWORD WINAPI MineThread(HMODULE hModule) {
    AllocConsole();
    FILE* f;
    fopen_s(&f,"CONOUT$","w");

    printf("Minesweeper DLL Hack");



    DWORD moduleBase = (DWORD)GetModuleHandle("Winmine__XP.exe");

    
    
    while (true)
    {
        int* time = (int*)moduleBase + 0x579C;
        *time = 1;
        
    }


    fclose(f);
    
    FreeConsole();
    FreeLibraryAndExitThread(hModule, 0);
    return 0;
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CloseHandle(CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)MineThread, hModule, 0, nullptr));
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

