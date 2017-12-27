/*******************************************************************************
Copyright(c) 2015-2017 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"
#include "WirelessProtocol.h"
#include "AutoCalInfo.h"
#include "mscl/Version.h"
#include "mscl/MicroStrain/Wireless/BaseStation.h"
#include "mscl/MicroStrain/Wireless/BaseStation_Impl.h"
#include "mscl/MicroStrain/Wireless/Features/NodeFeatures.h"

namespace mscl
{
    WirelessProtocol::WirelessProtocol()
    {
    }

    Version WirelessProtocol::asppVersionFromBaseFw(const Version& fwVersion)
    {
        if(fwVersion >= NodeFeatures::MIN_BASE_FW_PROTOCOL_1_3)
        {
            return Version(1, 3);
        }
        else if(fwVersion >= NodeFeatures::MIN_BASE_FW_PROTOCOL_1_1)
        {
            return Version(1, 1);
        }
        else
        {
            return Version(1, 0);
        }
    }

    Version WirelessProtocol::asppVersionFromNodeFw(const Version& fwVersion)
    {
        if(fwVersion >= NodeFeatures::MIN_NODE_FW_PROTOCOL_1_5)
        {
            return Version(1, 5);
        }
        else if(fwVersion >= NodeFeatures::MIN_NODE_FW_PROTOCOL_1_4)
        {
            return Version(1, 4);
        }
        else if(fwVersion >= NodeFeatures::MIN_NODE_FW_PROTOCOL_1_2)
        {
            return Version(1, 2);
        }
        else if(fwVersion >= NodeFeatures::MIN_NODE_FW_PROTOCOL_1_1)
        {
            return Version(1, 1);
        }
        else
        {
            return Version(1, 0);
        }
    }

    std::unique_ptr<WirelessProtocol> WirelessProtocol::getProtocol(const Version& asppVersion)
    {
        static const Version ASPP_1_1 = Version(1, 1);
        static const Version ASPP_1_2 = Version(1, 2);
        static const Version ASPP_1_3 = Version(1, 3);
        static const Version ASPP_1_4 = Version(1, 4);
        static const Version ASPP_1_5 = Version(1, 5);
        static const Version ASPP_1_6 = Version(1, 6);
        static const Version ASPP_1_7 = Version(1, 7);
        static const Version ASPP_3_0 = Version(3, 0);

        if(asppVersion >= ASPP_3_0) { return v3_0(); }
        if(asppVersion >= ASPP_1_7) { return v1_7(); }
        if(asppVersion >= ASPP_1_6) { return v1_6(); }
        if(asppVersion >= ASPP_1_5) { return v1_5(); }
        if(asppVersion >= ASPP_1_4) { return v1_4(); }
        if(asppVersion >= ASPP_1_3) { return v1_3(); }
        if(asppVersion >= ASPP_1_2) { return v1_2(); }
        if(asppVersion >= ASPP_1_1) { return v1_1(); }

        return v1_0();
    }

    std::unique_ptr<WirelessProtocol> WirelessProtocol::v1_0()
    {
        using namespace std::placeholders;
        static const WirelessPacket::AsppVersion ASPP1 = WirelessPacket::aspp_v1;

        std::unique_ptr<WirelessProtocol> result(new WirelessProtocol());

        //BaseStation Commands
        result->m_pingBase              = std::mem_fn(&BaseStation_Impl::protocol_ping_v1);
        result->m_readBaseEeprom        = std::mem_fn(&BaseStation_Impl::protocol_read_v1);
        result->m_writeBaseEeprom       = std::mem_fn(&BaseStation_Impl::protocol_write_v1);
        result->m_enableBeacon          = std::mem_fn(&BaseStation_Impl::protocol_enableBeacon_v1);
        result->m_setToIdle             = std::mem_fn(&BaseStation_Impl::protocol_node_setToIdle_v1);
        result->m_beaconStatus          = nullptr;
        result->m_startRfSweep          = nullptr;
        result->m_hardBaseReset         = nullptr;
        result->m_softBaseReset         = nullptr;
        result->m_testNodeCommProtocol  = nullptr;

        //Node Commands
        result->m_longPing              = std::bind(&BaseStation_Impl::protocol_node_longPing_v1, _1, ASPP1, _2);
        result->m_sleep                 = std::bind(&BaseStation_Impl::protocol_node_sleep_v1, _1, ASPP1, _2);
        result->m_readNodeEeprom        = std::mem_fn(&BaseStation_Impl::protocol_node_readEeprom_v1);
        result->m_writeNodeEeprom       = std::mem_fn(&BaseStation_Impl::protocol_node_writeEeprom_v1);
        result->m_pageDownload          = std::mem_fn(&BaseStation_Impl::protocol_node_pageDownload_v1);
        result->m_autoBalance           = std::mem_fn(&BaseStation_Impl::protocol_node_autoBalance_v1);
        result->m_erase                 = std::mem_fn(&BaseStation_Impl::protocol_node_erase_v1);
        result->m_startSyncSampling     = std::bind(&BaseStation_Impl::protocol_node_startSync_v1, _1, ASPP1, _2);
        result->m_startNonSyncSampling  = std::mem_fn(&BaseStation_Impl::protocol_node_startNonSync_v1);
        result->m_hardReset             = nullptr;
        result->m_softReset             = nullptr;
        result->m_getDatalogData        = nullptr;
        result->m_datalogSessionInfo    = nullptr;
        result->m_autoShuntCal          = nullptr;
        result->m_autoCal_shm           = nullptr;
        result->m_autoCal_shm201        = nullptr;
        result->m_getDiagnosticInfo     = nullptr;
        result->m_batchEepromRead       = nullptr;

        return result;
    }

    std::unique_ptr<WirelessProtocol> WirelessProtocol::v1_1()
    {
        using namespace std::placeholders;
        static const WirelessPacket::AsppVersion ASPP1 = WirelessPacket::aspp_v1;

        std::unique_ptr<WirelessProtocol> result = WirelessProtocol::v1_0();

        //changes from v1.0

        //BaseStation Commands
        result->m_pingBase              = std::bind(&BaseStation_Impl::protocol_ping_v2, _1, ASPP1);
        result->m_readBaseEeprom        = std::bind(&BaseStation_Impl::protocol_read_v2, _1, ASPP1, _2, _3);
        result->m_writeBaseEeprom       = std::bind(&BaseStation_Impl::protocol_write_v2, _1, ASPP1, _2, _3);
        result->m_enableBeacon          = std::bind(&BaseStation_Impl::protocol_enableBeacon_v2, _1, ASPP1, _2);
        result->m_beaconStatus          = std::bind(&BaseStation_Impl::protocol_beaconStatus_v1, _1, ASPP1);
    
        //Node Commands 
        result->m_readNodeEeprom        = std::bind(&BaseStation_Impl::protocol_node_readEeprom_v2, _1, ASPP1, _2, _3, _4);
        result->m_writeNodeEeprom       = std::bind(&BaseStation_Impl::protocol_node_writeEeprom_v2, _1, ASPP1, _2, _3, _4);

        return result;
    }

    std::unique_ptr<WirelessProtocol> WirelessProtocol::v1_2()
    {
        using namespace std::placeholders;
        static const WirelessPacket::AsppVersion ASPP1 = WirelessPacket::aspp_v1;

        std::unique_ptr<WirelessProtocol> result = WirelessProtocol::v1_1();

        //changes from v1.1

        //Node Commands
        result->m_autoBalance           = std::bind(&BaseStation_Impl::protocol_node_autoBalance_v2, _1, ASPP1, _2, _3, _4, _5);
        result->m_autoCal_shm           = std::bind(&BaseStation_Impl::protocol_node_autocal_shm_v1, _1, ASPP1, _2, _3);
        result->m_autoCal_shm201        = std::bind(&BaseStation_Impl::protocol_node_autocal_shm201_v1, _1, ASPP1, _2, _3);
        result->m_autoShuntCal          = std::bind(&BaseStation_Impl::protocol_node_autoshuntcal_v1, _1, ASPP1, _2, _3, _4, _5, _6, _7);

        return result;
    }

    std::unique_ptr<WirelessProtocol> WirelessProtocol::v1_3()
    {
        using namespace std::placeholders;
        static const WirelessPacket::AsppVersion ASPP1 = WirelessPacket::aspp_v1;

        std::unique_ptr<WirelessProtocol> result = WirelessProtocol::v1_2();

        //changes from v1.2
        
        //BaseStation Commands
        result->m_startRfSweep = std::bind(&BaseStation_Impl::protocol_startRfSweepMode_v1, _1, ASPP1, _2, _3, _4, _5);

        return result;
    }

    std::unique_ptr<WirelessProtocol> WirelessProtocol::v1_4()
    {
        using namespace std::placeholders;
        static const WirelessPacket::AsppVersion ASPP1 = WirelessPacket::aspp_v1;

        std::unique_ptr<WirelessProtocol> result = WirelessProtocol::v1_3();

        //changes from v1.3

        //Node Commands
        result->m_erase                 = std::bind(&BaseStation_Impl::protocol_node_erase_v2, _1, ASPP1, _2);
        result->m_datalogSessionInfo    = std::bind(&BaseStation_Impl::protocol_node_datalogInfo_v1, _1, ASPP1, _2, _3);
        result->m_getDatalogData        = std::bind(&BaseStation_Impl::protocol_node_getDatalogData_v1, _1, ASPP1, _2, _3, _4, _5);

        return result;
    }

    std::unique_ptr<WirelessProtocol> WirelessProtocol::v1_5()
    {
        using namespace std::placeholders;
        static const WirelessPacket::AsppVersion ASPP1 = WirelessPacket::aspp_v1;

        std::unique_ptr<WirelessProtocol> result = WirelessProtocol::v1_4();

        //changes from v1.4

        //Node Commands
        result->m_startNonSyncSampling  = std::bind(&BaseStation_Impl::protocol_node_startNonSync_v2, _1, ASPP1, _2);
        result->m_getDiagnosticInfo     = std::bind(&BaseStation_Impl::protocol_node_getDiagnosticInfo_v1, _1, ASPP1, _2, _3);

        return result;
    }

    std::unique_ptr<WirelessProtocol> WirelessProtocol::v1_6()
    {
        using namespace std::placeholders;
        static const WirelessPacket::AsppVersion ASPP1 = WirelessPacket::aspp_v1;

        std::unique_ptr<WirelessProtocol> result = WirelessProtocol::v1_5();

        //changes from v1.5

        //Base Commands
        result->m_setToIdle = std::bind(&BaseStation_Impl::protocol_node_setToIdle_v2, _1, ASPP1, _2, _3);

        return result;
    }

    std::unique_ptr<WirelessProtocol> WirelessProtocol::v1_7()
    {
        using namespace std::placeholders;
        static const WirelessPacket::AsppVersion ASPP1 = WirelessPacket::aspp_v1;

        std::unique_ptr<WirelessProtocol> result = WirelessProtocol::v1_6();

        //changes from v1.6

        //Base Commands
        result->m_testNodeCommProtocol = std::bind(&BaseStation_Impl::protocol_node_testCommProtocol, _1, ASPP1, _2, _3);

        return result;
    }

    std::unique_ptr<WirelessProtocol> WirelessProtocol::v3_0()
    {
        using namespace std::placeholders;
        static const WirelessPacket::AsppVersion ASPP3 = WirelessPacket::aspp_v3;

        //version 3.0 of the protocol redefines all commands, so not pulling in other functions
        //std::unique_ptr<WirelessProtocol> result = WirelessProtocol::v1_6();

        std::unique_ptr<WirelessProtocol> result(new WirelessProtocol());

        //Base Commands
        result->m_pingBase              = std::bind(&BaseStation_Impl::protocol_ping_v2, _1, ASPP3);
        result->m_readBaseEeprom        = std::bind(&BaseStation_Impl::protocol_read_v2, _1, ASPP3, _2, _3);
        result->m_writeBaseEeprom       = std::bind(&BaseStation_Impl::protocol_write_v2, _1, ASPP3, _2, _3);
        result->m_enableBeacon          = std::bind(&BaseStation_Impl::protocol_enableBeacon_v2, _1, ASPP3, _2);
        result->m_setToIdle             = std::bind(&BaseStation_Impl::protocol_node_setToIdle_v2, _1, ASPP3, _2, _3);
        result->m_beaconStatus          = std::bind(&BaseStation_Impl::protocol_beaconStatus_v1, _1, ASPP3);
        result->m_startRfSweep          = std::bind(&BaseStation_Impl::protocol_startRfSweepMode_v1, _1, ASPP3, _2, _3, _4, _5);
        result->m_hardBaseReset         = std::mem_fn(&BaseStation_Impl::protocol_hardReset_v2);
        result->m_softBaseReset         = std::mem_fn(&BaseStation_Impl::protocol_softReset_v2);
        result->m_testNodeCommProtocol  = std::bind(&BaseStation_Impl::protocol_node_testCommProtocol, _1, ASPP3, _2, _3);

        //Node Commands
        result->m_longPing              = std::bind(&BaseStation_Impl::protocol_node_longPing_v1, _1, ASPP3, _2);
        result->m_sleep                 = std::bind(&BaseStation_Impl::protocol_node_sleep_v1, _1, ASPP3, _2);
        result->m_readNodeEeprom        = std::bind(&BaseStation_Impl::protocol_node_readEeprom_v2, _1, ASPP3, _2, _3, _4);
        result->m_writeNodeEeprom       = std::bind(&BaseStation_Impl::protocol_node_writeEeprom_v2, _1, ASPP3, _2, _3, _4);
        result->m_pageDownload          = nullptr;
        result->m_autoBalance           = std::bind(&BaseStation_Impl::protocol_node_autoBalance_v2, _1, ASPP3, _2, _3, _4, _5);
        result->m_erase                 = std::bind(&BaseStation_Impl::protocol_node_erase_v2, _1, ASPP3, _2);
        result->m_startSyncSampling     = std::bind(&BaseStation_Impl::protocol_node_startSync_v1, _1, ASPP3, _2);
        result->m_startNonSyncSampling  = std::bind(&BaseStation_Impl::protocol_node_startNonSync_v2, _1, ASPP3, _2);
        result->m_hardReset             = std::mem_fn(&BaseStation_Impl::protocol_node_hardReset_v2);
        result->m_softReset             = std::mem_fn(&BaseStation_Impl::protocol_node_softReset_v2);
        result->m_getDatalogData        = std::bind(&BaseStation_Impl::protocol_node_getDatalogData_v1, _1, ASPP3, _2, _3, _4, _5);
        result->m_datalogSessionInfo    = std::bind(&BaseStation_Impl::protocol_node_datalogInfo_v1, _1, ASPP3, _2, _3);
        result->m_autoShuntCal          = std::bind(&BaseStation_Impl::protocol_node_autoshuntcal_v1, _1, ASPP3, _2, _3, _4, _5, _6, _7);
        result->m_autoCal_shm           = std::bind(&BaseStation_Impl::protocol_node_autocal_shm_v1, _1, ASPP3, _2, _3);
        result->m_autoCal_shm201        = std::bind(&BaseStation_Impl::protocol_node_autocal_shm201_v1, _1, ASPP3, _2, _3);
        result->m_getDiagnosticInfo     = std::bind(&BaseStation_Impl::protocol_node_getDiagnosticInfo_v1, _1, ASPP3, _2, _3);
        result->m_batchEepromRead       = std::mem_fn(&BaseStation_Impl::protocol_node_batchEepromRead_v1);

        return result;
    }

    bool WirelessProtocol::supportsBeaconStatus() const
    {
        return (m_beaconStatus != nullptr);
    }

    bool WirelessProtocol::supportsNodeHardReset() const
    {
        return (m_hardReset != nullptr);
    }

    bool WirelessProtocol::supportsNodeSoftReset() const
    {
        return (m_softReset != nullptr);
    }

    bool WirelessProtocol::supportsBaseHardReset() const
    {
        return (m_hardBaseReset != nullptr);
    }

    bool WirelessProtocol::supportsBaseSoftReset() const
    {
        return (m_softBaseReset != nullptr);
    }

    bool WirelessProtocol::supportsBatchEepromRead() const
    {
        return (m_batchEepromRead != nullptr);
    }

    bool WirelessProtocol::supportsTestCommProtocol() const
    {
        return (m_testNodeCommProtocol != nullptr);
    }
}