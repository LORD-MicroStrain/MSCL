#include "stdafx.h"
#include "ExternalHeadingUpdate.h"
#include "mscl/MicroStrain/Inertial/InertialDataField.h"
#include "mscl/MicroStrain/Inertial/Packets/InertialPacketBuilder.h"
#include "mscl/MicroStrain/Inertial/InertialTypes.h"
#include "Inertial_Commands.h"

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
            throw Error_InertialCmdFailed("Unknown heading type used.");
        byteCommand.append_uint8(headingType);

        return GenericInertialCommand::buildCommand(commandType(), byteCommand.data());
    }

}