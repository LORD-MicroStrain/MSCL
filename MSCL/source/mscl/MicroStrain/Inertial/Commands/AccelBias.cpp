#include "stdafx.h"
#include "AccelBias.h"
#include "mscl/MicroStrain/Inertial/InertialDataField.h"
#include "mscl/MicroStrain/Inertial/Packets/InertialPacketBuilder.h"
#include "mscl/MicroStrain/Inertial/InertialTypes.h"
#include "Inertial_Commands.h"

namespace mscl
{
    AccelBias::AccelBias(InertialTypes::FunctionSelector functionSelector, const GeometricVector& accelerometerBiasVector) :
        m_functionSelector(functionSelector),
        m_accelerometerBiasVector(accelerometerBiasVector)
    { }

    AccelBias::AccelBias(InertialTypes::FunctionSelector functionSelector) :
        m_functionSelector(functionSelector)
    {
        if (functionSelector == InertialTypes::USE_NEW_SETTINGS)
            throw Error_NoData("Data must be passed in for a set command.");
    }

    AccelBias AccelBias::MakeSetCommand(const GeometricVector& vectorToSet)
    {
        return AccelBias(InertialTypes::USE_NEW_SETTINGS, vectorToSet);
    }

    AccelBias AccelBias::MakeGetCommand()
    {
        GeometricVector dataToUse;  // The data won't get used for a get command.
        return AccelBias(InertialTypes::READ_BACK_CURRENT_SETTINGS, dataToUse);
    }

    bool AccelBias::responseExpected() const
    {
        return (m_functionSelector == InertialTypes::READ_BACK_CURRENT_SETTINGS) ? true : false;
    }

    GeometricVector AccelBias::getResponseData(const GenericInertialCommandResponse& response)
    {
        DataBuffer dataBuffer(response.data());
        GeometricVector returnData { dataBuffer.read_float(), dataBuffer.read_float(), dataBuffer.read_float() };
        return returnData;
    }

    AccelBias::operator ByteStream() const
    {
        ByteStream byteCommand;
        byteCommand.append_uint8(static_cast<uint8>(m_functionSelector));

        // Only fill in data if set command is being sent.
        if (m_functionSelector == InertialTypes::USE_NEW_SETTINGS)
        {    // Put in X, Y, and Z values of vector.
            byteCommand.append_float(m_accelerometerBiasVector[0]);
            byteCommand.append_float(m_accelerometerBiasVector[1]);
            byteCommand.append_float(m_accelerometerBiasVector[2]);
        }
        return GenericInertialCommand::buildCommand(commandType(), byteCommand.data()); ;
    }

}