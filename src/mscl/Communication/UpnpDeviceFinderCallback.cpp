/*****************************************************************************************
**          Copyright(c) 2015-2026 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "mscl/Communication/UpnpDeviceFinderCallback.h"

namespace mscl
{
    UpnpDeviceFinderCallback::UpnpDeviceFinderCallback() :
        m_refCount(0)
    {}

    std::string UpnpDeviceFinderCallback::WstringToString(const std::wstring& in)
    {
        std::vector<char> buffer(in.length() + 1);
        WideCharToMultiByte(CP_ACP, 0, in.c_str(), -1, &buffer[0], static_cast<int>(buffer.size()), NULL, NULL);
        return std::string(&buffer[0]);
    }

    STDMETHODIMP UpnpDeviceFinderCallback::QueryInterface(REFIID iid, LPVOID* ppvObject)
    {
        HRESULT hr = S_OK;

        if(NULL == ppvObject) { hr = E_POINTER; }
        else { *ppvObject = NULL; }

        if(SUCCEEDED(hr))
        {
            if(IsEqualIID(iid, IID_IUnknown) || IsEqualIID(iid, IID_IUPnPDeviceFinderCallback))
            {
                *ppvObject = static_cast<IUPnPDeviceFinderCallback*>(this);
                AddRef();
            }
            else
            {
                hr = E_NOINTERFACE;
            }
        }

        return hr;
    }

    STDMETHODIMP_(ULONG) UpnpDeviceFinderCallback::AddRef()
    {
        return ::InterlockedIncrement(&m_refCount);
    }

    STDMETHODIMP_(ULONG) UpnpDeviceFinderCallback::Release()
    {
        LONG lRefCount = ::InterlockedDecrement(&m_refCount);
        if(0 == lRefCount)
        {
            delete this;
        }

        return lRefCount;
    }

    STDMETHODIMP UpnpDeviceFinderCallback::DeviceAdded(LONG lFindData, IUPnPDevice* pDevice)
    {
        (void)lFindData;

        if(m_deviceAddedCallback)
        {
            UpnpDevice device;

            BSTR bstrFriendlyName = NULL;
            pDevice->get_FriendlyName(&bstrFriendlyName);
            if(bstrFriendlyName != NULL)
            {
                device.friendlyName = WstringToString(bstrFriendlyName);
            }
            SysFreeString(bstrFriendlyName);

            BSTR bstrPresentationURL = NULL;
            pDevice->get_PresentationURL(&bstrPresentationURL);
            if(bstrPresentationURL != NULL)
            {
                device.presentationUrl = WstringToString(bstrPresentationURL);
            }
            SysFreeString(bstrPresentationURL);

            BSTR bstrDescription = NULL;
            pDevice->get_Description(&bstrDescription);
            if(bstrDescription != NULL)
            {
                device.description = WstringToString(bstrDescription);
            }
            SysFreeString(bstrDescription);

            BSTR bstrManufacturerName = NULL;
            pDevice->get_ManufacturerName(&bstrManufacturerName);
            if(bstrManufacturerName != NULL)
            {
                device.manufacturerName = WstringToString(bstrManufacturerName);
            }
            SysFreeString(bstrManufacturerName);

            BSTR bstrManufacturerURL = NULL;
            pDevice->get_ManufacturerURL(&bstrManufacturerURL);
            if(bstrManufacturerURL != NULL)
            {
                device.manufacturerUrl = WstringToString(bstrManufacturerURL);
            }
            SysFreeString(bstrManufacturerURL);

            BSTR bstrModelName = NULL;
            pDevice->get_ModelName(&bstrModelName);
            if(bstrModelName != NULL)
            {
                device.modelName = WstringToString(bstrModelName);
            }
            SysFreeString(bstrModelName);

            BSTR bstrModelNumber = NULL;
            pDevice->get_ModelNumber(&bstrModelNumber);
            if(bstrModelNumber != NULL)
            {
                device.modelNumber = WstringToString(bstrModelNumber);
            }
            SysFreeString(bstrModelNumber);

            BSTR bstrModelURL = NULL;
            pDevice->get_ModelURL(&bstrModelURL);
            if(bstrModelURL != NULL)
            {
                device.modelUrl = WstringToString(bstrModelURL);
            }
            SysFreeString(bstrModelURL);

            BSTR bstrSerialNumber = NULL;
            pDevice->get_SerialNumber(&bstrSerialNumber);
            if(bstrSerialNumber != NULL)
            {
                device.serialNumber = WstringToString(bstrSerialNumber);
            }
            SysFreeString(bstrSerialNumber);

            BSTR bstrType = NULL;
            pDevice->get_Type(&bstrType);
            if(bstrType != NULL)
            {
                device.type = WstringToString(bstrType);
            }
            SysFreeString(bstrType);

            BSTR bstrUniqueDeviceName = NULL;
            pDevice->get_UniqueDeviceName(&bstrUniqueDeviceName);
            if(bstrUniqueDeviceName != NULL)
            {
                device.uniqueDeviceName = WstringToString(bstrUniqueDeviceName);
            }
            SysFreeString(bstrUniqueDeviceName);

            BSTR bstrUPC = NULL;
            pDevice->get_UPC(&bstrUPC);
            if(bstrUPC != NULL)
            {
                device.upc = WstringToString(bstrUPC);
            }
            SysFreeString(bstrUPC);

            //call the callback function with the new device
            m_deviceAddedCallback(device);
        }

        return S_OK;
    }

    STDMETHODIMP UpnpDeviceFinderCallback::DeviceRemoved(LONG lFindData, BSTR bstrUDN)
    {
        (void)lFindData;
        (void)bstrUDN;
        return S_OK;
    }

    STDMETHODIMP UpnpDeviceFinderCallback::SearchComplete(LONG lFindData)
    {
        (void)lFindData;

        if(m_searchCompleteCallback)
        {
            m_searchCompleteCallback();
        }

        return S_OK;
    }

    void UpnpDeviceFinderCallback::bindSearchComplete(std::function<void()> callback)
    {
        m_searchCompleteCallback = callback;
    }

    void UpnpDeviceFinderCallback::bindDeviceAdded(std::function<void(const UpnpDevice&)> callback)
    {
        m_deviceAddedCallback = callback;
    }
} // namespace mscl
