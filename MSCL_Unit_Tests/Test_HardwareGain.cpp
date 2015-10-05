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
#include "mscl/MicroStrain/Wireless/WirelessNode.h"
#include "mscl/MicroStrain/Wireless/Features/NodeFeatures.h"
#include "mscl/MicroStrain/Wireless/Configuration/HardwareGain.h"

#include <boost/test/unit_test.hpp>
#include "mock_WirelessNode.h"
using namespace mscl;


BOOST_AUTO_TEST_SUITE(HardwareGain_Test)

BOOST_AUTO_TEST_CASE(HardwareGain_sgLink)
{
	WirelessModels::NodeModel node = WirelessModels::node_sgLink;

	BOOST_CHECK_CLOSE(HardwareGain::bitsToGain(0, node), 1.85185, 0.001);
	BOOST_CHECK_CLOSE(HardwareGain::bitsToGain(255, node), 1853.70264999, 0.001);

	BOOST_CHECK_EQUAL(HardwareGain::gainToBits(1.85185, node), 0);
	BOOST_CHECK_EQUAL(HardwareGain::gainToBits(1853.70264999, node), 255);
}

BOOST_AUTO_TEST_CASE(HardwareGain_sgLinkOem)
{
	WirelessModels::NodeModel node = WirelessModels::node_sgLink_oem;

	BOOST_CHECK_CLOSE(HardwareGain::bitsToGain(0, node), 20.0, 0.001);
	BOOST_CHECK_CLOSE(HardwareGain::bitsToGain(255, node), 1.157920892373162e+078, 0.001);

	BOOST_CHECK_EQUAL(HardwareGain::gainToBits(20.0, node), 0);
	BOOST_CHECK_EQUAL(HardwareGain::gainToBits(1.157920892373162e+078, node), 255);
}

BOOST_AUTO_TEST_CASE(HardwareGain_shmLink)
{
	WirelessModels::NodeModel node = WirelessModels::node_shmLink;

	BOOST_CHECK_CLOSE(HardwareGain::bitsToGain(0, node), 129.0, 0.001);
	BOOST_CHECK_CLOSE(HardwareGain::bitsToGain(255, node), 1629.0, 0.001);

	BOOST_CHECK_EQUAL(HardwareGain::gainToBits(129.0, node), 0);
	BOOST_CHECK_EQUAL(HardwareGain::gainToBits(1629.0, node), 255);
}

BOOST_AUTO_TEST_CASE(HardwareGain_sgLinkRgd)
{
	WirelessModels::NodeModel node = WirelessModels::node_sgLink_rgd;

	BOOST_CHECK_CLOSE(HardwareGain::bitsToGain(0, node), 30.5, 0.001);
	BOOST_CHECK_CLOSE(HardwareGain::bitsToGain(255, node), 595.31, 0.001);

	BOOST_CHECK_EQUAL(HardwareGain::gainToBits(30.5, node), 0);
	BOOST_CHECK_EQUAL(HardwareGain::gainToBits(595.31, node), 255);
}

BOOST_AUTO_TEST_CASE(HardwareGain_vLink)
{
	WirelessModels::NodeModel node = WirelessModels::node_vLink;

	BOOST_CHECK_CLOSE(HardwareGain::bitsToGain(0, node), 20.96632233087558, 0.001);
	BOOST_CHECK_CLOSE(HardwareGain::bitsToGain(254, node), 3798.95005675, 0.001);
	BOOST_CHECK_CLOSE(HardwareGain::bitsToGain(255, node), 13073.73046875, 0.001);

	BOOST_CHECK_EQUAL(HardwareGain::gainToBits(20.96632233087558, node), 0);
	BOOST_CHECK_EQUAL(HardwareGain::gainToBits(3799, node), 254);
	BOOST_CHECK_EQUAL(HardwareGain::gainToBits(13073.73046875, node), 255);
}

BOOST_AUTO_TEST_CASE(HardwareGain_tcLink)
{
	WirelessModels::NodeModel tcLink = WirelessModels::node_tcLink_3ch;

	BOOST_CHECK_CLOSE(HardwareGain::bitsToGain(0, tcLink), 1.0, 0.001);
	BOOST_CHECK_CLOSE(HardwareGain::bitsToGain(1, tcLink), 2.0, 0.001);
	BOOST_CHECK_CLOSE(HardwareGain::bitsToGain(2, tcLink), 4.0, 0.001);
	BOOST_CHECK_CLOSE(HardwareGain::bitsToGain(7, tcLink), 128.0, 0.001);

	BOOST_CHECK_EQUAL(HardwareGain::gainToBits(1.0, tcLink), 0);
	BOOST_CHECK_EQUAL(HardwareGain::gainToBits(2.0, tcLink), 1);
	BOOST_CHECK_EQUAL(HardwareGain::gainToBits(4.0, tcLink), 2);
	BOOST_CHECK_EQUAL(HardwareGain::gainToBits(128.0, tcLink), 7);

	BOOST_CHECK_CLOSE(HardwareGain::minGain(tcLink), 1.0, 0.001);
	BOOST_CHECK_CLOSE(HardwareGain::maxGain(tcLink), 128.0, 0.001);

	BOOST_CHECK_CLOSE(HardwareGain::normalizeGain(2.0, tcLink), 2.0, 0.001);
	BOOST_CHECK_CLOSE(HardwareGain::normalizeGain(4.0, tcLink), 4.0, 0.001);
	BOOST_CHECK_CLOSE(HardwareGain::normalizeGain(128.0, tcLink), 128.0, 0.001);
	BOOST_CHECK_CLOSE(HardwareGain::normalizeGain(3.0, tcLink), 4.0, 0.001);
	BOOST_CHECK_CLOSE(HardwareGain::normalizeGain(5.0, tcLink), 4.0, 0.001);
}

BOOST_AUTO_TEST_CASE(HardwareGain_mvpervLink)
{
	WirelessModels::NodeModel model = WirelessModels::node_mvPerVLink;

	BOOST_CHECK_CLOSE(HardwareGain::bitsToGain(0, model), 20.0, 0.001);
	BOOST_CHECK_CLOSE(HardwareGain::bitsToGain(1, model), 40.0, 0.001);
	BOOST_CHECK_CLOSE(HardwareGain::bitsToGain(2, model), 80.0, 0.001);
	BOOST_CHECK_CLOSE(HardwareGain::bitsToGain(7, model), 2560.0, 0.001);

	BOOST_CHECK_EQUAL(HardwareGain::gainToBits(20.0, model), 0);
	BOOST_CHECK_EQUAL(HardwareGain::gainToBits(40.0, model), 1);
	BOOST_CHECK_EQUAL(HardwareGain::gainToBits(80.0, model), 2);
	BOOST_CHECK_EQUAL(HardwareGain::gainToBits(2560.0, model), 7);

	BOOST_CHECK_CLOSE(HardwareGain::minGain(model), 20.0, 0.001);
	BOOST_CHECK_CLOSE(HardwareGain::maxGain(model), 2560.0, 0.001);

	BOOST_CHECK_CLOSE(HardwareGain::normalizeGain(20.7, model), 20.0, 0.001);
	BOOST_CHECK_CLOSE(HardwareGain::normalizeGain(34.0, model), 40.0, 0.001);
	BOOST_CHECK_CLOSE(HardwareGain::normalizeGain(26.843, model), 20.0, 0.001);
	BOOST_CHECK_CLOSE(HardwareGain::normalizeGain(0.0, model), 20.0, 0.001);
	BOOST_CHECK_CLOSE(HardwareGain::normalizeGain(64234.1234, model), 2560.0, 0.001);
}

BOOST_AUTO_TEST_SUITE_END()