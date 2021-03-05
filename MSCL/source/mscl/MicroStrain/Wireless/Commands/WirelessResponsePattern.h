/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/

#pragma once

#include "mscl/Types.h"
#include "mscl/MicroStrain/ResponsePattern.h"
#include "WirelessProtocol.h"

namespace mscl
{
    //Class: WirelessResponsePattern
    //    A pattern matching the expected response from a wireless command.
    class WirelessResponsePattern : public ResponsePattern
    {
    public:
        //Default Constructor: WirelessResponsePattern
        //    Creates a default constructor WirelessResponsePattern.
        //    Note: You will need to use the <setResponseCollector> function before being used.
        WirelessResponsePattern(uint16 commandId, NodeAddress nodeAddress);

        //Constructor: WirelessResponsePattern
        //    Creates a WirelessResponsePattern attached to a collector.
        //
        //Parameters:
        //    collector - The <ResponseCollector> to register and unregister this response with.
        explicit WirelessResponsePattern(std::weak_ptr<ResponseCollector> collector, uint16 commandId, NodeAddress nodeAddress);

        //Destructor: ResponsePattern
        //    Destroys the ResponsePattern and unregisters this response from its <ResponseCollector>
        virtual ~WirelessResponsePattern();

        WirelessResponsePattern() = delete;                                             //default constructor disabled
        WirelessResponsePattern(const WirelessResponsePattern&) = delete;               //copy constructor disabled
        WirelessResponsePattern& operator=(const WirelessResponsePattern&) = delete;    //assignement operator disabled

    protected:
        //Variable: m_commandId
        //  The command ID to match in the response.
        uint16 m_commandId;

        //Variable: m_nodeAddress
        //  The NodeAddress to match in the response.
        NodeAddress m_nodeAddress;

        //Variable: m_baseReceived
        //  Whether the Base Station received response has been collected or not.
        bool m_baseReceived;

        //Variable: m_baseReceivedWaitTime
        //  The wait time (in milliseconds) that was sent in the Base Station received response.
        uint64 m_baseReceivedWaitTime;

    protected:
        virtual bool matchBaseReceivedResponse(const WirelessPacket& packet) override;

    public:
        //Function: baseReceived
        //  Gets whether the Base Station received response has been collected or not.
        bool baseReceived() const;

        //Function: baseReceivedWaitTime
        //  Gets the wait time (in milliseconds) that was sent in the Base Station received response.
        //  This is only valid if <baseReceived> returns true.
        uint64 baseReceivedWaitTime() const;
    };
}