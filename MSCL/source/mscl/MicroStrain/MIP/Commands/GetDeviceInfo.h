/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "mscl/MicroStrain/MIP/Commands/GenericMipCommand.h"
#include "mscl/Version.h"
#include "mscl/MicroStrain/MIP/Commands/MipCmdResponse.h"
#include "mscl/MicroStrain/MIP/MipModels.h"

#include <string>

namespace mscl
{
    //Title: GetDeviceInfo

    //Struct: MipDeviceInfo
    //    Contains information retrieved from an Inertial GetDeviceInfo command.
    struct MipDeviceInfo
    {
    public:
        //Variable: fwVersion
        //    The firmware <Version>.
        Version fwVersion;

        //Variable: modelName
        //    The model name.
        std::string modelName;

        //Variable: modelNumber
        //    The model number.
        std::string modelNumber;

        //Variable: serialNumber
        //    The serial number.
        std::string serialNumber;

        //Variable: lotNumber
        //    The lot number.
        std::string lotNumber;

        //Variable: deviceOptions
        //    The device options.
        std::string deviceOptions;
    };

    //Class: GetDeviceInfo
    //    Contains the logic for the Inertial GetDeviceInfo command
    class GetDeviceInfo
    {
    public:
        //Constants: Packet Bytes
        //  CMD_ID              - CMD_GET_DEVICE_INFO   - The <MipTypes::Command> for this command
        //  FIELD_DATA_BYTE     - 0x81                  - The Data Field Descriptor byte
        static const MipTypes::Command CMD_ID = MipTypes::CMD_GET_DEVICE_INFO;
        static const uint8 FIELD_DATA_BYTE = 0x81;

    private:
        GetDeviceInfo();                                //default constructor disabled

    public:
        //Function: buildCommand
        //    Builds the command packet
        //
        //Returns:
        //    A <ByteStream> containing the Inertial GetDeviceInfo command packet
        static ByteStream buildCommand();

        //Class: Response
        //    Handles the response to the GetDeviceInfo command
        class Response : public GenericMipCommand::Response
        {
        protected:
            virtual uint8 fieldDataByte() const override { return FIELD_DATA_BYTE; }

        public:
            //Constructor: Response
            //    Creates a GetDeviceInfo Response object
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
            //    Parses a successfully matched response for the GetDeviceInfo command.
            //
            //Parameters:
            //    response - The <GenericMipCmdResponse> that matches the data field for this response.
            //
            //Returns:
            //    The GetDeviceInfoResponse parsed from the response.
            MipDeviceInfo parseResponse(const GenericMipCmdResponse& response) const;
        };
    };
}