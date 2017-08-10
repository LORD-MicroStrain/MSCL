#include "stdafx.h"
#include "CaptureGyroBias.h"
#include "mscl/MicroStrain/Inertial/InertialDataField.h"
#include "mscl/MicroStrain/Inertial/Packets/InertialPacketBuilder.h"
#include "mscl/MicroStrain/Inertial/InertialTypes.h"
#include "Inertial_Commands.h"

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

    GeometricVector CaptureGyroBias::getResponseData(const GenericInertialCommandResponse& response)
    {
        DataBuffer dataBuffer(response.data());
        GeometricVector returnData{ dataBuffer.read_float(), dataBuffer.read_float(), dataBuffer.read_float() };
        return returnData;
    }

    CaptureGyroBias::operator ByteStream() const
    {
        ByteStream byteCommand;
        byteCommand.append_uint16(m_samplingTimeInMS);
        return GenericInertialCommand::buildCommand(commandType(), byteCommand.data()); ;
    }

}