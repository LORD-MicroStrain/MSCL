/*****************************************************************************************
**          Copyright(c) 2015-2026 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "mscl/Communication/UpnpService.h"

namespace mscl
{
    UpnpService::UpnpService(IUPnPDeviceFinderCallback& callback, BSTR description) :
        m_deviceFinderCallback(&callback),
        m_deviceFinder(nullptr),
        m_description(description),
        m_findDataIndex(0),
        m_findStarted(false),
        m_searching(false),
        m_shutdown(false),
        m_searchComplete(false)
    {
        //start searching for devices immediately
        m_searchThread.reset(new std::thread(&UpnpService::findDevices, this));
    }

    UpnpService::~UpnpService()
    {
        m_shutdown = true;
        m_searchThread->join();
    }

    bool UpnpService::startSearch()
    {
        bool success = false;

        HRESULT hr = S_OK;
        hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
        if(hr == RPC_E_CHANGED_MODE)
        {
            CoUninitialize();
            hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
        }

        if(!SUCCEEDED(hr))
        {
            throw Error("Failed to initialize UPnP search");
        }

        if(m_deviceFinderCallback != nullptr)
        {
            m_deviceFinderCallback->AddRef();

            hr = CoCreateInstance(CLSID_UPnPDeviceFinder, NULL, CLSCTX_INPROC_SERVER, IID_IUPnPDeviceFinder, reinterpret_cast<void**>(&m_deviceFinder));

            if(SUCCEEDED(hr))
            {
                hr = m_deviceFinder->CreateAsyncFind(m_description, NULL, m_deviceFinderCallback, &m_findDataIndex);

                if(SUCCEEDED(hr))
                {
                    hr = m_deviceFinder->StartAsyncFind(m_findDataIndex);

                    if(SUCCEEDED(hr))
                    {
                        success = true;
                    }
                }
            }
            else
            {
                if(m_deviceFinder)
                {
                    m_deviceFinder->Release();
                }
            }
        }
        else
        {
            if(m_deviceFinderCallback)
            {
                m_deviceFinderCallback->Release();
            }
        }

        return success;
    }

    void UpnpService::findDevices()
    {
        try
        {
            MSG message;

            //loop until asked to shut down
            while(!m_shutdown)
            {
                {
                    rec_mutex_lock_guard lock(m_upnpMutex);

                    //if there isn't a search already in progress
                    if(!m_searching)
                    {
                        if(startSearch())
                        {
                            m_searching = true;
                        }
                        else
                        {
                            //TODO: failed to start upnpservice, do something else here?
                            return;
                        }
                    }

                    if(m_searchComplete)
                    {
                        cancelFindDevices();
                    }

                }//unlock mutex

                // STA threads must pump messages
                while(PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
                {
                    DispatchMessage(&message);
                }
                Utils::threadSleep(250);
            }

            cancelFindDevices();
            CoUninitialize();
        }
        catch(...)
        {}
    }

    void UpnpService::setSearchComplete()
    {
        rec_mutex_lock_guard lock(m_upnpMutex);

        //sets the search to complete so that the current search loop
        //will terminate and a new search process will begin
        m_searchComplete = true;
    }

    void UpnpService::cancelFindDevices()
    {
        rec_mutex_lock_guard lock(m_upnpMutex);

        if(m_deviceFinder)
        {
            m_deviceFinder->CancelAsyncFind(m_findDataIndex);
            m_deviceFinder->Release();
            m_deviceFinder = nullptr;
        }

        m_searchComplete = false;
        m_searching = false;
    }

    void UpnpService::restartSearch()
    {
        setSearchComplete();
    }
} // namespace mscl
