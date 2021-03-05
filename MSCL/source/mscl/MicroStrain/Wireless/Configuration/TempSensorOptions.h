/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/

#pragma once

#include "mscl/MicroStrain/Wireless/WirelessTypes.h"

namespace mscl
{
    //API Class: TempSensorOptions
    //    Options to adjust the temperature sensor for a WirelessNode.
    class TempSensorOptions
    {
    private:
        TempSensorOptions();

    public:
        //API Function: Thermocouple
        //  Creates a TempSensorOptions object with Thermocouple options.
        //
        //Parameters:
        //  thermocouple - The <WirelessTypes::ThermocoupleType> to set.
        static TempSensorOptions Thermocouple(WirelessTypes::ThermocoupleType thermocouple);

        //API Function: RTD
        //  Creates a TempSensorOptions object with RTD options.
        //
        //Parameters:
        //  wire - The <WirelessTypes::RtdWireType> to set.
        //  rtd - The <WirelessTypes::RtdType> to set.
        static TempSensorOptions RTD(WirelessTypes::RtdWireType wire, WirelessTypes::RtdType rtd);

        //API Function: Thermistor
        //  Creates a TempSensorOptions object with Thermistor options.
        //
        //Parameters:
        //  thermistor - The <WirelessTypes::ThermistorType> to set.
        static TempSensorOptions Thermistor(WirelessTypes::ThermistorType thermistor);

    private:
        //Variable: m_transducerType
        //  The <WirelessTypes::TransducerType>.
        WirelessTypes::TransducerType m_transducerType;

        //Variable: m_thermocoupleType
        //  The <WirelessTypes::ThermocoupleType>.
        WirelessTypes::ThermocoupleType m_thermocoupleType;

        //Variable: m_rtdType
        //  The <WirelessTypes::RtdType>.
        WirelessTypes::RtdType m_rtdType;

        //Variable: m_wireType
        //  The <WirelessTypes::RtdWireType>.
        WirelessTypes::RtdWireType m_wireType;

        //Variable: m_thermistorType
        //  The <WirelessTypes::ThermistorType>.
        WirelessTypes::ThermistorType m_thermistorType;

    public:
        //API Function: transducerType
        //  Gets the <WirelessTypes::TransducerType> set in this options object.
        WirelessTypes::TransducerType transducerType() const;

        //API Function: thermocoupleType
        //  Gets the <WirelessTypes::ThermocoupleType> set in this options object.
        //  Note: this is only valid if <transducerType> returns <WirelessTypes::TransducerType::transducer_thermocouple>.
        WirelessTypes::ThermocoupleType thermocoupleType() const;

        //API Function: rtdType
        //  Gets the <WirelessTypes::RtdType> set in this options object.
        //  Note: this is only valid if <transducerType> returns <WirelessTypes::TransducerType::transducer_rtd>.
        WirelessTypes::RtdType rtdType() const;

        //API Function: rtdWireType
        //  Gets the <WirelessTypes::RtdWireType> set in this options object.
        //  Note: this is only valid if <transducerType> returns <WirelessTypes::TransducerType::transducer_rtd>.
        WirelessTypes::RtdWireType rtdWireType() const;

        //API Function: thermistorType
        //  Gets the <WirelessTypes::ThermistorType> set in this options object.
        //  Note: this is only valid if <transducerType> returns <WirelessTypes::TransducerType::transducer_thermistor>.
        WirelessTypes::ThermistorType thermistorType() const;
    };
}