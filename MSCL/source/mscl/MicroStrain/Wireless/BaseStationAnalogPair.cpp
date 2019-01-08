/*******************************************************************************
Copyright(c) 2015-2019 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"
#include "BaseStationAnalogPair.h"

namespace mscl
{
    const float BaseStationAnalogPair::CHANNEL_NOT_FLOAT = Utils::make_float(0xFF, 0xFF, 0xFF, 0x7F, Utils::bigEndian);

    BaseStationAnalogPair::BaseStationAnalogPair():
        m_nodeAddress(0),
        m_nodeChannel(1),
        m_outputVal_0V(0),
        m_outputVal_3V(65535)
    {
    }

    BaseStationAnalogPair::BaseStationAnalogPair(uint16 nodeAddress, uint8 nodeChannel, float output_0V, float output_3V):
        m_nodeAddress(nodeAddress),
        m_nodeChannel(nodeChannel),
        m_outputVal_0V(output_0V),
        m_outputVal_3V(output_3V)
    {
    }

    BaseStationAnalogPair BaseStationAnalogPair::Float(uint16 nodeAddress, uint8 nodeChannel, float output_0V, float output_3V)
    {
        //create and return a BaseStationAnalogPair object
        return BaseStationAnalogPair(nodeAddress, nodeChannel, output_0V, output_3V);
    }

    BaseStationAnalogPair BaseStationAnalogPair::NonFloat(uint16 nodeAddress, uint8 nodeChannel)
    {
        //create and return a BaseStationAnalogPair object, with CHANNEL_NOT_FLOAT for the float values
        return BaseStationAnalogPair(nodeAddress, nodeChannel, CHANNEL_NOT_FLOAT, CHANNEL_NOT_FLOAT);
    }

    uint16 BaseStationAnalogPair::nodeAddress() const
    {
        return m_nodeAddress;
    }

    void BaseStationAnalogPair::nodeAddress(uint16 address)
    {
        m_nodeAddress = address;
    }

    uint8 BaseStationAnalogPair::nodeChannel() const
    {
        return m_nodeChannel;
    }

    void BaseStationAnalogPair::nodeChannel(uint8 channelNumber)
    {
        m_nodeChannel = channelNumber;
    }

    bool BaseStationAnalogPair::expectFloatData() const
    {
        //if both of the values are NaNs
        if(Utils::isNaN(m_outputVal_0V) && Utils::isNaN(m_outputVal_3V))
        {
            //floating point is considered disabled
            return false;
        }
        
        return true;
    }

    void BaseStationAnalogPair::expectFloatData(bool enable)
    {
        //enable floating point data
        if(enable)
        {
            m_outputVal_0V = 0;
            m_outputVal_3V = 65535;
        }
        //disabling floating point data
        else
        {
            //set the values to the CHANNEL_NOT_FLOAT NaN
            m_outputVal_0V = CHANNEL_NOT_FLOAT;
            m_outputVal_3V = CHANNEL_NOT_FLOAT;
        }
    }

    float BaseStationAnalogPair::outputVal_0V() const
    {
        return m_outputVal_0V;
    }

    void BaseStationAnalogPair::outputVal_0V(float value)
    {
        m_outputVal_0V = value;

        //if setting a NaN (disabling)
        if(Utils::isNaN(value))
        {
            //set the 3V value to a NaN as well
            m_outputVal_3V = value;
        }
        else
        {
            //if the 3V output value is disabled (NaN)
            if(Utils::isNaN(m_outputVal_3V))
            {
                //update the 3V output value to be a real value
                m_outputVal_3V = value + 1.0f;
            }
        }
    }

    float BaseStationAnalogPair::outputVal_3V() const
    {
        return m_outputVal_3V;
    }

    void BaseStationAnalogPair::outputVal_3V(float value)
    {
        m_outputVal_3V = value;

        //if setting a NaN (disabling)
        if(Utils::isNaN(value))
        {
            //set the 0V value to a NaN as well
            m_outputVal_0V = value;
        }
        else
        {
            //if the 0V output value is disabled (NaN)
            if(Utils::isNaN(m_outputVal_0V))
            {
                //update the 0V output value to be a real value
                m_outputVal_0V = value - 1.0f;
            }
        }
    }
}