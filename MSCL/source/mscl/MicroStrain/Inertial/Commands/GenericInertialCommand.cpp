/*******************************************************************************
Copyright(c) 2015-2017 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"
#include "GenericInertialCommand.h"

#include "mscl/Utils.h"
#include "mscl/MicroStrain/Inertial/InertialDataField.h"
#include "mscl/MicroStrain/Inertial/Packets/InertialPacketBuilder.h"
#include "mscl/MicroStrain/Inertial/Packets/InertialPacket.h"

namespace mscl
{
    GenericInertialCommandResponse::GenericInertialCommandResponse():
        InertialCmdResponse()
    {
    }

    GenericInertialCommandResponse::GenericInertialCommandResponse(ResponsePattern::State state, bool success, InertialPacket::MipAckNack errorCode, std::string cmdName, ByteStream data):
        InertialCmdResponse(state, success, errorCode, cmdName),
        m_data(data)
    {
    }

    GenericInertialCommandResponse GenericInertialCommandResponse::ResponseSuccess(const std::string& cmdName, ByteStream data /*= ByteStream()*/)
    {
        return GenericInertialCommandResponse(ResponsePattern::STATE_SUCCESS, true, InertialPacket::MIP_ACK_NACK_ERROR_NONE, cmdName, data);
    }

    GenericInertialCommandResponse GenericInertialCommandResponse::ResponseFail(ResponsePattern::State errorState, InertialPacket::MipAckNack errorCode, const std::string& cmdName)
    {
        return GenericInertialCommandResponse(errorState, false, errorCode, cmdName, ByteStream());
    }

    ByteStream GenericInertialCommandResponse::data() const
    {
        //return the ByteStream containing the data from the response
        return m_data;
    }


    ByteStream GenericInertialCommand::buildCommand(uint8 descSetId, uint8 cmdByte, const Bytes& fieldData) //fieldData=Bytes()
    {
        //create the field to add to the packet
        InertialDataField field(Utils::make_uint16(descSetId, cmdByte), fieldData);

        //create a packet builder with the field
        InertialPacketBuilder builder(descSetId, field);

        //build the packet and return the ByteStream result
        return builder.buildPacket();
    }

    ByteStream GenericInertialCommand::buildCommand(InertialTypes::Command commandId, const Bytes& fieldData) //fieldData=Bytes())
    {
        uint16 field = static_cast<uint16>(commandId);

        //split the field id and call the other buildCommand function
        return buildCommand(Utils::msb(field), Utils::lsb(field), fieldData);
    }

    GenericInertialCommand::Response::Response(std::weak_ptr<ResponseCollector> collector, bool ackNackResponse, bool dataResponse, std::string cmdName):
        ResponsePattern(collector),
        m_ackNackResponse(ackNackResponse),
        m_dataResponse(dataResponse),
        m_commandName(cmdName)
    {
    }

    uint8 GenericInertialCommand::Response::fieldDataByte() const
    {
        return 0;
    }

    uint8 GenericInertialCommand::Response::descSetByte() const
    { 
        //the descriptor set byte is the MSB of the commandId value
        return Utils::msb(static_cast<uint16>(commandId())); 
    }

    uint8 GenericInertialCommand::Response::cmdByte() const
    { 
        //the command byte is the LSB of the commandId value
        return Utils::lsb(static_cast<uint16>(commandId()));
    }

    uint8 GenericInertialCommand::Response::fieldAckNackByte() const 
    { 
        return FIELD_ACK_NACK_BYTE; 
    }

    bool GenericInertialCommand::Response::match(const InertialDataField& field)
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

    bool GenericInertialCommand::Response::match_ackNack(const InertialDataField& field)
    {
        //verify that we are even expecting an ack/nack field
        if(!m_ackNackResponse)
        {
            return false;
        }

        //the length of every ack/nack field
        static const uint8 FIELD_DATA_LEN = 2;

        //get the field bytes
        InertialPacket::Payload fieldBytes(field.fieldData());

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
        InertialPacket::MipAckNack errorCode = static_cast<InertialPacket::MipAckNack>(fieldBytes.read_uint8(1));

        //if there was an error
        if(errorCode != InertialPacket::MIP_ACK_NACK_ERROR_NONE)
        {
            //set the response to a failure
            m_result = GenericInertialCommandResponse::ResponseFail(STATE_FAIL, errorCode, m_commandName);

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
                m_result = GenericInertialCommandResponse::ResponseSuccess(m_commandName);

                //we full matched the response
                m_fullyMatched = true;

                //notify that the response was matched
                m_matchCondition.notify();
            }
        }

        return true;
    }

    bool GenericInertialCommand::Response::match_data(const InertialDataField& field)
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
        m_result = GenericInertialCommandResponse::ResponseSuccess(m_commandName, field.fieldData());

        //getting this field means we have fully matched
        m_fullyMatched = true;

        //notify that the response was matched
        m_matchCondition.notify();

        return true;
    }

    bool GenericInertialCommand::Response::wait(uint64 timeout)
    {
        //perform a timedWait on the matchCondition, returning the result
        bool success = m_matchCondition.timedWait(timeout);

        //if we failed to get a good response
        if(!success)
        {
            //set the result to a fail response due to a timeout
            m_result = GenericInertialCommandResponse::ResponseFail(STATE_FAIL_TIMEOUT, InertialPacket::MIP_ACK_NACK_ERROR_NONE, m_commandName);
        }

        //return the result of the timedWait
        return success;
    }

    GenericInertialCommandResponse GenericInertialCommand::Response::result()
    {
        return m_result;
    }
}