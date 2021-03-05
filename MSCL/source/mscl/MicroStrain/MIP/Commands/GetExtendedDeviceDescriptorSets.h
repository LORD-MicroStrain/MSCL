/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "mscl/MicroStrain/MIP/Commands/GenericMipCommand.h"

namespace mscl
{
    //Class: GetExtendedDeviceDescriptorSets
    //    Contains the logic for the Inertial "Get Extended Device Descriptor Sets" command
    class GetExtendedDeviceDescriptorSets
    {
    public:
        //Constants: Packet Bytes
        //  CMD_ID              - CMD_GET_EXT_DESCRIPTOR_SETS   - The <MipTypes::Command> for this command
        //  FIELD_DATA_BYTE     - 0x86                          - The Data Field Descriptor byte
        static const MipTypes::Command CMD_ID = MipTypes::CMD_GET_EXT_DESCRIPTOR_SETS;
        static const uint8 FIELD_DATA_BYTE            = 0x86;

    private:
        GetExtendedDeviceDescriptorSets();        //default constructor disabled

    public:
        //Function: buildCommand
        //    Builds the command packet
        //
        //Returns:
        //    A <ByteStream> containing the Inertial GetExtendedDeviceDescriptorSets command packet
        static ByteStream buildCommand();

        //Class: Response
        //    Handles the response to the GetExtendedDeviceDescriptorSets command
        class Response : public GenericMipCommand::Response
        {
        protected:
            virtual uint8 fieldDataByte() const override { return FIELD_DATA_BYTE; }

        public:
            //Constructor: Response
            //    Creates a Response object
            //
            //Parameters:
            //    collector - The <ResponseCollector> used to register and unregister the response
            Response(std::weak_ptr<ResponseCollector> collector);

        public:
            //Function: match_data
            //    Attempts to match an <MipDataField> to the expected data field response.
            //
            //Returns:
            //    true if the field matches the expected data, false if it does not.
            virtual bool match_data(const MipDataField& field) override;

            //Function: parseResponse
            //    Parses a successfully matched response for the GetExtendedDeviceDescriptorSets command.
            //
            //Parameters:
            //    response - The <GenericMipCmdResponse> that matches the data field for this response.
            //    descriptors - The container to insert the extended descriptors into.
            //
            //Returns:
            //    The descriptor sets parsed from the response.
            void parseResponse(const GenericMipCmdResponse& response, std::vector<uint16>& descriptors) const;
        };
    };
}