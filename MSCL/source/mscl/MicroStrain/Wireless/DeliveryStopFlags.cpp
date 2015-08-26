/*****************************************************************************
Copyright(c) 2015 LORD Corporation. All rights reserved.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the included
LICENSE.txt file for a copy of the full GNU General Public License.
*****************************************************************************/
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
		return	pc          == src.pc          &&
				appBoard    == src.appBoard    &&
			    linkBoard   == src.linkBoard   &&
			    baseStation == src.baseStation;
	}

	DeliveryStopFlags DeliveryStopFlags::fromByte(uint8 dsf)
	{
		// The dsf byte sets a bit to 0 to indicate take action and to 1 to indicate ignore.
		// So true maps to 0 and false maps to 1
		bool pcByte          = !(dsf & 0x08);  //trunc off bit 4   0x08 => 0000 1000
		bool appBoardByte    = !(dsf & 0x04);  //trunc off bit 3   0x04 => 0000 0100
		bool linkBoardByte   = !(dsf & 0x02);  //trunc off bit 2   0x02 => 0000 0010
		bool baseStationByte = !(dsf & 0x01);  //trunc off bit 1   0x01 => 0000 0001

		return DeliveryStopFlags(pcByte, appBoardByte, linkBoardByte, baseStationByte);
	}

	uint8 DeliveryStopFlags::toByte() const
	{

		// The dsp byte sets a bit to 0 to indicate take action and to 1 to indicate ignore.  
		// So true maps to 0 and false maps to 1
		uint8 dsf = 0x0F;
		if(pc)         {dsf &= 0xF7;}  //trunc off bit 4   0xF7 => 1111 0111
		if(appBoard)   {dsf &= 0xFB;}  //trunc off bit 3   0xFB => 1111 1011
		if(linkBoard)  {dsf &= 0xFD;}  //trunc off bit 2   0xFD => 1111 1101
		if(baseStation){dsf &= 0xFE;}  //trunc off bit 1   0xFE => 1111 1110

		return dsf;
	}
}