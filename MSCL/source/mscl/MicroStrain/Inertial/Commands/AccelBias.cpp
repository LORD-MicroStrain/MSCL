/*****************************************************************************************
**          Copyright(c) 2015-2024 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "stdafx.h"
#include "AccelBias.h"
#include "mscl/MicroStrain/MIP/MipDataField.h"
#include "mscl/MicroStrain/MIP/Packets/MipPacketBuilder.h"
#include "mscl/MicroStrain/MIP/MipTypes.h"

namespace mscl
{
    AccelBias::AccelBias(MipTypes::FunctionSelector functionSelector, const GeometricVector& accelerometerBiasVector) :
        m_functionSelector(functionSelector),
        m_accelerometerBiasVector(accelerometerBiasVector)
    { }

    AccelBias::AccelBias(MipTypes::FunctionSelector functionSelector) :
        m_functionSelector(functionSelector)
    {
        if (functionSelector == MipTypes::USE_NEW_SETTINGS)
            throw Error_NoData("Data must be passed in for a set command.");
    }

    AccelBias AccelBias::MakeSetCommand(const GeometricVector& vectorToSet)
    {
        return AccelBias(MipTypes::USE_NEW_SETTINGS, vectorToSet);
    }

    AccelBias AccelBias::MakeGetCommand()
    {
        GeometricVector dataToUse;  // The data won't get used for a get command.
        return AccelBias(MipTypes::READ_BACK_CURRENT_SETTINGS, dataToUse);
    }

    bool AccelBias::responseExpected() const
    {
        return (m_functionSelector == MipTypes::READ_BACK_CURRENT_SETTINGS) ? true : false;
    }

    GeometricVector AccelBias::getResponseData(const GenericMipCmdResponse& response)
    {
        DataBuffer dataBuffer(response.data());
        GeometricVector returnData;
        returnData.x(dataBuffer.read_float());
        returnData.y(dataBuffer.read_float());
        returnData.z(dataBuffer.read_float());
        return returnData;
    }

    AccelBias::operator ByteStream() const
    {
        ByteStream byteCommand;
        byteCommand.append_uint8(static_cast<uint8>(m_functionSelector));

        // Only fill in data if set command is being sent.
        if (m_functionSelector == MipTypes::USE_NEW_SETTINGS)
        {    // Put in X, Y, and Z values of vector.
            byteCommand.append_float(m_accelerometerBiasVector.x());
            byteCommand.append_float(m_accelerometerBiasVector.y());
            byteCommand.append_float(m_accelerometerBiasVector.z());
        }
        return GenericMipCommand::buildCommand(commandType(), byteCommand.data());
    }

}
