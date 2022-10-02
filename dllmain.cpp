// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "Windows.h"
#include "iostream"

DWORD WINAPI MineThread(HMODULE hModule) {
    AllocConsole();
    FILE* f;
    fopen_s(&f,"CONOUT$","w");

    std::cout << "Minesweeper DLL Hack";

    FreeConsole();

    DWORD moduleBase = (DWORD)GetModuleHandle("Winmine__XP.exe");

    while (true)
    {
        int* time = (int*)moduleBase + 0x579C;
        *time = 1;
        int* flag = (int*)moduleBase + 0x5194;
        *flag = 99;
    }
    
    

    //fclose(f);
    

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

