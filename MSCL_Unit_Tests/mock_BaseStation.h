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

#include <memory>
#include "mscl/MicroStrain/Wireless/BaseStation_Impl.h"
#include "mscl/MicroStrain/Wireless/BaseStationInfo.h"
#include "mscl/MicroStrain/Wireless/Features/BaseStationFeatures.h"
#include "mscl/Timestamp.h"

#include <turtle/mock.hpp>
#include "mock_Connection.h"
using namespace mscl;

//declare a 'mock_baseStation class implementing the 'mockBaseStation' class
MOCK_BASE_CLASS(mock_baseStationImpl, BaseStation_Impl)
{	
	mock_baseStationImpl():
		BaseStation_Impl(makeConnectionWithMockImpl(), 10)
	{
	}

	mock_baseStationImpl(mscl::Connection c):
		BaseStation_Impl(c, 10)
	{
	}

	MOCK_METHOD(ping, 0);
	MOCK_METHOD_EXT(readEeprom, 1, Value(const EepromLocation&), readEeprom);
	MOCK_METHOD_EXT(writeEeprom, 2, void(const EepromLocation&, const Value&), writeEeprom);
	MOCK_METHOD_EXT(readEeprom, 1, uint16(uint16), readEeprom_uint16);
	MOCK_METHOD_EXT(writeEeprom, 2, void(uint16, uint16), writeEeprom_uint16);
	MOCK_METHOD_EXT(enableBeacon, 0, mscl::Timestamp(), enableBeacon_pctime);
	MOCK_METHOD_EXT(enableBeacon, 1, mscl::Timestamp(uint32), enableBeacon_withTime);
	MOCK_METHOD(disableBeacon, 0);
	MOCK_METHOD(features, 0);

	MOCK_METHOD(node_ping, 1);
	MOCK_METHOD(node_pageDownload, 3);
	MOCK_METHOD(node_readEeprom, 4);
	MOCK_METHOD(node_writeEeprom, 4);
	MOCK_METHOD(node_startSyncSampling, 1);
	MOCK_METHOD(node_armForDatalogging, 2);
	MOCK_METHOD(node_triggerArmedDatalogging, 1);
	MOCK_METHOD(node_erase, 1);
	MOCK_METHOD(node_setToIdle, 2);
};

static void expectRead(std::shared_ptr<mock_baseStationImpl> impl, const EepromLocation& loc, const Value& returnVal)
{
	MOCK_EXPECT(impl->readEeprom).with(loc).returns(returnVal);
}

static void expectWrite(std::shared_ptr<mock_baseStationImpl> impl, const EepromLocation& loc, const Value& val)
{
	MOCK_EXPECT(impl->writeEeprom).with(loc, val);
}


static BaseStation makeBaseStationWithMockImpl()
{
	static std::shared_ptr<BaseStation_Impl> impl(new mock_baseStationImpl());
	return BaseStation(impl);
}

static void expectBaseFeatures(std::unique_ptr<BaseStationFeatures>& features, std::shared_ptr<mock_baseStationImpl> impl, WirelessModels::BaseModel model = WirelessModels::base_wsdaBase_104_usb)
{
	BaseStationInfo info(Version(9, 9), model, WirelessTypes::region_usa);

	features = BaseStationFeatures::create(info);

	MOCK_EXPECT(impl->features).returns(std::ref(*(features.get())));
}