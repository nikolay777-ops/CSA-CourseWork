#include "Battery.h"

Battery::Battery()
{
	return;
}

string Battery::GetBatteryStatus(UINT type)
{
    switch(type)
    {
        case 1: return "Other";
        case 2: return "Unknown";
        case 3: return "Fully Charged";
        case 4: return "Low";
        case 5: return "Critical";
        case 6: return "Charging";
        case 7: return "Chargingand High";
        case 8: return "Chargingand Low";
        case 9: return "Chargingand Critical";
        case 10: return "Undefined";
        case 11: return "Partially Charged";
    }
}

string Battery::GetChemistryType(UINT type)
{
    switch(type)
    {
    case 1: return "Other";
    case 2: return "Unknown";
    case 3: return "Lead Acid";
    case 4: return "Nickel Cadmium";
    case 5: return "Nickel Metal Hydride";
    case 6: return "Lithium - ion";
    case 7: return "Zinc air";
    case 8: return "Lithium Polymer";
    }
}

Battery::Battery(UINT bat_status, UINT chem, UINT des_capacity, UINT des_voltage, BSTR d_id, UINT estim_time, UINT f_ch_cap, UINT f_ch_t)
{
    this->battery_status = GetBatteryStatus(bat_status);
    this->chemistry = GetChemistryType(chem);
    this->design_capacity = (double)des_capacity / 1000;
    this->design_voltage = (double)des_voltage / 1000;
    this->device_id = ConvertBSTRToMBS(d_id);
    this->estimated_time = (float)estim_time / 60;
    this->full_charge_capacity = f_ch_cap;
    this->full_charge_time = (float)f_ch_t / 60;
}


Battery* Battery::GetBatteryInfo(HRESULT *hres, IWbemLocator *pLoc, IWbemServices *pSvc)
{
    IEnumWbemClassObject* enumerator = NULL;

    BSTR bstr_wql = SysAllocString(L"WQL");
    BSTR bstr_sql = SysAllocString(L"SELECT * FROM Win32_Battery");

    *hres = pSvc->ExecQuery(
        bstr_wql,
        bstr_sql,
        WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
        NULL,
        &enumerator);

    if (FAILED(*hres)) {
        cout << "Query for Win32_Battery Error code = 0x" << hex << hres << endl;
        pSvc->Release();
        pLoc->Release();
        CoUninitialize();
    }

    SysFreeString(bstr_wql);
    SysFreeString(bstr_sql);

    IWbemClassObject* storageWbemObject = NULL;
    ULONG uReturn = 0;
    Battery* battery;

    while (enumerator)
    {
        HRESULT hr = enumerator->Next(WBEM_INFINITE, 1, &storageWbemObject, &uReturn);
        if (0 == uReturn)
        {
            break;
        }

        VARIANT* chars = new VARIANT[8];
        
        storageWbemObject->Get(L"BatteryStatus", 0, &chars[0], 0, 0);
        storageWbemObject->Get(L"Chemistry", 0, &chars[1], 0, 0);
        storageWbemObject->Get(L"DesignCapacity", 0, &chars[2], 0, 0);
        storageWbemObject->Get(L"DesignVoltage", 0, &chars[3], 0, 0);
        storageWbemObject->Get(L"DeviceID", 0, &chars[4], 0, 0);
        storageWbemObject->Get(L"EstimatedRunTime", 0, &chars[5], 0, 0);
        storageWbemObject->Get(L"FullChargedCapacity", 0, &chars[6], 0, 0);
        storageWbemObject->Get(L"TimeToFullCharge", 0, &chars[7], 0, 0);

        storageWbemObject->Release();

        battery = new Battery(chars[0].uintVal, chars[1].uintVal, chars[2].uintVal, chars[3].uintVal,
            chars[4].bstrVal, chars[5].uintVal, chars[6].uintVal, chars[7].uintVal);
        delete[] chars;
    }
    return battery;
}

unordered_map<string, string> Battery::ToMap(){

    unordered_map<string, string> map;

    map["Device ID"] = this->device_id;
    map["Battery Status"] = this->battery_status;
    map["Chemistry"] = this->chemistry;
    map["Design Capacity"] = std::to_string(this->design_capacity);
    map["Design Voltage"] = std::to_string(this->design_voltage);
    map["Estimated Time"] = std::to_string(estimated_time / 60);
    map["Full Charge Capacity"] = std::to_string(this->full_charge_capacity);
    map["Full Charge Time"] = std::to_string(this->full_charge_time / 60);

    return map;
}
