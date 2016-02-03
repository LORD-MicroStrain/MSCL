/*******************************************************************************
Copyright(c) 2015-2016 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include <functional>
#include <memory>
#include "mscl/Timestamp.h"
#include "AutoBalanceResult.h"
#include "BaseStation_BeaconStatus.h"

namespace mscl
{
    //forward declarations
    class BaseStation_Impl;

    //Class: WirelessProtocol
    //    Class containing protocol information for a device.
    class WirelessProtocol
    {
        friend class BaseStation_Impl;
        friend class NodeEeprom;

    private:
        WirelessProtocol();                                        //default constructor disabled
        WirelessProtocol(const WirelessProtocol&);                //copy constructor disabled
        WirelessProtocol& operator=(const WirelessProtocol&);    //assignment operator disabled

        //Variable: m_pingBase
        //    The function pointer for the Ping BaseStation protocol command.
        std::function<bool(BaseStation_Impl*)> m_pingBase;

        //Variable: m_readBaseEeprom
        //    The function pointer for the Read BaseStation EEPROM protocol command.
        std::function<bool(BaseStation_Impl*, uint16, uint16&)> m_readBaseEeprom;

        //Variable: m_writeBaseEeprom
        //    The function pointer for the Write BaseStation EEPROM protocol command.
        std::function<bool(BaseStation_Impl*, uint16, uint16)> m_writeBaseEeprom;

        //Variable: m_enableBeacon
        //    The function pointer for the Enable Beacon protocol command.
        std::function<Timestamp(BaseStation_Impl*, uint32)> m_enableBeacon;

        //Variable: m_beaconStatus
        //    The function pointer for the Beacon Status protocol command.
        std::function<BeaconStatus(BaseStation_Impl*)> m_beaconStatus;

        //Variable: m_startRfSweep
        //    The function pointer for the Start RF Sweep Mode protocol command.
        std::function<void(BaseStation_Impl*, uint32, uint32, uint32, uint16)> m_startRfSweep;

        //Variable: m_shortPing
        //    The function pointer for the Short Ping Node protocol command.
        std::function<bool(BaseStation_Impl*, NodeAddress)> m_shortPing;

        //Variable: m_readNodeEeprom
        //    The function pointer for the Read Node Eeprom protocol command.
        std::function<bool(BaseStation_Impl*, NodeAddress, uint16, uint16&)> m_readNodeEeprom;

        //Variable: m_writeNodeEeprom
        //    The function pointer for the Write Node Eeprom protocol command.
        std::function<bool(BaseStation_Impl*, NodeAddress, uint16, uint16)> m_writeNodeEeprom;

        //Variable: m_pageDownload
        //    The function pointer for the Node Page Download protocol command.
        std::function<bool(BaseStation_Impl*, NodeAddress, uint16, ByteStream&)> m_pageDownload;

        //Variable: m_autoBalance
        //    The function pointer for the Node AutoBalance protocol command.
        std::function<bool(BaseStation_Impl*, NodeAddress, uint8, float, AutoBalanceResult&)> m_autoBalance;

    public:
        //Constant: BASE_STATION_ADDRESS
        //    The address of our generic Base Station.
        static const uint16 BASE_STATION_ADDRESS = 0x1234;

        //Function: chooseBaseStationProtocol
        //    Returns the correct protocol version based on the Base Station's firmware vesrion.
        //
        //Parameters:
        //    fwVersion - The firmware version of the Base Station.
        static std::unique_ptr<WirelessProtocol> chooseBaseStationProtocol(const Version& fwVersion);

        //Function: chooseBaseStationProtocol
        //    Returns the correct protocol version based on the Wireless Node's firmware vesrion.
        //
        //Parameters:
        //    fwVersion - The firmware version of the Node.
        static std::unique_ptr<WirelessProtocol> chooseNodeProtocol(const Version& fwVersion);

        //Function: v1_0
        //    Static function to create a WirelessProtocol with version 1.0.
        static std::unique_ptr<WirelessProtocol> v1_0();

        //Function: v1_1
        //    Static function to create a WirelessProtocol with version 1.1.
        static std::unique_ptr<WirelessProtocol> v1_1();

        //Function: v1_2
        //    Static function to create a WirelessProtocol with version 1.2.
        static std::unique_ptr<WirelessProtocol> v1_2();

        //Function: v1_3
        //    Static function to create a WirelessProtocol with version 1.3.
        static std::unique_ptr<WirelessProtocol> v1_3();
    };
}