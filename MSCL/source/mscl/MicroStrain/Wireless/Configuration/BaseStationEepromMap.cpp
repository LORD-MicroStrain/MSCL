/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"
#include "BaseStationEepromMap.h"
#include "mscl/MicroStrain/Wireless/BaseStationButton.h"

#include "mscl/Types.h"

namespace mscl
{
    const EepromLocation BaseStationEepromMap::SERIAL_ID                   (20, valueType_uint32, "Serial ID");
    const EepromLocation BaseStationEepromMap::BEACON_CONFIG               (40, valueType_uint16, "Beacon Config");
    const EepromLocation BaseStationEepromMap::MODEL_NUMBER                (46, valueType_uint16, "Model Number");
    const EepromLocation BaseStationEepromMap::MODEL_OPTION                (48, valueType_uint16, "Model Option");
    const EepromLocation BaseStationEepromMap::FREQUENCY                   (90, valueType_uint16, "Frequency");
    const EepromLocation BaseStationEepromMap::TX_POWER_LEVEL              (94, valueType_int16, "Transmit Power Level");
    const EepromLocation BaseStationEepromMap::BEACON_SOURCE               (96, valueType_uint16, "Beacon Source");
    const EepromLocation BaseStationEepromMap::FIRMWARE_VER                (108, valueType_uint16, "Firmware Version");
    const EepromLocation BaseStationEepromMap::FIRMWARE_VER2               (110, valueType_uint16, "Firmware Version");
    const EepromLocation BaseStationEepromMap::LEGACY_MODEL_NUMBER         (112, valueType_uint16, "Model Number");
    const EepromLocation BaseStationEepromMap::LEGACY_SERIAL_ID            (114, valueType_uint16, "Serial ID");
    const EepromLocation BaseStationEepromMap::RADIO_ID                    (118, valueType_uint16, "Radio ID");
    const EepromLocation BaseStationEepromMap::MICROCONTROLLER             (120, valueType_uint16, "Microcontroller");
    const EepromLocation BaseStationEepromMap::FW_ARCH_VER                 (122, valueType_uint16, "Firmware Arch Version");
    const EepromLocation BaseStationEepromMap::ASPP_VER_LXRS               (124, valueType_uint16, "LXRS Protocol Version");
    const EepromLocation BaseStationEepromMap::ASPP_VER_LXRS_PLUS          (126, valueType_uint16, "LXRS+ Protocol Version");
    const EepromLocation BaseStationEepromMap::ANALOG_1_NODE_ADDRESS       (128, valueType_uint16, "Analog Node Address");
    const EepromLocation BaseStationEepromMap::ANALOG_1_NODE_CHANNEL       (130, valueType_uint16, "Analog Node Channel");
    const EepromLocation BaseStationEepromMap::ANALOG_1_FLOAT_MAX          (132, valueType_float, "Analog Float Max");
    const EepromLocation BaseStationEepromMap::ANALOG_1_FLOAT_MIN          (136, valueType_float, "Analog Float Min");
    const EepromLocation BaseStationEepromMap::ANALOG_2_NODE_ADDRESS       (140, valueType_uint16, "Analog Node Address");
    const EepromLocation BaseStationEepromMap::ANALOG_2_NODE_CHANNEL       (142, valueType_uint16, "Analog Node Channel");
    const EepromLocation BaseStationEepromMap::ANALOG_2_FLOAT_MAX          (144, valueType_float, "Analog Float Max");
    const EepromLocation BaseStationEepromMap::ANALOG_2_FLOAT_MIN          (148, valueType_float, "Analog Float Min");
    const EepromLocation BaseStationEepromMap::ANALOG_3_NODE_ADDRESS       (152, valueType_uint16, "Analog Node Address");
    const EepromLocation BaseStationEepromMap::ANALOG_3_NODE_CHANNEL       (154, valueType_uint16, "Analog Node Channel");
    const EepromLocation BaseStationEepromMap::ANALOG_3_FLOAT_MAX          (156, valueType_float, "Analog Float Max");
    const EepromLocation BaseStationEepromMap::ANALOG_3_FLOAT_MIN          (160, valueType_float, "Analog Float Min");
    const EepromLocation BaseStationEepromMap::ANALOG_4_NODE_ADDRESS       (164, valueType_uint16, "Analog Node Address");
    const EepromLocation BaseStationEepromMap::ANALOG_4_NODE_CHANNEL       (166, valueType_uint16, "Analog Node Channel");
    const EepromLocation BaseStationEepromMap::ANALOG_4_FLOAT_MAX          (168, valueType_float, "Analog Float Max");
    const EepromLocation BaseStationEepromMap::ANALOG_4_FLOAT_MIN          (172, valueType_float, "Analog Float Min");
    const EepromLocation BaseStationEepromMap::ANALOG_5_NODE_ADDRESS       (176, valueType_uint16, "Analog Node Address");
    const EepromLocation BaseStationEepromMap::ANALOG_5_NODE_CHANNEL       (178, valueType_uint16, "Analog Node Channel");
    const EepromLocation BaseStationEepromMap::ANALOG_5_FLOAT_MAX          (180, valueType_float, "Analog Float Max");
    const EepromLocation BaseStationEepromMap::ANALOG_5_FLOAT_MIN          (184, valueType_float, "Analog Float Min");
    const EepromLocation BaseStationEepromMap::ANALOG_6_NODE_ADDRESS       (188, valueType_uint16, "Analog Node Address");
    const EepromLocation BaseStationEepromMap::ANALOG_6_NODE_CHANNEL       (190, valueType_uint16, "Analog Node Channel");
    const EepromLocation BaseStationEepromMap::ANALOG_6_FLOAT_MAX          (192, valueType_float, "Analog Float Max");
    const EepromLocation BaseStationEepromMap::ANALOG_6_FLOAT_MIN          (196, valueType_float, "Analog Float Min");
    const EepromLocation BaseStationEepromMap::ANALOG_7_NODE_ADDRESS       (200, valueType_uint16, "Analog Node Address");
    const EepromLocation BaseStationEepromMap::ANALOG_7_NODE_CHANNEL       (202, valueType_uint16, "Analog Node Channel");
    const EepromLocation BaseStationEepromMap::ANALOG_7_FLOAT_MAX          (204, valueType_float, "Analog Float Max");
    const EepromLocation BaseStationEepromMap::ANALOG_7_FLOAT_MIN          (208, valueType_float, "Analog Float Min");
    const EepromLocation BaseStationEepromMap::ANALOG_8_NODE_ADDRESS       (212, valueType_uint16, "Analog Node Address");
    const EepromLocation BaseStationEepromMap::ANALOG_8_NODE_CHANNEL       (214, valueType_uint16, "Analog Node Channel");
    const EepromLocation BaseStationEepromMap::ANALOG_8_FLOAT_MAX          (216, valueType_float, "Analog Float Max");
    const EepromLocation BaseStationEepromMap::ANALOG_8_FLOAT_MIN          (220, valueType_float, "Analog Float Min");
    const EepromLocation BaseStationEepromMap::ANALOG_PAIRING_ENABLE       (224, valueType_uint16, "Analog Pairing Flag");
    const EepromLocation BaseStationEepromMap::ANALOG_TIMEOUT_TIME         (226, valueType_uint16, "Analog Timeout Time");
    const EepromLocation BaseStationEepromMap::ANALOG_TIMEOUT_VOLTAGE      (228, valueType_float, "Analog Timeout Voltage");
    const EepromLocation BaseStationEepromMap::BUTTON1_LONG_FUNC           (232, valueType_uint16, "Button Long Press Function");
    const EepromLocation BaseStationEepromMap::BUTTON1_LONG_NODE           (234, valueType_uint16, "Button Long Press Node");
    const EepromLocation BaseStationEepromMap::BUTTON1_SHORT_FUNC          (236, valueType_uint16, "Button Short Press Function");
    const EepromLocation BaseStationEepromMap::BUTTON1_SHORT_NODE          (256, valueType_uint16, "Button Short Press Node");
    const EepromLocation BaseStationEepromMap::BUTTON2_LONG_FUNC           (258, valueType_uint16, "Button Long Press Function");
    const EepromLocation BaseStationEepromMap::BUTTON2_LONG_NODE           (260, valueType_uint16, "Button Long Press Node");
    const EepromLocation BaseStationEepromMap::BUTTON2_SHORT_FUNC          (262, valueType_uint16, "Button Short Press Function");
    const EepromLocation BaseStationEepromMap::BUTTON2_SHORT_NODE          (264, valueType_uint16, "Button Short Press Node");
    const EepromLocation BaseStationEepromMap::LED_ACTION                  (238, valueType_uint16, "LED Action");
    const EepromLocation BaseStationEepromMap::BAUD_RATE                   (240, valueType_uint16, "Baud Rate");
    const EepromLocation BaseStationEepromMap::CYCLE_POWER                 (250, valueType_uint16, "Cycle Power");
    const EepromLocation BaseStationEepromMap::REGION_CODE                 (280, valueType_uint16, "Region Code");
    const EepromLocation BaseStationEepromMap::ANALOG_EXCEED_MAX           (348, valueType_float, "Analog Exceedance Max");
    const EepromLocation BaseStationEepromMap::ANALOG_EXCEED_MIN           (352, valueType_float, "Analog Exceedance Min");
    const EepromLocation BaseStationEepromMap::ANALOG_EXCEED_ENABLE        (356, valueType_uint16, "Analog Exceedance Flag");
    const EepromLocation BaseStationEepromMap::MIN_SOFT_VER_MAJOR          (480, valueType_uint16, "Min Software Version");
    const EepromLocation BaseStationEepromMap::MIN_SOFT_VER_MINOR          (482, valueType_uint16, "Min Software Version");
    const EepromLocation BaseStationEepromMap::COMM_PROTOCOL               (1024, valueType_uint16, "Communication Protocol");

    bool BaseStationEepromMap::canUseCache_read(uint16 eepromLocation)
    {
        switch(eepromLocation)
        {
            case 1030:
                return false;

            default:
                return true;
        }
    }

    bool BaseStationEepromMap::canUseCache_write(uint16 eepromLocation)
    {
        switch(eepromLocation)
        {
            //eeprom locations that should always be written to the device, never using the cache to check if its the same value
            case 90:    //FREQUENCY
            case 250:   //CYCLE_POWER
            case 1024:  //RADIO_CONFIG
            case 1030:
                return false;

            //all other eeprom locations can use the cache
            default:
                return true;
        }
    }

    EepromLocation BaseStationEepromMap::buttonFuncEeprom(uint8 buttonNumber, BaseStationButton::UserAction action)
    {
        //button 1
        if(buttonNumber == 1)
        {
            if(action == BaseStationButton::action_longPress)
            {
                return BUTTON1_LONG_FUNC;
            }
            else
            {
                return BUTTON1_SHORT_FUNC;
            }
        }
        //button 2
        else if(buttonNumber == 2)
        {
            if(action == BaseStationButton::action_longPress)
            {
                return BUTTON2_LONG_FUNC;
            }
            else
            {
                return BUTTON2_SHORT_FUNC;
            }
        }

        throw Error_NotSupported("Unsupported Button Number");
    }

    EepromLocation BaseStationEepromMap::buttonNodeEeprom(uint8 buttonNumber, BaseStationButton::UserAction action)
    {
        //button 1
        if(buttonNumber == 1)
        {
            if(action == BaseStationButton::action_longPress)
            {
                return BaseStationEepromMap::BUTTON1_LONG_NODE;
            }
            else
            {
                return BaseStationEepromMap::BUTTON1_SHORT_NODE;
            }
        }
        //button 2
        else if(buttonNumber == 2)
        {
            if(action == BaseStationButton::action_longPress)
            {
                return BaseStationEepromMap::BUTTON2_LONG_NODE;
            }
            else
            {
                return BaseStationEepromMap::BUTTON2_SHORT_NODE;
            }
        }

        throw Error("Unsupported Button Number");
    }

    EepromLocation BaseStationEepromMap::findAnalogEeprom(const EepromLocation& port1Location, uint8 portNum)
    {
        //each analog eeprom group location is spaced 12 eeproms apart
        static const uint16 diffBetweenEeproms = (ANALOG_2_NODE_ADDRESS.location() - ANALOG_1_NODE_ADDRESS.location());

        //the number of eeproms before the next id
        static const uint16 diffBetweenIds = (ANALOG_2_NODE_ADDRESS.id() - ANALOG_1_NODE_ADDRESS.id());

        uint16 id = (port1Location.id() + ((portNum - 1) * diffBetweenIds));
        uint16 location = (port1Location.location() + ((portNum - 1) * diffBetweenEeproms));

        return EepromLocation(id, location, port1Location.valueType(), port1Location.description());
    }

    EepromLocation BaseStationEepromMap::analogNodeAddressEeprom(uint8 portNum)
    {
        return findAnalogEeprom(ANALOG_1_NODE_ADDRESS, portNum);
    }

    EepromLocation BaseStationEepromMap::analogNodeChannelEeprom(uint8 portNum)
    {
        return findAnalogEeprom(ANALOG_1_NODE_CHANNEL, portNum);
    }

    EepromLocation BaseStationEepromMap::analogMaxFloatEeprom(uint8 portNum)
    {
        return findAnalogEeprom(ANALOG_1_FLOAT_MAX, portNum);
    }

    EepromLocation BaseStationEepromMap::analogMinFloatEeprom(uint8 portNum)
    {
        return findAnalogEeprom(ANALOG_1_FLOAT_MIN, portNum);
    }
}