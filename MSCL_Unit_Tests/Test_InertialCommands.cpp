/*******************************************************************************
Copyright(c) 2015-2017 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "mscl/MicroStrain/Inertial/Commands/Inertial_Commands.h"
#include "mscl/MicroStrain/Inertial/InertialChannel.h"

#include <boost/test/unit_test.hpp>
using namespace mscl;

BOOST_AUTO_TEST_SUITE(InertialCommands_Test)

BOOST_AUTO_TEST_CASE(InertialCommands_parseData_DataRateBase)
{
    ByteStream data;
    data.append_uint16(500);

    GenericInertialCommandResponse res = GenericInertialCommandResponse::ResponseSuccess("", data);

    uint16 rateBase = Inertial_Commands::parseData_DataRateBase(res);

    //check that it parsed the response correctly
    BOOST_CHECK_EQUAL(rateBase, 500);
}

BOOST_AUTO_TEST_CASE(InertialCommands_parseData_MessageFormat)
{
    ByteStream data;
    data.append_uint8(0x02);
    data.append_uint8(0x06);    //CH_AHRS_SCALED_MAG_VEC
    data.append_uint16(10);        //rate decimation
    data.append_uint8(0x09);    //CH_AHRS_ORIENTATION_MATRIX
    data.append_uint16(2);        //rate decimation

    GenericInertialCommandResponse res = GenericInertialCommandResponse::ResponseSuccess("", data);

    uint16 sampleRateBase = 1000;

    InertialChannels chs = Inertial_Commands::parseData_MessageFormat(res, 0x80, sampleRateBase);

    //check that it parsed the response correctly
    BOOST_CHECK_EQUAL(chs.size(), 2);
    BOOST_CHECK_EQUAL(chs.at(0).channelField(), InertialTypes::CH_FIELD_SENSOR_SCALED_MAG_VEC);
    BOOST_CHECK_EQUAL(chs.at(0).rateDecimation(sampleRateBase), 10);
    BOOST_CHECK_EQUAL(chs.at(0).sampleRate().samplesPerSecond(), SampleRate::Hertz(100).samplesPerSecond());
    BOOST_CHECK_EQUAL(chs.at(1).channelField(), InertialTypes::CH_FIELD_SENSOR_ORIENTATION_MATRIX);
    BOOST_CHECK_EQUAL(chs.at(1).rateDecimation(sampleRateBase), 2);
    BOOST_CHECK_EQUAL(chs.at(1).sampleRate().samplesPerSecond(), SampleRate::Hertz(500).samplesPerSecond());
}

BOOST_AUTO_TEST_SUITE_END()