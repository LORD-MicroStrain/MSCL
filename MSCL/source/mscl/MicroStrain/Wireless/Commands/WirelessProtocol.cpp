/*******************************************************************************
Copyright(c) 2015-2016 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"
#include "WirelessProtocol.h"
#include "mscl/Version.h"
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

        if(asppVersion >= ASPP_1_5) { return v1_5(); }
        if(asppVersion >= ASPP_1_4) { return v1_4(); }
        if(asppVersion >= ASPP_1_3) { return v1_3(); }
        if(asppVersion >= ASPP_1_2) { return v1_2(); }
        if(asppVersion >= ASPP_1_1) { return v1_1(); }

        return v1_0();
    }

    std::unique_ptr<WirelessProtocol> WirelessProtocol::v1_0()
    {
        std::unique_ptr<WirelessProtocol> result(new WirelessProtocol());

        //BaseStation Commands
        result->m_pingBase              = std::mem_fn(&BaseStation_Impl::protocol_ping_v1);
        result->m_readBaseEeprom        = std::mem_fn(&BaseStation_Impl::protocol_read_v1);
        result->m_writeBaseEeprom       = std::mem_fn(&BaseStation_Impl::protocol_write_v1);
        result->m_enableBeacon          = std::mem_fn(&BaseStation_Impl::protocol_enableBeacon_v1);
        result->m_beaconStatus          = nullptr;
        result->m_startRfSweep          = nullptr;

        //Node Commands
        result->m_shortPing             = std::mem_fn(&BaseStation_Impl::protocol_node_shortPing_v1);
        result->m_readNodeEeprom        = std::mem_fn(&BaseStation_Impl::protocol_node_readEeprom_v1);
        result->m_writeNodeEeprom       = std::mem_fn(&BaseStation_Impl::protocol_node_writeEeprom_v1);
        result->m_pageDownload          = std::mem_fn(&BaseStation_Impl::protocol_node_pageDownload_v1);
        result->m_autoBalance           = std::mem_fn(&BaseStation_Impl::protocol_node_autoBalance_v1);
        result->m_erase                 = std::mem_fn(&BaseStation_Impl::protocol_node_erase_v1);
        result->m_startNonSyncSampling  = std::mem_fn(&BaseStation_Impl::protocol_node_startNonSync_v1);
        result->m_datalogSessionInfo    = nullptr;
        result->m_getDatalogData        = nullptr;

        return result;
    }

    std::unique_ptr<WirelessProtocol> WirelessProtocol::v1_1()
    {
        std::unique_ptr<WirelessProtocol> result = WirelessProtocol::v1_0();

        //changes from v1.0

        //BaseStation Commands
        result->m_pingBase              = std::mem_fn(&BaseStation_Impl::protocol_ping_v2);
        result->m_readBaseEeprom        = std::mem_fn(&BaseStation_Impl::protocol_read_v2);
        result->m_writeBaseEeprom       = std::mem_fn(&BaseStation_Impl::protocol_write_v2);
        result->m_enableBeacon          = std::mem_fn(&BaseStation_Impl::protocol_enableBeacon_v2);
        result->m_beaconStatus          = std::mem_fn(&BaseStation_Impl::protocol_beaconStatus_v1);
    
        //Node Commands 
        result->m_readNodeEeprom        = std::mem_fn(&BaseStation_Impl::protocol_node_readEeprom_v2);
        result->m_writeNodeEeprom       = std::mem_fn(&BaseStation_Impl::protocol_node_writeEeprom_v2);

        return result;
    }

    std::unique_ptr<WirelessProtocol> WirelessProtocol::v1_2()
    {
        std::unique_ptr<WirelessProtocol> result = WirelessProtocol::v1_1();

        //changes from v1.1

        //Node Commands
        result->m_shortPing             = std::mem_fn(&BaseStation_Impl::protocol_node_shortPing_v2);
        result->m_autoBalance           = std::mem_fn(&BaseStation_Impl::protocol_node_autoBalance_v2);

        return result;
    }

    std::unique_ptr<WirelessProtocol> WirelessProtocol::v1_3()
    {
        std::unique_ptr<WirelessProtocol> result = WirelessProtocol::v1_2();

        //changes from v1.2
        
        //BaseStation Commands
        result->m_startRfSweep          = std::mem_fn(&BaseStation_Impl::protocol_startRfSweepMode);

        return result;
    }

    std::unique_ptr<WirelessProtocol> WirelessProtocol::v1_4()
    {
        std::unique_ptr<WirelessProtocol> result = WirelessProtocol::v1_3();

        //changes from v1.3

        //Node Commands
        result->m_erase                 = std::mem_fn(&BaseStation_Impl::protocol_node_erase_v2);
        result->m_datalogSessionInfo    = std::mem_fn(&BaseStation_Impl::protocol_node_datalogInfo_v1);
        result->m_getDatalogData        = std::mem_fn(&BaseStation_Impl::protocol_node_getDatalogData_v1);

        return result;
    }

    std::unique_ptr<WirelessProtocol> WirelessProtocol::v1_5()
    {
        std::unique_ptr<WirelessProtocol> result = WirelessProtocol::v1_4();

        //changes from v1.4

        //Node Commands
        result->m_startNonSyncSampling = std::mem_fn(&BaseStation_Impl::protocol_node_startNonSync_v2);

        return result;
    }
}