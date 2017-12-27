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

    //Class: ComplementaryFilterSettings
    //    Contains the logic for the Inertial ComplementaryFilterSettings command.
    class ComplementaryFilterSettings : public InertialCommand
    {
    public:
        //Function: commandName
		//
        //Returns:
        //    std::string - the string name for this class.
        virtual std::string commandName() const { return "ComplementaryFilterSettings"; }

        //Function: MakeSetCommand
		//
        //Parameter: dataToUse
		//    The <ComplementaryFilterSettingsData> object to set.
		//
        //Returns:
        //    ComplementaryFilterSettings - object set up for sending a set command.
        static ComplementaryFilterSettings MakeSetCommand(const ComplementaryFilterData& dataToUse);

        //Function: MakeGetCommand
		//
        //Returns:
        //    ComplementaryFilterSettings - object set up for sending a get command.
        static ComplementaryFilterSettings MakeGetCommand();

        //Function: getResponseData
		//
        //Parameter:
        //    response - The <GenericInertialCommandResponse> object from which to get formatted data.
		//
        //Returns:
        //    ConstellationSettingsData - An object with the data returned from the device.
        static ComplementaryFilterData getResponseData(const GenericInertialCommandResponse& response);

        //Function: operator ByteStream
        //  Converts this class to a ByteStream.
        operator ByteStream() const;

    private:
        // Function: Constructor ComplementaryFilterSettings
        //    Private constructor creates a ComplementaryFilterSettings object.  Use Make___Command methods to create an object.
        ComplementaryFilterSettings(InertialTypes::FunctionSelector function_selector, ComplementaryFilterData dataToUse);
		ComplementaryFilterSettings(InertialTypes::FunctionSelector function_selector);

        //Function: commandType
		//
        //Returns:
        //    InertialTypes::Command - the command ID.
        virtual InertialTypes::Command commandType() const { return InertialTypes::CMD_COMPLEMENTARY_FILTER_SETTINGS; }

        //Function: fieldDataByte
		//
        //Returns:
        //    uint8 - the byte ID for field data in the reply.
        virtual uint8 fieldDataByte() const { return 0x97; }

        //Function: responseExpected
		//
        //Returns:
        //    bool - True indicates that a response should return from the device.
        virtual bool responseExpected() const;

        //Variable: m_data
        //    The ComplementaryFilterSettingsData to send to the device.
        ComplementaryFilterData m_data;

        //Variable: m_functionSelector
        //    The FunctionSelector type of command to send, get/set, reset to factory defaults, et al.
        InertialTypes::FunctionSelector m_functionSelector;

    public:
	// Destructor
        ~ComplementaryFilterSettings() { }
    };

#endif
}
