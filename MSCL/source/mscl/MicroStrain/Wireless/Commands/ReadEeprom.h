/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "mscl/MicroStrain/ByteStream.h"
#include "WirelessResponsePattern.h"
#include "mscl/Types.h"

namespace mscl
{

#ifndef SWIG

    //Class: ReadEeprom
    //    Contains logic for the ReadEeprom Node command
    class ReadEeprom
    {
    private:
        ReadEeprom();                                //default constructor disabled
        ReadEeprom(const ReadEeprom&);                //copy constructor disabled
        ReadEeprom& operator=(const ReadEeprom&);    //assignment operator disabled

    public:
        //Function: buildCommand
        //    Builds the ReadEeprom command packet
        //
        //Parameters:
        //    nodeAddress - the address of the Node to build the command for
        //    eepromAddress - the Eeprom address to read from
        //
        //Returns:
        //    A <ByteStream> containing the command packet
        static ByteStream buildCommand(NodeAddress nodeAddress, uint16 eepromAddress);

        //Class: Response
        //    Handles the response to the ReadEeprom Node command
        class Response : public WirelessResponsePattern
        {
        public:
            //Constructor: Response
            //    Creates a EepromRead Response object
            //
            //Parameters:
            //    nodeAddress - the node address to check for
            //    collector - The <ResponseCollector> used to register and unregister the response
            Response(NodeAddress nodeAddress, std::weak_ptr<ResponseCollector> collector);

        private:
            //Variable: m_nodeAddress
            //    The node address to look for in the ReadEeprom response
            NodeAddress m_nodeAddress;

            //Variable: eepromValue
            //    The result eeprom value from the command.
            uint16 m_eepromValue;

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

        public:
            //Function: eepromValue
            //    Gets the result eeprom value that was read from the Node.
            //
            //Returns:
            //    The eeprom value read from the Node.
            uint16 eepromValue() const;
        };
    };

#endif
}