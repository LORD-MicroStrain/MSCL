/*****************************************************************************************
**          Copyright(c) 2015-2022 Parker Hannifin Corp. All rights reserved.           **
**                                                                                      **
**    MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.    **
*****************************************************************************************/

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

        //Variable: m_nodeInfo
        //    The <MipNodeInfo> object that gives access to information of the Node
        mutable std::unique_ptr<MipNodeInfo> m_nodeInfo;

    public:
        virtual ~MipNodeFeatures() {};

    protected:
        friend class MipNode_Impl;

        //Constructor: MipNodeFeatures
        //    Creates a MipNodeFeatures object.
        //
        //Parameters:
        //    node - An <MipNode_Impl> object that this is a member of (used for lazy loading).
        MipNodeFeatures(const MipNode_Impl* node);

        //Variable: m_node
        //  The <MipNode_Impl> to use for lazy loading of values.
        const MipNode_Impl* m_node;

        //Function: nodeInfo
        //    Gets the basic device info (serial, model, fw version, etc.).
        //
        //Returns:
        //    A <MipNodeInfo> object containing the basic device info.
        //
        //Exceptions:
        //    - <Error_MipCmdFailed>: The command has failed.
        //    - <Error_Communication>: Timed out waiting for a response.
        //    - <Error_Connection>: A connection error has occurred with the Node.
        const MipNodeInfo& nodeInfo() const;

        //Function: resetNodeInfo
        //  Clears cached info read from device (ie fw version, receiver info, etc.).
        void resetNodeInfo();

#ifndef SWIG
        //Function: create
        //    Builds and returns a MipNodeFeatures pointer.
        //
        //Parameters:
        //    node - An <MipNode_Impl> object that this is a member of (used for lazy loading).
        //
        //Returns:
        //    A MipNodeFeatures unique_ptr.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The Node model is not supported by MSCL.
        static std::unique_ptr<MipNodeFeatures> create(const MipNode_Impl* node);
#endif

    public:
        //API Function: isChannelField
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

        //API Function: supportsChannelField
        //    Checks whether or not the given <MipTypes::ChannelField> is supported by the Node.
        //
        //Parameters:
        //    fieldId - The <MipTypes::ChannelField> to check if supported.
        //
        //Returns:
        //    true if the <MipTypes::ChannelField> is supported by the Node, false otherwise.
        bool supportsChannelField(MipTypes::ChannelField fieldId) const;

        //API Function: filterSupportedChannelFields
        //    Checks whether or not the <MipTypes::ChannelField> values in the specified list are supported by the Node and returns a list of those that are.
        //
        //Parameters:
        //    fields - The <MipTypes::MipChannelFields> to check if supported.
        //
        //Returns:
        //    <MipTypes::MipChannelFields> list of fields from the specified list that are supported by the device
        MipTypes::MipChannelFields filterSupportedChannelFields(const MipTypes::MipChannelFields& fields) const;

        //API Function: supportedChannelFields
        //    Gets a list of the supported channel fields for a given <MipTypes::DataClass>.
        //
        //Parameters:
        //    dataClass - default -1 - The <MipTypes::DataClass> to get the list of supported channels for. If -1, all supported ChannelFields will be returned regardless of DataClass
        //
        //Returns:
        //    A <MipTypes::ChannelFields> object containing the list of supported channel fields.
        //
        //Exceptions:
        //    - <Error_MipCmdFailed>: The command has failed.
        //    - <Error_Communication>: Timed out waiting for a response.
        //    - <Error_NotSupported>: The <MipTypes::DataClass> is not supported by this node.
        //    - <Error_Connection>: A connection error has occurred with the Node.
        MipTypes::MipChannelFields supportedChannelFields(MipTypes::DataClass dataClass = MipTypes::DataClass(-1)) const;

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

        //API Function: baseDataRate
        //    Gets the base data rate for a given <MipTypes::DataClass>.
        //
        //Parameters:
        //    dataClass - The <MipTypes::DataClass> to get base data rate for.
        //
        //Returns:
        //    uint16 - the base data rate.
        //
        //Exceptions:
        //    - <Error_MipCmdFailed>: The command has failed.
        //    - <Error_Communication>: Timed out waiting for a response.
        //    - <Error_NotSupported>: The <MipTypes::DataClass> is not supported by this node.
        //    - <Error_Connection>: A connection error has occurred with the Node.
        const uint16& baseDataRate(MipTypes::DataClass dataClass) const;

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

        //API Function: supportedGnssSources
        //    Gets a list of <InertialTypes::GNSS_Source> for supported GNSS sources.
        //
        //Returns:
        //    A <GnssSources> list containing <InertialTypes::GNSS_Source> for supported sources
        //
        //Exceptions:
        //    - <Error_MipCmdFailed>: The command has failed.
        //    - <Error_Communication>: Timed out waiting for a response.
        //    - <Error_Connection>: A connection error has occurred with the Node.
        const GnssSources supportedGnssSources() const;

        //API Function: supportedSensorRanges
        //    Gets the <SupportedSensorRanges> for each configurable sensor type.
        //
        //Returns:
        //    A <SupportedSensorRanges> list containing all supported <SensorRange> options
        //
        //Exceptions:
        //    - <Error_MipCmdFailed>: The command has failed.
        //    - <Error_Communication>: Timed out waiting for a response.
        //    - <Error_Connection>: A connection error has occurred with the Node.
        const SupportedSensorRanges& supportedSensorRanges() const;

        //API Function: supportedSensorRanges
        //    Gets the <SupportedSensorRanges> for the specified configurable sensor type.
        //
        //Parameters:
        //    type - The <SensorRange::Type> to lookup range options for
        //
        //Returns:
        //    A <SupportedSensorRanges> list containing all supported <SensorRange> options
        //
        //Exceptions:
        //    - <Error_MipCmdFailed>: The command has failed.
        //    - <Error_Communication>: Timed out waiting for a response.
        //    - <Error_Connection>: A connection error has occurred with the Node.
        const SensorRanges supportedSensorRanges(SensorRange::Type type) const;

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

        //API Function: supportedAidingMeasurementOptions
        //    Gets the aiding measurement sources supported by this device.
        //
        //Returns:
        //    A <AidingMeasurementSourceOptions> list containing all the supported options.
        const AidingMeasurementSourceOptions supportedAidingMeasurementOptions() const;

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

        //API Function: supportedGnssSignalConfigurations
        //    Gets bitmask vectors of supported <GnssSignalConfiguration> for each constellation
        //
        //Returns:
        //    Bitmask vectors of supported <GnssSignalConfiguration> for each constellation
        GnssSignalConfigOptions supportedGnssSignalConfigurations() const;

        //API Function: supportedDeclinationOptions
        //    Gets a vector of supported declination source options
        //
        //Returns:
        //    A <GeographicSources> vector of supported declination source options
        GeographicSources supportedDeclinationSources() const;

        //API Function: supportedInclinationOptions
        //    Gets a vector of supported inclination source options
        //
        //Returns:
        //    A <GeographicSources> vector of supported inclination source options
        GeographicSources supportedInclinationSources() const;

        //API Function: supportedMagneticMagnitudeOptions
        //    Gets a vector of supported magnetic magnitude source options
        //
        //Returns:
        //    A <GeographicSources> vector of supported magnetic magnitude source options
        GeographicSources supportedMagneticMagnitudeSources() const;

        //API Function: supportedEventThresholdChannels
        //    Gets the supported channel fields/qualifiers for event threshold configuration.
        //
        //Return:
        //    <ChannelFieldQualifiers> - The supported channel fields/qualifiers.
        MipTypes::ChannelFieldQualifiers supportedEventThresholdChannels() const;

        //API Function: supportedEventActionInfo
        //    Gets <EventSupportInfo> for event triggers and their types supported by the device.
        //
        //Returns:
        //    <EventSupportInfo> of the event actions and their types
        const EventSupportInfo supportedEventActionInfo() const;

        //API Function: supportedEventTriggerInfo
        //    Gets <EventSupportInfo> for event actions and their types supported by the device.
        //
        //Returns:
        //    <EventSupportInfo> of the event triggers and their types
        const EventSupportInfo supportedEventTriggerInfo() const;

        //API Function: supportsNorthCompensation
        //    Checks whether or not north compensation is supported by the Node.
        //    Only supported on devices with a magnetometer.
        //
        //Returns:
        //    True if north compensation is supported by the Node, false otherwise.
        const bool supportsNorthCompensation() const;

        //API Function: supportedLowPassFilterChannelFields
        //    Gets the list of <MipTypes::ChannelFields> that the low-pass filter can be applied to for this device.
        //
        //Returns:
        //    <MipTypes::MipChannelFields> - list of supported <MipTypes::ChannelFields>.
        MipTypes::MipChannelFields supportedLowPassFilterChannelFields() const;
    };
}