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
#include "mscl/MicroStrain/Wireless/BaseStation.h"
#include "mscl/Communication/Connection.h"
#include "mscl/Communication/SerialConnection.h"
#include "mscl/Utils.h"
#include "mscl/Exceptions.h"
#include "mscl/TimeSpan.h"
#include "mscl/MicroStrain/ByteStream.h"
#include "mscl/MicroStrain/Wireless/Configuration/BaseStationEepromMap.h"
#include "mscl/MicroStrain/Wireless/WirelessTypes.h"
#include "mscl/MicroStrain/Wireless/Commands/AutoCal.h"
#include <vector>



#include "customErrorPolicyLogging.h"

#define BOOST_TEST_MODULE MSCL_Unit_Test



#include <boost/test/unit_test.hpp>
#include <turtle/mock.hpp>

using namespace mscl;

#include "mock_Connection.h"
#include "mock_BaseStation.h"


namespace mock
{
	//Override the output of Bytes so it doesn't print a 'soh' character and break xml
	inline stream& operator<<( stream& s, const ByteStream& v )
	{
		return s << "ByteStream";
	}
}


BOOST_AUTO_TEST_SUITE(BaseStation_Test)


BOOST_AUTO_TEST_CASE(BaseStation_frequency)
{
	std::shared_ptr<mockConnectionImpl> connImpl(new mockConnectionImpl);
	Connection conn(connImpl);

	//build the response bytes that need to be read on creation of a BaseStation
	std::vector<ByteStream> responses;
	responses.push_back(loadBaseInfoResponse());
	connImpl->setResponseBytes(responses);

	//create a base station
	BaseStation base(conn);

	//check the frequency is what we expect
	BOOST_CHECK_EQUAL(base.frequency(), 13);
}

BOOST_AUTO_TEST_CASE(BaseStation_firmwareVersion)
{
	std::shared_ptr<mock_baseStationImpl> baseImpl(new mock_baseStationImpl());
	BaseStation b(baseImpl);

	expectRead(baseImpl, BaseStationEepromMap::FIRMWARE_VER, Value::UINT16(0x050D));

	//check that the response is successful
	BOOST_CHECK_EQUAL(b.firmwareVersion().str(), "5.13.0");
}

BOOST_AUTO_TEST_CASE(BaseStation_firmwareVersion_withSvn)
{
	std::shared_ptr<mock_baseStationImpl> baseImpl(new mock_baseStationImpl());
	BaseStation b(baseImpl);

	expectRead(baseImpl, BaseStationEepromMap::FIRMWARE_VER, Value::UINT16(0x0A00));
	expectRead(baseImpl, BaseStationEepromMap::FIRMWARE_VER2, Value::UINT16(0x6F33));

	//check that the response is successful
	BOOST_CHECK_EQUAL(b.firmwareVersion().str(), "10.28467.0");
}

BOOST_AUTO_TEST_CASE(BaseStation_firmwareVersion_withSvn_larger)
{
	std::shared_ptr<mock_baseStationImpl> baseImpl(new mock_baseStationImpl());
	BaseStation b(baseImpl);

	expectRead(baseImpl, BaseStationEepromMap::FIRMWARE_VER, Value::UINT16(0x0A02));
	expectRead(baseImpl, BaseStationEepromMap::FIRMWARE_VER2, Value::UINT16(0x6F33));

	//check that the response is successful
	BOOST_CHECK_EQUAL(b.firmwareVersion().str(), "10.159539.0");
}

BOOST_AUTO_TEST_CASE(BaseStation_model)
{
	std::shared_ptr<mock_baseStationImpl> baseImpl(new mock_baseStationImpl());
	BaseStation b(baseImpl);

	expectRead(baseImpl, BaseStationEepromMap::FIRMWARE_VER, Value::UINT16(0x050D));
	expectRead(baseImpl, BaseStationEepromMap::MODEL_NUMBER, Value::UINT16(6307));
	expectRead(baseImpl, BaseStationEepromMap::MODEL_OPTION, Value::UINT16(1010));

	//check that the response is successful
	BOOST_CHECK_EQUAL(b.model(), WirelessModels::base_wsdaBase_101_analog);
}

BOOST_AUTO_TEST_CASE(BaseStation_model_legacy)
{
	std::shared_ptr<mock_baseStationImpl> baseImpl(new mock_baseStationImpl());
	BaseStation b(baseImpl);

	expectRead(baseImpl, BaseStationEepromMap::FIRMWARE_VER, Value::UINT16(0x050D));
	expectRead(baseImpl, BaseStationEepromMap::MODEL_NUMBER, Value::UINT16(0xAAAA));//uninitialized
	expectRead(baseImpl, BaseStationEepromMap::LEGACY_MODEL_NUMBER, Value::UINT16(1040));

	//check that the response is successful
	BOOST_CHECK_EQUAL(b.model(), WirelessModels::base_wsdaBase_104_usb);
}

BOOST_AUTO_TEST_CASE(BaseStation_serial)
{
	std::shared_ptr<mock_baseStationImpl> baseImpl(new mock_baseStationImpl());
	BaseStation b(baseImpl);

	expectRead(baseImpl, BaseStationEepromMap::FIRMWARE_VER, Value::UINT16(0x050D));
	expectRead(baseImpl, BaseStationEepromMap::SERIAL_ID, Value(valueType_uint32, static_cast<uint32>(7546)));
	expectRead(baseImpl, BaseStationEepromMap::MODEL_NUMBER, Value::UINT16(6307));
	expectRead(baseImpl, BaseStationEepromMap::MODEL_OPTION, Value::UINT16(1010));

	//check that the response is successful
	BOOST_CHECK_EQUAL(b.serial(), "6307-1010-07546");
}

BOOST_AUTO_TEST_CASE(BaseStation_GetNextData_NoData)
{
	std::shared_ptr<mockConnectionImpl> connImpl(new mockConnectionImpl);
	Connection conn(connImpl);

	//create the base station (loads the info)
	BaseStation base(conn);

	//check that calling getNextData throws an Error_NoData exception
	BOOST_CHECK_THROW(base.getNextData(), Error_NoData);
}

BOOST_AUTO_TEST_CASE(BaseStation_GetNextData_Success)
{
	std::shared_ptr<mockConnectionImpl> connImpl(new mockConnectionImpl);
	Connection conn(connImpl);

	//create the base station (loads the info)
	BaseStation base(conn);

	//build a LDC data packet to send
	ByteStream data;
	data.append_uint8(0xAA);
	data.append_uint8(0x07);
	data.append_uint8(0x04);
	data.append_uint16(456);	//node address
	data.append_uint8(8);		//payload length
	data.append_uint8(0x02);
	data.append_uint8(0x01);
	data.append_uint8(0x70);
	data.append_uint8(0x03);	//data type
	data.append_uint16(45);
	data.append_uint16(165);	//channel data
	data.append_uint16(0x00);
	data.append_uint16(data.calculateSimpleChecksum(1, 13));	//checksum
	connImpl->setResponseBytes(data);

	//force parsing of the bytes we just set
	connImpl->parseNextResponse();

	DataSweep sweep = base.getNextData(1000);

	//check that the packet came across and looks right
	BOOST_CHECK_EQUAL(sweep.tick(), 45);
	BOOST_CHECK_EQUAL(sweep.nodeAddress(), 456);
	BOOST_CHECK_EQUAL(sweep.frequency(), WirelessTypes::freq_unknown);
}

BOOST_AUTO_TEST_CASE(BaseStation_GetData_NoData)
{
	std::shared_ptr<mockConnectionImpl> connImpl(new mockConnectionImpl);
	Connection conn(connImpl);

	//create the base station (loads the info)
	BaseStation base(conn);

	//check that there is no data to get
	BOOST_CHECK_EQUAL(base.totalData(), 0);
	BOOST_CHECK_EQUAL(base.getData().size(), 0);
}

BOOST_AUTO_TEST_CASE(BaseStation_GetData_Success)
{
	std::shared_ptr<mockConnectionImpl> connImpl(new mockConnectionImpl);
	Connection conn(connImpl);

	//create the base station (loads the info)
	BaseStation base(conn);

	//build a LDC data packet to send
	ByteStream data;
	data.append_uint8(0xAA);
	data.append_uint8(0x07);
	data.append_uint8(0x04);
	data.append_uint16(456);	//node address
	data.append_uint8(8);		//payload length
	data.append_uint8(0x02);
	data.append_uint8(0x01);
	data.append_uint8(0x70);
	data.append_uint8(0x03);	//data type
	data.append_uint16(45);
	data.append_uint16(165);	//channel data
	data.append_uint16(0x00);
	data.append_uint16(data.calculateSimpleChecksum(1, 13));	//checksum
	connImpl->setResponseBytes(data);

	//force parsing of the bytes we just set
	connImpl->parseNextResponse();

	DataSweeps sweeps = base.getData();

	//check that the packet came across and looks right
	BOOST_CHECK_EQUAL(sweeps.size(), 1);
	BOOST_CHECK_EQUAL(sweeps.at(0).nodeAddress(), 456);
}

BOOST_AUTO_TEST_CASE(BaseStation_GetNodeDiscoveries)
{
	std::shared_ptr<mockConnectionImpl> connImpl(new mockConnectionImpl);
	Connection conn(connImpl);

	//create the base station (loads the info)
	BaseStation base(conn);

	//build a node discovery packet to send
	ByteStream data;
	data.append_uint8(0xAA);
	data.append_uint8(0x00);
	data.append_uint8(0x00);
	data.append_uint16(456);	//node address
	data.append_uint8(3);		//payload length
	data.append_uint8(13);
	data.append_uint16(2423);
	data.append_uint16(0x0000);	//rssi bytes
	data.append_uint16(data.calculateSimpleChecksum(1, 8));	//checksum
	connImpl->setResponseBytes(data);

	//force parsing of the bytes we just set
	connImpl->parseNextResponse();

	NodeDiscovery nd = base.getNodeDiscoveries().at(0);

	//check that a node discovery packet was found
	BOOST_CHECK_EQUAL(nd.nodeAddress(), 456);
	BOOST_CHECK_EQUAL(nd.model(), WirelessModels::node_sgLink_oem);
	BOOST_CHECK_EQUAL(nd.frequency(), 13);
}

BOOST_AUTO_TEST_CASE(BaseStation_GetNodeDiscoveries_Empty)
{
	std::shared_ptr<mockConnectionImpl> connImpl(new mockConnectionImpl);
	Connection conn(connImpl);

	//create the base station (loads the info)
	BaseStation base(conn);

	NodeDiscoveries nds = base.getNodeDiscoveries();

	//check that no node discovery packets were found
	BOOST_CHECK_EQUAL(nds.size(), 0);
}

BOOST_AUTO_TEST_CASE(BaseStation_Ping_Success)
{
	std::shared_ptr<mockConnectionImpl> connImpl(new mockConnectionImpl);
	Connection conn(connImpl);

	//create the base station (loads the info)
	BaseStation base(conn);
	base.baseCommandsTimeout(10);

	//build the data to send
	ByteStream data;
	data.append_uint8(0x01);
	connImpl->setResponseBytes(data);

	//check that the ping response is successful
	BOOST_CHECK_EQUAL(base.ping(), true);
}

BOOST_AUTO_TEST_CASE(BaseStation_Ping_Fail)
{
	std::shared_ptr<mockConnectionImpl> connImpl(new mockConnectionImpl);
	Connection conn(connImpl);

	//create the base station (loads the info)
	BaseStation base(conn);
	base.baseCommandsTimeout(10);

	//build the data to send
	ByteStream data;
	data.append_uint8(0x45);	//incorrect response
	connImpl->setResponseBytes(data);

	//check that the ping response failed
	BOOST_CHECK_EQUAL(base.ping(), false);
}

BOOST_AUTO_TEST_CASE(BaseStation_ReadEEPROM_Success)
{
	std::shared_ptr<mockConnectionImpl> connImpl(new mockConnectionImpl);
	Connection conn(connImpl);

	ByteStream data;
	data.append_uint8(0x73);
	data.append_uint16(32);
	data.append_uint16(32);

	//build the response bytes that need to be read on creation of a BaseStation
	std::vector<ByteStream> responses;
	responses.push_back(data);
	connImpl->setResponseBytes(responses);

	//create the base station (loads the info)
	BaseStation base(conn);

	//now get the actual readEEprom response
	uint16 result = base.readEeprom(56);

	//check that the response was a success and has correct values
	BOOST_CHECK_EQUAL(result, 32);
}

BOOST_AUTO_TEST_CASE(BaseStation_ReadEEPROM_Fail)
{
	std::shared_ptr<mockConnectionImpl> connImpl(new mockConnectionImpl);
	Connection conn(connImpl);

	//create the base station (loads the info)
	BaseStation base(conn);
	base.baseCommandsTimeout(10);

	//build the data to send
	ByteStream data;
	data.append_uint8(0x73);
	data.append_uint16(32);
	data.append_uint16(31);	//invalid checksum
	connImpl->setResponseBytes(data);

	BOOST_CHECK_THROW(base.readEeprom(56), Error_Communication);
}

BOOST_AUTO_TEST_CASE(BaseStation_ReadEEPROM_withEnum_Success)
{
	std::shared_ptr<mockConnectionImpl> connImpl(new mockConnectionImpl);
	Connection conn(connImpl);

	ByteStream data;
	data.append_uint8(0x73);
	data.append_uint16(32);
	data.append_uint16(32);
	connImpl->setResponseBytes(data);

	//build the response bytes that need to be read on creation of a BaseStation
	std::vector<ByteStream> responses;
	responses.push_back(data);
	connImpl->setResponseBytes(responses);

	//create the base station (loads the info)
	BaseStation base(conn);

	//now get the actual readEEprom response
	uint16 result = base.readEeprom(BaseStationEepromMap::BEACON_CONFIG.location());

	//check that the response was a success and has correct values
	BOOST_CHECK_EQUAL(result, 32);
}

BOOST_AUTO_TEST_CASE(BaseStation_WriteEEPROM_Success)
{
	std::shared_ptr<mockConnectionImpl> connImpl(new mockConnectionImpl);
	Connection conn(connImpl);

	//create the base station (loads the info)
	BaseStation base(conn);

	//build the response to send
	ByteStream data;
	data.append_uint8(0x78);
	data.append_uint16(0);
	data.append_uint16(0);//checksum

	std::vector<ByteStream> responses;
	responses.push_back(data);
	connImpl->setResponseBytes(responses);

	//check that the command doesn't throw an exception (succeeded)
	BOOST_CHECK_NO_THROW(base.writeEeprom(112, 0));
}

BOOST_AUTO_TEST_CASE(BaseStation_WriteEEPROM_Fail)
{
	std::shared_ptr<mockConnectionImpl> connImpl(new mockConnectionImpl);
	Connection conn(connImpl);

	//build the data to send
	ByteStream data;
	data.append_uint8(0x78);
	data.append_uint16(112);
	data.append_uint16(0);
	data.append_uint16(31);	//invalid checksum

	//build the response bytes that need to be read on creation of a BaseStation
	std::vector<ByteStream> responses;
	responses.push_back(data);
	connImpl->setResponseBytes(responses);

	//create the base station (loads the info)
	BaseStation base(conn);
	base.baseCommandsTimeout(10);

	//check that the command throws an exception (fails)
	BOOST_CHECK_THROW(base.writeEeprom(112, 0), Error);
}

BOOST_AUTO_TEST_CASE(BaseStation_WriteEEPROM_withEnum_Success)
{
	std::shared_ptr<mockConnectionImpl> connImpl(new mockConnectionImpl);
	Connection conn(connImpl);

	//create the base station (loads the info)
	BaseStation base(conn);

	//build the response to send
	ByteStream data;
	data.append_uint8(0x78);
	data.append_uint16(15);
	data.append_uint16(15);//checksum

	//build the response bytes that need to be read on creation of a BaseStation
	std::vector<ByteStream> responses;
	responses.push_back(data);
	connImpl->setResponseBytes(responses);

	//check that the command doesn't throw an exception (succeeded)
	BOOST_CHECK_NO_THROW(base.writeEeprom(BaseStationEepromMap::FREQUENCY.location(), 15));
}

BOOST_AUTO_TEST_CASE(BaseStation_EnableBeacon_WithTime_Success)
{
	std::shared_ptr<mockConnectionImpl> connImpl(new mockConnectionImpl);
	Connection conn(connImpl);

	//create the base station (loads the info)
	BaseStation base(conn);

	//build the data to send
	ByteStream data;
	data.append_uint16(0xBEAC);
	connImpl->setResponseBytes(data);

	const uint32 BEACON_TIME = 1358201247;
	BOOST_CHECK_NO_THROW(base.enableBeacon(BEACON_TIME));
}

BOOST_AUTO_TEST_CASE(BaseStation_EnableBeacon_Fail_Timeout)
{
	std::shared_ptr<mockConnectionImpl> connImpl(new mockConnectionImpl);
	Connection conn(connImpl);

	//create the base station (loads the info)
	BaseStation base(conn);
	base.baseCommandsTimeout(10);

	//build the data to send
	ByteStream data;
	data.append_uint16(0xACBE);//incorrect response
	connImpl->setResponseBytes(data);

	//check that the command throws an exception (failed)
	BOOST_CHECK_THROW(base.enableBeacon(), Error);
}

BOOST_AUTO_TEST_CASE(BaseStation_DisableBeacon_Success)
{
	std::shared_ptr<mockConnectionImpl> connImpl(new mockConnectionImpl);
	Connection conn(connImpl);

	//create the base station (loads the info)
	BaseStation base(conn);

	//build the data to send
	ByteStream data;
	data.append_uint16(0xBEAC);
	connImpl->setResponseBytes(data);

	//check that the command succeeded
	BOOST_CHECK_NO_THROW(base.disableBeacon());
}

BOOST_AUTO_TEST_CASE(BaseStation_DisableBeacon_Fail_Timeout)
{
	std::shared_ptr<mockConnectionImpl> connImpl(new mockConnectionImpl);
	Connection conn(connImpl);

	//create the base station (loads the info)
	BaseStation base(conn);
	base.baseCommandsTimeout(10);

	//build the data to send
	ByteStream data;
	data.append_uint16(0xABCD);
	connImpl->setResponseBytes(data);

	//check that the command succeeded
	BOOST_CHECK_THROW(base.disableBeacon(), Error);
}

BOOST_AUTO_TEST_CASE(BaseStation_cyclePower)
{
	std::shared_ptr<mockConnectionImpl> connImpl(new mockConnectionImpl);
	Connection conn(connImpl);

	//create the base station (loads the info)
	BaseStation base(conn);

	//check that the command doesn't throw an exception (succeeded)
	//Cycle Power has no response and is an eeprom write, but shouldn't throw an exception
	BOOST_CHECK_NO_THROW(base.cyclePower());
}

BOOST_AUTO_TEST_CASE(BaseStation_changeFrequency_success)
{
	std::shared_ptr<mockConnectionImpl> connImpl(new mockConnectionImpl);
	Connection conn(connImpl);

	//create the base station (loads the info)
	BaseStation base(conn);

	//build the Change Frequency response
	ByteStream data;
	data.append_uint8(0x78);
	data.append_uint16(14);
	data.append_uint16(14);//checksum

	//build the cycle power response
	ByteStream resetData;
	resetData.append_uint8(0x78);
	resetData.append_uint16(0x02);
	resetData.append_uint16(0x02);//checksum

	std::vector<ByteStream> dataResponses;
	dataResponses.push_back(data);
	dataResponses.push_back(resetData);
	connImpl->setResponseBytes(dataResponses);

	//check that the command doesn't throw an exception (succeeded)
	BOOST_CHECK_NO_THROW(base.changeFrequency(WirelessTypes::freq_14));
	BOOST_CHECK_EQUAL(base.frequency(), WirelessTypes::freq_14);
}

BOOST_AUTO_TEST_CASE(BaseStation_changeFrequency_success_outOfRange)
{
	std::shared_ptr<mockConnectionImpl> connImpl(new mockConnectionImpl);
	Connection conn(connImpl);

	//create the base station (loads the info)
	BaseStation base(conn);

	//build the Change Frequency response
	ByteStream data;
	data.append_uint8(0x78);
	data.append_uint16(11);
	data.append_uint16(11);//checksum
	
	//build the cycle power responsere
	ByteStream resetData;
	resetData.append_uint8(0x78);
	resetData.append_uint16(0x02);
	resetData.append_uint16(0x02);//checksum

	std::vector<ByteStream> dataResponses;
	dataResponses.push_back(data);
	dataResponses.push_back(resetData);
	connImpl->setResponseBytes(dataResponses);

	//check that the command doesn't throw an exception (succeeded)
	BOOST_CHECK_NO_THROW(base.changeFrequency(static_cast<WirelessTypes::Frequency>(5)));
	BOOST_CHECK_EQUAL(base.frequency(), WirelessTypes::freq_11);
}

BOOST_AUTO_TEST_CASE(BaseStation_changeFrequency_fail)
{
	std::shared_ptr<mockConnectionImpl> connImpl(new mockConnectionImpl);
	Connection conn(connImpl);

	//create the base station (loads the info)
	BaseStation base(conn, 1);

	BOOST_CHECK_THROW(base.changeFrequency(WirelessTypes::freq_14), Error);

	connImpl->setResponseBytes(loadBaseInfoResponse());
	BOOST_CHECK_EQUAL(base.frequency(), WirelessTypes::freq_13);	//verify that it didn't change frequencies
}

BOOST_AUTO_TEST_SUITE(BaseStation_Test_NodeCommands)

BOOST_AUTO_TEST_CASE(BaseStation_NodeLongPing_Success)
{
	std::shared_ptr<mockConnectionImpl> connImpl(new mockConnectionImpl);
	Connection conn(connImpl);

	//create the base station (loads the info)
	BaseStation base(conn);

	//create and set the response for the node_ping command
	ByteStream data;
	data.append_uint8(0xAA);
	data.append_uint8(0x07);
	data.append_uint8(0x02);
	data.append_uint16(327);	//node address
	data.append_uint8(0x02);
	data.append_uint16(0x0000);
	data.append_uint8(0x01);
	data.append_uint8(0x02);
	data.append_uint16(data.calculateSimpleChecksum(1, 7));	//checksum
	connImpl->setResponseBytes(data);

	//send the node_ping command
	PingResponse result = base.node_ping(327);

	BOOST_CHECK_EQUAL(result.success(), true);
	BOOST_CHECK_EQUAL(result.nodeRssi(), 1);
	BOOST_CHECK_EQUAL(result.baseRssi(), 2);
}

BOOST_AUTO_TEST_CASE(BaseStation_NodeLongPing_Fail_Timeout)
{
	std::shared_ptr<mockConnectionImpl> connImpl(new mockConnectionImpl);
	Connection conn(connImpl);

	//create the base station (loads the info)
	BaseStation base(conn);
	base.nodeCommandsTimeout(10);

	//create and set the response for the node_ping command
	ByteStream data;
	data.append_uint8(0xAA);
	connImpl->setResponseBytes(data);

	//call the node_ping command
	PingResponse result = base.node_ping(327);

	int unknownRssi = WirelessTypes::UNKNOWN_RSSI;

	BOOST_CHECK_EQUAL(result.success(), false);
	BOOST_CHECK_EQUAL(result.nodeRssi(), unknownRssi);
	BOOST_CHECK_EQUAL(result.baseRssi(), unknownRssi);
}

BOOST_AUTO_TEST_CASE(BaseStation_NodeShortPing_Fail)
{
	std::shared_ptr<mockConnectionImpl> connImpl(new mockConnectionImpl);
	Connection conn(connImpl);

	//create the base station (loads the info)
	BaseStation base(conn);

	//build the data to send
	ByteStream data;
	data.append_uint8(0x21);
	connImpl->setResponseBytes(data);

	//check that the short ping returns false
	BOOST_CHECK_EQUAL(base.node_shortPing(327), false);
}

BOOST_AUTO_TEST_CASE(BaseStation_NodeShortPing_Success)
{
	std::shared_ptr<mockConnectionImpl> connImpl(new mockConnectionImpl);
	Connection conn(connImpl);

	//create the base station (loads the info)
	BaseStation base(conn);

	//build the data to send
	ByteStream data;
	data.append_uint8(0x02);
	connImpl->setResponseBytes(data);

	//check that the short ping returns true
	BOOST_CHECK_EQUAL(base.node_shortPing(327), true);
}

BOOST_AUTO_TEST_CASE(BaseStation_NodeEepromRead_Success)
{
	std::shared_ptr<mockConnectionImpl> connImpl(new mockConnectionImpl);
	Connection conn(connImpl);

	//create the base station (loads the info)
	BaseStation base(conn);

	//build the data to send
	ByteStream data;
	data.append_uint8(0xAA);
	data.append_uint8(0x00);
	data.append_uint8(0x00);
	data.append_uint16(327);	//node address
	data.append_uint8(0x02);
	data.append_uint16(2423);
	data.append_uint8(0x01);
	data.append_uint8(0x02);
	data.append_uint16(data.calculateSimpleChecksum(1, 7));	//checksum
	connImpl->setResponseBytes(data);

	uint16 eepromValue;
	bool success = base.node_readEeprom(1, 327, 112, eepromValue);

	BOOST_CHECK_EQUAL(success, true);
	BOOST_CHECK_EQUAL(eepromValue, 2423);
}

BOOST_AUTO_TEST_CASE(BaseStation_NodeEepromRead_Fail_Timeout)
{
	std::shared_ptr<mockConnectionImpl> connImpl(new mockConnectionImpl);
	Connection conn(connImpl);

	//create the base station (loads the info)
	BaseStation base(conn);
	base.nodeCommandsTimeout(10);

	uint16 eepromValue = 0;
	bool result = base.node_readEeprom(1, 327, 112, eepromValue);

	BOOST_CHECK_EQUAL(result, false);
	BOOST_CHECK_EQUAL(eepromValue, 0);
}

BOOST_AUTO_TEST_CASE(BaseStation_NodeEepromWrite_Success)
{
	std::shared_ptr<mockConnectionImpl> connImpl(new mockConnectionImpl);
	Connection conn(connImpl);

	//build the response bytes that need to be read on creation of a BaseStation
	std::vector<ByteStream> responses;
	responses.push_back(loadBaseInfoResponse());
	connImpl->setResponseBytes(responses);

	//create the base station (loads the info)
	BaseStation base(conn);

	//build the data to send
	ByteStream data;
	data.append_uint8(0xAA);
	data.append_uint8(0x00);
	data.append_uint8(0x00);
	data.append_uint16(327);	//node address
	data.append_uint8(0x02);
	data.append_uint16(0x0004);
	data.append_uint8(0x01);
	data.append_uint8(0x02);
	data.append_uint16(data.calculateSimpleChecksum(1, 7));	//checksum
	connImpl->setResponseBytes(data);

	bool result = base.node_writeEeprom(1, 327, 112, 456);

	BOOST_CHECK_EQUAL(result, true);
}

BOOST_AUTO_TEST_CASE(BaseStation_NodeEepromWrite_Fail_Timeout)
{
	std::shared_ptr<mockConnectionImpl> connImpl(new mockConnectionImpl);
	Connection conn(connImpl);

	//create the base station (loads the info)
	BaseStation base(conn);
	base.nodeCommandsTimeout(10);


	//build the data to send
	ByteStream data;
	data.append_uint8(0xAA);
	connImpl->setResponseBytes(data);

	bool result = base.node_writeEeprom(1, 327, 112, 456);

	BOOST_CHECK_EQUAL(result, false);
}

BOOST_AUTO_TEST_CASE(BaseStation_NodePageDownload_Success)
{
	std::shared_ptr<mockConnectionImpl> connImpl(new mockConnectionImpl);
	Connection conn(connImpl);

	//create the base station (loads the info)
	BaseStation base(conn);

	//build the data to send
	ByteStream data;
	data.append_uint8(0x05);	//command id
	for(int dataItr = 0; dataItr < 132; dataItr++)
	{
		data.append_uint16(0x0000);//fake data
	}
	data.append_uint16(0x0000);//checksum
	connImpl->setResponseBytes(data);


	ByteStream resultData;
	bool result = base.node_pageDownload(123, 0, resultData);

	BOOST_CHECK_EQUAL(result, true);
	BOOST_CHECK_EQUAL(resultData.size(), 264);
	BOOST_CHECK_EQUAL(resultData.read_uint16(0), 0);
}

BOOST_AUTO_TEST_CASE(BaseStation_NodePageDownload_FailResponse)
{
	std::shared_ptr<mockConnectionImpl> connImpl(new mockConnectionImpl);
	Connection conn(connImpl);

	//create the base station (loads the info)
	BaseStation base(conn);
	base.nodeCommandsTimeout(10);

	//build the data to send
	ByteStream data;
	data.append_uint8(0x05);	//command id
	data.append_uint8(0x21);	//fail response
	connImpl->setResponseBytes(data);

	ByteStream resultData;
	bool result = base.node_pageDownload(123, 0, resultData);

	BOOST_CHECK_EQUAL(result, false);
	BOOST_CHECK_EQUAL(resultData.size(), 0);
}

BOOST_AUTO_TEST_CASE(BaseStation_node_startSyncSampling)
{
	std::shared_ptr<mockConnectionImpl> connImpl(new mockConnectionImpl);
	Connection conn(connImpl);

	//create the base station (loads the info)
	BaseStation base(conn);
	base.baseCommandsTimeout(10);
	base.nodeCommandsTimeout(10);

	//build the Start Sync Sampling response bytes
	ByteStream data;
	data.append_uint8(0xAA);
	data.append_uint8(0x07);
	data.append_uint8(0x00);
	data.append_uint16(327);	//node address
	data.append_uint8(0x03);
	data.append_uint16(0x003B);
	data.append_uint8(0x00);
	data.append_uint8(0x01);
	data.append_uint8(0x02);
	data.append_uint16(data.calculateSimpleChecksum(1, 8));	//checksum
	connImpl->setResponseBytes(data);
	
	BOOST_CHECK_EQUAL(base.node_startSyncSampling(327), true);

	//send the command again, but fail this time
	BOOST_CHECK_EQUAL(base.node_startSyncSampling(400), false);
}

BOOST_AUTO_TEST_CASE(BaseStation_getButtonLongPress)
{
	//Tests getButtonLongPress() function

	std::shared_ptr<mock_baseStationImpl> impl(new mock_baseStationImpl());
	BaseStation b(impl);

	//make the features() function return the BaseStationFeatures we want
	std::unique_ptr<BaseStationFeatures> features;
	expectBaseFeatures(features, impl, WirelessModels::base_wsdaBase_101_analog);

	//expect the eeprom writes
	expectRead(impl, BaseStationEepromMap::BUTTON1_LONG_FUNC, Value::UINT16(BaseStationButton::btn_nodeSleep));
	expectRead(impl, BaseStationEepromMap::BUTTON1_LONG_NODE, Value::UINT16(65534));

	BaseStationButton btn = b.getButtonLongPress(1);

	BOOST_CHECK_EQUAL(btn.command(), BaseStationButton::btn_nodeSleep);
	BOOST_CHECK_EQUAL(btn.nodeAddress(), 65534);
}

BOOST_AUTO_TEST_CASE(BaseStation_getButtonShortPress)
{
	//Tests getButtonShortPress() function

	std::shared_ptr<mock_baseStationImpl> impl(new mock_baseStationImpl());
	BaseStation b(impl);

	//make the features() function return the BaseStationFeatures we want
	std::unique_ptr<BaseStationFeatures> features;
	expectBaseFeatures(features, impl, WirelessModels::base_wsdaBase_101_analog);

	//expect the eeprom writes
	expectRead(impl, BaseStationEepromMap::BUTTON2_SHORT_FUNC, Value::UINT16(BaseStationButton::btn_disabled));
	expectRead(impl, BaseStationEepromMap::BUTTON2_SHORT_NODE, Value::UINT16(0));

	BaseStationButton btn = b.getButtonShortPress(2);

	BOOST_CHECK_EQUAL(btn.command(), BaseStationButton::btn_disabled);
	BOOST_CHECK_EQUAL(btn.nodeAddress(), 0);
}

BOOST_AUTO_TEST_CASE(BaseStation_node_autocal_fail)
{
	std::shared_ptr<mockConnectionImpl> connImpl(new mockConnectionImpl);
	Connection conn(connImpl);

	//create the base station (loads the info)
	BaseStation base(conn);
	base.baseCommandsTimeout(10);
	base.nodeCommandsTimeout(10);

	//Build the Node Received response bytes
	ByteStream data;
	data.append_uint8(0xAA);
	data.append_uint8(0x07);
	data.append_uint8(0x20);
	data.append_uint16(327);	//node address
	data.append_uint8(0x07);
	data.append_uint16(0x0064);
	data.append_uint8(0x00);
	data.append_float(0.1f);	//time to completion
	data.append_uint8(0x02);
	data.append_uint8(0x00);
	data.append_uint16(data.calculateSimpleChecksum(1, 12));	//checksum
	connImpl->setResponseBytes(data);

	AutoCalResult_shmLink result;
	BOOST_CHECK_EQUAL(base.node_autocal(327, WirelessModels::node_shmLink2, Version(9,0), result), false);

	BOOST_CHECK_EQUAL(result.completionFlag(), WirelessTypes::autocal_notComplete);
}

BOOST_AUTO_TEST_CASE(BaseStation_node_autocal_success)
{
	std::shared_ptr<mockConnectionImpl> connImpl(new mockConnectionImpl);
	Connection conn(connImpl);

	//create the base station (loads the info)
	BaseStation base(conn);
	base.baseCommandsTimeout(10);
	base.nodeCommandsTimeout(10);

	//Build the Node Received response bytes
	ByteStream data;
	data.append_uint8(0xAA);
	data.append_uint8(0x07);
	data.append_uint8(0x20);
	data.append_uint16(327);	//node address
	data.append_uint8(0x07);
	data.append_uint16(0x0064);
	data.append_uint8(0x00);
	data.append_float(2.0f);	//time to completion
	data.append_uint8(0x02);
	data.append_uint8(0x00);
	data.append_uint16(data.calculateSimpleChecksum(1, 12));	//checksum

	//Build the Completion response bytes
	ByteStream data2;
	data2.append_uint8(0xAA);
	data2.append_uint8(0x07);
	data2.append_uint8(0x01);
	data2.append_uint16(327);	//node address
	data2.append_uint8(22);
	data2.append_uint16(0x0064);	//cmd id
	data2.append_uint8(0x00);	//completion flag
	data2.append_uint8(0x00);	//ch1 error flag
	data2.append_float(0.4f);	//ch1 offset
	data2.append_uint8(0x01);	//ch2 error flag
	data2.append_float(0.09f);	//ch2 offset
	data2.append_uint8(0x02);	//ch3 error flag
	data2.append_float(87.56f);	//ch3 offset
	data2.append_float(20.5f);//temperature
	data2.append_uint8(0x00);
	data2.append_uint8(0x00);
	data2.append_uint16(data2.calculateSimpleChecksum(1, 27));	//checksum

	std::vector<ByteStream> responses;
	responses.push_back(data);
	responses.push_back(data2);
	connImpl->setResponseBytesWithDelay(responses, 2000);

	AutoCalResult_shmLink result;
	BOOST_CHECK_EQUAL(base.node_autocal(327, WirelessModels::node_shmLink2, Version(9, 0), result), true);

	BOOST_CHECK_EQUAL(result.completionFlag(), WirelessTypes::autocal_success);
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE_END()