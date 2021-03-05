/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "mscl/MicroStrain/MIP/Commands/GenericMipCommand.h"
#include "mscl/MicroStrain/ResponseCollector.h"
#include "mscl/MicroStrain/Inertial/ExposedInertialTypes.h"
#include "mscl/MicroStrain/MIP/Commands/MipCommand.h"
#include "mscl/MicroStrain/MIP/MipModels.h"

namespace mscl
{

#ifndef SWIG 

    //Class: DeviceStatus
    //    Contains the logic for the Inertial DeviceStatus command.
    class DeviceStatus : public MipCommand
    {
    public:
        //Function: commandName
		//
        //Returns:
        //    std::string - the string name for this class.
        virtual std::string commandName() const { return "DeviceStatus"; }

        //Function: MakeGetCommand
        //
        //Parameters:
        //    model - model number of the current device
        //    statusSelector - response format (basic or diagnostic)
        //
        //Returns:
        //    DeviceStatus - object set up for getting the device status.
        static DeviceStatus MakeGetCommand(MipModels::NodeModel model, DeviceStatusData::StatusSelector statusSelector);

        //Function: MakeGetBasicCommand
        //
        //Parameters:
        //    model - model number of the current device
		//
        //Returns:
        //    DeviceStatus - object set up for getting a basic status.
        static DeviceStatus MakeGetBasicCommand(MipModels::NodeModel model);

        //Function: MakeGetDiagnosticCommand
        //
        //Parameters:
        //    model - model number of the current device
		//
        //Returns:
        //    DeviceStatus - object set up for getting a diagnostic status.
        static DeviceStatus MakeGetDiagnosticCommand(MipModels::NodeModel model);

        //Function: getResponseData
		//
        //Parameter:
        //    response - The <GenericMipCmdResponse> object from which to get formatted data.
		//
        //Returns:
        //    DeviceStatusData - An object with the data returned from the device.
        static DeviceStatusData getResponseData(const GenericMipCmdResponse& response);

        //Function: operator ByteStream
        //  Converts this class to a ByteStream.
        operator ByteStream() const;

    private:
        // Function: Constructor DeviceStatus
        //    Private constructor creates a DeviceStatus object.  Use Make___Command methods to create an object.
		DeviceStatus(MipModels::NodeModel model, DeviceStatusData::StatusSelector status_selector);

        //Function: commandType
		//
        //Returns:
        //    MipTypes::Command - the command ID.
        virtual MipTypes::Command commandType() const { return MipTypes::CMD_DEVICE_STATUS; }

        //Function: fieldDataByte
		//
        //Returns:
        //    uint8 - the byte ID for field data in the reply.
        virtual uint8 fieldDataByte() const { return 0x90; }

        //Function: responseExpected
		//
        //Returns:
        //    bool - True indicates that a response should return from the device.
        virtual bool responseExpected() const;

        //Variable: m_model
        //    The inertial <NodeModel> of the device.
        MipModels::NodeModel m_model;

        //Variable: m_statusSelector
        //    The <StatusSelector> to determine
        DeviceStatusData::StatusSelector m_statusSelector;

    public:
	// Destructor
        ~DeviceStatus() { }
    };

#endif
}
