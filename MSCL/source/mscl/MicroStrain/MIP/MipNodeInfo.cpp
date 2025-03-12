/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "mscl/MicroStrain/MIP/MipNodeInfo.h"

#include "mscl/MicroStrain/MIP/MipNode_Impl.h"

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
            { MipTypes::CLASS_SYSTEM, Utils::Lazy<SampleRates>(std::bind(&MipNode_Impl::supportedSampleRates, m_node, MipTypes::CLASS_SYSTEM)) },
        }),
        m_baseRates({
            { MipTypes::CLASS_AHRS_IMU, Utils::Lazy<uint16>(std::bind(&MipNode_Impl::getDataRateBase, m_node, MipTypes::CLASS_AHRS_IMU)) },
            { MipTypes::CLASS_GNSS, Utils::Lazy<uint16>(std::bind(&MipNode_Impl::getDataRateBase, m_node, MipTypes::CLASS_GNSS)) },
            { MipTypes::CLASS_ESTFILTER, Utils::Lazy<uint16>(std::bind(&MipNode_Impl::getDataRateBase, m_node, MipTypes::CLASS_ESTFILTER)) },
            { MipTypes::CLASS_DISPLACEMENT, Utils::Lazy<uint16>(std::bind(&MipNode_Impl::getDataRateBase, m_node, MipTypes::CLASS_DISPLACEMENT)) },
            { MipTypes::CLASS_GNSS1, Utils::Lazy<uint16>(std::bind(&MipNode_Impl::getDataRateBase, m_node, MipTypes::CLASS_GNSS1)) },
            { MipTypes::CLASS_GNSS2, Utils::Lazy<uint16>(std::bind(&MipNode_Impl::getDataRateBase, m_node, MipTypes::CLASS_GNSS2)) },
            { MipTypes::CLASS_GNSS3, Utils::Lazy<uint16>(std::bind(&MipNode_Impl::getDataRateBase, m_node, MipTypes::CLASS_GNSS3)) },
            { MipTypes::CLASS_GNSS4, Utils::Lazy<uint16>(std::bind(&MipNode_Impl::getDataRateBase, m_node, MipTypes::CLASS_GNSS4)) },
            { MipTypes::CLASS_GNSS5, Utils::Lazy<uint16>(std::bind(&MipNode_Impl::getDataRateBase, m_node, MipTypes::CLASS_GNSS5)) },
            { MipTypes::CLASS_SYSTEM, Utils::Lazy<uint16>(std::bind(&MipNode_Impl::getDataRateBase, m_node, MipTypes::CLASS_SYSTEM)) },
        }),
        m_receiverInfo(std::bind(&MipNode_Impl::getGnssReceiverInfo, m_node)),
        m_eventActionInfo(std::bind(&MipNode_Impl::getEventInfo, m_node, EventSupportInfo::ACTIONS)),
        m_eventTriggerInfo(std::bind(&MipNode_Impl::getEventInfo, m_node, EventSupportInfo::TRIGGERS)),
        m_sensorRanges(std::bind(&MipNode_Impl::getSupportedSensorRanges, m_node))
    {
    }

    MipNodeInfo::MipNodeInfo(const MipDeviceInfo& info,
                                const std::vector<uint16>& supportedDescriptors,
                                const std::map<MipTypes::DataClass, SampleRates>& sampleRates,
                                const std::map<MipTypes::DataClass, uint16>& baseRates) :
        m_deviceInfo(info),
        m_descriptors(supportedDescriptors),
        m_receiverInfo({}),
        m_eventActionInfo({}),
        m_eventTriggerInfo({}),
        m_sensorRanges(SupportedSensorRanges())
    {
        for (auto dataClass : sampleRates)
        {
            m_sampleRates.emplace(dataClass.first, dataClass.second);
        }

        for (auto dataClass : baseRates)
        {
            m_baseRates.emplace(dataClass.first, dataClass.second);
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

    const uint16& MipNodeInfo::baseDataRate(MipTypes::DataClass dataClass) const
    {
        if (m_baseRates.find(dataClass) == m_baseRates.end())
        {
            throw Error("Invalid DataClass.");
        }

        return *m_baseRates.at(dataClass);
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

    const SupportedSensorRanges& MipNodeInfo::supportedSensorRanges() const
    {
        return *m_sensorRanges;
    }
}
