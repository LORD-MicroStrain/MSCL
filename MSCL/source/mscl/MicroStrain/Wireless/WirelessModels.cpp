/*******************************************************************************
Copyright(c) 2015 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"
#include "WirelessModels.h"

namespace mscl
{
    WirelessModels::NodeModel WirelessModels::nodeFromLegacyModel(uint16 legacyModel)
    {
        switch(legacyModel)
        {
        case 2316:    return node_wattLink;
        case 2418:    return node_gLink_2g;
        case 2419:    return node_gLink_10g;
        case 2417:    return node_sgLink;
        case 2420:    return node_sgLink_oem_S;
        case 2421:    return node_dvrtLink;
        case 2423:    return node_sgLink_oem;
        case 2426:    return node_sgLink_rgd;        
        case 2427:    return node_tcLink_6ch;            
        case 2430:    return node_sgLink_herm;    
        case 2435:    return node_gLinkII_cust_in;
        case 2432:    return node_gLinkII_2g_in;    
        case 2436:    return node_gLinkII_10g_in;    
        case 2437:    return node_gLinkII_cust_ex;
        case 2438:    return node_gLinkII_2g_ex;    
        case 2439:    return node_gLinkII_10g_ex;    
        case 2440:    return node_gLink_rgd_10g;    
        case 2428:    return node_vLink_legacy;
        case 2433:    return node_vLink;
        case 2622:    return node_tcLink_1ch;            
        case 2624:    return node_envLink_mini;    
        case 2625:    return node_rtdLink;        
        case 2984:    return node_iepeLink;    
        case 2623:    return node_tcLink_3ch;
        case 2434:    return node_tcLink_6ch_ip67;
        case 2429:    return node_shmLink;

        case 2993:    return node_envLink_pro;
        case 2431:    return node_sgLink_8ch;

        default:
            //don't know the model, just cast to a wireless model and return
            return static_cast<WirelessModels::NodeModel>(legacyModel);
        }
    }

    WirelessModels::BaseModel WirelessModels::baseFromLegacyModel(uint16 legacyModel)
    {
        switch(legacyModel)
        {
        case 50:
        case 2995:
            return base_wsda_1000;

        case 2050:
            return base_wsda_2000;

        case 1010:
        case 2625:
            return base_wsdaBase_101_analog;

        case 1020:
        case 2626:
            return base_wsdaBase_102_rs232;

        case 1040:
        case 2621:
            return base_wsdaBase_104_usb;

        default:
            //don't know the model, just cast to a base model and return
            return static_cast<WirelessModels::BaseModel>(legacyModel);
        }
    }
}