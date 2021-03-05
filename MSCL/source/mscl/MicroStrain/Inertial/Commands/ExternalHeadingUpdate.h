/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "mscl/MicroStrain/MIP/Commands/GenericMipCommand.h"
#include "mscl/MicroStrain/ResponseCollector.h"
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
        virtual std::string commandName() const { return "ExternalHeadingUpdate"; }

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
        operator ByteStream() const;

    private:
        // Function: Constructor ExternalHeadingUpdate
        //    Private constructor creates a ExternalHeadingUpdate object.  Use Make___Command methods to create an object.
        ExternalHeadingUpdate(const HeadingData& headingData);

        //Function: commandType
		//
        //Returns:
        //    MipTypes::Command - the command ID.
        virtual MipTypes::Command commandType() const { return MipTypes::CMD_EF_EXTERN_HEADING_UPDATE; }

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

    public:
	// Destructor
        ~ExternalHeadingUpdate() { }
    };

#endif
}
