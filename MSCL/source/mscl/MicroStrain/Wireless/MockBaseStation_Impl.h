/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#pragma once

#include "mscl/MicroStrain/Wireless/BaseStationInfo.h"
#include "mscl/MicroStrain/Wireless/BaseStation_Impl.h"

namespace mscl
{
    //Class: MockBaseStation_Impl
    //    Contains the Mock implementation for a <BaseStation> object.
    class MockBaseStation_Impl : public BaseStation_Impl
    {
    public:
        //Constructor: MockBaseStation_Impl
        //  Creates a MockBaseStation_Impl object.
        //
        //Parameters:
        //  info - The <BaseStationInfo> describing this BaseStation.
        MockBaseStation_Impl(const BaseStationInfo& info);

        //Destructor: ~BaseStation_Impl
        //    Destroys the BaseStation object
        ~MockBaseStation_Impl() override;

    private:
        MockBaseStation_Impl() = delete;                                        //default constructor disabled
        MockBaseStation_Impl(const MockBaseStation_Impl&) = delete;             //copy constructor disabled
        MockBaseStation_Impl& operator=(const MockBaseStation_Impl&) = delete;  //assignement operator disabled

        //Variable: m_info
        //  The <BaseStationInfo> for the MockBaseStation to use when needed.
        BaseStationInfo m_info;

    public:
        const BaseStationFeatures& features() const override;

        const WirelessProtocol& protocol(WirelessTypes::CommProtocol commProtocol) const override;

        WirelessTypes::CommProtocol communicationProtocol() const override;

        bool ping() override;

        bool read(uint16 eepromAddress, uint16& result) override;

        bool write(uint16 eepromAddress, uint16 value) override;

        Timestamp enableBeacon() override;

        Timestamp enableBeacon(uint32 utcTime) override;

        void disableBeacon() override;

        BeaconStatus beaconStatus() override;

        void startRfSweepMode() override;

        void startRfSweepMode(uint32 minFreq, uint32 maxFreq, uint32 interval, uint16 options) override;

        void cyclePower(bool checkComm=true) override;

        void resetRadio() override;
    };
}
