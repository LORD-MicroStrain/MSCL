/*******************************************************************************
Copyright(c) 2015-2018 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/

#pragma once

#ifdef _WIN32
#include <UPnP.h>   //Windows only file
#include <Windows.h>

#include <map>
#include <string>
#include <thread>

namespace mscl
{
    class UpnpService
    {
    public:
        UpnpService(IUPnPDeviceFinderCallback& callback, BSTR description);
        ~UpnpService();

    private:
        UpnpService(const UpnpService&);              //copy constructor disabled
        UpnpService& operator=(const UpnpService&);   //assignment operator disabled

    private:
        IUPnPDeviceFinderCallback* m_deviceFinderCallback;
        IUPnPDeviceFinder* m_deviceFinder;
        BSTR m_description;
        LONG m_findDataIndex;
        bool m_findStarted;
        bool m_searching;
        bool m_shutdown;
        bool m_searchComplete;
        std::unique_ptr<std::thread> m_searchThread;

    private:
        bool startSearch();
        void findDevices();

    public:
        void setSearchComplete();
        void cancelFindDevices();
    };
}

#endif