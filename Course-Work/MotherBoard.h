#include "BaseLibs.h"

class MotherBoard {
private:
	string caption;
	string device_id;
	string primary_bus_type;
	string revision_num;
	string secondary_bus_type;
	string status_info;

public:
	MotherBoard();
	MotherBoard(BSTR caption, BSTR device_id, BSTR pr_bus_type, BSTR revis_num, BSTR sec_bus_type, BSTR status_info);

    static MotherBoard* GetMotherBoardInfo(HRESULT* hres, IWbemLocator* pLoc, IWbemServices* pSvc);
	static string GetBusType(UINT type);
    unordered_map<string, string> ToMap();
};
