/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "mscl/MicroStrain/DataBuffer.h"
#include "mscl/MicroStrain/ResponseCollector.h"
#include "mscl/MicroStrain/Wireless/Commands/PageDownload.h"

using namespace mscl;

DISABLE_WARNING_BOOST_START
#include <boost/test/unit_test.hpp>
DISABLE_WARNING_BOOST_END

DataBuffer buildPageDownloadResponse()
{
    Bytes resultBytes;
    resultBytes.push_back(0x05);    //command id

    for(int i = 0; i < 264; i++)
    {
        resultBytes.push_back(0x00);//data points
    }

    resultBytes.push_back(0x00);    //checksum msb
    resultBytes.push_back(0x00);    //checksum lsb

    DataBuffer result(resultBytes);

    return result;
}

DataBuffer buildPageDownloadResponse_BadChecksum()
{
    Bytes resultBytes;
    resultBytes.push_back(0x05);    //command id

    for(int i = 0; i < 264; i++)
    {
        resultBytes.push_back(0x00);//data points
    }

    //put a bad checksum byte
    resultBytes.push_back(0x00);
    resultBytes.push_back(0x02);

    DataBuffer result(resultBytes);

    return result;
}

DataBuffer buildPageDownloadResponse_BadCommandId()
{
    Bytes resultBytes;
    resultBytes.push_back(0x06);    //bad command id

    for(int i = 0; i < 264; i++)
    {
        resultBytes.push_back(0x00);//data points
    }

    //checksum bytes
    resultBytes.push_back(0x00);
    resultBytes.push_back(0x00);

    DataBuffer result(resultBytes);

    return result;
}

DataBuffer buildPageDownloadFailResponse()
{
    Bytes resultBytes;
    resultBytes.push_back(0x05);    //command id
    resultBytes.push_back(0x21);    //fail response id

    DataBuffer result(resultBytes);

    return result;
}

BOOST_AUTO_TEST_SUITE(PageDownload_Test)

BOOST_AUTO_TEST_CASE(PageDownload_BuildCommand)
{
    //create the command
    ByteStream b = PageDownload::buildCommand(123, 2);

    //check all the bytes in the ByteStream
    BOOST_CHECK_EQUAL(b.read_uint8(0), 0x05);    //command id
    BOOST_CHECK_EQUAL(b.read_uint16(1), 123);    //node address
    BOOST_CHECK_EQUAL(b.read_uint16(3), 2);        //page index
}

BOOST_AUTO_TEST_CASE(PageDownload_MatchSuccess)
{
    std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
    PageDownload::Response response(rc);

    DataBuffer bytes = buildPageDownloadResponse();

    //first time through just matches the command id
    BOOST_CHECK_EQUAL(response.match(bytes), true);
    BOOST_CHECK_EQUAL(response.fullyMatched(), false);

    //second time through should match the rest of the packet
    BOOST_CHECK_EQUAL(response.match(bytes), true);
    BOOST_CHECK_EQUAL(response.fullyMatched(), true);
    BOOST_CHECK_EQUAL(response.success(), true);
    BOOST_CHECK_EQUAL(response.dataPoints().size(), 264);
    BOOST_CHECK_EQUAL(response.dataPoints().read_uint16(0), 0);//just check the first byte of the data
}

BOOST_AUTO_TEST_CASE(PageDownload_MatchFail_DataLenZero)
{
    std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
    PageDownload::Response response(rc);

    DataBuffer bytes(0);

    BOOST_CHECK_EQUAL(response.match(bytes), false);//failed to match bytes remaining
}

BOOST_AUTO_TEST_CASE(PageDownload_MatchFail_DataLenBad)
{
    std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
    PageDownload::Response response(rc);

    Bytes resultBytes;
    resultBytes.push_back(0x05);    //command id

    for(int i = 0; i < 50; i++)
    {
        resultBytes.push_back(0x00);//data points
    }

    DataBuffer result(resultBytes);

    //first time through just matches the command id
    BOOST_CHECK_EQUAL(response.match(result), true);
    BOOST_CHECK_EQUAL(response.fullyMatched(), false);

    BOOST_CHECK_EQUAL(response.match(result), false);    //not enough bytes
}

BOOST_AUTO_TEST_CASE(PageDownload_MatchFail_CmdId)
{
    std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
    PageDownload::Response response(rc);

    DataBuffer bytes = buildPageDownloadResponse_BadCommandId();

    BOOST_CHECK_EQUAL(response.match(bytes), false);//first time through fails to match command id
    BOOST_CHECK_EQUAL(response.match(bytes), false);//second time through fails still because command id was never matched
}

BOOST_AUTO_TEST_CASE(PageDownload_MatchFail_Checksum)
{
    std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
    PageDownload::Response response(rc);

    DataBuffer bytes = buildPageDownloadResponse_BadChecksum();

    BOOST_CHECK_EQUAL(response.match(bytes), true);//first time through just matches the command id
    BOOST_CHECK_EQUAL(response.match(bytes), false);//second time through fails to match because of a bad checksum
}

// BOOST_AUTO_TEST_CASE(PageDownload_MatchFailResponse_Success)
// {
//     std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
//     PageDownload::Response response(rc);
//
//     DataBuffer bytes = buildPageDownloadFailResponse();
//
//     //first time through just matches the command id
//     BOOST_CHECK_EQUAL(response.match(bytes), true);
//     BOOST_CHECK_EQUAL(response.fullyMatched(), false);
//
//     //second time through should match the fail response id
//     BOOST_CHECK_EQUAL(response.match(bytes), true);
//     BOOST_CHECK_EQUAL(response.fullyMatched(), true);
//     BOOST_CHECK_EQUAL(response.success(), false);
// }
//
// BOOST_AUTO_TEST_CASE(PageDownload_MatchFailResponse_BadId)
// {
//     std::shared_ptr<ResponseCollector> rc(new ResponseCollector);
//     PageDownload::Response response(rc);
//
//     Bytes resultBytes;
//     resultBytes.push_back(0x05);    //command id
//     resultBytes.push_back(0x22);    //fail response id
//
//     DataBuffer bytes(resultBytes);
//
//     BOOST_CHECK_EQUAL(response.match(bytes), true);    //matches cmd id
//     BOOST_CHECK_EQUAL(response.match(bytes), false);
// }

BOOST_AUTO_TEST_SUITE_END()
