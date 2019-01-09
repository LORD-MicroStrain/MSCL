/*******************************************************************************
Copyright(c) 2015-2019 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"
#include "MockNodeEeprom.h"
#include "mscl/MicroStrain/Wireless/WirelessNode_Impl.h"

namespace mscl
{
    MockNodeEeprom::MockNodeEeprom(const WirelessNode_Impl* node, const BaseStation& base, const NodeEepromSettings& settings):
        NodeEeprom(node, base, settings)
    { }

    uint16 MockNodeEeprom::readEeprom(uint16 location)
    {
        uint16 result;

        //attempt to read the value from the cache
        if(readCache(location, result))
        {
            //the value was found in the cache, just return the result
            return result;
        }

        //we failed to read the eeprom value from the cache or the device
        throw Error_NodeCommunication(m_node->nodeAddress(), "EEPROM " + Utils::toStr(location) + " is not in the Mock Node's cache.");
    }

    void MockNodeEeprom::writeEeprom(uint16 location, uint16 value)
    {
        updateCache(location, value);
    }
}