/*******************************************************************************
Copyright(c) 2015-2019 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"
#include "MockBaseStation_Impl.h"
#include "mscl/Communication/Connection.h"
#include "Features/BaseStationFeatures.h"
#include "WirelessTypes.h"

namespace mscl
{
    //Constructor
    MockBaseStation_Impl::MockBaseStation_Impl(const BaseStationInfo& info):
        BaseStation_Impl(Connection::Mock(), 10),
        m_info(info)
    {
    }

    //Destructor
    MockBaseStation_Impl::~MockBaseStation_Impl()
    {
    }

    const BaseStationFeatures& MockBaseStation_Impl::features() const
    {
        //if the features variable hasn't been set yet
        if(m_features == NULL)
        {
            //set the features variable by creating a new BaseStationFeatures pointer
            m_features = BaseStationFeatures::create(m_info);
        }

        return *(m_features.get());
    }

    const WirelessProtocol& MockBaseStation_Impl::protocol(WirelessTypes::CommProtocol commProtocol) const
    {
        rec_mutex_lock_guard lock(m_protocolMutex);

        //given the BaseInfo up front for the MockBaseStation, so just use this
        return m_info.protocol(commProtocol);
    }

    WirelessTypes::CommProtocol MockBaseStation_Impl::communicationProtocol() const
    {
        rec_mutex_lock_guard lock(m_protocolMutex);

        //just fake it for the MockBaseStation
        return WirelessTypes::commProtocol_lxrs;
    }


    //================================================================================================
    //                                    BASE STATION COMMANDS
    //================================================================================================

    bool MockBaseStation_Impl::ping()
    {
        return true;
    }

    bool MockBaseStation_Impl::read(uint16 eepromAddress, uint16& result)
    {
        throw Error_NotSupported("Read Eeprom is not supported with MockBaseStation.");
    }

    bool MockBaseStation_Impl::write(uint16 eepromAddress, uint16 value)
    {
        throw Error_NotSupported("Write Eeprom is not supported with MockBaseStation.");
    }

    Timestamp MockBaseStation_Impl::enableBeacon()
    {
        throw Error_NotSupported("Enable Beacon is not supported with MockBaseStation.");
    }

    Timestamp MockBaseStation_Impl::enableBeacon(uint32 utcTime)
    {
        throw Error_NotSupported("Enable Beacon is not supported with MockBaseStation.");
    }

    void MockBaseStation_Impl::disableBeacon()
    {
        throw Error_NotSupported("Disable Beacon is not supported with MockBaseStation.");
    }

    BeaconStatus MockBaseStation_Impl::beaconStatus()
    {
        throw Error_NotSupported("Beacon Status is not supported with MockBaseStation.");
    }

    void MockBaseStation_Impl::startRfSweepMode()
    {
        throw Error_NotSupported("RF Mode is not supported with MockBaseStation.");
    }

    void MockBaseStation_Impl::startRfSweepMode(uint32 minFreq, uint32 maxFreq, uint32 interval, uint16 options)
    {
        throw Error_NotSupported("RF Mode is not supported with MockBaseStation.");
    }

    void MockBaseStation_Impl::cyclePower(bool checkComm)
    {
        return;
    }

    void MockBaseStation_Impl::resetRadio()
    {
        return;
    }
}