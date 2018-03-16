/*******************************************************************************
Copyright(c) 2015-2018 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"
#include "mscl/MicroStrain/MIP/Commands/GenericMipCommand.h"

#include "mscl/Utils.h"
#include "mscl/MicroStrain/MIP/MipDataField.h"
#include "mscl/MicroStrain/MIP/Packets/MipPacketBuilder.h"
#include "mscl/MicroStrain/MIP/Packets/MipPacket.h"

namespace mscl
{
    GenericMipCmdResponse::GenericMipCmdResponse():
        MipCmdResponse()
    {
    }

    GenericMipCmdResponse::GenericMipCmdResponse(ResponsePattern::State state, bool success, MipPacket::MipAckNack errorCode, std::string cmdName, ByteStream data):
        MipCmdResponse(state, success, errorCode, cmdName),
        m_data(data)
    {
    }

    GenericMipCmdResponse GenericMipCmdResponse::ResponseSuccess(const std::string& cmdName, ByteStream data /*= ByteStream()*/)
    {
        return GenericMipCmdResponse(ResponsePattern::STATE_SUCCESS, true, MipPacket::MIP_ACK_NACK_ERROR_NONE, cmdName, data);
    }

    GenericMipCmdResponse GenericMipCmdResponse::ResponseFail(ResponsePattern::State errorState, MipPacket::MipAckNack errorCode, const std::string& cmdName)
    {
        return GenericMipCmdResponse(errorState, false, errorCode, cmdName, ByteStream());
    }

    ByteStream GenericMipCmdResponse::data() const
    {
        //return the ByteStream containing the data from the response
        return m_data;
    }


    ByteStream GenericMipCommand::buildCommand(uint8 descSetId, uint8 cmdByte, const Bytes& fieldData) //fieldData=Bytes()
    {
        //create the field to add to the packet
        MipDataField field(Utils::make_uint16(descSetId, cmdByte), fieldData);

        //create a packet builder with the field
        MipPacketBuilder builder(descSetId, field);

        //build the packet and return the ByteStream result
        return builder.buildPacket();
    }

    ByteStream GenericMipCommand::buildCommand(MipTypes::Command commandId, const Bytes& fieldData) //fieldData=Bytes())
    {
        uint16 field = static_cast<uint16>(commandId);

        //split the field id and call the other buildCommand function
        return buildCommand(Utils::msb(field), Utils::lsb(field), fieldData);
    }

    ByteStream GenericMipCommand::buildCommand(const Bytes& fieldData) //fieldData=Bytes())
    {
        uint16 field = static_cast<uint16>(commandId());

        //split the field id and call the other buildCommand function
        return buildCommand(Utils::msb(field), Utils::lsb(field), fieldData);
    }

    GenericMipCommand::Response::Response(const MipTypes::Command& command, bool ackNackResponse, bool dataResponse, std::string cmdName):
        ResponsePattern(),
        m_ackNackResponse(ackNackResponse),
        m_dataResponse(dataResponse),
        m_command(command),
        m_commandName(cmdName)
    {
    }

    GenericMipCommand::Response::Response(const MipTypes::Command& command, std::weak_ptr<ResponseCollector> collector,
                                               bool ackNackResponse, bool dataResponse, const std::string& cmdName, uint8 fieldDataByte):
        ResponsePattern(collector),
        m_ackNackResponse(ackNackResponse),
        m_dataResponse(dataResponse),
        m_command(command),
        m_commandName(cmdName),
        m_fieldDataByte(fieldDataByte)
    {
    }

    uint8 GenericMipCommand::Response::fieldDataByte() const
    {
        return m_fieldDataByte;
    }

    uint8 GenericMipCommand::Response::descSetByte() const
    { 
        //the descriptor set byte is the MSB of the commandId value
        return Utils::msb(static_cast<uint16>(m_command));
    }

    uint8 GenericMipCommand::Response::cmdByte() const
    { 
        //the command byte is the LSB of the commandId value
        return Utils::lsb(static_cast<uint16>(m_command));
    }

    uint8 GenericMipCommand::Response::fieldAckNackByte() const 
    { 
        return FIELD_ACK_NACK_BYTE; 
    }

    bool GenericMipCommand::Response::match(const MipDataField& field)
    {
        //get the field descriptor from the given field
        uint8 fieldDesc = field.fieldDescriptor();

        //if the field descriptor matches the ack/nack id
        if(fieldDesc == fieldAckNackByte())
        {
            //return the result of trying to match the ack/nack field
            return match_ackNack(field);
        }

        //if we are looking for a data response field
        if(m_dataResponse)
        {
            //if the field descriptor matches the data id
            if(fieldDesc == fieldDataByte())
            {
                //return the result of trying to match the data field
                return match_data(field);
            }
        }

        //doesn't match anything
        return false;
    }

    bool GenericMipCommand::Response::match_ackNack(const MipDataField& field)
    {
        //verify that we are even expecting an ack/nack field
        if(!m_ackNackResponse)
        {
            return false;
        }

        //the length of every ack/nack field
        static const uint8 FIELD_DATA_LEN = 2;

        //get the field bytes
        MipPacket::Payload fieldBytes(field.fieldData());

		//check the main bytes of the packet
		if(field.descriptorSet()    != this->descSetByte()        ||    //descriptor set
           fieldBytes.size()         < FIELD_DATA_LEN            ||    //field data length
           fieldBytes.read_uint8(0) != this->cmdByte()                //command echo
          )
        {
            //failed to match some of the bytes
            return false;
        }

        //if we made it here, the packet matches the response pattern

        //read the error code
        MipPacket::MipAckNack errorCode = static_cast<MipPacket::MipAckNack>(fieldBytes.read_uint8(1));

        //if there was an error
        if(errorCode != MipPacket::MIP_ACK_NACK_ERROR_NONE)
        {
            //set the response to a failure
            m_result = GenericMipCmdResponse::ResponseFail(STATE_FAIL, errorCode, m_commandName);

            //a NACK means we won't get any other fields for this response
            m_fullyMatched = true;

            //notify that the response was matched
            m_matchCondition.notify();
        }
        else
        {
            //if we aren't expecting a data response (only an ack/nack)
            if(!m_dataResponse)
            {
                m_result = GenericMipCmdResponse::ResponseSuccess(m_commandName);

                //we fully matched the response
                m_fullyMatched = true;

                //notify that the response was matched
                m_matchCondition.notify();
            }
        }

        return true;
    }

    bool GenericMipCommand::Response::match_data(const MipDataField& field)
    {
        //verify that we are even expecting a data field
        if(!m_dataResponse)
        {
            return false;
        }

        //check the main bytes of the packet
        if(field.descriptorSet()    != this->descSetByte() ||    //descriptor set byte
           field.fieldDescriptor()    != this->fieldDataByte())    //field data byte
        {
            //failed to match some of the bytes
            return false;
        }

        //if we made it here, the packet matches the response pattern

        //set the response to a success
        m_result = GenericMipCmdResponse::ResponseSuccess(m_commandName, field.fieldData());

        //getting this field means we have fully matched
        m_fullyMatched = true;

        //notify that the response was matched
        m_matchCondition.notify();

        return true;
    }

    bool GenericMipCommand::Response::wait(uint64 timeout)
    {
        //perform a timedWait on the matchCondition, returning the result
        bool success = m_matchCondition.timedWait(timeout);

        //if we failed to get a good response
        if(!success)
        {
            //set the result to a fail response due to a timeout
            m_result = GenericMipCmdResponse::ResponseFail(STATE_FAIL_TIMEOUT, MipPacket::MIP_ACK_NACK_ERROR_NONE, m_commandName);
        }

        //return the result of the timedWait
        return success;
    }

    GenericMipCmdResponse GenericMipCommand::Response::result()
    {
        return m_result;
    }
}