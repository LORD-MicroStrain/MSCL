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

    //Class: WriteEeprom_v2
    //    Contains logic for the WriteEeprom (version 2) Node command
    class WriteEeprom_v2
    {
    public:
        WriteEeprom_v2() = delete;                                  //default constructor disabled
        WriteEeprom_v2(const WriteEeprom_v2&) = delete;             //copy constructor disabled
        WriteEeprom_v2& operator=(const WriteEeprom_v2&) = delete;  //assignment operator disabled

    public:
        //Function: buildCommand
        //    Builds the WriteEeprom_v2 command packet
        //
        //Parameters:
        //    nodeAddress - the address of the Node to build the command for
        //    eepromAddress - the Eeprom address to write to
        //    valueToWrite - the value to write to the Eeprom
        //
        //Returns:
        //    A <ByteStream> containing the command packet
        static ByteStream buildCommand(WirelessPacket::AsppVersion asppVer, NodeAddress nodeAddress, uint16 eepromAddress, uint16 valueToWrite);

        //Class: Response
        //    Handles the response to the WriteEeprom_v2 Node command
        class Response : public WirelessResponsePattern
        {
        public:
            //Constructor: Response
            //    Creates a WriteEeprom_v2 Response object
            //
            //Parameters:
            //    nodeAddress - the node address to check for.
            //    eepromAddress - the eeprom address that was written to.
            //    valueWritten - the value that was written to eeprom.
            //    collector - The <ResponseCollector> used to register and unregister the response.
            Response(NodeAddress nodeAddress, uint16 eepromAddress, uint16 valueWritten, std::weak_ptr<ResponseCollector> collector);

        private:
            //Variable: m_nodeAddress
            //    The node address to look for in the WriteEeprom_v2 response
            NodeAddress m_nodeAddress;

            //Variable: m_eepromAddress
            //    The eeprom address to look for in the WriteEeprom_v2 response.
            uint16 m_eepromAddress;

            //Variable: eepromValue
            //    The eeprom value to look for in the WriteEeprom_v2 response.
            uint16 m_eepromValue;

            //Variable: m_errorCode
            //    The <WirelessPacket::ResponseErrorCode> from the response.
            WirelessPacket::ResponseErrorCode m_errorCode;

        public:
            //Function: errorCode
            //    Gets the <WirelessPacket::ResponseErrorCode> from the response packet.
            //
            //Returns:
            //    The error code from the response.
            WirelessPacket::ResponseErrorCode errorCode() const;

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

            //Function: matchFailResponse
            //    Checks if the <WirelessPacket> passed in matches the failure response.
            //
            //Parameters:
            //    packet - The <WirelessPacket> to match.
            //
            //Returns:
            //    true if the packet matches the fail response, false otherwise.
            bool matchFailResponse(const WirelessPacket& packet) override;
        };
    };

#endif
}