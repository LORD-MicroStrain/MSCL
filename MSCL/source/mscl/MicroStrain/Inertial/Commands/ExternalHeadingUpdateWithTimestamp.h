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

    //Class: ExternalHeadingUpdateWithTimestamp
    //    Contains the logic for the Inertial ExternalHeadingUpdateWithTimestamp command.
    class ExternalHeadingUpdateWithTimestamp : public InertialCommand
    {
    public:
        //Function: commandName
		//
        //Returns:
        //    std::string - the string name for this class.
        virtual std::string commandName() const { return "ExternalHeadingUpdateWithTimestamp"; }

        //Function: MakeCommand
		//
        //Parameters:
        //headingData - The <HeadingData> object to set.
        //timestamp - The <TimeUpdate> object to set.
        //
        //Returns:
        //    ExternalHeadingUpdateWithTimestamp - object set up for sending a set command.
        static ExternalHeadingUpdateWithTimestamp MakeCommand(const HeadingData& headingData, const TimeUpdate& timestamp);

        //Function: operator ByteStream
        //  Converts this class to a ByteStream.
        operator ByteStream() const;

    private:
        //Function: Constructor ExternalHeadingUpdateWithTimestamp
        //    Private constructor creates a ExternalHeadingUpdateWithTimestamp object from a <HeadingData> and a <TimeUpdate>.
        ExternalHeadingUpdateWithTimestamp(const HeadingData& headingData, const TimeUpdate& timestamp);

        //Function: commandType
		//
        //Returns:
        //    InertialTypes::Command - the command ID.
        virtual InertialTypes::Command commandType() const { return InertialTypes::CMD_EF_EXT_HEADING_UPDATE_TS; }

        //Function: fieldDataByte
		//
        //Returns:
        //    uint8 - the byte ID for field data in the reply.
        virtual uint8 fieldDataByte() const { return 0x00; }

        //Function: responseExpected
		//
        //Returns:
        //    bool - True indicates that a response should return from the device.
        virtual bool responseExpected() const;

        //Variable: m_data
        //    The <HeadingData> to send to the device.
        HeadingData m_headingData;

        //Variable: m_Timestamp
        //    The <TimeUpdate> timestamp to send to the device.
        TimeUpdate m_Timestamp;

    public:
	// Destructor
        ~ExternalHeadingUpdateWithTimestamp() { }
    };

#endif
}
