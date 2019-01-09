/*******************************************************************************
Copyright(c) 2015-2019 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/

#pragma once

#include <string>
#include "mscl/MicroStrain/SampleRate.h"
#include "mscl/Types.h"
#include "mscl/Utils.h"
#include "mscl/Version.h"
#include "mscl/MicroStrain/MIP/Commands/GetDeviceInfo.h"
#include "mscl/MicroStrain/MIP/MipTypes.h"

namespace mscl
{
    class MipNode_Impl;

    //Class: MipNodeInfo
    //    Contains basic information about a MipNode.
    class MipNodeInfo
    {
    public:
        //Constructor: MipNodeInfo
        //  Creates a MipNodeInfo object.
        //
        //Parameters:
        //  node - The <MipNode_Impl> to use for lazy loading.
        MipNodeInfo(const MipNode_Impl* node);

        //Constructor: MipNodeInfo
        //    Creates a MipNodeInfo object.
        //
        //Parameters:
        //    info - The <MipDeviceInfo> containing information about the device.
        //    supportedDescriptors - The descriptor set ids that are supported by this device.
        MipNodeInfo(const MipDeviceInfo& info, const std::vector<uint16>& supportedDescriptors, const SampleRates& sensorRates, const SampleRates& gnssRates, const SampleRates& estFilterRates, const SampleRates& displacementRates);

    private:
        MipNodeInfo();    //disabled default constructor

        //Variable: m_node
        //  The <MipNode_Impl> to use for lazy loading of values.
        const MipNode_Impl* m_node;

    private:
        //Variable: m_deviceInfo
        //  The <MipDeviceInfo> of the Node (lazy loaded).
        Utils::Lazy<MipDeviceInfo> m_deviceInfo;

        //Variable: m_descriptors
        //  A vector of descriptors supported by the Node (lazy loaded).
        Utils::Lazy<std::vector<uint16>> m_descriptors;

        //Variable: m_ahrsImuSampleRates
        //  Contains the sample rates for the Sensor group (lazy loaded).
        Utils::Lazy<SampleRates> m_ahrsImuSampleRates;

        //Variable: m_gnssSampleRates
        //  Contains the sample rates for the GNSS group (lazy loaded).
        Utils::Lazy<SampleRates> m_gnssSampleRates;

        //Variable: m_estfilterSampleRates
        //  Contains the sample rates for the Estimation Filter group (lazy loaded).
        Utils::Lazy<SampleRates> m_estfilterSampleRates;

        //Variable: m_displacementSampleRates
        //  Contains the sample rates for the Displacement group (lazy loaded).
        Utils::Lazy<SampleRates> m_displacementSampleRates;

    public:
        //Function: deviceInfo
        //  Gets the <MipDeviceInfo> of the Node.
        const MipDeviceInfo& deviceInfo() const;

        //Function: descriptors
        //  Gets a vector of the descriptors supported by the Node.
        const std::vector<uint16>& descriptors() const;

        //Function: supportedSampleRates
        //  Gets the <SampleRates> supported by the Node for the given <MipTypes::DataClass>.
        const SampleRates& supportedSampleRates(MipTypes::DataClass dataClass) const;
    };

}