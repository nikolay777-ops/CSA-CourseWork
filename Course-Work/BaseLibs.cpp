#include "BaseLibs.h"

int wmi_initialize(HRESULT* hres, IWbemLocator** pLoc, IWbemServices** pSvc) {
    *hres = CoCreateInstance(
        CLSID_WbemLocator,
        0,
        CLSCTX_INPROC_SERVER,
        IID_IWbemLocator, (LPVOID*)pLoc);

    if (FAILED(*hres))
    {
        cout << "Failed to create IWbemLocator object. "
            << "Err code = 0x"
            << hex << *hres << endl;
        CoUninitialize();
        return 1;
    }

    *hres = (*pLoc)->ConnectServer(
        _bstr_t(L"ROOT\\CIMV2"),
        NULL,
        NULL,
        0,
        NULL,
        0,
        0,
        pSvc
    );

    if (FAILED(*hres))
    {
        cout << "Could not connect. Error code = 0x"
            << hex << hres << endl;
        (*pLoc)->Release();
        CoUninitialize();
        return 1;                // Program has failed.
    }

    *hres = CoSetProxyBlanket(
        *pSvc,                        // Indicates the proxy to set
        RPC_C_AUTHN_WINNT,           // RPC_C_AUTHN_xxx
        RPC_C_AUTHZ_NONE,            // RPC_C_AUTHZ_xxx
        NULL,                        // Server principal name
        RPC_C_AUTHN_LEVEL_CALL,      // RPC_C_AUTHN_LEVEL_xxx
        RPC_C_IMP_LEVEL_IMPERSONATE, // RPC_C_IMP_LEVEL_xxx
        NULL,                        // client identity
        EOAC_NONE                    // proxy capabilities
    );

    if (FAILED(*hres))
    {
        cout << "Could not set proxy blanket. Error code = 0x"
            << hex << *hres << endl;
        (*pSvc)->Release();
        (*pLoc)->Release();
        CoUninitialize();
        return 1;
    }
    return 0;
}

string ConvertWCSToMBS(const wchar_t* pstr, long wslen)
{
    int len = ::WideCharToMultiByte(CP_ACP, 0, pstr, wslen, NULL, 0, NULL, NULL);

    string dblstr(len, '\0');
    len = ::WideCharToMultiByte(CP_ACP, 0, pstr, wslen, &dblstr[0], len, NULL, NULL);

    return dblstr;
}

string ConvertBSTRToMBS(BSTR bstr)
{
    int wslen = ::SysStringLen(bstr);
    return ConvertWCSToMBS((wchar_t*)bstr, wslen);
}
