#include "stdafx.h"
#include "VehicleDynamicsMode.h"
#include "mscl/MicroStrain/Inertial/InertialDataField.h"
#include "mscl/MicroStrain/Inertial/Packets/InertialPacketBuilder.h"
#include "mscl/MicroStrain/Inertial/InertialTypes.h"
#include "Inertial_Commands.h"

namespace mscl
{
    VehicleDynamicsMode::VehicleDynamicsMode(InertialTypes::FunctionSelector function_selector, const VehicleModeType& dataToUse) :
        m_functionSelector(function_selector),
        m_VehicleType(dataToUse)
    { }

    VehicleDynamicsMode::VehicleDynamicsMode(InertialTypes::FunctionSelector function_selector) :
        m_functionSelector(function_selector)
    {
        if (function_selector == InertialTypes::USE_NEW_SETTINGS)
            throw Error_NoData("Data must be passed in for a set command.");
    }

    VehicleDynamicsMode VehicleDynamicsMode::MakeSetCommand(const VehicleModeType& vehicleType)
    {
        return VehicleDynamicsMode(InertialTypes::USE_NEW_SETTINGS, vehicleType);
    }

    VehicleDynamicsMode VehicleDynamicsMode::MakeGetCommand()
    {
        VehicleModeType dataToUse;  // The data won't get used for a get command.
        return VehicleDynamicsMode(InertialTypes::READ_BACK_CURRENT_SETTINGS, dataToUse);
    }

    bool VehicleDynamicsMode::responseExpected() const
    {
        return (m_functionSelector == InertialTypes::READ_BACK_CURRENT_SETTINGS) ? true : false;
    }

    VehicleModeType VehicleDynamicsMode::getResponseData(const GenericInertialCommandResponse& response)
    {
        DataBuffer dataBuffer(response.data());
        VehicleModeType returnData;
        returnData = static_cast<VehicleModeType>(dataBuffer.read_uint8());

        return returnData;
    }

    VehicleDynamicsMode::operator ByteStream() const
    {
        ByteStream byteCommand;
        byteCommand.append_uint8(static_cast<uint8>(m_functionSelector));

        // Only fill in data if set command is being sent.
        if (m_functionSelector == InertialTypes::USE_NEW_SETTINGS)
        {
            byteCommand.append_uint8(static_cast<uint8>(m_VehicleType));
        }
        return GenericInertialCommand::buildCommand(commandType(), byteCommand.data());
    }

}