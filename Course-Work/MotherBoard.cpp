#include "MotherBoard.h"

MotherBoard::MotherBoard()
{
    return;
}

MotherBoard::MotherBoard(BSTR caption, BSTR device_id, BSTR pr_bus_type, BSTR revis_num, BSTR sec_bus_type, BSTR status_info)
{
    this->caption = ConvertBSTRToMBS(caption);
    this->device_id = ConvertBSTRToMBS(device_id);
    this->primary_bus_type = ConvertBSTRToMBS(pr_bus_type);
    this->revision_num = ConvertBSTRToMBS(revis_num);
    this->secondary_bus_type = ConvertBSTRToMBS(sec_bus_type);
    this->status_info = ConvertBSTRToMBS(status_info);
}

MotherBoard* MotherBoard::GetMotherBoardInfo(HRESULT* hres, IWbemLocator* pLoc, IWbemServices* pSvc)
{
    IEnumWbemClassObject* enumerator = NULL;
    BSTR bstr_wql = SysAllocString(L"WQL");
    BSTR bstr_sql = SysAllocString(L"SELECT * FROM Win32_MotherboardDevice");

    *hres = pSvc->ExecQuery(
        bstr_wql,
        bstr_sql,
        WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
        NULL,
        &enumerator);

    if (FAILED(*hres)) {
        cout << "Query for Win32_MotherboardDevice Error code = 0x" << hex << hres << endl;
        pSvc->Release();
        pLoc->Release();
        CoUninitialize();
    }
    SysFreeString(bstr_wql);
    SysFreeString(bstr_sql);

    IWbemClassObject* storageWbemObject = NULL;
    ULONG uReturn = 0;
    MotherBoard* board;

    while (enumerator)
    {
        HRESULT hr = enumerator->Next(WBEM_INFINITE, 1, &storageWbemObject, &uReturn);
        if (0 == uReturn)
        {
            break;
        }

        VARIANT* chars = new VARIANT[6];

        storageWbemObject->Get(L"Caption", 0, &chars[0], 0, 0);
        storageWbemObject->Get(L"DeviceID", 0, &chars[1], 0, 0);
        storageWbemObject->Get(L"PrimaryBusType", 0, &chars[2], 0, 0);
        storageWbemObject->Get(L"RevisionNumber", 0, &chars[3], 0, 0);
        storageWbemObject->Get(L"SecondaryBusType", 0, &chars[4], 0, 0);
        storageWbemObject->Get(L"StatusInfo", 0, &chars[5], 0, 0);

        storageWbemObject->Release();

        board = new MotherBoard(chars[0].bstrVal, chars[1].bstrVal, chars[2].bstrVal,
                chars[3].bstrVal, chars[4].bstrVal, chars[5].bstrVal);
    }
    return board;
}

unordered_map<string, string> MotherBoard::ToMap(){

    unordered_map<string, string> map;

    map["Name"] = this->caption;
    map["Device ID"] = this->device_id;
    map["Primary Bus Type"] = this->primary_bus_type;
    map["Secondary Bus Type"] = this->secondary_bus_type;
    map["Revision Number"] = this->revision_num;
    map["Status Info"] = this->status_info;

    return map;
}
