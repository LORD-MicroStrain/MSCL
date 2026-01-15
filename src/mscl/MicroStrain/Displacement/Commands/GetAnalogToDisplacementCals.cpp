/*****************************************************************************************
**          Copyright(c) 2015-2026 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "mscl/MicroStrain/Displacement/Commands/GetAnalogToDisplacementCals.h"

namespace mscl
{
    ByteStream GetAnalogToDisplacementCals::buildCommand_get()
    {
        return buildCommand(MipTypes::CMD_GET_ANALOG_DISPLACEMENT_CALS);
    }

    GetAnalogToDisplacementCals::Response::Response(std::weak_ptr<ResponseCollector> collector) :
        GenericMipCommand::Response(MipTypes::CMD_GET_ANALOG_DISPLACEMENT_CALS, collector, true, true, "Displacement Output Data Rate")
    {}

    LinearEquation GetAnalogToDisplacementCals::Response::parseResponse(const GenericMipCmdResponse& response) const
    {
        float slope = response.data().read_float(0);
        float offset = response.data().read_float(4);

        return LinearEquation(slope, offset);
    }
} // namespace mscl
