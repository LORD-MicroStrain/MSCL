/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "mscl/MicroStrain/ByteStream.h"
#include "WirelessResponsePattern.h"
#include "mscl/MicroStrain/Wireless/Packets/WirelessPacket.h"

namespace mscl
{
    class WirelessPacket;

    //Class: TestNodeCommProtocol
    //  Contains logic for the TestNodeCommProtocol command.
    class TestNodeCommProtocol
    {
    public:
        TestNodeCommProtocol() = delete;                                        //default constructor disabled
        TestNodeCommProtocol(const TestNodeCommProtocol&) = delete;             //copy constructor disabled
        TestNodeCommProtocol& operator=(const TestNodeCommProtocol&) = delete;  //assignment operator disabled 

    public:
        //Function: buildCommand
        //    Builds the TestNodeCommProtocol command packet
        //
        //Parameters:
        //    nodeAddress - the address of the Node to build the command for.
        //    protocol - The <WirelessTypes::CommProtocol> to use in the command.
        //
        //Returns:
        //    A <ByteStream> containing the TestNodeCommProtocol command packet.
        static ByteStream buildCommand(WirelessPacket::AsppVersion asppVer, NodeAddress nodeAddress, WirelessTypes::CommProtocol protocol);

        //Class: Response
        //    Handles the response to the TestNodeCommProtocol Node command.
        class Response : public WirelessResponsePattern
        {
        public:
            //Constructor: Response
            //    Creates a TestNodeCommProtocol Response object.
            //
            //Parameters:
            //    nodeAddress - the node address to check for.
            //    protocol - The <WirelessTypes::CommProtocol> to check for.
            //    collector - The <ResponseCollector> used to register and unregister the response.
            Response(NodeAddress nodeAddress, WirelessTypes::CommProtocol protocol, std::weak_ptr<ResponseCollector> collector);

        private:
            //Variable: m_nodeAddress
            //    The node address to look for in the response.
            NodeAddress m_nodeAddress;

            //Variable: m_protocol
            //  The <WirelessTypes::CommProtocol> to match in the response.
            WirelessTypes::CommProtocol m_protocol;

        protected:
            //Function: matchSuccessResponse
            //    Checks if the <WirelessPacket> passed in matches the success response pattern's bytes
            //
            //Parameters:
            //    packet - The <WirelessPacket> in which to try to find the pattern
            //
            //Returns:
            //    true if the packet matches the success response pattern, false otherwise
            bool matchSuccessResponse(const WirelessPacket& packet) override;

            //Function: matchFailResponse
            //    Checks if the <WirelessPacket> passed in matches the failure response pattern's bytes
            //
            //Parameters:
            //    packet - The <WirelessPacket> in which to try to find the pattern
            //
            //Returns:
            //    true if the packet matches the success response pattern, false otherwise
            bool matchFailResponse(const WirelessPacket& packet) override;
        };
    };
}