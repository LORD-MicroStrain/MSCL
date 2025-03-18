/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#ifdef _WIN32

#include "mscl/WMI_Helper.h"

#include <comdef.h>

WMI_Helper::WMI_Helper(std::string wmi_namespace, std::string wmi_class) :
    m_wmi_namespace(wmi_namespace),
    m_wmi_class(wmi_class),
    m_enumerator(nullptr)
{
}

WMI_Helper::~WMI_Helper()
{
    //close down the WMI Service
    CoUninitialize();
}

void WMI_Helper::connect()
{
    HRESULT hres;
    std::stringstream error;

    // Step 1: --------------------------------------------------
    // Initialize COM. ------------------------------------------

    hres =  CoInitializeEx(0, COINIT_MULTITHREADED);

    //if we failed to intialize COM library
    if (FAILED(hres))
    {
        //throw an exception, Program has failed.
        error << "Failed to initialize COM library. Error code = 0x" << std::hex << hres;
        throw std::exception(error.str().c_str());
    }

    // Step 2: --------------------------------------------------
    // Set general COM security levels --------------------------
    // Note: If you are using Windows 2000, you need to specify -
    // the default authentication credentials for a user by using
    // a SOLE_AUTHENTICATION_LIST structure in the pAuthList ----
    // parameter of CoInitializeSecurity ------------------------

    hres =  CoInitializeSecurity(
        NULL,
        -1,                          // COM authentication
        NULL,                        // Authentication services
        NULL,                        // Reserved
        RPC_C_AUTHN_LEVEL_DEFAULT,   // Default authentication
        RPC_C_IMP_LEVEL_IMPERSONATE, // Default Impersonation
        NULL,                        // Authentication info
        EOAC_NONE,                   // Additional capabilities
        NULL                         // Reserved
        );


    //if we failed to initialize security
    if (FAILED(hres) && (hres != RPC_E_TOO_LATE))
    {
        CoUninitialize();

        //throw an exception, Program has failed.
        error << "Failed to initialize security. Error code = 0x" << std::hex << hres;
        throw std::exception(error.str().c_str());
    }

    // Step 3: ---------------------------------------------------
    // Obtain the initial locator to WMI -------------------------

    IWbemLocator *pLoc = NULL;

    hres = CoCreateInstance(
        CLSID_WbemLocator,
        0,
        CLSCTX_INPROC_SERVER,
        IID_IWbemLocator, (LPVOID *) &pLoc);

    //if we failed to create the initial locator to WMI
    if (FAILED(hres))
    {
        CoUninitialize();

        //throw an exception, Program has failed.
        error << "Failed to create IWbemLocator object. Error code = 0x" << std::hex << hres;
        throw std::exception(error.str().c_str());
    }

    // Step 4: -----------------------------------------------------
    // Connect to WMI through the IWbemLocator::ConnectServer method

    IWbemServices *pSvc = NULL;

    // Connect to a namespace with
    // the current user and obtain pointer pSvc
    // to make IWbemServices calls.
    hres = pLoc->ConnectServer(
        _bstr_t(m_wmi_namespace.c_str()),    // Object path of WMI namespace
         NULL,                                // User name. NULL = current user
         NULL,                                // User password. NULL = current
         0,                                    // Locale. NULL indicates current
         NULL,                                // Security flags.
         0,                                    // Authority (for example, Kerberos)
         0,                                    // Context object
         &pSvc                                // pointer to IWbemServices proxy
         );

    if (FAILED(hres))
    {
        pLoc->Release();
        CoUninitialize();

        //throw an exception, program has failed
        error << "Could not connect to namespace " << m_wmi_namespace << ". Error code = 0x" << std::hex << hres;
        throw std::exception(error.str().c_str());
    }

    // Step 5: --------------------------------------------------
    // Set security levels on the proxy -------------------------

    hres = CoSetProxyBlanket(
       pSvc,                        // Indicates the proxy to set
       RPC_C_AUTHN_WINNT,           // RPC_C_AUTHN_xxx
       RPC_C_AUTHZ_NONE,            // RPC_C_AUTHZ_xxx
       NULL,                        // Server principal name
       RPC_C_AUTHN_LEVEL_CALL,      // RPC_C_AUTHN_LEVEL_xxx
       RPC_C_IMP_LEVEL_IMPERSONATE, // RPC_C_IMP_LEVEL_xxx
       NULL,                        // client identity
       EOAC_NONE                    // proxy capabilities
    );

    if (FAILED(hres))
    {
        pSvc->Release();
        pLoc->Release();
        CoUninitialize();

        //throw an exception, Program has failed.
        error << "Could not set proxy blanket. Error code = 0x" << std::hex << hres;
        throw std::exception(error.str().c_str());
    }

    // Step 6: --------------------------------------------------
    // Use the IWbemServices pointer to make requests of WMI ----

    //build the query to send
    std::stringstream query;
    query << "SELECT * FROM " << m_wmi_class;

    m_enumerator = NULL;

    hres = pSvc->ExecQuery(
        bstr_t("WQL"),
        bstr_t(query.str().c_str()),
        WBEM_FLAG_RETURN_IMMEDIATELY,
        NULL,
        &m_enumerator);

    if (FAILED(hres))
    {
        pSvc->Release();
        pLoc->Release();
        CoUninitialize();

        //throw an exception, Program has failed
        error << "Query: '" << query.str() << "' has failed. Error code = 0x" << std::hex << hres;
        throw std::exception(error.str().c_str());
    }

    // Cleanup
    // ========

    pSvc->Release();
    pLoc->Release();
}

void WMI_Helper::requestThread(std::vector<std::string> valuesToGet)
{
    connect();

    IWbemClassObject *pclsObj;
    ULONG uReturn = 0;

    //reset the enumerator back to the start, to allow for multiple requests
    m_enumerator->Reset();

    //loop through every item that was found
    while (m_enumerator)
    {
        //get the next item
        HRESULT hr = m_enumerator->Next(WBEM_INFINITE, 1, &pclsObj, &uReturn);

        if(uReturn == 0)
        {
            break;
        }

        wmiValue valueToAdd;

        //for each value that the user requested
        for(std::string valueName : valuesToGet)
        {
            //convert to a wstring
            std::wstring stemp = std::wstring(valueName.begin(), valueName.end());

            VARIANT vtProp;

            // Get the value of the requested property
            hr = pclsObj->Get(stemp.c_str(), 0, &vtProp, 0, 0);

            //if this value wasn't found
            if(FAILED(hr))
            {
                std::stringstream error;
                error << "Failed to find value for " << valueName;
                throw std::exception(error.str().c_str());
            }

            //add to the map
            valueToAdd[valueName] = vtProp;
        }

        //add the new map of values to the result vector
        m_values.push_back(valueToAdd);

        pclsObj->Release();
    }
}

WMI_Helper::wmiValues WMI_Helper::request(std::vector<std::string> valuesToGet)
{
    std::thread t(&WMI_Helper::requestThread, this, valuesToGet);

    t.join();

    return m_values;
}
#endif // _WIN32
