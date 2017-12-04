#include "stdafx.h"
#include "UARTBaudRate.h"
#include "mscl/MicroStrain/Inertial/InertialDataField.h"
#include "mscl/MicroStrain/Inertial/Packets/InertialPacketBuilder.h"
#include "mscl/MicroStrain/Inertial/InertialTypes.h"
#include "Inertial_Commands.h"

namespace mscl
{
    UARTBaudRate::UARTBaudRate(InertialTypes::FunctionSelector function_selector, uint32 dataToUse) :
        m_functionSelector(function_selector),
        m_baudRate(dataToUse)
    { }

    UARTBaudRate::UARTBaudRate(InertialTypes::FunctionSelector function_selector) :
        m_functionSelector(function_selector)
    {
        if (function_selector == InertialTypes::USE_NEW_SETTINGS)
            throw Error_NoData("Data must be passed in for a set command.");
    }

    UARTBaudRate UARTBaudRate::MakeSetCommand(uint32 dataToUse)
    {
        return UARTBaudRate(InertialTypes::USE_NEW_SETTINGS, dataToUse);
    }

    UARTBaudRate UARTBaudRate::MakeGetCommand()
    {
        return UARTBaudRate(InertialTypes::READ_BACK_CURRENT_SETTINGS, 0);
    }

    bool UARTBaudRate::responseExpected() const
    {
        return (m_functionSelector == InertialTypes::READ_BACK_CURRENT_SETTINGS) ? true : false;
    }

    uint32 UARTBaudRate::getResponseData(const GenericInertialCommandResponse& response)
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
        if (m_functionSelector == InertialTypes::USE_NEW_SETTINGS)
        {
            byteCommand.append_uint32(m_baudRate);
        }
        return GenericInertialCommand::buildCommand(commandType(), byteCommand.data()); ;
    }

}