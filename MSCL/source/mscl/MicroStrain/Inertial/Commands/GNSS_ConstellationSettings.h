/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "mscl/MicroStrain/MIP/Commands/GenericMipCommand.h"
#include "mscl/MicroStrain/Inertial/ExposedInertialTypes.h"
#include "mscl/MicroStrain/MIP/Commands/MipCommand.h"

namespace mscl
{

#ifndef SWIG 

    //Class: GNSS_ConstellationSettings
    //    Contains the logic for the "GNSS Constellation Settings" command
    class GNSS_ConstellationSettings : public MipCommand
    {
    public:
        //Function: commandType
        //
        //Returns:
        //    MipTypes::Command - the command ID.
        virtual MipTypes::Command commandType() const { return MipTypes::CMD_GNSS_CONSTELLATION_SETTINGS; }

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
        //    GNSS_ConstellationSettings - object set up to send a set command.
        static GNSS_ConstellationSettings MakeSetCommand(ConstellationSettingsData);

        //Function: MakeGetCommand
        //
        //Returns:
        //    GNSS_ConstellationSettings - object set up to send a get command.
        static GNSS_ConstellationSettings MakeGetCommand();

        //Function: MakeResetToDefaultCommand
        //
        //Returns:
        //    bool - True indicates that a response should return from the device.
        static GNSS_ConstellationSettings MakeResetToDefaultCommand();

        //Function: getResponseData
        //
        //Returns:
        //    ConstellationSettingsData - An object with the data returned from the device.
        static ConstellationSettingsData getResponseData(const GenericMipCmdResponse& response);

        //Function: operator ByteStream
        //  Converts this class to a ByteStream.
        operator ByteStream() const;

    private:
        // Private Constructors.  Use static accessor classes to create an object.
        GNSS_ConstellationSettings(MipTypes::FunctionSelector function_selector, ConstellationSettingsData dataToUse);
        GNSS_ConstellationSettings(MipTypes::FunctionSelector function_selector);

        //Variable: m_functionSelector
        //    The <MipTypes::FunctionSelector> type of command to send, get/set, reset to factory defaults, et al.
        MipTypes::FunctionSelector m_functionSelector;

        //Variable: m_data
        //    The <ConstellationSettingsData> to send to the device.
        ConstellationSettingsData m_data;

    public:
        // Destructor
        ~GNSS_ConstellationSettings() { }
    };

#endif
}
