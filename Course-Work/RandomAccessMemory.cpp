#include "RAM.h"
#include <list>


RAM::RAM(int used_mem, BSTR manufacturer, UINT clock_speed, UINT memory_type,
    UINT speed, UINT max_speed, ULONGLONG capacity)
{
    this->used_mem = used_mem;
    this->manufacturer = ConvertBSTRToMBS(manufacturer);
    this->clock_speed = clock_speed;
    this->memory_type = GetPhysicalMemoryType(memory_type);
    this->speed = speed;
    this->max_speed = max_speed;
    this->capacity = capacity;
}

string RAM::GetPhysicalMemoryType(UINT type)
{
    switch (type) 
    {
    case 0: return "Unknown";
    case 1: return "Other";
    case 2: return "DRAM";
    case 3: return "Synchronous DRAM";
    case 4: return "Cache DRAM";
    case 5: return "EDO";
    case 6: return "EDRAM";
    case 7: return "VRAM";
    case 8: return "SRAM";
    case 9: return "RAM";
    case 10: return "ROM";
    case 11: return "Flash";
    case 12: return "EEPROM";
    case 13: return "FEPROM";
    case 14: return "EPROM";
    case 15: return "CDRAM";
    case 16: return "3DRAM";
    case 17: return "SDRAM";
    case 18: return "SGRAM";
    case 19: return "RDRAM";
    case 20: return "DDR";
    case 21: return "DDR2";
    case 22: return "DDR2 FB-DIMM";
    }
}

RAM::RAM()
{
    return;
}

vector<RAM*> RAM::GetRamInfo(HRESULT* hres, IWbemLocator* pLoc, IWbemServices* pSvc)
{
    IEnumWbemClassObject* enumerator = NULL;
    BSTR bstr_wql = SysAllocString(L"WQL");
    BSTR bstr_sql = SysAllocString(L"SELECT * FROM Win32_PhysicalMemory");

    *hres = pSvc->ExecQuery(
        bstr_wql,
        bstr_sql,
        WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
        NULL,
        &enumerator);

    if (FAILED(*hres)) {
        cout << "Query for Win32_PhysicalMemory Error code = 0x" << hex << hres << endl;
        pSvc->Release();
        pLoc->Release();
        CoUninitialize();
    }
    SysFreeString(bstr_wql);
    SysFreeString(bstr_sql);

    IWbemClassObject* storageWbemObject = NULL;
    ULONG uReturn = 0;
    vector<RAM*> list;
    
    while (enumerator)
    {
        HRESULT hr = enumerator->Next(WBEM_INFINITE, 1, &storageWbemObject, &uReturn);
        if (0 == uReturn)
        {
            break;
        }

        VARIANT* chars = new VARIANT[8];

        storageWbemObject->Get(L"Caption", 0, &chars[0], 0, 0);
        storageWbemObject->Get(L"Capacity", 0, &chars[1], 0, 0);
        storageWbemObject->Get(L"ConfiguredClockSpeed", 0, &chars[2], 0, 0);
        storageWbemObject->Get(L"Manufacturer", 0, &chars[3], 0, 0);
        storageWbemObject->Get(L"MemoryType", 0, &chars[4], 0, 0);
        storageWbemObject->Get(L"Speed", 0, &chars[5], 0, 0);

        MEMORYSTATUS statex;
        GlobalMemoryStatus(&statex);
        storageWbemObject->Release();
        

        list.push_back(new RAM((int)statex.dwMemoryLoad, chars[3].bstrVal, chars[2].uintVal, chars[4].uintVal,
            chars[5].uintVal * statex.dwMemoryLoad / 100, chars[5].uintVal, (ULONGLONG)statex.dwTotalPhys));
    }
    return list;
}

unordered_map<string, string> RAM::ToMap(){

    unordered_map<string, string> map;
    map["Manufacturer"] = this->manufacturer;
    map["Memory type"] = this->memory_type;
    map["Used Memory"] = std::to_string(this->used_mem);
    map["Clock Speed"] = std::to_string(this->clock_speed);
    map["Speed"] = std::to_string(this->speed);
    map["Max Speed"] = std::to_string(this->max_speed);
    map["Capacity"] = std::to_string(this->capacity);

    return map;
}
