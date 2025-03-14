/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "mscl/MicroStrain/Wireless/Configuration/ConfigIssue.h"

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
