/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "mscl/MicroStrain/Wireless/Configuration/BaseStationEepromHelper.h"

#include "mscl/MicroStrain/Wireless/BaseStation_Impl.h"
#include "mscl/MicroStrain/Wireless/Configuration/BaseStationEepromMap.h"
#include "mscl/MicroStrain/Wireless/Features/BaseStationFeatures.h"

namespace mscl
{
    BaseStationEepromHelper::BaseStationEepromHelper(BaseStation_Impl* basestation) :
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

    Version BaseStationEepromHelper::read_asppVersion(WirelessTypes::CommProtocol commProtocol) const
    {
        static const Version MIN_BASE_FW_SUPPORTS_ASPP_VER(3, 39);

        //Don't check the ASPP Version eeprom unless the firmware version supports that eeprom
        //Note: This is because the Base can be downgraded but still keep its value in the ASPP Version eeprom which is invalid.
        Version fwVersion = read_fwVersion();
        if(fwVersion < MIN_BASE_FW_SUPPORTS_ASPP_VER)
        {
            //convert the firmware version of the ASPP version
            return WirelessProtocol::asppVersionFromBaseFw(fwVersion);
        }

        uint16 asppValue = 0;

        try
        {
            if(commProtocol == WirelessTypes::commProtocol_lxrsPlus)
            {
                asppValue = read(BaseStationEepromMap::ASPP_VER_LXRS_PLUS).as_uint16();
            }
            else
            {
                asppValue = read(BaseStationEepromMap::ASPP_VER_LXRS).as_uint16();
            }
        }
        catch(Error_NotSupported&)
        {
            //if the eeprom isn't supported, just leave it as 0
            //which will then fall back to the firmware version to
            //determine the ASPP version number
        }

        //if the aspp version is uninitialized
        if(asppValue == 0xFFFF || asppValue == 0xAAAA || asppValue == 0)
        {
            //if the ASPP version isn't supported in EEPROM, and we are looking for 250kpbs aspp version
            if(commProtocol == WirelessTypes::commProtocol_lxrs)
            {
                //convert the firmware version of the ASPP version
                return WirelessProtocol::asppVersionFromBaseFw(fwVersion);
            }

            //if we have an invalid value (or not supported) and we are looking for lxrs+
            if(commProtocol == WirelessTypes::commProtocol_lxrsPlus)
            {
                return Version(3, 0);
            }

            assert(false);  //need to add support for a new radio mode
            return Version(1, 0);
        }

        //ASPP version is good in eeprom, just return that version number
        return Version(Utils::msb(asppValue), Utils::lsb(asppValue));
    }

    WirelessTypes::CommProtocol BaseStationEepromHelper::read_commProtocol() const
    {
        const uint8 MIN_BASE_FW_SUPPORTS_COMM_PROTOCOL = 5;

        if(read_fwVersionMajor() < MIN_BASE_FW_SUPPORTS_COMM_PROTOCOL)
        {
            //doesn't support for the comm protocol eeprom
            return WirelessTypes::commProtocol_lxrs;
        }

        uint16 radioValue = 0;

        try
        {
            radioValue = read(BaseStationEepromMap::COMM_PROTOCOL).as_uint16();
        }
        catch(Error_NotSupported&)
        {
            //if the device doesn't support the radio config eeprom, it supports LXRS only
            return WirelessTypes::commProtocol_lxrs;
        }

        switch(radioValue)
        {
            case WirelessTypes::commProtocol_lxrsPlus:
            case 2:
                return WirelessTypes::commProtocol_lxrsPlus;

            case WirelessTypes::commProtocol_lxrs:
            case 0xFFFF:
            case 0xAAAA:
            case 250:
            default:
                return WirelessTypes::commProtocol_lxrs;
        }
    }

    void BaseStationEepromHelper::write_commProtocol(WirelessTypes::CommProtocol commProtocol)
    {
        const uint8 MIN_BASE_FW_SUPPORTS_COMM_PROTOCOL = 5;

        if(read_fwVersionMajor() < MIN_BASE_FW_SUPPORTS_COMM_PROTOCOL)
        {
            if(m_baseStation->features().supportsCommunicationProtocol(commProtocol))
            {
                //cannot write the eeprom, but the Base supports the given protocol, just silently return
                return;
            }

            throw Error_NotSupported("The Communication Protocol cannot be written to the BaseStation.");
        }

        write(BaseStationEepromMap::COMM_PROTOCOL, Value::UINT16(static_cast<uint16>(commProtocol)));
    }

    Version BaseStationEepromHelper::read_fwVersion() const
    {
        //read the firmware version eeprom
        uint16 fwValue1 = read(BaseStationEepromMap::FIRMWARE_VER).as_uint16();

        uint8 major = Utils::msb(fwValue1);

        //firmware versions < 4 use the scheme [Major].[Minor]
        if(major < 4)
        {
            uint8 minor = Utils::lsb(fwValue1);

            return Version(major, minor);
        }

        //firmware versions >= 4 use the scheme [Major].[svnRevision]
        uint16 fwValue2 = read(BaseStationEepromMap::FIRMWARE_VER2).as_uint16();

        //make the svn revision from the lsb of the first fw value, and the entire second fw value
        uint32 svnRevision = Utils::make_uint32(0, Utils::lsb(fwValue1), Utils::msb(fwValue2), Utils::lsb(fwValue2));

        return Version(major, svnRevision);
    }

    uint8 BaseStationEepromHelper::read_fwVersionMajor() const
    {
        return Utils::msb(read(BaseStationEepromMap::FIRMWARE_VER).as_uint16());
    }

    WirelessModels::BaseModel BaseStationEepromHelper::read_model() const
    {
        //read the model number from eeprom
        uint16 model = read(BaseStationEepromMap::MODEL_NUMBER).as_uint16();

        //if the model stored in eeprom is invalid (uninitialized)
        if(model == 0xFFFF || model == 0xAAAA || model == 0)
        {
            //this basestation uses the legacy model number

            //read the model from the legacy model eeprom location
            model = read(BaseStationEepromMap::LEGACY_MODEL_NUMBER).as_uint16();

            //convert the legacy model to the new model number and return it
            return WirelessModels::baseFromLegacyModel(model);
        }

        //read the model option from eeprom
        uint16 modelOption = read(BaseStationEepromMap::MODEL_OPTION).as_uint16();

        //build the model and model class together to form the model number
        return static_cast<WirelessModels::BaseModel>(model * 10000 + modelOption);
    }

    std::string BaseStationEepromHelper::read_serial() const
    {
        //read the serial number
        uint32 serial = read(BaseStationEepromMap::SERIAL_ID).as_uint32();

        //if the serial stored in eeprom is invalid (uninitialized)
        if(serial == 0xFFFFFFFF || serial == 0xAAAAAAAA || serial == 0)
        {
            //this basestation uses the legacy serial number

            //read the serial from the legacy serial id eeprom location
            serial = read(BaseStationEepromMap::LEGACY_SERIAL_ID).as_uint16();
        }

        //get the model number of the basestation
        WirelessModels::BaseModel fullModel = read_model();

        //split the model into its 2 pieces
        uint16 model = static_cast<uint16>(fullModel / 10000);
        uint16 modelClass = fullModel % 10000;

        //build the string result
        std::stringstream modelStr;
        modelStr << std::setfill('0') << std::setw(4) << model;

        std::stringstream modelClassStr;
        modelClassStr << std::setfill('0') << std::setw(4) << modelClass;

        std::stringstream serialStr;
        serialStr << std::setfill('0') << std::setw(5) << serial;

        return modelStr.str() + "-" + modelClassStr.str() + "-" + serialStr.str();
    }

    WirelessTypes::MicroControllerType BaseStationEepromHelper::read_microcontroller() const
    {
        //read the value from eeprom
        return static_cast<WirelessTypes::MicroControllerType>(read(BaseStationEepromMap::MICROCONTROLLER).as_uint16());
    }

    WirelessTypes::TransmitPower BaseStationEepromHelper::read_transmitPower() const
    {
        int16 val = read(BaseStationEepromMap::TX_POWER_LEVEL).as_int16();

        if(m_baseStation->features().supportsNewTransmitPowers())
        {
            return static_cast<WirelessTypes::TransmitPower>(val);
        }

        //legacy value, convert to current value before returning

        //read and return the transmit power level
        return WirelessTypes::legacyToTransmitPower(static_cast<WirelessTypes::LegacyTransmitPower>(val));
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
            code = WirelessTypes::region_europeanUnion;
        }

        return static_cast<WirelessTypes::RegionCode>(code);
    }
}
