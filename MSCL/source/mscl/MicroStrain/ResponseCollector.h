/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include <memory>
#include <mutex>
#include <vector>

namespace mscl
{
    class Connection;
    class DataBuffer;
    class WirelessPacket;
    class MipDataField;
    class ResponsePattern;

    struct ResponseInfo
    {
        ResponsePattern* pattern;
        std::size_t minBytePosition;

        ResponseInfo(ResponsePattern* responsePattern, std::size_t minBytePos):
          pattern(responsePattern),
          minBytePosition(minBytePos)
        { }
    };

    //Class: ResponseCollector
    //    Stores all the expected command responses
    class ResponseCollector
    {
    public:
        //Default Constructor: ResponseCollector
        //    Creates a ResponseCollector object
        ResponseCollector();

    private:
        ResponseCollector(const ResponseCollector&);                                //copy constructor disabled
        ResponseCollector& operator=(const ResponseCollector&);                     //disable assignment operator
        //std::shared_ptr<ResponseCollector> operator=(const ResponseCollector&);     //assignement operator disabled

    private:
        //Variable: m_expectedResponses
        //    Holds the response patterns that, if matched, belong to this collector
        std::vector<ResponseInfo> m_expectedResponses;

        //Variable: m_responseMutex
        //    A mutex used for thread safety when accessing/modifying the m_expectedResponses vector
        std::mutex m_responseMutex;

        //Variable: m_connection
        //    The <Connection> pointer to use for retrieving byte information.
        Connection* m_connection;

    public:
        //Function: setConnection
        //    Sets the connection points to use for retrieving byte information.
        //
        //Parameters:
        //    connection - The <Connection> pointer to use for retrieving byte info.
        void setConnection(Connection* connection);

        //Function: registerResponse
        //    Registers a <ResponsePattern> with this collector
        //
        //Parameters:
        //    response - The <ResponsePattern> to register
        void registerResponse(ResponsePattern* response);

        //Function: unregisterResponse
        //    Unregisters a <ResponsePattern> that is within this collector
        //
        //Parameters:
        //    response - A pointer to the <ResponsePattern> to unregister
        void unregisterResponse(ResponsePattern* response);

        //Function: waitingForResponse
        //    Gets whether or not this response collector currently has any response patterns to match
        //
        //Returns:
        //    true if the response collector has any response patterns to match, false otherwise
        bool waitingForResponse();

        void adjustResponsesMinBytePos(std::size_t bytesToSubtract);

        //Function: matchExpected
        //    Checks to see if the byte(s) passed in match any of the expected responses
        //
        //Parameters:
        //    data - The <DataBuffer> containing the bytes to be read and compared against the
        //            expected responses, starting at the current read position.
        //
        //Returns:
        //    true if the byte(s) matched an expected response, false otherwise
        bool matchExpected(DataBuffer& data);

        //Function: matchExpected
        //    Checks to see if the wireless packet passed in matches any of the expected responses
        //
        //Parameters:
        //    packet - The <WirelessPacket> to be compared against the expected responses
        //    lastReadPos - The last read position where the packet was parsed from.
        //
        //Returns:
        //    true if the packet matched an expected response, false otherwise
        bool matchExpected(const WirelessPacket& packet, std::size_t lastReadPos);

        //Function: matchExpected
        //    Checks to see if the <MipDataField> passed in matches any of the expected responses
        //
        //Parameters:
        //    field - The <MipDataField> to be compared against the expected responses
        //
        //Returns:
        //    true if the packet matched an expected response, false otherwise
        bool matchExpected(MipDataField& field);
    };
}