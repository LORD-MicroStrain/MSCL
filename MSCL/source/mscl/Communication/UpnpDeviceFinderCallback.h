/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/

#pragma once

#ifdef _WIN32
#include <UPnP.h>   //Windows only file
#include <functional>

namespace mscl
{
    //Struct: UpnpDevice
    //  Contains information about an added upnp device.
    struct UpnpDevice
    {
        std::string description;
        std::string friendlyName;
        std::string manufacturerName;
        std::string manufacturerUrl;
        std::string modelName;
        std::string modelNumber;
        std::string modelUrl;
        std::string presentationUrl;
        std::string serialNumber;
        std::string type;
        std::string uniqueDeviceName;
        std::string upc;
    };


    class UpnpDeviceFinderCallback : public IUPnPDeviceFinderCallback
    {
    public:
        UpnpDeviceFinderCallback();

    private:
        UpnpDeviceFinderCallback(const UpnpDeviceFinderCallback&);              //copy constructor disabled
        UpnpDeviceFinderCallback& operator=(const UpnpDeviceFinderCallback&);   //assignment operator disabled

        static std::string WstringToString(const std::wstring& in);

    private:
        long m_refCount;
        std::function<void()> m_searchCompleteCallback;
        std::function<void(const UpnpDevice&)> m_deviceAddedCallback;

    public:
        STDMETHODIMP QueryInterface(REFIID iid, LPVOID* ppvObject);
        STDMETHODIMP_(ULONG) AddRef();
        STDMETHODIMP_(ULONG) Release();

        STDMETHODIMP DeviceAdded(LONG lFindData, IUPnPDevice* pDevice);
        STDMETHODIMP DeviceRemoved(LONG lFindData, BSTR bstrUDN);
        STDMETHODIMP SearchComplete(LONG lFindData);

        void bindSearchComplete(std::function<void()> callback);
        void bindDeviceAdded(std::function<void(const UpnpDevice&)> callback);
    };
}
#endif