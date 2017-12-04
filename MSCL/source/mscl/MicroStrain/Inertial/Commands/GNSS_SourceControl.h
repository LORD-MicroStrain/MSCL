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

    //Class: GNSS_SourceControl
    //    Contains the logic for the Inertial GNSS_SourceControl command.
    class GNSS_SourceControl : public InertialCommand
    {
    public:
        //Function: commandName
		//
        //Returns:
        //    std::string - the string name for this class.
        virtual std::string commandName() const { return "GNSS_SourceControl"; }

        //Function: MakeSetCommand
		//
        //Parameter: dataToUse
		//    The <GNSS_Source> object to set.
		//
        //Returns:
        //    GNSS_SourceControl - object set up for sending a set command.
        static GNSS_SourceControl MakeSetCommand(const GNSS_Source& dataToUse);

        //Function: MakeGetCommand
		//
        //Returns:
        //    GNSS_SourceControl - object set up for sending a get command.
        static GNSS_SourceControl MakeGetCommand();

        //Function: getResponseData
		//
        //Parameter:
        //    response - The <GenericInertialCommandResponse> object from which to get formatted data.
		//
        //Returns:
        //    ConstellationSettingsData - An object with the data returned from the device.
        static GNSS_Source getResponseData(const GenericInertialCommandResponse& response);

        //Function: operator ByteStream
        //  Converts this class to a ByteStream.
        operator ByteStream() const;

    private:
        // Function: Constructor GNSS_SourceControl
        //    Private constructor creates a GNSS_SourceControl object.  Use Make___Command methods to create an object.
        GNSS_SourceControl(InertialTypes::FunctionSelector function_selector, const GNSS_Source& gnssSource);
		GNSS_SourceControl(InertialTypes::FunctionSelector function_selector);

        //Function: commandType
		//
        //Returns:
        //    InertialTypes::Command - the command ID.
        virtual InertialTypes::Command commandType() const { return InertialTypes::CMD_EF_GNSS_SRC_CTRL; }

        //Function: fieldDataByte
		//
        //Returns:
        //    uint8 - the byte ID for field data in the reply.
        virtual uint8 fieldDataByte() const { return 0x86; }

        //Function: responseExpected
		//
        //Returns:
        //    bool - True indicates that a response should return from the device.
        virtual bool responseExpected() const;

        //Variable: m_gnssSource
        //    The GNSS_Source to send to the device.
        GNSS_Source m_gnssSource;

        //Variable: m_functionSelector
        //    The FunctionSelector type of command to send, get/set, reset to factory defaults, et al.
        InertialTypes::FunctionSelector m_functionSelector;

    public:
	// Destructor
        ~GNSS_SourceControl() { }
    };

#endif
}
