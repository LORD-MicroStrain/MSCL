#include "stdafx.h"
#include "CaptureGyroBias.h"
#include "mscl/MicroStrain/MIP/MipDataField.h"
#include "mscl/MicroStrain/MIP/Packets/MipPacketBuilder.h"
#include "mscl/MicroStrain/MIP/MipTypes.h"
#include "mscl/MicroStrain/MIP/Commands/MIP_Commands.h"

namespace mscl
{
    CaptureGyroBias::CaptureGyroBias(uint16 samplingTimeInMS) :
        m_samplingTimeInMS(samplingTimeInMS)
    { }

    CaptureGyroBias CaptureGyroBias::MakeCommand(uint16 dataToUse)
    {
        return CaptureGyroBias(dataToUse);
    }

    bool CaptureGyroBias::responseExpected() const
    {
        return true;
    }

    GeometricVector CaptureGyroBias::getResponseData(const GenericMipCmdResponse& response)
    {
        DataBuffer dataBuffer(response.data());
        GeometricVector returnData{ dataBuffer.read_float(), dataBuffer.read_float(), dataBuffer.read_float() };
        return returnData;
    }

    CaptureGyroBias::operator ByteStream() const
    {
        ByteStream byteCommand;
        byteCommand.append_uint16(m_samplingTimeInMS);
        return GenericMipCommand::buildCommand(commandType(), byteCommand.data()); ;
    }

}