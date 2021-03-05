/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

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
        //  node_vLink_legacy                   - 2428 - V-Link (legacy)
        //  node_cfBearingTempLink              - 51280096 - CF-Bearing-Temp-Link
        //  node_envLink_pro                    - 60000001 - ENV-Link-Pro (NO ACTUAL 6XXX NUMBER, NODE NEEDS TO BE UPDATED!)
        //  node_gLink_2g                       - 63052000 - G-Link 2G
        //  node_gLink_10g                      - 63053000 - G-Link 10G
        //  node_gLinkII_cust_in                - 63054000 - G-Link II Custom Internal
        //  node_gLinkII_2g_in                  - 63054002 - G-Link II 2G Internal
        //  node_gLinkII_10g_in                 - 63054010 - G-Link II 10G Internal
        //  node_gLinkII_cust_ex                - 63055000 - G-Link II Custom External
        //  node_gLinkII_2g_ex                  - 63055002 - G-Link II 2g External
        //  node_gLinkII_10g_ex                 - 63055010 - G-Link II 10G External
        //  node_gLink_rgd_10g                  - 63056010 - G-Link-RGD 10G
        //  node_gLink_200_8g                   - 63056000 - G-Link-200-8g
        //  node_gLink_200_40g                  - 63056001 - G-Link-200-40g
        //  node_gLink_200_8g_oem               - 63056002 - G-Link-200-8g-OEM (Internal Antenna)
        //  node_gLink_200_40g_oem              - 63056003 - G-Link-200-40g-OEM (Internal Antenna)
        //  node_gLink_200_8g_oem_mmcx          - 63056181 - G-Link-200-8g-OEM (MMCX Antenna)
        //  node_gLink_200_40g_oem_mmcx         - 63056141 - G-Link-200-40g-OEM (MMCX Antenna)
        //  node_gLink_200_8g_oem_u_fl          - 63056182 - G-Link-200-8g-OEM (U.Fl Antenna)
        //  node_gLink_200_40g_oem_u_fl         - 63056142 - G-Link-200-40g-OEM (U.Fl Antenna)
        //  node_gLink_200_r                    - 63056200 - G-Link-200-R
        //  node_sgLink_oem_S                   - 63081000 - SG-Link 0EM -S (non-xr)
        //  node_sgLink                         - 63083000 - SG-Link
        //  node_sgLink200                      - 63083300 - SG-Link-200, Full Bridge
        //  node_sgLink200_hbridge_350          - 63083330 - SG-Link-200, Half Bridge, 350 ohm
        //  node_sgLink200_hbridge_120          - 63083320 - SG-Link-200, Half Bridge, 120 ohm
        //  node_sgLink200_qbridge_1K           - 63083410 - SG-Link-200, Quarter Bridge, 1k ohm
        //  node_sgLink200_hbridge_1K           - 63083310 - SG-Link-200, Half Bridge, 1k ohm
        //  node_sgLink200_qbridge_350          - 63083430 - SG-Link-200, Quarter Bridge, 350 ohm
        //  node_sgLink200_qbridge_120          - 63083420 - SG-Link-200, Quarter Bridge, 120 ohm
        //  node_sgLink_oem                     - 63084000 - SG-Link OEM
        //  node_sgLink_micro                   - 63084100 - SG-Link Micro
        //  node_sgLink200_oem                  - 63084200 - SG-Link-200-OEM - Full Bridge, Internal Antenna
        //  node_sgLink200_oem_ufl              - 63084201 - SG-Link-200-OEM - Full Bridge, U.Fl Antenna
        //  node_sgLink200_oem_hbridge_1K       - 63084310 - SG-Link-200-OEM - Half Bridge, 1K OHM, Internal Antenna
        //  node_sgLink200_oem_hbridge_1K_ufl   - 63084311 - SG-Link-200-OEM - Half Bridge, 1K OHM, U.Fl Antenna
        //  node_sgLink200_oem_hbridge_120      - 63084320 - SG-Link-200-OEM - Half Bridge, 120 OHM, Internal Antenna
        //  node_sgLink200_oem_hbridge_120_ufl  - 63084321 - SG-Link-200-OEM - Half Bridge, 120 OHM, U.Fl Antenna
        //  node_sgLink200_oem_hbridge_350      - 63084330 - SG-Link-200-OEM - Half Bridge, 350 OHM, Internal Antenna
        //  node_sgLink200_oem_hbridge_350_ufl  - 63084331 - SG-Link-200-OEM - Half Bridge, 120 OHM, U.Fl Antenna
        //  node_sgLink200_oem_qbridge_1K       - 63084410 - SG-Link-200-OEM - Quarter Bridge, 1K OHM, Internal Antenna
        //  node_sgLink200_oem_qbridge_1K_ufl   - 63084411 - SG-Link-200-OEM - Quarter Bridge, 1K OHM, U.Fl Antenna
        //  node_sgLink200_oem_qbridge_120      - 63084420 - SG-Link-200-OEM - Quarter Bridge, 120 OHM, Internal Antenna
        //  node_sgLink200_oem_qbridge_120_ufl  - 63084421 - SG-Link-200-OEM - Quarter Bridge, 120 OHM, U.Fl Antenna
        //  node_sgLink200_oem_qbridge_350      - 63084430 - SG-Link-200-OEM - Quarter Bridge, 350 OHM, Internal Antenna
        //  node_sgLink200_oem_qbridge_350_ufl  - 63084431 - SG-Link-200-OEM - Quarter Bridge, 120 OHM, U.Fl Antenna
        //  node_sgLink_rgd                     - 63085000 - SG-Link RGD
        //  node_shmLink                        - 63086000 - SHM-Link
        //  node_tcLink_1ch                     - 63104000 - TC-Link 1CH
        //  node_tcLink_6ch                     - 63105000 - TC-Link 6CH
        //  node_tcLink_3ch                     - 63106000 - TC-Link 3CH
        //  node_tcLink_6ch_ip67                - 63107000 - TC-Link 6CH IP67
        //  node_tcLink200_oem                  - 63104100 - TC-Link-200-OEM, Internal Antenna
        //  node_tcLink200_oem_ufl              - 63104101 - TC-Link-200-OEM, U.Fl Antenna
        //  node_tcLink200                      - 63105400 - TC-Link-200
        //  node_rtdLink200                     - 63105500 - RTD-Link-200
        //  node_tcLink_6ch_ip67_rht            - 63108000 - TC-Link 6CH IP67 RHT
        //  node_vLink                          - 63121000 - V-Link
        //  node_vLink200                       - 63122000 - V-Link 200 - Full Bridge
        //  node_vLink200_qbridge_1K            - 63122110 - V-Link 200 - Quarter Bridge, 1K OHM
        //  node_vLink200_qbridge_120           - 63122120 - V-Link 200 - Quarter Bridge, 120 OHM
        //  node_vLink200_qbridge_350           - 63122130 - V-Link 200 - Quarter Bridge, 350 OHM
        //  node_vLink200_hbridge_1K            - 63122210 - V-Link 200 - Half Bridge, 1K OHM
        //  node_vLink200_hbridge_120           - 63122220 - V-Link 200 - Half Bridge, 120 OHM
        //  node_vLink200_hbridge_350           - 63122230 - V-Link 200 - Half Bridge, 350 OHM
        //  node_iepeLink                       - 63160010 - IEPE-Link
        //  node_dvrtLink                       - 63181000 - DVRT-Link
        //  node_envLink_mini                   - 63220000 - ENV-Link-Mini
        //  node_wattLink                       - 63230000 - Watt-Link
        //  node_wattLink_3Y208                 - 63231100 - Watt-Link 3Y208
        //  node_wattLink_3D240                 - 63232200 - Watt-Link 3D240
        //  node_wattLink_3Y400                 - 63233100 - Watt-Link 3Y400
        //  node_wattLink_3D400                 - 63233200 - Watt-Link 3D400
        //  node_wattLink_3Y480                 - 63234100 - Watt-Link 3Y480
        //  node_wattLink_3D480                 - 63234200 - Watt-Link 3D480
        //  node_wattLink_3Y600                 - 63235100 - Watt-Link 3Y600
        //  node_mvPerVLink                     - 63250200 - mV/V-Link - REMOVED: support removed, this model number now mapped to PT-Link-200
        //  node_ptLink200                      - 63250200 - PT-Link-200
        //  node_rtdLink                        - 63260000 - RTD-Link
        //  node_shmLink2_cust1_oldNumber       - 63290000 - SHM-Link 2 - Custom 1 (old model number)
        //  node_shmLink2_cust1                 - 63290100 - SHM-Link 2 - Custom 1
        //  node_shmLink200                     - 63290200 - SHM-Link 200
        //  node_shmLink201                     - 63290150 - SHM-Link 201 - Rosette - 3000 resistance
        //  node_shmLink201_qbridge_1K          - 63290151 - SHM-Link 201 - Quarter Bridge - 1K resistance
        //  node_shmLink201_qbridge_348         - 63290152 - SHM-Link 201 - Quarter Bridge - 348 resistance
        //  node_shmLink201_hbridge_1K          - 63290153 - SHM-Link 201 - Half Bridge - 1K resistance
        //  node_shmLink201_hbridge_348         - 63290154 - SHM-Link 201 - Half Bridge - 348 resistance
        //  node_shmLink201_fullbridge          - 63290155 - SHM-Link 201 - Full Bridge
        //  node_shmLink210_fullbridge          - 63290170 - SHM-Link 210 - Full Bridge
        //  node_shmLink210_qbridge_3K          - 63290171 - SHM-Link 210 - Quarter Bridge - 3K OHM
        //  node_torqueLink                     - 63309999 - Torque-Link
        //  node_torqueLink200                  - 63319999 - Torque-Link-200
        //  node_sgLink_herm                    - 65010000 - SG-Link-Hermetic
        //  node_sgLink_herm_2600               - 65011110 - SG-Link-Hermetic 2600 belt assembly
        //  node_sgLink_herm_2700               - 65011210 - SG-Link-Hermetic 2700 belt assembly
        //  node_sgLink_herm_2800               - 65011310 - SG-Link-Hermetic 2800 belt assembly
        //  node_sgLink_herm_2900               - 65011410 - SG-Link-Hermetic 2900 belt assembly
        //  node_wirelessImpactSensor           - 65080000 - Wireless Impact Sensor
        //=========================================================================
        enum NodeModel
        {
            node_vLink_legacy                   = 2428,         //V-Link (legacy)
            node_cfBearingTempLink              = 51280096,     //CF-Bearing-Temp-Link
            node_envLink_pro                    = 60000001,     //ENV-Link-Pro (NO ACTUAL 6XXX NUMBER, NODE NEEDS TO BE UPDATED!)
            node_gLink_2g                       = 63052000,     //G-Link 2G
            node_gLink_10g                      = 63053000,     //G-Link 10G
            node_gLinkII_cust_in                = 63054000,     //G-Link II Custom Internal
            node_gLinkII_2g_in                  = 63054002,     //G-Link II 2G Internal
            node_gLinkII_10g_in                 = 63054010,     //G-Link II 10G Internal
            node_gLinkII_cust_ex                = 63055000,     //G-Link II Custom External
            node_gLinkII_2g_ex                  = 63055002,     //G-Link II 2g External
            node_gLinkII_10g_ex                 = 63055010,     //G-Link II 10G External
            node_gLink_rgd_10g                  = 63056010,     //G-Link-RGD 10G
            node_gLink_200_8g                   = 63056000,     //G-Link-200-8g
            node_gLink_200_40g                  = 63056001,     //G-Link-200-40g
            node_gLink_200_8g_oem               = 63056002,     //G-Link-200-8g-OEM (Internal Antenna)
            node_gLink_200_40g_oem              = 63056003,     //G-Link-200-40g-OEM (Internal Antenna)
            node_gLink_200_8g_oem_mmcx          = 63056181,     //G-Link-200-8g-OEM (MMCX Antenna)
            node_gLink_200_40g_oem_mmcx         = 63056141,     //G-Link-200-40g-OEM (MMCX Antenna)
            node_gLink_200_8g_oem_u_fl          = 63056182,     //G-Link-200-8g-OEM (U.Fl Antenna)
            node_gLink_200_40g_oem_u_fl         = 63056142,     //G-Link-200-40g-OEM (U.Fl Antenna)
            node_gLink_200_r                    = 63056200,     //G-Link-200-R
            node_sgLink_oem_S                   = 63081000,     //SG-Link 0EM -S (non-xr)
            node_sgLink                         = 63083000,     //SG-Link
            node_sgLink200                      = 63083300,     //SG-Link-200, Full Bridge
            node_sgLink200_hbridge_1K           = 63083310,     //SG-Link-200, Half Bridge, 1k ohm
            node_sgLink200_hbridge_350          = 63083330,     //SG-Link-200, Half Bridge, 350 ohm
            node_sgLink200_hbridge_120          = 63083320,     //SG-Link-200, Half Bridge, 120 ohm
            node_sgLink200_qbridge_1K           = 63083410,     //SG-Link-200, Quarter Bridge, 1k ohm
            node_sgLink200_qbridge_350          = 63083430,     //SG-Link-200, Quarter Bridge, 350 ohm
            node_sgLink200_qbridge_120          = 63083420,     //SG-Link-200, Quarter Bridge, 120 ohm
            node_sgLink_oem                     = 63084000,     //SG-Link OEM
            node_sgLink_micro                   = 63084100,     //SG-Link Micro
            node_sgLink200_oem                  = 63084200,     //SG-Link-200-OEM - Full Bridge, Internal Antenna
            node_sgLink200_oem_ufl              = 63084201,     //SG-Link-200-OEM - Full Bridge, U.Fl Antenna
            node_sgLink200_oem_hbridge_1K       = 63084310,     //SG-Link-200-OEM - Half Bridge, 1K OHM, Internal Antenna
            node_sgLink200_oem_hbridge_1K_ufl   = 63084311,     //SG-Link-200-OEM - Half Bridge, 1K OHM, U.Fl Antenna
            node_sgLink200_oem_hbridge_120      = 63084320,     //SG-Link-200-OEM - Half Bridge, 120 OHM, Internal Antenna
            node_sgLink200_oem_hbridge_120_ufl  = 63084321,     //SG-Link-200-OEM - Half Bridge, 120 OHM, U.Fl Antenna
            node_sgLink200_oem_hbridge_350      = 63084330,     //SG-Link-200-OEM - Half Bridge, 350 OHM, Internal Antenna
            node_sgLink200_oem_hbridge_350_ufl  = 63084331,     //SG-Link-200-OEM - Half Bridge, 120 OHM, U.Fl Antenna
            node_sgLink200_oem_qbridge_1K       = 63084410,     //SG-Link-200-OEM - Quarter Bridge, 1K OHM, Internal Antenna
            node_sgLink200_oem_qbridge_1K_ufl   = 63084411,     //SG-Link-200-OEM - Quarter Bridge, 1K OHM, U.Fl Antenna
            node_sgLink200_oem_qbridge_120      = 63084420,     //SG-Link-200-OEM - Quarter Bridge, 120 OHM, Internal Antenna
            node_sgLink200_oem_qbridge_120_ufl  = 63084421,     //SG-Link-200-OEM - Quarter Bridge, 120 OHM, U.Fl Antenna
            node_sgLink200_oem_qbridge_350      = 63084430,     //SG-Link-200-OEM - Quarter Bridge, 350 OHM, Internal Antenna
            node_sgLink200_oem_qbridge_350_ufl  = 63084431,     //SG-Link-200-OEM - Quarter Bridge, 120 OHM, U.Fl Antenna
            node_sgLink_rgd                     = 63085000,     //SG-Link RGD
            node_shmLink                        = 63086000,     //SHM-Link
            node_tcLink_1ch                     = 63104000,     //TC-Link 1CH
            node_tcLink_6ch                     = 63105000,     //TC-Link 6CH
            node_tcLink_3ch                     = 63106000,     //TC-Link 3CH
            node_tcLink_6ch_ip67                = 63107000,     //TC-Link 6CH IP67
            node_tcLink200_oem                  = 63104100,     //TC-Link-200-OEM, Internal Antenna
            node_tcLink200_oem_ufl              = 63104101,     //TC-Link-200-OEM, U.Fl Antenna
            node_tcLink200                      = 63105400,     //TC-Link-200
            node_rtdLink200                     = 63105500,     //RTD-Link-200
            node_tcLink_6ch_ip67_rht            = 63108000,     //TC-Link 6CH IP67 RHT
            node_vLink                          = 63121000,     //V-Link
            node_vLink200                       = 63122000,     //V-Link 200 - Full Bridge
            node_vLink200_qbridge_1K            = 63122110,     //V-Link 200 - Quarter Bridge 1K OHM
            node_vLink200_qbridge_120           = 63122120,     //V-Link 200 - Quarter Bridge 120 OHM
            node_vLink200_qbridge_350           = 63122130,     //V-Link 200 - Quarter Bridge 350 OHM
            node_vLink200_hbridge_1K            = 63122210,     //V-Link 200 - Half Bridge 1K OHM
            node_vLink200_hbridge_120           = 63122220,     //V-Link 200 - Half Bridge 120 OHM
            node_vLink200_hbridge_350           = 63122230,     //V-Link 200 - Half Bridge 350 OHM
            node_iepeLink                       = 63160010,     //IEPE-Link
            node_dvrtLink                       = 63181000,     //DVRT-Link
            node_envLink_mini                   = 63220000,     //ENV-Link-Mini
            node_wattLink                       = 63230000,     //Watt-Link
            node_wattLink_3Y208                 = 63231100,     //Watt-Link 3Y208
            node_wattLink_3D240                 = 63232200,     //Watt-Link 3D240
            node_wattLink_3Y400                 = 63233100,     //Watt-Link 3Y400
            node_wattLink_3D400                 = 63233200,     //Watt-Link 3D400
            node_wattLink_3Y480                 = 63234100,     //Watt-Link 3Y480
            node_wattLink_3D480                 = 63234200,     //Watt-Link 3D480
            node_wattLink_3Y600                 = 63235100,     //Watt-Link 3Y600
            node_ptLink200                      = 63250200,     //PT-Link-200
            node_rtdLink                        = 63260000,     //RTD-Link
            node_shmLink2_cust1_oldNumber       = 63290000,     //SHM-Link 2 - Custom 1 (old model number)
            node_shmLink2_cust1                 = 63290100,     //SHM-Link 2 - Custom 1
            node_shmLink200                     = 63290200,     //SHM-Link 200
            node_shmLink201                     = 63290150,     //SHM-Link 201 - Rosette - 3000 resistance
            node_shmLink201_qbridge_1K          = 63290151,     //SHM-Link 201 - Quarter Bridge - 1K resistance
            node_shmLink201_qbridge_348         = 63290152,     //SHM-Link 201 - Quarter Bridge - 348 resistance
            node_shmLink201_hbridge_1K          = 63290153,     //SHM-Link 201 - Half Bridge - 1K resistance
            node_shmLink201_hbridge_348         = 63290154,     //SHM-Link 201 - Half Bridge - 348 resistance
            node_shmLink201_fullbridge          = 63290155,     //SHM-Link 201 - Full Bridge
            node_shmLink210_fullbridge          = 63290170,     //SHM-Link 210 - Full Bridge
            node_shmLink210_qbridge_3K          = 63290171,     //SHM-Link 210 - Quarter Bridge - 3K OHM
            node_torqueLink                     = 63309999,     //Torque-Link
            node_torqueLink200                  = 63319999,     //Torque-Link-200
            node_sgLink_herm                    = 65010000,     //SG-Link-Hermetic
            node_sgLink_herm_2600               = 65011110,     //SG-Link-Hermetic 2600 belt assembly
            node_sgLink_herm_2700               = 65011210,     //SG-Link-Hermetic 2700 belt assembly
            node_sgLink_herm_2800               = 65011310,     //SG-Link-Hermetic 2800 belt assembly
            node_sgLink_herm_2900               = 65011410,     //SG-Link-Hermetic 2900 belt assembly
            node_wirelessImpactSensor           = 65080000,     //Wireless Impact Sensor
        };

        //=========================================================================
        //API Enum: BaseModel
        //    The model numbers for each of the Wireless Base Stations
        //
        //base_wsda_1000                - 63140050       -WSDA-1000
        //base_wsda_1500                - 63141500       -WSDA-1500
        //base_wsda_2000                - 63142000       -WSDA-2000
        //base_wsdaBase_200             - 63072040       -WSDA-Base-200 (USB)
        //base_wsdaBase_200_extAntenna  - 63072140       -WSDA-Base-200 (USB) - External Antenna
        //base_wsdaBase_101_analog      - 63071010       -WSDA-Base-101 (Analog)
        //base_wsdaBase_102_rs232       - 63071020       -WSDA-Base-102 (RS232)
        //base_wsdaBase_104_usb         - 63071040       -WSDA-Base-104 (USB)
        //base_wsi_104                  - 63072000       -WSI/104
        //base_wsdaBase_mini            - 63079999       -WSDA-Base-Mini
        //=========================================================================
        enum BaseModel
        {
            base_wsda_1000                 = 63140050,      //WSDA-1000
            base_wsda_1500                 = 63141500,      //WSDA-1500
            base_wsda_2000                 = 63142000,      //WSDA-2000
            base_wsdaBase_200_legacy       = 63070200,      //WSDA-Base-200 (USB) (Legacy, never released)
            base_wsdaBase_200              = 63072040,      //WSDA-Base-200 (USB)
            base_wsdaBase_200_extAntenna   = 63072140,      //WSDA-Base-200 (USB) - External Antenna
            base_wsdaBase_101_analog       = 63071010,      //WSDA-Base-101 (Analog)
            base_wsdaBase_102_rs232        = 63071020,      //WSDA-Base-102 (RS232)
            base_wsdaBase_104_usb          = 63071040,      //WSDA-Base-104 (USB)
            base_wsi_104                   = 63072000,      //WSI/104
            base_wsdaBase_mini             = 63079999       //WSDA-Base-Mini
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