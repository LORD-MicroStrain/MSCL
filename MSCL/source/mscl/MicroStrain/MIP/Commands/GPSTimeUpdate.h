/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "mscl/MicroStrain/MIP/Commands/GenericMipCommand.h"
#include "mscl/MicroStrain/ResponseCollector.h"
#include "mscl/MicroStrain/Inertial/ExposedInertialTypes.h"

namespace mscl
{

#ifndef SWIG 

    //Class: GPSTimeUpdate
    //    Contains the logic for the Inertial GPSTimeUpdate command.
    class GPSTimeUpdate : private GenericMipCommand
    {
    public:
        static const uint8 FIELD_DATA_BYTE_WEEKS = 0x84;
        static const uint8 FIELD_DATA_BYTE_SECONDS = 0x85;

    protected:
        //Function: CommandId
        //
        //Returns:
        //    MipTypes::Command - the command ID.
        virtual MipTypes::Command commandId() const override { return MipTypes::CMD_GPS_TIME_UPDATE; }

        //API Enums: TimeFieldSelector
        //    The enums to represnt type of time being sent/received.
        //GPS_WEEK_NUMBER - used to identify time being sent or received as a week number type.
        //GPS_SECONDS     - used to identify time being sent or received as a seconds type.
        enum TimeFieldSelector
        {
            GPS_WEEK_NUMBER = 0x01,
            GPS_SECONDS = 0x02
        };

    public:
        //  Constructor: GPSTimeUpdate
        //      Creates a GPSTimeUpdate object.
        GPSTimeUpdate();

    public:
        //  Destructor: ~GPSTimeUpdate
        virtual ~GPSTimeUpdate() {};

        //Function: GetWeekValue
        //    Builds the bytes to get the GPS week value.
        //
        //Returns:
        //    A <ByteStream> containing the GPSTimeUpdate command packet
        ByteStream GetWeekValue();

        //Function: GetSecondsValue
        //    Builds the bytes to get the GPS seconds value.
        //
        //Returns:
        //    A <ByteStream> containing the GPSTimeUpdate command packet
        ByteStream GetSecondsValue();

        //Function: SetWeekValue
        //    Builds the bytes for the "set" command.
        //
        //Parameters:
        //    timeData - The week time to set.
        //
        //Returns:
        //    A <ByteStream> containing the GPSTimeUpdate command packet
        ByteStream SetWeekValue(uint32 timeData);

        //Function: SetSecondsValue
        //    Builds the bytes for the "set" command.
        //
        //Parameters:
        //    timeData -  The seconds time to set.
        //
        //Returns:
        //    A <ByteStream> containing the GPSTimeUpdate command packet
        ByteStream SetSecondsValue(uint32 timeData);

        //Function: resetToFactorySettings
        //    Builds the bytes for the "set" command.
        //
        //Returns:
        //    A <ByteStream> containing the GPSTimeUpdate command packet
        ByteStream resetToFactorySettings();
            
        //Class: Response
        //    Handles the response to the GPSTimeUpdate command.
        class Response : public GenericMipCommand::Response
        {
            //Function: fieldDataByte
            //    Gets the data field descriptor byte
            virtual uint8 fieldDataByte() const  override { return m_fieldDataByte; }

        public:
            //Constructor: Response
            //    Creates a GPSTimeUpdate Response object
            //
            //Parameters:
            //    collector - The <ResponseCollector> used to register and unregister the response
            Response(const uint8 fieldDataByte, std::weak_ptr<ResponseCollector> collector, bool ackNackExpected, bool dataResponseExpected);

            //Function: parseResponse
            //    Parses the response, getting the assist time result
            //
            //Parameters:
            //    response - The <GenericMipCmdResponse> holding the response to parse
            //
            //Returns:
            //    The data rate base result
            unsigned long parseResponse(const GenericMipCmdResponse& response) const;

        private:
            //Variable: m_fieldDataByte
            //  uint8 byte to identify field data.
            const uint8 m_fieldDataByte;
        };
    };

#endif
}
