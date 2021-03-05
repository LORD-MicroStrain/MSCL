/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/

#pragma once

#include "mscl/Types.h"

namespace mscl
{
    //API Class: BaseStationAnalogPair
    //    Represents an Analog Pairing on a BaseStation.
    class BaseStationAnalogPair
    {
    private:
        //Constructor: BaseStationAnalogPair
        //    Creates a BaseStationAnalogPair object with the provided parameters.
        //    Note: This constructor is private to enforce using ::Float and ::NonFloat static functions for construction.
        BaseStationAnalogPair(uint16 nodeAddress, uint8 nodeChannel, float output_0V, float output_3V);

    public:
        //API Constant: CHANNEL_NOT_FLOAT
        //    A (NaN) value representing that the paired node channel is not transmitting float point values.
        //    The outputVal_0V and outputVal_3V values should be set to this value if not being paired to a channel transmitting floats.
        static const float CHANNEL_NOT_FLOAT;

        //API Class: BaseStationAnalogPair
        //    Creates a default constructed BaseStationAnalogPair object.
        BaseStationAnalogPair();

        //API Function: Float
        //    Creates a BaseStationAnalogPair object to be paired to WirelessNode's channel that is transmitting floating point values.
        //
        //Parameters:
        //    nodeAddress - The node address to pair to.
        //    nodeChannel - The node's channel number to pair to.
        //    output_0V - The floating point value that represents 0 volt output.
        //    output_3V - The floating point value that represents 3 volt output.
        //
        //Returns:
        //    A <BaseStationAnalogPair> object created with the specified parameters.
        static BaseStationAnalogPair Float(uint16 nodeAddress, uint8 nodeChannel, float output_0V, float output_3V);

        //API Function: NonFloat
        //    Creates a BaseStationAnalogPair object to be paired to WirelessNode's channel that is NOT transmitting floating point values.
        //
        //Parameters:
        //    nodeAddress - The node address to pair to.
        //    nodeChannel - The node's channel number to pair to.
        //
        //Returns:
        //    A <BaseStationAnalogPair> object created with the specified parameters.
        static BaseStationAnalogPair NonFloat(uint16 nodeAddress, uint8 nodeChannel);

    private:
        //Variable: m_nodeAddress
        //    The node address to pair.
        uint16 m_nodeAddress;

        //Variable: m_nodeChannel
        //    The node's channel to pair.
        uint8 m_nodeChannel;

        //Variable: m_outputVal_0V
        //    The floating point value that represents 0 volts, if the node/channel is sending floating point data.
        float m_outputVal_0V;

        //Variable: m_outputVal_3V
        //    The floating point value that represents 3 volts, if the node/channel is sending floating point data.
        float m_outputVal_3V;

    public:
        //API Function: nodeAddress
        //    Gets the node address to be paired with that is currently set in this object.
        //
        //Returns:
        //    The node address to be paired with that is currently set in this object.
        uint16 nodeAddress() const;

        //API Function: nodeAddress
        //    Sets the node address of the WirelessNode to be paired with.
        //
        //Parameters:
        //    address - The node address to be paired with.
        void nodeAddress(uint16 address);

        //API Function: nodeChannel
        //    Gets the node's channel to be paired with that is currently set in this object.
        //
        //Returns:
        //    The node's channel to be paired with that is currently set in this object.
        uint8 nodeChannel() const;

        //API Function: nodeChannel
        //    Sets the node's channel of the WirelessNode to be paired with.
        //
        //Parameters:
        //    channelNumber - The node's channel number (ch1 = 1, ch8 = 8) to be paired with.
        void nodeChannel(uint8 channelNumber);

        //API Function: floatData
        //    Checks whether floating point data is expected in this object.
        //    
        //Returns:
        //    True if floating point data is expected, false if it is not.
        bool expectFloatData() const;

        //API Function: floatData
        //    Sets whether floating point data is expected or not.
        //    Note: If enabling, this will set outputVal_0V to 0 and outputVal_3V to 65535. You should update these values accordingly.
        //    Note: If disabling, this will set outputVal_0V and outputVal_3V to <CHANNEL_NOT_FLOAT>.
        //
        //Parameters:
        //    enable - Whether to enable or disable the expectation for floating point data.
        void expectFloatData(bool enable);

        //API Function: outputVal_0V
        //    Gets the output value that represents 0 Volts that is currently set in this object.
        //
        //Returns:
        //    The output value that represents 0 Volts.
        float outputVal_0V() const;

        //API Function: outputVal_0V
        //    Sets the output value that represents 0 Volts.
        //    Note: Setting this to a NaN (<CHANNEL_NOT_FLOAT>) disables the float expectation and sets outputVal_3V to <CHANNEL_NOT_FLOAT> as well.
        //    Note: If outputVal_3V is set to <CHANNEL_NOT_FLOAT> when this is called with a real value, outputVal_3V will be updated to (value + 1.0). 
        //
        //Parameters:
        //    value - The output value to represent 0 Volts.
        void outputVal_0V(float value);

        //API Function: outputVal_3V
        //    Gets the output value that represents 3 Volts that is currently set in this object.
        //
        //Returns:
        //    The output value that represents 3 Volts.
        float outputVal_3V() const;

        //API Function: outputVal_3V
        //    Sets the output value that represents 3 Volts.
        //    Note: Setting this to a NaN (<CHANNEL_NOT_FLOAT>) disables the float expectation and sets outputVal_0V to <CHANNEL_NOT_FLOAT> as well.
        //    Note: If outputVal_0V is set to <CHANNEL_NOT_FLOAT> when this is called with a real value, outputVal_0V will be updated to (value - 1.0). 
        //
        //Parameters:
        //    value - The output value to represent 3 Volts.
        void outputVal_3V(float value);
    };
}