/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "mscl/MicroStrain/Wireless/WirelessModels.h"
#include "mscl/Exceptions.h"

#include <boost/test/unit_test.hpp>

using namespace mscl;

BOOST_AUTO_TEST_SUITE(WirelessModels_Test)

BOOST_AUTO_TEST_CASE(WirelessModels_nodeFromLegacyModel)
{
    //verify that converting from old model numbers to new model numbers works
    BOOST_CHECK_EQUAL(WirelessModels::nodeFromLegacyModel(2316), WirelessModels::node_wattLink);
    BOOST_CHECK_EQUAL(WirelessModels::nodeFromLegacyModel(2418), WirelessModels::node_gLink_2g);
    BOOST_CHECK_EQUAL(WirelessModels::nodeFromLegacyModel(2419), WirelessModels::node_gLink_10g);
    BOOST_CHECK_EQUAL(WirelessModels::nodeFromLegacyModel(2417), WirelessModels::node_sgLink);
    BOOST_CHECK_EQUAL(WirelessModels::nodeFromLegacyModel(2420), WirelessModels::node_sgLink_oem_S);
    BOOST_CHECK_EQUAL(WirelessModels::nodeFromLegacyModel(2421), WirelessModels::node_dvrtLink);
    BOOST_CHECK_EQUAL(WirelessModels::nodeFromLegacyModel(2423), WirelessModels::node_sgLink_oem);
    BOOST_CHECK_EQUAL(WirelessModels::nodeFromLegacyModel(2426), WirelessModels::node_sgLink_rgd);
    BOOST_CHECK_EQUAL(WirelessModels::nodeFromLegacyModel(2427), WirelessModels::node_tcLink_6ch);
    BOOST_CHECK_EQUAL(WirelessModels::nodeFromLegacyModel(2430), WirelessModels::node_sgLink_herm);
    BOOST_CHECK_EQUAL(WirelessModels::nodeFromLegacyModel(2435), WirelessModels::node_gLinkII_cust_in);
    BOOST_CHECK_EQUAL(WirelessModels::nodeFromLegacyModel(2432), WirelessModels::node_gLinkII_2g_in);
    BOOST_CHECK_EQUAL(WirelessModels::nodeFromLegacyModel(2436), WirelessModels::node_gLinkII_10g_in);
    BOOST_CHECK_EQUAL(WirelessModels::nodeFromLegacyModel(2437), WirelessModels::node_gLinkII_cust_ex);
    BOOST_CHECK_EQUAL(WirelessModels::nodeFromLegacyModel(2438), WirelessModels::node_gLinkII_2g_ex);
    BOOST_CHECK_EQUAL(WirelessModels::nodeFromLegacyModel(2439), WirelessModels::node_gLinkII_10g_ex);
    BOOST_CHECK_EQUAL(WirelessModels::nodeFromLegacyModel(2440), WirelessModels::node_gLink_rgd_10g);
    BOOST_CHECK_EQUAL(WirelessModels::nodeFromLegacyModel(2433), WirelessModels::node_vLink);
    BOOST_CHECK_EQUAL(WirelessModels::nodeFromLegacyModel(2622), WirelessModels::node_tcLink_1ch);
    BOOST_CHECK_EQUAL(WirelessModels::nodeFromLegacyModel(2624), WirelessModels::node_envLink_mini);
    BOOST_CHECK_EQUAL(WirelessModels::nodeFromLegacyModel(2625), WirelessModels::node_rtdLink);
    BOOST_CHECK_EQUAL(WirelessModels::nodeFromLegacyModel(2984), WirelessModels::node_iepeLink);
    BOOST_CHECK_EQUAL(WirelessModels::nodeFromLegacyModel(2623), WirelessModels::node_tcLink_3ch);
    BOOST_CHECK_EQUAL(WirelessModels::nodeFromLegacyModel(2434), WirelessModels::node_tcLink_6ch_ip67);
    BOOST_CHECK_EQUAL(WirelessModels::nodeFromLegacyModel(2429), WirelessModels::node_shmLink);
    BOOST_CHECK_EQUAL(WirelessModels::nodeFromLegacyModel(2993), WirelessModels::node_envLink_pro);

    BOOST_CHECK_EQUAL(WirelessModels::nodeFromLegacyModel(0), 0);
}

BOOST_AUTO_TEST_CASE(WirelessModels_baseFromLegacyModel)
{
    BOOST_CHECK_EQUAL(WirelessModels::baseFromLegacyModel(50), WirelessModels::base_wsda_1000);
    BOOST_CHECK_EQUAL(WirelessModels::baseFromLegacyModel(2995), WirelessModels::base_wsda_1000);
    BOOST_CHECK_EQUAL(WirelessModels::baseFromLegacyModel(2050), WirelessModels::base_wsda_2000);
    BOOST_CHECK_EQUAL(WirelessModels::baseFromLegacyModel(1010), WirelessModels::base_wsdaBase_101_analog);
    BOOST_CHECK_EQUAL(WirelessModels::baseFromLegacyModel(2625), WirelessModels::base_wsdaBase_101_analog);
    BOOST_CHECK_EQUAL(WirelessModels::baseFromLegacyModel(1020), WirelessModels::base_wsdaBase_102_rs232);
    BOOST_CHECK_EQUAL(WirelessModels::baseFromLegacyModel(2626), WirelessModels::base_wsdaBase_102_rs232);
    BOOST_CHECK_EQUAL(WirelessModels::baseFromLegacyModel(1040), WirelessModels::base_wsdaBase_104_usb);
    BOOST_CHECK_EQUAL(WirelessModels::baseFromLegacyModel(2621), WirelessModels::base_wsdaBase_104_usb);

    BOOST_CHECK_EQUAL(WirelessModels::baseFromLegacyModel(1), 1);
}

BOOST_AUTO_TEST_SUITE_END()
