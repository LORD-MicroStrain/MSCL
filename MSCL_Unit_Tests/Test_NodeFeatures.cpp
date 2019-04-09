/*******************************************************************************
Copyright(c) 2015-2019 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "mscl/MicroStrain/Wireless/Features/NodeFeatures.h"
#include "mscl/Exceptions.h"
#include "mscl/MicroStrain/Wireless/ChannelMask.h"

#include <boost/test/unit_test.hpp>

using namespace mscl;

BOOST_AUTO_TEST_SUITE(NodeFeatures_Test)

NodeInfo createInfo(WirelessModels::NodeModel node)
{
    return NodeInfo(Version(9, 9), node, WirelessTypes::region_usa);
}

BOOST_AUTO_TEST_CASE(NodeFeatures_create)
{
    std::shared_ptr<NodeFeatures> dvrtLink = NodeFeatures::create(createInfo(WirelessModels::node_dvrtLink));
    BOOST_CHECK_EQUAL(dvrtLink->supportsInputRange(), false);

    std::shared_ptr<NodeFeatures> glink10g = NodeFeatures::create(createInfo(WirelessModels::node_gLink_10g));
    BOOST_CHECK_EQUAL(glink10g->supportsInputRange(), false);

    std::shared_ptr<NodeFeatures> glink2 = NodeFeatures::create(createInfo(WirelessModels::node_gLinkII_2g_ex));
    BOOST_CHECK_EQUAL(glink2->supportsInputRange(), false);

    std::shared_ptr<NodeFeatures> glink2in = NodeFeatures::create(createInfo(WirelessModels::node_gLinkII_2g_in));
    BOOST_CHECK_EQUAL(glink2in->supportsInputRange(), false);

    std::shared_ptr<NodeFeatures> sgLink = NodeFeatures::create(createInfo(WirelessModels::node_sgLink));
    BOOST_CHECK_EQUAL(sgLink->supportsInputRange(), true);

    std::shared_ptr<NodeFeatures> sgLinkoem = NodeFeatures::create(createInfo(WirelessModels::node_sgLink_oem));
    BOOST_CHECK_EQUAL(sgLinkoem->supportsInputRange(), true);

    std::shared_ptr<NodeFeatures> sgLinkHerm = NodeFeatures::create(createInfo(WirelessModels::node_sgLink_herm));
    BOOST_CHECK_EQUAL(sgLinkHerm->supportsInputRange(), true);

    std::shared_ptr<NodeFeatures> sgLinkOemNoXr = NodeFeatures::create(createInfo(WirelessModels::node_sgLink_oem_S));
    BOOST_CHECK_EQUAL(sgLinkOemNoXr->supportsInputRange(), true);

    std::shared_ptr<NodeFeatures> sgLinkrgd = NodeFeatures::create(createInfo(WirelessModels::node_sgLink_rgd));
    BOOST_CHECK_EQUAL(sgLinkrgd->supportsInputRange(), true);

    std::shared_ptr<NodeFeatures> shmLink = NodeFeatures::create(createInfo(WirelessModels::node_shmLink));
    BOOST_CHECK_EQUAL(shmLink->supportsInputRange(), true);

    std::shared_ptr<NodeFeatures> vLink = NodeFeatures::create(createInfo(WirelessModels::node_vLink));
    BOOST_CHECK_EQUAL(vLink->supportsInputRange(), true);

    std::shared_ptr<NodeFeatures> tcLink6 = NodeFeatures::create(createInfo(WirelessModels::node_tcLink_6ch));
    BOOST_CHECK_EQUAL(tcLink6->supportsInputRange(), true);

    std::shared_ptr<NodeFeatures> tcLink3 = NodeFeatures::create(createInfo(WirelessModels::node_tcLink_3ch));
    BOOST_CHECK_EQUAL(tcLink3->supportsInputRange(), true);

    std::shared_ptr<NodeFeatures> tcLink1 = NodeFeatures::create(createInfo(WirelessModels::node_tcLink_1ch));
    BOOST_CHECK_EQUAL(tcLink1->supportsInputRange(), true);

    std::shared_ptr<NodeFeatures> rtd = NodeFeatures::create(createInfo(WirelessModels::node_rtdLink));
    BOOST_CHECK_EQUAL(rtd->supportsInputRange(), true);

    std::shared_ptr<NodeFeatures> iepe = NodeFeatures::create(createInfo(WirelessModels::node_iepeLink));
    BOOST_CHECK_EQUAL(iepe->supportsInputRange(), false);

    std::shared_ptr<NodeFeatures> envPro = NodeFeatures::create(createInfo(WirelessModels::node_envLink_pro));
    BOOST_CHECK_EQUAL(envPro->supportsInputRange(), true);

    std::shared_ptr<NodeFeatures> envMini = NodeFeatures::create(createInfo(WirelessModels::node_envLink_mini));
    BOOST_CHECK_EQUAL(envMini->supportsInputRange(), true);
}

BOOST_AUTO_TEST_CASE(NodeFeatures_create_unknownModel)
{
    BOOST_CHECK_THROW(NodeFeatures::create(createInfo(static_cast<WirelessModels::NodeModel>(0))), Error_NotSupported);
}

BOOST_AUTO_TEST_CASE(NodeFeatures_supportsGaugeFactor)
{
    std::shared_ptr<NodeFeatures> sglink = NodeFeatures::create(createInfo(WirelessModels::node_sgLink));
    BOOST_CHECK_EQUAL(sglink->supportsGaugeFactor(), false);

    std::shared_ptr<NodeFeatures> shmLink2 = NodeFeatures::create(createInfo(WirelessModels::node_shmLink2_cust1));
    BOOST_CHECK_EQUAL(shmLink2->supportsGaugeFactor(), true);
}

BOOST_AUTO_TEST_CASE(NodeFeatures_supportsDefaultMode)
{
    std::shared_ptr<NodeFeatures> glink = NodeFeatures::create(createInfo(WirelessModels::node_gLink_10g));
    BOOST_CHECK_EQUAL(glink->supportsDefaultMode(WirelessTypes::defaultMode_ldc), true);
    BOOST_CHECK_EQUAL(glink->supportsDefaultMode(WirelessTypes::defaultMode_datalog), true);
    BOOST_CHECK_EQUAL(glink->supportsDefaultMode(WirelessTypes::defaultMode_idle), true);
    BOOST_CHECK_EQUAL(glink->supportsDefaultMode(WirelessTypes::defaultMode_sleep), true);
    BOOST_CHECK_EQUAL(glink->supportsDefaultMode(WirelessTypes::defaultMode_sync), true);

    std::shared_ptr<NodeFeatures> iepe = NodeFeatures::create(createInfo(WirelessModels::node_iepeLink));
    BOOST_CHECK_EQUAL(iepe->supportsDefaultMode(WirelessTypes::defaultMode_ldc), false);
    BOOST_CHECK_EQUAL(iepe->supportsDefaultMode(WirelessTypes::defaultMode_datalog), false);
    BOOST_CHECK_EQUAL(iepe->supportsDefaultMode(WirelessTypes::defaultMode_idle), true);
    BOOST_CHECK_EQUAL(iepe->supportsDefaultMode(WirelessTypes::defaultMode_sleep), true);
    BOOST_CHECK_EQUAL(iepe->supportsDefaultMode(WirelessTypes::defaultMode_sync), true);
}

BOOST_AUTO_TEST_CASE(NodeFeatures_supportsChannel)
{
    std::shared_ptr<NodeFeatures> dvrtLink = NodeFeatures::create(createInfo(WirelessModels::node_dvrtLink));
    BOOST_CHECK_EQUAL(dvrtLink->supportsChannel(1), false);
    BOOST_CHECK_EQUAL(dvrtLink->supportsChannel(3), true);

    std::shared_ptr<NodeFeatures> glink10g = NodeFeatures::create(createInfo(WirelessModels::node_gLink_10g));
    BOOST_CHECK_EQUAL(glink10g->supportsChannel(1), true);
    BOOST_CHECK_EQUAL(glink10g->supportsChannel(3), true);
    BOOST_CHECK_EQUAL(glink10g->supportsChannel(5), false);

    std::shared_ptr<NodeFeatures> glink2 = NodeFeatures::create(createInfo(WirelessModels::node_gLinkII_2g_ex));
    BOOST_CHECK_EQUAL(glink10g->supportsChannel(1), true);
    BOOST_CHECK_EQUAL(glink10g->supportsChannel(3), true);
    BOOST_CHECK_EQUAL(glink10g->supportsChannel(5), false);

    std::shared_ptr<NodeFeatures> sgLink = NodeFeatures::create(createInfo(WirelessModels::node_sgLink));
    BOOST_CHECK_EQUAL(sgLink->supportsChannel(1), true);
    BOOST_CHECK_EQUAL(sgLink->supportsChannel(4), true);
    BOOST_CHECK_EQUAL(sgLink->supportsChannel(5), false);

    std::shared_ptr<NodeFeatures> sgLinkoem = NodeFeatures::create(createInfo(WirelessModels::node_sgLink_oem));
    BOOST_CHECK_EQUAL(sgLinkoem->supportsChannel(1), true);
    BOOST_CHECK_EQUAL(sgLinkoem->supportsChannel(4), true);
    BOOST_CHECK_EQUAL(sgLinkoem->supportsChannel(5), false);

    std::shared_ptr<NodeFeatures> sgLinkHerm = NodeFeatures::create(createInfo(WirelessModels::node_sgLink_herm));
    BOOST_CHECK_EQUAL(sgLinkHerm->supportsChannel(1), true);
    BOOST_CHECK_EQUAL(sgLinkHerm->supportsChannel(4), true);
    BOOST_CHECK_EQUAL(sgLinkHerm->supportsChannel(5), false);

    std::shared_ptr<NodeFeatures> sgLinkOemNoXr = NodeFeatures::create(createInfo(WirelessModels::node_sgLink_oem_S));
    BOOST_CHECK_EQUAL(sgLinkOemNoXr->supportsChannel(1), true);
    BOOST_CHECK_EQUAL(sgLinkOemNoXr->supportsChannel(4), true);
    BOOST_CHECK_EQUAL(sgLinkOemNoXr->supportsChannel(5), false);

    std::shared_ptr<NodeFeatures> sgLinkrgd = NodeFeatures::create(createInfo(WirelessModels::node_sgLink_rgd));
    BOOST_CHECK_EQUAL(sgLinkrgd->supportsChannel(1), true);
    BOOST_CHECK_EQUAL(sgLinkrgd->supportsChannel(4), true);
    BOOST_CHECK_EQUAL(sgLinkrgd->supportsChannel(7), true);
    BOOST_CHECK_EQUAL(sgLinkrgd->supportsChannel(9), false);

    std::shared_ptr<NodeFeatures> shmLink = NodeFeatures::create(createInfo(WirelessModels::node_shmLink));
    BOOST_CHECK_EQUAL(shmLink->supportsChannel(1), true);
    BOOST_CHECK_EQUAL(shmLink->supportsChannel(4), false);
    BOOST_CHECK_EQUAL(shmLink->supportsChannel(7), true);
    BOOST_CHECK_EQUAL(shmLink->supportsChannel(9), false);

    std::shared_ptr<NodeFeatures> vLink = NodeFeatures::create(createInfo(WirelessModels::node_vLink));
    BOOST_CHECK_EQUAL(vLink->supportsChannel(1), true);
    BOOST_CHECK_EQUAL(vLink->supportsChannel(4), true);
    BOOST_CHECK_EQUAL(vLink->supportsChannel(5), true);
    BOOST_CHECK_EQUAL(vLink->supportsChannel(8), true);
    BOOST_CHECK_EQUAL(vLink->supportsChannel(10), false);
}

BOOST_AUTO_TEST_CASE(NodeFeatures_minTimeBetweenBursts)
{
    NodeInfo info(Version(1, 0), WirelessModels::node_vLink, WirelessTypes::region_usa);

    std::shared_ptr<NodeFeatures> features = NodeFeatures::create(info);

    ChannelMask chs4(15);
    ChannelMask chs2(3);
    WirelessTypes::DerivedChannelMasks derivedMasks;

    WirelessTypes::DataFormat format_uint16 = WirelessTypes::dataFormat_raw_uint16;
    WirelessTypes::DataFormat format_float = WirelessTypes::dataFormat_cal_float;
    WirelessTypes::DataMode mode_raw = WirelessTypes::dataMode_raw;
    WirelessTypes::DataMode mode_derived = WirelessTypes::dataMode_derived;
    WirelessTypes::CommProtocol lxrs = WirelessTypes::commProtocol_lxrs;

    BOOST_CHECK(features->minTimeBetweenBursts(mode_raw, format_uint16, chs4, derivedMasks, SampleRate::Hertz(256), 100, lxrs) == TimeSpan::Seconds(5));
    BOOST_CHECK(features->minTimeBetweenBursts(mode_raw, format_uint16, chs4, derivedMasks, SampleRate::Hertz(32), 100, lxrs) == TimeSpan::Seconds(8));
    BOOST_CHECK(features->minTimeBetweenBursts(mode_raw, format_uint16, chs4, derivedMasks, SampleRate::Hertz(32), 200, lxrs) == TimeSpan::Seconds(11));
    BOOST_CHECK(features->minTimeBetweenBursts(mode_raw, format_float, chs4, derivedMasks, SampleRate::Hertz(32), 200, lxrs) == TimeSpan::Seconds(12));
    BOOST_CHECK(features->minTimeBetweenBursts(mode_raw, format_uint16, chs4, derivedMasks, SampleRate::Hertz(2048), 100, lxrs) == TimeSpan::Seconds(5));
    BOOST_CHECK(features->minTimeBetweenBursts(mode_raw, format_uint16, chs2, derivedMasks, SampleRate::Hertz(64), 100, lxrs) == TimeSpan::Seconds(6));

    derivedMasks.emplace(WirelessTypes::derivedCategory_rms, ChannelMask(255));
    derivedMasks.emplace(WirelessTypes::derivedCategory_peakToPeak, ChannelMask(255));
    derivedMasks.emplace(WirelessTypes::derivedCategory_velocity, ChannelMask(255));
    derivedMasks.emplace(WirelessTypes::derivedCategory_crestFactor, ChannelMask(255));
    BOOST_CHECK(features->minTimeBetweenBursts(mode_derived, format_uint16, chs4, derivedMasks, SampleRate::Hertz(32), 100, lxrs) == TimeSpan::Seconds(8));
}

BOOST_AUTO_TEST_CASE(NodeFeatures_maxSampleRate_vLink)
{
    NodeInfo info(Version(1, 0), WirelessModels::node_vLink, WirelessTypes::region_usa);

    std::shared_ptr<NodeFeatures> features = NodeFeatures::create(info);

    ChannelMask chs(1);
    WirelessTypes::DataCollectionMethod method = WirelessTypes::collectionMethod_transmitOnly;
    WirelessTypes::DataMode mode = WirelessTypes::dataMode_raw;

    BOOST_CHECK_EQUAL(features->maxSampleRate(WirelessTypes::samplingMode_syncBurst, chs, method, mode), WirelessTypes::sampleRate_10kHz);

    chs.enable(2, true);

    BOOST_CHECK_EQUAL(features->maxSampleRate(WirelessTypes::samplingMode_syncBurst, chs, method, mode), WirelessTypes::sampleRate_9kHz);

    chs.enable(7, true);
    chs.enable(8, true);

    BOOST_CHECK_EQUAL(features->maxSampleRate(WirelessTypes::samplingMode_syncBurst, chs, method, mode), WirelessTypes::sampleRate_6kHz);
}

BOOST_AUTO_TEST_CASE(NodeFeatures_maxSampleRate_gLink2)
{
    NodeInfo info(Version(1, 0), WirelessModels::node_gLinkII_10g_in, WirelessTypes::region_usa);

    std::shared_ptr<NodeFeatures> features = NodeFeatures::create(info);

    ChannelMask chs(1);
    WirelessTypes::DataCollectionMethod method = WirelessTypes::collectionMethod_transmitOnly;
    WirelessTypes::DataMode mode = WirelessTypes::dataMode_raw;

    BOOST_CHECK_EQUAL(features->maxSampleRate(WirelessTypes::samplingMode_syncBurst, chs, method, mode), WirelessTypes::sampleRate_10kHz);

    chs.enable(2, true);

    BOOST_CHECK_EQUAL(features->maxSampleRate(WirelessTypes::samplingMode_syncBurst, chs, method, mode), WirelessTypes::sampleRate_10kHz);

    chs.enable(7, true);
    chs.enable(8, true);

    BOOST_CHECK_EQUAL(features->maxSampleRate(WirelessTypes::samplingMode_syncBurst, chs, method, mode), WirelessTypes::sampleRate_10kHz);
}

BOOST_AUTO_TEST_CASE(NodeFeatures_maxSampleRate_gLink)
{
    NodeInfo info(Version(1, 0), WirelessModels::node_gLink_10g, WirelessTypes::region_usa);

    std::shared_ptr<NodeFeatures> features = NodeFeatures::create(info);

    ChannelMask chs(1);
    WirelessTypes::DataCollectionMethod method = WirelessTypes::collectionMethod_transmitOnly;
    WirelessTypes::DataMode mode = WirelessTypes::dataMode_raw;

    BOOST_CHECK_EQUAL(features->maxSampleRate(WirelessTypes::samplingMode_syncBurst, chs, method, mode), WirelessTypes::sampleRate_4096Hz);

    chs.enable(2, true);

    BOOST_CHECK_EQUAL(features->maxSampleRate(WirelessTypes::samplingMode_syncBurst, chs, method, mode), WirelessTypes::sampleRate_2048Hz);

    chs.enable(7, true);
    chs.enable(8, true);

    BOOST_CHECK_EQUAL(features->maxSampleRate(WirelessTypes::samplingMode_syncBurst, chs, method, mode), WirelessTypes::sampleRate_2048Hz);

    BOOST_CHECK_EQUAL(features->maxSampleRate(WirelessTypes::samplingMode_nonSync, chs, method, mode), WirelessTypes::sampleRate_512Hz);
}

BOOST_AUTO_TEST_CASE(NodeFeatures_normalizeNumSweeps)
{
    NodeInfo info(Version(1, 0), WirelessModels::node_gLink_10g, WirelessTypes::region_usa);
    std::shared_ptr<NodeFeatures> features = NodeFeatures::create(info);

    uint32 sweeps = 1;
    sweeps = features->normalizeNumSweeps(sweeps);
    BOOST_CHECK_EQUAL(sweeps, 100);

    sweeps = 99;
    sweeps = features->normalizeNumSweeps(sweeps);
    BOOST_CHECK_EQUAL(sweeps, 100);

    sweeps = 200;
    sweeps = features->normalizeNumSweeps(sweeps);
    BOOST_CHECK_EQUAL(sweeps, 200);

    sweeps = 97845;
    sweeps = features->normalizeNumSweeps(sweeps);
    BOOST_CHECK_EQUAL(sweeps, 97900);
}

BOOST_AUTO_TEST_CASE(NodeFeatures_normalizeTimeBetweenBursts)
{
    NodeInfo info(Version(1, 0), WirelessModels::node_gLink_10g, WirelessTypes::region_usa);
    std::shared_ptr<NodeFeatures> features = NodeFeatures::create(info);

    //standard
    TimeSpan time1 = TimeSpan::Seconds(12345);
    time1 = features->normalizeTimeBetweenBursts(time1);
    BOOST_CHECK(time1 == TimeSpan::Seconds(12345));

    //min time
    TimeSpan time2 = TimeSpan::MilliSeconds(20);
    time2 = features->normalizeTimeBetweenBursts(time2);
    BOOST_CHECK(time2 == TimeSpan::Seconds(1));

    //max time
    TimeSpan time3 = TimeSpan::Hours(30);
    time3 = features->normalizeTimeBetweenBursts(time3);
    BOOST_CHECK(time3 == TimeSpan::Hours(24));

    //above max that can be stored as seconds, rounds up to minutes
    TimeSpan time4 = TimeSpan::Seconds(40000);
    time4 = features->normalizeTimeBetweenBursts(time4);
    BOOST_CHECK(time4 == TimeSpan::Minutes(667));
}

BOOST_AUTO_TEST_CASE(NodeFeatures_normalizeEventDuration)
{
    NodeInfo info1(Version(8, 0), WirelessModels::node_wirelessImpactSensor, WirelessTypes::region_usa);
    std::shared_ptr<NodeFeatures> features1 = NodeFeatures::create(info1);

    NodeInfo info2(Version(10, 0), WirelessModels::node_wirelessImpactSensor, WirelessTypes::region_usa);
    std::shared_ptr<NodeFeatures> features2 = NodeFeatures::create(info2);

    uint32 f1 = 1000;
    uint32 f2 = 50;
    uint32 f3 = 247058;
    uint32 f4 = 72435123;

    BOOST_CHECK_EQUAL(features1->normalizeEventDuration(f1), 1000);
    BOOST_CHECK_EQUAL(features2->normalizeEventDuration(f1), 1000);

    BOOST_CHECK_EQUAL(features1->normalizeEventDuration(f2), 1000);
    BOOST_CHECK_EQUAL(features2->normalizeEventDuration(f2), 50);

    BOOST_CHECK_EQUAL(features1->normalizeEventDuration(f3), 248000);
    BOOST_CHECK_EQUAL(features2->normalizeEventDuration(f3), 247060);

    BOOST_CHECK_EQUAL(features1->normalizeEventDuration(f4), 65535000);
    BOOST_CHECK_EQUAL(features2->normalizeEventDuration(f4), 655350);
}

BOOST_AUTO_TEST_CASE(NodeFeatures_transmitPowers_usa_brazil)
{
    {
        NodeInfo info(Version(1, 0), WirelessModels::node_gLink_10g, WirelessTypes::region_usa);
        std::shared_ptr<NodeFeatures> features = NodeFeatures::create(info);

        WirelessTypes::TransmitPowers powers = features->transmitPowers(WirelessTypes::commProtocol_lxrs);

        BOOST_CHECK_EQUAL(powers.size(), 4);
        BOOST_CHECK_EQUAL(powers.at(0), WirelessTypes::power_16dBm);
        BOOST_CHECK_EQUAL(powers.at(1), WirelessTypes::power_10dBm);
        BOOST_CHECK_EQUAL(powers.at(2), WirelessTypes::power_5dBm);
        BOOST_CHECK_EQUAL(powers.at(3), WirelessTypes::power_0dBm);
    }

    {
        NodeInfo info(Version(10, 0), WirelessModels::node_tcLink200, WirelessTypes::region_usa);
        std::shared_ptr<NodeFeatures> features = NodeFeatures::create(info);

        WirelessTypes::TransmitPowers powers = features->transmitPowers(WirelessTypes::commProtocol_lxrsPlus);

        BOOST_CHECK_EQUAL(powers.size(), 4);
        BOOST_CHECK_EQUAL(powers.at(0), WirelessTypes::power_16dBm);
        BOOST_CHECK_EQUAL(powers.at(1), WirelessTypes::power_10dBm);
        BOOST_CHECK_EQUAL(powers.at(2), WirelessTypes::power_5dBm);
        BOOST_CHECK_EQUAL(powers.at(3), WirelessTypes::power_0dBm);
    }

    {
        NodeInfo info(Version(10, 0), WirelessModels::node_tcLink200, WirelessTypes::region_usa);
        std::shared_ptr<NodeFeatures> features = NodeFeatures::create(info);

        WirelessTypes::TransmitPowers powers = features->transmitPowers(WirelessTypes::commProtocol_lxrs);

        BOOST_CHECK_EQUAL(powers.size(), 5);
        BOOST_CHECK_EQUAL(powers.at(0), WirelessTypes::power_20dBm);
        BOOST_CHECK_EQUAL(powers.at(1), WirelessTypes::power_16dBm);
        BOOST_CHECK_EQUAL(powers.at(2), WirelessTypes::power_10dBm);
        BOOST_CHECK_EQUAL(powers.at(3), WirelessTypes::power_5dBm);
        BOOST_CHECK_EQUAL(powers.at(4), WirelessTypes::power_0dBm);
    }

    {
        NodeInfo info(Version(1, 0), WirelessModels::node_gLink_10g, WirelessTypes::region_brazil);
        std::shared_ptr<NodeFeatures> features = NodeFeatures::create(info);

        WirelessTypes::TransmitPowers powers = features->transmitPowers(WirelessTypes::commProtocol_lxrs);

        BOOST_CHECK_EQUAL(powers.size(), 4);
        BOOST_CHECK_EQUAL(powers.at(0), WirelessTypes::power_16dBm);
        BOOST_CHECK_EQUAL(powers.at(1), WirelessTypes::power_10dBm);
        BOOST_CHECK_EQUAL(powers.at(2), WirelessTypes::power_5dBm);
        BOOST_CHECK_EQUAL(powers.at(3), WirelessTypes::power_0dBm);
    }
}

BOOST_AUTO_TEST_CASE(NodeFeatures_transmitPowers_europe_other)
{
    {
        NodeInfo info(Version(1, 0), WirelessModels::node_gLink_10g, WirelessTypes::region_europeanUnion);
        std::shared_ptr<NodeFeatures> features = NodeFeatures::create(info);

        WirelessTypes::TransmitPowers powers = features->transmitPowers(WirelessTypes::commProtocol_lxrs);

        BOOST_CHECK_EQUAL(powers.size(), 3);
        BOOST_CHECK_EQUAL(powers.at(0), WirelessTypes::power_10dBm);
        BOOST_CHECK_EQUAL(powers.at(1), WirelessTypes::power_5dBm);
        BOOST_CHECK_EQUAL(powers.at(2), WirelessTypes::power_0dBm);
    }

    {
        NodeInfo info(Version(10, 0), WirelessModels::node_rtdLink200, WirelessTypes::region_europeanUnion);
        std::shared_ptr<NodeFeatures> features = NodeFeatures::create(info);

        WirelessTypes::TransmitPowers powers = features->transmitPowers(WirelessTypes::commProtocol_lxrs);

        BOOST_CHECK_EQUAL(powers.size(), 4);
        BOOST_CHECK_EQUAL(powers.at(0), WirelessTypes::power_11dBm);
        BOOST_CHECK_EQUAL(powers.at(1), WirelessTypes::power_10dBm);
        BOOST_CHECK_EQUAL(powers.at(2), WirelessTypes::power_5dBm);
        BOOST_CHECK_EQUAL(powers.at(3), WirelessTypes::power_0dBm);
    }

    {
        NodeInfo info(Version(1, 0), WirelessModels::node_gLink_10g, WirelessTypes::region_other);
        std::shared_ptr<NodeFeatures> features = NodeFeatures::create(info);

        WirelessTypes::TransmitPowers powers = features->transmitPowers(WirelessTypes::commProtocol_lxrs);

        BOOST_CHECK_EQUAL(powers.size(), 3);
        BOOST_CHECK_EQUAL(powers.at(0), WirelessTypes::power_10dBm);
        BOOST_CHECK_EQUAL(powers.at(1), WirelessTypes::power_5dBm);
        BOOST_CHECK_EQUAL(powers.at(2), WirelessTypes::power_0dBm);
    }
}

BOOST_AUTO_TEST_CASE(NodeFeatures_transmitPowers_japan)
{
    {
        NodeInfo info(Version(1, 0), WirelessModels::node_gLink_10g, WirelessTypes::region_japan);
        std::shared_ptr<NodeFeatures> features = NodeFeatures::create(info);

        WirelessTypes::TransmitPowers powers = features->transmitPowers(WirelessTypes::commProtocol_lxrs);

        BOOST_CHECK_EQUAL(powers.size(), 2);
        BOOST_CHECK_EQUAL(powers.at(0), WirelessTypes::power_10dBm);
        BOOST_CHECK_EQUAL(powers.at(1), WirelessTypes::power_5dBm);
    }

    {
        NodeInfo info(Version(10, 0), WirelessModels::node_gLink_200_8g, WirelessTypes::region_japan);
        std::shared_ptr<NodeFeatures> features = NodeFeatures::create(info);

        WirelessTypes::TransmitPowers powers = features->transmitPowers(WirelessTypes::commProtocol_lxrs);

        BOOST_CHECK_EQUAL(powers.size(), 3);
        BOOST_CHECK_EQUAL(powers.at(0), WirelessTypes::power_16dBm);
        BOOST_CHECK_EQUAL(powers.at(1), WirelessTypes::power_10dBm);
        BOOST_CHECK_EQUAL(powers.at(2), WirelessTypes::power_5dBm);
    }

    {
        NodeInfo info(Version(10, 0), WirelessModels::node_gLink_200_8g, WirelessTypes::region_japan);
        std::shared_ptr<NodeFeatures> features = NodeFeatures::create(info);

        WirelessTypes::TransmitPowers powers = features->transmitPowers(WirelessTypes::commProtocol_lxrsPlus);

        BOOST_CHECK_EQUAL(powers.size(), 3);
        BOOST_CHECK_EQUAL(powers.at(0), WirelessTypes::power_12dBm);
        BOOST_CHECK_EQUAL(powers.at(1), WirelessTypes::power_5dBm);
        BOOST_CHECK_EQUAL(powers.at(2), WirelessTypes::power_1dBm);
    }

    {
        NodeInfo info(Version(10, 0), WirelessModels::node_sgLink200, WirelessTypes::region_japan);
        std::shared_ptr<NodeFeatures> features = NodeFeatures::create(info);

        WirelessTypes::TransmitPowers powers = features->transmitPowers(WirelessTypes::commProtocol_lxrs);

        BOOST_CHECK_EQUAL(powers.size(), 3);
        BOOST_CHECK_EQUAL(powers.at(0), WirelessTypes::power_15dBm);
        BOOST_CHECK_EQUAL(powers.at(1), WirelessTypes::power_10dBm);
        BOOST_CHECK_EQUAL(powers.at(2), WirelessTypes::power_5dBm);
    }

    {
        NodeInfo info(Version(10, 0), WirelessModels::node_tcLink200_oem, WirelessTypes::region_japan);
        std::shared_ptr<NodeFeatures> features = NodeFeatures::create(info);

        WirelessTypes::TransmitPowers powers = features->transmitPowers(WirelessTypes::commProtocol_lxrsPlus);

        BOOST_CHECK_EQUAL(powers.size(), 3);
        BOOST_CHECK_EQUAL(powers.at(0), WirelessTypes::power_11dBm);
        BOOST_CHECK_EQUAL(powers.at(1), WirelessTypes::power_5dBm);
        BOOST_CHECK_EQUAL(powers.at(2), WirelessTypes::power_0dBm);
    }

    {
        NodeInfo info(Version(10, 0), WirelessModels::node_gLink_200_40g_oem, WirelessTypes::region_japan);
        std::shared_ptr<NodeFeatures> features = NodeFeatures::create(info);

        WirelessTypes::TransmitPowers powers = features->transmitPowers(WirelessTypes::commProtocol_lxrsPlus);

        BOOST_CHECK_EQUAL(powers.size(), 4);
        BOOST_CHECK_EQUAL(powers.at(0), WirelessTypes::power_11dBm);
        BOOST_CHECK_EQUAL(powers.at(1), WirelessTypes::power_5dBm);
        BOOST_CHECK_EQUAL(powers.at(2), WirelessTypes::power_1dBm);
        BOOST_CHECK_EQUAL(powers.at(3), WirelessTypes::power_0dBm);
    }
}

BOOST_AUTO_TEST_CASE(NodeFeatures_filterSettlingTime_a)
{
    NodeInfo info(Version(1, 0), WirelessModels::node_tcLink_6ch, WirelessTypes::region_usa);

    std::unique_ptr<NodeFeatures> features = NodeFeatures::create(info);

    BOOST_CHECK_EQUAL(features->maxFilterSettlingTime(SampleRate::Hertz(32)), WirelessTypes::settling_4ms);
    BOOST_CHECK_EQUAL(features->maxFilterSettlingTime(SampleRate::Hertz(8)), WirelessTypes::settling_4ms);
    BOOST_CHECK_EQUAL(features->maxFilterSettlingTime(SampleRate::Hertz(4)), WirelessTypes::settling_8ms);
    BOOST_CHECK_EQUAL(features->maxFilterSettlingTime(SampleRate::Hertz(2)), WirelessTypes::settling_16ms);
    BOOST_CHECK_EQUAL(features->maxFilterSettlingTime(SampleRate::Hertz(1)), WirelessTypes::settling_60ms);
    BOOST_CHECK_EQUAL(features->maxFilterSettlingTime(SampleRate::Seconds(10)), WirelessTypes::settling_200ms);

    WirelessTypes::SamplingMode mode = WirelessTypes::samplingMode_nonSync;
    WirelessTypes::DataCollectionMethod method = WirelessTypes::collectionMethod_transmitOnly;
    WirelessTypes::DataMode dataMode = WirelessTypes::dataMode_raw;
    BOOST_CHECK_EQUAL(features->maxSampleRateForSettlingTime(WirelessTypes::settling_4ms, mode, method, dataMode), WirelessTypes::sampleRate_8Hz);
    BOOST_CHECK_EQUAL(features->maxSampleRateForSettlingTime(WirelessTypes::settling_8ms, mode, method, dataMode), WirelessTypes::sampleRate_4Hz);
    BOOST_CHECK_EQUAL(features->maxSampleRateForSettlingTime(WirelessTypes::settling_16ms, mode, method, dataMode), WirelessTypes::sampleRate_2Hz);
    BOOST_CHECK_EQUAL(features->maxSampleRateForSettlingTime(WirelessTypes::settling_40ms, mode, method, dataMode), WirelessTypes::sampleRate_1Hz);
    BOOST_CHECK_EQUAL(features->maxSampleRateForSettlingTime(WirelessTypes::settling_60ms, mode, method, dataMode), WirelessTypes::sampleRate_1Hz);
    BOOST_CHECK_EQUAL(features->maxSampleRateForSettlingTime(WirelessTypes::settling_101ms_90db, mode, method, dataMode), WirelessTypes::sampleRate_2Sec);
    BOOST_CHECK_EQUAL(features->maxSampleRateForSettlingTime(WirelessTypes::settling_120ms_65db, mode, method, dataMode), WirelessTypes::sampleRate_2Sec);
}

BOOST_AUTO_TEST_CASE(NodeFeatures_filterSettlingTime_b)
{
    NodeInfo info(Version(1, 0), WirelessModels::node_tcLink_1ch, WirelessTypes::region_usa);

    std::unique_ptr<NodeFeatures> features = NodeFeatures::create(info);

    BOOST_CHECK_EQUAL(features->maxFilterSettlingTime(SampleRate::Hertz(128)), WirelessTypes::settling_4ms);
    BOOST_CHECK_EQUAL(features->maxFilterSettlingTime(SampleRate::Hertz(64)), WirelessTypes::settling_4ms);
    BOOST_CHECK_EQUAL(features->maxFilterSettlingTime(SampleRate::Hertz(32)), WirelessTypes::settling_8ms);
    BOOST_CHECK_EQUAL(features->maxFilterSettlingTime(SampleRate::Hertz(16)), WirelessTypes::settling_16ms);
    BOOST_CHECK_EQUAL(features->maxFilterSettlingTime(SampleRate::Hertz(8)), WirelessTypes::settling_32ms);
    BOOST_CHECK_EQUAL(features->maxFilterSettlingTime(SampleRate::Hertz(2)), WirelessTypes::settling_200ms);

    WirelessTypes::SamplingMode mode = WirelessTypes::samplingMode_nonSync;
    WirelessTypes::DataCollectionMethod method = WirelessTypes::collectionMethod_transmitOnly;
    WirelessTypes::DataMode dataMode = WirelessTypes::dataMode_raw;
    BOOST_CHECK_EQUAL(features->maxSampleRateForSettlingTime(WirelessTypes::settling_4ms, mode, method, dataMode), WirelessTypes::sampleRate_64Hz);
    BOOST_CHECK_EQUAL(features->maxSampleRateForSettlingTime(WirelessTypes::settling_8ms, mode, method, dataMode), WirelessTypes::sampleRate_32Hz);
    BOOST_CHECK_EQUAL(features->maxSampleRateForSettlingTime(WirelessTypes::settling_16ms, mode, method, dataMode), WirelessTypes::sampleRate_16Hz);
    BOOST_CHECK_EQUAL(features->maxSampleRateForSettlingTime(WirelessTypes::settling_32ms, mode, method, dataMode), WirelessTypes::sampleRate_8Hz);
    BOOST_CHECK_EQUAL(features->maxSampleRateForSettlingTime(WirelessTypes::settling_60ms, mode, method, dataMode), WirelessTypes::sampleRate_4Hz);
    BOOST_CHECK_EQUAL(features->maxSampleRateForSettlingTime(WirelessTypes::settling_101ms_90db, mode, method, dataMode), WirelessTypes::sampleRate_4Hz);
    BOOST_CHECK_EQUAL(features->maxSampleRateForSettlingTime(WirelessTypes::settling_120ms_65db, mode, method, dataMode), WirelessTypes::sampleRate_4Hz);
}

BOOST_AUTO_TEST_CASE(NodeFeatures_normalizeSensorDelay_v1)
{
    //Tests normalizing sensor delay (v1 only supports milliseconds)
    NodeInfo info(Version(1, 0), WirelessModels::node_sgLink, WirelessTypes::region_usa);
    std::unique_ptr<NodeFeatures> features = NodeFeatures::create(info);

    BOOST_CHECK_EQUAL(features->minSensorDelay(), 1 * 1000);
    BOOST_CHECK_EQUAL(features->maxSensorDelay(), 500 * 1000);
    BOOST_CHECK_EQUAL(features->normalizeSensorDelay(0), 0);
    BOOST_CHECK_EQUAL(features->normalizeSensorDelay(1 * 1000), 1 * 1000);      //minimum (besides off)
    BOOST_CHECK_EQUAL(features->normalizeSensorDelay(500 * 1000), 500 * 1000);  //maximum
    BOOST_CHECK_EQUAL(features->normalizeSensorDelay(1), 1 * 1000);             //out of range min
    BOOST_CHECK_EQUAL(features->normalizeSensorDelay(1000 * 1000), 500 * 1000); //out of range max
    BOOST_CHECK_EQUAL(features->normalizeSensorDelay(481541), 482 * 1000);
}

BOOST_AUTO_TEST_CASE(NodeFeatures_normalizeSensorDelay_v2)
{
    //Tests normalizing sensor delay (v2 only supports microseconds)
    NodeInfo info(Version(1, 0), WirelessModels::node_shmLink, WirelessTypes::region_usa);
    std::unique_ptr<NodeFeatures> features = NodeFeatures::create(info);

    BOOST_CHECK_EQUAL(features->minSensorDelay(), 1);
    BOOST_CHECK_EQUAL(features->maxSensorDelay(), 65535);
    BOOST_CHECK_EQUAL(features->normalizeSensorDelay(0), 0);
    BOOST_CHECK_EQUAL(features->normalizeSensorDelay(1), 1);            //minimum (besides off)
    BOOST_CHECK_EQUAL(features->normalizeSensorDelay(65535), 65535);    //maximum
    BOOST_CHECK_EQUAL(features->normalizeSensorDelay(481), 481);
}

BOOST_AUTO_TEST_CASE(NodeFeatures_normalizeSensorDelay_v3)
{
    //Tests normalizing sensor delay (v3 supports seconds and milliseconds)
    NodeInfo info(Version(1, 0), WirelessModels::node_vLink, WirelessTypes::region_usa);
    std::unique_ptr<NodeFeatures> features = NodeFeatures::create(info);

    BOOST_CHECK_EQUAL(features->minSensorDelay(), 1 * 1000);
    BOOST_CHECK_EQUAL(features->maxSensorDelay(), 600000000);
    BOOST_CHECK_EQUAL(features->normalizeSensorDelay(0), 0);
    BOOST_CHECK_EQUAL(features->normalizeSensorDelay(1 * 1000), 1 * 1000);      //minimum (besides off)
    BOOST_CHECK_EQUAL(features->normalizeSensorDelay(600000000), 600000000);    //maximum
    BOOST_CHECK_EQUAL(features->normalizeSensorDelay(3), 1 * 1000);             //out of range min
    BOOST_CHECK_EQUAL(features->normalizeSensorDelay(750004103), 600000000);    //out of range max

    BOOST_CHECK_EQUAL(features->normalizeSensorDelay(500 * 1000), 500 * 1000);  //can go up to 500ms before switching to seconds
    BOOST_CHECK_EQUAL(features->normalizeSensorDelay(501 * 1000), 1000000);     //can go up to 500ms before switching to seconds
    BOOST_CHECK_EQUAL(features->normalizeSensorDelay(439748), 440 * 1000);

    BOOST_CHECK_EQUAL(features->normalizeSensorDelay(5000001), 6000000);        //seconds (PWUWU)
    BOOST_CHECK_EQUAL(features->normalizeSensorDelay(700000000), 600000000);     //max of 10 minutes
}

BOOST_AUTO_TEST_CASE(NodeFeatures_normalizeSensorDelay_v4)
{
    //Tests normalizing sensor delay (v3 supports seconds and milliseconds)
    NodeInfo info(Version(11, 0), WirelessModels::node_vLink200, WirelessTypes::region_usa);
    std::unique_ptr<NodeFeatures> features = NodeFeatures::create(info);

    BOOST_CHECK_EQUAL(features->minSensorDelay(), 1);
    BOOST_CHECK_EQUAL(features->maxSensorDelay(), 600000000);
    BOOST_CHECK_EQUAL(features->normalizeSensorDelay(0), 0);
    BOOST_CHECK_EQUAL(features->normalizeSensorDelay(1), 1);                    //minimum (besides off)
    BOOST_CHECK_EQUAL(features->normalizeSensorDelay(600000000), 600000000);    //maximum
    BOOST_CHECK_EQUAL(features->normalizeSensorDelay(750004103), 600000000);    //out of range max


    BOOST_CHECK_EQUAL(features->normalizeSensorDelay(16383), 16383);            //can go up to 16383 microseconds before switching to milliseconds
    BOOST_CHECK_EQUAL(features->normalizeSensorDelay(17383), 18000);            //can go up to 16383 microseconds before switching to milliseconds
    BOOST_CHECK_EQUAL(features->normalizeSensorDelay(16383000), 16383000);      //can go up to 16383000 milliseconds before switching to seconds
    BOOST_CHECK_EQUAL(features->normalizeSensorDelay(16383415), 17000000);      //can go up to 16383000 milliseconds before switching to seconds
    BOOST_CHECK_EQUAL(features->normalizeSensorDelay(439748), 440 * 1000);
}

BOOST_AUTO_TEST_SUITE_END()