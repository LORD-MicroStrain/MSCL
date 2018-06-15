/*******************************************************************************
Copyright(c) 2015-2018 LORD Corporation. All rights reserved.

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

    //Class: UARTBaudRate
    //    Contains the logic for the Inertial UARTBaudRate command.
    class UARTBaudRate : public MipCommand
    {
    public:
        //Function: commandName
        //
        //Returns:
        //    std::string - the string name for this class.
        virtual std::string commandName() const { return "UARTBaudRate"; }

        //Function: MakeSetCommand
        //
        //Parameter: dataToUse
        //    The <uint32> object to set.
        //
        //Returns:
        //    UARTBaudRate - object set up for sending a set command.
        static UARTBaudRate MakeSetCommand(uint32 dataToUse);

        //Function: MakeGetCommand
        //
        //Returns:
        //    UARTBaudRate - object set up for sending a get command.
        static UARTBaudRate MakeGetCommand();

        //Function: getResponseData
        //
        //Parameter:
        //    response - The <GenericMipCmdResponse> object from which to get formatted data.
        //
        //Returns:
        //    ConstellationSettingsData - An object with the data returned from the device.
        static uint32 getResponseData(const GenericMipCmdResponse& response);

        //Function: operator ByteStream
        //  Converts this class to a ByteStream.
        operator ByteStream() const;

    private:
        // Function: Constructor UARTBaudRate
        //    Private constructor creates a UARTBaudRate object.  Use Make___Command methods to create an object.
        UARTBaudRate(MipTypes::FunctionSelector function_selector, uint32 dataToUse);
        UARTBaudRate(MipTypes::FunctionSelector function_selector);

        //Function: commandType
        //
        //Returns:
        //    MipTypes::Command - the command ID.
        virtual MipTypes::Command commandType() const { return MipTypes::CMD_UART_BAUD_RATE; }

        //Function: fieldDataByte
        //
        //Returns:
        //    uint8 - the byte ID for field data in the reply.
        virtual uint8 fieldDataByte() const { return 0x87; }

        //Function: responseExpected
        //
        //Returns:
        //    bool - True indicates that a response should return from the device.
        virtual bool responseExpected() const;

        //Variable: m_functionSelector
        //    The FunctionSelector type of command to send, get/set, reset to factory defaults, et al.
        MipTypes::FunctionSelector m_functionSelector;

        //Variable: m_baudRate
        //    The uint32 to send to the device.
        uint32 m_baudRate;

    public:
        // Destructor
        ~UARTBaudRate() { }
    };

#endif
}
