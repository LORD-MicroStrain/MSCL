#include "stdafx.h"
#include "GNSS_AssistedFixControl.h"
#include "mscl/MicroStrain/Inertial/InertialDataField.h"
#include "mscl/MicroStrain/Inertial/Packets/InertialPacketBuilder.h"
#include "mscl/MicroStrain/Inertial/InertialTypes.h"
#include "Inertial_Commands.h"

namespace mscl
{
	ByteStream GNSS_AssistedFixControl::buildCommand_get()
	{
		mscl::Bytes fieldData;
		fieldData.push_back(InertialTypes::READ_BACK_CURRENT_SETTINGS);

        return buildCommand(InertialTypes::CMD_GNSS_ASSIST_FIX_CONTROL, fieldData);
	}

	ByteStream GNSS_AssistedFixControl::buildCommand_set(bool enableAssistedFix)
	{
        InertialTypes::EnableSetting assistedFixOption = enableAssistedFix ? InertialTypes::ENABLED : InertialTypes::DISABLED;
		//create the field to add to the packet
		mscl::Bytes fieldData;
		fieldData.push_back(InertialTypes::USE_NEW_SETTINGS);
		fieldData.push_back( static_cast<unsigned char>(assistedFixOption));
		fieldData.push_back(NO_FLAGS_DEFINED);
        return buildCommand(InertialTypes::CMD_GNSS_ASSIST_FIX_CONTROL, fieldData);
	}

	GNSS_AssistedFixControl::Response::Response(std::weak_ptr<ResponseCollector> collector, bool ackNackExpected, bool dataResponseExpected) :
		GenericInertialCommand::Response(InertialTypes::CMD_GNSS_ASSIST_FIX_CONTROL, collector, ackNackExpected, dataResponseExpected, "GNSS_AssistedFixControl")
	{
	}

    bool GNSS_AssistedFixControl::Response::parseResponse(const GenericInertialCommandResponse& response) const
    {
        uint8 theResult = response.data().read_uint8(0);
        if (theResult > 1)
            throw Error_InertialCmdFailed();

        if (theResult == 0)
            return false;
        
        return true;  // (theResult == 1)
    }
}