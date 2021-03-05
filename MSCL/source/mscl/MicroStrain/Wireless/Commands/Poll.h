/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "mscl/Types.h"
#include "mscl/MicroStrain/ByteStream.h"
#include "WirelessResponsePattern.h"
#include "mscl/MicroStrain/Wireless/WirelessChannel.h"
#include "mscl/MicroStrain/Wireless/WirelessModels.h"
#include "mscl/MicroStrain/Wireless/WirelessTypes.h"
#include "mscl/MicroStrain/Wireless/Packets/WirelessPacket.h"

namespace mscl
{
    //Class: Poll
    //    Contains logic for the Poll Node command.
    class Poll
    {
    public:
        Poll() = delete;                        //default constructor disabled
        Poll(const Poll&) = delete;             //copy constructor disabled
        Poll& operator=(const Poll&) = delete;  //assignment operator disabled

    public:
        //Function: buildCommand
        //    Builds the Poll command packet.
        //
        //Parameters:
        //    asppVer - The <WirelessPacket::AsppVersion> to build the command for.
        //    nodeAddress - The address of the Node to build the command for.
        //    chMask - The <ChannelMask> representing the channels to poll.
        //
        //Returns:
        //    A <ByteStream> containing the command packet.
        static ByteStream buildCommand(WirelessPacket::AsppVersion asppVer, NodeAddress nodeAddress, const ChannelMask& chMask);

        //Class: Response
        //    Handles the response to the AutoBalance Node command
        class Response : public WirelessResponsePattern
        {
        public:
            //Constructor: Response
            //    Creates a Poll Response object
            //
            //Parameters:
            //    nodeAddress - The node address to check for.
            //    collector - The <ResponseCollector> used to register and unregister the response.
            Response(NodeAddress nodeAddress, std::weak_ptr<ResponseCollector> collector);

        protected:
            //Variable: m_nodeAddress
            //    The node address to look for in the response.
            NodeAddress m_nodeAddress;

            //Variable: m_started
            //    Whether the Poll has been successfully started or not (as reported by the Node).
            bool m_started;

            //Variable: m_timeUntilCompletion
            //    The amount of time (in seconds) that the Poll operation will take to complete.
            //    This value gets reported by the Node before starting the Poll.
            float m_timeUntilCompletion;

            //Variable: m_result
            //  The <WirelessPollData> response from a successful poll command.
            WirelessPollData m_result;

        public:
            //Function: started
            //    Gets whether the Poll operation has started or not.
            //
            //Returns:
            //    true if the Node indicated that the Poll operation has started, false otherwise.
            bool started() const;

            //Function: timeToComplete
            //    Gets the total time (in seconds) that the Node reported it will take to complete the Poll operation.
            //
            //Returns:
            //    The time (in seconds) that the Node reported it will take to complete Poll.
            float timeToComplete() const;

            //Function: result
            //  Gets the <WirelessPollData> from a successful poll command.
            //
            //Returns:
            //  A <WirelessPollData> map.
            const WirelessPollData& result() const;

            //Function: match
            //    Checks if the <WirelessPacket> passed in matches the expected response pattern's bytes.
            //
            //Parameters:
            //    packet - The <WirelessPacket> in which to try to find the pattern
            //
            //Returns:
            //    true if the packet matches a response pattern, false otherwise
            virtual bool match(const WirelessPacket& packet) override;

        protected:
            //Function: match_nodeReceived
            //    Checks if the <WirelessPacket> passed in matches the "Node Received" packet.
            //
            //Parmeters:
            //    packet - The <WirelessPacket> to try to match.
            //
            //Returns:
            //    true if the packet matches the Node Received packet, false otherwise.
            bool match_nodeReceived(const WirelessPacket& packet);

            bool matchSuccessResponse(const WirelessPacket& packet);
        };
    };
}