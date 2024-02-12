/*****************************************************************************************
**          Copyright(c) 2015-2024 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.    **
*****************************************************************************************/

#include "stdafx.h"
#include "GyroBias.h"
#include "mscl/MicroStrain/MIP/MipDataField.h"
#include "mscl/MicroStrain/MIP/Packets/MipPacketBuilder.h"
#include "mscl/MicroStrain/MIP/MipTypes.h"
#include "mscl/MicroStrain/MIP/Commands/MIP_Commands.h"

namespace mscl
{
    GyroBias::GyroBias(MipTypes::FunctionSelector function_selector, GeometricVector gyroBiasVector) :
        m_functionSelector(function_selector),
        m_gyroBiasVector(gyroBiasVector)
    { }

    GyroBias::GyroBias(MipTypes::FunctionSelector function_selector) :
        m_functionSelector(function_selector)
    {
        if (function_selector == MipTypes::USE_NEW_SETTINGS)
            throw Error_NoData("Data must be passed in for a set command.");
    }

    GyroBias GyroBias::MakeSetCommand(GeometricVector offsetVector)
    {
        return GyroBias(MipTypes::USE_NEW_SETTINGS, offsetVector);
    }

    GyroBias GyroBias::MakeGetCommand()
    {
        GeometricVector dataToUse;  // The data won't get used for a get command.
        return GyroBias(MipTypes::READ_BACK_CURRENT_SETTINGS, dataToUse);
    }

    bool GyroBias::responseExpected() const
    {
        return (m_functionSelector == MipTypes::READ_BACK_CURRENT_SETTINGS) ? true : false;
    }

    GeometricVector GyroBias::getResponseData(const GenericMipCmdResponse& response)
    {
        DataBuffer dataBuffer(response.data());
        GeometricVector returnData;
        returnData.x(dataBuffer.read_float());
        returnData.y(dataBuffer.read_float());
        returnData.z(dataBuffer.read_float());
        return returnData;
    }

    GyroBias::operator ByteStream() const
    {
        ByteStream byteCommand;
        byteCommand.append_uint8(static_cast<uint8>(m_functionSelector));

        // Only fill in data if set command is being sent.
        if (m_functionSelector == MipTypes::USE_NEW_SETTINGS)
        {    // Put in X, Y, and Z values of vector.
            byteCommand.append_float(m_gyroBiasVector.x());
            byteCommand.append_float(m_gyroBiasVector.y());
            byteCommand.append_float(m_gyroBiasVector.z());
        }
        return GenericMipCommand::buildCommand(commandType(), byteCommand.data()); ;
    }

}