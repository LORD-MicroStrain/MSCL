/*******************************************************************************
Copyright(c) 2015-2017 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"

#include "BaseStation_WriteEeprom.h"
#include "WirelessProtocol.h"
#include "mscl/MicroStrain/ChecksumBuilder.h"

namespace mscl
{
    ByteStream BaseStation_WriteEeprom::buildCommand(uint16 eepromAddress, uint16 valueToWrite)
    {
        //build the command ByteStream
        ByteStream cmd;

        cmd.append_uint8(WirelessProtocol::cmdId_base_writeEeprom);
        cmd.append_uint16(eepromAddress);                        //eeprom address to write to
        cmd.append_uint16(valueToWrite);                        //value to write to eeprom
        cmd.append_uint16(cmd.calculateSimpleChecksum(1, 4));    //checksum

        return cmd;
    }


    BaseStation_WriteEeprom::Response::Response(uint16 valueToWrite, std::weak_ptr<ResponseCollector> collector):
        WirelessResponsePattern(collector, WirelessProtocol::cmdId_base_writeEeprom, WirelessProtocol::BASE_STATION_ADDRESS),
        m_valueWritten(valueToWrite)
    {
    }

    bool BaseStation_WriteEeprom::Response::matchSuccessResponse(DataBuffer& data)
    {
        const uint16 TOTAL_SUCCESS_BYTES = 5;

        //create a save point with the data
        ReadBufferSavePoint savePoint(&data);

        //if there aren't enough bytes in the buffer to match the response
        if(data.bytesRemaining() < TOTAL_SUCCESS_BYTES) 
        { 
            return false; 
        }

        //if the first byte isn't the command byte
        if(data.read_uint8() != WirelessProtocol::cmdId_base_writeEeprom)
        { 
            return false; 
        }

        //the next two bytes should be the eeprom value we wrote in the command
        uint16 eepromVal = data.read_uint16();

        //if the eeprom value isn't the one we tried to write, then this packet is not correct
        if(eepromVal != m_valueWritten)
        {
            return false;
        }


        //build the ChecksumBuilder with the necessary bytes
        ChecksumBuilder checksum;
        checksum.append_uint16(eepromVal);    //eeprom value

        //if the checksum doesn't match
        if(data.read_uint16() != checksum.simpleChecksum()) 
        { 
            return false; 
        }


        //if we made it this far, we successfully matched everything

        //commit the current read position
        savePoint.commit();

        return true;
    }

    bool BaseStation_WriteEeprom::Response::matchFailResponse(DataBuffer& data)
    {
        const uint16 TOTAL_FAILURE_BYTES = 1;

        //create a save point with the data
        ReadBufferSavePoint savePoint(&data);

        //if there aren't enough bytes in the buffer to match the response
        if(data.bytesRemaining() < TOTAL_FAILURE_BYTES) 
        {
            return false; 
        }

        //if the first byte isn't the fail byte
        if(data.read_uint8() != 0x21) 
        { 
            return false; 
        }

        //if we made it this far, we successfully matched everything

        //commit the current read position
        savePoint.commit();

        return true;
    }
}