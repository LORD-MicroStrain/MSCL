#include "stdafx.h"
#include "MagnetometerSoftIronMatrix.h"
#include "mscl/MicroStrain/Inertial/InertialDataField.h"
#include "mscl/MicroStrain/Inertial/Packets/InertialPacketBuilder.h"
#include "mscl/MicroStrain/Inertial/InertialTypes.h"
#include "Inertial_Commands.h"

namespace mscl
{
    MagnetometerSoftIronMatrix::MagnetometerSoftIronMatrix(InertialTypes::FunctionSelector function_selector, Matrix_3x3 matrix) :
        m_functionSelector(function_selector),
        m_matrix(matrix)
    { }

    MagnetometerSoftIronMatrix::MagnetometerSoftIronMatrix(InertialTypes::FunctionSelector function_selector) :
        m_functionSelector(function_selector),
        m_matrix(0, 0, 0, 0, 0, 0, 0, 0, 0)
    {
        if (function_selector == InertialTypes::USE_NEW_SETTINGS)
            throw Error_NoData("Data must be passed in for a set command.");
    }

    MagnetometerSoftIronMatrix MagnetometerSoftIronMatrix::MakeSetCommand(Matrix_3x3 dataToUse)
    {
        return MagnetometerSoftIronMatrix(InertialTypes::USE_NEW_SETTINGS, dataToUse);
    }

    MagnetometerSoftIronMatrix MagnetometerSoftIronMatrix::MakeGetCommand()
    {
        Matrix_3x3 zeroMatrix (0,0,0, 0, 0, 0, 0, 0, 0);  // The data won't get used for a get command.
        return MagnetometerSoftIronMatrix(InertialTypes::READ_BACK_CURRENT_SETTINGS, zeroMatrix);
    }

    bool MagnetometerSoftIronMatrix::responseExpected() const
    {
        return (m_functionSelector == InertialTypes::READ_BACK_CURRENT_SETTINGS) ? true : false;
    }

    Matrix_3x3 MagnetometerSoftIronMatrix::getResponseData(const GenericInertialCommandResponse& response)
    {
        DataBuffer dataBuffer(response.data());
        Matrix_3x3 returnData;
        for (uint8 row = 0; row < 3; ++row)
        {
            for (uint8 col = 0; col < 3; ++col)
            {
                returnData.set(row, col, dataBuffer.read_float());
            }
        }
        return returnData;
    }

    MagnetometerSoftIronMatrix::operator ByteStream() const
    {
        ByteStream byteCommand;
        byteCommand.append_uint8(static_cast<uint8>(m_functionSelector));

        // Only fill in data if set command is being sent.
        if (m_functionSelector == InertialTypes::USE_NEW_SETTINGS)
        {
            for (uint8 row = 0; row < 3; ++row)
            {
                for (uint8 col = 0; col < 3; ++col)
                {
                    byteCommand.append_float(m_matrix(row,col));
                }
            }
        }
        return GenericInertialCommand::buildCommand(commandType(), byteCommand.data()); ;
    }

}