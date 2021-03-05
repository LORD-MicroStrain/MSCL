/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "mscl/MicroStrain/MIP/Commands/GenericMipCommand.h"
#include "mscl/MicroStrain/MIP/MipTypes.h"

namespace mscl
{
    //Class: ContinuousDataStream
    //    Contains the logic for the "Continuous Data Stream" command.
    class ContinuousDataStream
    {
    public:
        //Constants: Packet Bytes
        //    CMD_ID                - CMD_CONTINUOUS_DATA_STREAM    - The <MipTypes::Command> for this command
        //  FIELD_DATA_BYTE        - 0x85                            - The Data Field Descriptor byte
        static const MipTypes::Command CMD_ID    = MipTypes::CMD_CONTINUOUS_DATA_STREAM;
        static const uint8 FIELD_DATA_BYTE            = 0x85;

    private:
        ContinuousDataStream();    //disabled default constructor

        //Function: getDeviceSelector
        //    Converts an <MipTypes::DataClass> to the device selector for this command.
        //
        //Parameters:
        //    type - The <MipTypes::DataClass> to get the device selector for.
        //
        //Returns:
        //    The device selector for the given <MipTypes::DataClass>.
        static uint8 getDeviceSelector(MipTypes::DataClass type);

    public:
        //Function: buildCommand_get
        //    Builds the bytes for the "get" command.
        //
        //Parameters:
        //    type - The <MipTypes::DataClass> to get the current state for.
        //
        //Returns:
        //    A <ByteStream> that holds the bytes that make up the command.
        static ByteStream buildCommand_get(MipTypes::DataClass type);

        //Function: buildCommand_set
        //    Builds the bytes for the "set" command. 
        //
        //Parameters:
        //    type - The <MipTypes::DataClass> to set the state for.
        //    enable - Whether to enable (true) or disable (false) continuous data streaming.
        //
        //Returns:
        //    A <ByteStream> that holds the bytes that make up the command.
        static ByteStream buildCommand_set(MipTypes::DataClass type, bool enable);

        //Class: Response
        //    Handles the response to the ContinuousDataStream command.
        class Response : public GenericMipCommand::Response
        {
        protected:
            virtual MipTypes::Command commandId() const { return CMD_ID; }
            virtual uint8 fieldDataByte() const            { return FIELD_DATA_BYTE; }

        private:
            //Variable: m_deviceSelector
            //    The device selector to look for in the response.
            uint8 m_deviceSelector;

        public:
            //Constructor: Response
            //    Creates the ContinuousDataStream::Response object.
            //    
            //Parameters:
            //    collector - The ResponseCollector to register the response with.
            //    dataResponse - Whether the command is expecting a data field response
            //    type - The <MipTypes::DataClass> to use for the command/response.
            Response(std::weak_ptr<ResponseCollector> collector, bool dataResponse, MipTypes::DataClass type);

            //Function: match_data
            //    Attempts to match an <MipDataField> to the expected data field response.
            //
            //Returns:
            //    true if the field matches the expected data, false if it does not.
            virtual bool match_data(const MipDataField& field) override;

            //Function: parseResponse
            //    Parses a successfully matched response for the ContinuousDataStream command.
            //
            //Parameters:
            //    response - The <GenericMipCmdResponse> that matches the data field for this response.
            //
            //Returns:
            //    true if the data stream is enabled, false if it is disabled.
            bool parseResponse(const GenericMipCmdResponse& response) const;
        };
    };
}