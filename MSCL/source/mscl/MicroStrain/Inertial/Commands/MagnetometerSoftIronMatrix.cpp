/*****************************************************************************************
**          Copyright(c) 2015-2022 Parker Hannifin Corp. All rights reserved.           **
**                                                                                      **
**    MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.    **
*****************************************************************************************/

#include "stdafx.h"
#include "MagnetometerSoftIronMatrix.h"
#include "mscl/MicroStrain/MIP/MipDataField.h"
#include "mscl/MicroStrain/MIP/Packets/MipPacketBuilder.h"
#include "mscl/MicroStrain/MIP/MipTypes.h"
#include "mscl/MicroStrain/MIP/Commands/MIP_Commands.h"

namespace mscl
{
    MagnetometerSoftIronMatrix::MagnetometerSoftIronMatrix(MipTypes::FunctionSelector function_selector, Matrix_3x3 matrix) :
        m_functionSelector(function_selector),
        m_matrix(matrix)
    { }

    MagnetometerSoftIronMatrix::MagnetometerSoftIronMatrix(MipTypes::FunctionSelector function_selector) :
        m_functionSelector(function_selector),
        m_matrix(0, 0, 0, 0, 0, 0, 0, 0, 0)
    {
        if (function_selector == MipTypes::USE_NEW_SETTINGS)
            throw Error_NoData("Data must be passed in for a set command.");
    }

    MagnetometerSoftIronMatrix MagnetometerSoftIronMatrix::MakeSetCommand(Matrix_3x3 dataToUse)
    {
        return MagnetometerSoftIronMatrix(MipTypes::USE_NEW_SETTINGS, dataToUse);
    }

    MagnetometerSoftIronMatrix MagnetometerSoftIronMatrix::MakeGetCommand()
    {
        Matrix_3x3 zeroMatrix (0,0,0, 0, 0, 0, 0, 0, 0);  // The data won't get used for a get command.
        return MagnetometerSoftIronMatrix(MipTypes::READ_BACK_CURRENT_SETTINGS, zeroMatrix);
    }

    bool MagnetometerSoftIronMatrix::responseExpected() const
    {
        return (m_functionSelector == MipTypes::READ_BACK_CURRENT_SETTINGS) ? true : false;
    }

    Matrix_3x3 MagnetometerSoftIronMatrix::getResponseData(const GenericMipCmdResponse& response)
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
        if (m_functionSelector == MipTypes::USE_NEW_SETTINGS)
        {
            for (uint8 row = 0; row < 3; ++row)
            {
                for (uint8 col = 0; col < 3; ++col)
                {
                    byteCommand.append_float(m_matrix(row,col));
                }
            }
        }
        return GenericMipCommand::buildCommand(commandType(), byteCommand.data()); ;
    }

}