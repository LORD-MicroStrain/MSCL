#include "stdafx.h"
#include "UARTBaudRate.h"
#include "mscl/MicroStrain/MIP/MipDataField.h"
#include "mscl/MicroStrain/MIP/Packets/MipPacketBuilder.h"
#include "mscl/MicroStrain/MIP/MipTypes.h"

namespace mscl
{
    UARTBaudRate::UARTBaudRate(MipTypes::FunctionSelector function_selector, uint32 dataToUse) :
        m_functionSelector(function_selector),
        m_baudRate(dataToUse)
    { }

    UARTBaudRate::UARTBaudRate(MipTypes::FunctionSelector function_selector) :
        m_functionSelector(function_selector)
    {
        if (function_selector == MipTypes::USE_NEW_SETTINGS)
            throw Error_NoData("Data must be passed in for a set command.");
    }

    UARTBaudRate UARTBaudRate::MakeSetCommand(uint32 dataToUse)
    {
        return UARTBaudRate(MipTypes::USE_NEW_SETTINGS, dataToUse);
    }

    UARTBaudRate UARTBaudRate::MakeGetCommand()
    {
        return UARTBaudRate(MipTypes::READ_BACK_CURRENT_SETTINGS, 0);
    }

    bool UARTBaudRate::responseExpected() const
    {
        return (m_functionSelector == MipTypes::READ_BACK_CURRENT_SETTINGS) ? true : false;
    }

    uint32 UARTBaudRate::getResponseData(const GenericMipCmdResponse& response)
    {
        DataBuffer dataBuffer(response.data());
        uint32 returnData = dataBuffer.read_uint32();

        return returnData;
    }

    UARTBaudRate::operator ByteStream() const
    {
        ByteStream byteCommand;
        byteCommand.append_uint8(static_cast<uint8>(m_functionSelector));

        // Only fill in data if set command is being sent.
        if (m_functionSelector == MipTypes::USE_NEW_SETTINGS)
        {
            byteCommand.append_uint32(m_baudRate);
        }
        return GenericMipCommand::buildCommand(commandType(), byteCommand.data()); ;
    }

}