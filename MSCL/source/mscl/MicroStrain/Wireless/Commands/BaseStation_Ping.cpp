/*****************************************************************************************
**          Copyright(c) 2015-2022 Parker Hannifin Corp. All rights reserved.           **
**                                                                                      **
**    MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.    **
*****************************************************************************************/

#include "stdafx.h"

#include "BaseStation_Ping.h"
#include "WirelessProtocol.h"

namespace mscl
{

    ByteStream BaseStation_Ping::buildCommand()
    {
        //build the command ByteStream
        ByteStream cmd;
        cmd.append_uint8(WirelessProtocol::cmdId_basePing);

        return cmd;
    }

    BaseStation_Ping::Response::Response(std::weak_ptr<ResponseCollector> collector):
        WirelessResponsePattern(collector, WirelessProtocol::cmdId_basePing, WirelessProtocol::BASE_STATION_ADDRESS)
    {
    }

    bool BaseStation_Ping::Response::matchSuccessResponse(DataBuffer& data)
    {
        const uint16 TOTAL_BYTES = 1;

        //if there aren't enough bytes in the buffer to match the response
        if(data.bytesRemaining() < TOTAL_BYTES)
        {
            //not a good response
            m_success = false;
            return false;
        }

        //create a save point with the data
        ReadBufferSavePoint savePoint(&data);

        //single byte response of 0x01
        if(data.read_uint8() != WirelessProtocol::cmdId_basePing)
        {
            //not a good response
            m_success = false;
            return false;
        }

        //if we made it this far, the bytes match the response

        //commit the current read position
        savePoint.commit();

        return true;
    }
}