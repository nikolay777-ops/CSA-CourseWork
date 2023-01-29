#include "BaseLibs.h"

class VideoAdapter {
    public:
	string name;
	UINT ram;
	string memory_type;
	string video_processor;
	string video_mode_desc;
	string dac_adapter;

public: 
	VideoAdapter();
	VideoAdapter(BSTR name, UINT ram, UINT memory_type, BSTR v_proc, BSTR vm_desc, BSTR dac);
	string GetMemoryType(UINT type);
    unordered_map<string, string> ToMap();
    static vector<VideoAdapter*> VideoAdapterInfo(HRESULT* hres, IWbemLocator* pLoc, IWbemServices* pSvc);
};
