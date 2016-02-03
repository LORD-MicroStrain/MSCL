/*******************************************************************************
Copyright(c) 2015-2016 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"
#include "BaseStationEepromHelper.h"
#include "BaseStationEeprom.h"
#include "BaseStationEepromMap.h"
#include "mscl/MicroStrain/Wireless/BaseStation_Impl.h"
#include "mscl/MicroStrain/Wireless/Features/BaseStationFeatures.h"

namespace mscl
{
    BaseStationEepromHelper::BaseStationEepromHelper(BaseStation_Impl* basestation):
        m_baseStation(basestation)
    {
    }

    void BaseStationEepromHelper::checkAnalogPairingSupported() const
    {
        //check analog pairing is supported
        if(!m_baseStation->features().supportsAnalogPairing())
        {
            throw Error_NotSupported("Analog Pairing is not supported by this BaseStation.");
        }
    }

    Value BaseStationEepromHelper::read(const EepromLocation& location) const
    {
        return m_baseStation->readEeprom(location);
    }

    void BaseStationEepromHelper::write(const EepromLocation& location, const Value& val)
    {
        m_baseStation->writeEeprom(location, val);
    }

    WirelessTypes::TransmitPower BaseStationEepromHelper::read_transmitPower() const
    {
        int16 val = read(BaseStationEepromMap::TX_POWER_LEVEL).as_int16();

        if(m_baseStation->features().supportsNewTransmitPowers())
        {
            return static_cast<WirelessTypes::TransmitPower>(val);
        }
        else
        {
            //legacy value, convert to current value before returning

            //read and return the transmit power level
            return WirelessTypes::legacyToTransmitPower(static_cast<WirelessTypes::LegacyTransmitPower>(val));
        }
    }

    void BaseStationEepromHelper::write_transmitPower(WirelessTypes::TransmitPower power)
    {
        int16 valToWrite = 0;

        if(m_baseStation->features().supportsNewTransmitPowers())
        {
            valToWrite = static_cast<int16>(power);
        }
        else
        {
            //need to write the legacy value for the device to understand it
            valToWrite = static_cast<int16>(WirelessTypes::transmitPowerToLegacy(power));
        }

        //write the transmit power level to the node
        write(BaseStationEepromMap::TX_POWER_LEVEL, Value(valueType_int16, valToWrite));
    }

    BaseStationButton BaseStationEepromHelper::read_button(uint8 buttonNumber, BaseStationButton::UserAction action) const
    {
        //check buttons are supported
        if(!m_baseStation->features().supportsButtons())
        {
            throw Error_NotSupported("Button Configuration is not supported by this BaseStation.");
        }

        //find the eeprom locations to read from
        EepromLocation funcEeprom = BaseStationEepromMap::buttonFuncEeprom(buttonNumber, action);
        EepromLocation nodeEeprom = BaseStationEepromMap::buttonNodeEeprom(buttonNumber, action);

        //read the function and node and build a button
        return BaseStationButton(static_cast<BaseStationButton::Command>(read(funcEeprom).as_uint16()), read(nodeEeprom).as_uint16());
    }

    void BaseStationEepromHelper::write_button(uint8 buttonNumber, BaseStationButton::UserAction action, const BaseStationButton& btn)
    {
        //check buttons are supported
        if(!m_baseStation->features().supportsButtons())
        {
            throw Error_NotSupported("Button Configuration is not supported by this BaseStation.");
        }

        //find the eeprom locations to write to
        EepromLocation funcEeprom = BaseStationEepromMap::buttonFuncEeprom(buttonNumber, action);
        EepromLocation nodeEeprom = BaseStationEepromMap::buttonNodeEeprom(buttonNumber, action);

        //write the button's function/command
        write(funcEeprom, Value::UINT16(static_cast<uint16>(btn.command())));

        //write the button's node address
        write(nodeEeprom, Value::UINT16(btn.nodeAddress()));
    }

    bool BaseStationEepromHelper::read_analogPairingEnabled() const
    {
        //throw exception is analog pairing isn't supported
        checkAnalogPairingSupported();

        //read the value from eeprom
        return (read(BaseStationEepromMap::ANALOG_PAIRING_ENABLE).as_uint16() == 1);
    }

    void BaseStationEepromHelper::write_analogPairingEnabled(bool enable)
    {
        //throw exception is analog pairing isn't supported
        checkAnalogPairingSupported();

        //write the value to eeprom
        write(BaseStationEepromMap::ANALOG_PAIRING_ENABLE, Value::UINT16(static_cast<uint16>(enable)));
    }

    uint16 BaseStationEepromHelper::read_analogTimeoutTime() const
    {
        //throw exception is analog pairing isn't supported
        checkAnalogPairingSupported();

        //read and return the value from eeprom
        return read(BaseStationEepromMap::ANALOG_TIMEOUT_TIME).as_uint16();
    }

    void BaseStationEepromHelper::write_analogTimeoutTime(uint16 seconds)
    {
        //throw exception is analog pairing isn't supported
        checkAnalogPairingSupported();

        //write the value to eeprom
        write(BaseStationEepromMap::ANALOG_TIMEOUT_TIME, Value::UINT16(seconds));
    }

    float BaseStationEepromHelper::read_analogTimeoutVoltage() const
    {
        //throw exception is analog pairing isn't supported
        checkAnalogPairingSupported();

        //read and return the value from eeprom
        return read(BaseStationEepromMap::ANALOG_TIMEOUT_VOLTAGE).as_float();
    }

    void BaseStationEepromHelper::write_analogTimeoutVoltage(float voltage)
    {
        //throw exception is analog pairing isn't supported
        checkAnalogPairingSupported();

        //write the value to eeprom
        write(BaseStationEepromMap::ANALOG_TIMEOUT_VOLTAGE, Value::FLOAT(voltage));
    }

    bool BaseStationEepromHelper::read_analogExceedanceEnabled() const
    {
        //throw exception is analog pairing isn't supported
        checkAnalogPairingSupported();

        //read and return the value from eeprom
        return (read(BaseStationEepromMap::ANALOG_EXCEED_ENABLE).as_uint16() == 1);
    }

    void BaseStationEepromHelper::write_analogExceedanceEnabled(bool enable)
    {
        //throw exception is analog pairing isn't supported
        checkAnalogPairingSupported();

        //write the value to eeprom
        write(BaseStationEepromMap::ANALOG_EXCEED_ENABLE, Value::UINT16(static_cast<uint16>(enable)));
    }

    BaseStationAnalogPair BaseStationEepromHelper::read_analogPair(uint8 portNumber) const
    {
        //throw exception is analog pairing isn't supported
        checkAnalogPairingSupported();

        EepromLocation analogEE_nodeAddress = BaseStationEepromMap::analogNodeAddressEeprom(portNumber);
        EepromLocation analogEE_nodeChannel = BaseStationEepromMap::analogNodeChannelEeprom(portNumber);
        EepromLocation analogEE_maxFloat = BaseStationEepromMap::analogMaxFloatEeprom(portNumber);
        EepromLocation analogEE_minFloat = BaseStationEepromMap::analogMinFloatEeprom(portNumber);

        //read all the eeprom values
        uint16 nodeAddress = read(analogEE_nodeAddress).as_uint16();
        uint8 nodeChannel = static_cast<uint8>(read(analogEE_nodeChannel).as_uint16());
        float maxFloat = read(analogEE_maxFloat).as_float();
        float minFloat = read(analogEE_minFloat).as_float();

        //build and return a BaseStationAnalogPair
        return BaseStationAnalogPair::Float(nodeAddress, nodeChannel, minFloat, maxFloat);
    }

    void BaseStationEepromHelper::write_analogPair(uint8 portNumber, const BaseStationAnalogPair& pair)
    {
        //throw exception is analog pairing isn't supported
        checkAnalogPairingSupported();

        EepromLocation analogEE_nodeAddress = BaseStationEepromMap::analogNodeAddressEeprom(portNumber);
        EepromLocation analogEE_nodeChannel = BaseStationEepromMap::analogNodeChannelEeprom(portNumber);
        EepromLocation analogEE_maxFloat = BaseStationEepromMap::analogMaxFloatEeprom(portNumber);
        EepromLocation analogEE_minFloat = BaseStationEepromMap::analogMinFloatEeprom(portNumber);

        //write all the values to eeprom
        write(analogEE_nodeAddress, Value::UINT16(pair.nodeAddress()));

        //a value of 0xFF should disable the channel (actually write a 0xFFFF)
        uint16 chToWrite = pair.nodeChannel();
        if(chToWrite == 0xFF)
        {
            chToWrite = 0xFFFF;
        }
        write(analogEE_nodeChannel, Value::UINT16(chToWrite));

        write(analogEE_maxFloat, Value::FLOAT(pair.outputVal_3V()));
        write(analogEE_minFloat, Value::FLOAT(pair.outputVal_0V()));
    }

    WirelessTypes::RegionCode BaseStationEepromHelper::read_regionCode() const
    {
        //Note: this function can never use the BaseStaionFeatures/BaseStationInfo call, as BaseStationInfo relies on this function.

        //read the value from eeprom
        uint16 code = read(BaseStationEepromMap::REGION_CODE).as_uint16();

        //if set to an "uninitialized" value
        if(code == 0xAAAA || code == 0xFFFF)
        {
            code = WirelessTypes::region_usa;
        }
        //to support legacy base stations, a code of 0xFFFE should be treated as Europe
        else if(code == 0xFFFE)
        {
            code = WirelessTypes::region_europe;
        }

        return static_cast<WirelessTypes::RegionCode>(code);
    }
}