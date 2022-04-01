/*****************************************************************************************
**          Copyright(c) 2015-2022 Parker Hannifin Corp. All rights reserved.           **
**                                                                                      **
**    MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.    **
*****************************************************************************************/

#include "stdafx.h"
#include "WsdaFinder.h"
#include <tchar.h>

namespace mscl
{
    WsdaInfo::WsdaInfo()
    { }

    WsdaInfo::WsdaInfo(std::string url, std::string serial) :
        m_url(url),
        m_serial(serial)
    { }

    std::string WsdaInfo::ipAddress() const
    {
        size_t pathStart = std::string::npos;
        size_t serviceEnd = std::string::npos;

        if((serviceEnd = m_url.find("://")) != std::string::npos)
        {
            pathStart = m_url.find_first_of("/?", serviceEnd + 3);
            
            if(pathStart != std::string::npos)
            {
                return m_url.substr(serviceEnd + 3, pathStart - (serviceEnd + 3));
            }
        }

        return "";
    }

    uint16 WsdaInfo::port() const
    {
        return 5000;
    }
    
    std::string WsdaInfo::name() const
    {
        return m_serial;
    }
    

    WsdaFinder::WsdaFinder()
    {
        start();
    }

    WsdaFinder::~WsdaFinder()
    {
        m_upnpService.reset(nullptr);

        if(m_upnpSearchCallback)
        {
            m_upnpSearchCallback->Release();
        }
    }

    void WsdaFinder::start()
    {
        m_upnpSearchCallback.reset(new UpnpDeviceFinderCallback());
        m_upnpSearchCallback->AddRef();
        m_upnpSearchCallback->bindSearchComplete(std::bind(&WsdaFinder::onSearchComplete, this));
        m_upnpSearchCallback->bindDeviceAdded(std::bind(&WsdaFinder::onDeviceAdded, this, std::placeholders::_1));

        m_upnpService.reset(new UpnpService(*m_upnpSearchCallback, L"urn:www-microstrain-com:device:wsda:1"));
    }

    void WsdaFinder::onSearchComplete()
    {
        //Note: this search complete callback doesn't actually indicate the process has stopped -
        //      just that it has completed the search for the devices that were already attached when
        //      starting the search. Any new add/remove notifications will still fire.
        std::unique_lock<std::mutex> lock(m_wsdaMapMutex);
        m_foundWsdas = m_tempWsdas;
        m_tempWsdas.clear();

        //tell the upnp service to start the search again
        m_upnpService->setSearchComplete();
    }

    void WsdaFinder::onDeviceAdded(const UpnpDevice& device)
    {
        static const std::string ACCEPTED_MODEL_NAME = "WSDA";

        int comp = device.modelName.compare(ACCEPTED_MODEL_NAME);
        if(comp == 0)
        {
            std::unique_lock<std::mutex> lock(m_wsdaMapMutex);

            //add/update the found wsda list, and the temp list
            m_tempWsdas[device.uniqueDeviceName] = WsdaInfo(device.presentationUrl, device.serialNumber);
            m_foundWsdas[device.uniqueDeviceName] = WsdaInfo(device.presentationUrl, device.serialNumber);
        }
    }

    WsdaFinder::WsdaMap WsdaFinder::found()
    {
        std::unique_lock<std::mutex> lock(m_wsdaMapMutex);

        //return a copy of the found wsdas
        return m_foundWsdas;
    }

    void WsdaFinder::restart()
    {
        std::unique_lock<std::mutex> lock(m_wsdaMapMutex);
        m_tempWsdas.clear();
        m_foundWsdas.clear();

        m_upnpService->restartSearch();
    }
}