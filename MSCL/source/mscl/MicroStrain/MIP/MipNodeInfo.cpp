/*****************************************************************************************
**          Copyright(c) 2015-2022 Parker Hannifin Corp. All rights reserved.           **
**                                                                                      **
**    MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.    **
*****************************************************************************************/

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
        m_sampleRates({
            { MipTypes::CLASS_AHRS_IMU, Utils::Lazy<SampleRates>(std::bind(&MipNode_Impl::supportedSampleRates, m_node, MipTypes::CLASS_AHRS_IMU))},
            { MipTypes::CLASS_GNSS, Utils::Lazy<SampleRates>(std::bind(&MipNode_Impl::supportedSampleRates, m_node, MipTypes::CLASS_GNSS)) },
            { MipTypes::CLASS_ESTFILTER, Utils::Lazy<SampleRates>(std::bind(&MipNode_Impl::supportedSampleRates, m_node, MipTypes::CLASS_ESTFILTER)) },
            { MipTypes::CLASS_DISPLACEMENT, Utils::Lazy<SampleRates>(std::bind(&MipNode_Impl::supportedSampleRates, m_node, MipTypes::CLASS_DISPLACEMENT)) },
            { MipTypes::CLASS_GNSS1, Utils::Lazy<SampleRates>(std::bind(&MipNode_Impl::supportedSampleRates, m_node, MipTypes::CLASS_GNSS1)) },
            { MipTypes::CLASS_GNSS2, Utils::Lazy<SampleRates>(std::bind(&MipNode_Impl::supportedSampleRates, m_node, MipTypes::CLASS_GNSS2)) },
            { MipTypes::CLASS_GNSS3, Utils::Lazy<SampleRates>(std::bind(&MipNode_Impl::supportedSampleRates, m_node, MipTypes::CLASS_GNSS3)) },
            { MipTypes::CLASS_GNSS4, Utils::Lazy<SampleRates>(std::bind(&MipNode_Impl::supportedSampleRates, m_node, MipTypes::CLASS_GNSS4)) },
            { MipTypes::CLASS_GNSS5, Utils::Lazy<SampleRates>(std::bind(&MipNode_Impl::supportedSampleRates, m_node, MipTypes::CLASS_GNSS5)) },
        }),
        m_receiverInfo(std::bind(&MipNode_Impl::getGnssReceiverInfo, m_node)),
		m_eventActionInfo(std::bind(&MipNode_Impl::getEventInfo, m_node, EventSupportInfo::ACTIONS)),
        m_eventTriggerInfo(std::bind(&MipNode_Impl::getEventInfo, m_node, EventSupportInfo::TRIGGERS))
    {
    }

    MipNodeInfo::MipNodeInfo(const MipDeviceInfo& info,
                                const std::vector<uint16>& supportedDescriptors,
                                const std::map<MipTypes::DataClass, SampleRates>& sampleRates) :
        m_deviceInfo(info),
        m_descriptors(supportedDescriptors),
        m_receiverInfo({}),
		m_eventActionInfo({}),
		m_eventTriggerInfo({})
    {
        for (auto dataClass : sampleRates)
        {
            m_sampleRates.emplace(dataClass.first, dataClass.second);
        }
    }

    const MipDeviceInfo& MipNodeInfo::deviceInfo() const
    {
        return *m_deviceInfo;
    }

    const std::vector<uint16>& MipNodeInfo::descriptors() const
    {
        return *m_descriptors;
    }

    const SampleRates& MipNodeInfo::supportedSampleRates(MipTypes::DataClass dataClass) const
    {
        if (m_sampleRates.find(dataClass) == m_sampleRates.end())
        {
            throw Error("Invalid DataClass.");
        }

        return *m_sampleRates.at(dataClass);
    }

    const GnssReceivers& MipNodeInfo::gnssReceiverInfo() const
    {
        return *m_receiverInfo;
    }

    const EventSupportInfo& MipNodeInfo::eventActionInfo() const
    {
		return *m_eventActionInfo;
    }

    const EventSupportInfo& MipNodeInfo::eventTriggerInfo() const
    {
		return *m_eventTriggerInfo;
    }
}
