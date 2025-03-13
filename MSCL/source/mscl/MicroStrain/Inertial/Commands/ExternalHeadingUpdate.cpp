/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "stdafx.h"
#include "ExternalHeadingUpdate.h"
#include "mscl/MicroStrain/MIP/MipDataField.h"
#include "mscl/MicroStrain/MIP/Packets/MipPacketBuilder.h"
#include "mscl/MicroStrain/MIP/MipTypes.h"
#include "mscl/MicroStrain/MIP/Commands/MIP_Commands.h"

namespace mscl
{
    ExternalHeadingUpdate::ExternalHeadingUpdate(const HeadingData& headingData) :
        m_headingData(headingData)
    { }

    ExternalHeadingUpdate ExternalHeadingUpdate::MakeCommand(const HeadingData& headingData)
    {
        return ExternalHeadingUpdate(headingData);
    }

    bool ExternalHeadingUpdate::responseExpected() const
    {
        return false;
    }

    ExternalHeadingUpdate::operator ByteStream() const
    {
        ByteStream byteCommand;
        byteCommand.append_float(m_headingData.headingAngle);
        byteCommand.append_float(m_headingData.headingAngleUncertainty);
        uint8 headingType = 0x01;
        if (m_headingData.heading == HeadingData::HeadingType::TRUE_HEADING)
            headingType = 0x01;
        else if (m_headingData.heading == HeadingData::HeadingType::MAGNETIC_HEADING)
            headingType = 0x02;
        else
            throw Error_MipCmdFailed("Unknown heading type used.");
        byteCommand.append_uint8(headingType);

        return GenericMipCommand::buildCommand(commandType(), byteCommand.data());
    }

}
