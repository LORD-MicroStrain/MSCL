/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#pragma once

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
        std::string commandName() const override { return "UARTBaudRate"; }

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
        //    uint32 - The baud rate value returned from the device.
        static uint32 getResponseData(const GenericMipCmdResponse& response);

        //Function: peekParameterValue
        //  Read the baud rate parameter value from the provided UART Baud Rate command bytes.
        //  Note: The provided command bytes are assumed to be formatted properly, no validation occurs.
        //
        //Parameter:
        //    commandBytes - The <Bytes> representing a complete UART Baud Rate command
        //
        //Returns:
        //    uint32 - the baud rate parameter value within the commandBytes object, returns 0 if parameter value is beyond the bounds of commandBytes
        static uint32 peekParameterValue(const Bytes& commandBytes);

        //Function: operator ByteStream
        //  Converts this class to a ByteStream.
        operator ByteStream() const override;

    private:
        // Function: Constructor UARTBaudRate
        //    Private constructor creates a UARTBaudRate object.  Use Make___Command methods to create an object.
        UARTBaudRate(MipTypes::FunctionSelector function_selector, uint32 dataToUse);
        UARTBaudRate(MipTypes::FunctionSelector function_selector);

        //Function: commandType
        //
        //Returns:
        //    MipTypes::Command - the command ID.
        MipTypes::Command commandType() const override { return MipTypes::CMD_UART_BAUD_RATE; }

        //Function: fieldDataByte
        //
        //Returns:
        //    uint8 - the byte ID for field data in the reply.
        uint8 fieldDataByte() const override { return 0x87; }

        //Function: responseExpected
        //
        //Returns:
        //    bool - True indicates that a response should return from the device.
        bool responseExpected() const override;

        //Variable: m_functionSelector
        //    The FunctionSelector type of command to send, get/set, reset to factory defaults, et al.
        MipTypes::FunctionSelector m_functionSelector;

        //Variable: m_baudRate
        //    The uint32 to send to the device.
        uint32 m_baudRate;

    public:
        // Destructor
        ~UARTBaudRate() {}
    };
#endif // !SWIG
} // namespace mscl
