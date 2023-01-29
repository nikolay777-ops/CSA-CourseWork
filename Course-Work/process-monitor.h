#include <windows.h>
#include <tlhelp32.h>
#include <tchar.h>
#include "psapi.h"
#include <list>

#include <QString>

using namespace std;

class Process {

public:
    QString name;
    DWORD proc_id;
    QString th_count;
    QString prior_base;
    Process()
    {
        return;
    }
    Process(WCHAR* name, DWORD proc_id, DWORD thread_count, LONG priority_base)
    {
        this->name = QString::fromWCharArray(name, wcslen(name));
        this->proc_id = proc_id;
        this->th_count = QString::number(thread_count);
        this->prior_base = QString::number(priority_base);
    }
};

//  Forward declarations:
QList<Process*> GetProcessList();

BOOL ListProcessModules(DWORD dwPID);
BOOL ListProcessThreads(DWORD dwOwnerPID);
void printError(const TCHAR* msg);
void killProcessByID(unsigned long pID);
void createProcessByCmd(const wchar_t* procName);
double getRamValue(HANDLE handle);
double getCpuValue(HANDLE handle);
//unsigned long* arr = new unsigned long[1000];
