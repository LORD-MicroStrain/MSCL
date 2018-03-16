/*******************************************************************************
Copyright(c) 2015-2018 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"
#include "MipNodeInfo.h"

#include "MipNode_Impl.h"
#include "mscl/Utils.h"

#include <string>

namespace mscl
{
    MipNodeInfo::MipNodeInfo(const MipNode_Impl* node):
        m_node(node),
        m_deviceInfo(std::bind(&MipNode_Impl::getDeviceInfo, m_node)),
        m_descriptors(std::bind(&MipNode_Impl::getDescriptorSets, m_node)),
        m_ahrsImuSampleRates(std::bind(&MipNode_Impl::supportedSampleRates, m_node, MipTypes::CLASS_AHRS_IMU)),
        m_gnssSampleRates(std::bind(&MipNode_Impl::supportedSampleRates, m_node, MipTypes::CLASS_GNSS)),
        m_estfilterSampleRates(std::bind(&MipNode_Impl::supportedSampleRates, m_node, MipTypes::CLASS_ESTFILTER)),
        m_displacementSampleRates(std::bind(&MipNode_Impl::supportedSampleRates, m_node, MipTypes::CLASS_DISPLACEMENT))
    {
    }

    MipNodeInfo::MipNodeInfo(const MipDeviceInfo& info,
                                       const std::vector<uint16>& supportedDescriptors,
                                       const SampleRates& sensorRates,
                                       const SampleRates& gnssRates, 
                                       const SampleRates& estFilterRates,
                                       const SampleRates& displacementRates) :
        m_deviceInfo(info),
        m_descriptors(supportedDescriptors),
        m_ahrsImuSampleRates(sensorRates),
        m_gnssSampleRates(gnssRates),
        m_estfilterSampleRates(estFilterRates),
        m_displacementSampleRates(displacementRates)
    {
    }

    const MipDeviceInfo& MipNodeInfo::deviceInfo() const
    {
        return *m_deviceInfo;
    }

    const std::vector<uint16>& MipNodeInfo::descriptors() const
    {
        return *m_descriptors;
    }

    const SampleRates& MipNodeInfo::supportedSampleRates(MipTypes::DataClass category) const
    {
        //set the SampleRates pointer depending on the category that is being asked for
        switch(category)
        {
            case MipTypes::CLASS_AHRS_IMU:
                return *m_ahrsImuSampleRates;

            case MipTypes::CLASS_GNSS:
                return *m_gnssSampleRates;

            case MipTypes::CLASS_ESTFILTER:
                return *m_estfilterSampleRates;

            case MipTypes::CLASS_DISPLACEMENT:
                return *m_displacementSampleRates;

            default:
                throw Error("Invalid DataClass.");
        }
    }
}