/*****************************************************************************************
**          Copyright(c) 2015-2022 Parker Hannifin Corp. All rights reserved.           **
**                                                                                      **
**    MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.    **
*****************************************************************************************/

#include "stdafx.h"
#include "VehicleDynamicsMode.h"
#include "mscl/MicroStrain/MIP/MipDataField.h"
#include "mscl/MicroStrain/MIP/Packets/MipPacketBuilder.h"
#include "mscl/MicroStrain/MIP/MipTypes.h"

namespace mscl
{
    VehicleDynamicsMode::VehicleDynamicsMode(MipTypes::FunctionSelector function_selector, const InertialTypes::VehicleModeType& dataToUse) :
        m_functionSelector(function_selector),
        m_VehicleType(dataToUse)
    { }

    VehicleDynamicsMode::VehicleDynamicsMode(MipTypes::FunctionSelector function_selector) :
        m_functionSelector(function_selector)
    {
        if (function_selector == MipTypes::USE_NEW_SETTINGS)
            throw Error_NoData("Data must be passed in for a set command.");
    }

    VehicleDynamicsMode VehicleDynamicsMode::MakeSetCommand(const InertialTypes::VehicleModeType& vehicleType)
    {
        return VehicleDynamicsMode(MipTypes::USE_NEW_SETTINGS, vehicleType);
    }

    VehicleDynamicsMode VehicleDynamicsMode::MakeGetCommand()
    {
        InertialTypes::VehicleModeType dataToUse;  // The data won't get used for a get command.
        return VehicleDynamicsMode(MipTypes::READ_BACK_CURRENT_SETTINGS, dataToUse);
    }

    bool VehicleDynamicsMode::responseExpected() const
    {
        return (m_functionSelector == MipTypes::READ_BACK_CURRENT_SETTINGS) ? true : false;
    }

    InertialTypes::VehicleModeType VehicleDynamicsMode::getResponseData(const GenericMipCmdResponse& response)
    {
        DataBuffer dataBuffer(response.data());
        InertialTypes::VehicleModeType returnData;
        returnData = static_cast<InertialTypes::VehicleModeType>(dataBuffer.read_uint8());

        return returnData;
    }

    VehicleDynamicsMode::operator ByteStream() const
    {
        ByteStream byteCommand;
        byteCommand.append_uint8(static_cast<uint8>(m_functionSelector));

        // Only fill in data if set command is being sent.
        if (m_functionSelector == MipTypes::USE_NEW_SETTINGS)
        {
            byteCommand.append_uint8(static_cast<uint8>(m_VehicleType));
        }
        return GenericMipCommand::buildCommand(commandType(), byteCommand.data());
    }

}