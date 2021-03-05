/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "WirelessResponsePattern.h"
#include "mscl/MicroStrain/Wireless/BaseStation.h"

namespace mscl
{
    //Title: SetToIdle

#ifndef SWIG
    //Class: SetToIdle
    //    Contains logic for the Set to Idle command.
    namespace SetToIdle
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


    //public:
        //Class: Response
        //    Handles the response to the SetToIdle command
        class Response : public WirelessResponsePattern
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
            virtual ~Response();

        protected:
            //Variable: m_nodeAddress
            //    The node address to look for in the response.
            NodeAddress m_nodeAddress;

            //Variable: m_result
            //    The <SetToIdleResult> detailing the result of the Set to Idle command.
            SetToIdleStatus::SetToIdleResult m_result;

            //Variable: m_baseStation
            //    The <BaseStation> that will send the command (used for canceling this command).
            BaseStation m_baseStation;

            //Variable: m_setToIdleMutex
            //    The mutex used for thread safety.
            std::mutex m_setToIdleMutex;

        public:
            //Function: match
            //    Checks if the bytes passed in match the response pattern from their current read position.
            //
            //Parameters:
            //    data - The <DataBuffer> containing the bytes in which to try to find the pattern.
            //
            //Returns:
            //    true if the response pattern was found, false otherwise.
            virtual bool match(DataBuffer& data) override;

            //Function: cancel
            //    Attempts to cancel the Stop Node operation.
            //
            //Exceptions:
            //    - <Error_Connection>: A connection error has occurred when trying to cancel.
            virtual void cancel();

            //Function: result
            //    Gets the <SetToIdleResult> of the Stop Node command.
            //
            //Returns:
            //    The <SetToIdleResult> containing the result of the Stop Node command.
            SetToIdleStatus::SetToIdleResult result();
        };
    };
#endif
}