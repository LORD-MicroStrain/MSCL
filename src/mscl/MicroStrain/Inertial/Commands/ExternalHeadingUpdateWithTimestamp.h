/*****************************************************************************************
**          Copyright(c) 2015-2026 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#pragma once

#include "mscl/MicroStrain/Inertial/ExposedInertialTypes.h"
#include "mscl/MicroStrain/MIP/Commands/MipCommand.h"

namespace mscl
{
#ifndef SWIG
    //Class: ExternalHeadingUpdateWithTimestamp
    //    Contains the logic for the Inertial ExternalHeadingUpdateWithTimestamp command.
    class ExternalHeadingUpdateWithTimestamp : public MipCommand
    {
    public:
        //Function: commandName
		//
        //Returns:
        //    std::string - the string name for this class.
        std::string commandName() const override { return "ExternalHeadingUpdateWithTimestamp"; }

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
        operator ByteStream() const override;

    private:
        //Function: Constructor ExternalHeadingUpdateWithTimestamp
        //    Private constructor creates a ExternalHeadingUpdateWithTimestamp object from a <HeadingData> and a <TimeUpdate>.
        ExternalHeadingUpdateWithTimestamp(const HeadingData& headingData, const TimeUpdate& timestamp);

        //Function: commandType
		//
        //Returns:
        //    MipTypes::Command - the command ID.
        MipTypes::Command commandType() const override { return MipTypes::CMD_EF_EXT_HEADING_UPDATE_TS; }

        //Function: fieldDataByte
		//
        //Returns:
        //    uint8 - the byte ID for field data in the reply.
        uint8 fieldDataByte() const override { return 0x00; }

        //Function: responseExpected
		//
        //Returns:
        //    bool - True indicates that a response should return from the device.
        bool responseExpected() const override;

        //Variable: m_data
        //    The <HeadingData> to send to the device.
        HeadingData m_headingData;

        //Variable: m_Timestamp
        //    The <TimeUpdate> timestamp to send to the device.
        TimeUpdate m_Timestamp;

    public:
	// Destructor
        ~ExternalHeadingUpdateWithTimestamp() {}
    };
#endif // !SWIG
} // namespace mscl
