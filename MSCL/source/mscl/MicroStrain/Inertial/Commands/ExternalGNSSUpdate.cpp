/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "mscl/MicroStrain/Inertial/Commands/ExternalGNSSUpdate.h"

namespace mscl
{
    ExternalGNSSUpdate::ExternalGNSSUpdate(const ExternalGNSSUpdateData& dataToUse) :
        m_data(dataToUse)
    {}

    ExternalGNSSUpdate ExternalGNSSUpdate::MakeCommand(const ExternalGNSSUpdateData& dataToUse)
    {
        return ExternalGNSSUpdate(dataToUse);
    }

    bool ExternalGNSSUpdate::responseExpected() const
    {
        return false;
    }

    ExternalGNSSUpdate::operator ByteStream() const
    {
        ByteStream byteCommand;
        byteCommand.append_double(m_data.gpsTimeOfWeek);
        byteCommand.append_uint16(m_data.gpsWeekNumber);
        byteCommand.append_double(m_data.lattitude);
        byteCommand.append_double(m_data.longitude);
        byteCommand.append_double(m_data.altitudeAboveWGS84Ellipsoid);
        byteCommand.append_float(m_data.northVelocity);
        byteCommand.append_float(m_data.eastVelocity);
        byteCommand.append_float(m_data.downVelocity);
        byteCommand.append_float(m_data.northPositionUncertainty);
        byteCommand.append_float(m_data.eastPositionUncertainty);
        byteCommand.append_float(m_data.downPositionUncertainty);
        byteCommand.append_float(m_data.northVelocityUncertainty);
        byteCommand.append_float(m_data.eastVelocityUncertainty);
        byteCommand.append_float(m_data.downVelocityUncertainty);

        return GenericMipCommand::buildCommand(commandType(), byteCommand.data());
    }
} // namespace mscl
