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

    //Class: BaseStation_ReadEeprom_v2
    //    Contains logic for the base station read eeprom command (v2).
    class BaseStation_ReadEeprom_v2
    {
    public:
        BaseStation_ReadEeprom_v2() = delete;                                               //default constructor disabled
        BaseStation_ReadEeprom_v2(const BaseStation_ReadEeprom_v2&) = delete;               //copy constructor disabled
        BaseStation_ReadEeprom_v2& operator=(const BaseStation_ReadEeprom_v2&) = delete;    //assignement operator disabled

    public:
        //Function: buildCommand
        //    Builds the eeprom read command packet.
        //
        //Parameters:
        //    eepromAddress - The eeprom address to read from the base station.
        //
        //Returns:
        //    A <ByteStream> containing the base station read eeprom command
        static ByteStream buildCommand(WirelessPacket::AsppVersion asppVer, uint16 eepromAddress);

        //Class: Response
        //    Handles the response to the base station read eeprom command.
        class Response : public WirelessResponsePattern
        {
        public:
            //Constructor: Response
            //    Creates a read eeprom Response object.
            //
            //Parameters:
            //    eepromAddress - The eeprom address being read from.
            //    collector - The <ResponseCollector> used to register and unregister the response.
            Response(uint16 eepromAddress, std::weak_ptr<ResponseCollector> collector);

        private:
            //Variable: m_eepromAddress
            //    The eeprom address to match in the response.
            uint16 m_eepromAddress;

            //Variable: m_result
            //    The result value of the read eeprom command.
            uint16 m_result;

            //Variable: m_errorCode
            //    The <WirelessPacket::ResponseErrorCode> from the response.
            WirelessPacket::ResponseErrorCode m_errorCode;

        public:
            //Function: result
            //    Gets the result value of the response.
            //
            //Returns:
            //    The result value of the response.
            //
            //Exceptions:
            //    - <Error>: failed to read the base station's eeprom.
            uint16 result() const;

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