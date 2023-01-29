#include "process-monitor.h"
#include <windows.h>
#include <tlhelp32.h>
#include <tchar.h>
#include "psapi.h"
#include <list>

#include <QList>


void init(HANDLE handle, int* numProcessors, ULARGE_INTEGER* lastCPU, ULARGE_INTEGER* lastSysCPU, ULARGE_INTEGER* lastUserCPU) {
    SYSTEM_INFO sysInfo;
    FILETIME ftime, fsys, fuser;

    GetSystemInfo(&sysInfo);
    *numProcessors = sysInfo.dwNumberOfProcessors;

    GetSystemTimeAsFileTime(&ftime);
    memcpy(lastCPU, &ftime, sizeof(FILETIME));
    Sleep(300);
    GetProcessTimes(handle, &ftime, &ftime, &fsys, &fuser);
    memcpy(lastSysCPU, &fsys, sizeof(FILETIME));
    Sleep(300);
    memcpy(lastUserCPU, &fuser, sizeof(FILETIME));
}

double getCpuValue(HANDLE handle) {
    FILETIME ftime, fsys, fuser;
    ULARGE_INTEGER now, sys, user;
    long double percent = 0;

    ULARGE_INTEGER lastCPU, lastSysCPU, lastUserCPU;
    int numProcessors = 0;
    init(handle, &numProcessors, &lastCPU, &lastSysCPU, &lastUserCPU);

    GetSystemTimeAsFileTime(&ftime);
    memcpy(&now, &ftime, sizeof(FILETIME));
    Sleep(300);
    GetProcessTimes(handle, &ftime, &ftime, &fsys, &fuser);
    memcpy(&sys, &fsys, sizeof(FILETIME));
    Sleep(300);
    memcpy(&user, &fuser, sizeof(FILETIME));
    percent = (sys.QuadPart - lastSysCPU.QuadPart) +
        (user.QuadPart - lastUserCPU.QuadPart);
    percent /= (now.QuadPart - lastCPU.QuadPart) == 0 ? 1 : (now.QuadPart - lastCPU.QuadPart);
    percent /= numProcessors;
    lastCPU = now;
    lastUserCPU = user;
    lastSysCPU = sys;

    return percent * 100;
}

double getRamValue(HANDLE handle)
{
    MEMORYSTATUSEX memInfo;
    memInfo.dwLength = sizeof(MEMORYSTATUSEX);
    GlobalMemoryStatusEx(&memInfo);
    DWORDLONG totalVirtualMem = memInfo.ullTotalPageFile;

    PROCESS_MEMORY_COUNTERS_EX pmc;
    GetProcessMemoryInfo(handle, (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc));
    SIZE_T virtualMemUsedByMe = pmc.PrivateUsage;
    double percentage = (double (virtualMemUsedByMe) / totalVirtualMem);
    return (percentage * totalVirtualMem) / 1000000;
}


QList<Process*> GetProcessList()
{
    HANDLE hProcessSnap;
    HANDLE hProcess;
    PROCESSENTRY32 pe32;
    DWORD dwPriorityClass;

    hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hProcessSnap == INVALID_HANDLE_VALUE)
    {
        printError(TEXT("CreateToolhelp32Snapshot (of processes)"));
        return QList<Process*>();
    }

    pe32.dwSize = sizeof(PROCESSENTRY32);

    if (!Process32First(hProcessSnap, &pe32))
    {
        printError(TEXT("Process32First"));
        CloseHandle(hProcessSnap);
        return QList<Process*>();
    }

    QList<Process*> list;
    do
    {
        dwPriorityClass = 0;
        hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pe32.th32ProcessID);

        if (hProcess == NULL)
            printError(TEXT("OpenProcess"));
        else
        {
            dwPriorityClass = GetPriorityClass(hProcess);
            if (!dwPriorityClass)
                printError(TEXT("GetPriorityClass"));
            CloseHandle(hProcess);
        }
        list.push_back(new Process(pe32.szExeFile, pe32.th32ProcessID, pe32.cntThreads, pe32.pcPriClassBase));
         } while (Process32Next(hProcessSnap, &pe32));

    CloseHandle(hProcessSnap);
    return list;
}

void printError(const TCHAR* msg)
{
    DWORD eNum;
    TCHAR sysMsg[256];
    TCHAR* p;

    eNum = GetLastError();
    FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL, eNum,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        sysMsg, 256, NULL);

    p = sysMsg;
    while ((*p > 31) || (*p == 9))
        ++p;
    do { *p-- = 0; } while ((p >= sysMsg) &&
        ((*p == '.') || (*p < 33)));

    _tprintf(TEXT("\n  WARNING: %s failed with error %d (%s)"), msg, eNum, sysMsg);
}

void killProcessByID(unsigned long pID)
{
    HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPALL, NULL);
    PROCESSENTRY32 pEntry;
    pEntry.dwSize = sizeof(pEntry);
    BOOL hRes = Process32First(hSnapShot, &pEntry);
    while (hRes)
    {
        if (pEntry.th32ProcessID == pID)
        {
            HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, 0,
                (DWORD)pEntry.th32ProcessID);
            if (hProcess != NULL)
            {
                TerminateProcess(hProcess, 9);
                CloseHandle(hProcess);
            }
        }
        hRes = Process32Next(hSnapShot, &pEntry);
    }
    CloseHandle(hSnapShot);
}

void createProcessByCmd(const wchar_t* procName) {
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));


    if (!CreateProcess(
        NULL,
        (TCHAR *)procName,
        NULL,
        NULL,
        FALSE,
        0,
        NULL,
        NULL,
        &si,
        &pi)
        )
    {
        _tprintf(TEXT("CreateProcess failed (%d).\n"), GetLastError());
        return;
    }
}
