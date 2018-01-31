/*******************************************************************************
Copyright(c) 2015-2018 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "mscl/MicroStrain/Wireless/WirelessModels.h"
#include "mscl/MicroStrain/Wireless/WirelessTypes.h"

namespace mscl
{
    class ChannelMask;

    //Class: InputRange
    //    Contains functions specific to input range for Wireless Nodes.
    class InputRange
    {
    private:
        //Typedef: InputRangeMap
        //  typedef for a map of uint16 eeprom values to <WirelessTypes::InputRange> values.
        typedef std::map<uint16, WirelessTypes::InputRange> InputRangeMap;

    public:
        static const InputRangeMap RANGES_SGLINK;
        static const InputRangeMap RANGES_SGLINK_OEM;
        static const InputRangeMap RANGES_SGLINK_HERMETIC;
        static const InputRangeMap RANGES_SGLINK_RGD;
        static const InputRangeMap RANGES_SHMLINK;
        static const InputRangeMap RANGES_VLINK;
        static const InputRangeMap RANGES_VLINK200_FULLDIFF_CHS;
        static const InputRangeMap RANGES_VLINK200_SINGLEENDED_CHS;
        static const InputRangeMap RANGES_TCLINK;
        static const InputRangeMap RANGES_ENVLINK_PRO_TEMPERATURE_CHS;
        static const InputRangeMap RANGES_ENVLINK_PRO_VOLTAGE_CHS;
        static const InputRangeMap RANGES_MVPVLINK;
        static const InputRangeMap RANGES_GLINK200;
        static const InputRangeMap RANGES_GLINK200_40G;

    private:
        //Function: getRangeMap
        //  Gets the <InputRangeMap> for the specified node and channel type.
        //
        //Parameters:
        //  nodeType - The <WirelessModels::NodeModel> to get the map for.
        //  channelType - The <WirelessTypes::ChannelType> of the channel to get the map for.
        //
        //Returns:
        //  The <InputRangeMap> for the requested parameters.
        //
        //Exceptions:
        //  - <Error_NotSupported>: Input Range map was not found for the requested node type and channel type.
        static const InputRange::InputRangeMap& getRangeMap(WirelessModels::NodeModel nodeType, WirelessTypes::ChannelType channelType);

    public:
        //Function: inputRangeToEepromVal
        //  Converts a <WirelessTypes::InputRange> to the hardware gain eeprom value that corresponds to it.
        //
        //Parameters:
        //  range - The <WirelessTypes::InputRange> to convert.
        //  nodeType - The <WirelessModels::NodeModel> to use in converting.
        //  channelType - The <WirelessTypes::ChannelType> to use in converting.
        //
        //Returns:
        //  The eeprom value that corresponds to the given range.
        //
        //Exceptions:
        //  - <Error_NotSupported>: The provided InputRange is invalid for the node type and channel type.
        static uint16 inputRangeToEepromVal(WirelessTypes::InputRange range, WirelessModels::NodeModel nodeType, WirelessTypes::ChannelType channelType);

        //Function: eepromValToInputRange
        //  Converts an eeprom value to the corresponding <WirelessTypes::InputRange>.
        //
        //Parameters:
        //  eepromValue - The eeprom value to convert.
        //  nodeType - The <WirelessModels::NodeModel> to use in converting.
        //  channelType - The <WirelessTypes::ChannelType> to use in converting.
        //
        //Returns:
        //  The <WirelessTypes::InputRange> found, or <WirelessTypres::InputRange::range_invalid> if not found.
        static WirelessTypes::InputRange eepromValToInputRange(uint16 eepromValue, WirelessModels::NodeModel nodeType, WirelessTypes::ChannelType channelType);

        //Function: getRangeVector
        //  Gets a <WirelessTypes::InputRanges> container for the provided node type and channel type.
        //
        //Parameters:
        //  nodeType - The <WirelessModels::NodeModel> to get the ranges for.
        //  channelType - The <WirelessTypes::ChannelType> to get the ranges for.
        //  result - An empty <WirelessTypes::InputRanges> container that will be populated with the supported ranges.
        static void getRangeVector(WirelessModels::NodeModel nodeType, WirelessTypes::ChannelType channelType, WirelessTypes::InputRanges& result);
    };
}