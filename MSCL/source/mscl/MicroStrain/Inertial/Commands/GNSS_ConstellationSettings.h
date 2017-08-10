/*******************************************************************************
Copyright(c) 2017 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "GenericInertialCommand.h"
#include "mscl/MicroStrain/Inertial/InertialReturnTypes.h"
#include "mscl/MicroStrain/Inertial/Commands/InertialCommand.h"

namespace mscl
{

#ifndef SWIG 

    //Class: GNSS_ConstellationSettings
    //    Contains the logic for the "GNSS Constellation Settings" command
    class GNSS_ConstellationSettings : public InertialCommand
    {
    public:
        //Function: commandType
        //
        //Returns:
        //    InertialTypes::Command - the command ID.
        virtual InertialTypes::Command commandType() const { return InertialTypes::CMD_GNSS_CONSTELLATION_SETTINGS; }

        //Function: fieldDataByte
        //
        //Returns:
        //    uint8 - the byte ID for field data in the reply.
        virtual uint8 fieldDataByte() const { return 0xA0; }

        //Function: commandName
        //
        //Returns:
        //    std::string - the string name for this class.
        virtual std::string commandName() const { return "GNSS_ConstellationSettings"; }

        //Function: responseExpected
        //
        //Returns:
        //    bool - True indicates that a response should return from the device.
        virtual bool responseExpected() const;

        //Function: MakeSetCommand
        //
        //Returns:
        //    bool - True indicates that a response should return from the device.
        static GNSS_ConstellationSettings MakeSetCommand(ConstellationSettingsData);

        //Function: MakeGetCommand
        //
        //Returns:
        //    bool - True indicates that a response should return from the device.
        static GNSS_ConstellationSettings MakeGetCommand();

        //Function: MakeResetToDefaultCommand
        //
        //Returns:
        //    bool - True indicates that a response should return from the device.
        static GNSS_ConstellationSettings MakeResetToDefaultCommand();

        //Function: getResponseData
        //
        //Returns:
        //    ConstellationSettingsData - An object iwth the data returned from the device.
        static ConstellationSettingsData getResponseData(const GenericInertialCommandResponse& response);

        //Function: operator ByteStream
        //  Converts this class to a ByteStream.
        operator ByteStream() const;

    private:
	// Private Constructors.  Use static accessor classes to create an object.
        GNSS_ConstellationSettings(InertialTypes::FunctionSelector function_selector, ConstellationSettingsData dataToUse);
        GNSS_ConstellationSettings(InertialTypes::FunctionSelector function_selector);

        //Variable: m_data
        //    The <ConstellationSettingsData> to send to the device.
        //Variable: m_functionSelector
        //    The <InertialTypes::FunctionSelector> type of command to send, get/set, reset to factory defaults, et al.
        ConstellationSettingsData m_data;
        InertialTypes::FunctionSelector m_functionSelector;

    public:
	// Destructor
        ~GNSS_ConstellationSettings() { }
    };

#endif
}
