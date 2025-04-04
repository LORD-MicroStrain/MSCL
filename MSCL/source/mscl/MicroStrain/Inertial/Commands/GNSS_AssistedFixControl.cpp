/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "mscl/MicroStrain/Inertial/Commands/GNSS_AssistedFixControl.h"

namespace mscl
{
    ByteStream GNSS_AssistedFixControl::buildCommand_get()
    {
        Bytes fieldData;
        fieldData.push_back(MipTypes::READ_BACK_CURRENT_SETTINGS);

        return buildCommand(MipTypes::CMD_GNSS_ASSIST_FIX_CONTROL, fieldData);
    }

    ByteStream GNSS_AssistedFixControl::buildCommand_set(bool enableAssistedFix)
    {
        MipTypes::EnableSetting assistedFixOption = enableAssistedFix ? MipTypes::ENABLED : MipTypes::DISABLED;
        //create the field to add to the packet
        Bytes fieldData;
        fieldData.push_back(MipTypes::USE_NEW_SETTINGS);
        fieldData.push_back( static_cast<unsigned char>(assistedFixOption));
        fieldData.push_back(NO_FLAGS_DEFINED);
        return buildCommand(MipTypes::CMD_GNSS_ASSIST_FIX_CONTROL, fieldData);
    }

    GNSS_AssistedFixControl::Response::Response(std::weak_ptr<ResponseCollector> collector, bool ackNackExpected, bool dataResponseExpected) :
        GenericMipCommand::Response(MipTypes::CMD_GNSS_ASSIST_FIX_CONTROL, collector, ackNackExpected, dataResponseExpected, "GNSS_AssistedFixControl")
    {}

    bool GNSS_AssistedFixControl::Response::parseResponse(const GenericMipCmdResponse& response) const
    {
        uint8 theResult = response.data().read_uint8(0);
        if (theResult > 1)
            throw Error_MipCmdFailed();

        if (theResult == 0)
            return false;

        return true;  // (theResult == 1)
    }
} // namespace mscl
