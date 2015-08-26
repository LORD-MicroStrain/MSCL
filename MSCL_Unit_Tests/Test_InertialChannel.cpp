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
#include "mscl/MicroStrain/Inertial/InertialChannel.h"

#include <boost/test/unit_test.hpp>

using namespace mscl;

BOOST_AUTO_TEST_SUITE(InertialChannel_Test)

BOOST_AUTO_TEST_CASE(InertialChannel_Constructor_Success)
{
	InertialChannel ch1(InertialTypes::CH_FIELD_GPS_LLH_POSITION, SampleRate::Hertz(20));

	BOOST_CHECK_EQUAL(ch1.channelField(), InertialTypes::CH_FIELD_GPS_LLH_POSITION);
	BOOST_CHECK_EQUAL(ch1.rateDecimation(200), 10);
	BOOST_CHECK_EQUAL(ch1.sampleRate().samplesPerSecond(), SampleRate::Hertz(20).samplesPerSecond());
	BOOST_CHECK_EQUAL(ch1.fieldDescriptor(), 0x03);
	BOOST_CHECK_EQUAL(ch1.descriptorSet(), 0x81);

	InertialChannel ch2(InertialTypes::CH_FIELD_SENSOR_EULER_ANGLES, SampleRate::Hertz(32));

	BOOST_CHECK_EQUAL(ch2.channelField(), InertialTypes::CH_FIELD_SENSOR_EULER_ANGLES);
	BOOST_CHECK_EQUAL(ch2.rateDecimation(128), 4);
	BOOST_CHECK_EQUAL(ch2.sampleRate().samplesPerSecond(), SampleRate::Hertz(32).samplesPerSecond());
	BOOST_CHECK_EQUAL(ch2.fieldDescriptor(), 0x0C);
	BOOST_CHECK_EQUAL(ch2.descriptorSet(), 0x80);
}

BOOST_AUTO_TEST_CASE(InertialChannel_validateSampleRate_noChange)
{
	SampleRate result;

	InertialChannel ch1(InertialTypes::CH_FIELD_GPS_LLH_POSITION, SampleRate::Hertz(2));

	result = ch1.validateSampleRate(1000);
	BOOST_CHECK_EQUAL(ch1.sampleRate().samplesPerSecond(), SampleRate::Hertz(2).samplesPerSecond());	//check nothing changed
	BOOST_CHECK_EQUAL(result.samplesPerSecond(), SampleRate::Hertz(2).samplesPerSecond());	//check nothing changed
}

BOOST_AUTO_TEST_CASE(InertialChannel_validateSampleRate_changed)
{
	SampleRate result;

	InertialChannel ch1(InertialTypes::CH_FIELD_GPS_LLH_POSITION, SampleRate::Hertz(3));

	result = ch1.validateSampleRate(1000);
	BOOST_CHECK_EQUAL(ch1.sampleRate().samplesPerSecond(), SampleRate::Hertz(4).samplesPerSecond());	//check it was updated to 4 hz
	BOOST_CHECK_EQUAL(result.samplesPerSecond(), SampleRate::Hertz(4).samplesPerSecond());	//check it is 4hz


	InertialChannel ch2(InertialTypes::CH_FIELD_GPS_LLH_POSITION, SampleRate::Hertz(275));

	result = ch2.validateSampleRate(1000);
	BOOST_CHECK_EQUAL(ch2.sampleRate().samplesPerSecond(), SampleRate::Hertz(500).samplesPerSecond());	//check it was updated
	BOOST_CHECK_EQUAL(result.samplesPerSecond(), SampleRate::Hertz(500).samplesPerSecond());	//check it is updated


	InertialChannel ch3(InertialTypes::CH_FIELD_GPS_LLH_POSITION, SampleRate::Hertz(3));

	result = ch3.validateSampleRate(4);
	BOOST_CHECK_EQUAL(ch3.sampleRate().samplesPerSecond(), SampleRate::Hertz(4).samplesPerSecond());	//check it was updated
	BOOST_CHECK_EQUAL(result.samplesPerSecond(), SampleRate::Hertz(4).samplesPerSecond());	//check it is updated

	InertialChannel ch4(InertialTypes::CH_FIELD_GPS_LLH_POSITION, SampleRate::Hertz(100));

	result = ch4.validateSampleRate(4);
	BOOST_CHECK_EQUAL(ch4.sampleRate().samplesPerSecond(), SampleRate::Hertz(4).samplesPerSecond());	//check it was updated
	BOOST_CHECK_EQUAL(result.samplesPerSecond(), SampleRate::Hertz(4).samplesPerSecond());	//check it is updated

	InertialChannel ch5(InertialTypes::CH_FIELD_GPS_LLH_POSITION, SampleRate::Seconds(10));

	result = ch5.validateSampleRate(1000);
	BOOST_CHECK_EQUAL(ch5.sampleRate().samplesPerSecond(), SampleRate::Hertz(1).samplesPerSecond());	//check it was updated
	BOOST_CHECK_EQUAL(result.samplesPerSecond(), SampleRate::Hertz(1).samplesPerSecond());	//check it is updated
}

BOOST_AUTO_TEST_SUITE_END()