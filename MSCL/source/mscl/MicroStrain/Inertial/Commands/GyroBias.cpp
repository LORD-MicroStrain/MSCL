#include "stdafx.h"
#include "GyroBias.h"
#include "mscl/MicroStrain/Inertial/InertialDataField.h"
#include "mscl/MicroStrain/Inertial/Packets/InertialPacketBuilder.h"
#include "mscl/MicroStrain/Inertial/InertialTypes.h"
#include "Inertial_Commands.h"

namespace mscl
{
    GyroBias::GyroBias(InertialTypes::FunctionSelector function_selector, GeometricVector gyroBiasVector) :
        m_functionSelector(function_selector),
        m_gyroBiasVector(gyroBiasVector)
    { }

    GyroBias::GyroBias(InertialTypes::FunctionSelector function_selector) :
        m_functionSelector(function_selector)
    {
        if (function_selector == InertialTypes::USE_NEW_SETTINGS)
            throw Error_NoData("Data must be passed in for a set command.");
    }

    GyroBias GyroBias::MakeSetCommand(GeometricVector offsetVector)
    {
        return GyroBias(InertialTypes::USE_NEW_SETTINGS, offsetVector);
    }

    GyroBias GyroBias::MakeGetCommand()
    {
        GeometricVector dataToUse;  // The data won't get used for a get command.
        return GyroBias(InertialTypes::READ_BACK_CURRENT_SETTINGS, dataToUse);
    }

    bool GyroBias::responseExpected() const
    {
        return (m_functionSelector == InertialTypes::READ_BACK_CURRENT_SETTINGS) ? true : false;
    }

    GeometricVector GyroBias::getResponseData(const GenericInertialCommandResponse& response)
    {
        DataBuffer dataBuffer(response.data());
        GeometricVector returnData{ dataBuffer.read_float(), dataBuffer.read_float(), dataBuffer.read_float() };
        return returnData;
    }

    GyroBias::operator ByteStream() const
    {
        ByteStream byteCommand;
        byteCommand.append_uint8(static_cast<uint8>(m_functionSelector));

        // Only fill in data if set command is being sent.
        if (m_functionSelector == InertialTypes::USE_NEW_SETTINGS)
        {    // Put in X, Y, and Z values of vector.
            byteCommand.append_float(m_gyroBiasVector.x);
            byteCommand.append_float(m_gyroBiasVector.y);
            byteCommand.append_float(m_gyroBiasVector.z);
        }
        return GenericInertialCommand::buildCommand(commandType(), byteCommand.data()); ;
    }

}