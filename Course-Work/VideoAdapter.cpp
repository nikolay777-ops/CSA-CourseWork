#include "VideoAdapter.h"
#include <list>


VideoAdapter::VideoAdapter(BSTR name, UINT ram, UINT memory_type, BSTR v_proc, BSTR vm_desc, BSTR dac)
{
    this->name = ConvertBSTRToMBS(name);
    this->ram = ram / 1000000000;
    this->memory_type = GetMemoryType(memory_type);
    this->video_processor = ConvertBSTRToMBS(v_proc);
    this->video_mode_desc = ConvertBSTRToMBS(vm_desc);
    this->dac_adapter = ConvertBSTRToMBS(dac);
}

VideoAdapter::VideoAdapter() 
{
    return;
}

string VideoAdapter::GetMemoryType(UINT type) {
    switch (type) {
        case 1: return "Other";
        case 2: return "Unknown";
        case 3: return "VRAM";
        case 4: return "DRAM";
        case 5: return "SRAM";
        case 6: return "WRAM";
        case 7: return "EDO RAM";
        case 8: return "Burst Synchronous DRAM";
        case 9: return "Pipelined Burst RAM";
        case 10: return "CDRAM";
        case 11: return "3DRAM";
        case 12: return "SDRAM";
        case 13: return "SGRAM";
        default: return "Unkown";
    }
}

vector<VideoAdapter*> VideoAdapter::VideoAdapterInfo(HRESULT* hres, IWbemLocator* pLoc, IWbemServices* pSvc)
{
    vector<VideoAdapter*> list;
    IEnumWbemClassObject* enumerator = NULL;
    BSTR bstr_wql = SysAllocString(L"WQL");
    BSTR bstr_sql = SysAllocString(L"SELECT * FROM Win32_VideoController");

    *hres = pSvc->ExecQuery(
        bstr_wql,
        bstr_sql,
        WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
        NULL,
        &enumerator);

    if (FAILED(*hres)) {
        cout << "Query for Win32_VideoController Error code = 0x" << hex << hres << endl;
        pSvc->Release();
        pLoc->Release();
        CoUninitialize();
    }
    SysFreeString(bstr_wql);
    SysFreeString(bstr_sql);

    IWbemClassObject* storageWbemObject = NULL;
    ULONG uReturn = 0;

    while (enumerator)
    {
        HRESULT hr = enumerator->Next(WBEM_INFINITE, 1, &storageWbemObject, &uReturn);
        if (0 == uReturn)
        {
            break;
        }

        VARIANT caption;
        VARIANT ram;
        VARIANT mem_type;
        VARIANT v_proc;
        VARIANT v_mode_desc;
        VARIANT dac_type;

        storageWbemObject->Get(L"Name", 0, &caption, 0, 0);
        storageWbemObject->Get(L"AdapterRAM", 0, &ram, 0, 0);
        storageWbemObject->Get(L"VideoMemoryType", 0, &mem_type, 0, 0);
        storageWbemObject->Get(L"VideoProcessor", 0, &v_proc, 0, 0);
        storageWbemObject->Get(L"VideoModeDescription", 0, &v_mode_desc, 0, 0);
        storageWbemObject->Get(L"AdapterDACType", 0, &dac_type, 0, 0);

        VideoAdapter* va = new VideoAdapter(caption.bstrVal, ram.uintVal, mem_type.uintVal, v_proc.bstrVal, v_mode_desc.bstrVal, dac_type.bstrVal);
        list.push_back(va);
        storageWbemObject->Release();
    }
    return list;
}

unordered_map<string, string> VideoAdapter::ToMap(){

    unordered_map<string, string> map;
    map["Name"] = this->name;
    map["RAM"] = std::to_string(this->ram);
    map["Memory Type"] = this->memory_type;
    map["Video Processor"] = this->video_processor;
    map["Video Mode"] = this->video_mode_desc;
    map["DAC Adapter"] = this->dac_adapter;

    return map;
}
