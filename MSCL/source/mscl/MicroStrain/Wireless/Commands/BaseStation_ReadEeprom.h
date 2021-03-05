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

    //Class: BaseStation_ReadEeprom
    //    Contains logic for the base station read eeprom command
    class BaseStation_ReadEeprom
    {
    private:
        BaseStation_ReadEeprom();                                            //default constructor disabled
        BaseStation_ReadEeprom(const BaseStation_ReadEeprom&);                //copy constructor disabled
        BaseStation_ReadEeprom& operator=(const BaseStation_ReadEeprom&);    //assignement operator disabled

    public:
        //Function: buildCommand
        //    Builds the eeprom read command packet
        //
        //Parameters:
        //    eepromAddress - The eeprom address to read from the base station
        //
        //Returns:
        //    A <ByteStream> containing the base station read eeprom command
        static ByteStream buildCommand(uint16 eepromAddress);

        //Class: Response
        //    Handles the response to the base station read eeprom command
        class Response : public WirelessResponsePattern
        {
        public:
            //Constructor: Response
            //    Creates a read eeprom Response object
            //
            //Parameters:
            //    collector - The <ResponseCollector> used to register and unregister the response 
            Response(std::weak_ptr<ResponseCollector> collector);

        private:
            //Variable: m_result
            //    The result value of the read eeprom command.
            uint16 m_result;

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