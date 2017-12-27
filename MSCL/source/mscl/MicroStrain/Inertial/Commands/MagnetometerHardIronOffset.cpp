#include "stdafx.h"
#include "MagnetometerHardIronOffset.h"
#include "mscl/MicroStrain/Inertial/InertialDataField.h"
#include "mscl/MicroStrain/Inertial/Packets/InertialPacketBuilder.h"
#include "mscl/MicroStrain/Inertial/InertialTypes.h"
#include "Inertial_Commands.h"

namespace mscl
{
    MagnetometerHardIronOffset::MagnetometerHardIronOffset(InertialTypes::FunctionSelector function_selector, GeometricVector dataToUse) :
        m_functionSelector(function_selector),
        m_offsetVector(dataToUse)
    { }

    MagnetometerHardIronOffset::MagnetometerHardIronOffset(InertialTypes::FunctionSelector function_selector) :
        m_functionSelector(function_selector)
    {
        if (function_selector == InertialTypes::USE_NEW_SETTINGS)
            throw Error_NoData("Data must be passed in for a set command.");
    }

    MagnetometerHardIronOffset MagnetometerHardIronOffset::MakeSetCommand(GeometricVector dataToUse)
    {
        return MagnetometerHardIronOffset(InertialTypes::USE_NEW_SETTINGS, dataToUse);
    }

    MagnetometerHardIronOffset MagnetometerHardIronOffset::MakeGetCommand()
    {
        GeometricVector dataToUse;  // The data won't get used for a get command.
        return MagnetometerHardIronOffset(InertialTypes::READ_BACK_CURRENT_SETTINGS, dataToUse);
    }

    bool MagnetometerHardIronOffset::responseExpected() const
    {
        return (m_functionSelector == InertialTypes::READ_BACK_CURRENT_SETTINGS) ? true : false;
    }

    GeometricVector MagnetometerHardIronOffset::getResponseData(const GenericInertialCommandResponse& response)
    {
        DataBuffer dataBuffer(response.data());
        GeometricVector returnData{ dataBuffer.read_float(), dataBuffer.read_float(), dataBuffer.read_float() };
        return returnData;
    }

    MagnetometerHardIronOffset::operator ByteStream() const
    {
        ByteStream byteCommand;
        byteCommand.append_uint8(static_cast<uint8>(m_functionSelector));

        // Only fill in data if set command is being sent.
        if (m_functionSelector == InertialTypes::USE_NEW_SETTINGS)
        {    // Put in X, Y, and Z values of vector.
            byteCommand.append_float(m_offsetVector.x);
            byteCommand.append_float(m_offsetVector.y);
            byteCommand.append_float(m_offsetVector.z);
        }
        return GenericInertialCommand::buildCommand(commandType(), byteCommand.data()); ;
    }

}