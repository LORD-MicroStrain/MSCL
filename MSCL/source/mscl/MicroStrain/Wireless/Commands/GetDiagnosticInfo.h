/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/

#pragma once

#include "mscl/MicroStrain/ByteStream.h"
#include "WirelessResponsePattern.h"
#include "mscl/MicroStrain/Wireless/WirelessDataPoint.h"
#include "mscl/MicroStrain/Wireless/Packets/WirelessPacket.h"

namespace mscl
{
    class WirelessPacket;

    //Class: GetDiagnosticInfo
    //  Contains logic for the Get Diagnostic Info Node command.
    class GetDiagnosticInfo
    {
    public:
        GetDiagnosticInfo() = delete;                                        //default constructor disabled
        GetDiagnosticInfo(const GetDiagnosticInfo&) = delete;                //copy constructor disabled
        GetDiagnosticInfo& operator=(const GetDiagnosticInfo&) = delete;     //assignment operator disabled 

    public:
        //Function: buildCommand
        //  Builds the command packet.
        //
        //Parameters:
        //  nodeAddress - the address of the Node to build the command for.
        //
        //Returns:
        //  A <ByteStream> containing the command packet
        static ByteStream buildCommand(WirelessPacket::AsppVersion asppVer, NodeAddress nodeAddress);

        //Class: Response
        //  Handles the response to the GetDiagnosticInfo Node command.
        class Response : public WirelessResponsePattern
        {
        public:
            //Constructor: Response
            //  Creates a GetDiagnosticInfo Response object
            //
            //Parameters:
            //  nodeAddress - the node address to check for.
            //  collector - The <ResponseCollector> used to register and unregister the response.
            Response(NodeAddress nodeAddress, std::weak_ptr<ResponseCollector> collector);

        private:
            //Variable: m_nodeAddress
            //    The node address to look for in the Long Ping response.
            NodeAddress m_nodeAddress;

            //Variable: m_result
            //  The <ChannelData> that holds the result data of the GetDiagnosticInfo Node command.
            ChannelData m_result;

        protected:
            //Function: match
            //  Checks if the <WirelessPacket> passed in matches the expected response pattern's bytes
            //
            //Parameters:
            //  packet - The <WirelessPacket> in which to try to find the pattern
            //
            //Returns:
            //  true if the packet matches a response pattern, false otherwise
            virtual bool matchSuccessResponse(const WirelessPacket& packet) override;

        public:
            //Function: result
            //  Gets the <ChannelData> that holds the result info from the response
            //
            //Returns:
            //  A <ChannelData> that holds the result info from the response
            const ChannelData& result() const;
        };
    };
}