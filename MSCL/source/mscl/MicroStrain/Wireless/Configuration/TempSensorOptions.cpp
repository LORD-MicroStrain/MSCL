/*******************************************************************************
Copyright(c) 2015-2020 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"

#include "TempSensorOptions.h"

namespace mscl
{
    TempSensorOptions::TempSensorOptions():
        m_transducerType(WirelessTypes::transducer_thermocouple),
        m_thermocoupleType(WirelessTypes::tc_K),
        m_rtdType(WirelessTypes::rtd_pt10),
        m_wireType(WirelessTypes::rtd_2wire),
        m_thermistorType(WirelessTypes::thermistor_44004_44033)
    {}

    TempSensorOptions TempSensorOptions::Thermocouple(WirelessTypes::ThermocoupleType thermocouple)
    {
        TempSensorOptions t;
        t.m_transducerType = WirelessTypes::transducer_thermocouple;
        t.m_thermocoupleType = thermocouple;
        return t;
    }

    TempSensorOptions TempSensorOptions::RTD(WirelessTypes::RtdWireType wire, WirelessTypes::RtdType rtd)
    {
        TempSensorOptions t;
        t.m_transducerType = WirelessTypes::transducer_rtd;
        t.m_wireType = wire;
        t.m_rtdType = rtd;
        return t;
    }

    TempSensorOptions TempSensorOptions::Thermistor(WirelessTypes::ThermistorType thermistor)
    {
        TempSensorOptions t;
        t.m_transducerType = WirelessTypes::transducer_thermistor;
        t.m_thermistorType = thermistor;
        return t;
    }

    WirelessTypes::TransducerType TempSensorOptions::transducerType() const
    {
        return m_transducerType;
    }

    WirelessTypes::ThermocoupleType TempSensorOptions::thermocoupleType() const
    {
        return m_thermocoupleType;
    }

    WirelessTypes::RtdType TempSensorOptions::rtdType() const
    {
        return m_rtdType;
    }

    WirelessTypes::RtdWireType TempSensorOptions::rtdWireType() const
    {
        return m_wireType;
    }

    WirelessTypes::ThermistorType TempSensorOptions::thermistorType() const
    {
        return m_thermistorType;
    }
}