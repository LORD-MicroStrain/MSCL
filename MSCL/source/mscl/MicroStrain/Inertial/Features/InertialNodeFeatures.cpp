/*******************************************************************************
Copyright(c) 2015-2017 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"

#include <functional>
#include <memory>

#include "InertialNodeFeatures.h"
#include "InertialNodeFeatures_3dm.h"
#include "InertialNodeFeatures_3dm_gx2.h"
#include "InertialNodeFeatures_3dm_dh3.h"
#include "InertialNodeFeatures_3dm_gx3_15.h"
#include "InertialNodeFeatures_3dm_gx3_25.h"
#include "InertialNodeFeatures_3dm_gx3_35.h"
#include "InertialNodeFeatures_3dm_gx3_45.h"
#include "InertialNodeFeatures_3dm_gx4_15.h"
#include "InertialNodeFeatures_3dm_gx4_25.h"
#include "InertialNodeFeatures_3dm_gx4_45.h"
#include "InertialNodeFeatures_3dm_rq1_45.h"
#include "InertialNodeFeatures_fasA.h"

namespace mscl
{
    InertialNodeFeatures::InertialNodeFeatures(const InertialNodeInfo& info):
        m_nodeInfo(info)
    {
    }

    std::unique_ptr<InertialNodeFeatures> InertialNodeFeatures::create(const InertialNodeInfo& info)
    {
        switch(info.deviceInfo().model)
        {
            case InertialModels::node_3dm:
                return std::unique_ptr<InertialNodeFeatures>(new InertialNodeFeatures_3dm(info));

            case InertialModels::node_fasA:
                return std::unique_ptr<InertialNodeFeatures>(new InertialNodeFeatures_fasA(info));

            case InertialModels::node_3dm_gx2:
                return std::unique_ptr<InertialNodeFeatures>(new InertialNodeFeatures_3dm_gx2(info));

            case InertialModels::node_3dm_dh3:
                return std::unique_ptr<InertialNodeFeatures>(new InertialNodeFeatures_3dm_dh3(info));

            case InertialModels::node_3dm_gx3_15:
                return std::unique_ptr<InertialNodeFeatures>(new InertialNodeFeatures_3dm_gx3_15(info));

            case InertialModels::node_3dm_gx3_25:
                return std::unique_ptr<InertialNodeFeatures>(new InertialNodeFeatures_3dm_gx3_25(info));

            case InertialModels::node_3dm_gx3_35:
                return std::unique_ptr<InertialNodeFeatures>(new InertialNodeFeatures_3dm_gx3_35(info));

            case InertialModels::node_3dm_gx3_45:
                return std::unique_ptr<InertialNodeFeatures>(new InertialNodeFeatures_3dm_gx3_45(info));

            case InertialModels::node_3dm_gx4_15:
                return std::unique_ptr<InertialNodeFeatures>(new InertialNodeFeatures_3dm_gx4_15(info));

            case InertialModels::node_3dm_gx4_25:
                return std::unique_ptr<InertialNodeFeatures>(new InertialNodeFeatures_3dm_gx4_25(info));

            case InertialModels::node_3dm_gx4_45:
                return std::unique_ptr<InertialNodeFeatures>(new InertialNodeFeatures_3dm_gx4_45(info));

            case InertialModels::node_3dm_rq1_45:
                return std::unique_ptr<InertialNodeFeatures>(new InertialNodeFeatures_3dm_rq1_45(info));

            //TODO: break these out to use their own NodeFeatures class
            //      currently just using the gx4-45 until more support is needed
            case InertialModels::node_3dm_gx5_10:
            case InertialModels::node_3dm_gx5_15:
            case InertialModels::node_3dm_gx5_25:
            case InertialModels::node_3dm_gx5_35:
            case InertialModels::node_3dm_gx5_45:
            case InertialModels::node_3dm_cv5_10:
            case InertialModels::node_3dm_cv5_15:
            case InertialModels::node_3dm_cv5_25:
            case InertialModels::node_3dm_cv5_45:
                return std::unique_ptr<InertialNodeFeatures>(new InertialNodeFeatures_3dm_gx4_45(info));

            default:
                //we don't know anything about this node, throw an exception
                throw Error_NotSupported("The Inertial Node model (" + Utils::toStr(info.deviceInfo().model) + ", " + info.deviceInfo().modelName + " ) is not supported by MSCL.");
        }
    }

    bool InertialNodeFeatures::isChannelField(uint16 descriptor)
    {
        uint8 msb = Utils::msb(descriptor);

        switch(msb)
        {
            //if the descriptor has any of these for the MSB, it is a channel field
            case InertialTypes::CATEGORY_SENSOR:
            case InertialTypes::CATEGORY_GNSS:
            case InertialTypes::CATEGORY_ESTFILTER:
                return true;

            default:
                return false;
        }
    }

    bool InertialNodeFeatures::supportsCategory(InertialTypes::InertialCategory category) const
    {
        const auto& descriptors = m_nodeInfo.descriptors();

        //loop over all the descriptors we have
        for(auto desc : descriptors)
        {
            //if ths MSB of the descriptor matches the InertialCategory being requested
            if(Utils::msb(static_cast<uint16>(desc)) == static_cast<uint16>(category))
            {
                //the device supports this category
                return true;
            }
        }

        //no descriptors found that match the requested category
        return false;
    }

    InertialTypes::InertialChannelFields InertialNodeFeatures::supportedChannelFields(InertialTypes::InertialCategory category) const
    {
        InertialTypes::InertialChannelFields result;

        const auto& descriptors = m_nodeInfo.descriptors();

        //loop over all the descriptors we have
        for(auto desc : descriptors)
        {
            //if ths MSB of the descriptor matches the InertialCategory being requested
            if(Utils::msb(static_cast<uint16>(desc)) == static_cast<uint16>(category))
            {
                //cast the descriptor to a ChannelField, and add it to the result container
                result.push_back(static_cast<InertialTypes::ChannelField>(desc));
            }
        }

        if(result.size() == 0)
        {
            throw Error_NotSupported("The requested InertialCategory is not supported by this Node.");
        }

        return result;
    }

    bool InertialNodeFeatures::supportsCommand(InertialTypes::Command commandId) const
    {
        const auto& descriptors = m_nodeInfo.descriptors();
        return (std::find(descriptors.begin(), descriptors.end(), static_cast<uint16>(commandId)) != descriptors.end());
    }

    InertialTypes::InertialCommands InertialNodeFeatures::supportedCommands() const
    {
        InertialTypes::InertialCommands result;

        auto& descriptors = m_nodeInfo.descriptors();

        for(const auto& desc : descriptors)
        {
            //anything that isn't a channel field, should be a command
            if(!isChannelField(desc))
            {
                result.push_back(static_cast<InertialTypes::Command>(desc));
            }
        }

        return result;
    }

    const SampleRates& InertialNodeFeatures::supportedSampleRates(InertialTypes::InertialCategory category) const
    {
        return m_nodeInfo.supportedSampleRates(category);
    }
}