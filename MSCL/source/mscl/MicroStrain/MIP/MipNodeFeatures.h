/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/

#pragma once

#include <memory>

#include "mscl/MicroStrain/MIP/MipNodeInfo.h"
#include "mscl/MicroStrain/MIP/MipTypes.h"
#include "mscl/MicroStrain/Inertial/ExposedInertialTypes.h"
#include "mscl/MicroStrain/SampleRate.h"

namespace mscl
{    
    //API Class: MipNodeFeatures
    //    Contains information on which features are supported by an <InertialNode>.
    class MipNodeFeatures
    {
    private:
        MipNodeFeatures();                                            //disabled default constructor
        MipNodeFeatures(const MipNodeFeatures&);                //disabled copy constructor
        MipNodeFeatures& operator=(const MipNodeFeatures&);    //disable assignment operator

    public:
        virtual ~MipNodeFeatures() {};

    protected:
        //Constructor: MipNodeFeatures
        //    Creates a MipNodeFeatures object.
        //
        //Parameters:
        //    info - An <MipNodeInfo> object representing standard information of a Mip Node.
        MipNodeFeatures(const MipNodeInfo& info);

        //Variable: m_nodeInfo
        //    The <MipNodeInfo>.
        MipNodeInfo m_nodeInfo;

    public:
#ifndef SWIG
        //Function: create
        //    Builds and returns a MipNodeFeatures pointer based on the given parameters.
        //
        //Parameters:
        //    info - An <MipNodeInfo> object representing standard information of the device.
        //
        //Returns:
        //    A MipNodeFeatures unique_ptr.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The Node model is not supported by MSCL.
        static std::unique_ptr<MipNodeFeatures> create(const MipNodeInfo& info);
#endif

    public:
        //Function: isChannelField
        //  Checks if the uint16 descriptor value is a Channel field or not.
        //
        //Returns:
        //  true if the descriptor is a data channel field, false otherwise.
        static bool isChannelField(uint16 descriptor);

        //API Function: supportsCategory
        //    Checks whether or not a given <MipTypes::DataClass> is supported by the Node.
        //
        //Parameters:
        //    dataClass - The <MipTypes::DataClass> to check if supported.
        bool supportsCategory(MipTypes::DataClass dataClass) const;

        //API Function: supportsCommand
        //    Checks whether or not the given <MipTypes::Command> is supported by the Node.
        //
        //Parameters:
        //    commandId - The <MipTypes::Command> to check if supported.
        //
        //Returns:
        //    true if the <InertialFieldId::ID> is supported by the Node, false otherwise.
        bool supportsCommand(MipTypes::Command commandId) const;

        //API Function: supportedCommands
        //  Gets a list of the supported <MipTypes::MipCommands> that are supported by the Node.
        //
        //Returns:
        //  The <MipTypes::MipCommands> supported by the Node.
        MipTypes::MipCommands supportedCommands() const;

        //API Function: supportedChannelFields
        //    Gets a list of the supported channel fields for a given <MipTypes::DataClass>.
        //
        //Parameters:
        //    dataClass - The <MipTypes::DataClass> to get the list of supported channels for.
        //
        //Returns:
        //    A <MipTypes::ChannelFields> object containing the list of supported channel fields.
        //
        //Exceptions:
        //    - <Error_MipCmdFailed>: The command has failed.
        //    - <Error_Communication>: Timed out waiting for a response.
        //    - <Error_NotSupported>: The <MipTypes::DataClass> is not supported by this node.
        //    - <Error_Connection>: A connection error has occurred with the Node.
        MipTypes::MipChannelFields supportedChannelFields(MipTypes::DataClass dataClass) const;

        //API Function: supportedSampleRates
        //    Gets a list of the supported sample rates for a given <MipTypes::DataClass>.
        //
        //Parameters:
        //    dataClass - The <MipTypes::DataClass> to get the sample rate list for.
        //
        //Returns:
        //    A <SampleRates> list containing all the supported sample rates for the provided channel.
        //
        //Exceptions:
        //    - <Error_MipCmdFailed>: The command has failed.
        //    - <Error_Communication>: Timed out waiting for a response.
        //    - <Error_NotSupported>: The <MipTypes::DataClass> is not supported by this node.
        //    - <Error_Connection>: A connection error has occurred with the Node.
        const SampleRates& supportedSampleRates(MipTypes::DataClass dataClass) const;

        //API Function: gnssReceiverInfo
        //    Gets a list of <GnssReceiverInfo> for supported GNSS receivers.
        //
        //Returns:
        //    A <GnssReceivers> list containing <GnssReceiverInfo> for supported receivers
        //
        //Exceptions:
        //    - <Error_MipCmdFailed>: The command has failed.
        //    - <Error_Communication>: Timed out waiting for a response.
        //    - <Error_Connection>: A connection error has occurred with the Node.
        const GnssReceivers& gnssReceiverInfo() const;

        //API Function: commPortInfo
        //    Gets a list of <DeviceCommPort> info objects for each comm port on the device.
        //
        //Returns:
        //    A <CommPortInfo> list containing <DeviceCommPort> info for supported receivers
        const CommPortInfo getCommPortInfo() const;

        //API Function: useLegacyIdsForEnableDataStream
        //
        //Returns:
        //  true if the device uses Legacy IDs for the IMU/AHRS, GNSS, and EF data sets in the Enable Data Stream command (0x0C, 0x11)
        bool useLegacyIdsForEnableDataStream() const;

        //API Function: supportedHeadingUpdateOptions
        //    Gets a list of the supported heading update control options for this node.
        //
        //Returns:
        //    A <HeadingUpdateOptionsList> containing all the supported heading update control options for this node.
        const HeadingUpdateOptionsList supportedHeadingUpdateOptions() const;

        //API Function: supportedStatusSelectors
        //    Gets a list of the supported device data status selectors for this node.
        //
        //Returns:
        //    A <StatusSelectors> containing all the supported device data status selectors for this node.
        const StatusSelectors supportedStatusSelectors() const;

        //API Function: supportedEstimationControlOptions
        //    Gets an object containing the estimation control options supported by this node.
        //
        //Returns:
        //    A EstimationControlOptions object containing all the supported estimation control options for this node.
        const EstimationControlOptions supportedEstimationControlOptions() const;

        //API Function: supportedVehicleModeTypes
        //    Gets a list of the supported vehicle mode types for this node.
        //
        //Returns:
        //    A <VehicleModeTypes> containing all the supported vehicle mode types for this node.
        const VehicleModeTypes supportedVehicleModeTypes() const;

        //API Function: supportedAdaptiveMeasurementModes
        //    Gets an object containing the adaptive measurement modes supported by this node.
        //
        //Returns:
        //    An AdaptiveMeasurementModes object containing all the supported adaptive measurement modes for this node.
        const AdaptiveMeasurementModes supportedAdaptiveMeasurementModes() const;

        //API Function: supportedAdaptiveFilterLevels
        //    Gets an object containing the adaptive filtering levels supported by this node.
        //
        //Returns:
        //    An AdaptiveFilterLevels object containing all the supported adaptive filtering levels for this node.
        const AdaptiveFilterLevels supportedAdaptiveFilterLevels() const;

        //API Function: supportedPpsSourceOptions
        //    Gets the PPS source options supported by this device.
        //
        //Returns:
        //    A <PpsSourceOptions> list containing all the supported options.
        const PpsSourceOptions supportedPpsSourceOptions() const;

        //API Function: supportedGpioPinModes
        //    Gets the Pin Mode options supported by this device based on the selected feature and behavior.
        //
        //Parameters:
        //    feature - the <GpioConfiguration::Feature>
        //    behavior - the behavior ID to look up supported pin modes for
        //               Depending on feature option, behavior IDs defined by <GpioConfiguration::GpioBehavior>, <GpioConfiguration::PpsBehavior>, <GpioConfiguration::EncoderBehavior>
        //
        //Returns:
        //    A <GpioPinModeOptions> list containing all the supported options.
        const GpioPinModeOptions supportedGpioPinModes(GpioConfiguration::Feature feature, uint8 behavior) const;

        //API Function: supportedGpioBehaviors
        //    Gets the GPIO Behavior options supported by this device based on the selected feature.
        //
        //Parameters:
        //      feature - the <GpioConfiguration::Feature>
        //
        //Returns:
        //    A <GpioBehaviorModes> list containing all the supported options.
        const GpioBehaviorModes supportedGpioBehaviors(GpioConfiguration::Feature feature) const;

        //API Function: supportedGpioFeatures
        //    Gets the GPIO Feature options supported by this device for the specified GPIO pin.
        //
        //Parameters:
        //      pin - the pin ID to look up supported features
        //
        //Returns:
        //    A <GpioFeatureOptions> list containing all the supported options.
        const GpioFeatureBehaviors supportedGpioFeatures(uint8 pin) const;

        //API Function: supportedGpioConfigurations
        //    Gets a map of supported GPIO configuration options for each supported pin
        //
        //Returns:
        //    A <GpioPinOptions> map of supported GPIO pin configurations
        const GpioPinOptions supportedGpioConfigurations() const;
    };
}