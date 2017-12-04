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

    //Class: ConingAndScullingEnable
    //    Contains the logic for the Inertial ConingAndScullingEnable command.
    class ConingAndScullingEnable : public InertialCommand
    {
    public:
        //Function: commandName
		//
        //Returns:
        //    std::string - the string name for this class.
        virtual std::string commandName() const { return "ConingAndScullingEnable"; }

        //Function: MakeSetCommand
		//
        //Parameter: dataToUse
		//    The <ConingAndScullingEnableData> object to set.
		//
        //Returns:
        //    ConingAndScullingEnable - object set up for sending a set command.
        static ConingAndScullingEnable MakeSetCommand(bool enable);

        //Function: MakeGetCommand
		//
        //Returns:
        //    ConingAndScullingEnable - object set up for sending a get command.
        static ConingAndScullingEnable MakeGetCommand();

        //Function: getResponseData
		//
        //Parameter:
        //    response - The <GenericInertialCommandResponse> object from which to get formatted data.
		//
        //Returns:
        //    ConstellationSettingsData - An object with the data returned from the device.
        static bool getResponseData(const GenericInertialCommandResponse& response);

        //Function: operator ByteStream
        //  Converts this class to a ByteStream.
        operator ByteStream() const;

    private:
        // Function: Constructor ConingAndScullingEnable
        //    Private constructor creates a ConingAndScullingEnable object.  Use Make___Command methods to create an object.
        ConingAndScullingEnable(InertialTypes::FunctionSelector function_selector, bool enable);
		ConingAndScullingEnable(InertialTypes::FunctionSelector function_selector);

        //Function: commandType
		//
        //Returns:
        //    InertialTypes::Command - the command ID.
        virtual InertialTypes::Command commandType() const { return InertialTypes::CMD_CONING_SCULLING; }

        //Function: fieldDataByte
		//
        //Returns:
        //    uint8 - the byte ID for field data in the reply.
        virtual uint8 fieldDataByte() const { return 0x9E; }

        //Function: responseExpected
		//
        //Returns:
        //    bool - True indicates that a response should return from the device.
        virtual bool responseExpected() const;

        //Variable: m_data
        //    The ConingAndScullingEnableData to send to the device.
        bool m_enabled;

        //Variable: m_functionSelector
        //    The FunctionSelector type of command to send, get/set, reset to factory defaults, et al.
        InertialTypes::FunctionSelector m_functionSelector;

    public:
	// Destructor
        ~ConingAndScullingEnable() { }
    };

#endif
}
