/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "WirelessResponsePattern.h"

namespace mscl
{
#ifndef SWIG

    //Class: BaseStation_WriteEeprom
    //    Contains logic for the base station write eeprom command
    class BaseStation_WriteEeprom
    {
    private:
        BaseStation_WriteEeprom();                                            //default constructor disabled
        BaseStation_WriteEeprom(const BaseStation_WriteEeprom&);            //copy constructor disabled
        BaseStation_WriteEeprom& operator=(const BaseStation_WriteEeprom&);    //assignement operator disabled

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
        static ByteStream buildCommand(uint16 eepromAddress, uint16 valueToWrite);

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
            //    collector - The <ResponseCollector> used to register and unregister the response
            Response(uint16 valueToWrite, std::weak_ptr<ResponseCollector> collector);

        private:
            //Variable: m_valueWritten
            //    The value that is expected to be written to eeprom from the associated command
            uint16 m_valueWritten;

        protected:
            //Function: matchSuccessResponse
            //    Checks if the bytes passed in match the success response pattern from their current read position
            //
            //Parameters:
            //    data - The <DataBuffer> containing the bytes in which to try to find the pattern
            //
            //Returns:
            //    true if the success response pattern was found, false otherwise
            bool matchSuccessResponse(DataBuffer& data) override;

            //Function: matchFailResponse
            //    Checks if the bytes passed in match the failure response pattern from their current read position
            //
            //Parameters:
            //    data - The <DataBuffer> containing the bytes in which to try to find the pattern
            //
            //Returns:
            //    true if the failure response pattern was found, false otherwise
            bool matchFailResponse(DataBuffer& data) override;
        };
    };

#endif

}