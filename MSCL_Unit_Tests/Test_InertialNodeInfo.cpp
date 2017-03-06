/*******************************************************************************
Copyright(c) 2015-2017 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "mscl/MicroStrain/Inertial/Features/InertialNodeFeatures.h"
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
    info.model = InertialModels::node_3dm_dh3;
    info.modelName = "ABCDABCDABCDABCD";
    info.modelNumber = "6219-12345";
    info.serialNumber = "ABCDABCDABCDABCD";
    info.lotNumber = "ABCDABCDABCDABCD";
    info.deviceOptions = "ABCDABCDABCDABCD";

    //make the getDeviceInfo command return the response we created
    MOCK_EXPECT(impl->getDeviceInfo).once().returns(info);    


    std::vector<uint16> fields;
    fields.push_back(InertialTypes::CMD_SENSOR_MESSAGE_FORMAT);
    fields.push_back(InertialTypes::CMD_GNSS_MESSAGE_FORMAT);
    fields.push_back(InertialTypes::CH_FIELD_SENSOR_RAW_MAG_VEC);
    fields.push_back(InertialTypes::CH_FIELD_SENSOR_SCALED_ACCEL_VEC);
    fields.push_back(InertialTypes::CH_FIELD_SENSOR_DELTA_THETA_VEC);
    fields.push_back(InertialTypes::CH_FIELD_ESTFILTER_ESTIMATED_ORIENT_MATRIX);
    fields.push_back(InertialTypes::CH_FIELD_ESTFILTER_ESTIMATED_NED_UNCERT);
    fields.push_back(InertialTypes::CH_FIELD_ESTFILTER_FILTER_STATUS);
    
    //make the getDescriptorSets command return the response we created
    MOCK_EXPECT(impl->getDescriptorSets).once().returns(fields);

    //verify the result is good
    BOOST_CHECK_EQUAL(node.firmwareVersion().str(), "1.1.17");
    BOOST_CHECK_EQUAL(node.model(), InertialModels::node_3dm_dh3);
    BOOST_CHECK_EQUAL(node.modelName(), "ABCDABCDABCDABCD");
    BOOST_CHECK_EQUAL(node.modelNumber(), "6219-12345");
    BOOST_CHECK_EQUAL(node.serialNumber(), "ABCDABCDABCDABCD");
    BOOST_CHECK_EQUAL(node.lotNumber(), "ABCDABCDABCDABCD");
    BOOST_CHECK_EQUAL(node.deviceOptions(), "ABCDABCDABCDABCD");
    BOOST_CHECK_EQUAL(node.features().supportsCommand(InertialTypes::CMD_SENSOR_MESSAGE_FORMAT), true);
    BOOST_CHECK_EQUAL(node.features().supportsCategory(InertialTypes::CATEGORY_ESTFILTER), true);
    BOOST_CHECK_EQUAL(node.features().supportsCategory(InertialTypes::CATEGORY_GNSS), false);
    BOOST_CHECK_EQUAL(node.features().supportsCategory(InertialTypes::CATEGORY_SENSOR), true);
    
    InertialTypes::InertialChannelFields estFilterChs = node.features().supportedChannelFields(InertialTypes::CATEGORY_ESTFILTER);
    InertialTypes::InertialChannelFields sensorChs = node.features().supportedChannelFields(InertialTypes::CATEGORY_SENSOR);
    
    BOOST_CHECK_THROW(node.features().supportedChannelFields(InertialTypes::CATEGORY_GNSS), Error_NotSupported);

    BOOST_CHECK_EQUAL(estFilterChs.at(0), InertialTypes::CH_FIELD_ESTFILTER_ESTIMATED_ORIENT_MATRIX);
    BOOST_CHECK_EQUAL(estFilterChs.at(1), InertialTypes::CH_FIELD_ESTFILTER_ESTIMATED_NED_UNCERT);
    BOOST_CHECK_EQUAL(estFilterChs.at(2), InertialTypes::CH_FIELD_ESTFILTER_FILTER_STATUS);
    BOOST_CHECK_EQUAL(sensorChs.at(0), InertialTypes::CH_FIELD_SENSOR_RAW_MAG_VEC);
    BOOST_CHECK_EQUAL(sensorChs.at(1), InertialTypes::CH_FIELD_SENSOR_SCALED_ACCEL_VEC);
    BOOST_CHECK_EQUAL(sensorChs.at(2), InertialTypes::CH_FIELD_SENSOR_DELTA_THETA_VEC);

    BOOST_CHECK_EQUAL(node.name(), "inertial-ABCDABCDABCDABCD");
}

BOOST_AUTO_TEST_SUITE_END()