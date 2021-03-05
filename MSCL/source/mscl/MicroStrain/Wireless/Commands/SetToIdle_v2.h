/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "mscl/MicroStrain/ResponsePattern.h"
#include "mscl/MicroStrain/Wireless/BaseStation.h"
#include "SetToIdleStatus.h"
#include "SetToIdle.h"

namespace mscl
{
    //Title: SetToIdle_v2

#ifndef SWIG
    //Class: SetToIdle_v2
    //    Contains logic for the Set to Idle (v2) command.
    namespace SetToIdle_v2
    {
        //Function: buildCommand
        //    Builds the SetToIdle command packet.
        //
        //Parameters:
        //    nodeAddress - the address of the Node to build the command for.
        //
        //Returns:
        //    A <ByteStream> containing the SetToIdle command packet
        ByteStream buildCommand(NodeAddress nodeAddress);
        ByteStream buildCommand_aspp3(NodeAddress nodeAddress);


        //Class: Response
        //    Handles the response to the SetToIdle command
        class Response : public SetToIdle::Response
        {
        public:
            //Constructor: Response
            //    Creates a SetToIdle Response object
            //
            //Parameters:
            //    nodeAddress - the node address to check for.
            //    collector - The <ResponseCollector> used to register and unregister the response.
            //    baseStation - The <BaseStation> that will send the command (used for canceling this command).
            Response(NodeAddress nodeAddress, std::weak_ptr<ResponseCollector> collector, const BaseStation& baseStation);

            //Destructor: Response
            //    Destroys the SetToIdle Response object. This also cancels the SetToIdle operation on the BaseStation, if not already complete or canceled.
            ~Response();

        private:
            //Variable: m_started
            //    Whether the set to idle process has been started or not.
            bool m_started;

        protected:
            //Function: match_baseReceived
            //    Checks if the packet passed in matches the base station received packet.
            //
            //Parameters:
            //    packet - The <WirelessPacket> to try to match.
            //
            //Returns:
            //    true if the base station received packet was found, false otherwise.
            bool match_baseReceived(const WirelessPacket& packet);

            //Function: match_completion
            //    Checks if the packet passed in matches the completion packet.
            //
            //Parameters:
            //    packet - The <WirelessPacket> to try to match.
            //
            //Returns:
            //    true if the match_completion packet was found, false otherwise.
            bool match_completion(const WirelessPacket& packet);

        public:
            //Function: match
            //    Checks if the packet passed in matches a response packet.
            //
            //Parameters:
            //    packet - The <WirelessPacket> to try to match.
            //
            //Returns:
            //    true if the packet matches a response pattern, false otherwise.
            virtual bool match(const WirelessPacket& packet) override;

            //Function: started
            //  Checks if the set to idle operation has started or not.
            //
            //Returns:
            //  true if the operation has started, false otherwise.
            bool started();
        };
    };
#endif
}