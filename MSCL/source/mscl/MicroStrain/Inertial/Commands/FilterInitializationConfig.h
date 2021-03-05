/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "mscl/MicroStrain/ResponseCollector.h"
#include "mscl/MicroStrain/Inertial/ExposedInertialTypes.h"
#include "mscl/MicroStrain/MIP/Commands/MipCommand.h"

namespace mscl
{
#ifndef SWIG
    //Class: FilterInitializationConfig
    //    A generic command class that contains the logic for the Filter Initialization Config command (0x0D, 0x52).
    class FilterInitializationConfig : public MipCommand
    {
    public:
        //Function: commandName
        //
        //Returns:
        //    std::string - the string name for the command.
        virtual std::string commandName() const;

        //Function: MakeSetCommand
        //
        //Parameter: cmd
        //    The specific <MipTypes::Command> type to be constructed
        //
        //Parameter: data
        //    The <FilterInitializationValues> to set.
        //
        //Returns:
        //    FilterInitializationConfig - object set up for sending a set command.
        static FilterInitializationConfig MakeSetCommand(const FilterInitializationValues& data);

        //Function: MakeGetCommand
        //
        //Parameter: cmd
        //    The specific <MipTypes::Command> type to be constructed
        //
        //Returns:
        //    FilterInitializationConfig - object set up for sending a get command.
        static FilterInitializationConfig MakeGetCommand();

        //Function: getResponseData
        //
        //Parameter:
        //    response - The <GenericMipCmdResponse> object from which to get formatted data.
        //
        //Returns:
        //    FilterInitializationValues - A <FilterInitializationValues> object with the initialization config returned from the device.
        FilterInitializationValues getResponseData(const GenericMipCmdResponse& response);

        //Function: operator ByteStream
        //  Converts this class to a ByteStream.
        operator ByteStream() const;

    private:
        // Function: Constructor FilterInitializationConfig
        //    Private constructor creates a FilterInitializationConfig object.  Use Make___Command methods to create an object.
        FilterInitializationConfig(MipTypes::FunctionSelector function_selector, const FilterInitializationValues& dataToUse);
        FilterInitializationConfig(MipTypes::FunctionSelector function_selector);

        //Function: commandType
        //
        //Returns:
        //    MipTypes::Command - the command ID.
        virtual MipTypes::Command commandType() const { return MipTypes::Command::CMD_EF_INITIALIZATION_CONFIG; }

        //Function: fieldDataByte
        //
        //Returns:
        //    uint8 - the byte ID for field data in the reply.
        virtual uint8 fieldDataByte() const { return 0xD2; };

        //Function: responseExpected
        //
        //Returns:
        //    bool - True indicates that a response should return from the device.
        virtual bool responseExpected() const;

        //Variable: m_functionSelector
        //    The FunctionSelector type of command to send, get/set, reset to factory defaults, et al.
        MipTypes::FunctionSelector m_functionSelector;

        //Variable: m_data
        //    The <FilterInitializationValues> to send to the device.
        FilterInitializationValues m_data;

    public:
        // Destructor
        ~FilterInitializationConfig() { }
    };
#endif
}