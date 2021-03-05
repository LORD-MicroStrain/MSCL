/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "EepromLocation.h"
#include "mscl/MicroStrain/Wireless/BaseStationButton.h"

namespace mscl
{
    //Class: BaseStationEepromMap
    //    Contains information on every EEPROM available on BaseStations
    class BaseStationEepromMap
    {
    private:
        BaseStationEepromMap();                                            //disabled default constructor
        BaseStationEepromMap(const BaseStationEepromMap&);                //disabled copy constructor
        BaseStationEepromMap& operator=(const BaseStationEepromMap&);    //disabled assignement operator

    private:
        static EepromLocation findAnalogEeprom(const EepromLocation& port1Location, uint8 portNum);

    public:
        //Function: canUseCache_read
        //    Gets whether or not the specified eeprom location can use the eeprom cache for reading, or should always be read from the BaseStation.
        //
        //Parameters:
        //    eepromLocation - The eepromLocation that is in question
        //
        //Returns:
        //    true if the location can use the cache for reading, false if the location should be read from the BaseStation.
        static bool canUseCache_read(uint16 eepromLocation);

        //Function: canUseCache_write
        //    Gets whether or not the specified eeprom location can use the eeprom cache for writing, or should always be written to the BaseStation.
        //
        //Parameters:
        //    eepromLocation - The eepromLocation that is in question
        //
        //Returns:
        //    true if the location can use the cache for writing, false if the location should always be written to the BaseStation.
        static bool canUseCache_write(uint16 eepromLocation);

        static EepromLocation buttonFuncEeprom(uint8 buttonNumber, BaseStationButton::UserAction action);
        static EepromLocation buttonNodeEeprom(uint8 buttonNumber, BaseStationButton::UserAction action);
        static EepromLocation analogNodeAddressEeprom(uint8 portNum);
        static EepromLocation analogNodeChannelEeprom(uint8 portNum);
        static EepromLocation analogMaxFloatEeprom(uint8 portNum);
        static EepromLocation analogMinFloatEeprom(uint8 portNum);

        //=======================================================================================================================
        //Constants: Eeprom Locations
        //
        //    SERIAL_ID                  -The serial ID for the base station. Combine with the model number for the full serial number
        //    BEACON_CONFIG              -Configuration of the beacon
        //    MODEL_NUMBER               -The model number of the base station
        //    MODEL_OPTION               -The model option of the base station
        //    FREQUENCY                  -The radio frequency channel
        //    TX_POWER_LEVEL             -The transmit output power of the radio
        //    BEACON_SOURCE              -The source of the beacon
        //    FIRMWARE_VER               -The firmware version of the base station (part 1)
        //    FIRMWARE_VER2              -The firmware version of the base station (part 2)
        //    LEGACY_MODEL_NUMBER        -The (legacy) model number of the base station
        //    LEGACY_SERIAL_ID           -The (legacy) serial ID for the base station. Combine with the model number for the full serial number
        //    RADIO_ID                   -The id of the radio on the base station
        //    MICROCONTROLLER            -The id of the microcontroller
        //    FW_ARCH_VER                -The firmware architecture version
        //    ASPP_VER_LXRS              -The ASPP version of the device for the LXRS Radio Configuration
        //    ASPP_VER_LXRS_PLUS         -The ASPP version of the device for the LXRS+ Radio Configuration
        //    ANALOG_1_NODE_ADDRESS      -The Node Address to Pair to Analog Port 1
        //    ANALOG_1_NODE_CHANNEL      -The Node Channel to Pair to Analog Port 1
        //    ANALOG_1_FLOAT_MAX         -The Maximum Float value (3V output) for Analog Port 1
        //    ANALOG_1_FLOAT_MIN         -The Minimum Float value (0V output) for Analog Port 1
        //    ANALOG_2_NODE_ADDRESS      -The Node Address to Pair to Analog Port 2
        //    ANALOG_2_NODE_CHANNEL      -The Node Channel to Pair to Analog Port 2
        //    ANALOG_2_FLOAT_MAX         -The Maximum Float value (3V output) for Analog Port 2
        //    ANALOG_2_FLOAT_MIN         -The Minimum Float value (0V output) for Analog Port 2
        //    ANALOG_3_NODE_ADDRESS      -The Node Address to Pair to Analog Port 3
        //    ANALOG_3_NODE_CHANNEL      -The Node Channel to Pair to Analog Port 3
        //    ANALOG_3_FLOAT_MAX         -The Maximum Float value (3V output) for Analog Port 3
        //    ANALOG_3_FLOAT_MIN         -The Minimum Float value (0V output) for Analog Port 3
        //    ANALOG_4_NODE_ADDRESS      -The Node Address to Pair to Analog Port 4
        //    ANALOG_4_NODE_CHANNEL      -The Node Channel to Pair to Analog Port 4
        //    ANALOG_4_FLOAT_MAX         -The Maximum Float value (3V output) for Analog Port 4
        //    ANALOG_4_FLOAT_MIN         -The Minimum Float value (0V output) for Analog Port 4
        //    ANALOG_5_NODE_ADDRESS      -The Node Address to Pair to Analog Port 5
        //    ANALOG_5_NODE_CHANNEL      -The Node Channel to Pair to Analog Port 5
        //    ANALOG_5_FLOAT_MAX         -The Maximum Float value (3V output) for Analog Port 5
        //    ANALOG_5_FLOAT_MIN         -The Minimum Float value (0V output) for Analog Port 5
        //    ANALOG_6_NODE_ADDRESS      -The Node Address to Pair to Analog Port 6
        //    ANALOG_6_NODE_CHANNEL      -The Node Channel to Pair to Analog Port 6
        //    ANALOG_6_FLOAT_MAX         -The Maximum Float value (3V output) for Analog Port 6
        //    ANALOG_6_FLOAT_MIN         -The Minimum Float value (0V output) for Analog Port 6
        //    ANALOG_7_NODE_ADDRESS      -The Node Address to Pair to Analog Port 7
        //    ANALOG_7_NODE_CHANNEL      -The Node Channel to Pair to Analog Port 7
        //    ANALOG_7_FLOAT_MAX         -The Maximum Float value (3V output) for Analog Port 7
        //    ANALOG_7_FLOAT_MIN         -The Minimum Float value (0V output) for Analog Port 7
        //    ANALOG_8_NODE_ADDRESS      -The Node Address to Pair to Analog Port 8
        //    ANALOG_8_NODE_CHANNEL      -The Node Channel to Pair to Analog Port 8
        //    ANALOG_8_FLOAT_MAX         -The Maximum Float value (3V output) for Analog Port 8
        //    ANALOG_8_FLOAT_MIN         -The Minimum Float value (0V output) for Analog Port 8
        //    ANALOG_PAIRING_ENABLE      -Enable/Disable analog pairing on an analog base station
        //    ANALOG_TIMEOUT_TIME        -The time (seconds) for the analog timeout on an analog base station
        //    ANALOG_TIMEOUT_VOLTAGE     -The voltage to time out for on an analog base station
        //    BUTTON1_LONG_FUNC          -The function for a long press of Button 1 on a base station with buttons
        //    BUTTON1_LONG_NODE          -The Wireless Node associated with a long press of Button 1 on a base station with buttons
        //    BUTTON1_SHORT_FUNC         -The function for a short press of Button 1 on a base station with buttons
        //    BUTTON1_SHORT_NODE         -The Wireless Node associated with a short press of Button 1 on a base station with buttons
        //    BUTTON2_LONG_FUNC          -The function for a long press of Button 2 on a base station with buttons
        //    BUTTON2_LONG_NODE          -The Wireless Node associated with a long press of Button 2 on a base station with buttons
        //    BUTTON2_SHORT_FUNC         -The function for a short press of Button 2 on a base station with buttons
        //    BUTTON2_SHORT_NODE         -The Wireless Node associated with a short press of Button 2 on a base station with buttons
        //    LED_ACTION                 -Controls the action of the LED on the base station
        //    BAUD_RATE                  -The baud rate of the serial connection with the base station
        //    CYCLE_POWER                -Used to soft reset the base station
        //    REGION_CODE                -The region code for the device
        //    ANALOG_EXCEED_MAX          -The maximum value for the Analog Exceedance setting
        //    ANALOG_EXCEED_MIN          -The minimum value for the Analog Exceedance setting
        //    ANALOG_EXCEED_ENABLE       -Enable/Disable analog exceedance
        //    MIN_SOFT_VER_MAJOR         -The minimum software version for support of this device (major)
        //    MIN_SOFT_VER_MINOR         -The minimum software version for support of this device (minor)
        //    COMM_PROTOCOL              -The communication protocol of the device.
        //=======================================================================================================================
        static const EepromLocation SERIAL_ID;                 // The serial ID for the base station. Combine with the model number for the full serial number
        static const EepromLocation BEACON_CONFIG;             // Configuration of the beacon
        static const EepromLocation MODEL_NUMBER;              // The model number of the base station
        static const EepromLocation MODEL_OPTION;              // The model option of the base station
        static const EepromLocation FREQUENCY;                 // The radio frequency channel
        static const EepromLocation TX_POWER_LEVEL;            // The transmit output power of the radio
        static const EepromLocation BEACON_SOURCE;             // The source of the beacon
        static const EepromLocation FIRMWARE_VER;              // The firmware version of the base station (part 1)
        static const EepromLocation FIRMWARE_VER2;             // The firmware version of the base station (part 2)
        static const EepromLocation LEGACY_MODEL_NUMBER;       // The (legacy) model number of the base station
        static const EepromLocation LEGACY_SERIAL_ID;          // The (legacy) serial ID for the base station. Combine with the model number for the full serial number
        static const EepromLocation RADIO_ID;                  // The id of the radio on the base station
        static const EepromLocation MICROCONTROLLER;           // The id of the microcontroller
        static const EepromLocation FW_ARCH_VER;               // The firmware architecture version
        static const EepromLocation ASPP_VER_LXRS;             // The ASPP version of the device for the LXRS Radio Configuration
        static const EepromLocation ASPP_VER_LXRS_PLUS;        // The ASPP version of the device for the LXRS+ Radio Configuration
        static const EepromLocation ANALOG_1_NODE_ADDRESS;     // The Node Address to Pair to Analog Port 1
        static const EepromLocation ANALOG_1_NODE_CHANNEL;     // The Node Channel to Pair to Analog Port 1
        static const EepromLocation ANALOG_1_FLOAT_MAX;        // The Maximum Float value (3V output) for Analog Port 1
        static const EepromLocation ANALOG_1_FLOAT_MIN;        // The Minimum Float value (3V output) for Analog Port 1
        static const EepromLocation ANALOG_2_NODE_ADDRESS;     // The Node Address to Pair to Analog Port 2
        static const EepromLocation ANALOG_2_NODE_CHANNEL;     // The Node Channel to Pair to Analog Port 2
        static const EepromLocation ANALOG_2_FLOAT_MAX;        // The Maximum Float value (3V output) for Analog Port 2
        static const EepromLocation ANALOG_2_FLOAT_MIN;        // The Minimum Float value (3V output) for Analog Port 2
        static const EepromLocation ANALOG_3_NODE_ADDRESS;     // The Node Address to Pair to Analog Port 3
        static const EepromLocation ANALOG_3_NODE_CHANNEL;     // The Node Channel to Pair to Analog Port 3
        static const EepromLocation ANALOG_3_FLOAT_MAX;        // The Maximum Float value (3V output) for Analog Port 3
        static const EepromLocation ANALOG_3_FLOAT_MIN;        // The Minimum Float value (3V output) for Analog Port 3
        static const EepromLocation ANALOG_4_NODE_ADDRESS;     // The Node Address to Pair to Analog Port 4
        static const EepromLocation ANALOG_4_NODE_CHANNEL;     // The Node Channel to Pair to Analog Port 4
        static const EepromLocation ANALOG_4_FLOAT_MAX;        // The Maximum Float value (3V output) for Analog Port 4
        static const EepromLocation ANALOG_4_FLOAT_MIN;        // The Minimum Float value (3V output) for Analog Port 4
        static const EepromLocation ANALOG_5_NODE_ADDRESS;     // The Node Address to Pair to Analog Port 5
        static const EepromLocation ANALOG_5_NODE_CHANNEL;     // The Node Channel to Pair to Analog Port 5
        static const EepromLocation ANALOG_5_FLOAT_MAX;        // The Maximum Float value (3V output) for Analog Port 5
        static const EepromLocation ANALOG_5_FLOAT_MIN;        // The Minimum Float value (3V output) for Analog Port 5
        static const EepromLocation ANALOG_6_NODE_ADDRESS;     // The Node Address to Pair to Analog Port 6
        static const EepromLocation ANALOG_6_NODE_CHANNEL;     // The Node Channel to Pair to Analog Port 6
        static const EepromLocation ANALOG_6_FLOAT_MAX;        // The Maximum Float value (3V output) for Analog Port 6
        static const EepromLocation ANALOG_6_FLOAT_MIN;        // The Minimum Float value (3V output) for Analog Port 6
        static const EepromLocation ANALOG_7_NODE_ADDRESS;     // The Node Address to Pair to Analog Port 7
        static const EepromLocation ANALOG_7_NODE_CHANNEL;     // The Node Channel to Pair to Analog Port 7
        static const EepromLocation ANALOG_7_FLOAT_MAX;        // The Maximum Float value (3V output) for Analog Port 7
        static const EepromLocation ANALOG_7_FLOAT_MIN;        // The Minimum Float value (3V output) for Analog Port 7
        static const EepromLocation ANALOG_8_NODE_ADDRESS;     // The Node Address to Pair to Analog Port 8
        static const EepromLocation ANALOG_8_NODE_CHANNEL;     // The Node Channel to Pair to Analog Port 8
        static const EepromLocation ANALOG_8_FLOAT_MAX;        // The Maximum Float value (3V output) for Analog Port 8
        static const EepromLocation ANALOG_8_FLOAT_MIN;        // The Minimum Float value (3V output) for Analog Port 8
        static const EepromLocation ANALOG_PAIRING_ENABLE;     // Enable/Disable analog pairing on an analog base station
        static const EepromLocation ANALOG_TIMEOUT_TIME;       // The time (seconds) for the analog timeout on an analog base station
        static const EepromLocation ANALOG_TIMEOUT_VOLTAGE;    // The voltage to time out for on an analog base station
        static const EepromLocation BUTTON1_LONG_FUNC;         // The function for a long press of Button 1 on a base station with buttons
        static const EepromLocation BUTTON1_LONG_NODE;         // The Wireless Node associated with a long press of Button 1 on a base station with buttons
        static const EepromLocation BUTTON1_SHORT_FUNC;        // The function for a short press of Button 1 on a base station with buttons
        static const EepromLocation BUTTON1_SHORT_NODE;        // The Wireless Node associated with a short press of Button 1 on a base station with buttons
        static const EepromLocation BUTTON2_LONG_FUNC;         // The function for a long press of Button 2 on a base station with buttons
        static const EepromLocation BUTTON2_LONG_NODE;         // The Wireless Node associated with a long press of Button 2 on a base station with buttons
        static const EepromLocation BUTTON2_SHORT_FUNC;        // The function for a short press of Button 2 on a base station with buttons
        static const EepromLocation BUTTON2_SHORT_NODE;        // The Wireless Node associated with a short press of Button 2 on a base station with buttons
        static const EepromLocation LED_ACTION;                // Controls the action of the LED on the base station
        static const EepromLocation BAUD_RATE;                 // The baud rate of the serial connection with the base station
        static const EepromLocation CYCLE_POWER;               // Used to soft reset the base station
        static const EepromLocation REGION_CODE;               // The region code for the device.
        static const EepromLocation ANALOG_EXCEED_MAX;         // The maximum value for the Analog Exceedance setting
        static const EepromLocation ANALOG_EXCEED_MIN;         // The minimum value for the Analog Exceedance setting
        static const EepromLocation ANALOG_EXCEED_ENABLE;      // Enable/Disable analog exceedance
        static const EepromLocation MIN_SOFT_VER_MAJOR;        // The minimum software version for support of this device (major).
        static const EepromLocation MIN_SOFT_VER_MINOR;        // The minimum software version for support of this device (minor).
        static const EepromLocation COMM_PROTOCOL;             // The communication protocol of the device.
    };
}