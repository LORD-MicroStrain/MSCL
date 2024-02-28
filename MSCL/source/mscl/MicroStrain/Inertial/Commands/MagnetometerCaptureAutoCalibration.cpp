/*****************************************************************************************
**          Copyright(c) 2015-2024 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "stdafx.h"
#include "MagnetometerCaptureAutoCalibration.h"
#include "mscl/MicroStrain/MIP/MipDataField.h"
#include "mscl/MicroStrain/MIP/Packets/MipPacketBuilder.h"
#include "mscl/MicroStrain/MIP/MipTypes.h"
#include "mscl/MicroStrain/MIP/Commands/MIP_Commands.h"

namespace mscl
{
    MagnetometerCaptureAutoCalibration::MagnetometerCaptureAutoCalibration(MipTypes::FunctionSelector functionSelector) :
        m_functionSelector(functionSelector)
    { }

    bool MagnetometerCaptureAutoCalibration::responseExpected() const
    {
        return false;
    }

    MagnetometerCaptureAutoCalibration MagnetometerCaptureAutoCalibration::MakeCommand()
    {
        return MagnetometerCaptureAutoCalibration(MipTypes::USE_NEW_SETTINGS);
    }

    MagnetometerCaptureAutoCalibration MagnetometerCaptureAutoCalibration::MakeSaveCommand()
    {
        return MagnetometerCaptureAutoCalibration(MipTypes::SAVE_CURRENT_SETTINGS);
    }

    bool MagnetometerCaptureAutoCalibration::getResponseData(const GenericMipCmdResponse& response)
    {
        DataBuffer dataBuffer(response.data());

        return false;
    }

    MagnetometerCaptureAutoCalibration::operator ByteStream() const
    {
        ByteStream byteCommand;
        byteCommand.append_uint8(static_cast<uint8>(m_functionSelector));
        return GenericMipCommand::buildCommand(commandType(), byteCommand.data());
    }

}
