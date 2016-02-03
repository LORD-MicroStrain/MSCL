/*******************************************************************************
Copyright(c) 2015-2016 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"

#include "BaseStationConfig.h"
#include "mscl/MicroStrain/Wireless/BaseStation.h"
#include "mscl/MicroStrain/Wireless/Features/BaseStationFeatures.h"
#include "BaseStationEepromHelper.h"

namespace mscl
{
    BaseStationConfig::BaseStationConfig()
    {
    }

    bool BaseStationConfig::verify(const BaseStationFeatures& features, const BaseStationEepromHelper& eeprom, ConfigIssues& outIssues) const
    {
        //clear out the config issues container
        outIssues.clear();

        //if any of the buttons are set
        if(!m_btnsLongPress.empty() || !m_btnsShortPress.empty())
        {
            //verify the base station supports buttons
            if(!features.supportsButtons())
            {
                outIssues.push_back(ConfigIssue(ConfigIssue::CONFIG_BUTTON, "Buttons are not supported by this BaseStation."));
            }
            else
            {
                uint8 btnCount = features.buttonCount();

                //verify each button number (long press) is supported
                for(auto& btn : m_btnsLongPress)
                {
                    //check the button number is supported and not 0
                    if(btnCount < btn.first || btn.first == 0)
                    {
                        outIssues.push_back(ConfigIssue(ConfigIssue::CONFIG_BUTTON, "Button " + Utils::toStr(btn.first) + " is not supported by this BaseStation."));
                    }
                }

                //verify each button number (short press) is supported
                for(auto& btn : m_btnsShortPress)
                {
                    //check the button number is supported and not 0
                    if(btnCount < btn.first || btn.first == 0)
                    {
                        outIssues.push_back(ConfigIssue(ConfigIssue::CONFIG_BUTTON, "Button " + Utils::toStr(btn.first) + " is not supported by this BaseStation."));
                    }
                }
            }
        }

        //if analog pairing isn't supported
        if(!features.supportsAnalogPairing())
        {
            //if any analog pairing options are set
            if(isSet(m_analogPairingEnable) ||
               isSet(m_analogTimeoutTime) ||
               isSet(m_analogTimeoutVoltage) ||
               isSet(m_analogExceedanceEnable) ||
               !m_analogPairs.empty())
            {
                outIssues.push_back(ConfigIssue(ConfigIssue::CONFIG_ANALOG_PAIR, "Analog Pairing is not supported by this BaseStation."));
            }
        }
        else
        {
            //if any analog pairs are set
            if(!m_analogPairs.empty())
            {
                uint8 portCount = features.analogPortCount();

                //verify each port number is supported
                for(auto& pair : m_analogPairs)
                {
                    //check the port number is supported and not 0
                    if(portCount < pair.first || pair.first == 0)
                    {
                        outIssues.push_back(ConfigIssue(ConfigIssue::CONFIG_ANALOG_PAIR, "Analog Port " + Utils::toStr(pair.first) + " is not supported by this BaseStation."));
                    }
                }
            }
        }

        //Transmit Power
        if(isSet(m_transmitPower))
        {
            //verify the transmit power is supported
            if(!features.supportsTransmitPower(*m_transmitPower))
            {
                outIssues.push_back(ConfigIssue(ConfigIssue::CONFIG_TRANSMIT_POWER, "The Transmit Power is not supported by this BaseStation."));
            }
        }

        //return true if no issues
        return outIssues.size() == 0;
    }

    void BaseStationConfig::apply(const BaseStationFeatures& features, BaseStationEepromHelper& eeprom) const
    {
        //verify the config can be applied to the basestation
        ConfigIssues issues;
        if(!verify(features, eeprom, issues))
        {
            //invalid configuration, throw an exception
            throw Error_InvalidConfig(issues);
        }

        //write transmit power
        if(isSet(m_transmitPower)) { eeprom.write_transmitPower(*m_transmitPower); }

        //write all of the long press buttons that are set
        for(auto& btn : m_btnsLongPress)
        {
            eeprom.write_button(btn.first, BaseStationButton::action_longPress, btn.second);
        }

        //write all of the short press buttons that are set
        for(auto& btn : m_btnsShortPress)
        {
            eeprom.write_button(btn.first, BaseStationButton::action_shortPress, btn.second);
        }

        //write analog pairing enable
        if(isSet(m_analogPairingEnable)) { eeprom.write_analogPairingEnabled(*m_analogPairingEnable); }

        //write analog timeout time
        if(isSet(m_analogTimeoutTime)) { eeprom.write_analogTimeoutTime(*m_analogTimeoutTime); }

        //write analog timeout voltage
        if(isSet(m_analogTimeoutVoltage)) { eeprom.write_analogTimeoutVoltage(*m_analogTimeoutVoltage); }

        //write analog exceedance enable
        if(isSet(m_analogExceedanceEnable)) { eeprom.write_analogExceedanceEnabled(*m_analogExceedanceEnable); }

        //write all the analog pairs that are set
        for(auto& pair : m_analogPairs)
        {
            eeprom.write_analogPair(pair.first, pair.second);
        }
    }

    WirelessTypes::TransmitPower BaseStationConfig::transmitPower() const
    {
        checkValue(m_transmitPower, "Transmit Power");
        return *m_transmitPower;
    }

    void BaseStationConfig::transmitPower(WirelessTypes::TransmitPower power)
    {
        m_transmitPower = power;
    }

    BaseStationButton BaseStationConfig::buttonLongPress(uint8 buttonNumber) const
    {
        //attempt to find the button in the existing map
        ButtonMap::const_iterator btn = m_btnsLongPress.find(buttonNumber);
        if(btn == m_btnsLongPress.end())
        {
            throw Error_NoData("The BaseStation Button has not been set for long press.");
        }

        //we found it, so return the button
        return btn->second;
    }

    void BaseStationConfig::buttonLongPress(uint8 buttonNumber, const BaseStationButton& button)
    {
        m_btnsLongPress[buttonNumber] = button;
    }

    BaseStationButton BaseStationConfig::buttonShortPress(uint8 buttonNumber) const
    {
        //attempt to find the button in the existing map
        ButtonMap::const_iterator btn = m_btnsShortPress.find(buttonNumber);
        if(btn == m_btnsShortPress.end())
        {
            throw Error_NoData("The BaseStation Button has not been set for short press.");
        }

        //we found it, so return the button
        return btn->second;
    }

    void BaseStationConfig::buttonShortPress(uint8 buttonNumber, const BaseStationButton& button)
    {
        m_btnsShortPress[buttonNumber] = button;
    }

    bool BaseStationConfig::analogPairingEnable() const
    {
        checkValue(m_analogPairingEnable, "Analog Pairing Enabled");
        return *m_analogPairingEnable;
    }

    void BaseStationConfig::analogPairingEnable(bool enable)
    {
        m_analogPairingEnable = enable;
    }

    uint16 BaseStationConfig::analogTimeoutTime() const
    {
        checkValue(m_analogTimeoutTime, "Analog Timeout Time");
        return *m_analogTimeoutTime;
    }

    void BaseStationConfig::analogTimeoutTime(uint16 seconds)
    {
        m_analogTimeoutTime = seconds;
    }

    float BaseStationConfig::analogTimeoutVoltage() const
    {
        checkValue(m_analogTimeoutVoltage, "Analog Timeout Voltage");
        return *m_analogTimeoutVoltage;
    }

    void BaseStationConfig::analogTimeoutVoltage(float voltage)
    {
        m_analogTimeoutVoltage = voltage;
    }

    bool BaseStationConfig::analogExceedanceEnable()
    {
        checkValue(m_analogExceedanceEnable, "Analog Exceedance Enabled");
        return *m_analogExceedanceEnable;
    }

    void BaseStationConfig::analogExceedanceEnable(bool enable)
    {
        m_analogExceedanceEnable = enable;
    }

    BaseStationAnalogPair BaseStationConfig::analogPairing(uint8 portNumber) const
    {
        //attempt to find the analog pair in the existing map
        AnalogPairMap::const_iterator pair = m_analogPairs.find(portNumber);
        if(pair == m_analogPairs.end())
        {
            throw Error_NoData("Analog pairing has not been set for port " + Utils::toStr(static_cast<uint16>(portNumber)) + ".");
        }

        //we found it, so return the analog pair
        return pair->second;
    }

    void BaseStationConfig::analogPairing(uint8 portNumber, const BaseStationAnalogPair& pair)
    {
        m_analogPairs[portNumber] = pair;
    }
}