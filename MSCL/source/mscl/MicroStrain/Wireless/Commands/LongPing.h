/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/

#pragma once

#include "mscl/MicroStrain/ByteStream.h"
#include "WirelessResponsePattern.h"
#include "mscl/MicroStrain/Wireless/Packets/WirelessPacket.h"
#include "PingResponse.h"

namespace mscl
{
    class WirelessPacket;

    //Class: LongPing
    //    Contains logic for the LongPing Node command
    class LongPing
    {
    public:
        LongPing() = delete;                            //default constructor disabled
        LongPing(const LongPing&) = delete;             //copy constructor disabled
        LongPing& operator=(const LongPing&) = delete;  //assignment operator disabled 

    public:
        //Function: buildCommand
        //    Builds the LongPing command packet
        //
        //Parameters:
        //    asppVer - The <WirelessPacket::AsppVersion> to use in parsing the response
        //    nodeAddress - the address of the Node to build the command for
        //
        //Returns:
        //    A <ByteStream> containing the LongPing command packet
        static ByteStream buildCommand(WirelessPacket::AsppVersion asppVer, NodeAddress nodeAddress);

        //Class: Response
        //    Handles the response to the LongPing Node command
        class Response : public WirelessResponsePattern
        {
        public:
            //Constructor: Response
            //    Creates a LongPing Response object
            //
            //Parameters:
            //    nodeAddress - the node address to check for
            //    collector - The <ResponseCollector> used to register and unregister the response
            Response(NodeAddress nodeAddress, std::weak_ptr<ResponseCollector> collector);

        private:
            //Variable: m_nodeAddress
            //    The node address to look for in the Long Ping response
            NodeAddress m_nodeAddress;

            //Variable: m_result
            //    The <PingResponse> that holds the result of the LongPing Node command
            PingResponse m_result;

        protected:
            //Function: match
            //    Checks if the <WirelessPacket> passed in matches the expected response pattern's bytes
            //
            //Parameters:
            //    packet - The <WirelessPacket> in which to try to find the pattern
            //
            //Returns:
            //    true if the packet matches a response pattern, false otherwise
            virtual bool matchSuccessResponse(const WirelessPacket& packet) override;

        public:
            //Function: result
            //    Gets the <PingResponse> that holds the result of the response
            //
            //Returns:
            //    A <PingResponse> that holds the result of the response
            PingResponse result();
        };
    };
}