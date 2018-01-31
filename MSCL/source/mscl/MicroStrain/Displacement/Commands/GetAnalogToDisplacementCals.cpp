#include "stdafx.h"
#include "GetAnalogToDisplacementCals.h"
#include "mscl/MicroStrain/MIP/MipDataField.h"
#include "mscl/MicroStrain/MIP/Packets/MipPacketBuilder.h"
#include "mscl/MicroStrain/MIP/MipTypes.h"
#include "mscl/MicroStrain/MIP/Commands/MIP_Commands.h"

namespace mscl
{
    ByteStream GetAnalogToDisplacementCals::buildCommand_get()
    {
        return buildCommand(MipTypes::CMD_GET_ANALOG_DISPLACEMENT_CALS);
    }

    GetAnalogToDisplacementCals::Response::Response(std::weak_ptr<ResponseCollector> collector) :
        GenericMipCommand::Response(MipTypes::CMD_GET_ANALOG_DISPLACEMENT_CALS, collector, true, true, "Displacement Output Data Rate")
    {
    }

    LinearEquation GetAnalogToDisplacementCals::Response::parseResponse(const GenericMipCmdResponse& response) const
    {
        float slope = response.data().read_float(0);
        float offset = response.data().read_float(4);

        return LinearEquation(slope, offset);
    }
}