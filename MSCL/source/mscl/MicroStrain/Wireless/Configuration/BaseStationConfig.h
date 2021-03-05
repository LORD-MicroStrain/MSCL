/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/

#pragma once

#include <boost/optional.hpp>
#include <map>
#include "mscl/MicroStrain/Wireless/WirelessTypes.h"
#include "mscl/MicroStrain/Wireless/BaseStationButton.h"
#include "mscl/MicroStrain/Wireless/BaseStationAnalogPair.h"
#include "mscl/Exceptions.h"

namespace mscl
{
    //forward declarations
    class BaseStation;
    class BaseStationFeatures;
    class BaseStationEepromHelper;

    //API Class: BaseStationConfig
    //    Class used for setting the configuration of BaseStations.
    //    Set all the configuration values that you want to change, then verify and apply them to a BaseStation.
    //
    //See also:
    //    <BaseStation::applyConfig>
    class BaseStationConfig
    {
        friend class BaseStation_Impl;

    public:
        //API Constructor: BaseStationConfig
        //    Creates a blank BaseStationConfig.
        BaseStationConfig();

    private:
        typedef std::map<uint8, BaseStationButton> ButtonMap;
        typedef std::map<uint8, BaseStationAnalogPair> AnalogPairMap;

        //Variable: m_transmitPower
        //    The <WirelessTypes::TransmitPower> to set.
        boost::optional<WirelessTypes::TransmitPower> m_transmitPower;

        //Variable: m_commProtocol
        //  The <WirelessTypes::CommProtocol> to set.
        boost::optional<WirelessTypes::CommProtocol> m_commProtocol;

        //Variable: m_btnsLongPress
        //    The <ButtonMap> for long press actions.
        ButtonMap m_btnsLongPress;

        //Variable: m_btnsShortPress
        //    The <ButtonMap> for short press actions.
        ButtonMap m_btnsShortPress;

        //Variable: m_analogPairs
        //    The <AnalogPairMap> holding all analog pairs to set
        AnalogPairMap m_analogPairs;

        //Variable: m_analogPairingEnable
        //    The analog pairing enable master option to set.
        boost::optional<bool> m_analogPairingEnable;

        //Variable: m_analogTimeoutTime
        //    The analog timeout time (in seconds) to set.
        boost::optional<uint16> m_analogTimeoutTime;

        //Variable: m_analogTimeoutVoltage
        //    The analog timeout voltage to set.
        boost::optional<float> m_analogTimeoutVoltage;

        //Variable: m_analogExceedanceEnable
        //    The analog exceedance enable option to set.
        boost::optional<bool> m_analogExceedanceEnable;

    private:
        //Function: checkValue
        //    Throws an exception if an optional value isn't set.
        //
        //Parameters:
        //    opt - The boost::optional value to check if it is set.
        //    valueName - The name of the value being checked. This will be included in the exception description if not set.
        //
        //Exceptions:
        //    <Error_NoData> - The requested value has not been set.
        template<typename T>
        void checkValue(const boost::optional<T>& opt, const std::string& valueName) const
        {
            if(!isSet(opt))
            {
                throw Error_NoData("The " + valueName + " option has not been set");
            }
        }

        //Function: isSet
        //    Checks whether the optional value is set.
        //
        //Parameters:
        //    opt - The boost::optional value to check if it is set.
        //
        //Returns:
        //    true if the value is set, false if it is not set.
        template<typename T>
        bool isSet(const boost::optional<T>& opt) const
        {
            return static_cast<bool>(opt);
        }

        //Function: curTransmitPower
        //    Gets the transmit power currently set, or from the node if not set.
        WirelessTypes::TransmitPower curTransmitPower(const BaseStationEepromHelper& eeprom) const;

        //Function: curCommProtocol
        //    Gets the communication protocol currently set, or from the base if not set.
        WirelessTypes::CommProtocol curCommProtocol(const BaseStationEepromHelper& eeprom) const;

        //Function: verify
        //    Checks whether the current settings are ok to be written to a given <BaseStation>.
        //
        //Parameters:
        //    features - The <BaseStationFeatures> of the BaseStation to verify the configuration for.
        //    eeprom - The <BaseStationEepromHelper> of the BaseStation to use for communication.
        //    outIssues - The <ConfigIssues> holding any resulting issues that are found with the configuration.
        //
        //Returns:
        //    true if the configuration is valid. false if the configuration is invalid and outIssues should be checked for more information.
        //
        //Exceptions:
        //    - <Error_Communication>: Failed to communicate with the BaseStation.
        //    - <Error_Connection>: A connection error has occurred.
        bool verify(const BaseStationFeatures& features, const BaseStationEepromHelper& eeprom, ConfigIssues& outIssues) const;

        //Function: apply
        //    Writes all of the configuration values that are set to a WirelessNode. 
        //
        //Parameters:
        //    features - The <BaseStationFeatures> of the BaseStation to write the config to.
        //    eeprom - The <BaseStationEepromHelper> of the BaseStation to write the config to.
        //
        //Exceptions:
        //    - <Error_InvalidConfig>: Invalid Configuration for the BaseStation. Check the exception for specific details.
        //    - <Error_Communication>: Failed to communicate with the BaseStation.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        void apply(const BaseStationFeatures& features, BaseStationEepromHelper& eeprom) const;

    public:
        //API Function: transmitPower
        //    Gets the <WirelessTypes::TransmitPower> value in the Config, if set.
        //
        //Exceptions:
        //    <Error_NoData> - The requested value has not been set.
        WirelessTypes::TransmitPower transmitPower() const;

        //API Function: transmitPower
        //    Sets the <WirelessTypes::TransmitPower> value in the Config.
        void transmitPower(WirelessTypes::TransmitPower power);

        //API Function: communicationProtocol
        //    Gets the <WirelessTypes::CommProtocol> value in the Config, if set.
        //
        //Exceptions:
        //    <Error_NoData> - The requested value has not been set.
        WirelessTypes::CommProtocol communicationProtocol() const;

        //API Function: communicationProtocol
        //    Sets the <WirelessTypes::CommProtocol> value in the Config.
        void communicationProtocol(WirelessTypes::CommProtocol commProtocol);

        //API Function: buttonLongPress
        //    Gets the <BaseStationButton> value in the Config for performing a long press on a specific button, if set.
        //
        //Parameters:
        //    buttonNumber - The button number (1 = button 1) to get the value for.
        //
        //Exceptions:
        //    <Error_NoData> - The requested button number for long press has not been set.
        BaseStationButton buttonLongPress(uint8 buttonNumber) const;

        //API Function: buttonLongPress
        //    Sets the <BaseStationButton> value in the Config for performing a short press on a specific button.
        //
        //Parameters:
        //    buttonNumber - The button number (1 = button 1) to set.
        //    button - The <BaseStationButton> to set.
        void buttonLongPress(uint8 buttonNumber, const BaseStationButton& button);

        //API Function: buttonShortPress
        //    Gets the <BaseStationButton> value in the Config for performing a short press on a specific button, if set.
        //
        //Parameters:
        //    buttonNumber - The button number (1 = button 1) to get the value for.
        //
        //Exceptions:
        //    <Error_NoData> - The requested button number for short press has not been set.
        BaseStationButton buttonShortPress(uint8 buttonNumber) const;

        //API Function: buttonShortPress
        //    Sets the <BaseStationButton> value in the Config for performing a long press on a specific button.
        //
        //Parameters:
        //    buttonNumber - The button number (1 = button 1) to set.
        //    button - The <BaseStationButton> to set.
        void buttonShortPress(uint8 buttonNumber, const BaseStationButton& button);

        //API Function: analogPairingEnable
        //    Gets the Analog Pairing Enabled value in the Config, if set.
        //
        //Exceptions:
        //    <Error_NoData> - The requested button number for short press has not been set.
        bool analogPairingEnable() const;

        //API Function: analogPairingEnable
        //    Sets the Analog Pairing Enabled value in the Config. 
        //    This controls whether all of the other analog pairing settings have any affect.
        //
        //Parameters:
        //    enable - Whether to enable or disable analog pairing in the Config.
        void analogPairingEnable(bool enable);

        //API Function: analogTimeoutTime
        //    Gets the Analog Timeout Time value (in seconds) in the Config, if set.
        //    If this is 0, Analog Timeout is disabled.
        //
        //Exceptions:
        //    <Error_NoData> - The requested button number for short press has not been set.
        uint16 analogTimeoutTime() const;

        //API Function: analogTimeoutTime
        //    Sets the Analog Timeout Time value (in seconds) in the Config. 
        //    If this is 0, Analog Timeout is disabled.
        //
        //Parameters:
        //    seconds - The analog timeout time in seconds to set.
        void analogTimeoutTime(uint16 seconds);

        //API Function: analogTimeoutVoltage
        //    Gets the Analog Timeout Voltage in the Config, if set.
        //
        //Exceptions:
        //    <Error_NoData> - The requested button number for short press has not been set.
        float analogTimeoutVoltage() const;

        //API Function: analogTimeoutVoltage
        //    Sets the Analog Timeout Voltage in the Config. 
        //    If this is 0, Analog Timeout is disabled.
        //
        //Parameters:
        //    voltage - The voltage to set.
        void analogTimeoutVoltage(float voltage);

        //API Function: analogExceedanceEnable
        //    Gets the Analog Exceedance Enabled value in the Config, if set.
        //
        //Exceptions:
        //    <Error_NoData> - The requested button number for short press has not been set.
        bool analogExceedanceEnable();

        //API Function: analogExceedanceEnable
        //    Sets the Analog Exceedance Enabled value in the Config. 
        //
        //Parameters:
        //    enable - Whether to enable or disable analog exceedance in the Config.
        void analogExceedanceEnable(bool enable);

        //API Function: analogPairing
        //    Gets the <BaseStationAnalogPair> value in the Config for the specified port number, if set.
        //
        //Parameters:
        //    portNumber - The port number (1 = port 1) to get the pairing for.
        //
        //Exceptions:
        //    <Error_NoData> - The requested port number has not been set.
        BaseStationAnalogPair analogPairing(uint8 portNumber) const;

        //API Function: buttonLongPress
        //    Sets the <BaseStationAnalogPair> value in the Config for the specified port number.
        //
        //Parameters:
        //    portNumber - The port number (1 = port 1) to set.
        //    pair - The <BaseStationAnalogPair> to set.
        void analogPairing(uint8 portNumber, const BaseStationAnalogPair& pair);
    };
}
