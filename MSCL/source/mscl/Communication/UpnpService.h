/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#pragma once

// Windows-only file
#ifdef _WIN32
#include <UPnP.h>

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

        IUPnPDeviceFinderCallback* m_deviceFinderCallback;
        IUPnPDeviceFinder* m_deviceFinder;
        BSTR m_description;
        LONG m_findDataIndex;
        bool m_findStarted;
        bool m_searching;
        bool m_shutdown;
        bool m_searchComplete;
        std::recursive_mutex m_upnpMutex;
        std::unique_ptr<std::thread> m_searchThread;

        bool startSearch();
        void findDevices();
        void cancelFindDevices();

    public:
        void setSearchComplete();
        void restartSearch();
    };
} // namespace mscl
#endif // _WIN32
