/*****************************************************************************************
**          Copyright(c) 2015-2024 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "stdafx.h"

#include "DeliveryStopFlags.h"

namespace mscl
{
    DeliveryStopFlags::DeliveryStopFlags() :
        pc(false),
        appBoard(false),
        linkBoard(false),
        baseStation(false)
    {
    }

    DeliveryStopFlags::DeliveryStopFlags(bool pc, bool appBoard, bool linkBoard, bool baseStation) :
        pc(pc),
        appBoard(appBoard),
        linkBoard(linkBoard),
        baseStation(baseStation)
    {
    }

    bool DeliveryStopFlags::operator==(const DeliveryStopFlags& src) const
    {
        return compare(src);
    }

    bool DeliveryStopFlags::operator!=(const DeliveryStopFlags& src) const
    {
        return !compare(src);
    }

    bool DeliveryStopFlags::compare(const DeliveryStopFlags& src) const
    {
        return  pc          == src.pc          &&
                appBoard    == src.appBoard    &&
                linkBoard   == src.linkBoard   &&
                baseStation == src.baseStation;
    }

    DeliveryStopFlags DeliveryStopFlags::fromInvertedByte(uint8 dsf)
    {
        // The inverted dsf byte sets a bit to 0 to indicate take action and to 1 to indicate ignore.
        // So true maps to 0 and false maps to 1
        bool pcByte             = !(dsf & 0x08);  //trunc off bit 4   0x08 => 0000 1000
        bool appBoardByte       = !(dsf & 0x04);  //trunc off bit 3   0x04 => 0000 0100
        bool linkBoardByte      = !(dsf & 0x02);  //trunc off bit 2   0x02 => 0000 0010
        bool baseStationByte    = !(dsf & 0x01);  //trunc off bit 1   0x01 => 0000 0001

        return DeliveryStopFlags(pcByte, appBoardByte, linkBoardByte, baseStationByte);
    }

    DeliveryStopFlags DeliveryStopFlags::fromByte(uint8 dsf)
    {
        // The dsf byte sets a bit to 1 to indicate take action and 0 to indicate ignore.
        bool pcByte          = (dsf & 0x08) != 0;  //trunc off bit 4   0x08 => 0000 1000
        bool appBoardByte    = (dsf & 0x04) != 0;  //trunc off bit 3   0x04 => 0000 0100
        bool linkBoardByte   = (dsf & 0x02) != 0;  //trunc off bit 2   0x02 => 0000 0010
        bool baseStationByte = (dsf & 0x01) != 0;  //trunc off bit 1   0x01 => 0000 0001

        return DeliveryStopFlags(pcByte, appBoardByte, linkBoardByte, baseStationByte);
    }

    uint8 DeliveryStopFlags::toInvertedByte() const
    {
        // The inverted dsf byte sets a bit to 0 to indicate take action and to 1 to indicate ignore.
        // So true maps to 0 and false maps to 1
        uint8 dsf = 0x0F;   //upper nibble mapped to all 0's by mistake in protocol
        if(pc)          { dsf &= 0xF7; }  //trunc off bit 4   0xF7 => 1111 0111
        if(appBoard)    { dsf &= 0xFB; }  //trunc off bit 3   0xFB => 1111 1011
        if(linkBoard)   { dsf &= 0xFD; }  //trunc off bit 2   0xFD => 1111 1101
        if(baseStation) { dsf &= 0xFE; }  //trunc off bit 1   0xFE => 1111 1110

        return dsf;
    }

    uint8 DeliveryStopFlags::toByte() const
    {
        // The dsf byte sets a bit to 1 to indicate take action and 0 to indicate ignore.
        uint8 dsf = 0x00;
        if(pc)          { dsf |= 0x08; }  //trunc off bit 4   0x08 => 0000 1000
        if(appBoard)    { dsf |= 0x04; }  //trunc off bit 3   0x04 => 0000 0100
        if(linkBoard)   { dsf |= 0x02; }  //trunc off bit 2   0x02 => 0000 0010
        if(baseStation) { dsf |= 0x01; }  //trunc off bit 1   0x01 => 0000 0001

        return dsf;
    }
}
