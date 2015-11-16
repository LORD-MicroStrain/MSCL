/*******************************************************************************
Copyright(c) 2015 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "mscl/MicroStrain/Wireless/Packets/WirelessPacket.h"
#include "mscl/MicroStrain/ByteStream.h"
#include "mscl/MicroStrain/ResponsePattern.h"
#include "mscl/Types.h"

namespace mscl
{

#ifndef SWIG

    //Class: ReadEeprom_v2
    //    Contains logic for the ReadEeprom (version 2) Node command
    class ReadEeprom_v2
    {
    private:
        ReadEeprom_v2();                                //default constructor disabled
        ReadEeprom_v2(const ReadEeprom_v2&);            //copy constructor disabled
        ReadEeprom_v2& operator=(const ReadEeprom_v2&);    //assignment operator disabled

    public:
        //Function: buildCommand
        //    Builds the ReadEeprom command packet
        //
        //Parameters:
        //    nodeAddress - the address of the Node to build the command for.
        //    eepromAddress - the Eeprom address to read from.
        //
        //Returns:
        //    A <ByteStream> containing the command packet
        static ByteStream buildCommand(NodeAddress nodeAddress, uint16 eepromAddress);

        //Class: Response
        //    Handles the response to the ReadEeprom Node command
        class Response : public ResponsePattern
        {
        public:
            //Constructor: Response
            //    Creates a EepromRead Response object
            //
            //Parameters:
            //    nodeAddress - The node address to check for.
            //    eepromAddress - The eeprom address we read from.
            //    collector - The <ResponseCollector> used to register and unregister the response.
            Response(NodeAddress nodeAddress, uint16 eepromAddress, std::weak_ptr<ResponseCollector> collector);

        private:
            //Variable: m_nodeAddress
            //    The node address to look for in the ReadEeprom response.
            NodeAddress m_nodeAddress;

            //Variable: m_eepromAddress
            //    The eeprom address to look for in the ReadEeprom response.
            uint16 m_eepromAddress;

            //Variable: eepromValue
            //    The result eeprom value from the command.
            uint16 m_eepromValue;

            //Variable: m_errorCode
            //    The <WirelessPacket::ResponseErrorCode> from the response.
            WirelessPacket::ResponseErrorCode m_errorCode;

        public:
            //Function: match
            //    Checks if the <WirelessPacket> passed in matches the expected response pattern's bytes.
            //
            //Parameters:
            //    packet - The <WirelessPacket> in which to try to find the pattern.
            //
            //Returns:
            //    true if the packet matches a response pattern, false otherwise.
            virtual bool match(const WirelessPacket& packet) override;

            //Function: eepromValue
            //    Gets the result eeprom value that was read from the Node.
            //
            //Returns:
            //    The eeprom value read from the Node.
            uint16 eepromValue() const;

            //Function: errorCode
            //    Gets the <WirelessPacket::ResponseErrorCode> from the response packet.
            //
            //Returns:
            //    The error code from the response.
            WirelessPacket::ResponseErrorCode errorCode() const;

        private:
            //Function: matchSuccessResponse
            //    Checks if the <WirelessPacket> passed in matches the success response.
            //
            //Parameters:
            //    packet - The <WirelessPacket> to match.
            //
            //Returns:
            //    true if the packet matches the success response, false otherwise.
            bool matchSuccessResponse(const WirelessPacket& packet);

            //Function: matchFailResponse
            //    Checks if the <WirelessPacket> passed in matches the failure response.
            //
            //Parameters:
            //    packet - The <WirelessPacket> to match.
            //
            //Returns:
            //    true if the packet matches the fail response, false otherwise.
            bool matchFailResponse(const WirelessPacket& packet);
        };
    };

#endif
}