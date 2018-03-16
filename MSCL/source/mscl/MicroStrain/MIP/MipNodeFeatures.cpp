/*******************************************************************************
Copyright(c) 2015-2018 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"

#include <functional>
#include <memory>

#include "MipNodeFeatures.h"

namespace mscl
{
    MipNodeFeatures::MipNodeFeatures(const MipNodeInfo& info):
        m_nodeInfo(info)
    {
    }

    std::unique_ptr<MipNodeFeatures> MipNodeFeatures::create(const MipNodeInfo& info)
    {
        return std::unique_ptr<MipNodeFeatures>(new MipNodeFeatures(info));
    }

    bool MipNodeFeatures::isChannelField(uint16 descriptor)
    {
        uint8 msb = Utils::msb(descriptor);

        switch(msb)
        {
            //if the descriptor has any of these for the MSB, it is a channel field
            case MipTypes::CLASS_AHRS_IMU:
            case MipTypes::CLASS_GNSS:
            case MipTypes::CLASS_ESTFILTER:
                return true;

            default:
                return false;
        }
    }

    bool MipNodeFeatures::supportsCategory(MipTypes::DataClass category) const
    {
        const auto& descriptors = m_nodeInfo.descriptors();

        //loop over all the descriptors we have
        for(auto desc : descriptors)
        {
            //if ths MSB of the descriptor matches the DataClass being requested
            if(Utils::msb(static_cast<uint16>(desc)) == static_cast<uint16>(category))
            {
                //the device supports this category
                return true;
            }
        }

        //no descriptors found that match the requested category
        return false;
    }

    MipTypes::MipChannelFields MipNodeFeatures::supportedChannelFields(MipTypes::DataClass category) const
    {
        MipTypes::MipChannelFields result;

        const auto& descriptors = m_nodeInfo.descriptors();

        //loop over all the descriptors we have
        for(auto desc : descriptors)
        {
            //if ths MSB of the descriptor matches the DataClass being requested
            if(Utils::msb(static_cast<uint16>(desc)) == static_cast<uint16>(category))
            {
                //cast the descriptor to a ChannelField, and add it to the result container
                result.push_back(static_cast<MipTypes::ChannelField>(desc));
            }
        }

        if(result.size() == 0)
        {
            throw Error_NotSupported("The requested DataClass is not supported by this Node.");
        }

        return result;
    }

    bool MipNodeFeatures::supportsCommand(MipTypes::Command commandId) const
    {
        const auto& descriptors = m_nodeInfo.descriptors();
        return (std::find(descriptors.begin(), descriptors.end(), static_cast<uint16>(commandId)) != descriptors.end());
    }

    MipTypes::MipCommands MipNodeFeatures::supportedCommands() const
    {
        MipTypes::MipCommands result;

        auto& descriptors = m_nodeInfo.descriptors();

        for(const auto& desc : descriptors)
        {
            //anything that isn't a channel field, should be a command
            if(!isChannelField(desc))
            {
                result.push_back(static_cast<MipTypes::Command>(desc));
            }
        }

        return result;
    }

    const SampleRates& MipNodeFeatures::supportedSampleRates(MipTypes::DataClass category) const
    {
        return m_nodeInfo.supportedSampleRates(category);
    }
}