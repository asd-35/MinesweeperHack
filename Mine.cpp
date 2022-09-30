#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>

DWORD flagBaseAddr = 0x01005194;
DWORD timeBaseAddr = 0x0100579C;
int flagValue = 99;
int timeValue = 1;


DWORD procID;

DWORD findProcId(char* procName) {
    DWORD result = NULL;

    PROCESSENTRY32 procEntry32;
   
    procEntry32.dwSize == sizeof(PROCESSENTRY32);

    auto procSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    if (procSnap == INVALID_HANDLE_VALUE)
    {
        std::cout << "taking a snapshot failed" << std::endl;
        CloseHandle(procSnap);
        return result;
    }
    else {
        while (Process32Next(procSnap,&procEntry32))
        {
            if (!strcmp(procName, procEntry32.szExeFile)) {
                result = procEntry32.th32ProcessID;
                break;
            }
        }
        CloseHandle(procSnap);
        return result;
    }
    
    
}

int main()
{
    HWND hwnd = FindWindowA(NULL, "Minesweeper");

    if (hwnd == NULL) {
        std::cout << "game is not open";
    }
    else {
        GetWindowThreadProcessId(hwnd, &procID);
        if (findProcId((char*)"Winmine__XP.exe") == procID)
        {
            std::cout << "proc ID's match. One is from snap and one is from window name" << std::endl;
            std::cout << "Getting a handle and changing the address values.." << std::endl;
            HANDLE handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procID);
            
           
            while (true)
            {
                WriteProcessMemory(handle, (PVOID)timeBaseAddr, &timeValue, sizeof(int), 0);
                WriteProcessMemory(handle, (PVOID)flagBaseAddr, &flagBaseAddr, sizeof(int), 0);
            }
            
        }
    }




}

