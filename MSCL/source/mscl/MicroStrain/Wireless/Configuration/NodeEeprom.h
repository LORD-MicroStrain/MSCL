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
#pragma once

#include "Eeprom.h"
#include "mscl/MicroStrain/Wireless/BaseStation.h"
#include "mscl/MicroStrain/Wireless/Commands/WirelessProtocol.h"

namespace mscl
{
	class ByteStream;

	//Class: NodeEeprom
	//	Used to read and write to Wireless Nodes' eeproms and provide caching functionality.
	class NodeEeprom : public Eeprom
	{
	private:
		static const uint16 PAGE_0_MAX_EEPROM = 262;	//the max eeprom location that is in page 0 (from the node page download command)
		static const uint16 PAGE_1_MAX_EEPROM = 526;	//the max eeprom location that is in page 1 (from the node page download command)
		static const uint16 EEPROMS_PER_PAGE = 264;		//the number of eeprom locations per page (from the node page download command)

	public:
		//Constructor: Eeprom
		//	Creates an Eeprom object.
		//
		//Parameters:
		//	nodeAddress - The address of the Node to access the Eeprom of.
		//	base - The <BaseStation> to use for communicating with the Node.
		//	protocol - The <WirelessProtocol> that is supported by the Node.
		//	useCache - Whether or not to use the eeprom cache.
		NodeEeprom(NodeAddress nodeAddress, const BaseStation& base, const WirelessProtocol& protocol, bool useCache = true);

		virtual ~NodeEeprom() {};

	private:
		//Variable: m_nodeAddress
		//	The address of the <WirelessNode> to access the eeprom of.
		NodeAddress m_nodeAddress;

		//Variable: m_baseStation
		//	The <BaseStation> to use for communication with the Node.
		BaseStation m_baseStation;

		//Variable: m_protocol
		//	The <WirelessProtocol> that is supported by the Node.
		const WirelessProtocol* m_protocol;

	protected:
		//Function: updateCacheFromDevice
		//	Attempts to update the cache by reading the value from the Node with the nodeAddress given at initialization.
		//	Any values that are read from the Node will be updated in the cache.
		//
		//Parameters:
		//	location - The eeprom location to read from the device and update in the cache.
		//	canUseGroupDownload - Whether or not the devices can download a group of eeproms when available. If this is false, a single eeprom read will be used.
		//
		//Returns:
		//	true if the value was read from the device and the cache has been updated, false otherwise.
		virtual bool updateCacheFromDevice(uint16 location, bool canUseGroupDownload = true) final;

	private:
		//Function: parseEepromPage
		//	Parses a page download result containing eeprom values. 
		//	The eeprom cache will be updated with all the parsed values.
		//
		//Parameters:
		//	pageData - The <ByteStream> that contains the data read from the page download command
		//	pageIndex - The 0-based index that was used to download the page
		virtual void parseEepromPage(const ByteStream& pageData, uint16 pageIndex);

	public:
		using Eeprom::readEeprom;
		using Eeprom::writeEeprom;

		//Function: setBaseStation
		//	Updates the BaseStation object that is set for use in communicating with the Node.
		void setBaseStation(const BaseStation& base);

		//Function: readEeprom
		//	Attempts to read an eeprom value from the Node.
		//	If caching is enabled and there is a previously cached value available, this will 
		//	just return the value from the cache and will not communicate with the Node.
		//
		//Parameters:
		//	location - The eeprom location to read from the Node and update in the cache.
		//
		//Returns:
		//	The eeprom value for the requested location.
		//
		//Exceptions:
		//	- <Error_NodeCommunication>: Failed to read the value from the Node.
		//	- <Error_Connection>: A connection error has occurred with the BaseStation.
		virtual uint16 readEeprom(uint16 location) override;

		//Function: writeEeprom
		//	Attempts to write an eeprom value to the Node.
		//	If successful, the cache will be updated with the changed value as well.
		//	If caching is enabled and the value in the cache is the same as that attempting to be written,
		//	nothing will be written to the Node and this function will have no affect.
		//
		//Parameters:
		//	location - The eeprom location to write to on the Node and update in the cache.
		//	value - The value to write to the eeprom on the Node and update in the cache.
		//
		//Exceptions:
		//	- <Error_NodeCommunication>: Failed to write the value to the Node.
		//	- <Error_Connection>: A connection error has occurred with the BaseStation.
		virtual void writeEeprom(uint16 location, uint16 value) override;
	};
}