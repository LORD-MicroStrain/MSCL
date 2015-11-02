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
#include "mscl/MicroStrain/Wireless/Features/NodeFeatures.h"
#include "mscl/Exceptions.h"
#include "mscl/MicroStrain/Wireless/ChannelMask.h"

#include <boost/test/unit_test.hpp>

using namespace mscl;

BOOST_AUTO_TEST_SUITE(NodeFeatures_Test)

NodeInfo createInfo(WirelessModels::NodeModel node)
{
	return NodeInfo(Version(9, 9), node, 0, WirelessTypes::region_usa);
}

BOOST_AUTO_TEST_CASE(NodeFeatures_create)
{
	std::shared_ptr<NodeFeatures> dvrtLink = NodeFeatures::create(createInfo(WirelessModels::node_dvrtLink));
	BOOST_CHECK_EQUAL(dvrtLink->supportsHardwareGain(), false);

	std::shared_ptr<NodeFeatures> glink10g = NodeFeatures::create(createInfo(WirelessModels::node_gLink_10g));
	BOOST_CHECK_EQUAL(glink10g->supportsHardwareGain(), false);

	std::shared_ptr<NodeFeatures> glink2 = NodeFeatures::create(createInfo(WirelessModels::node_gLinkII_2g_ex));
	BOOST_CHECK_EQUAL(glink2->supportsHardwareGain(), false);

	std::shared_ptr<NodeFeatures> glink2in = NodeFeatures::create(createInfo(WirelessModels::node_gLinkII_2g_in));
	BOOST_CHECK_EQUAL(glink2in->supportsHardwareGain(), false);

	std::shared_ptr<NodeFeatures> sgLink = NodeFeatures::create(createInfo(WirelessModels::node_sgLink));
	BOOST_CHECK_EQUAL(sgLink->supportsHardwareGain(), true);

	std::shared_ptr<NodeFeatures> sgLink8ch = NodeFeatures::create(createInfo(WirelessModels::node_sgLink_8ch));
	BOOST_CHECK_EQUAL(sgLink8ch->supportsHardwareGain(), true);

	std::shared_ptr<NodeFeatures> sgLinkoem = NodeFeatures::create(createInfo(WirelessModels::node_sgLink_oem));
	BOOST_CHECK_EQUAL(sgLinkoem->supportsHardwareGain(), true);

	std::shared_ptr<NodeFeatures> sgLinkHerm = NodeFeatures::create(createInfo(WirelessModels::node_sgLink_herm));
	BOOST_CHECK_EQUAL(sgLinkHerm->supportsHardwareGain(), true);

	std::shared_ptr<NodeFeatures> sgLinkOemNoXr = NodeFeatures::create(createInfo(WirelessModels::node_sgLink_oem_S));
	BOOST_CHECK_EQUAL(sgLinkOemNoXr->supportsHardwareGain(), true);

	std::shared_ptr<NodeFeatures> sgLinkrgd = NodeFeatures::create(createInfo(WirelessModels::node_sgLink_rgd));
	BOOST_CHECK_EQUAL(sgLinkrgd->supportsHardwareGain(), true);

	std::shared_ptr<NodeFeatures> shmLink = NodeFeatures::create(createInfo(WirelessModels::node_shmLink));
	BOOST_CHECK_EQUAL(shmLink->supportsHardwareGain(), true);

	std::shared_ptr<NodeFeatures> vLink = NodeFeatures::create(createInfo(WirelessModels::node_vLink));
	BOOST_CHECK_EQUAL(vLink->supportsHardwareGain(), true);

	std::shared_ptr<NodeFeatures> tcLink6 = NodeFeatures::create(createInfo(WirelessModels::node_tcLink_6ch));
	BOOST_CHECK_EQUAL(tcLink6->supportsHardwareGain(), true);

	std::shared_ptr<NodeFeatures> tcLink3 = NodeFeatures::create(createInfo(WirelessModels::node_tcLink_3ch));
	BOOST_CHECK_EQUAL(tcLink3->supportsHardwareGain(), true);

	std::shared_ptr<NodeFeatures> tcLink1 = NodeFeatures::create(createInfo(WirelessModels::node_tcLink_1ch));
	BOOST_CHECK_EQUAL(tcLink1->supportsHardwareGain(), true);

	std::shared_ptr<NodeFeatures> rtd = NodeFeatures::create(createInfo(WirelessModels::node_rtdLink));
	BOOST_CHECK_EQUAL(rtd->supportsHardwareGain(), true);

	std::shared_ptr<NodeFeatures> iepe = NodeFeatures::create(createInfo(WirelessModels::node_iepeLink));
	BOOST_CHECK_EQUAL(iepe->supportsHardwareGain(), false);

	std::shared_ptr<NodeFeatures> envPro = NodeFeatures::create(createInfo(WirelessModels::node_envLink_pro));
	BOOST_CHECK_EQUAL(envPro->supportsHardwareGain(), true);

	std::shared_ptr<NodeFeatures> envMini = NodeFeatures::create(createInfo(WirelessModels::node_envLink_mini));
	BOOST_CHECK_EQUAL(envMini->supportsHardwareGain(), true);
}

BOOST_AUTO_TEST_CASE(NodeFeatures_create_unknownModel)
{
	BOOST_CHECK_THROW(NodeFeatures::create(createInfo(static_cast<WirelessModels::NodeModel>(0))), Error_NotSupported);
}

BOOST_AUTO_TEST_CASE(NodeFeatures_supportsGaugeFactor)
{
	std::shared_ptr<NodeFeatures> sglink = NodeFeatures::create(createInfo(WirelessModels::node_sgLink));
	BOOST_CHECK_EQUAL(sglink->supportsGaugeFactor(), false);

	std::shared_ptr<NodeFeatures> shmLink2 = NodeFeatures::create(createInfo(WirelessModels::node_shmLink2));
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

	std::shared_ptr<NodeFeatures> sgLink8ch = NodeFeatures::create(createInfo(WirelessModels::node_sgLink_8ch));
	BOOST_CHECK_EQUAL(sgLink8ch->supportsChannel(1), true);
	BOOST_CHECK_EQUAL(sgLink8ch->supportsChannel(4), true);
	BOOST_CHECK_EQUAL(sgLink8ch->supportsChannel(5), true);
	BOOST_CHECK_EQUAL(sgLink8ch->supportsChannel(8), true);
	BOOST_CHECK_EQUAL(sgLink8ch->supportsChannel(10), false);

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
	NodeInfo info(Version(1, 0), WirelessModels::node_vLink, 0, WirelessTypes::region_usa);

	std::shared_ptr<NodeFeatures> features = NodeFeatures::create(info);

	ChannelMask chs4(15);
	ChannelMask chs2(3);

	BOOST_CHECK(features->minTimeBetweenBursts(WirelessTypes::dataFormat_2byte_uint, chs4, SampleRate::Hertz(256), 100) == TimeSpan::Seconds(5));
	BOOST_CHECK(features->minTimeBetweenBursts(WirelessTypes::dataFormat_2byte_uint, chs4, SampleRate::Hertz(32), 100) == TimeSpan::Seconds(8));
	BOOST_CHECK(features->minTimeBetweenBursts(WirelessTypes::dataFormat_2byte_uint, chs4, SampleRate::Hertz(32), 200) == TimeSpan::Seconds(11));
	BOOST_CHECK(features->minTimeBetweenBursts(WirelessTypes::dataFormat_4byte_float, chs4, SampleRate::Hertz(32), 200) == TimeSpan::Seconds(12));
	BOOST_CHECK(features->minTimeBetweenBursts(WirelessTypes::dataFormat_2byte_uint, chs4, SampleRate::Hertz(2048), 100) == TimeSpan::Seconds(5));
	BOOST_CHECK(features->minTimeBetweenBursts(WirelessTypes::dataFormat_2byte_uint, chs2, SampleRate::Hertz(64), 100) == TimeSpan::Seconds(6));
}

BOOST_AUTO_TEST_CASE(NodeFeatures_maxSampleRate_vLink)
{
	NodeInfo info(Version(1, 0), WirelessModels::node_vLink, 0, WirelessTypes::region_usa);

	std::shared_ptr<NodeFeatures> features = NodeFeatures::create(info);

	ChannelMask chs(1);

	BOOST_CHECK_EQUAL(features->maxSampleRate(WirelessTypes::samplingMode_syncBurst, chs), WirelessTypes::sampleRate_10kHz);

	chs.enable(2, true);

	BOOST_CHECK_EQUAL(features->maxSampleRate(WirelessTypes::samplingMode_syncBurst, chs), WirelessTypes::sampleRate_9kHz);

	chs.enable(7, true);
	chs.enable(8, true);

	BOOST_CHECK_EQUAL(features->maxSampleRate(WirelessTypes::samplingMode_syncBurst, chs), WirelessTypes::sampleRate_6kHz);
}

BOOST_AUTO_TEST_CASE(NodeFeatures_maxSampleRate_gLink2)
{
	NodeInfo info(Version(1, 0), WirelessModels::node_gLinkII_10g_in, 0, WirelessTypes::region_usa);

	std::shared_ptr<NodeFeatures> features = NodeFeatures::create(info);

	ChannelMask chs(1);

	BOOST_CHECK_EQUAL(features->maxSampleRate(WirelessTypes::samplingMode_syncBurst, chs), WirelessTypes::sampleRate_10kHz);

	chs.enable(2, true);

	BOOST_CHECK_EQUAL(features->maxSampleRate(WirelessTypes::samplingMode_syncBurst, chs), WirelessTypes::sampleRate_10kHz);

	chs.enable(7, true);
	chs.enable(8, true);

	BOOST_CHECK_EQUAL(features->maxSampleRate(WirelessTypes::samplingMode_syncBurst, chs), WirelessTypes::sampleRate_10kHz);
}

BOOST_AUTO_TEST_CASE(NodeFeatures_maxSampleRate_gLink)
{
	NodeInfo info(Version(1, 0), WirelessModels::node_gLink_10g, 0, WirelessTypes::region_usa);

	std::shared_ptr<NodeFeatures> features = NodeFeatures::create(info);

	ChannelMask chs(1);

	BOOST_CHECK_EQUAL(features->maxSampleRate(WirelessTypes::samplingMode_syncBurst, chs), WirelessTypes::sampleRate_4096Hz);

	chs.enable(2, true);

	BOOST_CHECK_EQUAL(features->maxSampleRate(WirelessTypes::samplingMode_syncBurst, chs), WirelessTypes::sampleRate_2048Hz);

	chs.enable(7, true);
	chs.enable(8, true);

	BOOST_CHECK_EQUAL(features->maxSampleRate(WirelessTypes::samplingMode_syncBurst, chs), WirelessTypes::sampleRate_2048Hz);

	BOOST_CHECK_EQUAL(features->maxSampleRate(WirelessTypes::samplingMode_nonSync, chs), WirelessTypes::sampleRate_512Hz);
}

BOOST_AUTO_TEST_CASE(NodeFeatures_normalizeNumSweeps)
{
	NodeInfo info(Version(1, 0), WirelessModels::node_gLink_10g, 0, WirelessTypes::region_usa);
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
	NodeInfo info(Version(1, 0), WirelessModels::node_gLink_10g, 0, WirelessTypes::region_usa);
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

BOOST_AUTO_TEST_CASE(NodeFeatures_transmitPowers_usa_brazil)
{
	{
		NodeInfo info(Version(1, 0), WirelessModels::node_gLink_10g, 0, WirelessTypes::region_usa);
		std::shared_ptr<NodeFeatures> features = NodeFeatures::create(info);

		WirelessTypes::TransmitPowers powers = features->transmitPowers();

		BOOST_CHECK_EQUAL(powers.size(), 4);
		BOOST_CHECK_EQUAL(powers.at(0), WirelessTypes::power_16dBm);
		BOOST_CHECK_EQUAL(powers.at(1), WirelessTypes::power_10dBm);
		BOOST_CHECK_EQUAL(powers.at(2), WirelessTypes::power_5dBm);
		BOOST_CHECK_EQUAL(powers.at(3), WirelessTypes::power_0dBm);
	}

	{
		NodeInfo info(Version(1, 0), WirelessModels::node_gLink_10g, 0, WirelessTypes::region_brazil);
		std::shared_ptr<NodeFeatures> features = NodeFeatures::create(info);

		WirelessTypes::TransmitPowers powers = features->transmitPowers();

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
		NodeInfo info(Version(1, 0), WirelessModels::node_gLink_10g, 0, WirelessTypes::region_europe);
		std::shared_ptr<NodeFeatures> features = NodeFeatures::create(info);

		WirelessTypes::TransmitPowers powers = features->transmitPowers();

		BOOST_CHECK_EQUAL(powers.size(), 3);
		BOOST_CHECK_EQUAL(powers.at(0), WirelessTypes::power_10dBm);
		BOOST_CHECK_EQUAL(powers.at(1), WirelessTypes::power_5dBm);
		BOOST_CHECK_EQUAL(powers.at(2), WirelessTypes::power_0dBm);
	}

	{
		NodeInfo info(Version(1, 0), WirelessModels::node_gLink_10g, 0, WirelessTypes::region_other);
		std::shared_ptr<NodeFeatures> features = NodeFeatures::create(info);

		WirelessTypes::TransmitPowers powers = features->transmitPowers();

		BOOST_CHECK_EQUAL(powers.size(), 3);
		BOOST_CHECK_EQUAL(powers.at(0), WirelessTypes::power_10dBm);
		BOOST_CHECK_EQUAL(powers.at(1), WirelessTypes::power_5dBm);
		BOOST_CHECK_EQUAL(powers.at(2), WirelessTypes::power_0dBm);
	}
}

BOOST_AUTO_TEST_CASE(NodeFeatures_transmitPowers_japan)
{
	{
		NodeInfo info(Version(1, 0), WirelessModels::node_gLink_10g, 0, WirelessTypes::region_japan);
		std::shared_ptr<NodeFeatures> features = NodeFeatures::create(info);

		WirelessTypes::TransmitPowers powers = features->transmitPowers();

		BOOST_CHECK_EQUAL(powers.size(), 2);
		BOOST_CHECK_EQUAL(powers.at(0), WirelessTypes::power_5dBm);
		BOOST_CHECK_EQUAL(powers.at(1), WirelessTypes::power_0dBm);
	}
}

BOOST_AUTO_TEST_CASE(NodeFeatures_minmaxHardwareGain_multiNodes)
{
	//dvrt link
	{
		NodeInfo info(Version(9, 9), WirelessModels::node_dvrtLink, 0, WirelessTypes::region_usa);

		//make the features() function return the NodeFeatures we want
		std::unique_ptr<NodeFeatures> features = NodeFeatures::create(info);

		BOOST_CHECK_THROW(features->minHardwareGain(), Error_NotSupported);
		BOOST_CHECK_THROW(features->maxHardwareGain(), Error_NotSupported);
	}

	//sg-link oem
	{
		NodeInfo info(Version(9, 9), WirelessModels::node_sgLink_oem, 0, WirelessTypes::region_usa);

		//make the features() function return the NodeFeatures we want
		std::unique_ptr<NodeFeatures> features = NodeFeatures::create(info);

		BOOST_CHECK_CLOSE(features->minHardwareGain(), 20.0, 0.1);
		BOOST_CHECK_CLOSE(features->maxHardwareGain(), 2560.0, 0.1);
	}

	//shm-link
	{
		NodeInfo info(Version(9, 9), WirelessModels::node_shmLink, 0, WirelessTypes::region_usa);

		//make the features() function return the NodeFeatures we want
		std::unique_ptr<NodeFeatures> features = NodeFeatures::create(info);

		BOOST_CHECK_CLOSE(features->minHardwareGain(), 129.0, 0.1);
		BOOST_CHECK_CLOSE(features->maxHardwareGain(), 1629.0, 0.1);
	}

	//v-link
	{
		NodeInfo info(Version(9, 9), WirelessModels::node_vLink, 0, WirelessTypes::region_usa);

		//make the features() function return the NodeFeatures we want
		std::unique_ptr<NodeFeatures> features = NodeFeatures::create(info);

		BOOST_CHECK_CLOSE(features->minHardwareGain(), 20.96632233087558, 0.1);
		BOOST_CHECK_CLOSE(features->maxHardwareGain(), 13073.73046875, 0.1);
	}
}

BOOST_AUTO_TEST_CASE(NodeFeatures_normalizeHardwareGain_sgLink)
{
	NodeInfo info(Version(1, 0), WirelessModels::node_sgLink, 0, WirelessTypes::region_usa);

	std::unique_ptr<NodeFeatures> features = NodeFeatures::create(info);

	BOOST_CHECK_CLOSE(features->normalizeHardwareGain(0.0), 1.85185, 0.1);
	BOOST_CHECK_CLOSE(features->normalizeHardwareGain(1.85185), 1.85185, 0.1);
	BOOST_CHECK_CLOSE(features->normalizeHardwareGain(125), 125.30856999999999, 0.1);
	BOOST_CHECK_CLOSE(features->normalizeHardwareGain(125.30856999999999), 125.30856999999999, 0.1);
	BOOST_CHECK_CLOSE(features->normalizeHardwareGain(250), 248.76529, 0.1);
	BOOST_CHECK_CLOSE(features->normalizeHardwareGain(248.76529), 248.76529, 0.1);
	BOOST_CHECK_CLOSE(features->normalizeHardwareGain(1000), 996.7677699999999, 0.1);
	BOOST_CHECK_CLOSE(features->normalizeHardwareGain(996.7677699999999), 996.7677699999999, 0.1);
	BOOST_CHECK_CLOSE(features->normalizeHardwareGain(1500), 1497.85681, 0.1);
	BOOST_CHECK_CLOSE(features->normalizeHardwareGain(1497.85681), 1497.85681, 0.1);
}

BOOST_AUTO_TEST_CASE(NodeFeatures_normalizeHardwareGain_sgLinkOem)
{
	NodeInfo info(Version(1, 0), WirelessModels::node_sgLink_oem, 0, WirelessTypes::region_usa);

	std::unique_ptr<NodeFeatures> features = NodeFeatures::create(info);

	BOOST_CHECK_CLOSE(features->normalizeHardwareGain(21.0), 20.0, 0.1);
	BOOST_CHECK_CLOSE(features->normalizeHardwareGain(20.0), 20.0, 0.1);
	BOOST_CHECK_CLOSE(features->normalizeHardwareGain(125), 160.0, 0.1);
	BOOST_CHECK_CLOSE(features->normalizeHardwareGain(160.0), 160.0, 0.1);
	BOOST_CHECK_CLOSE(features->normalizeHardwareGain(250), 320.0, 0.1);
	BOOST_CHECK_CLOSE(features->normalizeHardwareGain(320.0), 320.0, 0.1);
}

BOOST_AUTO_TEST_CASE(NodeFeatures_normalizeHardwareGain_shmLink)
{
	NodeInfo info(Version(1, 0), WirelessModels::node_shmLink, 0, WirelessTypes::region_usa);

	std::unique_ptr<NodeFeatures> features = NodeFeatures::create(info);

	BOOST_CHECK_CLOSE(features->normalizeHardwareGain(130), 129.0, 0.1);
	BOOST_CHECK_CLOSE(features->normalizeHardwareGain(129.0), 129.0, 0.1);
	BOOST_CHECK_CLOSE(features->normalizeHardwareGain(1200), 1199.5882352941176, 0.1);
	BOOST_CHECK_CLOSE(features->normalizeHardwareGain(1199.5882352941176), 1199.5882352941176, 0.1);
	BOOST_CHECK_CLOSE(features->normalizeHardwareGain(1628), 1629.0, 0.1);
	BOOST_CHECK_CLOSE(features->normalizeHardwareGain(1629.0), 1629.0, 0.1);
}

BOOST_AUTO_TEST_CASE(NodeFeatures_normalizeHardwareGain_sgLinkRgd)
{
	NodeInfo info(Version(1, 0), WirelessModels::node_sgLink_rgd, 0, WirelessTypes::region_usa);

	std::unique_ptr<NodeFeatures> features = NodeFeatures::create(info);

	BOOST_CHECK_CLOSE(features->normalizeHardwareGain(130), 130.173, 0.1);
	BOOST_CHECK_CLOSE(features->normalizeHardwareGain(129.0), 127.958, 0.1);
	BOOST_CHECK_CLOSE(features->normalizeHardwareGain(1200), features->maxHardwareGain(), 0.1);
	BOOST_CHECK_CLOSE(features->normalizeHardwareGain(403.5882352941176), 402.613, 0.1);
	BOOST_CHECK_CLOSE(features->normalizeHardwareGain(0), 30.5, 0.1);
}

BOOST_AUTO_TEST_CASE(ChannelFeatures_normalizeHardwareGain_vLink)
{
	NodeInfo info(Version(1, 0), WirelessModels::node_vLink, 0, WirelessTypes::region_usa);

	std::unique_ptr<NodeFeatures> features = NodeFeatures::create(info);

	BOOST_CHECK_CLOSE(features->normalizeHardwareGain(22), 21.99995398702434, 0.1);
	BOOST_CHECK_CLOSE(features->normalizeHardwareGain(21.99995398702434), 21.99995398702434, 0.1);
	BOOST_CHECK_CLOSE(features->normalizeHardwareGain(13000), 13073.73046875, 0.1);
	BOOST_CHECK_CLOSE(features->normalizeHardwareGain(3798), 3798.9500567536893, 0.1);
	BOOST_CHECK_CLOSE(features->normalizeHardwareGain(3798.9500567536893), 3798.9500567536893, 0.1);
	BOOST_CHECK_CLOSE(features->normalizeHardwareGain(3799), 3798.9500567536893, 0.1);
	BOOST_CHECK_CLOSE(features->normalizeHardwareGain(13070), 13073.73046875, 0.1);
	BOOST_CHECK_CLOSE(features->normalizeHardwareGain(13073.73046875), 13073.73046875, 0.1);
}

BOOST_AUTO_TEST_SUITE_END()