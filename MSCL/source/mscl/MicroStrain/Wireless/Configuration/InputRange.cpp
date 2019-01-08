/*******************************************************************************
Copyright(c) 2015-2019 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"
#include "InputRange.h"

#include "mscl/Utils.h"

namespace mscl
{
    const InputRangeHelper::InputRangeMap InputRangeHelper::RANGES_SGLINK = {
        {14, InputRangeEntry(WirelessTypes::range_14_545mV, 103.125f)},
        {20, InputRangeEntry(WirelessTypes::range_10mV, 146.528f)},
        {27, InputRangeEntry(WirelessTypes::range_7_608mV, 197.164f)},
        {51, InputRangeEntry(WirelessTypes::range_4_046mV, 370.775f)},
        {103, InputRangeEntry(WirelessTypes::range_2_008mV, 746.933f)},
        {137, InputRangeEntry(WirelessTypes::range_1_511mV, 992.882f)},
        {207, InputRangeEntry(WirelessTypes::range_1_001mV, 1499.248f)},
        {255, InputRangeEntry(WirelessTypes::range_0_812mV, 1846.470f)}
    };

    const InputRangeHelper::InputRangeMap InputRangeHelper::RANGES_SGLINK_OEM = {
        {0, InputRangeEntry(WirelessTypes::range_75mV, 20.0f)},
        {1, InputRangeEntry(WirelessTypes::range_37_5mV, 40.0f)},
        {2, InputRangeEntry(WirelessTypes::range_18_75mV, 80.0f)},
        {3, InputRangeEntry(WirelessTypes::range_9_38mV, 160.0f)},
        {4, InputRangeEntry(WirelessTypes::range_4_69mV, 320.0f)},
        {5, InputRangeEntry(WirelessTypes::range_2_34mV, 640.0f)},
        {6, InputRangeEntry(WirelessTypes::range_1_17mV, 1280.0f)},
        {7, InputRangeEntry(WirelessTypes::range_0_586mV, 2560.0f)}
    };

    const InputRangeHelper::InputRangeMap InputRangeHelper::RANGES_SGLINK_HERMETIC = {
        {0, InputRangeEntry(WirelessTypes::range_70mV, 20.0f)},
        {1, InputRangeEntry(WirelessTypes::range_35mV, 40.0f)},
        {2, InputRangeEntry(WirelessTypes::range_17_5mV, 80.0f)},
        {3, InputRangeEntry(WirelessTypes::range_8_75mV, 160.0f)},
        {4, InputRangeEntry(WirelessTypes::range_4_38mV, 320.0f)},
        {5, InputRangeEntry(WirelessTypes::range_2_19mV, 640.0f)},
        {6, InputRangeEntry(WirelessTypes::range_1_09mV, 1280.0f)},
        {7, InputRangeEntry(WirelessTypes::range_0_547mV, 2560.0f)}
    };

    const InputRangeHelper::InputRangeMap InputRangeHelper::RANGES_SGLINK_RGD = {
        {0, InputRangeEntry(WirelessTypes::range_44mV, 30.5f)},
        {6, InputRangeEntry(WirelessTypes::range_30mV, 43.789f)},
        {16, InputRangeEntry(WirelessTypes::range_20mV, 65.939f)},
        {27, InputRangeEntry(WirelessTypes::range_15mV, 90.304f)},
        {47, InputRangeEntry(WirelessTypes::range_10mV, 134.603f)},
        {108, InputRangeEntry(WirelessTypes::range_5mV, 269.716f)},
        {189, InputRangeEntry(WirelessTypes::range_3mV, 446.127f)},
        {255, InputRangeEntry(WirelessTypes::range_2mV, 595.315f)}
    };

    const InputRangeHelper::InputRangeMap InputRangeHelper::RANGES_SHMLINK = {
        {0, InputRangeEntry(WirelessTypes::range_10mV, 134.882f)},
        {12, InputRangeEntry(WirelessTypes::range_6mV, 199.558f)},
        {23, InputRangeEntry(WirelessTypes::range_5mV, 264.294f)},
        {54, InputRangeEntry(WirelessTypes::range_3mV, 446.647f)},
        {92, InputRangeEntry(WirelessTypes::range_2mV, 670.176f)},
        {207, InputRangeEntry(WirelessTypes::range_1mV, 1346.647f)}
    };

    const InputRangeHelper::InputRangeMap InputRangeHelper::RANGES_VLINK = {
        {5, InputRangeEntry(WirelessTypes::range_70mV, 21.0f)},
        {76, InputRangeEntry(WirelessTypes::range_50mV, 30.0f)},
        {184, InputRangeEntry(WirelessTypes::range_20mV, 75.0f)},
        {219, InputRangeEntry(WirelessTypes::range_10mV, 147.0f)},
        {237, InputRangeEntry(WirelessTypes::range_5mV, 291.0f)},
        {246, InputRangeEntry(WirelessTypes::range_2_5mV, 569.0f)},
        {251, InputRangeEntry(WirelessTypes::range_1mV, 1214.0f)},
        {253, InputRangeEntry(WirelessTypes::range_0_6mV, 2222.0f)},
        {254, InputRangeEntry(WirelessTypes::range_0_35mV, 3799.0f)},
        {255, InputRangeEntry(WirelessTypes::range_0_1mV, 13074.0f)}
    };

    const InputRangeHelper::InputRangeMap InputRangeHelper::RANGES_VLINK200_FULLDIFF_CHS = {
        {0, InputRangeEntry(WirelessTypes::range_156mV, 16.0f)},
        {1, InputRangeEntry(WirelessTypes::range_78_1mV, 32.0f)},
        {2, InputRangeEntry(WirelessTypes::range_39mV, 64.0f)},
        {3, InputRangeEntry(WirelessTypes::range_19_5mV, 128.0f)},
        {4, InputRangeEntry(WirelessTypes::range_9_76mV, 256.0f)},
        {5, InputRangeEntry(WirelessTypes::range_4_88mV, 512.0f)},
        {6, InputRangeEntry(WirelessTypes::range_2_44mV, 1024.0f)},
        {7, InputRangeEntry(WirelessTypes::range_1_22mV, 2048.0f)}
    };

    const InputRangeHelper::InputRangeMap InputRangeHelper::RANGES_VLINK200_SINGLEENDED_CHS = {
        {0, InputRangeEntry(WirelessTypes::range_10_24V)},
        {1, InputRangeEntry(WirelessTypes::range_5_12V)},
        {2, InputRangeEntry(WirelessTypes::range_2_56V)},
        {5, InputRangeEntry(WirelessTypes::range_0to10_24V)},
        {6, InputRangeEntry(WirelessTypes::range_0to5_12V)}
    };

    const InputRangeHelper::InputRangeMap InputRangeHelper::RANGES_TCLINK = {
        {0, InputRangeEntry(WirelessTypes::range_1_147V)},
        {1, InputRangeEntry(WirelessTypes::range_585mV)},
        {2, InputRangeEntry(WirelessTypes::range_292_5mV)},
        {3, InputRangeEntry(WirelessTypes::range_146_25mV)},
        {4, InputRangeEntry(WirelessTypes::range_73_13mV)},
        {5, InputRangeEntry(WirelessTypes::range_36_56mV)},
        {6, InputRangeEntry(WirelessTypes::range_18_23mV)},
        {7, InputRangeEntry(WirelessTypes::range_9_14mV)}
    };

    const InputRangeHelper::InputRangeMap InputRangeHelper::RANGES_ENVLINK_PRO_TEMPERATURE_CHS = {
        {0, InputRangeEntry(WirelessTypes::range_1_147V)},
        {1, InputRangeEntry(WirelessTypes::range_585mV)},
        {2, InputRangeEntry(WirelessTypes::range_292_5mV)},
        {3, InputRangeEntry(WirelessTypes::range_146_25mV)},
        {4, InputRangeEntry(WirelessTypes::range_73_13mV)},
        {5, InputRangeEntry(WirelessTypes::range_36_56mV)},
        {6, InputRangeEntry(WirelessTypes::range_18_23mV)},
        {7, InputRangeEntry(WirelessTypes::range_9_14mV)}
    };

    const InputRangeHelper::InputRangeMap InputRangeHelper::RANGES_ENVLINK_PRO_VOLTAGE_CHS = {
        {0, InputRangeEntry(WirelessTypes::range_5_74V)},
        {1, InputRangeEntry(WirelessTypes::range_2_93V)},
        {2, InputRangeEntry(WirelessTypes::range_1_46V)},
        {3, InputRangeEntry(WirelessTypes::range_731_3mV)},
        {4, InputRangeEntry(WirelessTypes::range_365_6mV)},
        {5, InputRangeEntry(WirelessTypes::range_182_8mV)},
        {6, InputRangeEntry(WirelessTypes::range_91_4mV)},
        {7, InputRangeEntry(WirelessTypes::range_45_7mV)}
    };

    const InputRangeHelper::InputRangeMap InputRangeHelper::RANGES_MVPVLINK = {
        {0, InputRangeEntry(WirelessTypes::range_62_5mV, 20.0f)},
        {1, InputRangeEntry(WirelessTypes::range_31_25mV, 40.0f)},
        {2, InputRangeEntry(WirelessTypes::range_15_63mV, 80.0f)},
        {3, InputRangeEntry(WirelessTypes::range_7_81mV, 160.0f)},
        {4, InputRangeEntry(WirelessTypes::range_3_91mV, 320.0f)},
        {5, InputRangeEntry(WirelessTypes::range_1_95mV, 640.0f)},
        {6, InputRangeEntry(WirelessTypes::range_0_976mV, 1280.0f)},
        {7, InputRangeEntry(WirelessTypes::range_0_488mV, 2560.0f)}
    };

    const InputRangeHelper::InputRangeMap InputRangeHelper::RANGES_GLINK200 = {
        {1, InputRangeEntry(WirelessTypes::range_2G)},
        {2, InputRangeEntry(WirelessTypes::range_4G)},
        {3, InputRangeEntry(WirelessTypes::range_8G)}
    };

    const InputRangeHelper::InputRangeMap InputRangeHelper::RANGES_GLINK200_40G = {
        {1, InputRangeEntry(WirelessTypes::range_10G)},
        {2, InputRangeEntry(WirelessTypes::range_20G)},
        {3, InputRangeEntry(WirelessTypes::range_40G)}
    };

    const InputRangeHelper::InputRangeMap InputRangeHelper::RANGES_SGLINK200_FULLDIFF_CHS_2500mV = {
        {0, InputRangeEntry(WirelessTypes::range_2_5V, 1.0f)},
        {1, InputRangeEntry(WirelessTypes::range_1_25V, 2.0f)},
        {2, InputRangeEntry(WirelessTypes::range_625mV, 4.0f)},
        {3, InputRangeEntry(WirelessTypes::range_312_5mV, 8.0f)},
        {4, InputRangeEntry(WirelessTypes::range_156_25mV, 16.0f)},
        {5, InputRangeEntry(WirelessTypes::range_78_125mV, 32.0f)},
        {6, InputRangeEntry(WirelessTypes::range_39_063mV, 64.0f)},
        {7, InputRangeEntry(WirelessTypes::range_19_532mV, 128.0f)}
    };

    const InputRangeHelper::InputRangeMap InputRangeHelper::RANGES_SGLINK200_FULLDIFF_CHS_1500mV = {
        {0, InputRangeEntry(WirelessTypes::range_1_5V, 1.0f)},
        {1, InputRangeEntry(WirelessTypes::range_750mV, 2.0f)},
        {2, InputRangeEntry(WirelessTypes::range_375mV, 4.0f)},
        {3, InputRangeEntry(WirelessTypes::range_187_5mV, 8.0f)},
        {4, InputRangeEntry(WirelessTypes::range_93_75mV, 16.0f)},
        {5, InputRangeEntry(WirelessTypes::range_46_875mV, 32.0f)},
        {6, InputRangeEntry(WirelessTypes::range_23_438mV, 64.0f)},
        {7, InputRangeEntry(WirelessTypes::range_11_719mV, 128.0f)}
    };

    const InputRangeHelper::InputRangeMap InputRangeHelper::RANGES_SGLINK200_SINGLEENDED_CHS_2500mV = {
        {0, InputRangeEntry(WirelessTypes::range_0to2_5V)},
        {1, InputRangeEntry(WirelessTypes::range_0to1_25V)},
        {2, InputRangeEntry(WirelessTypes::range_0to625mV)},
        {3, InputRangeEntry(WirelessTypes::range_0to312_5mV)},
        {4, InputRangeEntry(WirelessTypes::range_0to156_25mV)},
        {5, InputRangeEntry(WirelessTypes::range_0to78_125mV)},
        {6, InputRangeEntry(WirelessTypes::range_0to39_063mV)},
        {7, InputRangeEntry(WirelessTypes::range_0to19_532mV)}
    };

    const InputRangeHelper::InputRangeMap InputRangeHelper::RANGES_SGLINK200_SINGLEENDED_CHS_1500mV = {
        {0, InputRangeEntry(WirelessTypes::range_0to1_5V)},
        {1, InputRangeEntry(WirelessTypes::range_0to750mV)},
        {2, InputRangeEntry(WirelessTypes::range_0to375mV)},
        {3, InputRangeEntry(WirelessTypes::range_0to187_5mV)},
        {4, InputRangeEntry(WirelessTypes::range_0to93_75mV)},
        {5, InputRangeEntry(WirelessTypes::range_0to46_875mV)},
        {6, InputRangeEntry(WirelessTypes::range_0to23_438mV)},
        {7, InputRangeEntry(WirelessTypes::range_0to11_719mV)}
    };

    const InputRangeHelper::InputRangeMap InputRangeHelper::RANGES_TCLINK_200_OEM = {
        {1, InputRangeEntry(WirelessTypes::range_1_35V_or_0to1000000ohm, 1.0f)},
        {2, InputRangeEntry(WirelessTypes::range_1_25V_or_0to10000ohm, 2.0f)},
        {4, InputRangeEntry(WirelessTypes::range_625mV_or_0to3333_3ohm, 4.0f)},
        {8, InputRangeEntry(WirelessTypes::range_312_5mV_or_0to1428_6ohm, 8.0f)},
        {16, InputRangeEntry(WirelessTypes::range_156_25mV_or_0to666_67ohm, 16.0f)},
        {32, InputRangeEntry(WirelessTypes::range_78_125mV_or_0to322_58ohm, 32.0f)},
        {64, InputRangeEntry(WirelessTypes::range_39_0625mV_or_0to158_73ohm, 64.0f)},
        {128, InputRangeEntry(WirelessTypes::range_19_5313mV_or_0to78_74ohm, 128.0f)}
    };

    const InputRangeHelper::InputRangeMap InputRangeHelper::RANGES_TCLINK_200 = {
        {1, InputRangeEntry(WirelessTypes::range_1_35V, 1.0f)},
        {2, InputRangeEntry(WirelessTypes::range_1_25V, 2.0f)},
        {4, InputRangeEntry(WirelessTypes::range_625mV, 4.0f)},
        {8, InputRangeEntry(WirelessTypes::range_312_5mV, 8.0f)},
        {16, InputRangeEntry(WirelessTypes::range_156_25mV, 16.0f)},
        {32, InputRangeEntry(WirelessTypes::range_78_125mV, 32.0f)},
        {64, InputRangeEntry(WirelessTypes::range_39_063mV, 64.0f)},
        {128, InputRangeEntry(WirelessTypes::range_19_532mV, 128.0f)}
    };

    const InputRangeHelper::InputRangeMap InputRangeHelper::RANGES_RTDLINK_200 = {
        {1, InputRangeEntry(WirelessTypes::range_0to1000000ohm, 1.0f)},
        {2, InputRangeEntry(WirelessTypes::range_0to10000ohm, 2.0f)},
        {4, InputRangeEntry(WirelessTypes::range_0to3333_3ohm, 4.0f)},
        {8, InputRangeEntry(WirelessTypes::range_0to1428_6ohm, 8.0f)},
        {16, InputRangeEntry(WirelessTypes::range_0to666_67ohm, 16.0f)},
        {32, InputRangeEntry(WirelessTypes::range_0to322_58ohm, 32.0f)},
        {64, InputRangeEntry(WirelessTypes::range_0to158_73ohm, 64.0f)},
        {128, InputRangeEntry(WirelessTypes::range_0to78_74ohm, 128.0f)}
    };

    const InputRangeHelper::InputRangeMap& InputRangeHelper::getRangeMap(WirelessModels::NodeModel nodeType, WirelessTypes::ChannelType channelType, WirelessTypes::Voltage excitationVoltage)
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
            case WirelessModels::node_sgLink_herm_2900:
                return RANGES_SGLINK_HERMETIC;

            case WirelessModels::node_sgLink_rgd:
                return RANGES_SGLINK_RGD;

            case WirelessModels::node_sgLink200:
            case WirelessModels::node_sgLink200_hbridge_1K:
            case WirelessModels::node_sgLink200_hbridge_350:
            case WirelessModels::node_sgLink200_hbridge_120:
            case WirelessModels::node_sgLink200_qbridge_1K:
            case WirelessModels::node_sgLink200_qbridge_350:
            case WirelessModels::node_sgLink200_qbridge_120:
            case WirelessModels::node_sgLink200_oem:
            case WirelessModels::node_sgLink200_oem_ufl:
            case WirelessModels::node_sgLink200_oem_hbridge_1K:
            case WirelessModels::node_sgLink200_oem_hbridge_1K_ufl:
            case WirelessModels::node_sgLink200_oem_hbridge_120:
            case WirelessModels::node_sgLink200_oem_hbridge_120_ufl:
            case WirelessModels::node_sgLink200_oem_hbridge_350:
            case WirelessModels::node_sgLink200_oem_hbridge_350_ufl:
            case WirelessModels::node_sgLink200_oem_qbridge_1K:
            case WirelessModels::node_sgLink200_oem_qbridge_1K_ufl:
            case WirelessModels::node_sgLink200_oem_qbridge_120:
            case WirelessModels::node_sgLink200_oem_qbridge_120_ufl:
            case WirelessModels::node_sgLink200_oem_qbridge_350:
            case WirelessModels::node_sgLink200_oem_qbridge_350_ufl:
            case WirelessModels::node_torqueLink200:
            {
                if(channelType == WirelessTypes::chType_fullDifferential)
                {
                    if(excitationVoltage == WirelessTypes::voltage_1500mV)      { return RANGES_SGLINK200_FULLDIFF_CHS_1500mV; }
                    else if(excitationVoltage == WirelessTypes::voltage_2500mV) { return RANGES_SGLINK200_FULLDIFF_CHS_2500mV; }
                }
                else if(channelType == WirelessTypes::chType_singleEnded)
                {
                    if(excitationVoltage == WirelessTypes::voltage_1500mV)      { return RANGES_SGLINK200_SINGLEENDED_CHS_1500mV; }
                    else if(excitationVoltage == WirelessTypes::voltage_2500mV) { return RANGES_SGLINK200_SINGLEENDED_CHS_2500mV; }
                }

                throw Error_NotSupported("Input Range Map not found for this Node or Channel");
            }

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

            case WirelessModels::node_gLink_200_8g:
            case WirelessModels::node_gLink_200_8g_oem:
            case WirelessModels::node_gLink_200_8g_oem_mmcx:
            case WirelessModels::node_gLink_200_40g_oem_mmcx:
            case WirelessModels::node_gLink_200_8g_oem_u_fl:
            case WirelessModels::node_gLink_200_40g_oem_u_fl:
                return RANGES_GLINK200;

            case WirelessModels::node_gLink_200_40g:
            case WirelessModels::node_gLink_200_40g_oem:
                return RANGES_GLINK200_40G;

            case WirelessModels::node_tcLink200_oem:
            case WirelessModels::node_tcLink200_oem_ufl:
                return RANGES_TCLINK_200_OEM;

            case WirelessModels::node_tcLink200:
                return RANGES_TCLINK_200;

            case WirelessModels::node_rtdLink200:
                return RANGES_RTDLINK_200;

            default:
                break;
        }

        throw Error_NotSupported("Input Range Map not found for this Node or Channel");
    }

    uint16 InputRangeHelper::inputRangeToEepromVal(WirelessTypes::InputRange range, WirelessModels::NodeModel nodeType, WirelessTypes::ChannelType channelType)
    {
        const InputRangeMap& ranges = getRangeMap(nodeType, channelType);

        for(auto& r : ranges)
        {
            if(r.second.inputRange == range)
            {
                return r.first;
            }
        }

        throw Error_NotSupported("Invalid Input Range Value");
    }

    uint16 InputRangeHelper::inputRangeToEepromVal(WirelessTypes::InputRange range, WirelessModels::NodeModel nodeType, WirelessTypes::ChannelType channelType, WirelessTypes::Voltage excitationVoltage)
    {
        const InputRangeMap& ranges = getRangeMap(nodeType, channelType, excitationVoltage);

        for(auto& r : ranges)
        {
            if(r.second.inputRange == range)
            {
                return r.first;
            }
        }

        throw Error_NotSupported("Invalid Input Range Value");
    }

    WirelessTypes::InputRange InputRangeHelper::eepromValToInputRange(uint16 eepromValue,
                                                                      WirelessModels::NodeModel nodeType,
                                                                      WirelessTypes::ChannelType channelType)
    {
        const InputRangeMap& ranges = getRangeMap(nodeType, channelType);

        try
        {
            return ranges.at(eepromValue).inputRange;
        }
        catch(std::out_of_range&)
        {
            return WirelessTypes::range_invalid;
        }
    }

    WirelessTypes::InputRange InputRangeHelper::eepromValToInputRange(uint16 eepromValue,
                                                                             WirelessModels::NodeModel nodeType,
                                                                             WirelessTypes::ChannelType channelType,
                                                                             WirelessTypes::Voltage excitationVoltage)
    {
        const InputRangeMap& ranges = getRangeMap(nodeType, channelType, excitationVoltage);

        try
        {
            return ranges.at(eepromValue).inputRange;
        }
        catch(std::out_of_range&)
        {
            return WirelessTypes::range_invalid;
        }
    }

    void InputRangeHelper::getRangeVector(WirelessModels::NodeModel nodeType, WirelessTypes::ChannelType channelType, InputRanges& result)
    {
        const auto& rangeMap = getRangeMap(nodeType, channelType);
        for(auto& range : rangeMap)
        {
            result.push_back(range.second);
        }
    }

    void InputRangeHelper::getRangeVector(WirelessModels::NodeModel nodeType, WirelessTypes::ChannelType channelType, WirelessTypes::Voltage excitationVoltage, InputRanges& result)
    {
        const auto& rangeMap = getRangeMap(nodeType, channelType, excitationVoltage);
        for(auto& range : rangeMap)
        {
            result.push_back(range.second);
        }
    }
}