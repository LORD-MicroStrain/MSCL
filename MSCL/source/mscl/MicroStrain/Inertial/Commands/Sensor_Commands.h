/*******************************************************************************
Copyright(c) 2015-2017 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "GenericInertialCommand.h"
#include "mscl/MicroStrain/Inertial/InertialChannel.h"

namespace mscl
{
    //Title: Sensor_Commands

    //Class: GetSensorDataRateBase
    //    Contains the logic for the "Get Sensor Data Rate Base" command
    class GetSensorDataRateBase
    {
    public:
        //Constants: Packet Bytes
        //    CMD_ID                - CMD_GET_SENSOR_RATE_BASE    - The <InertialTypes::Command> for this command
        //  FIELD_DATA_BYTE        - 0x83                        - The Data Field Descriptor byte
        static const InertialTypes::Command CMD_ID = InertialTypes::CMD_GET_SENSOR_RATE_BASE;
        static const uint8 FIELD_DATA_BYTE            = 0x83;
        
    private:
        GetSensorDataRateBase();    //disabled default constructor

    public:
        //Function: buildCommand
        //    Builds the bytes in the command
        //
        //Returns:
        //    A <ByteStream> that holds the bytes that make up the command
        static ByteStream buildCommand();

        //Class: Response
        //    Handles the response to the command
        //
        //See Also:
        //    <GenericInertialCommand::Response>
        class Response : public GenericInertialCommand::Response
        {
        protected:
            //Function: fieldDataByte
            //    Gets the data field descriptor byte
            virtual uint8 fieldDataByte() const override { return FIELD_DATA_BYTE; }

        public:
            //Constructor: Response
            //    Creates the Response object
            Response(std::weak_ptr<ResponseCollector> collector);

            //Function: parseResponse
            //    Parses the response, getting the data rate base result
            //
            //Parameters:
            //    response - The <GenericInertialCommandResponse> holding the response to parse
            //
            //Returns:
            //    The data rate base result
            uint16 parseResponse(const GenericInertialCommandResponse& response) const;
        };
    };


    //Class: SensorMessageFormat
    //    Contains the logic for the "Sensor Data Message Format" command
    class SensorMessageFormat
    {
    public:
        //Constants: Packet Bytes
        //    CMD_ID                - CMD_SENSOR_MESSAGE_FORMAT    - The <InertialTypes::Command> for this command
        //  FIELD_DATA_BYTE        - 0x80                        - The Data Field Descriptor byte
        static const InertialTypes::Command CMD_ID    = InertialTypes::CMD_SENSOR_MESSAGE_FORMAT;
        static const uint8 FIELD_DATA_BYTE            = 0x80;

    private:
        SensorMessageFormat();    //disabled default constructor

    public:
        //Function: buildCommand_get
        //    Builds the bytes for the "get" command
        //
        //Returns:
        //    A <ByteStream> that holds the bytes that make up the command
        static ByteStream buildCommand_get();

        //Function: buildCommand_set
        //    Builds the bytes for the "set" command. 
        //
        //Parameters:
        //    channels - The <InertialChannels> holding the channels to be set. This should only contain channels that are in the Sensor (0x80) descriptor set.
        //    sampleRateBase - The base sample rate for the sensor command set.
        //
        //Returns:
        //    A <ByteStream> that holds the bytes that make up the command
        //
        //Exceptions:
        //    - <Error>: An <InertialChannel> in the channels parameter is not part of the Sensor descriptor set
        static ByteStream buildCommand_set(const InertialChannels& channels, uint16 sampleRateBase);

        class Response : public GenericInertialCommand::Response
        {
        protected:
            virtual uint8 fieldDataByte() const    override { return FIELD_DATA_BYTE; }

        public:
            Response(std::weak_ptr<ResponseCollector> collector, bool dataResponse);
            InertialChannels parseResponse(const GenericInertialCommandResponse& response, uint16 sampleRateBase) const;
        };
    };
}