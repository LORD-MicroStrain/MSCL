/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "mscl/MicroStrain/Wireless/Packets/WirelessPacket.h"
#include "WirelessResponsePattern.h"

namespace mscl
{
#ifndef SWIG

    //Class: BaseStation_WriteEeprom_v2
    //    Contains logic for the base station write eeprom command (v2)
    class BaseStation_WriteEeprom_v2
    {
    public:
        BaseStation_WriteEeprom_v2() = delete;                                                //default constructor disabled
        BaseStation_WriteEeprom_v2(const BaseStation_WriteEeprom_v2&) = delete;                //copy constructor disabled
        BaseStation_WriteEeprom_v2& operator=(const BaseStation_WriteEeprom_v2&) = delete;    //assignement operator disabled

    public:
        //Function: buildCommand
        //    Builds the eeprom write command packet
        //
        //Parameters:
        //    eepromAddress - The eeprom address to write to on the base station
        //    valueToWrite - The value to write to the specified eeprom address
        //
        //Returns:
        //    A <ByteStream> containing the base station write eeprom command
        static ByteStream buildCommand(WirelessPacket::AsppVersion asppVer, uint16 eepromAddress, uint16 valueToWrite);

        //Class: Response
        //    Handles the response to the base station write eeprom command
        class Response : public WirelessResponsePattern
        {
        public:
            //Constructor: Response
            //    Creates a write eeprom Response object
            //
            //Parameters:
            //    valueToWrite - The value that is expected to be written to eeprom from the associated command
            //    eepromAddress - The eeprom address being written to.
            //    collector - The <ResponseCollector> used to register and unregister the response
            Response(uint16 valueToWrite, uint16 eepromAddress, std::weak_ptr<ResponseCollector> collector);

        private:
            //Variable: m_valueWritten
            //    The value that is expected to be written to eeprom from the associated command.
            uint16 m_valueWritten;

            //Variable: m_eepromAddress
            //    The eeprom address to match in the response.
            uint16 m_eepromAddress;

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
            //    Checks if the packet passed in matches the success response.
            //
            //Parameters:
            //    packet - The <WirelessPacket> to try to match.
            //
            //Returns:
            //    true if the success response pattern was found, false otherwise
            bool matchSuccessResponse(const WirelessPacket& packet) override;

            //Function: matchFailResponse
            //    Checks if the packet passed in matches the failure response.
            //
            //Parameters:
            //    packet - The <WirelessPacket> to try to match.
            //
            //Returns:
            //    true if the failure response pattern was found, false otherwise
            bool matchFailResponse(const WirelessPacket& packet) override;
        };
    };

#endif

}