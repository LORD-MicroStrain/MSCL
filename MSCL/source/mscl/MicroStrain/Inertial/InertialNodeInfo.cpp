/*******************************************************************************
Copyright(c) 2015-2017 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"
#include "InertialNodeInfo.h"

#include "InertialNode_Impl.h"
#include "mscl/Utils.h"

#include <string>

namespace mscl
{
    InertialNodeInfo::InertialNodeInfo(const InertialNode_Impl* node):
        m_node(node),
        m_deviceInfo(std::bind(&InertialNode_Impl::getDeviceInfo, m_node)),
        m_descriptors(std::bind(&InertialNode_Impl::getDescriptorSets, m_node)),
        m_sensorSampleRates(std::bind(&InertialNode_Impl::supportedSampleRates, m_node, InertialTypes::CATEGORY_SENSOR)),
        m_gnssSampleRates(std::bind(&InertialNode_Impl::supportedSampleRates, m_node, InertialTypes::CATEGORY_GNSS)),
        m_estfilterSampleRates(std::bind(&InertialNode_Impl::supportedSampleRates, m_node, InertialTypes::CATEGORY_ESTFILTER))
    {
    }

    InertialNodeInfo::InertialNodeInfo(const InertialDeviceInfo& info,
                                       const std::vector<uint16>& supportedDescriptors,
                                       const SampleRates& sensorRates,
                                       const SampleRates& gnssRates, 
                                       const SampleRates& estFilterRates) :
        m_deviceInfo(info),
        m_descriptors(supportedDescriptors),
        m_sensorSampleRates(sensorRates),
        m_gnssSampleRates(gnssRates),
        m_estfilterSampleRates(estFilterRates)
    {
    }

    const InertialDeviceInfo& InertialNodeInfo::deviceInfo() const
    {
        return *m_deviceInfo;
    }

    const std::vector<uint16>& InertialNodeInfo::descriptors() const
    {
        return *m_descriptors;
    }

    const SampleRates& InertialNodeInfo::supportedSampleRates(InertialTypes::InertialCategory category) const
    {
        //set the SampleRates pointer depending on the category that is being asked for
        switch(category)
        {
            case InertialTypes::CATEGORY_SENSOR:
                return *m_sensorSampleRates;

            case InertialTypes::CATEGORY_GNSS:
                return *m_gnssSampleRates;

            case InertialTypes::CATEGORY_ESTFILTER:
                return *m_estfilterSampleRates;

            default:
                throw Error("Invalid InertialCategory.");
        }
    }
}