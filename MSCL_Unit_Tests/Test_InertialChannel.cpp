/*****************************************************************************************
**          Copyright(c) 2015-2024 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "mscl/MicroStrain/MIP/MipChannel.h"

#include <boost/test/unit_test.hpp>

using namespace mscl;

BOOST_AUTO_TEST_SUITE(InertialChannel_Test)

BOOST_AUTO_TEST_CASE(InertialChannel_Constructor_Success)
{
    MipChannel ch1(MipTypes::CH_FIELD_GNSS_LLH_POSITION, SampleRate::Hertz(20));

    BOOST_CHECK_EQUAL(ch1.channelField(), MipTypes::CH_FIELD_GNSS_LLH_POSITION);
    BOOST_CHECK_EQUAL(ch1.rateDecimation(200), 10);
    BOOST_CHECK_EQUAL(ch1.sampleRate().samplesPerSecond(), SampleRate::Hertz(20).samplesPerSecond());
    BOOST_CHECK_EQUAL(ch1.fieldDescriptor(), 0x03);
    BOOST_CHECK_EQUAL(ch1.descriptorSet(), 0x81);

    MipChannel ch2(MipTypes::CH_FIELD_SENSOR_EULER_ANGLES, SampleRate::Hertz(32));

    BOOST_CHECK_EQUAL(ch2.channelField(), MipTypes::CH_FIELD_SENSOR_EULER_ANGLES);
    BOOST_CHECK_EQUAL(ch2.rateDecimation(128), 4);
    BOOST_CHECK_EQUAL(ch2.sampleRate().samplesPerSecond(), SampleRate::Hertz(32).samplesPerSecond());
    BOOST_CHECK_EQUAL(ch2.fieldDescriptor(), 0x0C);
    BOOST_CHECK_EQUAL(ch2.descriptorSet(), 0x80);
}

BOOST_AUTO_TEST_SUITE_END()
