/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#pragma once

#include "mscl/MicroStrain/Wireless/Commands/WirelessResponsePattern.h"
#include "mscl/MicroStrain/Wireless/Packets/WirelessPacket.h"

namespace mscl
{
#ifndef SWIG
    //Class: Sleep_v2
    //    Contains logic for the Sleep (v2) Node command
    class Sleep_v2
    {
    public:
        Sleep_v2() = delete;                            //default constructor disabled
        Sleep_v2(const Sleep_v2&) = delete;             //copy constructor disabled
        Sleep_v2& operator=(const Sleep_v2&) = delete;  //assignment operator disabled

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
            bool matchSuccessResponse(const WirelessPacket& packet) override;
        };
    };
#endif // !SWIG
} // namespace mscl
