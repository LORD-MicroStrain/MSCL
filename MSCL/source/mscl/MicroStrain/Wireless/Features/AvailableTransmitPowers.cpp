/*******************************************************************************
Copyright(c) 2015-2020 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"

#include "AvailableTransmitPowers.h"

namespace mscl
{
    const WirelessTypes::TransmitPowers AvailableTransmitPowers::get(const NodeInfo& info, WirelessTypes::CommProtocol commProtocol)
    {
        //special cases for Japan
        if(info.regionCode() == WirelessTypes::region_japan)
        {
            //NOTE: only adding special cases for older nodes here.
            //      see the ::get200series() function below for the 200-series nodes
            switch(info.model())
            {
                case WirelessModels::node_shmLink2_cust1_oldNumber:
                case WirelessModels::node_shmLink2_cust1:
                {
                    return{
                        WirelessTypes::power_16dBm,
                        WirelessTypes::power_10dBm
                    };
                }

                //the rest of the Nodes, in Japan
                default:
                    return{
                        WirelessTypes::power_10dBm,
                        WirelessTypes::power_5dBm
                    };
            }
        }

        //standard transmit powers shared among devices
        switch(info.regionCode())
        {
            //case WirelessTypes::region_japan:   // japan handled separately above

            case WirelessTypes::region_europeanUnion:
            case WirelessTypes::region_australia_newzealand:
            case WirelessTypes::region_singapore:
            case WirelessTypes::region_other:
                return{
                    WirelessTypes::power_10dBm,
                    WirelessTypes::power_5dBm,
                    WirelessTypes::power_0dBm
                };

            case WirelessTypes::region_usa:
            case WirelessTypes::region_canada:
            case WirelessTypes::region_brazil:
            case WirelessTypes::region_china:
            default:
            {
                return{
                    WirelessTypes::power_16dBm,
                    WirelessTypes::power_10dBm,
                    WirelessTypes::power_5dBm,
                    WirelessTypes::power_0dBm
                };
            }
        }

    }

    const WirelessTypes::TransmitPowers AvailableTransmitPowers::get200series(const NodeInfo& info, WirelessTypes::CommProtocol commProtocol)
    {
        //special cases for Japan
        if(info.regionCode() == WirelessTypes::region_japan)
        {
            //NOTE: only adding special cases for 200-series nodes here.
            //      see the ::get() function above for the older nodes
            switch(info.model())
            {
                case WirelessModels::node_shmLink201:
                case WirelessModels::node_shmLink201_qbridge_1K:
                case WirelessModels::node_shmLink201_qbridge_348:
                case WirelessModels::node_shmLink201_hbridge_1K:
                case WirelessModels::node_shmLink201_hbridge_348:
                case WirelessModels::node_shmLink201_fullbridge:
                    return{
                        WirelessTypes::power_10dBm,
                        WirelessTypes::power_5dBm
                    };

                case WirelessModels::node_gLink_200_8g_oem:
                case WirelessModels::node_gLink_200_40g_oem:
                case WirelessModels::node_gLink_200_8g_oem_mmcx:
                case WirelessModels::node_gLink_200_40g_oem_mmcx:
                case WirelessModels::node_gLink_200_8g_oem_u_fl:
                case WirelessModels::node_gLink_200_40g_oem_u_fl:
                {
                    if(commProtocol == WirelessTypes::commProtocol_lxrs)
                    {
                        return{
                            WirelessTypes::power_16dBm,
                            WirelessTypes::power_10dBm,
                            WirelessTypes::power_5dBm
                        };
                    }
                    else
                    {
                        return{
                            WirelessTypes::power_11dBm,
                            WirelessTypes::power_5dBm,
                            WirelessTypes::power_1dBm,
                            WirelessTypes::power_0dBm
                        };
                    }
                }

                case WirelessModels::node_ptLink200:
                case WirelessModels::node_rtdLink200:
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
                case WirelessModels::node_shmLink210_fullbridge:
                case WirelessModels::node_shmLink210_qbridge_3K:
                case WirelessModels::node_tcLink200:
                case WirelessModels::node_tcLink200_oem:
                case WirelessModels::node_tcLink200_oem_ufl:
                {
                    if(commProtocol == WirelessTypes::commProtocol_lxrs)
                    {
                        return{
                            WirelessTypes::power_15dBm,
                            WirelessTypes::power_10dBm,
                            WirelessTypes::power_5dBm
                        };
                    }
                    else
                    {
                        return{
                            WirelessTypes::power_11dBm,
                            WirelessTypes::power_5dBm,
                            WirelessTypes::power_0dBm,
                        };
                    }
                }

                //all other nodes fall through to standard transmit powers below
                default:
                    break;
            }
        }

        //special cases for some model/region/protocol combinations
        switch(info.model())
        {
            case WirelessModels::node_rtdLink200:
            case WirelessModels::node_tcLink200:
            {
                if(info.regionCode() == WirelessTypes::region_europeanUnion ||
                   info.regionCode() == WirelessTypes::region_singapore ||
                   info.regionCode() == WirelessTypes::region_australia_newzealand ||
                   info.regionCode() == WirelessTypes::region_other)
                {
                    if(commProtocol == WirelessTypes::commProtocol_lxrs)
                    {
                        return{
                            WirelessTypes::power_11dBm,
                            WirelessTypes::power_10dBm,
                            WirelessTypes::power_5dBm,
                            WirelessTypes::power_0dBm
                        };
                    }
                }
                else if(info.regionCode() == WirelessTypes::region_usa ||
                        info.regionCode() == WirelessTypes::region_canada)
                {
                    if(commProtocol == WirelessTypes::commProtocol_lxrsPlus)
                    {
                        return{
                            WirelessTypes::power_16dBm,
                            WirelessTypes::power_10dBm,
                            WirelessTypes::power_5dBm,
                            WirelessTypes::power_0dBm
                        };
                    }
                    break;
                }

            }

            //all other nodes fall through to standard transmit powers below
            default:
                break;
        }

        //standard transmit powers shared among devices
        switch(info.regionCode())
        {
            case WirelessTypes::region_japan:
            {
                if(commProtocol == WirelessTypes::commProtocol_lxrs)
                {
                    return{
                        WirelessTypes::power_16dBm,
                        WirelessTypes::power_10dBm,
                        WirelessTypes::power_5dBm
                    };
                }
                else
                {
                    return{
                        WirelessTypes::power_12dBm,
                        WirelessTypes::power_5dBm,
                        WirelessTypes::power_1dBm,
                    };
                }
            }

            case WirelessTypes::region_europeanUnion:
            case WirelessTypes::region_australia_newzealand:
            case WirelessTypes::region_singapore:
            case WirelessTypes::region_other:
                return{
                    WirelessTypes::power_10dBm,
                    WirelessTypes::power_5dBm,
                    WirelessTypes::power_0dBm
                };

            case WirelessTypes::region_usa:
            case WirelessTypes::region_canada:
            case WirelessTypes::region_brazil:
            case WirelessTypes::region_china:
            default:
            {
                //if firmware supports 20dBm
                if(info.firmwareVersion() >= Version(10, 0))
                {
                    return{
                        WirelessTypes::power_20dBm,
                        WirelessTypes::power_16dBm,
                        WirelessTypes::power_10dBm,
                        WirelessTypes::power_5dBm,
                        WirelessTypes::power_0dBm
                    };
                }
                else
                {
                    return{
                        WirelessTypes::power_16dBm,
                        WirelessTypes::power_10dBm,
                        WirelessTypes::power_5dBm,
                        WirelessTypes::power_0dBm
                    };
                }
            }
        }

    }

    const WirelessTypes::TransmitPowers AvailableTransmitPowers::get(WirelessTypes::RegionCode region, WirelessModels::BaseModel model, const Version& fwVersion, WirelessTypes::CommProtocol commProtocol)
    {
        //special cases for Japan
        if(region == WirelessTypes::region_japan)
        {
            switch(model)
            {
                case WirelessModels::base_wsdaBase_200_legacy:
                case WirelessModels::base_wsdaBase_200:
                case WirelessModels::base_wsdaBase_200_extAntenna:
                case WirelessModels::base_wsi_104:
                case WirelessModels::base_wsda_2000:
                {
                    if(commProtocol == WirelessTypes::commProtocol_lxrs)
                    {
                        return{
                            WirelessTypes::power_16dBm,
                            WirelessTypes::power_11dBm,
                            WirelessTypes::power_5dBm
                        };
                    }
                    else
                    {
                        return{
                            WirelessTypes::power_11dBm,
                            WirelessTypes::power_5dBm,
                            WirelessTypes::power_0dBm,
                        };
                    }
                }

                //the rest of the BaseStations, in Japan
                default:
                    return{
                        WirelessTypes::power_10dBm,
                        WirelessTypes::power_5dBm
                    };
            }
        }

        //standard transmit powers shared among devices
        switch(region)
        {
            //case WirelessTypes::region_japan: //japan handled separately above

            case WirelessTypes::region_europeanUnion:
            case WirelessTypes::region_australia_newzealand:
            case WirelessTypes::region_singapore:
            case WirelessTypes::region_other:
                return{
                    WirelessTypes::power_10dBm,
                    WirelessTypes::power_5dBm,
                    WirelessTypes::power_0dBm
                };

            case WirelessTypes::region_usa:
            case WirelessTypes::region_canada:
            case WirelessTypes::region_brazil:
            case WirelessTypes::region_china:
            default:
            {
                //if firmware supports 20dBm
                if(fwVersion >= Version(4, 0))
                {
                    return{
                        WirelessTypes::power_20dBm,
                        WirelessTypes::power_16dBm,
                        WirelessTypes::power_10dBm,
                        WirelessTypes::power_5dBm,
                        WirelessTypes::power_0dBm
                    };
                }
                else
                {
                    return{
                        WirelessTypes::power_16dBm,
                        WirelessTypes::power_10dBm,
                        WirelessTypes::power_5dBm,
                        WirelessTypes::power_0dBm
                    };
                }
            }
        }
    }
}