/*******************************************************************************
Copyright(c) 2015-2016 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"
#include "WirelessProtocol.h"
#include "mscl/MicroStrain/Wireless/BaseStation_Impl.h"

namespace mscl
{
    WirelessProtocol::WirelessProtocol()
    {
    }

    std::unique_ptr<WirelessProtocol> WirelessProtocol::chooseBaseStationProtocol(const Version& fwVersion)
    {
        //the BaseStation min fw version for each protocol
        static const Version MIN_FW_PROTOCOL_1_3(4, 30448);
        static const Version MIN_FW_PROTOCOL_1_1(4, 0);

        if(fwVersion >= MIN_FW_PROTOCOL_1_3)
        {
            return v1_3();
        }
        else if(fwVersion >= MIN_FW_PROTOCOL_1_1)
        {
            return v1_1();
        }
        else
        {
            return v1_0();
        }
    }

    std::unique_ptr<WirelessProtocol> WirelessProtocol::chooseNodeProtocol(const Version& fwVersion)
    {
        //the Node min fw version for each protocol
        static const Version MIN_FW_PROTOCOL_1_2(10, 0);
        static const Version MIN_FW_PROTOCOL_1_1(8, 21);

        if(fwVersion >= MIN_FW_PROTOCOL_1_2)
        {
            return v1_2();
        }
        else if(fwVersion >= MIN_FW_PROTOCOL_1_1)
        {
            return v1_1();
        }
        else
        {
            return v1_0();
        }
    }

    std::unique_ptr<WirelessProtocol> WirelessProtocol::v1_0()
    {
        std::unique_ptr<WirelessProtocol> result(new WirelessProtocol());

        //BaseStation Commands
        result->m_pingBase             = std::mem_fn(&BaseStation_Impl::ping_v1);
        result->m_readBaseEeprom       = std::mem_fn(&BaseStation_Impl::read_v1);
        result->m_writeBaseEeprom      = std::mem_fn(&BaseStation_Impl::write_v1);
        result->m_enableBeacon         = std::mem_fn(&BaseStation_Impl::enableBeacon_v1);
        result->m_beaconStatus         = nullptr;
        result->m_startRfSweep         = nullptr;

        //Node Commands
        result->m_shortPing            = std::mem_fn(&BaseStation_Impl::node_shortPing_v1);
        result->m_readNodeEeprom       = std::mem_fn(&BaseStation_Impl::node_readEeprom_v1);
        result->m_writeNodeEeprom      = std::mem_fn(&BaseStation_Impl::node_writeEeprom_v1);
        result->m_pageDownload         = std::mem_fn(&BaseStation_Impl::node_pageDownload_v1);
        result->m_autoBalance          = std::mem_fn(&BaseStation_Impl::node_autoBalance_v1);

        return result;
    }

    std::unique_ptr<WirelessProtocol> WirelessProtocol::v1_1()
    {
        std::unique_ptr<WirelessProtocol> result = WirelessProtocol::v1_0();

        //changes from v1.0

        //BaseStation Commands
        result->m_pingBase            = std::mem_fn(&BaseStation_Impl::ping_v2);
        result->m_readBaseEeprom      = std::mem_fn(&BaseStation_Impl::read_v2);
        result->m_writeBaseEeprom     = std::mem_fn(&BaseStation_Impl::write_v2);
        result->m_enableBeacon        = std::mem_fn(&BaseStation_Impl::enableBeacon_v2);
        result->m_beaconStatus        = std::mem_fn(&BaseStation_Impl::beaconStatus_v1);

        //Node Commands
        result->m_readNodeEeprom      = std::mem_fn(&BaseStation_Impl::node_readEeprom_v2);
        result->m_writeNodeEeprom     = std::mem_fn(&BaseStation_Impl::node_writeEeprom_v2);

        return result;
    }

    std::unique_ptr<WirelessProtocol> WirelessProtocol::v1_2()
    {
        std::unique_ptr<WirelessProtocol> result = WirelessProtocol::v1_1();

        //changes from v1.1

        //Node Commands
        result->m_shortPing            = std::mem_fn(&BaseStation_Impl::node_shortPing_v2);
        result->m_autoBalance          = std::mem_fn(&BaseStation_Impl::node_autoBalance_v2);

        return result;
    }

    std::unique_ptr<WirelessProtocol> WirelessProtocol::v1_3()
    {
        std::unique_ptr<WirelessProtocol> result = WirelessProtocol::v1_2();

        //changes from v1.2
        
        //BaseStation Commands
        result->m_startRfSweep         = std::mem_fn(&BaseStation_Impl::startRfSweepMode);

        return result;
    }
}