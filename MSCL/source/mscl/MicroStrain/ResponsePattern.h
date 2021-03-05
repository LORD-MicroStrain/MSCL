/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/

#pragma once

#include "mscl/Types.h"
#include "ByteStream.h"
#include "mscl/TimedCondition.h"
#include "mscl/TimeSpan.h"
#include <memory>
#include <mutex>

namespace mscl
{
    class DataBuffer;
    class WirelessPacket;
    class MipDataField;
    class ResponseCollector;

    //Class: ResponsePattern
    //    A pattern matching the expected response from a device command (Base Class).
    //
    //Creating your own command/response:
    //    - Create a custom "Response" class that inherits from this class.
    //    - Create a custom version of one of the "match" functions that applies to your command.
    //    - In the match function, if the bytes match the expected response, return true.
    //    - Set m_success to whether the command succeeded (match a success response), or false (matched a fail response).
    //    - Set m_fullyMatched to true when all packets/bytes have been matched. Set it to false if the packet was matched
    //      but there are still more packets/bytes remaining (the case when 1 command has multiple responses before it is complete).
    class ResponsePattern
    {
    public:
        //=====================================================================================================
        //Enums: Response State
        //    STATE_WAITING            - The response has not yet been received.
        //    STATE_FAIL_TIMEOUT        - The response has timed out
        //    STATE_FAIL                - The response was a fail response
        //    STATE_SUCCESS            - The response was successfully received
        //=====================================================================================================
        enum State
        {
            STATE_WAITING,
            STATE_FAIL_TIMEOUT,
            STATE_FAIL,
            STATE_SUCCESS
        };

    public:
        //Default Constructor: ResponsePattern
        //    Creates a default constructor ResponsePattern.
        //    Note: You will need to use the <setResponseCollector> function before being used.
        ResponsePattern();

        //Constructor: ResponsePattern
        //    Creates a ResponsePattern attached to a collector.
        //
        //Parameters:
        //    collector - The <ResponseCollector> to register and unregister this response with.
        explicit ResponsePattern(std::weak_ptr<ResponseCollector> collector);

        //Destructor: ResponsePattern
        //    Destroys the ResponsePattern and unregisters this response from its <ResponseCollector>
        virtual ~ResponsePattern();

        //Function: setResponseCollector
        //    Sets the <ResponseCollector> for this pattern, and registers this pattern with the collector.
        //
        //Parameters:
        //    collector - The <ResponseCollector> to assign this pattern to.
        void setResponseCollector(std::weak_ptr<ResponseCollector> collector);

    private:
        ResponsePattern(const ResponsePattern&);                //copy constructor disabled
        ResponsePattern& operator=(const ResponsePattern&);        //assignement operator disabled

    private:
        //Variable: m_collector
        //    The <ResponseCollector> that holds this response pattern
        std::weak_ptr<ResponseCollector> m_collector;

    protected:
        //Variable: m_matchCondition
        //    The <TimedCondition> for matching the response pattern
        TimedCondition m_matchCondition;

        //Variable: m_parsingMutex
        //    A mutex used for parsing data, which may modify the fullMatched and success flags
        mutable std::mutex m_parsingMutex;

        //Variable: m_fullyMatched
        //    Whether or not the ResponsePattern has been fully matched. 
        //    Some commands have multiple parts to their response. This will not be true until all required parts have been matched.
        bool m_fullyMatched;

        //Variable: m_success
        //    Whether or not the command was a success (a success response was matched).
        bool m_success;

    protected:
        //Function: throwIfFailed
        //    Throws an <Error> if the command has failed (if m_success is false).
        //    Otherwise, no action is taken.
        //
        //Parameters:
        //    commandName - The name of the command to put in the exception if necessary.
        void throwIfFailed(const std::string& commandName) const;

        virtual bool matchSuccessResponse(DataBuffer& data);
        virtual bool matchSuccessResponse(const WirelessPacket& packet);
        virtual bool matchFailResponse(DataBuffer& data);
        virtual bool matchFailResponse(const WirelessPacket& packet);
        virtual bool matchBaseReceivedResponse(const WirelessPacket& packet);

    public:
        //Function: match
        //    Checks if the bytes passed in match the response pattern from their current read position.
        //    If data was matched, the read position in the DataBuffer will be updated to be passed the bytes read.
        //
        //Parameters:
        //    data - The <DataBuffer> containing the bytes in which to try to find the pattern
        //
        //Returns:
        //    true if the response pattern was found, false otherwise.
        virtual bool match(DataBuffer& data);

        //Function: match
        //    Checks if the <WirelessPacket> passed in matches the response pattern's bytes
        //
        //Parameters:
        //    packet - The <WirelessPacket> in which to try to find the pattern
        //
        //Returns:
        //    true if the packet matches a response pattern, false otherwise.
        virtual bool match(const WirelessPacket& packet);

        //Function: match
        //    Checks if the <MipDataField> passed in matches the response pattern's bytes
        //
        //Parameters:
        //    field - The <MipDataField> in which to try to find the pattern
        //
        //Returns:
        //    true if the packet matches a response pattern, false otherwise.
        virtual bool match(const MipDataField& field);

        //Function: wait
        //    Waits for a certain amount of time for the response pattern to be matched
        //
        //Parameters:
        //    timeout - The maximum amount of time (in milliseconds) to wait until the command times out and returns, if not found first.
        //
        //Returns:
        //    true if the response pattern was matched, false otherwise
        virtual bool wait(uint64 timeout);

        //Function: fullyMatched
        //    Checks whether the response pattern has been fully matched.
        //    Some commands have multiple parts to their response. This checks whether all responses have been satisfied.
        //
        //Returns:
        //    true if the response is fully matched, false otherwise
        bool fullyMatched() const;

        //Function: success
        //    Gets whether or not the command was a success (a success response was matched). 
        //
        //Returns:
        //    true if the command was a success, false otherwise.
        bool success() const;
    };
}