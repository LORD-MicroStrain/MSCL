/*****************************************************************************************
**          Copyright(c) 2015-2024 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "stdafx.h"
#include "ExternalHeadingUpdateWithTimestamp.h"
#include "mscl/MicroStrain/MIP/MipDataField.h"
#include "mscl/MicroStrain/MIP/Packets/MipPacketBuilder.h"
#include "mscl/MicroStrain/MIP/MipTypes.h"
#include "mscl/MicroStrain/MIP/Commands/MIP_Commands.h"

namespace mscl
{
    ExternalHeadingUpdateWithTimestamp::ExternalHeadingUpdateWithTimestamp(const HeadingData& headingData, const TimeUpdate& timestamp) :
        m_headingData(headingData),
        m_Timestamp (timestamp)
    { }

    ExternalHeadingUpdateWithTimestamp ExternalHeadingUpdateWithTimestamp::MakeCommand(const HeadingData& headingData, const TimeUpdate& timestamp)
    {
        return ExternalHeadingUpdateWithTimestamp(headingData, timestamp);
    }

    bool ExternalHeadingUpdateWithTimestamp::responseExpected() const
    {
        return false;
    }

    ExternalHeadingUpdateWithTimestamp::operator ByteStream() const
    {
        ByteStream byteCommand;
        byteCommand.append_double(m_Timestamp.timeOfWeek());
        byteCommand.append_uint16(m_Timestamp.weekNumber());
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
