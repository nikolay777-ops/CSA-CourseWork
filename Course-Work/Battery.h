#include "BaseLibs.h"

class Battery{
private:
	//get from switch case
	string battery_status;
	string chemistry;
	double design_capacity; // milliwatt-hours
	double design_voltage; // millivolts
	string device_id;
	float estimated_time; // in minutes --> hours 
	unsigned int full_charge_capacity;
	float full_charge_time; // in minutes --> hours

public:
	Battery();
	Battery(UINT bat_status, UINT chem, UINT des_capacity, UINT des_voltage, BSTR d_id, UINT estim_time, UINT f_ch_cap, UINT f_ch_t);
	string GetBatteryStatus(UINT type);
	string GetChemistryType(UINT type);

    static Battery* GetBatteryInfo(HRESULT* hres, IWbemLocator* pLoc, IWbemServices* pSvc);
    unordered_map<string, string> ToMap();
};
