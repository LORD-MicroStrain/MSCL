/*******************************************************************************
Copyright(c) 2015-2016 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"
#include "InputRange.h"

#include "mscl/Utils.h"

namespace mscl
{
    const InputRange::InputRangeMap InputRange::RANGES_SGLINK = {
        {14, WirelessTypes::range_14mV},
        {20, WirelessTypes::range_10mV},
        {27, WirelessTypes::range_7mV},
        {51, WirelessTypes::range_4mV},
        {103, WirelessTypes::range_2mV},
        {137, WirelessTypes::range_1500microV},
        {207, WirelessTypes::range_1mV},
        {255, WirelessTypes::range_812microV}
    };

    const InputRange::InputRangeMap InputRange::RANGES_SGLINK_OEM = {
        {0, WirelessTypes::range_75mV},
        {1, WirelessTypes::range_37mV},
        {2, WirelessTypes::range_18mV},
        {3, WirelessTypes::range_9mV},
        {4, WirelessTypes::range_4mV},
        {5, WirelessTypes::range_2mV},
        {6, WirelessTypes::range_1mV},
        {7, WirelessTypes::range_586microV}
    };

    const InputRange::InputRangeMap InputRange::RANGES_SGLINK_HERMETIC = {
        {0, WirelessTypes::range_70mV},
        {1, WirelessTypes::range_35mV},
        {2, WirelessTypes::range_17mV},
        {3, WirelessTypes::range_8mV},
        {4, WirelessTypes::range_4mV},
        {5, WirelessTypes::range_2mV},
        {6, WirelessTypes::range_1mV},
        {7, WirelessTypes::range_547microV}
    };

    const InputRange::InputRangeMap InputRange::RANGES_SGLINK_RGD = {
        {0, WirelessTypes::range_44mV},
        {6, WirelessTypes::range_30mV},
        {16, WirelessTypes::range_20mV},
        {27, WirelessTypes::range_15mV},
        {47, WirelessTypes::range_10mV},
        {108, WirelessTypes::range_5mV},
        {189, WirelessTypes::range_3mV},
        {255, WirelessTypes::range_2mV}
    };

    const InputRange::InputRangeMap InputRange::RANGES_SHMLINK = {
        {0, WirelessTypes::range_10mV},
        {12, WirelessTypes::range_6mV},
        {23, WirelessTypes::range_5mV},
        {54, WirelessTypes::range_3mV},
        {92, WirelessTypes::range_2mV},
        {207, WirelessTypes::range_1mV}
    };

    const InputRange::InputRangeMap InputRange::RANGES_VLINK = {
        {5, WirelessTypes::range_70mV},
        {76, WirelessTypes::range_50mV},
        {184, WirelessTypes::range_20mV},
        {219, WirelessTypes::range_10mV},
        {237, WirelessTypes::range_5mV},
        {246, WirelessTypes::range_2mV},
        {251, WirelessTypes::range_1mV},
        {253, WirelessTypes::range_600microV},
        {254, WirelessTypes::range_350microV},
        {255, WirelessTypes::range_100microV}
    };

    const InputRange::InputRangeMap InputRange::RANGES_VLINK200_FULLDIFF_CHS = {
        {0, WirelessTypes::range_156mV},
        {1, WirelessTypes::range_78mV},
        {2, WirelessTypes::range_39mV},
        {3, WirelessTypes::range_19mV},
        {4, WirelessTypes::range_9mV},
        {5, WirelessTypes::range_4mV},
        {6, WirelessTypes::range_2mV},
        {7, WirelessTypes::range_1mV}
    };

    const InputRange::InputRangeMap InputRange::RANGES_VLINK200_SINGLEENDED_CHS = {
        {0, WirelessTypes::range_10V},
        {1, WirelessTypes::range_5V},
        {2, WirelessTypes::range_2V},
        {5, WirelessTypes::range_0to10V},
        {6, WirelessTypes::range_0to5V}
    };

    const InputRange::InputRangeMap InputRange::RANGES_TCLINK = {
        {0, WirelessTypes::range_1V},
        {1, WirelessTypes::range_585mV},
        {2, WirelessTypes::range_292mV},
        {3, WirelessTypes::range_146mV},
        {4, WirelessTypes::range_73mV},
        {5, WirelessTypes::range_36mV},
        {6, WirelessTypes::range_18mV},
        {7, WirelessTypes::range_9mV}
    };

    const InputRange::InputRangeMap InputRange::RANGES_ENVLINK_PRO_TEMPERATURE_CHS = {
        {0, WirelessTypes::range_1V},
        {1, WirelessTypes::range_585mV},
        {2, WirelessTypes::range_292mV},
        {3, WirelessTypes::range_146mV},
        {4, WirelessTypes::range_73mV},
        {5, WirelessTypes::range_36mV},
        {6, WirelessTypes::range_18mV},
        {7, WirelessTypes::range_9mV}
    };

    const InputRange::InputRangeMap InputRange::RANGES_ENVLINK_PRO_VOLTAGE_CHS = {
        {0, WirelessTypes::range_5V},
        {1, WirelessTypes::range_2V},
        {2, WirelessTypes::range_1V},
        {3, WirelessTypes::range_731mV},
        {4, WirelessTypes::range_365mV},
        {5, WirelessTypes::range_182mV},
        {6, WirelessTypes::range_91mV},
        {7, WirelessTypes::range_45mV}
    };

    const InputRange::InputRangeMap InputRange::RANGES_MVPVLINK = {
        {0, WirelessTypes::range_62mV},
        {1, WirelessTypes::range_31mV},
        {2, WirelessTypes::range_15mV},
        {3, WirelessTypes::range_7mV},
        {4, WirelessTypes::range_3mV},
        {5, WirelessTypes::range_1mV},
        {6, WirelessTypes::range_976microV},
        {7, WirelessTypes::range_488microV}
    };

    const InputRange::InputRangeMap& InputRange::getRangeMap(WirelessModels::NodeModel nodeType, WirelessTypes::ChannelType channelType)
    {
        switch(nodeType)
        {
            case WirelessModels::node_sgLink:
                return RANGES_SGLINK;

            case WirelessModels::node_sgLink_oem:
            case WirelessModels::node_sgLink_oem_S:
            case WirelessModels::node_sgLink_micro:
            case WirelessModels::node_torqueLink:
                return RANGES_SGLINK_OEM;

            case WirelessModels::node_sgLink_herm:
            case WirelessModels::node_sgLink_herm_2600:
            case WirelessModels::node_sgLink_herm_2700:
            case WirelessModels::node_sgLink_herm_2800:
                return RANGES_SGLINK_HERMETIC;

            case WirelessModels::node_sgLink_rgd:
                return RANGES_SGLINK_RGD;

            case WirelessModels::node_shmLink:
                return RANGES_SHMLINK;

            case WirelessModels::node_vLink:
            case WirelessModels::node_vLink_legacy:
                return RANGES_VLINK;

            case WirelessModels::node_vLink200:
            case WirelessModels::node_vLink200_qbridge_1K:
            case WirelessModels::node_vLink200_qbridge_120:
            case WirelessModels::node_vLink200_qbridge_350:
            case WirelessModels::node_vLink200_hbridge_1K:
            case WirelessModels::node_vLink200_hbridge_120:
            case WirelessModels::node_vLink200_hbridge_350:
                if(channelType == WirelessTypes::chType_fullDifferential)
                {
                    return RANGES_VLINK200_FULLDIFF_CHS;
                }
                else if(channelType == WirelessTypes::chType_singleEnded)
                {
                    return RANGES_VLINK200_SINGLEENDED_CHS;
                }

            case WirelessModels::node_tcLink_1ch:
            case WirelessModels::node_tcLink_3ch:
            case WirelessModels::node_tcLink_6ch:
            case WirelessModels::node_tcLink_6ch_ip67:
            case WirelessModels::node_tcLink_6ch_ip67_rht:
            case WirelessModels::node_envLink_mini:
            case WirelessModels::node_rtdLink:
                return RANGES_TCLINK;

            case WirelessModels::node_envLink_pro:
                if(channelType == WirelessTypes::chType_diffTemperature)
                {
                    return RANGES_ENVLINK_PRO_TEMPERATURE_CHS;
                }
                else if(channelType == WirelessTypes::chType_voltage)
                {
                    return RANGES_ENVLINK_PRO_VOLTAGE_CHS;
                }

            case WirelessModels::node_mvPerVLink:
                return RANGES_MVPVLINK;
        }

        throw Error_NotSupported("Invalid Node Type");
    }

    uint16 InputRange::inputRangeToEepromVal(WirelessTypes::InputRange range, WirelessModels::NodeModel nodeType, WirelessTypes::ChannelType channelType)
    {
        const InputRangeMap& ranges = getRangeMap(nodeType, channelType);

        for(auto& r : ranges)
        {
            if(r.second == range)
            {
                return r.first;
            }
        }

        throw Error_NotSupported("Invalid Input Range Value");
    }

    WirelessTypes::InputRange InputRange::eepromValToInputRange(uint16 eepromValue, WirelessModels::NodeModel nodeType, WirelessTypes::ChannelType channelType)
    {
        const InputRangeMap& ranges = getRangeMap(nodeType, channelType);

        try
        {
            return ranges.at(eepromValue);
        }
        catch(std::out_of_range&)
        {
            return WirelessTypes::range_invalid;
        }
    }

    void InputRange::getRangeVector(WirelessModels::NodeModel nodeType, WirelessTypes::ChannelType channelType, WirelessTypes::InputRanges& result)
    {
        const auto& rangeMap = getRangeMap(nodeType, channelType);

        for(auto& range : rangeMap)
        {
            result.push_back(range.second);
        }
    }
}