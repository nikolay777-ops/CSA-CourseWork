#include <iostream>
using namespace std;
#include <comdef.h>
#include <Wbemidl.h>
#include <profileapi.h>
#include <vector>
#include <unordered_map>

#define RPC_E_CHANGED_MODE               _HRESULT_TYPEDEF_(0x80010106L)

int wmi_initialize(HRESULT* hres, IWbemLocator** pLoc, IWbemServices** pSvc);
string ConvertWCSToMBS(const wchar_t* pstr, long wslen);
string ConvertBSTRToMBS(BSTR bstr);
