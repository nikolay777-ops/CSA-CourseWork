#include "BIOS.h"

BIOS::BIOS()
{

}

BIOS::BIOS(BSTR version, BSTR caption, BSTR build_number, BSTR cur_lang, BSTR manuf, BSTR rel_data)
{
	this->version = ConvertBSTRToMBS(version);
	this->caption = ConvertBSTRToMBS(caption);
	this->build_number = ConvertBSTRToMBS(build_number);
	this->current_language = ConvertBSTRToMBS(cur_lang);
	this->manufacturer = ConvertBSTRToMBS(manuf);
	this->release_date = ConvertBSTRToMBS(rel_data);
}

BIOS* BIOS::GetBiosInfo(HRESULT* hres, IWbemLocator* pLoc, IWbemServices* pSvc)
{
    IEnumWbemClassObject* enumerator = NULL;

    BSTR bstr_wql = SysAllocString(L"WQL");
    BSTR bstr_sql = SysAllocString(L"SELECT * FROM Win32_BIOS");


    *hres = pSvc->ExecQuery(
        bstr_wql,
        bstr_sql,
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
    BIOS* bios;

    while (enumerator)
    {
        HRESULT hr = enumerator->Next(WBEM_INFINITE, 1, &storageWbemObject, &uReturn);
        if (0 == uReturn)
        {
            break;
        }

        VARIANT* chars = new VARIANT[6];

        storageWbemObject->Get(L"BIOSVersion", 0, &chars[0], 0, 0);
        storageWbemObject->Get(L"Caption", 0, &chars[1], 0, 0);
        storageWbemObject->Get(L"BuildNumber", 0, &chars[2], 0, 0);
        storageWbemObject->Get(L"CurrentLanguage", 0, &chars[3], 0, 0);
        storageWbemObject->Get(L"Manufacturer", 0, &chars[4], 0, 0);
        storageWbemObject->Get(L"ReleaseDate", 0, &chars[5], 0, 0);
        storageWbemObject->Get(L"TargetOperationSystem", 0, &chars[6], 0, 0);

        storageWbemObject->Release();

        bios = new BIOS(chars[0].bstrVal, chars[1].bstrVal, chars[2].bstrVal, chars[3].bstrVal, chars[4].bstrVal, chars[5].bstrVal);
    }
    return bios;
}

unordered_map<string, string> BIOS::ToMap(){

    unordered_map<string, string> map;
    map["Name"] = this->caption;
    map["Manufacturer"] = this->manufacturer;
    map["Version"] = this->version;
    map["Build Number"] = this->build_number;
    map["Current language"] = this->current_language;
    map["Release Date"] = this->release_date;

    return map;
}
