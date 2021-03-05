/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "BaseStation_Impl.h"
#include "BaseStationInfo.h"
#include "mscl/Communication/Connection.h"
#include "mscl/Types.h"

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
        virtual ~MockBaseStation_Impl();

    private:
        MockBaseStation_Impl() = delete;                                        //default constructor disabled
        MockBaseStation_Impl(const MockBaseStation_Impl&) = delete;             //copy constructor disabled
        MockBaseStation_Impl& operator=(const MockBaseStation_Impl&) = delete;  //assignement operator disabled

        //Variable: m_info
        //  The <BaseStationInfo> for the MockBaseStation to use when needed.
        BaseStationInfo m_info;

    public:
        virtual const BaseStationFeatures& features() const override;

        virtual const WirelessProtocol& protocol(WirelessTypes::CommProtocol commProtocol) const override;

        virtual WirelessTypes::CommProtocol communicationProtocol() const override;

        virtual bool ping() override;

        virtual bool read(uint16 eepromAddress, uint16& result) override;

        virtual bool write(uint16 eepromAddress, uint16 value) override;

        virtual Timestamp enableBeacon() override;

        virtual Timestamp enableBeacon(uint32 utcTime) override;

        virtual void disableBeacon() override;

        virtual BeaconStatus beaconStatus() override;

        void startRfSweepMode() override;

        virtual void startRfSweepMode(uint32 minFreq, uint32 maxFreq, uint32 interval, uint16 options) override;

        void cyclePower(bool checkComm=true) override;

        void resetRadio() override;
    };
}