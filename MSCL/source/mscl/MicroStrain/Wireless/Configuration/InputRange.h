/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "mscl/MicroStrain/Wireless/WirelessModels.h"
#include "mscl/MicroStrain/Wireless/WirelessTypes.h"

namespace mscl
{
    class ChannelMask;

    //API Struct: InputRangeEntry
    // struct for Input Range options that specify an input range and associated gain for a channel
    struct InputRangeEntry
    {
        //API Variable: inputRange
        //  The <WirelessTypes::InputRange> enum value for the input voltage range
        WirelessTypes::InputRange inputRange;

        //API Variable: hasGain
        // bool indicating whether or not this input range option has a valid associated gain
        bool hasGain;

        //API Variable: gain
        // the gain for this input range
        float gain;

        //API Constructor: InputRangeEntry
        // creates an InputRangeEntry with inputRange = range_invalid, hasGain = false, and gain = 0
        InputRangeEntry() :
            inputRange(WirelessTypes::range_invalid),
            hasGain(false),
            gain(0)
        { }

        //API Constructor: InputRangeEntry
        //  creates an InputRangeEntry with inputRange = ir, hasGain = false and gain = 0
        InputRangeEntry(WirelessTypes::InputRange ir) :
            inputRange(ir),
            hasGain(false),
            gain(0)
        { }

        //API Constructor: InputRangeEntry
        //  creates an InputRangeEntry with inputRange = ir, hasGain = true and gain = g
        InputRangeEntry(WirelessTypes::InputRange ir, float g) :
            inputRange(ir),
            hasGain(true),
            gain(g)
        { }
    };

    //API Typedef: InputRanges
    //  A vector of <InputRangeEntry> objects.
    typedef std::vector<InputRangeEntry> InputRanges;

#ifndef SWIG
    //Class: InputRangeHelper
    //    Contains functions specific to input range for Wireless Nodes.
    class InputRangeHelper
    {
    private:
        //Typedef: InputRangeMap
        //  typedef for a map of uint16 eeprom values to <WirelessTypes::InputRange> values.
        typedef std::map<uint16, InputRangeEntry> InputRangeMap;

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
        static const InputRangeMap RANGES_GLINK200;
        static const InputRangeMap RANGES_GLINK200_40G;
        static const InputRangeMap RANGES_SGLINK200_FULLDIFF_CHS_2500mV;
        static const InputRangeMap RANGES_SGLINK200_FULLDIFF_CHS_1500mV;
        static const InputRangeMap RANGES_SGLINK200_SINGLEENDED_CHS_2500mV;
        static const InputRangeMap RANGES_SGLINK200_SINGLEENDED_CHS_1500mV;
        static const InputRangeMap RANGES_TCLINK_200_OEM;
        static const InputRangeMap RANGES_TCLINK_200;
        static const InputRangeMap RANGES_RTDLINK_200;

    private:
        //Function: getRangeMap
        //  Gets the <InputRangeMap> for the specified node and channel type.
        //
        //Parameters:
        //  nodeType - The <WirelessModels::NodeModel> to get the map for.
        //  channelType - The <WirelessTypes::ChannelType> of the channel to get the map for.
        //  excitationVoltage - The Excitation <WirelessTypes::Voltage>, if necessary for the Node.
        //
        //Returns:
        //  The <InputRangeMap> for the requested parameters.
        //
        //Exceptions:
        //  - <Error_NotSupported>: Input Range map was not found for the requested node type and channel type.
        static const InputRangeMap& getRangeMap(WirelessModels::NodeModel nodeType,
                                                WirelessTypes::ChannelType channelType,
                                                WirelessTypes::Voltage excitationVoltage = static_cast<WirelessTypes::Voltage>(0));

    public:
        //Function: inputRangeToEepromVal
        //  Converts a <WirelessTypes::InputRange> to the eeprom value that corresponds to it.
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

        //Function: inputRangeToEepromVal
        //  Converts a <WirelessTypes::InputRange> to the eeprom value that corresponds to it, given the excitation voltage.
        static uint16 inputRangeToEepromVal(WirelessTypes::InputRange range, WirelessModels::NodeModel nodeType, WirelessTypes::ChannelType channelType, WirelessTypes::Voltage excitationVoltage);

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

        //Function: eepromValToInputRange
        //  Converts an eeprom value to the corresponding <WirelessTypes::InputRange>, given the excitation voltage.
        static WirelessTypes::InputRange eepromValToInputRange(uint16 eepromValue, WirelessModels::NodeModel nodeType, WirelessTypes::ChannelType channelType, WirelessTypes::Voltage excitationVoltage);

        //Function: getRangeVector
        //  Gets a <WirelessTypes::InputRanges> container for the provided node type and channel type.
        //
        //Parameters:
        //  nodeType - The <WirelessModels::NodeModel> to get the ranges for.
        //  channelType - The <WirelessTypes::ChannelType> to get the ranges for.
        //  result - An empty <WirelessTypes::InputRanges> container that will be populated with the supported ranges.
        static void getRangeVector(WirelessModels::NodeModel nodeType, WirelessTypes::ChannelType channelType, InputRanges& result);

        //Function: getRangeVector
        //  Gets a <WirelessTypes::InputRanges> container for the provided node type, channel type, and excitation voltage.
        static void getRangeVector(WirelessModels::NodeModel nodeType, WirelessTypes::ChannelType channelType, WirelessTypes::Voltage excitationVoltage, InputRanges& result);
    };
#endif
}