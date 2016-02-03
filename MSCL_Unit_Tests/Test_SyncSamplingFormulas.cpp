/*******************************************************************************
Copyright(c) 2015-2016 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "mscl/MicroStrain/Wireless/SyncSamplingFormulas.h"
#include "mscl/MicroStrain/SampleRate.h"

#include <boost/test/unit_test.hpp>

using namespace mscl;

BOOST_AUTO_TEST_SUITE(SyncSamplingFormulas_Test)

BOOST_AUTO_TEST_CASE(SyncSamplingFormulas_bytesPerSecond)
{
    SampleRate hz_1 = SampleRate::Hertz(1);
    SampleRate hz_256 = SampleRate::Hertz(256);
    SampleRate sec_10 = SampleRate::Seconds(10);

    BOOST_CHECK_CLOSE(SyncSamplingFormulas::bytesPerSecond(hz_1, 4, 2), 8.0, 0.1);
    BOOST_CHECK_CLOSE(SyncSamplingFormulas::bytesPerSecond(hz_1, 4, 4), 16.0, 0.1);
    
    BOOST_CHECK_CLOSE(SyncSamplingFormulas::bytesPerSecond(hz_256, 4, 2), 2048.0, 0.1);

    BOOST_CHECK_CLOSE(SyncSamplingFormulas::bytesPerSecond(sec_10, 4, 2), 0.8, 0.1);
}

BOOST_AUTO_TEST_CASE(SyncSamplingFormulas_maxBytesPerPacket)
{
    SampleRate hz_256 = SampleRate::Hertz(256);
    SampleRate hz_512 = SampleRate::Hertz(512);
    SampleRate sec_10 = SampleRate::Seconds(10);

    BOOST_CHECK_EQUAL(SyncSamplingFormulas::maxBytesPerPacket(hz_256, true, true, 1), 32);
    BOOST_CHECK_EQUAL(SyncSamplingFormulas::maxBytesPerPacket(hz_256, true, false, 1), 64);
    BOOST_CHECK_EQUAL(SyncSamplingFormulas::maxBytesPerPacket(hz_256, false, false, 1), 96);
    BOOST_CHECK_EQUAL(SyncSamplingFormulas::maxBytesPerPacket(hz_512, true, true, 1), 32);
    BOOST_CHECK_EQUAL(SyncSamplingFormulas::maxBytesPerPacket(hz_512, true, false, 1), 48);
    BOOST_CHECK_EQUAL(SyncSamplingFormulas::maxBytesPerPacket(sec_10, true, false, 1), 64);
}

BOOST_AUTO_TEST_CASE(SyncSamplingFormulas_groupSize)
{
    BOOST_CHECK_EQUAL(SyncSamplingFormulas::groupSize(128.0, 200, true), 1);
    BOOST_CHECK_EQUAL(SyncSamplingFormulas::groupSize(128.0, 400, true), 2);

    BOOST_CHECK_EQUAL(SyncSamplingFormulas::groupSize(128.0, 400, false), 1);

    BOOST_CHECK_EQUAL(SyncSamplingFormulas::groupSize(2.0, 400, true), 16);
}

BOOST_AUTO_TEST_CASE(SyncSamplingFormulas_txPerGroup)
{
    BOOST_CHECK_EQUAL(SyncSamplingFormulas::txPerGroup(128.0, 200, 1), 1);
    BOOST_CHECK_EQUAL(SyncSamplingFormulas::txPerGroup(128.0, 400, 2), 1);
    BOOST_CHECK_EQUAL(SyncSamplingFormulas::txPerGroup(2.0, 400, 16), 1);
    BOOST_CHECK_EQUAL(SyncSamplingFormulas::txPerGroup(128.0, 2, 1), 64);

    BOOST_CHECK_EQUAL(SyncSamplingFormulas::txPerGroup(2048.0, 64, 1), 32);
}

BOOST_AUTO_TEST_CASE(SyncSamplingFormulas_txPerSecond)
{
    BOOST_CHECK_CLOSE(SyncSamplingFormulas::txPerSecond(1, 0), 0.0, 0.1);
    BOOST_CHECK_CLOSE(SyncSamplingFormulas::txPerSecond(4, 1), 4.0, 0.1);
    BOOST_CHECK_CLOSE(SyncSamplingFormulas::txPerSecond(16, 2), 8.0, 0.1);
}

BOOST_AUTO_TEST_CASE(SyncSamplingFormulas_slotSpacing)
{
    BOOST_CHECK_EQUAL(SyncSamplingFormulas::slotSpacing(), 8);
}

BOOST_AUTO_TEST_CASE(SyncSamplingFormulas_maxTdmaAddress)
{
    BOOST_CHECK_EQUAL(SyncSamplingFormulas::maxTdmaAddress(4, 1), 248);
    BOOST_CHECK_EQUAL(SyncSamplingFormulas::maxTdmaAddress(16, 2), 120);
}

BOOST_AUTO_TEST_CASE(SyncSamplingFormulas_percentBandwidth)
{
    BOOST_CHECK_CLOSE(SyncSamplingFormulas::percentBandwidth(0.0f), 0.0, 0.1);
    BOOST_CHECK_CLOSE(SyncSamplingFormulas::percentBandwidth(4.0f), 3.128, 0.1);
    BOOST_CHECK_CLOSE(SyncSamplingFormulas::percentBandwidth(8.0f), 6.256, 0.1);
}

BOOST_AUTO_TEST_CASE(SyncSamplingFormulas_sampleDuration)
{
    SampleRate hz_1 = SampleRate::Hertz(1);
    SampleRate hz_256 = SampleRate::Hertz(256);
    SampleRate sec_10 = SampleRate::Seconds(10);

    BOOST_CHECK_CLOSE(SyncSamplingFormulas::sampleDuration(200, hz_1), 200, 0.1);
    BOOST_CHECK_CLOSE(SyncSamplingFormulas::sampleDuration(400, hz_256), 1.5625, 0.1);
    BOOST_CHECK_CLOSE(SyncSamplingFormulas::sampleDuration(800, sec_10), 8000, 0.1);
}

BOOST_AUTO_TEST_CASE(SyncSamplingFormulas_bytesPerSweep)
{
    BOOST_CHECK_EQUAL(SyncSamplingFormulas::bytesPerSweep(2, 4), 8);
    BOOST_CHECK_EQUAL(SyncSamplingFormulas::bytesPerSweep(4, 8), 32);
}

BOOST_AUTO_TEST_CASE(SyncSamplingFormulas_checkSamplingDelay)
{
    SampleRate hz_1 = SampleRate::Hertz(1);
    SampleRate hz_256 = SampleRate::Hertz(256);

    BOOST_CHECK_EQUAL(SyncSamplingFormulas::checkSamplingDelay(WirelessTypes::syncMode_continuous, hz_1, WirelessModels::node_gLink_10g), true);
    BOOST_CHECK_EQUAL(SyncSamplingFormulas::checkSamplingDelay(WirelessTypes::syncMode_continuous, hz_256, WirelessModels::node_tcLink_1ch), true);
    BOOST_CHECK_EQUAL(SyncSamplingFormulas::checkSamplingDelay(WirelessTypes::syncMode_continuous, hz_256, WirelessModels::node_shmLink), true);

    BOOST_CHECK_EQUAL(SyncSamplingFormulas::checkSamplingDelay(WirelessTypes::syncMode_continuous, hz_256, WirelessModels::node_gLink_10g), false);
}

BOOST_AUTO_TEST_CASE(SyncSamplingFormulas_slotsBetweenTx)
{
    BOOST_CHECK_EQUAL(SyncSamplingFormulas::slotsBetweenTx(2, 2), 1024);
    BOOST_CHECK_EQUAL(SyncSamplingFormulas::slotsBetweenTx(8, 2), 256);
    BOOST_CHECK_EQUAL(SyncSamplingFormulas::slotsBetweenTx(2, 8), 4096);
}

BOOST_AUTO_TEST_CASE(SyncSamplingFormulas_canHaveSlot1)
{
    BOOST_CHECK_EQUAL(SyncSamplingFormulas::canHaveSlot1(WirelessModels::node_sgLink, 1), true);
    BOOST_CHECK_EQUAL(SyncSamplingFormulas::canHaveSlot1(WirelessModels::node_tcLink_1ch, 1), false);
    BOOST_CHECK_EQUAL(SyncSamplingFormulas::canHaveSlot1(WirelessModels::node_tcLink_1ch, 2), true);
}

BOOST_AUTO_TEST_CASE(SyncSamplingFormulas_totalBytesPerBurst)
{
    BOOST_CHECK_EQUAL(SyncSamplingFormulas::totalBytesPerBurst(256, 2), 512);
    BOOST_CHECK_EQUAL(SyncSamplingFormulas::totalBytesPerBurst(20, 30), 600);
}

BOOST_AUTO_TEST_CASE(SyncSamplingFormulas_maxDataBytesPerPacket)
{
    BOOST_CHECK_EQUAL(SyncSamplingFormulas::maxDataBytesPerPacket(20, true), 80);
    BOOST_CHECK_EQUAL(SyncSamplingFormulas::maxDataBytesPerPacket(256, true), 0);
    BOOST_CHECK_EQUAL(SyncSamplingFormulas::maxDataBytesPerPacket(20, false), 80);
    BOOST_CHECK_EQUAL(SyncSamplingFormulas::maxDataBytesPerPacket(256, false), 0);
}

BOOST_AUTO_TEST_CASE(SyncSamplingFormulas_totalNeededBurstTx)
{
    BOOST_CHECK_EQUAL(SyncSamplingFormulas::totalNeededBurstTx(200, 400), 1);
    BOOST_CHECK_EQUAL(SyncSamplingFormulas::totalNeededBurstTx(400, 20), 20);
}

BOOST_AUTO_TEST_CASE(SyncSamplingFormulas_minTimeBetweenBursts)
{
    BOOST_CHECK_EQUAL(SyncSamplingFormulas::minTimeBetweenBursts(20, 2.0, true), 7);
    BOOST_CHECK_EQUAL(SyncSamplingFormulas::minTimeBetweenBursts(1, 0.5, true), 5);
    BOOST_CHECK_EQUAL(SyncSamplingFormulas::minTimeBetweenBursts(400, 2.0, false), 13);
}

BOOST_AUTO_TEST_CASE(SyncSamplingFormulas_burstTxPerSecond)
{
    BOOST_CHECK_EQUAL(SyncSamplingFormulas::burstTxPerSecond(4, 20, 2.0, true), 1);
    BOOST_CHECK_EQUAL(SyncSamplingFormulas::burstTxPerSecond(4, 2, 2.0, true), 2);
}

BOOST_AUTO_TEST_SUITE_END()