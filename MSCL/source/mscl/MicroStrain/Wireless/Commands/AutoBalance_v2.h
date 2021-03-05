/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "mscl/MicroStrain/ByteStream.h"
#include "WirelessResponsePattern.h"
#include "mscl/MicroStrain/Wireless/WirelessTypes.h"
#include "mscl/MicroStrain/Wireless/Packets/WirelessPacket.h"
#include "mscl/Types.h"
#include "AutoBalanceResult.h"

namespace mscl
{
    //Class: AutoBalance_v2
    //    Contains logic for the Auto Balance Node command (Version 2).
    class AutoBalance_v2
    {
    public:
        AutoBalance_v2() = delete;                                  //default constructor disabled
        AutoBalance_v2(const AutoBalance_v2&) = delete;             //copy constructor disabled
        AutoBalance_v2& operator=(const AutoBalance_v2&) = delete;  //assignment operator disabled

    public:
        //Function: buildCommand
        //    Builds the AutoBalance_v2 command packet.
        //
        //Parameters:
        //    nodeAddress - The address of the Node to build the command for.
        //    channelNumber - The channel number to balance (ch1 = 1, ch8 = 8).
        //    targetPercent - The target percentage to balance to (0 - 100).
        //
        //Returns:
        //    A <ByteStream> containing the command packet.
        static ByteStream buildCommand(WirelessPacket::AsppVersion asppVer, NodeAddress nodeAddress, uint8 channelNumber, float targetPercent);

        //Class: Response
        //    Handles the response to the AutoBalance Node command
        class Response: public WirelessResponsePattern
        {
        public:
            //Constructor: Response
            //    Creates an AutoBalance Response object
            //
            //Parameters:
            //    nodeAddress - the node address to check for in the response.
            //    channelNumber - The channel number to check for in the response.
            //    targetPercent - The target percentage (0-100) to check for in the response.
            //    collector - The <ResponseCollector> used to register and unregister the response.
            Response(NodeAddress nodeAddress, uint8 channelNumber, float targetPercent, std::weak_ptr<ResponseCollector> collector);

        private:
            //Variable: m_nodeAddress
            //    The node address to look for in the response.
            NodeAddress m_nodeAddress;

            //Variable: m_channelNumber
            //    The channel number to look for in the response.
            uint8 m_channelNumber;

            //Variable: m_targetPercent
            //    The target percentage to look for in the response.
            float m_targetPercent;

            //Variable: m_result
            //    The <AutoBalanceResult> containing info about the autobalance response.
            AutoBalanceResult m_result;

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

            //Function: result
            //    Gets the <AutoBalanceResult> of the command.
            const AutoBalanceResult& result() const;
        };
    };
}