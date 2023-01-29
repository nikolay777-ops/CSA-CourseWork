#include "NetworkAdapter.h"

NetworkAdapter::NetworkAdapter()
{
    return;
}

string NetworkAdapter::GetNetConnectionType(UINT type)
{
    switch(type)
    {
        case 0: return "Disconnected";
        case 1: return "Connecting";
        case 2: return "Connected";
        case 3: return "Disconnecting";
        case 4: return "Hardware Not Present";
        case 5: return "Hardware Disabled";
        case 6: return "Hardware Malfunction";
        case 7: return "Media Disconnected";
        case 8: return "Authenticating";
        case 9: return "Authentication Succeeded";
        case 10: return "Authentication Failed";
        case 11: return "Invalid Address";
        case 12: return "Credentials Required";
    }
}

NetworkAdapter::NetworkAdapter(BSTR adapter_type, BSTR caption, BSTR mac_address, BSTR manufacturer, ULONG max_speed, ULONG current_speed, UINT net_connection)
{
    this->adapter_type = ConvertBSTRToMBS(adapter_type);
    this->caption = ConvertBSTRToMBS(caption);
    this->mac_address = ConvertBSTRToMBS(mac_address);
    this->manufacturer = ConvertBSTRToMBS(manufacturer);
    this->max_speed = max_speed;
    this->current_speed = current_speed;
    this->net_connection = GetNetConnectionType(net_connection);
}

vector<NetworkAdapter*> NetworkAdapter::GetNetworkAdapterInfo(HRESULT* hres, IWbemLocator* pLoc, IWbemServices* pSvc)
{
    IEnumWbemClassObject* enumerator = NULL;
    BSTR bstr_wql = SysAllocString(L"WQL");
    BSTR bstr_sql = SysAllocString(L"SELECT * FROM Win32_NetworkAdapter");

    *hres = pSvc->ExecQuery(
        bstr_wql,
        bstr_sql,
        WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
        NULL,
        &enumerator);

    if (FAILED(*hres)) {
        cout << "Query for Win32_NetworkAdapter Error code = 0x" << hex << hres << endl;
        pSvc->Release();
        pLoc->Release();
        CoUninitialize();
    }
    SysFreeString(bstr_wql);
    SysFreeString(bstr_sql);


    IWbemClassObject* storageWbemObject = NULL;
    ULONG uReturn = 0;
    vector<NetworkAdapter*> list;

    while (enumerator)
    {
        HRESULT hr = enumerator->Next(WBEM_INFINITE, 1, &storageWbemObject, &uReturn);
        if (0 == uReturn)
        {
            break;
        }

        VARIANT* chars = new VARIANT[7];



        storageWbemObject->Get(L"AdapterType", 0, &chars[0], 0, 0);
        storageWbemObject->Get(L"Caption", 0, &chars[1], 0, 0);
        storageWbemObject->Get(L"MACAddress", 0, &chars[2], 0, 0);
        storageWbemObject->Get(L"Manufacturer", 0, &chars[3], 0, 0);
        storageWbemObject->Get(L"MaxSpeed", 0, &chars[4], 0, 0);
        storageWbemObject->Get(L"Speed", 0, &chars[5], 0, 0);
        storageWbemObject->Get(L"NetConnectionStatus", 0, &chars[6], 0, 0);

        list.push_back(new NetworkAdapter(chars[0].bstrVal, chars[1].bstrVal, chars[2].bstrVal,
                chars[3].bstrVal, chars[4].ulVal, chars[5].ulVal, chars[6].uintVal));

        storageWbemObject->Release();
        delete[] chars;
    }
    return list;
}

unordered_map<string, string> NetworkAdapter::ToMap(){

    unordered_map<string, string> map;
    map["Name"] = this->caption;
    map["Manufacturer"] = this->manufacturer;
    map["Adapter"] = this->adapter_type;
    map["MAC Address"] = this->mac_address;
    map["Max speed"] = std::to_string(this->max_speed);
    map["Current speed"] = std::to_string(this->current_speed);
    map["Network Connection"] = this->net_connection;

    return map;
}
