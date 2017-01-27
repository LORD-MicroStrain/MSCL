/*******************************************************************************
Copyright(c) 2015-2017 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "GenericInertialCommand.h"
#include "mscl/MicroStrain/Inertial/EulerAngles.h"
#include "mscl/MicroStrain/Inertial/InertialChannel.h"
#include "mscl/MicroStrain/Inertial/InertialTypes.h"
#include "mscl/MicroStrain/Inertial/PositionOffset.h"
#include "GetDeviceInfo.h"

namespace mscl
{
    //Class: Inertial_Commands
    //    Contains helper functions for Inertial Commands
    class Inertial_Commands
    {
    public:
        //Enums: InertialCmdSelector
        //    The possible command function selectors for Inertial commands
        //
        //    cmd_setCurrent                - 0x01 - Use new settings as the current settings
        //    cmd_getCurrent                - 0x02 - Read back the current settings
        //    cmd_saveCurrentAsStartup    - 0x03 - Save the current settings as the startup settings
        //    cmd_loadSavedToCurrent        - 0x04 - Load the saved startup settings as the current settings
        //    cmd_resetCurrentToDefault    - 0x05 - Reset the current settings to the factory default settings
        enum InertialCmdSelector
        {
            cmd_setCurrent = 0x01,
            cmd_getCurrent = 0x02,
            cmd_saveCurrentAsStartup = 0x03,
            cmd_loadSavedToCurrent = 0x04,
            cmd_resetCurrentToDefault = 0x05
        };

    public:
        //Function: parseData_singleBool
        //    Parses the data for a single boolean flag response.
        //
        //Parameters:
        //    response - The <GenericInertialCommandResponse> that contains the data to be parsed.
        //
        //Returns:
        //    The boolean parsed from the response.
        static bool parseData_singleBool(const GenericInertialCommandResponse& response);

        //Function: parseData_GetDeviceInfo
        //    Parses the data from a GetDeviceInfo response.
        //
        //Parameters:
        //    response - The <GenericInertialCommandResponse> that contains the data to be parsed.
        //    result - Holds the <InertialDeviceInfo> result.
        static void parseData_GetDeviceInfo(const GenericInertialCommandResponse& response, InertialDeviceInfo& result);

        //Function: parseData_GetDeviceDescriptorSets
        //    Parses the data from a GetDeviceDescriptorSets response.
        //
        //Parameters:
        //    response - The <GenericInertialCommandResponse> that contains the data to be parsed.
        //    result - Holds the descriptor sets result.
        static void parseData_GetDeviceDescriptorSets(const GenericInertialCommandResponse& response, std::vector<uint16>& result);

        //Function: parseData_DataRateBase
        //    Parses the data from a DataRateBase response
        //
        //Parameters:
        //    response - The <GenericInertialCommandResponse> that contains the data to be parsed
        //
        //Returns:
        //    The data rate base parsed from the response
        static uint16 parseData_DataRateBase(const GenericInertialCommandResponse& response);

        //Function: parseData_CommunicationMode
        //    Parses the data from a CommunicationMode response
        //
        //Parameters:
        //    response - The <GenericInertialCommandResponse> that contains the data to be parsed
        //
        //Returns:
        //    The data rate base parsed from the response
        static uint8 parseData_CommunicationMode(const GenericInertialCommandResponse& response);

        //Function: parseData_MessageFormat
        //    Parses the data from a MessageFormat response
        //
        //Parameters:
        //    response - The <GenericInertialCommandResponse> that contains the data to be parsed
        //    descSet - The descriptor set byte for this specific MessageFormat command
        //    sampleRateBase - The sample rate base for the device, used for determining sample rates.
        //
        //Returns:
        //    An <InertialChannels> object containing the channels that are active in the current MessageFormat
        static InertialChannels parseData_MessageFormat(const GenericInertialCommandResponse& response, uint8 descSet, uint16 sampleRateBase);

        //Function: parseData_ContinuousDataStream
        //    Parses the data from a ContinuousDataStream response
        //
        //Parameters:
        //    response - The <GenericInertialCommandResponse> that contains the data to be parsed
        //
        //Returns:
        //    true if the data stream is enabled, false if it is disabled.
        static bool parseData_ContinuousDataStream(const GenericInertialCommandResponse& response);

        //Function: parseData_EulerAngles
        //    Parses the data from a command response containing just 3 Euler Angles (roll, pitch, yaw).
        //
        //Parameters:
        //    response - The <GenericInertialCommandResponse> that contains the data to be parsed
        //
        //Returns:
        //    The <EulerAngles> containing the result that is parsed.
        static EulerAngles parseData_EulerAngles(const GenericInertialCommandResponse& response);

        //Function: parseData_PositionOffset
        //    Parses the data from a command response containing just 3 Position Offset values (x, y, z).
        //
        //Parameters:
        //    response - The <GenericInertialCommandResponse> that contains the data to be parsed
        //
        //Returns:
        //    The <EulerAngles> containing the result that is parsed.
        static PositionOffset parseData_PositionOffset(const GenericInertialCommandResponse& response);
    };
}