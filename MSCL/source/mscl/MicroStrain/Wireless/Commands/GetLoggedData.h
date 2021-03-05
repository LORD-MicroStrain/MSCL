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

    //Class: GetLoggedData
    //  Contains logic for the Get Logged Data Node command.
    class GetLoggedData
    {
    private:
        GetLoggedData() = delete;                                   //default constructor disabled
        GetLoggedData(const GetLoggedData&) = delete;               //copy constructor disabled
        GetLoggedData& operator=(const GetLoggedData&) = delete;    //assignment operator disabled 

    public:
        //Function: buildCommand
        //    Builds the GetLoggedData command packet.
        //
        //Parameters:
        //    nodeAddress - the address of the Node to build the command for.
        //    flashAddress - The flash address to read.
        //
        //Returns:
        //    A <ByteStream> containing the GetLoggedData command packet.
        static ByteStream buildCommand(WirelessPacket::AsppVersion asppVer, NodeAddress nodeAddress, uint32 flashAddress);

        //Class: Response
        //    Handles the response to the GetLoggedData Node command.
        class Response : public WirelessResponsePattern
        {
        public:
            //Constructor: Response
            //    Creates a GetLoggedData Response object.
            //
            //Parameters:
            //    nodeAddress - the node address to check for.
            //    flashAddress - The flash address to match in the response.
            //    collector - The <ResponseCollector> used to register and unregister the response.
            Response(NodeAddress nodeAddress, uint32 flashAddress, std::weak_ptr<ResponseCollector> collector);

        private:
            //Variable: m_nodeAddress
            //    The node address to look for in the response.
            NodeAddress m_nodeAddress;

            //Variable: m_flashAddress
            //  The flash address to match in the response.
            uint32 m_flashAddress;

            //Variable: m_data
            //  The <ByteStream> containing the resulting data on success.
            ByteStream m_data;

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

        public:
            //Function: data
            //  Gets the <ByteStream> containing the data from a successful response.
            const ByteStream& data() const;
        };
    };
}