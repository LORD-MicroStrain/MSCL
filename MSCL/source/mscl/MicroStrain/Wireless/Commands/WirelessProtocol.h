/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include <functional>
#include <memory>

#include "mscl/Timestamp.h"
#include "AutoBalanceResult.h"
#include "AutoCalResult.h"
#include "BeaconStatus.h"
#include "PingResponse.h"
#include "SetToIdleStatus.h"
#include "mscl/MicroStrain/Wireless/WirelessDataPoint.h"
#include "mscl/MicroStrain/Wireless/Packets/WirelessPacket.h"

namespace mscl
{
    //forward declarations
    struct AutoCalCmdDetails;
    class BaseStation_Impl;
    class BaseStation;
    class Version;
    struct DatalogSessionInfoResult;

    //Class: WirelessProtocol
    //    Class containing protocol information for a device.
    class WirelessProtocol
    {
        friend class BaseStation_Impl;
        friend class NodeEeprom;

    private:
        WirelessProtocol();

        //Variable: m_pingBase
        //  The function pointer for the Ping BaseStation protocol command.
        std::function<bool(BaseStation_Impl*)> m_pingBase;

        //Variable: m_hardBaseReset
        //  The function pointer for the Hard BaseStation Reset protocol command.
        std::function<void(BaseStation_Impl*)> m_hardBaseReset;

        //Variable: m_softBaseReset
        //  The function pointer for the Soft BaseStation Reset protocol command.
        std::function<void(BaseStation_Impl*)> m_softBaseReset;

        //Variable: m_readBaseEeprom
        //  The function pointer for the Read BaseStation EEPROM protocol command.
        std::function<bool(BaseStation_Impl*, uint16, uint16&)> m_readBaseEeprom;

        //Variable: m_writeBaseEeprom
        //  The function pointer for the Write BaseStation EEPROM protocol command.
        std::function<bool(BaseStation_Impl*, uint16, uint16)> m_writeBaseEeprom;

        //Variable: m_enableBeacon
        //  The function pointer for the Enable Beacon protocol command.
        std::function<Timestamp(BaseStation_Impl*, uint32)> m_enableBeacon;

        //Variable: m_beaconStatus
        //  The function pointer for the Beacon Status protocol command.
        std::function<BeaconStatus(BaseStation_Impl*)> m_beaconStatus;

        //Variable: m_startRfSweep
        //  The function pointer for the Start RF Sweep Mode protocol command.
        std::function<void(BaseStation_Impl*, uint32, uint32, uint32, uint16)> m_startRfSweep;

        //Variable: m_longPing
        //  The function pointer for the Long Ping protocol command.
        std::function<PingResponse(BaseStation_Impl*, NodeAddress)> m_longPing;

        //Variable: m_sleep
        //  The function pointer for the Node Sleep protocol command.
        std::function<bool(BaseStation_Impl*, NodeAddress)> m_sleep;

        //Variable: m_readNodeEeprom
        //  The function pointer for the Read Node Eeprom protocol command.
        std::function<bool(BaseStation_Impl*, NodeAddress, uint16, uint16&)> m_readNodeEeprom;

        //Variable: m_writeNodeEeprom
        //  The function pointer for the Write Node Eeprom protocol command.
        std::function<bool(BaseStation_Impl*, NodeAddress, uint16, uint16)> m_writeNodeEeprom;

        //Variable: m_pageDownload
        //  The function pointer for the Node Page Download protocol command.
        std::function<bool(BaseStation_Impl*, NodeAddress, uint16, ByteStream&)> m_pageDownload;

        //Variable: m_autoBalance
        //  The function pointer for the Node AutoBalance protocol command.
        std::function<bool(BaseStation_Impl*, NodeAddress, uint8, float, AutoBalanceResult&)> m_autoBalance;

        //Variable: m_autoCal_shm
        //  The function pointer for the Node AutoCal (SHM) protocol command.
        std::function<bool(BaseStation_Impl*, NodeAddress, AutoCalResult&)> m_autoCal_shm;

        //Variable: m_autoCal_shm201
        //  The function pointer for the Node AutoCal (SHM) protocol command.
        std::function<bool(BaseStation_Impl*, NodeAddress, AutoCalResult&)> m_autoCal_shm201;

        //Variable: m_autoShuntCal
        //  The function pointer for the Node AutoShuntCal protocol command.
        std::function<bool(BaseStation_Impl*, NodeAddress, const AutoCalCmdDetails&, AutoCalResult&)> m_autoShuntCal;

        //Variable: m_getDiagnosticInfo
        //  The function pointer for the Node Get Diagnostic Info protocol command.
        std::function<bool(BaseStation_Impl*, NodeAddress, ChannelData&)> m_getDiagnosticInfo;

        //Variable: m_erase
        //  The function pointer for the Node Erase protocol command.
        std::function<bool(BaseStation_Impl*, NodeAddress)> m_erase;

        //Variable: m_startSyncSampling
        //  The function pointer for the Node Start Sync Sampling protocol command.
        std::function<bool(BaseStation_Impl*, NodeAddress)> m_startSyncSampling;

        //Variable: m_datalogSessionInfo
        //  The function pointer for the Node Datalog Session Info protocol command.
        std::function<bool(BaseStation_Impl*, NodeAddress, DatalogSessionInfoResult&)> m_datalogSessionInfo;

        //Variable: m_getDatalogData
        //  The function pointer for the Get Node Datalog Data protocol command.
        std::function<bool(BaseStation_Impl*, NodeAddress, uint32, ByteStream&, uint16&)> m_getDatalogData;

        //Variable: m_startNonSyncSampling
        //  The function pointer for the Start Non Sync Sampling protocol command.
        std::function<bool(BaseStation_Impl*, NodeAddress)> m_startNonSyncSampling;

        //Variable: m_setToIdle
        //  The function pointer for the Set to Idle protocol command.
        std::function<SetToIdleStatus(BaseStation_Impl*, NodeAddress, const BaseStation&)> m_setToIdle;

        //Variable: m_hardReset
        //  The function pointer for the Hard Reset protocol command.
        std::function<void(BaseStation_Impl*, NodeAddress)> m_hardReset;

        //Variable: m_softReset
        //  The function pointer for the Soft Reset protocol command.
        std::function<void(BaseStation_Impl*, NodeAddress)> m_softReset;

        //Variable: m_batchEepromRead
        //  The function pointer for the Node batch eeprom read protocol command.
        std::function<bool(BaseStation_Impl*, NodeAddress, uint16, std::map<uint16, uint16>&)> m_batchEepromRead;

        //Variable: m_testNodeCommProtocol
        //  The function pointer for the Test Node Communication Protocol command.
        std::function<bool(BaseStation_Impl*, NodeAddress, WirelessTypes::CommProtocol)> m_testNodeCommProtocol;

        //Variable: m_poll
        //  The function pointer for the Node Poll command.
        std::function<bool(BaseStation_Impl*, NodeAddress, const ChannelMask&, WirelessPollData&)> m_poll;

    public:
        //Constant: BASE_STATION_ADDRESS
        //  The address of our generic Base Station.
        static const uint16 BASE_STATION_ADDRESS = 0x1234;

        //Function: asppVersionFromBaseFw
        //  Gets the ASPP version from the Base Station firmware version.
        //
        //Parameters:
        //  fwVersion - The firmware version of the Base Station.
        static Version asppVersionFromBaseFw(const Version& fwVersion);

        //Function: asppVersionFromNodeFw
        //  Gets the ASPP version from the Node firmware version.
        //
        //Parameters:
        //  fwVersion - The firmware version of the Node.
        static Version asppVersionFromNodeFw(const Version& fwVersion);

        //Function: getProtocol
        //  Returns the ASPP protocol based on the ASPP version.
        //
        //Parameters:
        //  asppVersion - The <Version> of the ASPP protocol that is supported.
        static std::unique_ptr<WirelessProtocol> getProtocol(const Version& asppVersion);

        //Function: v1_0
        //  Static function to create a WirelessProtocol with version 1.0.
        static std::unique_ptr<WirelessProtocol> v1_0();

        //Function: v1_1
        //  Static function to create a WirelessProtocol with version 1.1.
        static std::unique_ptr<WirelessProtocol> v1_1();

        //Function: v1_2
        //  Static function to create a WirelessProtocol with version 1.2.
        static std::unique_ptr<WirelessProtocol> v1_2();

        //Function: v1_3
        //  Static function to create a WirelessProtocol with version 1.3.
        static std::unique_ptr<WirelessProtocol> v1_3();

        //Function: v1_4
        //  Static function to create a WirelessProtocol with version 1.4.
        static std::unique_ptr<WirelessProtocol> v1_4();

        //Function: v1_5
        //  Static function to create a WirelessProtocol with version 1.5.
        static std::unique_ptr<WirelessProtocol> v1_5();

        //Function: v1_6
        //  Static function to create a WirelessProtocol with version 1.6.
        static std::unique_ptr<WirelessProtocol> v1_6();

        //Function: v1_7
        //  Static function to create a WirelessProtocol with version 1.7.
        static std::unique_ptr<WirelessProtocol> v1_7();

        //Function: v1_8
        //  Static function to create a WirelessProtocol with version 1.8.
        static std::unique_ptr<WirelessProtocol> v1_8();

        //Function: v1_9
        //  Static function to create a WirelessProtocol with version 1.9.
        static std::unique_ptr<WirelessProtocol> v1_9();

        //Function: v3_0
        //  Static function to create a WirelessProtocol with version 3.0.
        static std::unique_ptr<WirelessProtocol> v3_0();

        //Function: v3_1
        //  Static function to create a WirelessProtocol with version 3.1.
        static std::unique_ptr<WirelessProtocol> v3_1();

    public:
        bool supportsBeaconStatus() const;
        bool supportsNodeHardReset() const;
        bool supportsNodeSoftReset() const;
        bool supportsBaseHardReset() const;
        bool supportsBaseSoftReset() const;
        bool supportsBatchEepromRead() const;
        bool supportsTestCommProtocol() const;

    public:
        //Enums: CommandID
        //  The Wireless command IDs.
        //
        //  cmdId_basePing_v1               - 0x01      - Ping Base Station (v1)
        //  cmdId_basePing_v2               - 0x0001    - Ping Base Station (v2)
        //  cmdId_shortPing_v1              - 0x02      - Short Ping (v1)
        //  cmdId_longPing_v1               - 0x0002    - Long Ping (v1)
        //  cmdId_readSingleSensor          - 0x03      - Read Single Sensor
        //  cmdId_readEeprom_v1             - 0x0003    - Read Eeprom (v1)
        //  cmdId_writeEeprom_v1            - 0x0004    - Write Eeprom (v1) 
        //  cmdId_pageDownload              - 0x05      - Page Download
        //  cmdId_erase                     - 0x06      - Erase (v1)
        //  cmdId_writeEeprom_v2            - 0x0008    - Write Eeprom (v2)
        //  cmdId_getDiagInfo_v1            - 0x0009    - Get Diagnostic Info (v1)
        //  cmdId_batchEepromRead           - 0x000A    - Batch EEPROM Read
        //  cmdId_armForDatalog             - 0x000D    - Arm for Datalogging
        //  cmdId_triggerArmedLog           - 0x000E    - Trigger Armed Datalogging
        //  cmdId_shortPing_v2              - 0x0012    - Short Ping (v2)
        //  cmdId_testNodeCommProtocol      - 0x0013    - Test Node Communication Protocol
        //  cmdId_baseReset_v2              - 0x0030    - Base Station Reset (v2)
        //  cmdId_reset_v2                  - 0x0031    - Reset (v2)
        //  cmdId_sleep                     - 0x0032    - Sleep (v1)
        //  cmdId_startStreaming            - 0x38      - Start Streaming
        //  cmdId_startLdc_v1               - 0x0038    - Start Low Duty Cycle (v1)
        //  cmdId_startLdc_v2               - 0x0039    - Start Low Duty Cycle (v2)
        //  cmdId_startSync_v1              - 0x003B    - Start Sync Sampling (v1)
        //  cmdId_logSessionInfo_v1         - 0x0040    - Get the Logged Session Info (v1)
        //  cmdId_getLogData_v1             - 0x0041    - Get Logged Data (v1)
        //  cmdId_erase_v2                  - 0x0042    - Erase Logged Data (v2)
        //  cmdId_autoBalance_v1            - 0x62      - Auto Balance (v1)
        //  cmdId_autoCal_v1                - 0x0064    - Auto Calibrate (v1)
        //  cmdId_autoBalance_v2            - 0x0065    - Auto Balance (v2)
        //  cmdId_base_readEeprom_v1        - 0x73      - Read Base Station Eeprom (v1)
        //  cmdId_base_readEeprom_v2        - 0x0073    - Read Base Station Eeprom (v2)
        //  cmdId_base_readEeprom_v3        - 0x0073    - Read Base Station Eeprom (v3)
        //  cmdId_base_writeEeprom_v1       - 0x78      - Write Base Station Eeprom (v1)
        //  cmdId_base_writeEeprom_v2       - 0x0078    - Write Base Station Eeprom (v2)
        //  cmdId_base_writeEeprom_v3       - 0x0078    - Write Base Station Eeprom (v3)
        //  cmdId_stopNode                  - 0x0090    - Set Node to Idle (v1)
        //  cmdId_stopNode_v2               - 0x0091    - Set Node to Idle (v2)
        //  cmdId_base_rfScan_v1            - 0x00ED    - Base Station Rf Energy Frequency Scan (v1)
        //  cmdId_base_setBeaconTime        - 0xBEAB    - Base Station Set Beacon Timestamp
        //  cmdId_base_setBeacon_v1         - 0xBEAC    - Base Station Enable/Disable Beacon (v1)
        //  cmdId_base_setBeacon_v2         - 0xBEAC    - Base Station Enable/Disable Beacon (v2)
        //  cmdId_base_getBeaconStatus_v1   - 0xBEAD    - Base Station Get Beacon Status (v1)
        //  cmdId_poll                      - 0xDA7A    - Poll (v1)
        enum CommandID
        {
            cmdId_basePing                  = 0x01,
            cmdId_basePing_v2               = 0x0001,
            cmdId_shortPing                 = 0x02,
            cmdId_longPing_v1               = 0x0002,
            cmdId_readSingleSensor          = 0x03,
            cmdId_readEeprom                = 0x0003,
            cmdId_writeEeprom               = 0x0004,
            cmdId_pageDownload              = 0x05,
            cmdId_erase                     = 0x06,
            cmdId_readEeprom_v2             = 0x0007,
            cmdId_writeEeprom_v2            = 0x0008,
            cmdId_getDiagInfo_v1            = 0x0009,
            cmdId_batchEepromRead           = 0x000A,
            cmdId_armForDatalog             = 0x000D,
            cmdId_triggerArmedLog           = 0x000E,
            cmdId_shortPing_v2              = 0x0012,
            cmdId_testNodeCommProtocol      = 0x0013,
            cmdId_baseReset_v2              = 0x0030,
            cmdId_reset_v2                  = 0x0031,
            cmdId_sleep                     = 0x0032,
            cmdId_startStreaming            = 0x38,
            cmdId_startLdc_v1               = 0x0038,
            cmdId_startLdc_v2               = 0x0039,
            cmdId_startSync_v1              = 0x003B,
            cmdId_logSessionInfo_v1         = 0x0040,
            cmdId_getLogData_v1             = 0x0041,
            cmdId_erase_v2                  = 0x0042,
            cmdId_autoBalance               = 0x62,
            cmdId_autoCal_v1                = 0x0064,
            cmdId_autoBalance_v2            = 0x0065,
            cmdId_base_readEeprom           = 0x73,
            cmdId_base_readEeprom_v2        = 0x0073,
            cmdId_base_writeEeprom          = 0x78,
            cmdId_base_writeEeprom_v2       = 0x0078,
            cmdId_stopNode                  = 0x0090,
            cmdId_stopNode_v2               = 0x0091,
            cmdId_base_rfScan_v1            = 0x00ED,
            cmdId_base_setBeaconTime        = 0xBEAB,
            cmdId_base_setBeacon_v1         = 0xBEAC,
            cmdId_base_setBeacon_v2         = 0xBEAC,
            cmdId_base_getBeaconStatus_v1   = 0xBEAD,
            cmdId_poll                      = 0xDA7A
        };
    };
}