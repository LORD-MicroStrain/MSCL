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

    class SBASSettings : public MipCommand
    {
    public:
        //Function: commandType
        //
        //Returns:
        //    MipTypes::Command - the command ID.
        virtual MipTypes::Command commandType() const { return MipTypes::CMD_GNSS_SBAS_SETTINGS; }

        //Function: fieldDataByte
        //
        //Returns:
        //    uint8 - the byte ID for field data in the reply.
        virtual uint8 fieldDataByte() const { return 0xA1; }

        //Function: commandName
        //
        //Returns:
        //    std::string - the string name for this class.
        virtual std::string commandName() const { return "SBASSettings"; }

        //Function: responseExpected
        //
        //Returns:
        //    bool - True indicates that a response should return from the device.
        virtual bool responseExpected() const;

        //Function: MakeSetCommand
        //
        //Returns:
        //    bool - True indicates that a response should return from the device.
        static SBASSettings MakeSetCommand(SBASSettingsData);

        //Function: MakeGetCommand
        //
        //Returns:
        //    bool - True indicates that a response should return from the device.
        static SBASSettings MakeGetCommand();

        //Function: getResponseData
        //
        //Returns:
        //    ConstellationSettingsData - An object with the data returned from the device.
        static SBASSettingsData getResponseData(const GenericMipCmdResponse& response);

        //Function: operator ByteStream
        //  Converts this class to a ByteStream.
        operator ByteStream() const;

    private:
        //Constructor: SBASSettings
        SBASSettings(MipTypes::FunctionSelector function_selector, SBASSettingsData dataToUse) :
            m_functionSelector(function_selector),
            m_data(dataToUse)
        { }

        //Variable: m_functionSelector
        //  The MipTypes::FunctionSelector type of command to send, get/set, reset to factory defaults, et al.
        MipTypes::FunctionSelector m_functionSelector;

        //Variable: m_data
        //  The ConstellationSettingsData to send to the device.
        SBASSettingsData m_data;

    public:
        //  Destructor
        ~SBASSettings() { }
    };

#endif
}
