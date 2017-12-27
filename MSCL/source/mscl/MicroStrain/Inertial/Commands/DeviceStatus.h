/*******************************************************************************
Copyright(c) 2017 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "GenericInertialCommand.h"
#include "mscl/MicroStrain/ResponseCollector.h"
#include "mscl/MicroStrain/Inertial/ExposedInertialTypes.h"
#include "mscl/MicroStrain/Inertial/Commands/InertialCommand.h"

namespace mscl
{

#ifndef SWIG 

    //Class: DeviceStatus
    //    Contains the logic for the Inertial DeviceStatus command.
    class DeviceStatus : public InertialCommand
    {
    public:
        //Function: commandName
		//
        //Returns:
        //    std::string - the string name for this class.
        virtual std::string commandName() const { return "DeviceStatus"; }

        //Function: MakeBasicStatusCommand
		//
        //Returns:
        //    DeviceStatus - object set up for getting a basic status.
        static DeviceStatus MakeBasicStatusCommand();

        //Function: MakeDiagnosticStatusCommand
		//
        //Returns:
        //    DeviceStatus - object set up for getting a diagnostic status.
        static DeviceStatus MakeDiagnosticStatusCommand();

        //Function: getResponseData
		//
        //Parameter:
        //    response - The <GenericInertialCommandResponse> object from which to get formatted data.
		//
        //Returns:
        //    ConstellationSettingsData - An object with the data returned from the device.
        static DeviceStatusData getResponseData(const GenericInertialCommandResponse& response);

        //Function: operator ByteStream
        //  Converts this class to a ByteStream.
        operator ByteStream() const;

    private:
        // Function: Constructor DeviceStatus
        //    Private constructor creates a DeviceStatus object.  Use Make___Command methods to create an object.
		DeviceStatus(InertialTypes::StatusSelector status_selector);

        //Function: commandType
		//
        //Returns:
        //    InertialTypes::Command - the command ID.
        virtual InertialTypes::Command commandType() const { return InertialTypes::CMD_DEVICE_STATUS; }

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

        //Variable: m_data
        //    The DeviceStatusData to send to the device.
        DeviceStatusData m_data;

        //Variable: m_StatusSelector
        //    The StatusSelector type of command to send, get/set, reset to factory defaults, et al.
        InertialTypes::StatusSelector m_StatusSelector;

    public:
	// Destructor
        ~DeviceStatus() { }
    };

#endif
}
