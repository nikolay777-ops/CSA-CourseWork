#include "CacheLevel.h"

class Processor {
public:
	string architecture;
	string availability;
	string cpu_status;
	unsigned int max_speed;
	float current_speed;
	float current_voltage;
	unsigned short data_width;
	string name;
	unsigned int cores_num;
	unsigned int en_cores_num;
	string proc_type;
	unsigned int thread_count;
	float load_percentage;
    float max_voltage;
    vector<CacheLevel> cache;
public:
	Processor();
	// arch, avail_type, proc_type - get from cases CURRENT SPEED and CURRENT_VOLTAGE FROM METHODS
	Processor(UINT arch, UINT avail_type, float clock_speed, float voltage,
        UINT data_width, BSTR name, UINT cores, UINT en_cores, UINT proc_type, UINT t_count, float l_perc, UINT max_speed, float max_voltage);
	string GetArchitecture(UINT arch);
	string GetProcessorType(UINT type);
	string GetAvailableType(UINT type);
    unordered_map<string, string> ToMap();
    void SetCache(vector<CacheLevel> cache);


	void UpdateProcStats();
	static float GetCPULoad();
	static unsigned long long FileTimeToInt64(const FILETIME& ft);
	static float CalculateCPULoad(unsigned long long idleTicks, unsigned long long totalTicks);
    static Processor* GetProcessorInfo(HRESULT* hres, IWbemLocator* pLoc, IWbemServices* pSvc);
};

