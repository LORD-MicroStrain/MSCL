/*****************************************************************************************
**          Copyright(c) 2015-2024 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.    **
*****************************************************************************************/

#include "stdafx.h"
#include "ReadSingleSensor.h"
#include "WirelessProtocol.h"
#include "mscl/MicroStrain/ChecksumBuilder.h"

namespace mscl
{
    ByteStream ReadSingleSensor::buildCommand(NodeAddress nodeAddress, uint8 channelNumber)
    {
        //build the command ByteStream
        ByteStream cmd;
        cmd.append_uint8(WirelessProtocol::cmdId_readSingleSensor); //Command ID
        cmd.append_uint16(static_cast<uint16>(nodeAddress));        //Node address    (2 bytes)
        cmd.append_uint8(0x01);                                     //Command Byte
        cmd.append_uint8(channelNumber);                            //Channel number

        return cmd;
    }

    ReadSingleSensor::Response::Response(std::weak_ptr<ResponseCollector> collector):
        WirelessResponsePattern(collector, WirelessProtocol::cmdId_readSingleSensor, 0),    //note: passing 0 because this response doesn't check node address :(
        m_sensorValue(0)
    {
    }

    bool ReadSingleSensor::Response::matchSuccessResponse(DataBuffer& data)
    {
        const uint16 TOTAL_BYTES = 5;

        //if there aren't enough bytes in the buffer to match the response
        if(data.bytesRemaining() < TOTAL_BYTES)
        {
            //not a good response
            m_success = false;
            return false;
        }

        //create a save point with the data
        ReadBufferSavePoint savePoint(&data);
        
        //verify the command id
        if(data.read_uint8() != 0x03)
        {
            //not a good response
            m_success = false;
            return false;
        }

        uint16 sensorVal = data.read_uint16();

        ChecksumBuilder checksum;
        checksum.append_uint16(sensorVal);    //value of the requested channel

        //verify the checksum (only a checksum on the actual data value)
        if(checksum.simpleChecksum() != data.read_uint16())
        {
            //not a good response
            m_success = false;
            return false;
        }

        //if we made it this far, the bytes match the expected response

        m_sensorValue = sensorVal;

        //commit the current read position
        savePoint.commit();

        return true;
    }

    uint16 ReadSingleSensor::Response::sensorValue() const
    {
        return m_sensorValue;
    }
}