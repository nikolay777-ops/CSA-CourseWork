#include "BaseLibs.h"

class RAM {
public:
	int used_mem;
	string manufacturer;
	unsigned int clock_speed;
	string memory_type;
	unsigned int speed;
	unsigned int max_speed;
	unsigned long capacity;

public:
	RAM();
	RAM(int used_mem, BSTR manufacturer, UINT clock_speed, UINT memory_type,
		UINT speed, UINT max_speed, ULONGLONG capacity);

	string GetPhysicalMemoryType(UINT type);
    static vector<RAM*> GetRamInfo(HRESULT* hres, IWbemLocator* pLoc, IWbemServices* pSvc);
    unordered_map<string, string> ToMap();

};
