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
#include "mscl/MicroStrain/Wireless/Configuration/ConfigIssue.h"

#include <boost/test/unit_test.hpp>

using namespace mscl;

BOOST_AUTO_TEST_SUITE(ConfigIssue_Test)

BOOST_AUTO_TEST_CASE(ConfigIssue_constructor)
{
	ConfigIssue i(ConfigIssue::CONFIG_DATA_FORMAT, "Invalid Data Format");

	BOOST_CHECK_EQUAL(i.id(), ConfigIssue::CONFIG_DATA_FORMAT);
	BOOST_CHECK_EQUAL(i.description(), "Invalid Data Format");
}

BOOST_AUTO_TEST_CASE(ConfigIssue_vector)
{
	ConfigIssue i1(ConfigIssue::CONFIG_DATA_FORMAT, "Invalid Data Format");
	ConfigIssue i2(ConfigIssue::CONFIG_ACTIVE_CHANNELS, "Invalid Channel Mask");
	ConfigIssue i3(ConfigIssue::CONFIG_SAMPLE_RATE, "Invalid Rate");

	ConfigIssues issues;
	issues.push_back(i1);
	issues.push_back(i2);
	issues.push_back(i3);

	BOOST_CHECK_EQUAL(issues.size(), 3);
	BOOST_CHECK_EQUAL(issues.at(1).description(), "Invalid Channel Mask");
}

BOOST_AUTO_TEST_SUITE_END()