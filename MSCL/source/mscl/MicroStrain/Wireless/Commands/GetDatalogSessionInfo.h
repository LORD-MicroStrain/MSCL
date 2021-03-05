/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "DatalogSessionInfoResult.h"
#include "mscl/MicroStrain/ByteStream.h"
#include "WirelessResponsePattern.h"
#include "mscl/MicroStrain/Wireless/Packets/WirelessPacket.h"

namespace mscl
{
    class WirelessPacket;

    //Class: GetDatalogSessionInfo
    //  Contains logic for the Get Datalog Session Info Node command.
    class GetDatalogSessionInfo
    {
    private:
        GetDatalogSessionInfo() = delete;                                          //default constructor disabled
        GetDatalogSessionInfo(const GetDatalogSessionInfo&) = delete;              //copy constructor disabled
        GetDatalogSessionInfo& operator=(const GetDatalogSessionInfo&) = delete;   //assignment operator disabled 

    public:
        //Function: buildCommand
        //    Builds the GetDatalogSessionInfo command packet.
        //
        //Parameters:
        //    nodeAddress - the address of the Node to build the command for.
        //
        //Returns:
        //    A <ByteStream> containing the GetDatalogSessionInfo command packet.
        static ByteStream buildCommand(WirelessPacket::AsppVersion asppVer, NodeAddress nodeAddress);

        //Class: Response
        //    Handles the response to the GetDatalogSessionInfo Node command.
        class Response : public WirelessResponsePattern
        {
        public:
            //Constructor: Response
            //    Creates a GetDatalogSessionInfo Response object.
            //
            //Parameters:
            //    nodeAddress - the node address to check for.
            //    collector - The <ResponseCollector> used to register and unregister the response.
            Response(NodeAddress nodeAddress, std::weak_ptr<ResponseCollector> collector);

        private:
            //Variable: m_nodeAddress
            //    The node address to look for in the response.
            NodeAddress m_nodeAddress;

            //Variable: m_result
            //  The <DatalogSessionInfoResult> to hold the result on success.
            DatalogSessionInfoResult m_result;

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
            //Function: result
            //  Gets the <DatalogSessionInfoResult> from a successful response.
            const DatalogSessionInfoResult& result() const;
        };
    };
}