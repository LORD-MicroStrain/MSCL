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
    //Class: ExternalHeadingUpdate
    //    Contains the logic for the Inertial ExternalHeadingUpdate command.
    class ExternalHeadingUpdate : public MipCommand
    {
    public:
        //Function: commandName
		//
        //Returns:
        //    std::string - the string name for this class.
        std::string commandName() const override { return "ExternalHeadingUpdate"; }

        //Function: MakeCommand
		//
        //Parameter: headingData
		//    The <HeadingData> object to set.
		//
        //Returns:
        //    ExternalHeadingUpdate - object set up for sending a set command.
        static ExternalHeadingUpdate MakeCommand(const HeadingData& headingData);

        //Function: operator ByteStream
        //  Converts this class to a ByteStream.
        operator ByteStream() const override;

    private:
        // Function: Constructor ExternalHeadingUpdate
        //    Private constructor creates a ExternalHeadingUpdate object.  Use Make___Command methods to create an object.
        ExternalHeadingUpdate(const HeadingData& headingData);

        //Function: commandType
		//
        //Returns:
        //    MipTypes::Command - the command ID.
        MipTypes::Command commandType() const override { return MipTypes::CMD_EF_EXTERN_HEADING_UPDATE; }

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

    public:
	// Destructor
        ~ExternalHeadingUpdate() {}
    };
#endif // !SWIG
} // namespace mscl
