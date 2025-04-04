/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#pragma once

#include "mscl/MicroStrain/Inertial/ExposedInertialTypes.h"
#include "mscl/MicroStrain/MIP/Commands/MipCommand.h"

namespace mscl
{
#ifndef SWIG
    //Class: ExternalGNSSUpdate
    //    Contains the logic for the Inertial ExternalGNSSUpdate command.
    class ExternalGNSSUpdate : public MipCommand
    {
    public:
        //Function: commandName
		//
        //Returns:
        //    std::string - the string name for this class.
        std::string commandName() const override { return "ExternalGNSSUpdate"; }

        //Function: MakeSetCommand
		//
        //Parameter: dataToUse
		//    The <ExternalGNSSUpdateData> object to set.
		//
        //Returns:
        //    ExternalGNSSUpdate - object set up for sending a set command.
        static ExternalGNSSUpdate MakeCommand(const ExternalGNSSUpdateData& dataToUse);

        //Function: operator ByteStream
        //  Converts this class to a ByteStream.
        operator ByteStream() const override;

    private:
        // Function: Constructor ExternalGNSSUpdate
        //    Private constructor creates an ExternalGNSSUpdate object. Use Make___Command methods to create an object.
        ExternalGNSSUpdate(const ExternalGNSSUpdateData& dataToUse);

        //Function: commandType
		//
        //Returns:
        //    MipTypes::Command - the command ID.
        MipTypes::Command commandType() const override { return MipTypes::CMD_EF_EXTERN_GNSS_UPDATE; }

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
        //    The ExternalGNSSUpdateData to send to the device.
        ExternalGNSSUpdateData m_data;

    public:
	// Destructor
        ~ExternalGNSSUpdate() {}
    };
#endif // !SWIG
} // namespace mscl
