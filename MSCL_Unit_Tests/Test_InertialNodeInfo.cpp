/*******************************************************************************
Copyright(c) 2015-2016 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "mscl/MicroStrain/Inertial/InertialNodeInfo.h"
#include "mscl/MicroStrain/Inertial/InertialNode.h"

#include <boost/test/unit_test.hpp>
#include "mock_InertialNode.h"
using namespace mscl;


BOOST_AUTO_TEST_SUITE(InertialNodeInfo_Test)

BOOST_AUTO_TEST_CASE(InertialNodeInfo_loadNodeInfo)
{
    std::shared_ptr<mock_InertialNodeImpl> impl(new mock_InertialNodeImpl());
    InertialNode node(impl);

    InertialDeviceInfo info;
    info.fwVersion = Version(1, 1, 17);
    info.modelName = "ABCDABCDABCDABCD";
    info.modelNumber = "6219-12345";
    info.serialNumber = "ABCDABCDABCDABCD";
    info.lotNumber = "ABCDABCDABCDABCD";
    info.deviceOptions = "ABCDABCDABCDABCD";

    //make the getDeviceInfo command return the response we created
    MOCK_EXPECT(impl->getDeviceInfo).once().returns(info);    


    std::vector<uint16> fields;
    fields.push_back(InertialTypes::CMD_SENSOR_MESSAGE_FORMAT);
    fields.push_back(InertialTypes::CMD_GPS_MESSAGE_FORMAT);
    fields.push_back(InertialTypes::CH_FIELD_SENSOR_RAW_MAG_VEC);
    fields.push_back(InertialTypes::CH_FIELD_SENSOR_SCALED_ACCEL_VEC);
    fields.push_back(InertialTypes::CH_FIELD_SENSOR_DELTA_THETA_VEC);
    fields.push_back(InertialTypes::CH_FIELD_ESTFILTER_ESTIMATED_ORIENT_MATRIX);
    fields.push_back(InertialTypes::CH_FIELD_ESTFILTER_ESTIMATED_NED_UNCERT);
    fields.push_back(InertialTypes::CH_FIELD_ESTFILTER_FILTER_STATUS);
    
    //make the getDescriptorSets command return the response we created
    MOCK_EXPECT(impl->getDescriptorSets).once().returns(fields);


    //call the loadNodeInfo command
    InertialNodeInfo nodeInfo = node.info();

    //verify the result is good
    BOOST_CHECK_EQUAL(nodeInfo.firmwareVersion().str(), "1.1.17");
    BOOST_CHECK_EQUAL(nodeInfo.model(), InertialModels::node_3dm_dh3);
    BOOST_CHECK_EQUAL(nodeInfo.modelName(), "ABCDABCDABCDABCD");
    BOOST_CHECK_EQUAL(nodeInfo.modelNumber(), "6219-12345");
    BOOST_CHECK_EQUAL(nodeInfo.serialNumber(), "ABCDABCDABCDABCD");
    BOOST_CHECK_EQUAL(nodeInfo.lotNumber(), "ABCDABCDABCDABCD");
    BOOST_CHECK_EQUAL(nodeInfo.deviceOptions(), "ABCDABCDABCDABCD");
    BOOST_CHECK_EQUAL(nodeInfo.supportsCommand(InertialTypes::CMD_SENSOR_MESSAGE_FORMAT), true);
    BOOST_CHECK_EQUAL(nodeInfo.supportsCategory(InertialTypes::CATEGORY_ESTFILTER), true);
    BOOST_CHECK_EQUAL(nodeInfo.supportsCategory(InertialTypes::CATEGORY_GPS), false);
    BOOST_CHECK_EQUAL(nodeInfo.supportsCategory(InertialTypes::CATEGORY_SENSOR), true);
    
    InertialTypes::ChannelFields estFilterChs = nodeInfo.supportedChannelFields(InertialTypes::CATEGORY_ESTFILTER);
    InertialTypes::ChannelFields sensorChs = nodeInfo.supportedChannelFields(InertialTypes::CATEGORY_SENSOR);
    InertialTypes::ChannelFields gpsChs = nodeInfo.supportedChannelFields(InertialTypes::CATEGORY_GPS);

    BOOST_CHECK_EQUAL(gpsChs.size(), 0);
    BOOST_CHECK_EQUAL(estFilterChs.at(0), InertialTypes::CH_FIELD_ESTFILTER_ESTIMATED_ORIENT_MATRIX);
    BOOST_CHECK_EQUAL(estFilterChs.at(1), InertialTypes::CH_FIELD_ESTFILTER_ESTIMATED_NED_UNCERT);
    BOOST_CHECK_EQUAL(estFilterChs.at(2), InertialTypes::CH_FIELD_ESTFILTER_FILTER_STATUS);
    BOOST_CHECK_EQUAL(sensorChs.at(0), InertialTypes::CH_FIELD_SENSOR_RAW_MAG_VEC);
    BOOST_CHECK_EQUAL(sensorChs.at(1), InertialTypes::CH_FIELD_SENSOR_SCALED_ACCEL_VEC);
    BOOST_CHECK_EQUAL(sensorChs.at(2), InertialTypes::CH_FIELD_SENSOR_DELTA_THETA_VEC);

    BOOST_CHECK_EQUAL(node.name(), "inertial-ABCDABCDABCDABCD");
}

BOOST_AUTO_TEST_SUITE_END()