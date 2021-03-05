/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "WirelessResponsePattern.h"
#include "mscl/MicroStrain/ByteStream.h"

namespace mscl
{

#ifndef SWIG

    //Class: ArmForDatalogging
    //    Contains logic for the Arm For Datalogging Node command.
    class ArmForDatalogging
    {
    private:
        ArmForDatalogging();                                    //disabled default constructor
        ArmForDatalogging(const ArmForDatalogging&);            //disabled copy constructor
        ArmForDatalogging& operator=(const ArmForDatalogging&);    //disabled assignment operator

    public:
        //Function: buildCommand
        //    Builds the ArmForDatalogging command packet.
        //
        //Parameters:
        //    nodeAddress - The address of the Node to build the command for.
        //    message - A message, up to 50 characters, to send with the arm command. This message can be downloaded with the data. Will be trimmed to 50 chars if longer. (Default of "")
        //
        //Returns:
        //    A <ByteStream> containing the command packet.
        static ByteStream buildCommand(NodeAddress nodeAddress, const std::string& message = "");

        //Class: Response
        //    Handles the response to the ArmForDatalogging Node command
        class Response : public WirelessResponsePattern
        {
        public:
            //Constructor: Response
            //    Creates an ArmForDatalogging Response object
            //
            //Parameters:
            //    nodeAddress - the node address to check for
            //    collector - The <ResponseCollector> used to register and unregister the response
            Response(NodeAddress nodeAddress, std::weak_ptr<ResponseCollector> collector);

        private:
            //Variable: m_nodeAddress
            //    The node address to look for in the response
            NodeAddress m_nodeAddress;

        protected:
            //Function: match
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