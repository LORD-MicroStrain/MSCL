/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include <memory>
#include "EepromLocation.h"
#include "mscl/Value.h"
#include "mscl/Version.h"
#include "mscl/MicroStrain/Wireless/WirelessModels.h"
#include "mscl/MicroStrain/Wireless/WirelessTypes.h"
#include "mscl/MicroStrain/Wireless/BaseStationButton.h"
#include "mscl/MicroStrain/Wireless/BaseStationAnalogPair.h"

namespace mscl
{
    //forward declarations
    class BaseStation_Impl;

    //Class: BaseStationEepromHelper
    //    A helper class for reading and writing to a BaseStation's Eeprom.
    //    This class provides eeprom specific parsing so that high-level objects can
    //    be converted to their low-level eeprom value equivelent and vice-versa.
    class BaseStationEepromHelper
    {
    public:
        //Constructor: BaseStationEepromHelper
        //    Creates a BaseStationEepromHelper object with a <BaseStation>.
        //
        //Parameters:
        //    basestation - The <BaseStation> that will be read from and written to.
        BaseStationEepromHelper(BaseStation_Impl* basestation);

    private:
        BaseStationEepromHelper();        //disabled default constructor

        //Function: checkAnalogPairingSupported
        //    Checks that analog pairing is supported and throws an exception if it isn't.
        //
        //Exceptions:
        //    - <Error_NotSupported>: Analog Pairing is not supported.
        void checkAnalogPairingSupported() const;

    private:
        //Variable: m_baseStation
        //    The <BaseStation_Impl> used by this eeprom helper.
        BaseStation_Impl* m_baseStation;

    private:
        Value read(const EepromLocation& location) const;
        void write(const EepromLocation& location, const Value& val);

    public:
        //Function: read_asppVersion
        //  Gets the ASPP <Version> of the BaseStation.
        //
        //Parameters:
        //  commProtocol - The <WirelessTypes::CommProtocol> to get the ASPP version for.
        //
        //Exceptions:
        //  - <Error_Communication>: Failed to read the value from the BaseStation.
        //  - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        Version read_asppVersion(WirelessTypes::CommProtocol commProtocol) const;

        //Function: read_commProtocol
        //  Gets the <WirelessTypes::CommProtocol> of the BaseStation.
        //
        //Exceptions:
        //  - <Error_Communication>: Failed to read the value from the BaseStation.
        //  - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        WirelessTypes::CommProtocol read_commProtocol() const;

        //Function: write_commProtocol
        //  Changes the <WirelessTypes::CommProtocol> of the BaseStation.
        //
        //Parameters:
        //    commProtocol - The <WirelessTypes::CommProtocol> to write to the BaseStation.
        //
        //Exceptions:
        //    - <Error_Communication>: Failed to write to the BaseStation.
        //    - <Error_Connection>: A connection error has occurred with the BaseStation.
        void write_commProtocol(WirelessTypes::CommProtocol commProtocol);

        //Function: read_fwVersion
        //  Reads the firmware <Version> of the BaseStation.
        //
        //Exceptions:
        //  - <Error_Communication>: Failed to read from the BaseStation.
        //  - <Error_Connection>: A connection error has occurred with the BaseStation.
        Version read_fwVersion() const;

        uint8 read_fwVersionMajor() const;

        //Function: read_model
        //  Reads the <WirelessModels::BaseModel> of the BaseStation.
        //
        //Exceptions:
        //  - <Error_Communication>: Failed to read from the BaseStation.
        //  - <Error_Connection>: A connection error has occurred with the BaseStation.
        WirelessModels::BaseModel read_model() const;

        //Function: read_serial
        //  Reads the serial of the BaseStation.
        //
        //Exceptions:
        //  - <Error_Communication>: Failed to read from the BaseStation.
        //  - <Error_Connection>: A connection error has occurred with the BaseStation.
        std::string read_serial() const;

        //Function: read_microcontroller
        //  Reads the <WirelessTypes::MicroControllerType> of the BaseStation.
        //
        //Exceptions:
        //  - <Error_Communication>: Failed to read from the BaseStation.
        //  - <Error_Connection>: A connection error has occurred with the BaseStation.
        WirelessTypes::MicroControllerType read_microcontroller() const;

        //Function: read_transmitPower
        //    Reads the <WirelessTypes::TransmitPower> that is currently set on the BaseStation.
        //
        //Returns:
        //    The <WirelessTypes::TransmitPower> that is currently set on the BaseStation.
        //
        //Exceptions:
        //    - <Error_Communication>: Failed to read from the BaseStation.
        //    - <Error_Connection>: A connection error has occurred with the BaseStation.
        WirelessTypes::TransmitPower read_transmitPower() const;

        //Function: write_transmitPower
        //    Writes the <WirelessTypes::TransmitPower> to the BaseStation.
        //
        //Parameters:
        //    power - The <WirelessTypes::TransmitPower> to write to the BaseStation.
        //
        //Exceptions:
        //    - <Error_Communication>: Failed to write to the BaseStation.
        //    - <Error_Connection>: A connection error has occurred with the BaseStation.
        void write_transmitPower(WirelessTypes::TransmitPower power);

        //Function: read_button
        //    Reads the current settings for a particular button and action as a <BaseStationButton>.
        //
        //Prameters:
        //    buttonNumber - The button number (1 = button 1) to read for.
        //    action - The <BaseStationButton::UserAction> to read for.
        //
        //Returns:
        //    The current settings for the button, as a <BaseStationButton>
        //
        //Exceptions:
        //    - <Error_NotSupported>: Unsupported button number.
        //    - <Error_Communication>: Failed to read from the BaseStation.
        //    - <Error_Connection>: A connection error has occurred with the BaseStation.
        BaseStationButton read_button(uint8 buttonNumber, BaseStationButton::UserAction action) const;

        //Function: write_button
        //    Writes the <BaseStationButton> to the BaseStation for a particular button and action.
        //
        //Parameters:
        //    buttonNumber - The button number (1 = button 1) to write for.
        //    action - The <BaseStationButton::UserAction> to write for.
        //    button - The <BaseStationButton> to write.
        //
        //Exceptions:
        //    - <Error_NotSupported>: Unsupported button number.
        //    - <Error_Communication>: Failed to read from the BaseStation.
        //    - <Error_Connection>: A connection error has occurred with the BaseStation.
        void write_button(uint8 buttonNumber, BaseStationButton::UserAction action, const BaseStationButton& btn);

        //Function: read_analogPairingEnabled
        //    Reads the setting for if analog pairing is enabled.
        //
        //Returns:
        //    true if analog pairing is enabled, false otherwise.
        //
        //Exceptions:
        //    - <Error_NotSupported>: Analog Pairing is not supported.
        //    - <Error_Communication>: Failed to read from the BaseStation.
        //    - <Error_Connection>: A connection error has occurred with the BaseStation.
        bool read_analogPairingEnabled() const;

        //Function: write_analogPairingEnabled
        //    Writes the analog pairing enable setting to the BaseStation.
        //
        //Parameters:
        //    enable - Whether to enable analog pairing or not.
        //
        //Exceptions:
        //    - <Error_NotSupported>: Analog Pairing is not supported.
        //    - <Error_Communication>: Failed to read from the BaseStation.
        //    - <Error_Connection>: A connection error has occurred with the BaseStation.
        void write_analogPairingEnabled(bool enable);

        //Function: read_analogTimeoutTime
        //    Reads the analog timeout time in seconds.
        //
        //Returns:
        //    The time in seconds for analog timeout. If this is 0, timeout is disabled.
        //
        //Exceptions:
        //    - <Error_NotSupported>: Analog Pairing is not supported.
        //    - <Error_Communication>: Failed to read from the BaseStation.
        //    - <Error_Connection>: A connection error has occurred with the BaseStation.
        uint16 read_analogTimeoutTime() const;

        //Function: write_analogTimeoutTime
        //    Writes the analog timeout time to the BaseStation.
        //
        //Parameters:
        //    seconds - The analog timeout time in seconds. If this is 0, timeout will be disabled.
        //
        //Exceptions:
        //    - <Error_NotSupported>: Analog Pairing is not supported.
        //    - <Error_Communication>: Failed to read from the BaseStation.
        //    - <Error_Connection>: A connection error has occurred with the BaseStation.
        void write_analogTimeoutTime(uint16 seconds);

        //Function: read_analogTimeoutVoltage
        //    Reads the analog timeout voltage.
        //
        //Returns:
        //    The analog timeout voltage.
        //
        //Exceptions:
        //    - <Error_NotSupported>: Analog Pairing is not supported.
        //    - <Error_Communication>: Failed to read from the BaseStation.
        //    - <Error_Connection>: A connection error has occurred with the BaseStation.
        float read_analogTimeoutVoltage() const;

        //Function: write_analogTimeoutVoltage
        //    Writes the analog timeout voltage to the BaseStation.
        //
        //Parameters:
        //    voltage - The analog timeout voltage to write.
        //
        //Exceptions:
        //    - <Error_NotSupported>: Analog Pairing is not supported.
        //    - <Error_Communication>: Failed to read from the BaseStation.
        //    - <Error_Connection>: A connection error has occurred with the BaseStation.
        void write_analogTimeoutVoltage(float voltage);

        //Function: read_analogExceedanceEnabled
        //    Reads the setting for if analog exceedance is enabled.
        //
        //Returns:
        //    true if analog exceedance is enabled, false otherwise.
        //
        //Exceptions:
        //    - <Error_NotSupported>: Analog Pairing is not supported.
        //    - <Error_Communication>: Failed to read from the BaseStation.
        //    - <Error_Connection>: A connection error has occurred with the BaseStation.
        bool read_analogExceedanceEnabled() const;

        //Function: write_analogExceedanceEnabled
        //    Writes the analog exceedance enable setting to the BaseStation.
        //
        //Parameters:
        //    enable - Whether to enable analog exceedance or not.
        //
        //Exceptions:
        //    - <Error_NotSupported>: Analog Pairing is not supported.
        //    - <Error_Communication>: Failed to read from the BaseStation.
        //    - <Error_Connection>: A connection error has occurred with the BaseStation.
        void write_analogExceedanceEnabled(bool enable);

        //Function: read_analogPair
        //    Reads the current settings for a particular analog pairing as a <BaseStationAnalogPair>.
        //
        //Prameters:
        //    portNumber - The port number (1 = port 1) to read for.
        //
        //Returns:
        //    The current analog pairing settings for the port, as a <BaseStationAnalogPair>
        //
        //Exceptions:
        //    - <Error_NotSupported>: Unsupported port number.
        //    - <Error_Communication>: Failed to read from the BaseStation.
        //    - <Error_Connection>: A connection error has occurred with the BaseStation.
        BaseStationAnalogPair read_analogPair(uint8 portNumber) const;

        //Function: write_analogPair
        //    Writes the <BaseStationAnalogPair> to the BaseStation for a particular port number.
        //
        //Parameters:
        //    portNumber - The port number (1 = port 1) to write for.
        //    pair - The <BaseStationButton> to write.
        //
        //Exceptions:
        //    - <Error_NotSupported>: Unsupported button number.
        //    - <Error_Communication>: Failed to read from the BaseStation.
        //    - <Error_Connection>: A connection error has occurred with the BaseStation.
        void write_analogPair(uint8 portNumber, const BaseStationAnalogPair& pair);

        //Function: read_regionCode
        //    Reads the region code from the BaseStation.
        //
        //Returns:
        //    The <WirelessTypes::RegionCode> set on the BaseStation.
        //
        //Exceptions:
        //    - <Error_Communication>: Failed to read from the BaseStation.
        //    - <Error_Connection>: A connection error has occurred with the BaseStation.
        WirelessTypes::RegionCode read_regionCode() const;
    };
}