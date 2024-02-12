/*****************************************************************************************
**          Copyright(c) 2015-2024 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.    **
*****************************************************************************************/

#include "mscl/MicroStrain/Wireless/BaseStationAnalogPair.h"
#include "mscl/Utils.h"

#include <boost/test/unit_test.hpp>
using namespace mscl;


BOOST_AUTO_TEST_SUITE(BaseStationAnalogPair_Test)

BOOST_AUTO_TEST_CASE(BaseStationAnalogPair_Constructors)
{
    //tests the constructors

    BaseStationAnalogPair defaultPair;
    BOOST_CHECK_EQUAL(defaultPair.nodeAddress(), 0);
    BOOST_CHECK_EQUAL(defaultPair.nodeChannel(), 1);
    BOOST_CHECK_CLOSE(defaultPair.outputVal_0V(), 0.0, 0.0001);
    BOOST_CHECK_CLOSE(defaultPair.outputVal_3V(), 65535.0, 0.0001);
    BOOST_CHECK_EQUAL(defaultPair.expectFloatData(), true);

    BaseStationAnalogPair floatPair = BaseStationAnalogPair::Float(62353, 3, 1.234f, 97643.545f);
    BOOST_CHECK_EQUAL(floatPair.nodeAddress(), 62353);
    BOOST_CHECK_EQUAL(floatPair.nodeChannel(), 3);
    BOOST_CHECK_CLOSE(floatPair.outputVal_0V(), 1.234, 0.0001);
    BOOST_CHECK_CLOSE(floatPair.outputVal_3V(), 97643.545, 0.0001);
    BOOST_CHECK_EQUAL(floatPair.expectFloatData(), true);

    BaseStationAnalogPair nonFloatPair = BaseStationAnalogPair::NonFloat(945, 6);
    BOOST_CHECK_EQUAL(nonFloatPair.nodeAddress(), 945);
    BOOST_CHECK_EQUAL(nonFloatPair.nodeChannel(), 6);
    BOOST_CHECK_EQUAL(Utils::isNaN(nonFloatPair.outputVal_0V()), true);
    BOOST_CHECK_EQUAL(Utils::isNaN(nonFloatPair.outputVal_3V()), true);
    BOOST_CHECK_EQUAL(nonFloatPair.expectFloatData(), false);
}

BOOST_AUTO_TEST_CASE(BaseStationAnalogPair_outputVal_0V)
{
    //tests setting and getting outputVal_0V

    BaseStationAnalogPair pair = BaseStationAnalogPair::NonFloat(945, 6);
    
    BOOST_CHECK_EQUAL(Utils::isNaN(pair.outputVal_0V()), true);
    BOOST_CHECK_EQUAL(Utils::isNaN(pair.outputVal_3V()), true);
    BOOST_CHECK_EQUAL(pair.expectFloatData(), false);

    //set the 0V output value to a real value
    pair.outputVal_0V(674.8456f);
    BOOST_CHECK_CLOSE(pair.outputVal_0V(), 674.8456, 0.0001);
    BOOST_CHECK_CLOSE(pair.outputVal_3V(), 675.8456, 0.0001);    //verify outputVal_3V got set to outputVal_0V + 1
    BOOST_CHECK_EQUAL(pair.expectFloatData(), true);

    //change the 0V output value to another real value
    pair.outputVal_0V(0.00423f);
    BOOST_CHECK_CLOSE(pair.outputVal_0V(), 0.00423, 0.0001);
    BOOST_CHECK_CLOSE(pair.outputVal_3V(), 675.8456, 0.0001);    //verify outputVal_3V didn't get changed
    BOOST_CHECK_EQUAL(pair.expectFloatData(), true);

    //change the 0V output to disabled (NaN)
    pair.outputVal_0V(BaseStationAnalogPair::CHANNEL_NOT_FLOAT);
    BOOST_CHECK_EQUAL(Utils::isNaN(pair.outputVal_0V()), true);        //verify it is disabled
    BOOST_CHECK_EQUAL(Utils::isNaN(pair.outputVal_3V()), true);        //verify outputVal_3V got disabled as well
    BOOST_CHECK_EQUAL(pair.expectFloatData(), false);
}

BOOST_AUTO_TEST_CASE(BaseStationAnalogPair_outputVal_3V)
{
    //tests setting and getting outputVal_3V

    BaseStationAnalogPair pair = BaseStationAnalogPair::Float(945, 6, 123.45f, 0.975f);

    BOOST_CHECK_EQUAL(Utils::isNaN(pair.outputVal_0V()), false);
    BOOST_CHECK_EQUAL(Utils::isNaN(pair.outputVal_3V()), false);
    BOOST_CHECK_CLOSE(pair.outputVal_0V(), 123.45, 0.0001);
    BOOST_CHECK_CLOSE(pair.outputVal_3V(), 0.975, 0.0001);
    BOOST_CHECK_EQUAL(pair.expectFloatData(), true);

    //disable the 3V value (NaN)
    pair.outputVal_3V(BaseStationAnalogPair::CHANNEL_NOT_FLOAT);
    BOOST_CHECK_EQUAL(Utils::isNaN(pair.outputVal_0V()), true);        //verify outputVal_0V got disabled as well
    BOOST_CHECK_EQUAL(Utils::isNaN(pair.outputVal_3V()), true);        
    BOOST_CHECK_EQUAL(pair.expectFloatData(), false);

    //change the 3V output value to a real value
    pair.outputVal_3V(0.5f);
    BOOST_CHECK_CLOSE(pair.outputVal_0V(), -0.5, 0.0001);
    BOOST_CHECK_CLOSE(pair.outputVal_3V(), 0.5, 0.0001);    
    BOOST_CHECK_EQUAL(pair.expectFloatData(), true);

    //change the 3V output value to another real value
    pair.outputVal_3V(905.0f);
    BOOST_CHECK_CLOSE(pair.outputVal_0V(), -0.5, 0.0001); //verify outputVal_0V didn't get changed
    BOOST_CHECK_CLOSE(pair.outputVal_3V(), 905.0, 0.0001);    
    BOOST_CHECK_EQUAL(pair.expectFloatData(), true);
}

BOOST_AUTO_TEST_CASE(BaseStationAnalogPair_expectFloatData)
{
    //tests setting and getting the expectFloatData setting

    BaseStationAnalogPair pair = BaseStationAnalogPair::NonFloat(945, 6);

    BOOST_CHECK_EQUAL(pair.expectFloatData(), false);

    pair.expectFloatData(true);
    BOOST_CHECK_CLOSE(pair.outputVal_0V(), 0.0, 0.0001);
    BOOST_CHECK_CLOSE(pair.outputVal_3V(), 65535.0, 0.0001);
    BOOST_CHECK_EQUAL(pair.expectFloatData(), true);

    pair.expectFloatData(false);
    BOOST_CHECK_EQUAL(Utils::isNaN(pair.outputVal_0V()), true);
    BOOST_CHECK_EQUAL(Utils::isNaN(pair.outputVal_3V()), true);
    BOOST_CHECK_EQUAL(pair.expectFloatData(), false);
}

BOOST_AUTO_TEST_SUITE_END()