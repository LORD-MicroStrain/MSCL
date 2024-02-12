/*****************************************************************************************
**          Copyright(c) 2015-2024 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.    **
*****************************************************************************************/

#include "stdafx.h"
#include "Matrix3x3Command.h"
#include "mscl/MicroStrain/MIP/MipDataField.h"
#include "mscl/MicroStrain/MIP/Packets/MipPacketBuilder.h"
#include "mscl/MicroStrain/MIP/MipTypes.h"
#include "mscl/MicroStrain/MIP/Commands/MIP_Commands.h"

namespace mscl
{
    Matrix3x3Command::Matrix3x3Command(MipTypes::Command cmd, MipTypes::FunctionSelector function_selector, const Matrix_3x3s& dataToUse) :
        m_cmd(cmd),
        m_functionSelector(function_selector),
        m_data(dataToUse)
    { }

    Matrix3x3Command::Matrix3x3Command(MipTypes::Command cmd, MipTypes::FunctionSelector function_selector) :
        m_cmd(cmd),
        m_functionSelector(function_selector)
    {
        if (function_selector == MipTypes::USE_NEW_SETTINGS)
            throw Error_NoData("Data must be passed in for a set command.");
    }

    std::string Matrix3x3Command::commandName() const
    {
        switch (m_cmd)
        {
        case MipTypes::Command::CMD_EF_SOFT_IRON_OFFSET_PROCESS_NOISE:
            return "SoftIronMatrixProcessNoise";
        default:
            return "";
        }
    }

    uint8 Matrix3x3Command::fieldDataByte() const
    {
        switch (m_cmd)
        {
        case MipTypes::Command::CMD_EF_SOFT_IRON_OFFSET_PROCESS_NOISE:
            return 0x97;
        default:
            return 0;
        }
    }

    Matrix3x3Command Matrix3x3Command::MakeSetCommand(MipTypes::Command cmd, const Matrix_3x3s& data)
    {
        return Matrix3x3Command(cmd, MipTypes::USE_NEW_SETTINGS, data);
    }

    Matrix3x3Command Matrix3x3Command::MakeGetCommand(MipTypes::Command cmd)
    {
        return Matrix3x3Command(cmd, MipTypes::READ_BACK_CURRENT_SETTINGS);
    }

    bool Matrix3x3Command::responseExpected() const
    {
        return m_functionSelector == MipTypes::READ_BACK_CURRENT_SETTINGS;
    }

    Matrix_3x3s Matrix3x3Command::getResponseData(const GenericMipCmdResponse& response)
    {
        DataBuffer buffer(response.data());
        Matrix_3x3s data;

        int dataPointCount = 1;

        for (int i = 0; i < dataPointCount; i++)
        {
            Matrix_3x3 point;
            for (uint8 j = 0; j < 3; j++)
            {
                for (uint8 k = 0; k < 3; k++)
                {
                    point.set(j, k, buffer.read_float());
                }
            }
            data.push_back(point);
        }

        return data;
    }

    Matrix3x3Command::operator ByteStream() const
    {
        ByteStream byteCommand;
        byteCommand.append_uint8(static_cast<uint8>(m_functionSelector));

        if (m_functionSelector == MipTypes::USE_NEW_SETTINGS)
        {
            for (size_t i = 0; i < m_data.size(); i++)
            {
                for (uint8 j = 0; j < 3; j++)
                {
                    for (uint8 k = 0; k < 3; k++)
                    {
                        byteCommand.append_float(m_data[i](j, k));
                    }
                }
            }
        }

        return GenericMipCommand::buildCommand(commandType(), byteCommand.data());
    }
}