#include "CacheLevel.h"

CacheLevel::CacheLevel(UINT cache_type, UINT c_size, UINT c_speed, BSTR name)
{
    this->cache_type = GetCacheType(cache_type);
    this->cache_speed = c_speed;
    this->cache_size = c_size;
    this->name = ConvertBSTRToMBS(name);
}

string CacheLevel::GetCacheType(UINT type)
{
    switch(type)
    {
        case 1: return "Other";
        case 2: return "Unknown";
        case 3: return "Instruction";
        case 4: return "Data";
        case 5: return "Unified";
    }
}

vector<CacheLevel> CacheLevel::GetCacheInfo(HRESULT* hres, IWbemLocator* pLoc, IWbemServices* pSvc)
{
    IEnumWbemClassObject* enumerator = NULL;
    BSTR bstr_wql = SysAllocString(L"WQL");
    BSTR bstr_sql = SysAllocString(L"SELECT * FROM Win32_CacheMemory");

    *hres = pSvc->ExecQuery(
        bstr_wql,
        bstr_sql,
        WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
        NULL,
        &enumerator);

    if (FAILED(*hres)) {
        cout << "Query for Win32_CacheMemory Error code = 0x" << hex << hres << endl;
        pSvc->Release();
        pLoc->Release();
        CoUninitialize();
    }

    SysFreeString(bstr_wql);
    SysFreeString(bstr_sql);

    IWbemClassObject* storageWbemObject = NULL;
    ULONG uReturn = 0;

    vector<CacheLevel> cache;
    while (enumerator)
    {
        HRESULT hr = enumerator->Next(WBEM_INFINITE, 1, &storageWbemObject, &uReturn);
        if (0 == uReturn)
        {
            break;
        }

        VARIANT* chars = new VARIANT[4];
        string cache_type;
        unsigned int cache_size;
        unsigned int cache_speed;
        string name;


        storageWbemObject->Get(L"CacheType", 0, &chars[0], 0, 0);
        storageWbemObject->Get(L"SystemName", 0, &chars[1], 0, 0);
        storageWbemObject->Get(L"MaxCacheSize", 0, &chars[2], 0, 0);
        storageWbemObject->Get(L"CacheSpeed", 0, &chars[3], 0, 0);
        
        cache.push_back(CacheLevel(chars[0].uintVal, chars[2].uintVal, chars[3].uintVal, chars[1].bstrVal));

       /* float cpu_load = Processor::GetCPULoad();
        proc = Processor(chars[0].uintVal, chars[1].uintVal, chars[3].uintVal * cpu_load,
            chars[11].llVal * cpu_load, chars[4].uintVal, chars[5].bstrVal, chars[6].uintVal, chars[7].uintVal,
            chars[8].uintVal, chars[9].uintVal, cpu_load, chars[3].uintVal);
            */
        storageWbemObject->Release();
        delete[] chars;
    }


    pLoc->Release();
    pSvc->Release();
    CoUninitialize();
    return cache;
}
