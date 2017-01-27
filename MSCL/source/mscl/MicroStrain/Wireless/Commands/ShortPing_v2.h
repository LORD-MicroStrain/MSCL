/*******************************************************************************
Copyright(c) 2015-2017 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "mscl/MicroStrain/ByteStream.h"
#include "mscl/MicroStrain/ResponsePattern.h"

namespace mscl
{
    class WirelessPacket;

    //Class: ShortPing_v2
    //    Contains logic for the ShortPing Node command (version 2).
    class ShortPing_v2
    {
    private:
        ShortPing_v2();                                    //default constructor disabled
        ShortPing_v2(const ShortPing_v2&);                //copy constructor disabled
        ShortPing_v2& operator=(const ShortPing_v2&);    //assignment operator disabled 

    public:
        //Function: buildCommand
        //    Builds the ShortPing_v2 command packet
        //
        //Parameters:
        //    nodeAddress - the address of the Node to build the command for.
        //
        //Returns:
        //    A <ByteStream> containing the ShortPing_v2 command packet.
        static ByteStream buildCommand(NodeAddress nodeAddress);

        //Class: Response
        //    Handles the response to the ShortPing_v2 Node command.
        class Response : public ResponsePattern
        {
        public:
            //Constructor: Response
            //    Creates a ShortPing_v2 Response object.
            //
            //Parameters:
            //    nodeAddress - the node address to check for.
            //    collector - The <ResponseCollector> used to register and unregister the response.
            Response(NodeAddress nodeAddress, std::weak_ptr<ResponseCollector> collector);

        private:
            //Variable: m_nodeAddress
            //    The node address to look for in the response
            NodeAddress m_nodeAddress;

        public:
            //Function: match
            //    Checks if the <WirelessPacket> passed in matches the expected response pattern's bytes
            //
            //Parameters:
            //    packet - The <WirelessPacket> in which to try to find the pattern
            //
            //Returns:
            //    true if the packet matches a response pattern, false otherwise
            virtual bool match(const WirelessPacket& packet) override;

        private:
            //Function: matchReceivedResponse
            //    Checks if the packet passed in matches the Base Station received response.
            //
            //Parameters:
            //    packet - The <WirelessPacket> to try to match.
            //
            //Returns:
            //    true if the success response pattern was found, false otherwise
            bool matchReceivedResponse(const WirelessPacket& packet);

            //Function: matchSuccessResponse
            //    Checks if the packet passed in matches the success response.
            //
            //Parameters:
            //    packet - The <WirelessPacket> to try to match.
            //
            //Returns:
            //    true if the success response pattern was found, false otherwise
            bool matchSuccessResponse(const WirelessPacket& packet);

            //Function: matchFailResponse
            //    Checks if the packet passed in matches the failure response.
            //
            //Parameters:
            //    packet - The <WirelessPacket> to try to match.
            //
            //Returns:
            //    true if the failure response pattern was found, false otherwise
            bool matchFailResponse(const WirelessPacket& packet);
        };
    };
}