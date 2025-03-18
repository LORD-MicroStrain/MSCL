/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "mscl/MicroStrain/Displacement/Commands/DisplacementOutputDataRate.h"

namespace mscl
{
    ByteStream DisplacementOutputDataRate::buildCommand_get()
    {
        Bytes fieldData;
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
