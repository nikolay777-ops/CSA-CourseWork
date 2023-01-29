#include "BaseLibs.h"

class NetworkAdapter {
public:
	string adapter_type;
	string caption;
	string mac_address;
	string manufacturer;
	ULONG max_speed;
	ULONG current_speed;
	string net_connection;

public:
	NetworkAdapter();
	NetworkAdapter(BSTR adapter_type, BSTR caption, BSTR mac_address, BSTR manufacturer, ULONG max_speed, ULONG current_speed, UINT net_connection);
	string GetNetConnectionType(UINT type);

    unordered_map<string, string> ToMap();
    static vector<NetworkAdapter*> GetNetworkAdapterInfo(HRESULT* hres, IWbemLocator* pLoc, IWbemServices* pSvc);
	static string GetBusType(UINT type);
};
