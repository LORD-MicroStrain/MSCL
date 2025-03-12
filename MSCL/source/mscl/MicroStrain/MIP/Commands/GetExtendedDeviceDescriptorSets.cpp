/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "mscl/MicroStrain/MIP/Commands/GetExtendedDeviceDescriptorSets.h"

#include "mscl/MicroStrain/MIP/MipDataField.h"
#include "mscl/MicroStrain/MIP/Commands/MIP_Commands.h"
#include "mscl/MicroStrain/MIP/Packets/MipPacketBuilder.h"

namespace mscl
{
    ByteStream GetExtendedDeviceDescriptorSets::buildCommand()
    {
        static const uint8 DescSet = 0x01;
        static const uint8 FieldDesc = 0x07;

        //create the field to add to the packet
        MipDataField field(Utils::make_uint16(DescSet, FieldDesc));

        //create a packet builder with with field
        MipPacketBuilder builder(DescSet, field);

        //build the packet and return the ByteStream result
        return builder.buildPacket();
    }

    GetExtendedDeviceDescriptorSets::Response::Response(std::weak_ptr<ResponseCollector> collector):
        GenericMipCommand::Response(MipTypes::CMD_GET_EXT_DESCRIPTOR_SETS, collector, true, true, "Get Extended Device Descriptor Sets")
    {}

    bool GetExtendedDeviceDescriptorSets::Response::match_data(const MipDataField& field)
    {
        MipPacket::Payload fieldData(field.fieldData());

        //verify the field is the minimum size
        /*if(fieldData.size() < 2)
        {
            return false;
        }*/

        //call match from the super class as well
        return GenericMipCommand::Response::match_data(field);
    }

    void GetExtendedDeviceDescriptorSets::Response::parseResponse(const GenericMipCmdResponse& response, std::vector<uint16>& descriptors) const
    {
        MIP_Commands::parseData_GetDeviceDescriptorSets(response, descriptors);
    }
}
