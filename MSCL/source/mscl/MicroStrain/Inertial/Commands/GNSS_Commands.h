/*******************************************************************************
Copyright(c) 2015-2017 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "GenericInertialCommand.h"
#include "mscl/MicroStrain/Inertial/InertialChannel.h"

namespace mscl
{
    //Title: GNSS_Commands

    //Class: GetGnssDataRateBase
    //    Contains the logic for the "Get GNSS Data Rate Base" command
    class GetGnssDataRateBase
    {
    public:
        //Constants: Packet Bytes
        //    CMD_ID               - CMD_GET_GPS_RATE_BASE        - The <InertialTypes::Command> for this command
        //  FIELD_DATA_BYTE        - 0x84                        - The Data Field Descriptor byte
        static const InertialTypes::Command CMD_ID    = InertialTypes::CMD_GET_GNSS_RATE_BASE;
        static const uint8 FIELD_DATA_BYTE            = 0x84;

    private:
        GetGnssDataRateBase();    //private default constructor

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
            //Function: fieldId
            //    Gets the <InertialTypes::Command>
            virtual InertialTypes::Command commandId() const override { return CMD_ID; }

            //Function: fieldDataByte
            //    Gets the data field descriptor byte
            virtual uint8 fieldDataByte() const    override { return FIELD_DATA_BYTE; }

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

    //Class: GnssMessageFormat
    //    Contains the logic for the "GPS Message Format" command
    class GnssMessageFormat
    {
    public:
        //Constants: Packet Bytes
        //  CMD_ID                - CMD_GNSS_MESSAGE_FORMAT    - The <InertialTypes::Command> for this command
        //  FIELD_DATA_BYTE       - 0x81                       - The Data Field Descriptor byte
        static const InertialTypes::Command CMD_ID = InertialTypes::CMD_GNSS_MESSAGE_FORMAT;
        static const uint8 FIELD_DATA_BYTE            = 0x81;

    private:
        GnssMessageFormat();    //disabled default constructor

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
        //    channels - The <InertialChannels> holding the channels to be set. This should only contain channels that are in the GPS (0x81) descriptor set.
        //    sampleRateBase - The base sample rate for the gps command set.
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
            virtual InertialTypes::Command commandId() const override { return CMD_ID; }
            virtual uint8 fieldDataByte() const    override { return FIELD_DATA_BYTE; }

        public:
            Response(std::weak_ptr<ResponseCollector> collector, bool dataResponse);
            InertialChannels parseResponse(const GenericInertialCommandResponse& response, uint16 sampleRateBase) const;
        };
    };
}