/*******************************************************************************
Copyright(c) 2015-2019 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"
#include "GetDeviceDescriptorSets.h"
#include "MIP_Commands.h"
#include "mscl/Utils.h"
#include "mscl/MicroStrain/MIP/MipDataField.h"
#include "mscl/MicroStrain/MIP/Packets/MipPacketBuilder.h"

namespace mscl
{

    ByteStream GetDeviceDescriptorSets::buildCommand()
    {
        static const uint8 DescSet = 0x01;
        static const uint8 FieldDesc = 0x04;

        //create the field to add to the packet
        MipDataField field(Utils::make_uint16(DescSet, FieldDesc));

        //create a packet builder with with field
        MipPacketBuilder builder(DescSet, field);

        //build the packet and return the ByteStream result
        return builder.buildPacket();
    }


    GetDeviceDescriptorSets::Response::Response(std::weak_ptr<ResponseCollector> collector):
        GenericMipCommand::Response(MipTypes::CMD_GET_DESCRIPTOR_SETS, collector, true, true, "Get Device Descriptor Sets")
    {}

    bool GetDeviceDescriptorSets::Response::match_data(const MipDataField& field)
    {
        MipPacket::Payload fieldData(field.fieldData());

        //verify the field is the minimum size
        if(fieldData.size() < 2)
        {
            return false;
        }

        //call match from the super class as well
        return GenericMipCommand::Response::match_data(field);
    }

    void GetDeviceDescriptorSets::Response::parseResponse(const GenericMipCmdResponse& response, std::vector<uint16>& descriptors) const
    {
        MIP_Commands::parseData_GetDeviceDescriptorSets(response, descriptors);
    }
}