/*****************************************************************************************
**          Copyright(c) 2015-2022 Parker Hannifin Corp. All rights reserved.           **
**                                                                                      **
**    MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.    **
*****************************************************************************************/

#include "stdafx.h"
#include "DisplacementOutputDataRate.h"
#include "mscl/MicroStrain/MIP/MipDataField.h"
#include "mscl/MicroStrain/MIP/Packets/MipPacketBuilder.h"
#include "mscl/MicroStrain/MIP/MipTypes.h"
#include "mscl/MicroStrain/MIP/Commands/MIP_Commands.h"

namespace mscl
{
    ByteStream DisplacementOutputDataRate::buildCommand_get()
    {
        mscl::Bytes fieldData;
        fieldData.push_back(MipTypes::READ_BACK_CURRENT_SETTINGS);

        return buildCommand(MipTypes::CMD_DISPLACEMENT_OUTPUT_RATE, fieldData);
    }

    DisplacementOutputDataRate::Response::Response(std::weak_ptr<ResponseCollector> collector, bool dataResponseExpected) :
        GenericMipCommand::Response(MipTypes::CMD_DISPLACEMENT_OUTPUT_RATE, collector, true, dataResponseExpected, "Displacement Output Data Rate")
    {
    }

    SampleRate DisplacementOutputDataRate::Response::parseResponse(const GenericMipCmdResponse& response) const
    {
        uint32 hertzRate = response.data().read_uint32(0);

        return SampleRate::Hertz(hertzRate);
    }
}