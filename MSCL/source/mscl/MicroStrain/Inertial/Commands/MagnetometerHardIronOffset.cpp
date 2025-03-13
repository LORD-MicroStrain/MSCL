/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "stdafx.h"
#include "MagnetometerHardIronOffset.h"
#include "mscl/MicroStrain/MIP/MipDataField.h"
#include "mscl/MicroStrain/MIP/Packets/MipPacketBuilder.h"
#include "mscl/MicroStrain/MIP/MipTypes.h"
#include "mscl/MicroStrain/MIP/Commands/MIP_Commands.h"

namespace mscl
{
    MagnetometerHardIronOffset::MagnetometerHardIronOffset(MipTypes::FunctionSelector function_selector, GeometricVector dataToUse) :
        m_functionSelector(function_selector),
        m_offsetVector(dataToUse)
    { }

    MagnetometerHardIronOffset::MagnetometerHardIronOffset(MipTypes::FunctionSelector function_selector) :
        m_functionSelector(function_selector)
    {
        if (function_selector == MipTypes::USE_NEW_SETTINGS)
            throw Error_NoData("Data must be passed in for a set command.");
    }

    MagnetometerHardIronOffset MagnetometerHardIronOffset::MakeSetCommand(GeometricVector dataToUse)
    {
        return MagnetometerHardIronOffset(MipTypes::USE_NEW_SETTINGS, dataToUse);
    }

    MagnetometerHardIronOffset MagnetometerHardIronOffset::MakeGetCommand()
    {
        GeometricVector dataToUse;  // The data won't get used for a get command.
        return MagnetometerHardIronOffset(MipTypes::READ_BACK_CURRENT_SETTINGS, dataToUse);
    }

    bool MagnetometerHardIronOffset::responseExpected() const
    {
        return (m_functionSelector == MipTypes::READ_BACK_CURRENT_SETTINGS) ? true : false;
    }

    GeometricVector MagnetometerHardIronOffset::getResponseData(const GenericMipCmdResponse& response)
    {
        DataBuffer dataBuffer(response.data());
        GeometricVector returnData;
        returnData.x(dataBuffer.read_float());
        returnData.y(dataBuffer.read_float());
        returnData.z(dataBuffer.read_float());
        return returnData;
    }

    MagnetometerHardIronOffset::operator ByteStream() const
    {
        ByteStream byteCommand;
        byteCommand.append_uint8(static_cast<uint8>(m_functionSelector));

        // Only fill in data if set command is being sent.
        if (m_functionSelector == MipTypes::USE_NEW_SETTINGS)
        {    // Put in X, Y, and Z values of vector.
            byteCommand.append_float(m_offsetVector.x());
            byteCommand.append_float(m_offsetVector.y());
            byteCommand.append_float(m_offsetVector.z());
        }
        return GenericMipCommand::buildCommand(commandType(), byteCommand.data()); ;
    }

}
