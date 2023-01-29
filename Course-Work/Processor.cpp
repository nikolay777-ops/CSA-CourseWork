#include "Processor.h"

Processor::Processor() {
    return;
}

float Processor::CalculateCPULoad(unsigned long long idleTicks, unsigned long long totalTicks)
{
    static unsigned long long _previousTotalTicks = 0;
    static unsigned long long _previousIdleTicks = 0;

    unsigned long long totalTicksSinceLastTime = totalTicks - _previousTotalTicks;
    unsigned long long idleTicksSinceLastTime = idleTicks - _previousIdleTicks;

    float ret = 1.0f - ((totalTicksSinceLastTime > 0) ? ((float)idleTicksSinceLastTime) / totalTicksSinceLastTime : 0);

    _previousTotalTicks = totalTicks;
    _previousIdleTicks = idleTicks;
    return ret;
}

unsigned long long Processor::FileTimeToInt64(const FILETIME& ft)
{
    return (((unsigned long long)(ft.dwHighDateTime)) << 32) | ((unsigned long long)ft.dwLowDateTime);
}

float Processor::GetCPULoad()
{
    FILETIME idleTime, kernelTime, userTime;
    return GetSystemTimes(&idleTime, &kernelTime, &userTime) ? CalculateCPULoad(FileTimeToInt64(idleTime), FileTimeToInt64(kernelTime) + FileTimeToInt64(userTime)) : -1.0f;
}


string Processor::GetArchitecture(UINT arch) 
{
    switch (arch) 
    {
        case 0: return "x86";
        case 1: return "MIPS";
        case 2: return "Alpha";
        case 3: return "PowerPC";
        case 5: return "ARM";
        case 6: return "IA-64 (Itanum-based systems)";
        case 9: return "x64";
        case 12: return "ARM64";
        default: return "Unknown";
    }
}

string Processor::GetAvailableType(UINT type) 
{
    switch(type)
    {
        case 1: return "Other";
        case 2: return "Unknown";
        case 3: return "Running / Full Power";
        case 4: return "Warning";
        case 5: return "In Test";
        case 6: return "Not Applicable";
        case 7: return "Power Off";
        case 8: return "Off Line";
        case 9: return "Off Duty";
        case 10: return "Degraded";
        case 11: return "Not Installed";
        case 12: return "Install Error";
        case 13: return "Power Save - Unknown";
        case 14: return "Power Save - Low Power Mode";
        case 15: return "Power Save - Standby";
        case 16: return "Power Cycle";
        case 17: return "Power Save - Warning";
        case 18: return "Paused";
        case 19: return "Not Ready";
        case 20: return "Not Configured";
        case 21: return "Quiesced";
        case 22: return "Other";
        default: return "Unknown";
    }
}

string Processor::GetProcessorType(UINT type)
{
    switch(type)
    {
        case 1: return "Other";
        case 2: return "Unknown";
        case 3: return "Central Processor";
        case 4: return "Math Processor";
        case 5: return "DSP Processor";
        case 6: return "Video Processor";
    }
}

void Processor::SetCache(vector<CacheLevel> cache)
{
    this->cache = cache;
}


Processor::Processor(UINT arch, UINT avail_type, float clock_speed, float voltage,
    UINT data_width, BSTR name, UINT cores, UINT en_cores, UINT proc_type, UINT t_count, float l_perc, UINT max_speed, float max_voltage)
{
    this->architecture = GetArchitecture(arch);
    this->availability = GetAvailableType(avail_type);
    this->current_speed = clock_speed;
    this->current_voltage = voltage;
    this->data_width = data_width;
    this->name = ConvertBSTRToMBS(name);
    this->cores_num = cores;
    this->en_cores_num = en_cores;
    this->proc_type = GetProcessorType(proc_type);
    this->thread_count = t_count;
    this->load_percentage = l_perc;
    this->max_speed = max_speed;
    this->max_voltage = max_voltage;
}

Processor* Processor::GetProcessorInfo(HRESULT* hres, IWbemLocator* pLoc, IWbemServices* pSvc)
{
    IEnumWbemClassObject* enumerator = NULL;
    BSTR bstr_wql = SysAllocString(L"WQL");
    BSTR bstr_sql = SysAllocString(L"SELECT * FROM Win32_Processor");

    *hres = pSvc->ExecQuery(
        SysAllocString(L"WQL"),
        SysAllocString(L"SELECT * FROM Win32_Processor"),
        WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
        NULL,
        &enumerator);

    if (FAILED(*hres)) {
        cout << "Query for Win32_BIOS Error code = 0x" << hex << hres << endl;
        pSvc->Release();
        pLoc->Release();
        CoUninitialize();
    }
    SysFreeString(bstr_wql);
    SysFreeString(bstr_sql);

    IWbemClassObject* storageWbemObject = NULL;
    ULONG uReturn = 0;
  
    Processor* proc = NULL;
    while (enumerator)
    {
        HRESULT hr = enumerator->Next(WBEM_INFINITE, 1, &storageWbemObject, &uReturn);
        if (0 == uReturn)
        {
            break;
        }
        
        VARIANT* chars = new VARIANT[12];
        
        storageWbemObject->Get(L"Architecture", 0, &chars[0], 0, 0);
        storageWbemObject->Get(L"Availability", 0, &chars[1], 0, 0);
        storageWbemObject->Get(L"MaxClockSpeed", 0, &chars[3], 0, 0);
        storageWbemObject->Get(L"DataWidth", 0, &chars[4], 0, 0);
        storageWbemObject->Get(L"Name", 0, &chars[5], 0, 0);
        storageWbemObject->Get(L"NumberOfCores", 0, &chars[6], 0, 0);
        storageWbemObject->Get(L"NumberOfEnabledCores", 0, &chars[7], 0, 0);
        storageWbemObject->Get(L"ProcessorType", 0, &chars[8], 0, 0);
        storageWbemObject->Get(L"ThreadCount", 0, &chars[9], 0, 0);
        storageWbemObject->Get(L"NumberOfEnabledCores", 0, &chars[10], 0, 0);
        storageWbemObject->Get(L"CurrentVoltage", 0, &chars[11], 0, 0);

        float cpu_load = Processor::GetCPULoad();
        proc = new Processor(chars[0].uintVal, chars[1].uintVal, chars[3].uintVal * cpu_load,
            chars[11].llVal * cpu_load, chars[4].uintVal, chars[5].bstrVal, chars[6].uintVal, chars[7].uintVal,
            chars[8].uintVal, chars[9].uintVal, cpu_load, chars[3].uintVal, chars[11].llVal);
        
        storageWbemObject->Release();
        delete[] chars;
    }

    return proc;
}

void Processor::UpdateProcStats(){
    float cpu_load = Processor::GetCPULoad();
    this->current_speed = cpu_load * this->max_speed;
    this->load_percentage = cpu_load;
    this->current_voltage = cpu_load * this->max_voltage;
}

unordered_map<string, string> Processor::ToMap(){

    unordered_map<string, string> map;
    map["Name"] = this->name;
    map["Cores Num"] = std::to_string(this->cores_num);
    map["Current Voltage"] = std::to_string(this->current_voltage);
    map["Max Speed"] = std::to_string(this->max_speed);
    map["Processor Type"] = this->proc_type;
    map["Cpu Status"] = this->cpu_status;
    map["Data Width"] = std::to_string(this->data_width);
    map["Max Voltage"] = std::to_string(this->max_voltage);
    map["Architecture"] = this->architecture;
    map["Availability"] = this->availability;
    map["Enabled Cores"] = std::to_string(this->en_cores_num);
    map["Thread Count"] = std::to_string(this->thread_count);
    map["Current Speed"] = std::to_string(this->current_speed);

    return map;
}
