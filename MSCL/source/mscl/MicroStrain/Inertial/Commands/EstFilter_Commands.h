/*******************************************************************************
Copyright(c) 2015-2016 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "GenericInertialCommand.h"
#include "mscl/MicroStrain/Inertial/InertialChannel.h"

namespace mscl
{
    //Title: EstFilter_Commands

    //forward declarations
    class EulerAngles;
    class PositionOffset;

    //Class: GetEstFilterDataRateBase
    //    Contains the logic for the "Get Estimation Filter Data Rate Base" command
    class GetEstFilterDataRateBase
    {
    public:
        //Constants: Packet Bytes
        //  CMD_ID              - CMD_GET_EF_RATE_BASE        - The <InertialTypes::Command> for this command
        //  FIELD_DATA_BYTE     - 0x8A                        - The Data Field Descriptor byte
        static const InertialTypes::Command CMD_ID    = InertialTypes::CMD_GET_EF_RATE_BASE;
        static const uint8 FIELD_DATA_BYTE            = 0x8A;

    private:
        GetEstFilterDataRateBase() = delete;

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
            virtual InertialTypes::Command commandId() const { return CMD_ID; }

            //Function: fieldDataByte
            //    Gets the data field descriptor byte
            virtual uint8 fieldDataByte() const    { return FIELD_DATA_BYTE; }

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

    //Class: EstFilterMessageFormat
    //    Contains the logic for the "Estimation Filter Message Format" command
    class EstFilterMessageFormat
    {
    public:
        //Constants: Packet Bytes
        //  CMD_ID              - CMD_EF_MESSAGE_FORMAT    - The <InertialTypes::Command> for this command
        //  FIELD_DATA_BYTE     - 0x82                    - The Data Field Descriptor byte
        static const InertialTypes::Command CMD_ID    = InertialTypes::CMD_EF_MESSAGE_FORMAT;
        static const uint8 FIELD_DATA_BYTE            = 0x82;

    private:
        EstFilterMessageFormat() = delete;

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
        //    channels - The <InertialChannels> holding the channels to be set. This should only contain channels that are in the Estimation Filter (0x82) descriptor set 
        //    sampleRateBase - The base sample rate for the estimation filter command set.
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
            virtual InertialTypes::Command commandId() const { return CMD_ID; }
            virtual uint8 fieldDataByte() const { return FIELD_DATA_BYTE; }

        public:
            Response(std::weak_ptr<ResponseCollector> collector, bool dataResponse);
            InertialChannels parseResponse(const GenericInertialCommandResponse& response, uint16 sampleRateBase) const;
        };
    };

    //Class: ResetFilter
    //    Contains the logic for the "Reset Filter" command
    class ResetFilter
    {
    public:
        //Constants: Packet Bytes
        //  CMD_ID              - CMD_EF_RESET_FILTER       - The <InertialTypes::Command> for this command
        static const InertialTypes::Command CMD_ID = InertialTypes::CMD_EF_RESET_FILTER;

    private:
        ResetFilter() = delete;

    public:
        //Function: buildCommand
        //    Builds the bytes for the command. 
        static ByteStream buildCommand();

        class Response: public GenericInertialCommand::Response
        {
        protected:
            virtual InertialTypes::Command commandId() const { return CMD_ID; }

        public:
            Response(std::weak_ptr<ResponseCollector> collector);
        };
    };

    //Class: SetInitialAttitude
    //    Contains the logic for the "Set Initial Attitude" command
    class SetInitialAttitude
    {
    public:
        //Constants: Packet Bytes
        //  CMD_ID              - CMD_EF_INIT_ATTITUDE     - The <InertialTypes::Command> for this command
        static const InertialTypes::Command CMD_ID = InertialTypes::CMD_EF_INIT_ATTITUDE;

    private:
        SetInitialAttitude() = delete;

    public:
        //Function: buildCommand
        //    Builds the bytes for the command. 
        //
        //Parameters:
        //    attitude - The <EulerAngles> representing the initial attitude.
        static ByteStream buildCommand(const EulerAngles& attitude);

        class Response: public GenericInertialCommand::Response
        {
        protected:
            virtual InertialTypes::Command commandId() const { return CMD_ID; }

        public:
            Response(std::weak_ptr<ResponseCollector> collector);
        };
    };

    //Class: SetInitialHeading
    //    Contains the logic for the "Set Initial Heading" command
    class SetInitialHeading
    {
    public:
        //Constants: Packet Bytes
        //  CMD_ID              - CMD_EF_INIT_HEADING     - The <InertialTypes::Command> for this command
        static const InertialTypes::Command CMD_ID = InertialTypes::CMD_EF_INIT_HEADING;

    private:
        SetInitialHeading() = delete;

    public:
        //Function: buildCommand
        //    Builds the bytes for the command. 
        //
        //Parameters:
        //    heading - The heading value to set.
        static ByteStream buildCommand(float heading);

        class Response: public GenericInertialCommand::Response
        {
        protected:
            virtual InertialTypes::Command commandId() const { return CMD_ID; }

        public:
            Response(std::weak_ptr<ResponseCollector> collector);
        };
    };

    //Class: AutoInitializeControl
    //    Contains the logic for the "Auto-Initialization Control" command
    class AutoInitializeControl
    {
    public:
        //Constants: Packet Bytes
        //  CMD_ID              - CMD_EF_AUTO_INIT_CTRL     - The <InertialTypes::Command> for this command
        //  FIELD_DATA_BYTE     - 0x88                      - The Data Field Descriptor byte
        static const InertialTypes::Command CMD_ID = InertialTypes::CMD_EF_AUTO_INIT_CTRL;
        static const uint8 FIELD_DATA_BYTE = 0x88;

    private:
        AutoInitializeControl() = delete;

    public:
        //Function: buildCommand_get
        //    Builds the bytes for the "get" command.
        static ByteStream buildCommand_get();

        //Function: buildCommand_set
        //    Builds the bytes for the "set" command. 
        //
        //Parameters:
        //    enable - Whether to enable (true) or disable (false) the automatic initialization.
        static ByteStream buildCommand_set(bool enable);

        class Response: public GenericInertialCommand::Response
        {
        protected:
            virtual InertialTypes::Command commandId() const { return CMD_ID; }
            virtual uint8 fieldDataByte() const { return FIELD_DATA_BYTE; }

        public:
            Response(std::weak_ptr<ResponseCollector> collector, bool dataResponse);
            bool parseResponse(const GenericInertialCommandResponse& response) const;
        };
    };

    //Class: SensorToVehicFrameTrans
    //    Contains the logic for the "Sensor to Vehicle Frame Transformation" command
    class SensorToVehicFrameTrans
    {
    public:
        //Constants: Packet Bytes
        //  CMD_ID              - CMD_EF_SENS_VEHIC_FRAME_TRANS     - The <InertialTypes::Command> for this command
        //  FIELD_DATA_BYTE     - 0x81                              - The Data Field Descriptor byte
        static const InertialTypes::Command CMD_ID = InertialTypes::CMD_EF_SENS_VEHIC_FRAME_TRANS;
        static const uint8 FIELD_DATA_BYTE = 0x81;

    private:
        SensorToVehicFrameTrans() = delete;

    public:
        //Function: buildCommand_get
        //    Builds the bytes for the "get" command.
        static ByteStream buildCommand_get();

        //Function: buildCommand_set
        //    Builds the bytes for the "set" command. 
        //
        //Parameters:
        //    angles-  The <EulerAngles> containing the roll, pitch, and yaw (in radians).
        static ByteStream buildCommand_set(const EulerAngles& angles);

        class Response: public GenericInertialCommand::Response
        {
        protected:
            virtual InertialTypes::Command commandId() const { return CMD_ID; }
            virtual uint8 fieldDataByte() const { return FIELD_DATA_BYTE; }

        public:
            Response(std::weak_ptr<ResponseCollector> collector, bool dataResponse);
            EulerAngles parseResponse(const GenericInertialCommandResponse& response) const;
        };
    };

    //Class: SensorToVehicFrameOffset
    //    Contains the logic for the "Sensor to Vehicle Frame Offset" command
    class SensorToVehicFrameOffset
    {
    public:
        //Constants: Packet Bytes
        //  CMD_ID              - CMD_EF_SENS_VEHIC_FRAME_OFFSET    - The <InertialTypes::Command> for this command
        //  FIELD_DATA_BYTE     - 0x82                              - The Data Field Descriptor byte
        static const InertialTypes::Command CMD_ID = InertialTypes::CMD_EF_SENS_VEHIC_FRAME_OFFSET;
        static const uint8 FIELD_DATA_BYTE = 0x82;

    private:
        SensorToVehicFrameOffset() = delete;

    public:
        //Function: buildCommand_get
        //    Builds the bytes for the "get" command.
        static ByteStream buildCommand_get();

        //Function: buildCommand_set
        //    Builds the bytes for the "set" command. 
        //
        //Parameters:
        //    offset -  The <PositionOffset> in meters.
        static ByteStream buildCommand_set(const PositionOffset& offset);

        class Response: public GenericInertialCommand::Response
        {
        protected:
            virtual InertialTypes::Command commandId() const { return CMD_ID; }
            virtual uint8 fieldDataByte() const { return FIELD_DATA_BYTE; }

        public:
            Response(std::weak_ptr<ResponseCollector> collector, bool dataResponse);
            PositionOffset parseResponse(const GenericInertialCommandResponse& response) const;
        };
    };

    //Class: AntennaOffset
    //    Contains the logic for the "Antenna Offset" command
    class AntennaOffset
    {
    public:
        //Constants: Packet Bytes
        //  CMD_ID              - CMD_EF_ANTENNA_OFFSET     - The <InertialTypes::Command> for this command
        //  FIELD_DATA_BYTE     - 0x83                      - The Data Field Descriptor byte
        static const InertialTypes::Command CMD_ID = InertialTypes::CMD_EF_ANTENNA_OFFSET;
        static const uint8 FIELD_DATA_BYTE = 0x83;

    private:
        AntennaOffset() = delete;

    public:
        //Function: buildCommand_get
        //    Builds the bytes for the "get" command.
        static ByteStream buildCommand_get();

        //Function: buildCommand_set
        //    Builds the bytes for the "set" command. 
        //
        //Parameters:
        //    offset -  The <PositionOffset> in meters.
        static ByteStream buildCommand_set(const PositionOffset& offset);

        class Response: public GenericInertialCommand::Response
        {
        protected:
            virtual InertialTypes::Command commandId() const { return CMD_ID; }
            virtual uint8 fieldDataByte() const { return FIELD_DATA_BYTE; }

        public:
            Response(std::weak_ptr<ResponseCollector> collector, bool dataResponse);
            PositionOffset parseResponse(const GenericInertialCommandResponse& response) const;
        };
    };
}