/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "mscl/MicroStrain/Wireless/Packets/WirelessPacket.h"
#include "mscl/MicroStrain/ByteStream.h"
#include "WirelessResponsePattern.h"
#include "mscl/Types.h"

namespace mscl
{

#ifndef SWIG

    //Class: BatchEepromRead
    //    Contains logic for the Batch Eeprom Read Node command
    class BatchEepromRead
    {
    public:
        BatchEepromRead() = delete;                                   //default constructor disabled
        BatchEepromRead(const BatchEepromRead&) = delete;               //copy constructor disabled
        BatchEepromRead& operator=(const BatchEepromRead&) = delete;    //assignment operator disabled

    public:
        //Function: buildCommand
        //    Builds the ReadEeprom command packet
        //
        //Parameters:
        //    nodeAddress - the address of the Node to build the command for.
        //    startAddress - the Eeprom address to start reading from.
        //
        //Returns:
        //    A <ByteStream> containing the command packet
        static ByteStream buildCommand(NodeAddress nodeAddress, uint16 startAddress);

        //Class: Response
        //    Handles the response to the ReadEeprom Node command
        class Response : public WirelessResponsePattern
        {
        public:
            //Constructor: Response
            //    Creates a EepromRead Response object
            //
            //Parameters:
            //    nodeAddress - The node address to check for.
            //    collector - The <ResponseCollector> used to register and unregister the response.
            Response(NodeAddress nodeAddress, std::weak_ptr<ResponseCollector> collector);

        private:
            //Variable: m_nodeAddress
            //    The node address to look for in the ReadEeprom response.
            NodeAddress m_nodeAddress;

            //Variable: m_eepromMap
            //  A map of eeprom location to eeprom value pairs.
            std::map<uint16, uint16> m_eepromMap;

        public:
            const std::map<uint16, uint16>& eepromMap() const;

        protected:
            //Function: matchSuccessResponse
            //    Checks if the <WirelessPacket> passed in matches the success response.
            //
            //Parameters:
            //    packet - The <WirelessPacket> to match.
            //
            //Returns:
            //    true if the packet matches the success response, false otherwise.
            bool matchSuccessResponse(const WirelessPacket& packet) override;
        };
    };

#endif
}