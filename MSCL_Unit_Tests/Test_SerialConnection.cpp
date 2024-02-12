/*****************************************************************************************
**          Copyright(c) 2015-2024 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.    **
*****************************************************************************************/

#include "mscl/Communication/Connection.h"
#include "mscl/Communication/SerialConnection.h"
#include "mscl/Communication/BoostCommunication.h"
#include "mscl/Utils.h"
#include "mscl/Exceptions.h"

#include <boost/test/unit_test.hpp>
#include <turtle/mock.hpp>

using namespace mscl;

void parseResponse(DataBuffer& data)
{
}

BOOST_AUTO_TEST_SUITE(SerialConnection_Test)

BOOST_AUTO_TEST_CASE(SerialConnection_EstablishConnection_InvalidPort)
{
    //check that the connection throws an exception of an invalid com port
    BOOST_CHECK_THROW(Connection::Serial("ABC123", 921600), Error_InvalidSerialPort);
}

BOOST_AUTO_TEST_SUITE_END()