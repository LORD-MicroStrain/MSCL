/*****************************************************************************************
**          Copyright(c) 2015-2026 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#pragma once

#include "mscl/MicroStrain/Wireless/Configuration/NodeEeprom.h"

namespace mscl
{
    //Class: MockNodeEeprom
    //    Used as a Mock object for reading and writing to Wireless Nodes' eeproms, which just uses the cache for this Mock object.
    class MockNodeEeprom: public NodeEeprom
    {
    public:
        //Constructor: Eeprom
        //    Creates an Eeprom object.
        //
        //Parameters:
        //    nodeAddress - The address of the Node to access the Eeprom of.
        //    base - The <BaseStation> to use for communicating with the Node.
        //    settings - The <NodeEepromSettings> to use.
        MockNodeEeprom(const WirelessNode_Impl* node, const BaseStation& base, const NodeEepromSettings& settings);

        ~MockNodeEeprom() override {}

        uint16 readEeprom(uint16 location) override;

        void writeEeprom(uint16 location, uint16 value) override;
    };
} // namespace mscl
