/*******************************************************************************
Copyright(c) 2015-2017 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/

#pragma once

#include <string>
#include "mscl/MicroStrain/SampleRate.h"
#include "mscl/Types.h"
#include "mscl/Utils.h"
#include "mscl/Version.h"
#include "Commands/GetDeviceInfo.h"
#include "InertialTypes.h"
#include "InertialModels.h"

namespace mscl
{
    class InertialNode_Impl;

    //Class: InertialNodeInfo
    //    Contains basic information about an InertialNode.
    class InertialNodeInfo
    {
    public:
        //Constructor: InertialNodeInfo
        //  Creates an InertialNodeInfo object.
        //
        //Parameters:
        //  node - The <InertialNode_Impl> to use for lazy loading.
        InertialNodeInfo(const InertialNode_Impl* node);

        //Constructor: InertialNodeInfo
        //    Creates an InertialNodeInfo object.
        //
        //Parameters:
        //    info - The <InertialDeviceInfo> containing information about the device.
        //    supportedDescriptors - The descriptor set ids that are supported by this device.
        InertialNodeInfo(const InertialDeviceInfo& info, const std::vector<uint16>& supportedDescriptors, const SampleRates& sensorRates, const SampleRates& gnssRates, const SampleRates& estFilterRates);

    private:
        InertialNodeInfo();    //disabled default constructor

        //Variable: m_node
        //  The <InertialNode_Impl> to use for lazy loading of values.
        const InertialNode_Impl* m_node;

    private:
        //Variable: m_deviceInfo
        //  The <InertialDeviceInfo> of the Node (lazy loaded).
        Utils::Lazy<InertialDeviceInfo> m_deviceInfo;

        //Variable: m_descriptors
        //  A vector of descriptors supported by the Node (lazy loaded).
        Utils::Lazy<std::vector<uint16>> m_descriptors;

        //Variable: m_sensorSampleRates
        //  Contains the sample rates for the Sensor group (lazy loaded).
        Utils::Lazy<SampleRates> m_sensorSampleRates;

        //Variable: m_gnssSampleRates
        //  Contains the sample rates for the GNSS group (lazy loaded).
        Utils::Lazy<SampleRates> m_gnssSampleRates;

        //Variable: m_estfilterSampleRates
        //  Contains the sample rates for the Estimation Filter group (lazy loaded).
        Utils::Lazy<SampleRates> m_estfilterSampleRates;

    public:
        //Function: deviceInfo
        //  Gets the <InertialDeviceInfo> of the Node.
        const InertialDeviceInfo& deviceInfo() const;

        //Function: descriptors
        //  Gets a vector of the descriptors supported by the Node.
        const std::vector<uint16>& descriptors() const;

        //Function: supportedSampleRates
        //  Gets the <SampleRates> supported by the Node for the given <InertialTypes::InertialCategory>.
        const SampleRates& supportedSampleRates(InertialTypes::InertialCategory category) const;
    };

}