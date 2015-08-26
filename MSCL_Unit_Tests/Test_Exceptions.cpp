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
#include "mscl/Exceptions.h"

#include <boost/test/unit_test.hpp>

using namespace mscl;

BOOST_AUTO_TEST_SUITE(Exceptions_Test)

BOOST_AUTO_TEST_CASE(Exceptions_Error)
{
	std::string txt = "";

	try
	{
		//throw the standard Error() exception
		throw Error();
	}
	catch(Error& ex)
	{
		txt = ex.what();
	}

	//check that the standard text was received
	BOOST_CHECK_EQUAL(txt, "MSCL has thrown an exception.");


	try
	{
		txt = "";

		//throw the standard Error() exception
		throw Error("This is a test.");
	}
	catch(Error& ex)
	{
		txt = ex.what();
	}

	//check that the custom text was added to the message
	BOOST_CHECK_EQUAL(txt, "This is a test.");
}

BOOST_AUTO_TEST_CASE(Exceptions_ErrorNoData)
{
	std::string txt = "";

	try
	{
		//throw the Error_NoData() exception
		throw Error_NoData();
	}
	catch(Error_NoData& ex)
	{
		txt = ex.what();
	}

	//check that the standard text was received
	BOOST_CHECK_EQUAL(txt, "No data is available.");


	bool caughtException = false;
	try
	{
		//throw the Error_NoData() exception
		throw Error_NoData();
	}
	catch(Error&)
	{
		caughtException = true;
	}

	//check that we caught the exception using the base Error exception class
	BOOST_CHECK_EQUAL(caughtException, true);
}

BOOST_AUTO_TEST_CASE(Exceptions_ErrorBadDataType)
{
	std::string txt = "";

	try
	{
		//throw the Error_BadDataType() exception
		throw Error_BadDataType();
	}
	catch(Error_BadDataType& ex)
	{
		txt = ex.what();
	}

	//check that the standard text was received
	BOOST_CHECK_EQUAL(txt, "Data was accessed using the wrong data type.");


	bool caughtException = false;
	try
	{
		//throw the Error_BadDataType() exception
		throw Error_BadDataType();
	}
	catch(Error&)
	{
		caughtException = true;
	}

	//check that we caught the exception using the base Error exception class
	BOOST_CHECK_EQUAL(caughtException, true);
}

BOOST_AUTO_TEST_CASE(Exceptions_ErrorUnknownSampleRate)
{
	std::string txt = "";

	try
	{
		//throw the Error_UnknownSampleRate() exception
		throw Error_UnknownSampleRate();
	}
	catch(Error_UnknownSampleRate& ex)
	{
		txt = ex.what();
	}

	//check that the standard text was received
	BOOST_CHECK_EQUAL(txt, "Unknown Sample Rate.");


	bool caughtException = false;
	try
	{
		//throw the Error_UnknownSampleRate() exception
		throw Error_UnknownSampleRate();
	}
	catch(Error&)
	{
		caughtException = true;
	}

	//check that we caught the exception using the base Error exception class
	BOOST_CHECK_EQUAL(caughtException, true);
}

BOOST_AUTO_TEST_CASE(Exceptions_ErrorTimeout)
{
	std::string txt = "";

	try
	{
		//throw the Error_Timeout() exception
		throw Error_Timeout();
	}
	catch(Error_Timeout& ex)
	{
		txt = ex.what();
	}

	//check that the standard text was received
	BOOST_CHECK_EQUAL(txt, "The operation has timed out.");


	bool caughtException = false;
	try
	{
		//throw the Error_Timeout() exception
		throw Error_Timeout();
	}
	catch(Error&)
	{
		caughtException = true;
	}

	//check that we caught the exception using the base Error exception class
	BOOST_CHECK_EQUAL(caughtException, true);
}

BOOST_AUTO_TEST_CASE(Exceptions_ErrorCommunication)
{
	std::string txt = "";
	int code = 0;

	try
	{
		//throw the Error_Connection() exception
		throw Error_Connection(45);
	}
	catch(Error_Connection& ex)
	{
		txt = ex.what();
		code = ex.code();
	}

	//check that the standard text was received
	BOOST_CHECK_EQUAL(txt, "Connection error.");

	//check that the set code is received
	BOOST_CHECK_EQUAL(code, 45);

	bool caughtException = false;
	try
	{
		//throw the Error_Connection() exception
		throw Error_Connection();
	}
	catch(Error&)
	{
		caughtException = true;
	}

	//check that we caught the exception using the base Error exception class
	BOOST_CHECK_EQUAL(caughtException, true);
}

BOOST_AUTO_TEST_CASE(Exceptions_ErrorInvalidComPort)
{
	std::string txt = "";
	int code = 0;

	try
	{
		//throw the Error_InvalidSerialPort() exception
		throw Error_InvalidSerialPort(20);
	}
	catch(Error_InvalidSerialPort& ex)
	{
		txt = ex.what();
		code = ex.code();
	}

	//check that the standard text was received
	BOOST_CHECK_EQUAL(txt, "Invalid Com Port.");

	//check that the set code is received
	BOOST_CHECK_EQUAL(code, 20);

	bool caughtException = false;
	try
	{
		//throw the Error_InvalidSerialPort() exception
		throw Error_InvalidSerialPort(25);
	}
	catch(Error&)
	{
		caughtException = true;
	}

	//check that we caught the exception using the base Error exception class
	BOOST_CHECK_EQUAL(caughtException, true);


	caughtException = false;
	try
	{
		//throw the Error_InvalidSerialPort() exception
		throw Error_InvalidSerialPort(25);
	}
	catch(Error_Connection&)
	{
		caughtException = true;
	}

	//check that we caught the exception using the base Error_Connection exception class
	BOOST_CHECK_EQUAL(caughtException, true);
}

BOOST_AUTO_TEST_CASE(Exceptions_ErrorNotSupported)
{
	std::string txt = "";

	try
	{
		throw Error_NotSupported();
	}
	catch(Error_NotSupported& ex)
	{
		txt = ex.what();
	}

	//check that the standard text was received
	BOOST_CHECK_EQUAL(txt, "This feature is not supported.");


	bool caughtException = false;
	try
	{
		//throw the Error_InvalidSerialPort() exception
		throw Error_NotSupported("Hello World");
	}
	catch(Error& ex)
	{
		caughtException = true;
		txt = ex.what();
	}

	//check that we caught the exception using the base Error exception class
	BOOST_CHECK_EQUAL(caughtException, true);
	BOOST_CHECK_EQUAL(txt, "Hello World");
}

BOOST_AUTO_TEST_SUITE_END()