/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "mscl/MicroStrain/MIP/Commands/GenericMipCommand.h"
#include "mscl/MicroStrain/Inertial/EulerAngles.h"
#include "mscl/MicroStrain/MIP/MipChannel.h"
#include "mscl/MicroStrain/MIP/MipTypes.h"
#include "mscl/MicroStrain/Inertial/PositionOffset.h"
#include "GetDeviceInfo.h"
#include "mscl/MicroStrain/Inertial/ExposedInertialTypes.h"

namespace mscl
{
    //Class: MIP_Commands
    //    Contains helper functions for MIP Commands
    class MIP_Commands
    {
    public:
        //Function: parseData_singleBool
        //    Parses the data for a single boolean flag response.
        //
        //Parameters:
        //    response - The <GenericMipCmdResponse> that contains the data to be parsed.
        //
        //Returns:
        //    The boolean parsed from the response.
        static bool parseData_singleBool(const GenericMipCmdResponse& response);

        //Function: parseData_GetDeviceInfo
        //    Parses the data from a GetDeviceInfo response.
        //
        //Parameters:
        //    response - The <GenericMipCmdResponse> that contains the data to be parsed.
        //    result - Holds the <MipDeviceInfo> result.
        static void parseData_GetDeviceInfo(const GenericMipCmdResponse& response, MipDeviceInfo& result);

        //Function: parseData_GetDeviceDescriptorSets
        //    Parses the data from a GetDeviceDescriptorSets response.
        //
        //Parameters:
        //    response - The <GenericMipCmdResponse> that contains the data to be parsed.
        //    result - Holds the descriptor sets result.
        static void parseData_GetDeviceDescriptorSets(const GenericMipCmdResponse& response, std::vector<uint16>& result);

        //Function: parseData_DataRateBase
        //    Parses the data from a DataRateBase response
        //
        //Parameters:
        //    response - The <GenericMipCmdResponse> that contains the data to be parsed
        //
        //Returns:
        //    The data rate base parsed from the response
        static uint16 parseData_DataRateBase(const GenericMipCmdResponse& response);

        //Function: parseData_CommunicationMode
        //    Parses the data from a CommunicationMode response
        //
        //Parameters:
        //    response - The <GenericMipCmdResponse> that contains the data to be parsed
        //
        //Returns:
        //    The data rate base parsed from the response
        static uint8 parseData_CommunicationMode(const GenericMipCmdResponse& response);

//        static uint8 parseData_AssistedFixOptions(const GenericMipCmdResponse& response);

        //Function: parseData_MessageFormat
        //    Parses the data from a MessageFormat response
        //
        //Parameters:
        //    response - The <GenericMipCmdResponse> that contains the data to be parsed
        //    descSet - The descriptor set byte for this specific MessageFormat command
        //    sampleRateBase - The sample rate base for the device, used for determining sample rates.
        //
        //Returns:
        //    An <MipChannels> object containing the channels that are active in the current MessageFormat
        static MipChannels parseData_MessageFormat(const GenericMipCmdResponse& response, uint8 descSet, uint16 sampleRateBase);

        //Function: parseData_ContinuousDataStream
        //    Parses the data from a ContinuousDataStream response
        //
        //Parameters:
        //    response - The <GenericMipCmdResponse> that contains the data to be parsed
        //
        //Returns:
        //    true if the data stream is enabled, false if it is disabled.
        static bool parseData_ContinuousDataStream(const GenericMipCmdResponse& response);

        //Function: parseData_EulerAngles
        //    Parses the data from a command response containing just 3 Euler Angles (roll, pitch, yaw).
        //
        //Parameters:
        //    response - The <GenericMipCmdResponse> that contains the data to be parsed
        //
        //Returns:
        //    The <EulerAngles> containing the result that is parsed.
        static EulerAngles parseData_EulerAngles(const GenericMipCmdResponse& response);

        //Function: parseData_PositionOffset
        //    Parses the data from a command response containing just 3 Position Offset values (x, y, z).
        //
        //Parameters:
        //    response - The <GenericMipCmdResponse> that contains the data to be parsed
        //
        //Returns:
        //    The <EulerAngles> containing the result that is parsed.
        static PositionOffset parseData_PositionOffset(const GenericMipCmdResponse& response);

        //Function: parseData_ZuptControl
        //    Parses the data from a command response containing the response for a ZUPT field.
        //
        //Parameters:
        //    response - The <GenericMipCmdResponse> that contains the data to be parsed
        //
        //Returns:
        //    The <ZUPTSettingsData> containing the result that is parsed.
        static ZUPTSettingsData parseData_ZUPTControl(const GenericMipCmdResponse& response);
    };
}