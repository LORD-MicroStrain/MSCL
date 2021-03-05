/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/

#pragma once

#include "UpnpService.h"
#include "UpnpDeviceFinderCallback.h"

#include <string>
#include <map>

namespace mscl
{
    //API Title: WsdaFinder

    //API Class: WsdaInfo
    //  Holds info on a discovered WSDA.
    class WsdaInfo
    {
    public:
        //API Default Constructor: WsdaInfo
        //  Creates a default, empty WsdaInfo object.
        WsdaInfo();

        //Constructor: WsdaInfo
        //  Creates a WsdaInfo object.
        //
        //Parameters:
        //  url - The 'presentationUrl' from the upnp discovery.
        //  serial - The 'serial' from the upnp discovery.
        WsdaInfo(std::string url, std::string serial);

    private:
        //Variable: m_url
        //  The url of the upnp discovery.
        std::string m_url;

        //Variable: m_serial
        //  The serial of the upnp discovery.
        std::string m_serial;

    public:
        //API Function: ipAddress
        //  Gets the IP Address of the WSDA.
        std::string ipAddress() const;

        //API Function: port
        //  Gets the port number of the WSDA.
        uint16 port() const;

        //API Function: name
        //  Gets the name of the WSDA.
        std::string name() const;
    };

    //API Class: WsdaFinder
    //  Discovers upnp WSDA devices. (WINDOWS ONLY)
    class WsdaFinder
    {
    public:
        //API Typedef: WsdaMap
        //  Typedef for a uuid to <WsdaInfo> map.
        typedef std::map<std::string, WsdaInfo> WsdaMap;

    public:
        //API Default Constructor: WsdaFinder
        //  Creates a WsdaFinder object, starting the thread to search for WSDAs.
        //
        //Exceptions:
        //  - <Error>: The Wsda Finder upnp service could not be started.
        WsdaFinder();

        //API Destructor: ~WsdaFinder
        //  Destroys the WsdaFinder object, stopping the search.
        ~WsdaFinder();

    private:
        WsdaFinder(const WsdaFinder&);              //copy constructor disabled
        WsdaFinder& operator=(const WsdaFinder&);   //assignment operator disabled

    private:
        //Function: start
        //  Starts the search thread looking for upnp WSDAs.
        void start();

        //Function: onSearchComplete
        //  Callback function for when the initial search has completed.
        void onSearchComplete();

        //Function: onDeviceAdded
        //  Callback function for when any upnp device was added/found.
        //
        //Parameters:
        //  device - The <UpnpDevice> that was found.
        void onDeviceAdded(const UpnpDevice& device);

    private:
        //Variable: m_upnpService
        //  The <UpnpService> that asynchronously searches for upnp devices.
        std::unique_ptr<UpnpService> m_upnpService;

        //Variable: m_upnpSearchCallback
        //  The <UpnpDeviceFinderCallback> that handles all the upnp callbacks.
        std::unique_ptr<UpnpDeviceFinderCallback> m_upnpSearchCallback;

        //Variable: m_foundWsdas
        //  The <WsdaMap> containing the list of WSDAs that were found.
        WsdaMap m_foundWsdas;

        //Variable: m_tempWsdas
        //  A temporary map that gets cleared on every new search to aid in finding
        //  which WSDAs have been removed after already been found.
        WsdaMap m_tempWsdas;

        //Variable: m_wsdaMapMutex
        //  A mutex for accessing the found wsda maps.
        std::mutex m_wsdaMapMutex;

    public:
        //API Function: found
        //  Gets a copy of the <WsdaMap> that contains the WSDAs as they are known
        //  on the local network. If a WSDA is removed from the network, it will
        //  also be removed from this map if it was previously found.
        //
        //Returns:
        //  A <WsdaMap> of the WSDAs that were found on the network.
        WsdaFinder::WsdaMap found();

        //API Function: restart
        //  Clears out the list of found WSDAs and forces a restart of the upnp search.
        void restart();
    };
}