/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "mscl/Types.h"
#include "mscl/MicroStrain/Wireless/WirelessTypes.h"

namespace mscl
{
    //API Struct: ShuntCalCmdInfo
    //  Contains data for the shunt AutoCal command.
    struct ShuntCalCmdInfo
    {
        //API Variable: useInternalShunt
        //  Whether the Shunt Cal should use an internal shunt (true), or external shunt (false).
        //  When using an internal shunt, the process will usually take under 1 second to complete.
        //  When using an external shunt, the process will take about 30 seconds and involves the node
        //  being sampled without the shunt applied, followed by an LED change indicating to apply the shunt.
        //  Please see the product documentation for more information.
        bool useInternalShunt;

        //API Variable: numActiveGauges
        //  The number of active gauges for the Shunt Cal command.
        uint8 numActiveGauges;

        //API Variable: gaugeResistance
        //  The gauge resistance for the Shunt Cal command.
        uint16 gaugeResistance;

        //API Variable: shuntResistance
        //  The shunt resistance for the Shunt Cal command.
        uint32 shuntResistance;

        //API Variable: gaugeFactor
        //  The gauge factor for the Shunt Cal command.
        float gaugeFactor;

        //API Variable: inputRange
        //  The <WirelessTypes::InputRange> to use when performing the Shunt Cal command.
        WirelessTypes::InputRange inputRange;

        //API Variable: hardwareOffset
        //  The hardware offset to use when performing the Shunt Cal command.
        uint16 hardwareOffset;

        //API Variable: excitationVoltage;
        //  The excitation voltage of the Node when performing the Shunt Cal command.
        //  Note: This will only be used if the Node supports excitation voltage configuration (see <NodeFeatures::supportsExcitationVoltageConfig>).
        WirelessTypes::Voltage excitationVoltage;

        //API Constructor: ShuntCalCmdInfo
        //  Creates a default constructed ShuntCalCmdInfo object.
        ShuntCalCmdInfo():
            useInternalShunt(true),
            numActiveGauges(0),
            gaugeResistance(0),
            shuntResistance(0),
            gaugeFactor(0.0f),
            inputRange(WirelessTypes::range_1mV),
            hardwareOffset(0),
            excitationVoltage(WirelessTypes::voltage_1500mV)
        { }
    };
}