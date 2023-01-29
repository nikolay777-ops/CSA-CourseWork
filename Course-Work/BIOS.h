#include "BaseLibs.h"

class BIOS {
private:
	string version;
	string caption;
	string build_number;
	string current_language;
	string manufacturer;
	string release_date;

public:
	BIOS();
	BIOS(BSTR version, BSTR caption, BSTR build_number, BSTR cur_lang, BSTR manuf, BSTR rel_data);

    static BIOS* GetBiosInfo(HRESULT* hres, IWbemLocator* pLoc, IWbemServices* pSvc);
    unordered_map<string, string> ToMap();
};
