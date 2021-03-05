/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "mscl/MicroStrain/MIP/Commands/GenericMipCommand.h"
#include "mscl/MicroStrain/MIP/MipChannel.h"
#include "mscl/MicroStrain/Inertial/ExposedInertialTypes.h"

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
        //  CMD_ID              - CMD_GET_EF_RATE_BASE        - The <MipTypes::Command> for this command
        //  FIELD_DATA_BYTE     - 0x8A                        - The Data Field Descriptor byte
        static const MipTypes::Command CMD_ID    = MipTypes::CMD_GET_EF_RATE_BASE;
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
        //    <GenericMipCommand::Response>
        class Response : public GenericMipCommand::Response
        {
        protected:
            //Function: fieldId
            //    Gets the <MipTypes::Command>
            virtual MipTypes::Command commandId() const { return CMD_ID; }

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
            //    response - The <GenericMipCmdResponse> holding the response to parse
            //
            //Returns:
            //    The data rate base result
            uint16 parseResponse(const GenericMipCmdResponse& response) const;
        };
    };

    //Class: EstFilterMessageFormat
    //    Contains the logic for the "Estimation Filter Message Format" command
    class EstFilterMessageFormat
    {
    public:
        //Constants: Packet Bytes
        //  CMD_ID              - CMD_EF_MESSAGE_FORMAT    - The <MipTypes::Command> for this command
        //  FIELD_DATA_BYTE     - 0x82                    - The Data Field Descriptor byte
        static const MipTypes::Command CMD_ID    = MipTypes::CMD_EF_MESSAGE_FORMAT;
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
        //    channels - The <MipChannels> holding the channels to be set. This should only contain channels that are in the Estimation Filter (0x82) descriptor set 
        //    sampleRateBase - The base sample rate for the estimation filter command set.
        //
        //Returns:
        //    A <ByteStream> that holds the bytes that make up the command
        //
        //Exceptions:
        //    - <Error>: An <MipChannel> in the channels parameter is not part of the Sensor descriptor set
        static ByteStream buildCommand_set(const MipChannels& channels, uint16 sampleRateBase);

        //Function: buildCommand_save
        //    Builds the bytes for the "save" command
        //
        //Returns:
        //    A <ByteStream> that holds the bytes that make up the command
        static ByteStream buildCommand_save();
        
        class Response : public GenericMipCommand::Response
        {
        protected:
//            virtual MipTypes::Command commandId() const { return CMD_ID; }
            virtual uint8 fieldDataByte() const { return FIELD_DATA_BYTE; }

        public:
            Response(std::weak_ptr<ResponseCollector> collector, bool dataResponse);
            MipChannels parseResponse(const GenericMipCmdResponse& response, uint16 sampleRateBase) const;
        };
    };

    //Class: ResetFilter
    //    Contains the logic for the "Reset Filter" command
    class ResetFilter
    {
    public:
        //Constants: Packet Bytes
        //  CMD_ID              - CMD_EF_RESET_FILTER       - The <MipTypes::Command> for this command
        static const MipTypes::Command CMD_ID = MipTypes::CMD_EF_RESET_FILTER;

    private:
        ResetFilter() = delete;

    public:
        //Function: buildCommand
        //    Builds the bytes for the command. 
        static ByteStream buildCommand();

        class Response: public GenericMipCommand::Response
        {
        //protected:
        //    virtual MipTypes::Command commandId() const { return CMD_ID; }

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
        //  CMD_ID              - CMD_EF_INIT_ATTITUDE     - The <MipTypes::Command> for this command
        static const MipTypes::Command CMD_ID = MipTypes::CMD_EF_INIT_ATTITUDE;

    private:
        SetInitialAttitude() = delete;

    public:
        //Function: buildCommand
        //    Builds the bytes for the command. 
        //
        //Parameters:
        //    attitude - The <EulerAngles> representing the initial attitude.
        static ByteStream buildCommand(const EulerAngles& attitude);

        class Response: public GenericMipCommand::Response
        {
        //protected:
        //    virtual MipTypes::Command commandId() const { return CMD_ID; }

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
        //  CMD_ID              - CMD_EF_INIT_HEADING     - The <MipTypes::Command> for this command
        static const MipTypes::Command CMD_ID = MipTypes::CMD_EF_INIT_HEADING;

    private:
        SetInitialHeading() = delete;

    public:
        //Function: buildCommand
        //    Builds the bytes for the command. 
        //
        //Parameters:
        //    heading - The heading value to set.
        static ByteStream buildCommand(float heading);

        class Response: public GenericMipCommand::Response
        {
        protected:
            virtual MipTypes::Command commandId() const { return CMD_ID; }

        public:
            Response(std::weak_ptr<ResponseCollector> collector);
        };
    };

    //Class: AltitudeAidControl
    //    Contains the logic for the "Altitude Aid Control" command
    class AltitudeAidControl
    {
    public:
        //Constants: Packet Bytes
        //  CMD_ID              - CMD_EF_ALTITUDE_AID_CTRL  - The <MipTypes::Command> for this command
        //  FIELD_DATA_BYTE     - 0xB7                      - The Data Field Descriptor byte
        static const MipTypes::Command CMD_ID = MipTypes::CMD_EF_ALTITUDE_AID_CTRL;
        static const uint8 FIELD_DATA_BYTE = 0xB7;

    private:
        AltitudeAidControl() = delete;

    public:
        //Function: buildCommand_get
        //    Builds the bytes for the "get" command.
        static ByteStream buildCommand_get();

        //Function: buildCommand_set
        //    Builds the bytes for the "set" command. 
        //
        //Parameters:
        //    enable - Whether to enable (true) or disable (false) altitude aiding.
        static ByteStream buildCommand_set(bool enable);

        class Response : public GenericMipCommand::Response
        {
        protected:
            virtual MipTypes::Command commandId() const { return CMD_ID; }
            virtual uint8 fieldDataByte() const { return FIELD_DATA_BYTE; }

        public:
            Response(std::weak_ptr<ResponseCollector> collector, bool dataResponse);
            bool parseResponse(const GenericMipCmdResponse& response) const;
        };
    };

    //Class: PitchRollAidControl
    //    Contains the logic for the "Pitch/Roll Aid Control" command
    class PitchRollAidControl
    {
    public:
        //Constants: Packet Bytes
        //  CMD_ID              - CMD_EF_PITCH_ROLL_AID_CTRL- The <MipTypes::Command> for this command
        //  FIELD_DATA_BYTE     - 0xBB                      - The Data Field Descriptor byte
        static const MipTypes::Command CMD_ID = MipTypes::CMD_EF_PITCH_ROLL_AID_CTRL;
        static const uint8 FIELD_DATA_BYTE = 0xBB;

    private:
        PitchRollAidControl() = delete;

    public:
        //Function: buildCommand_get
        //    Builds the bytes for the "get" command.
        static ByteStream buildCommand_get();

        //Function: buildCommand_set
        //    Builds the bytes for the "set" command. 
        //
        //Parameters:
        //    enable - Whether to enable (true) or disable (false) the pitch/roll aiding.
        static ByteStream buildCommand_set(bool enable);

        class Response : public GenericMipCommand::Response
        {
        protected:
            virtual MipTypes::Command commandId() const { return CMD_ID; }
            virtual uint8 fieldDataByte() const { return FIELD_DATA_BYTE; }

        public:
            Response(std::weak_ptr<ResponseCollector> collector, bool dataResponse);
            bool parseResponse(const GenericMipCmdResponse& response) const;
        };
    };

    //Class: VelocityZUPTControl
    //    Contains the logic for the "Velocity ZUPT Control" command
    class VelocityZUPTControl
    {
    public:
        //Constants: Packet Bytes
        //  CMD_ID              - CMD_EF_ZERO_VEL_UPDATE_CTRL - The <MipTypes::Command> for this command
        //  FIELD_DATA_BYTE     - 0x8D                         - The Data Field Descriptor byte
        static const MipTypes::Command CMD_ID = MipTypes::CMD_EF_ZERO_VEL_UPDATE_CTRL;
        static const uint8 FIELD_DATA_BYTE = 0x8D;

    private:
        VelocityZUPTControl() = delete;

    public:
        //Function: buildCommand_get
        //    Builds the bytes for the "get" command.
        static ByteStream buildCommand_get();

        //Function: buildCommand_set
        //    Builds the bytes for the "set" command. 
        //
        //Parameters:
        //    settingsData - The ZUPTSettingsData object containing whether the command is enabled and the threshold.
        static ByteStream buildCommand_set(const ZUPTSettingsData& settingsData);

        class Response : public GenericMipCommand::Response
        {
        protected:
            virtual MipTypes::Command commandId() const { return CMD_ID; }
            virtual uint8 fieldDataByte() const { return FIELD_DATA_BYTE; }

        public:
            Response(std::weak_ptr<ResponseCollector> collector, bool dataResponse);
            ZUPTSettingsData parseResponse(const GenericMipCmdResponse& response) const;
        };
    };

    //Class: AngularRateZUPTControl
    //    Contains the logic for the "Angular Rate ZUPT Control" command
    class AngularRateZUPTControl
    {
    public:
        //Constants: Packet Bytes
        //  CMD_ID              - CMD_EF_CMDED_ZERO_ANG_RATE_UPDATE - The <MipTypes::Command> for this command
        //  FIELD_DATA_BYTE     - 0x8E                              - The Data Field Descriptor byte
        static const MipTypes::Command CMD_ID = MipTypes::CMD_EF_ZERO_ANG_RATE_UPDATE_CTRL;
        static const uint8 FIELD_DATA_BYTE = 0x8E;

    private:
        AngularRateZUPTControl() = delete;

    public:
        //Function: buildCommand_get
        //    Builds the bytes for the "get" command.
        static ByteStream buildCommand_get();

        //Function: buildCommand_set
        //    Builds the bytes for the "set" command. 
        //
        //Parameters:
        //    settingsData - The ZUPTSettingsData object containing whether the command is enabled and the threshold.
        static ByteStream buildCommand_set(const ZUPTSettingsData& settingsData);

        class Response : public GenericMipCommand::Response
        {
        protected:
            virtual MipTypes::Command commandId() const { return CMD_ID; }
            virtual uint8 fieldDataByte() const { return FIELD_DATA_BYTE; }

        public:
            Response(std::weak_ptr<ResponseCollector> collector, bool dataResponse);
            ZUPTSettingsData parseResponse(const GenericMipCmdResponse& response) const;
        };
    };


    //Class: TareOrientation
    //    Contains the logic for the "Tare Orientation" command
    class TareOrientation
    {
    public:
        //Constants: Packet Bytes
        //  CMD_ID              - CMD_EF_TARE_ORIENT - The <MipTypes::Command> for this command
        //  FIELD_DATA_BYTE     - 0x00 - The Data Field Descriptor byte as there is no data field
        static const MipTypes::Command CMD_ID = MipTypes::CMD_EF_TARE_ORIENT;
        static const uint8 FIELD_DATA_BYTE = 0xF1;

    private:
        TareOrientation() = delete;

    public:

        //Function: buildCommand_set
        //    Builds the bytes for the "set" command.
        //
        //Parameters:
        //    functionSelector - The function selector for how to load and save data.
        //    axisValue - The TareAxisValues for which axes to tare.
        static ByteStream buildCommand_set(const TareAxisValues& axisValue);

        class Response : public GenericMipCommand::Response
        {
        protected:
            virtual MipTypes::Command commandId() const { return CMD_ID; }
            virtual uint8 fieldDataByte() const { return FIELD_DATA_BYTE; }

        public:
            Response(std::weak_ptr<ResponseCollector> collector, bool dataResponse);
            bool parseResponse(const GenericMipCmdResponse& response) const;
        };
    };

    //Class: AutoInitializeControl
    //    Contains the logic for the "Auto-Initialization Control" command
    class AutoInitializeControl
    {
    public:
        //Constants: Packet Bytes
        //  CMD_ID              - CMD_EF_AUTO_INIT_CTRL     - The <MipTypes::Command> for this command
        //  FIELD_DATA_BYTE     - 0x88                      - The Data Field Descriptor byte
        static const MipTypes::Command CMD_ID = MipTypes::CMD_EF_AUTO_INIT_CTRL;
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

        class Response: public GenericMipCommand::Response
        {
        protected:
            virtual MipTypes::Command commandId() const { return CMD_ID; }
            virtual uint8 fieldDataByte() const { return FIELD_DATA_BYTE; }

        public:
            Response(std::weak_ptr<ResponseCollector> collector, bool dataResponse);
            bool parseResponse(const GenericMipCmdResponse& response) const;
        };
    };

    //Class: CmdedVelZupt
    //    Contains the logic for the "Commanded Zero Velocity Update" command
    class CmdedVelZupt
    {
    public:
        //Constants: Packet Bytes
        //  CMD_ID              - CMD_EF_CMDED_ZERO_VEL_UPDATE    - The <MipTypes::Command> for this command
        //  FIELD_DATA_BYTE     - 0xF1                                      - The Data Field Descriptor byte
        static const MipTypes::Command CMD_ID = MipTypes::CMD_EF_CMDED_ZERO_VEL_UPDATE;
        static const uint8 FIELD_DATA_BYTE = 0xF1;

    private:
        CmdedVelZupt() = delete;

    public:
        //Function: buildCommand_get
        //    Builds the bytes for the "get" command.
        static ByteStream buildCommand_get();

        class Response : public GenericMipCommand::Response
        {
        protected:
            virtual MipTypes::Command commandId() const { return CMD_ID; }
            virtual uint8 fieldDataByte() const { return FIELD_DATA_BYTE; }

        public:
            Response(std::weak_ptr<ResponseCollector> collector, bool dataResponse);
        };
    };


    //Class: CmdedAngularZupt
    //    Contains the logic for the "Commanded Zero Angular Rate Update" command
    class CmdedAngularZupt
    {
    public:
        //Constants: Packet Bytes
        //  CMD_ID              - CMD_EF_CMDED_ZERO_ANG_RATE_UPDATE    - The <MipTypes::Command> for this command
        //  FIELD_DATA_BYTE     - 0xF1                                      - The Data Field Descriptor byte
        static const MipTypes::Command CMD_ID = MipTypes::CMD_EF_CMDED_ZERO_ANG_RATE_UPDATE;
        static const uint8 FIELD_DATA_BYTE = 0xF1;

    private:
        CmdedAngularZupt() = delete;

    public:
        //Function: buildCommand_get
        //    Builds the bytes for the "get" command.
        static ByteStream buildCommand_get();

        class Response : public GenericMipCommand::Response
        {
        protected:
            virtual MipTypes::Command commandId() const { return CMD_ID; }
            virtual uint8 fieldDataByte() const { return FIELD_DATA_BYTE; }

        public:
            Response(std::weak_ptr<ResponseCollector> collector, bool dataResponse);
        };
    };

    //Class: SensorToVehicFrameTrans
    //    Contains the logic for the "Sensor to Vehicle Frame Transformation" command
    class SensorToVehicFrameTrans
    {
    public:
        //Constants: Packet Bytes
        //  CMD_ID              - CMD_EF_SENS_VEHIC_FRAME_ROTATION_EULER    - The <MipTypes::Command> for this command
        //  FIELD_DATA_BYTE     - 0x81                                      - The Data Field Descriptor byte
        static const MipTypes::Command CMD_ID = MipTypes::CMD_EF_SENS_VEHIC_FRAME_ROTATION_EULER;
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

        class Response: public GenericMipCommand::Response
        {
        protected:
            virtual MipTypes::Command commandId() const { return CMD_ID; }
            virtual uint8 fieldDataByte() const { return FIELD_DATA_BYTE; }

        public:
            Response(std::weak_ptr<ResponseCollector> collector, bool dataResponse);
            EulerAngles parseResponse(const GenericMipCmdResponse& response) const;
        };
    };

    //Class: SensorToVehicFrameOffset
    //    Contains the logic for the "Sensor to Vehicle Frame Offset" command
    class SensorToVehicFrameOffset
    {
    public:
        //Constants: Packet Bytes
        //  CMD_ID              - CMD_EF_SENS_VEHIC_FRAME_OFFSET    - The <MipTypes::Command> for this command
        //  FIELD_DATA_BYTE     - 0x82                              - The Data Field Descriptor byte
        static const MipTypes::Command CMD_ID = MipTypes::CMD_EF_SENS_VEHIC_FRAME_OFFSET;
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

        class Response: public GenericMipCommand::Response
        {
        protected:
            virtual MipTypes::Command commandId() const { return CMD_ID; }
            virtual uint8 fieldDataByte() const { return FIELD_DATA_BYTE; }

        public:
            Response(std::weak_ptr<ResponseCollector> collector, bool dataResponse);
            PositionOffset parseResponse(const GenericMipCmdResponse& response) const;
        };
    };

    //Class: AntennaOffset
    //    Contains the logic for the "Antenna Offset" command
    class AntennaOffset
    {
    public:
        //Constants: Packet Bytes
        //  CMD_ID              - CMD_EF_ANTENNA_OFFSET     - The <MipTypes::Command> for this command
        //  FIELD_DATA_BYTE     - 0x83                      - The Data Field Descriptor byte
        static const MipTypes::Command CMD_ID = MipTypes::CMD_EF_ANTENNA_OFFSET;
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

        class Response: public GenericMipCommand::Response
        {
        protected:
            virtual MipTypes::Command commandId() const { return CMD_ID; }
            virtual uint8 fieldDataByte() const { return FIELD_DATA_BYTE; }

        public:
            Response(std::weak_ptr<ResponseCollector> collector, bool dataResponse);
            PositionOffset parseResponse(const GenericMipCmdResponse& response) const;
        };
    };
}