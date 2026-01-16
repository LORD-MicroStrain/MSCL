/*****************************************************************************************
**          Copyright(c) 2015-2026 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#pragma once

namespace mscl
{
    //API Class: RadioFeatures
    //    Represents radio features of a <WirelessNode>.
    class RadioFeatures
    {
        //Variable: m_extendedRange
        //    Whether the radio is XR capable
        bool m_extendedRange;

    public:
        //API Default Constructor: RadioFeatures
        //    Creates a default RadioFeatures object
        RadioFeatures();

        //API Constructor: RadioFeatures
        //    Creates a RadioFeatures object from the eeprom value
        //
        //Parameters:
        //    eepromValue - The value from eeprom that determines the radio features
        RadioFeatures(uint16 eepromValue);

        //API Function: extendedRange
        //    Gets whether the Node is XR (has an extended range radio)
        //
        //Returns:
        //    true if the Node has an XR radio, false otherwise
        bool extendedRange();

    private:
        //Function: init
        //    Sets all the radio features from the given eeprom value
        //
        //Parameters:
        //    eepromValue - The value from eeprom that determines the radio features
        void init(uint16 eepromValue);
    };
} // namespace mscl
