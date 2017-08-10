/*******************************************************************************
Copyright(c) 2015-2017 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "mscl/MicroStrain/ByteStream.h"
#include "WirelessResponsePattern.h"
#include "mscl/MicroStrain/Wireless/Packets/WirelessPacket.h"
#include "mscl/Types.h"

namespace mscl
{

#ifndef SWIG

    //Class: Sleep
    //    Contains logic for the Sleep Node command
    class Sleep
    {
    public:
        Sleep() = delete;                           //default constructor disabled
        Sleep(const Sleep&) = delete;               //copy constructor disabled
        Sleep& operator=(const Sleep&) = delete;    //assignment operator disabled

    public:
        //Function: buildCommand
        //    Builds the Sleep command packet.
        //
        //Parameters:
        //    nodeAddress - The address of the Node to build the command for.
        //
        //Returns:
        //    A <ByteStream> containing the command packet.
        static ByteStream buildCommand(WirelessPacket::AsppVersion asppVer, NodeAddress nodeAddress);

        //Class: Response
        //    Handles the response to the Sleep_v2 Node command
        class Response: public WirelessResponsePattern
        {
        public:
            //Constructor: Response
            //    Creates a Sleep_v2 Response object
            //
            //Parameters:
            //    nodeAddress - the node address to check for
            //    collector - The <ResponseCollector> used to register and unregister the response
            Response(NodeAddress nodeAddress, std::weak_ptr<ResponseCollector> collector);

        private:
            //Variable: m_nodeAddress
            //    The node address to look for in the response
            NodeAddress m_nodeAddress;

        public:
            //Function: matchSuccessResponse
            //    Checks if the <WirelessPacket> passed in matches the expected response pattern's bytes
            //
            //Parameters:
            //    packet - The <WirelessPacket> in which to try to find the pattern
            //
            //Returns:
            //    true if the packet matches a response pattern, false otherwise
            virtual bool matchSuccessResponse(const WirelessPacket& packet) override;
        };
    };

#endif
}