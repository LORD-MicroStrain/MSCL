/*******************************************************************************
Copyright(c) 2015-2016 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/

#pragma once

#include "mscl/Types.h"

namespace mscl
{
    //API Class: WirelessModels
    //    Contains the models of Wireless hardware.
    class WirelessModels
    {
    public:
        //=========================================================================
        //API Enum: NodeModel
        //    The model numbers for each of the Wireless Nodes.
        //
        //node_gLink_2g                    - 63052000 - G-Link 2G
        //node_gLink_10g                   - 63053000 - G-Link 10G
        //node_gLinkII_cust_in             - 63054000 - G-Link II Custom Internal
        //node_gLinkII_2g_in               - 63054002 - G-Link II 2G Internal
        //node_gLinkII_10g_in              - 63054010 - G-Link II 10G Internal
        //node_gLinkII_cust_ex             - 63055000 - G-Link II Custom External
        //node_gLinkII_2g_ex               - 63055002 - G-Link II 2g External
        //node_gLinkII_10g_ex              - 63055010 - G-Link II 10G External
        //node_gLink_rgd_10g               - 63056010 - G-Link-RGD 10G
        //node_dvrtLink                    - 63181000 - DVRT-Link
        //node_shmLink                     - 63086000 - SHM-Link
        //node_shmLink2                    - 63290000 - SHM-Link 2
        //node_shmLink2_cust1              - 63290100 - SHM-Link 2 - Custom 1
        //node_sgLink                      - 63083000 - SG-Link
        //node_sgLink_oem_S                - 63081000 - SG-Link 0EM -S (non-xr)
        //node_sgLink_oem                  - 63084000 - SG-Link OEM
        //node_sgLink_micro                - 63084100 - SG-Link Micro
        //node_sgLink_rgd                  - 63085000 - SG-Link RGD
        //node_sgLink_herm                 - 65010000 - SG-Link-Hermetic (Generic)
        //node_sgLink_herm_2600            - 65011110 - SG-Link-Hermetic 2600 belt assembly
        //node_sgLink_herm_2700            - 65011210 - SG-Link-Hermetic 2700 belt assembly
        //node_sgLink_herm_2800            - 65011310 - SG-Link-Hermetic 2800 belt assembly
        //node_vLink_legacy                - 2428       - V-Link (legacy)
        //node_vLink                       - 63121000 - V-Link
        //node_tcLink_1ch                  - 63104000 - TC-Link 1CH
        //node_tcLink_3ch                  - 63106000 - TC-Link 3CH
        //node_tcLink_6ch                  - 63105000 - TC-Link 6CH
        //node_tcLink_6ch_ip67             - 63107000 - TC-Link 6CH IP67
        //node_tcLink_6ch_ip67_rht         - 63108000 - TC-Link 6CH IP67 with Relative Humidity
        //node_envLink_mini                - 63220000 - ENV-Link-Mini
        //node_rtdLink                     - 63260000 - RTD-Link
        //node_iepeLink                    - 63160010 - IEPE-Link        
        //node_wattLink                    - 63230000 - Watt-Link (Generic)
        //node_wattLink_3Y600              - 63235100 - Watt-Link 3Y600
        //node_wattLink_3Y480              - 63234100 - Watt-Link 3Y480
        //node_wattLink_3Y400              - 63233100 - Watt-Link 3Y400
        //node_wattLink_3Y208              - 63231100 - Watt-Link 3Y208
        //node_wattLink_3D480              - 63234200 - Watt-Link 3D480
        //node_wattLink_3D400              - 63233200 - Watt-Link 3D400
        //node_wattLink_3D240              - 63232200 - Watt-Link 3D240
        //node_mvPerVLink                  - 63250200 - mV/V-Link
        //node_envLink_pro                 - 60000001 - ENV-Link-Pro
        //node_sgLink_8ch                  - 60000002 - SG-Link-8CH
        //=========================================================================
        enum NodeModel
        {
            node_gLink_2g                   = 63052000,    //G-Link 2G
            node_gLink_10g                  = 63053000,    //G-Link 10G
            node_gLinkII_cust_in            = 63054000,    //G-Link II Custom Internal
            node_gLinkII_2g_in              = 63054002,    //G-Link II 2G Internal
            node_gLinkII_10g_in             = 63054010,    //G-Link II 10G Internal
            node_gLinkII_cust_ex            = 63055000,    //G-Link II Custom External
            node_gLinkII_2g_ex              = 63055002,    //G-Link II 2g External
            node_gLinkII_10g_ex             = 63055010,    //G-Link II 10G External
            node_gLink_rgd_10g              = 63056010,    //G-Link-RGD 10G
            node_dvrtLink                   = 63181000,    //DVRT-Link
            node_shmLink                    = 63086000,    //SHM-Link
            node_shmLink2                   = 63290000,    //SHM-Link 2
            node_shmLink2_cust1             = 63290100,    //SHM-Link 2 - Custom 1
            node_sgLink                     = 63083000,    //SG-Link
            node_sgLink_oem_S               = 63081000,    //SG-Link 0EM -S (non-xr)
            node_sgLink_oem                 = 63084000,    //SG-Link OEM
            node_sgLink_micro               = 63084100,    //SG-Link Micro
            node_sgLink_rgd                 = 63085000,    //SG-Link RGD
            node_sgLink_herm                = 65010000,    //SG-Link-Hermetic
            node_sgLink_herm_2600           = 65011110,    //SG-Link-Hermetic 2600 belt assembly
            node_sgLink_herm_2700           = 65011210,    //SG-Link-Hermetic 2700 belt assembly
            node_sgLink_herm_2800           = 65011310,    //SG-Link-Hermetic 2800 belt assembly
            node_vLink_legacy               = 2428,        //V-Link (legacy)
            node_vLink                      = 63121000,    //V-Link
            node_vLink2                     = 63122000,    //V-Link 2
            node_tcLink_1ch                 = 63104000,    //TC-Link 1CH
            node_tcLink_3ch                 = 63106000,    //TC-Link 3CH
            node_tcLink_6ch                 = 63105000,    //TC-Link 6CH
            node_tcLink_6ch_ip67            = 63107000,    //TC-Link 6CH IP67
            node_tcLink_6ch_ip67_rht        = 63108000,    //TC-Link 6CH IP67 RHT
            node_envLink_mini               = 63220000,    //ENV-Link-Mini
            node_rtdLink                    = 63260000,    //RTD-Link
            node_iepeLink                   = 63160010,    //IEPE-Link        
            node_wattLink                   = 63230000,    //Watt-Link
            node_wattLink_3Y600             = 63235100,    //Watt-Link 3Y600
            node_wattLink_3Y480             = 63234100,    //Watt-Link 3Y480
            node_wattLink_3Y400             = 63233100,    //Watt-Link 3Y400
            node_wattLink_3Y208             = 63231100,    //Watt-Link 3Y208
            node_wattLink_3D480             = 63234200,    //Watt-Link 3D480
            node_wattLink_3D400             = 63233200,    //Watt-Link 3D400
            node_wattLink_3D240             = 63232200,    //Watt-Link 3D240
            node_mvPerVLink                 = 63250200,    //mV/V-Link

            //TODO: the following nodes do not currently have 6XXX level model numbers (NODES NEED TO BE UPDATED!)
            node_envLink_pro                = 60000001,
            node_sgLink_8ch                 = 60000002
        };

        //=========================================================================
        //API Enum: BaseModel
        //    The model numbers for each of the Wireless Base Stations
        //
        //base_wsda_1000               - 63140050    -WSDA-1000
        //base_wsda_1500               - 63141500    -WSDA-1500
        //base_wsda_2000               - 63142050    -WSDA-2000
        //base_wsdaBase_101_analog     - 63071010    -WSDA-Base-101 (Analog)
        //base_wsdaBase_102_rs232      - 63071020    -WSDA-Base-102 (RS232)
        //base_wsdaBase_104_usb        - 63071040    -WSDA-Base-104 (USB)
        //base_wsdaBase_oem            - 63072000    -WSDA-Base-OEM
        //base_wsdaBase_mini           - 63079999    -WSDA-Base-Mini
        //=========================================================================
        enum BaseModel
        {
            base_wsda_1000                 = 63140050,    //WSDA-1000
            base_wsda_1500                 = 63141500,    //WSDA-1500
            base_wsda_2000                 = 63142050,    //WSDA-2000
            base_wsdaBase_101_analog       = 63071010,    //WSDA-Base-101 (Analog)
            base_wsdaBase_102_rs232        = 63071020,    //WSDA-Base-102 (RS232)
            base_wsdaBase_104_usb          = 63071040,    //WSDA-Base-104 (USB)
            base_wsdaBase_oem              = 63072000,    //WSDA-Base-OEM
            base_wsdaBase_mini             = 63079999     //WSDA-Base-Mini
        };

#ifndef SWIG
        //Function: nodeFromLegacyModel
        //    Gets the <NodeModel> from the legacy node model number.
        //
        //Parameters:
        //    legacyModel - The legacy model number.
        //
        //Returns:
        //    The <NodeModel> for the node.
        //
        //Exceptions:
        //    - <Error>: Unknown model number.
        static NodeModel nodeFromLegacyModel(uint16 legacyModel);

        //Function: baseFromLegacyModel
        //    Gets the <BaseModel> from the legacy base station model number.
        //
        //Parameters:
        //    legacyModel - The legacy model number.
        //
        //Returns:
        //    The <BaseModel> for the base station.
        //
        //Exceptions:
        //    - <Error>: Unknown model number.
        static BaseModel baseFromLegacyModel(uint16 legacyModel);
#endif
    };

}