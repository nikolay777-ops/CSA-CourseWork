#include "BaseLibs.h"

class CacheLevel {
private:
	string cache_type;
	unsigned int cache_size;
	unsigned int cache_speed;
	string name;
public:
	CacheLevel();
	CacheLevel(UINT cache_type, UINT c_size, UINT c_speed, BSTR name);

	static string GetCacheType(UINT type);
    static vector<CacheLevel> GetCacheInfo(HRESULT* hres, IWbemLocator* pLoc, IWbemServices* pSvc);
};
