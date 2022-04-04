/*****************************************************************************************
**          Copyright(c) 2015-2022 Parker Hannifin Corp. All rights reserved.           **
**                                                                                      **
**    MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.    **
*****************************************************************************************/

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
            case MipTypes::CLASS_GNSS1:
            case MipTypes::CLASS_GNSS2:
            case MipTypes::CLASS_GNSS3:
            case MipTypes::CLASS_GNSS4:
            case MipTypes::CLASS_GNSS5:
                return true;

            default:
                return false;
        }
    }

    bool MipNodeFeatures::supportsCategory(MipTypes::DataClass dataClass) const
    {
        const auto& descriptors = m_nodeInfo.descriptors();

        //loop over all the descriptors we have
        for(auto desc : descriptors)
        {
            //if ths MSB of the descriptor matches the DataClass being requested
            if(Utils::msb(static_cast<uint16>(desc)) == static_cast<uint16>(dataClass))
            {
                //the device supports this category
                return true;
            }
        }

        //no descriptors found that match the requested category
        return false;
    }

    MipTypes::MipChannelFields MipNodeFeatures::supportedChannelFields(MipTypes::DataClass dataClass) const
    {
        MipTypes::MipChannelFields result;

        const auto& descriptors = m_nodeInfo.descriptors();

        //loop over all the descriptors we have
        for(auto desc : descriptors)
        {
            //if ths MSB of the descriptor matches the DataClass being requested
            if(Utils::msb(static_cast<uint16>(desc)) == static_cast<uint16>(dataClass))
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

    const SampleRates& MipNodeFeatures::supportedSampleRates(MipTypes::DataClass dataClass) const
    {
        return m_nodeInfo.supportedSampleRates(dataClass);
    }

    const GnssReceivers& MipNodeFeatures::gnssReceiverInfo() const
    {
        return m_nodeInfo.gnssReceiverInfo();
    }

    const CommPortInfo MipNodeFeatures::getCommPortInfo() const
    {
        MipModel model(m_nodeInfo.deviceInfo().modelNumber);
        switch (model.baseModel().nodeModel())
        {
        case MipModels::node_3dm_gq7:
            return{
                DeviceCommPort(DeviceCommPort::Type::PRIMARY, 1),
                DeviceCommPort(DeviceCommPort::Type::AUX, 2)
            };

        default:
            return{
                DeviceCommPort(DeviceCommPort::Type::PRIMARY, 1)
            };
        }
    }

    const VehicleModeTypes MipNodeFeatures::supportedVehicleModeTypes() const
    {
        if (!supportsCommand(mscl::MipTypes::Command::CMD_EF_VEHIC_DYNAMICS_MODE))
        {
            return VehicleModeTypes(0);
        }

        MipModel model(m_nodeInfo.deviceInfo().modelNumber);
        switch (model.baseModel().nodeModel())
        {
        
        case MipModels::node_3dm_gx3_45:
            return{
                InertialTypes::VehicleModeType::PORTABLE_VEHICLE,
                InertialTypes::VehicleModeType::AUTOMOTIVE_VEHICLE,
                InertialTypes::VehicleModeType::AIRBORNE_VEHICLE
            };

        case MipModels::node_3dm_gx5_45:
        case MipModels::node_3dm_gx4_45:
        case MipModels::node_3dm_gq4_45:
        case MipModels::node_3dm_rq1_45_lt:
        case MipModels::node_3dm_rq1_45_st:
        default:
            return{
                InertialTypes::VehicleModeType::PORTABLE_VEHICLE,
                InertialTypes::VehicleModeType::AUTOMOTIVE_VEHICLE,
                InertialTypes::VehicleModeType::AIRBORNE_VEHICLE,
                InertialTypes::VehicleModeType::AIRBORNE_HIGH_G_VEHICLE
            };
        }
    }

    const mscl::StatusSelectors MipNodeFeatures::supportedStatusSelectors() const
    {
        if (!supportsCommand(mscl::MipTypes::Command::CMD_DEVICE_STATUS)) {
            return{};
        }

        MipModel model(m_nodeInfo.deviceInfo().modelNumber);
        switch (model.baseModel().nodeModel())
        {
        case MipModels::node_3dm_gq4_45:
        case MipModels::node_3dm_rq1_45_lt:
        case MipModels::node_3dm_rq1_45_st:
        case MipModels::node_3dm_gx5_10:
        case MipModels::node_3dm_cx5_10:
        case MipModels::node_3dm_cv5_10:
        case MipModels::node_3dm_gx5_15:
        case MipModels::node_3dm_gx5_25:
        case MipModels::node_3dm_cx5_15:
        case MipModels::node_3dm_cx5_25:
        case MipModels::node_3dm_cv5_15:
        case MipModels::node_3dm_cv5_25:
        case MipModels::node_3dm_cl5_15:
        case MipModels::node_3dm_cl5_25:
        case MipModels::node_3dm_gx4_15:
        case MipModels::node_3dm_gx4_25:
        case MipModels::node_3dm_gx5_35:
        case MipModels::node_3dm_gx5_45:
        case MipModels::node_3dm_cx5_35:
        case MipModels::node_3dm_cx5_45:
        case MipModels::node_3dm_gx4_45:
            return{
                DeviceStatusData::StatusSelector::BASIC_STATUS_STRUCTURE,
                DeviceStatusData::StatusSelector::DIAGNOSTIC_STATUS_STRUCTURE
            };
        default:
            return{
                DeviceStatusData::StatusSelector::BASIC_STATUS_STRUCTURE
            };
        }
    }

    bool MipNodeFeatures::useLegacyIdsForEnableDataStream() const
    {
        MipModel model(m_nodeInfo.deviceInfo().modelNumber);
        switch (model.baseModel().nodeModel())
        {
        case MipModels::node_3dm_dh3:
        case MipModels::node_3dm_gx3_15:
        case MipModels::node_3dm_gx3_25:
        case MipModels::node_3dm_gx3_35:
        case MipModels::node_3dm_gx3_45:
        case MipModels::node_3dm_rq1_45_lt:
        case MipModels::node_3dm_gx4_15:
        case MipModels::node_3dm_gx4_25:
        case MipModels::node_3dm_gx4_45:
        case MipModels::node_3dm_rq1_45_st:
        case MipModels::node_mv5_ar:
        case MipModels::node_3dm_gx5_10:
        case MipModels::node_3dm_gx5_15:
        case MipModels::node_3dm_gx5_25:
        case MipModels::node_3dm_gx5_35:
        case MipModels::node_3dm_gx5_45:
        case MipModels::node_3dm_cv5_10:
        case MipModels::node_3dm_cv5_15:
        case MipModels::node_3dm_cv5_25:
        case MipModels::node_3dm_cv5_45:
        case MipModels::node_3dm_gq4_45:
        case MipModels::node_3dm_cx5_45:
        case MipModels::node_3dm_cx5_35:
        case MipModels::node_3dm_cx5_25:
        case MipModels::node_3dm_cx5_15:
        case MipModels::node_3dm_cx5_10:
        case MipModels::node_3dm_cl5_15:
        case MipModels::node_3dm_cl5_25:
            return true;

        default:
            return false;
        }
    }

    const HeadingUpdateOptionsList MipNodeFeatures::supportedHeadingUpdateOptions() const
    {
        if (!supportsCommand(mscl::MipTypes::Command::CMD_EF_HEADING_UPDATE_CTRL))
        {
            return{ HeadingUpdateOptions(InertialTypes::HeadingUpdateEnableOption::ENABLE_NONE) };
        }

        MipModel model(m_nodeInfo.deviceInfo().modelNumber);
        switch (model.baseModel().nodeModel())
        {
        case MipModels::node_3dm_gx4_45:
        case MipModels::node_3dm_gx3_45:
        case MipModels::node_3dm_gq4_45:
            return{
                HeadingUpdateOptions(InertialTypes::HeadingUpdateEnableOption::ENABLE_NONE),
                HeadingUpdateOptions(InertialTypes::HeadingUpdateEnableOption::ENABLE_INTERNAL_MAGNETOMETER),
                HeadingUpdateOptions(InertialTypes::HeadingUpdateEnableOption::ENABLE_INTERNAL_GNSS),
                HeadingUpdateOptions(InertialTypes::HeadingUpdateEnableOption::ENABLE_EXTERNAL_MESSAGES)
            };

        case MipModels::node_3dm_gx5_25:
        case MipModels::node_3dm_gx4_25:
        case MipModels::node_3dm_cv5_25:
        case MipModels::node_3dm_cl5_25:
            return{
                HeadingUpdateOptions(InertialTypes::HeadingUpdateEnableOption::ENABLE_NONE),
                HeadingUpdateOptions(InertialTypes::HeadingUpdateEnableOption::ENABLE_INTERNAL_MAGNETOMETER),
                HeadingUpdateOptions(InertialTypes::HeadingUpdateEnableOption::ENABLE_EXTERNAL_MESSAGES)
            };

        case MipModels::node_3dm_rq1_45_lt:
        case MipModels::node_3dm_rq1_45_st:
            return{
                HeadingUpdateOptions(InertialTypes::HeadingUpdateEnableOption::ENABLE_NONE),
                HeadingUpdateOptions(InertialTypes::HeadingUpdateEnableOption::ENABLE_INTERNAL_GNSS),
                HeadingUpdateOptions(InertialTypes::HeadingUpdateEnableOption::ENABLE_EXTERNAL_MESSAGES)
            };

        case MipModels::node_3dm_gx5_15:
        case MipModels::node_3dm_cv5_15:
        case MipModels::node_3dm_cl5_15:
            return{
                HeadingUpdateOptions(InertialTypes::HeadingUpdateEnableOption::ENABLE_NONE),
                HeadingUpdateOptions(InertialTypes::HeadingUpdateEnableOption::ENABLE_EXTERNAL_MESSAGES)
            };

        case MipModels::node_3dm_gx5_45:
        case MipModels::node_3dm_gx5_35:
        case MipModels::node_3dm_gx5_10:
        case MipModels::node_3dm_gx4_15:
        case MipModels::node_3dm_gx3_15:
        case MipModels::node_3dm_gx3_25:
        case MipModels::node_3dm_gx3_35:
        case MipModels::node_3dm_cv5_45:
        case MipModels::node_3dm_cv5_10:
        case MipModels::node_3dm_dh3:
        default:
            return{
                HeadingUpdateOptions(InertialTypes::HeadingUpdateEnableOption::ENABLE_NONE),
                HeadingUpdateOptions(InertialTypes::HeadingUpdateEnableOption::ENABLE_INTERNAL_MAGNETOMETER),
                HeadingUpdateOptions(InertialTypes::HeadingUpdateEnableOption::ENABLE_INTERNAL_GNSS),
                HeadingUpdateOptions(InertialTypes::HeadingUpdateEnableOption::ENABLE_EXTERNAL_MESSAGES),
                HeadingUpdateOptions(InertialTypes::HeadingUpdateEnableOption::ENABLE_MAGNETOMETER_AND_GNSS),
                HeadingUpdateOptions(InertialTypes::HeadingUpdateEnableOption::ENABLE_GNSS_AND_EXTERNAL),
                HeadingUpdateOptions(InertialTypes::HeadingUpdateEnableOption::ENABLE_MAGNETOMETER_AND_EXTERNAL),
                HeadingUpdateOptions(InertialTypes::HeadingUpdateEnableOption::ENABLE_ALL)
            };
        }

    }

    const EstimationControlOptions MipNodeFeatures::supportedEstimationControlOptions() const
    {
        if (!supportsCommand(mscl::MipTypes::Command::CMD_EF_BIAS_EST_CTRL))
        {
            return{ EstimationControlOptions(0) };
        }

        MipModel model(m_nodeInfo.deviceInfo().modelNumber);
        switch (model.baseModel().nodeModel())
        {
        case MipModels::node_3dm_gx5_15:
        case MipModels::node_3dm_gx4_25:
        case MipModels::node_3dm_gx4_15:
        case MipModels::node_3dm_gx3_45:
        case MipModels::node_3dm_cv5_15:
        case MipModels::node_3dm_cl5_15:
            return EstimationControlOptions(
                InertialTypes::EstimationControlOption::ENABLE_GYRO_BIAS_ESTIMATION
            );

        case MipModels::node_3dm_gx4_45:
        case MipModels::node_3dm_rq1_45_lt:
        case MipModels::node_3dm_rq1_45_st:
        case MipModels::node_3dm_gq4_45:
            return EstimationControlOptions(
                InertialTypes::EstimationControlOption::ENABLE_GYRO_BIAS_ESTIMATION |
                InertialTypes::EstimationControlOption::ENABLE_ACCEL_BIAS_ESTIMATION |
                InertialTypes::EstimationControlOption::ENABLE_GYRO_SCALE_FACTOR_ESTIMATION |
                InertialTypes::EstimationControlOption::ENABLE_ACCEL_SCALE_FACTOR_ESTIMATION |
                InertialTypes::EstimationControlOption::ENABLE_GNSS_ANTENNA_OFFSET_ESTIMATION
            );

        case MipModels::node_3dm_gx5_25:
        case MipModels::node_3dm_cv5_25:
        case MipModels::node_3dm_cl5_25:
            return EstimationControlOptions(
                InertialTypes::EstimationControlOption::ENABLE_GYRO_BIAS_ESTIMATION |
                InertialTypes::EstimationControlOption::ENABLE_HARD_IRON_AUTO_CALIBRATION |
                InertialTypes::EstimationControlOption::ENABLE_SOFT_IRON_AUTO_CALIBRATION
            );

        case MipModels::node_3dm_gx5_45:
        case MipModels::node_3dm_gx5_35:
        case MipModels::node_3dm_gx5_10:
        case MipModels::node_3dm_gx3_15:
        case MipModels::node_3dm_gx3_25:
        case MipModels::node_3dm_gx3_35:
        case MipModels::node_3dm_cv5_45:
        case MipModels::node_3dm_cv5_10:
        case MipModels::node_3dm_dh3:
        default:
            return EstimationControlOptions(
                InertialTypes::EstimationControlOption::ENABLE_GYRO_BIAS_ESTIMATION |
                InertialTypes::EstimationControlOption::ENABLE_ACCEL_BIAS_ESTIMATION |
                InertialTypes::EstimationControlOption::ENABLE_GYRO_SCALE_FACTOR_ESTIMATION |
                InertialTypes::EstimationControlOption::ENABLE_ACCEL_SCALE_FACTOR_ESTIMATION |
                InertialTypes::EstimationControlOption::ENABLE_GNSS_ANTENNA_OFFSET_ESTIMATION |
                InertialTypes::EstimationControlOption::ENABLE_HARD_IRON_AUTO_CALIBRATION |
                InertialTypes::EstimationControlOption::ENABLE_SOFT_IRON_AUTO_CALIBRATION
            );
        }
    }

    const AdaptiveMeasurementModes MipNodeFeatures::supportedAdaptiveMeasurementModes() const
    {
        if (!supportsCommand(mscl::MipTypes::Command::CMD_EF_GRAV_MAGNITUDE_ERR_ADAPT_MEASURE)
            && !supportsCommand(mscl::MipTypes::Command::CMD_EF_MAG_MAGNITUDE_ERR_ADAPT_MEASURE)
            && !supportsCommand(mscl::MipTypes::Command::CMD_EF_MAG_DIP_ANGLE_ERR_ADAPT_MEASURE))
        {
            return{ AdaptiveMeasurementModes(0) };
        }

        MipModel model(m_nodeInfo.deviceInfo().modelNumber);
        switch (model.baseModel().nodeModel())
        {
            case MipModels::node_3dm_gx4_45:
            case MipModels::node_3dm_gx4_25:
            case MipModels::node_3dm_gx4_15:
            case MipModels::node_3dm_gx3_45:
            case MipModels::node_3dm_gx3_35:
            case MipModels::node_3dm_gx3_25:
            case MipModels::node_3dm_gx3_15:
            case MipModels::node_3dm_rq1_45_lt:
            case MipModels::node_3dm_rq1_45_st:
            case MipModels::node_3dm_gq4_45:
            case MipModels::node_3dm_dh3:
                return {
                    InertialTypes::AdaptiveMeasurementMode::ADAPTIVE_MEASUREMENT_DISABLE,
                    InertialTypes::AdaptiveMeasurementMode::ADAPTIVE_MEASUREMENT_ENABLE_FIXED 
                };

            case MipModels::node_3dm_gx5_45:
            case MipModels::node_3dm_gx5_35:
            case MipModels::node_3dm_gx5_25:
            case MipModels::node_3dm_gx5_15:
            case MipModels::node_3dm_gx5_10:
            case MipModels::node_3dm_cv5_45:
            case MipModels::node_3dm_cv5_25:
            case MipModels::node_3dm_cv5_15:
            case MipModels::node_3dm_cv5_10:
            case MipModels::node_3dm_cl5_25:
            case MipModels::node_3dm_cl5_15:
            default:
                return {
                    InertialTypes::AdaptiveMeasurementMode::ADAPTIVE_MEASUREMENT_DISABLE,
                    InertialTypes::AdaptiveMeasurementMode::ADAPTIVE_MEASUREMENT_ENABLE_FIXED, 
                    InertialTypes::AdaptiveMeasurementMode::ADAPTIVE_MEASUREMENT_ENABLE_AUTO
                };
        }
    }

    const AdaptiveFilterLevels MipNodeFeatures::supportedAdaptiveFilterLevels() const
    {
        if (!supportsCommand(mscl::MipTypes::Command::CMD_EF_ADAPTIVE_FILTER_OPTIONS))
        {
            return{ AdaptiveFilterLevels(0) };
        }

        MipModel model(m_nodeInfo.deviceInfo().modelNumber);
        switch (model.baseModel().nodeModel())
        {
        case MipModels::node_3dm_gx5_45:
        case MipModels::node_3dm_cv5_45:
            return{
                InertialTypes::AutoAdaptiveFilteringLevel::FILTERING_OFF,
                InertialTypes::AutoAdaptiveFilteringLevel::FILTERING_MODERATE
            };

        case MipModels::node_3dm_gq7:
        case MipModels::node_3dm_cv7_ahrs:
        case MipModels::node_3dm_cv7_ar:
        default:
            return{
                InertialTypes::AutoAdaptiveFilteringLevel::FILTERING_OFF,
                InertialTypes::AutoAdaptiveFilteringLevel::FILTERING_CONSERVATIVE,
                InertialTypes::AutoAdaptiveFilteringLevel::FILTERING_MODERATE,
                InertialTypes::AutoAdaptiveFilteringLevel::FILTERING_AGGRESIVE
            };
        }
    }

    const AidingMeasurementSourceOptions MipNodeFeatures::supportedAidingMeasurementOptions() const
    {
        if (!supportsCommand(mscl::MipTypes::Command::CMD_EF_AIDING_MEASUREMENT_ENABLE))
        {
            return{ AidingMeasurementSourceOptions(0) };
        }

        MipModel model(m_nodeInfo.deviceInfo().modelNumber);

        switch(model.baseModel().nodeModel())
        {
            case MipModels::node_3dm_cv7_ahrs:
            case MipModels::node_3dm_cv7_ar:
                return {
                    InertialTypes::AidingMeasurementSource::MAGNETOMETER_AIDING,
                    InertialTypes::AidingMeasurementSource::EXTERNAL_HEADING_AIDING
                };

            default:
                return {
                    InertialTypes::AidingMeasurementSource::GNSS_POS_VEL_AIDING,
                    InertialTypes::AidingMeasurementSource::GNSS_HEADING_AIDING,
                    InertialTypes::AidingMeasurementSource::ALTIMETER_AIDING,
                    InertialTypes::AidingMeasurementSource::ODOMETER_AIDING,
                    InertialTypes::AidingMeasurementSource::MAGNETOMETER_AIDING,
                    InertialTypes::AidingMeasurementSource::EXTERNAL_HEADING_AIDING
                };
        }
    }

    const PpsSourceOptions MipNodeFeatures::supportedPpsSourceOptions() const
    {
        if (!supportsCommand(mscl::MipTypes::Command::CMD_PPS_SOURCE))
        {
            return{ PpsSourceOptions(0) };
        }

        MipModel model(m_nodeInfo.deviceInfo().modelNumber);
        switch (model.baseModel().nodeModel())
        {
        case MipModels::node_3dm_cv7_ahrs:
        case MipModels::node_3dm_cv7_ar:
            return{
                InertialTypes::PpsSource::PPS_DISABLED,
                InertialTypes::PpsSource::PPS_GPIO,
                InertialTypes::PpsSource::PPS_GENERATED
            };

        default:
            return{
                InertialTypes::PpsSource::PPS_DISABLED,
                InertialTypes::PpsSource::PPS_RECEIVER_1,
                InertialTypes::PpsSource::PPS_RECEIVER_2,
                InertialTypes::PpsSource::PPS_GPIO,
                InertialTypes::PpsSource::PPS_GENERATED
            };
        }
    }

    const GpioPinModeOptions MipNodeFeatures::supportedGpioPinModes(GpioConfiguration::Feature feature, uint8 behavior) const
    {
        if (!supportsCommand(mscl::MipTypes::Command::CMD_GPIO_CONFIGURATION))
        {
            return{ GpioPinModeOptions(0) };
        }

        if ((feature == GpioConfiguration::ENCODER_FEATURE && behavior != GpioConfiguration::EncoderBehavior::ENCODER_UNUSED)
            || (feature == GpioConfiguration::GPIO_FEATURE && behavior == GpioConfiguration::GpioBehavior::GPIO_INPUT_BEHAVIOR))
        {
            return{
                GpioConfiguration::PinModes(0),
                GpioConfiguration::PinModes::PULLUP,
                GpioConfiguration::PinModes::PULLDOWN
            };
        }

        if (feature == GpioConfiguration::GPIO_FEATURE
            && (behavior == GpioConfiguration::GpioBehavior::GPIO_OUTPUT_LOW_BEHAVIOR || behavior == GpioConfiguration::GpioBehavior::GPIO_OUTPUT_HIGH_BEHAVIOR))
        {
            return{
            GpioConfiguration::PinModes(0),
            GpioConfiguration::PinModes::OPEN_DRAIN,
            GpioConfiguration::PinModes(GpioConfiguration::PinModes::OPEN_DRAIN | GpioConfiguration::PinModes::PULLUP)
            };
        }

        return{ GpioPinModeOptions(0) };
    }

    const GpioBehaviorModes MipNodeFeatures::supportedGpioBehaviors(GpioConfiguration::Feature feature) const
    {
        if (!supportsCommand(mscl::MipTypes::Command::CMD_GPIO_CONFIGURATION))
        {
            return{};
        }

        switch (feature)
        {
        case GpioConfiguration::Feature::GPIO_FEATURE:
            return{
            { GpioConfiguration::GpioBehavior::GPIO_INPUT_BEHAVIOR, supportedGpioPinModes(GpioConfiguration::GPIO_FEATURE, GpioConfiguration::GpioBehavior::GPIO_INPUT_BEHAVIOR) },
            { GpioConfiguration::GpioBehavior::GPIO_OUTPUT_LOW_BEHAVIOR, supportedGpioPinModes(GpioConfiguration::GPIO_FEATURE, GpioConfiguration::GpioBehavior::GPIO_OUTPUT_LOW_BEHAVIOR) },
            { GpioConfiguration::GpioBehavior::GPIO_OUTPUT_HIGH_BEHAVIOR, supportedGpioPinModes(GpioConfiguration::GPIO_FEATURE, GpioConfiguration::GpioBehavior::GPIO_OUTPUT_HIGH_BEHAVIOR) }
            };

        case GpioConfiguration::Feature::PPS_FEATURE:
            return{
                { GpioConfiguration::PpsBehavior::PPS_INPUT, GpioPinModeOptions(0) },
                { GpioConfiguration::PpsBehavior::PPS_OUTPUT, GpioPinModeOptions(0) }
            };

        case GpioConfiguration::Feature::ENCODER_FEATURE:
            return{
                { GpioConfiguration::EncoderBehavior::ENCODER_A, supportedGpioPinModes(GpioConfiguration::ENCODER_FEATURE, GpioConfiguration::EncoderBehavior::ENCODER_A) },
                { GpioConfiguration::EncoderBehavior::ENCODER_B, supportedGpioPinModes(GpioConfiguration::ENCODER_FEATURE, GpioConfiguration::EncoderBehavior::ENCODER_A) }
            };

        default:
            return{};
        }
    }

    const GpioFeatureBehaviors MipNodeFeatures::supportedGpioFeatures(uint8 pin) const
    {
        if (!supportsCommand(mscl::MipTypes::Command::CMD_GPIO_CONFIGURATION))
        {
            return{};
        }

        GpioPinOptions options = supportedGpioConfigurations();
        
        if (options.find(pin) == options.end())
        {
            return{};
        }

        return options[pin];
    }

    const GpioPinOptions MipNodeFeatures::supportedGpioConfigurations() const
    {
        if (!supportsCommand(mscl::MipTypes::Command::CMD_GPIO_CONFIGURATION))
        {
            return{};
        }

        GpioFeatureBehaviors pin1Features = {
            { GpioConfiguration::Feature::UNUSED_FEATURE, {} },
            { GpioConfiguration::Feature::GPIO_FEATURE, supportedGpioBehaviors(GpioConfiguration::Feature::GPIO_FEATURE) },
            { GpioConfiguration::Feature::PPS_FEATURE, supportedGpioBehaviors(GpioConfiguration::Feature::PPS_FEATURE) },
            { GpioConfiguration::Feature::ENCODER_FEATURE, supportedGpioBehaviors(GpioConfiguration::Feature::ENCODER_FEATURE) }
        };

        GpioFeatureBehaviors pin2Features = {
            { GpioConfiguration::Feature::UNUSED_FEATURE, {} },
            { GpioConfiguration::Feature::GPIO_FEATURE, supportedGpioBehaviors(GpioConfiguration::Feature::GPIO_FEATURE) },
            { GpioConfiguration::Feature::ENCODER_FEATURE, supportedGpioBehaviors(GpioConfiguration::Feature::ENCODER_FEATURE) }
        };

        GpioFeatureBehaviors pin3Features = {
            { GpioConfiguration::Feature::UNUSED_FEATURE, {} },
            { GpioConfiguration::Feature::GPIO_FEATURE, supportedGpioBehaviors(GpioConfiguration::Feature::GPIO_FEATURE) },
            { GpioConfiguration::Feature::PPS_FEATURE, supportedGpioBehaviors(GpioConfiguration::Feature::PPS_FEATURE) },
        };

        GpioFeatureBehaviors pin4Features = {
            { GpioConfiguration::Feature::UNUSED_FEATURE, {} },
            { GpioConfiguration::Feature::GPIO_FEATURE, supportedGpioBehaviors(GpioConfiguration::Feature::GPIO_FEATURE) },
        };

        return{
            { 1, pin1Features },
            { 2, pin2Features },
            { 3, pin3Features },
            { 4, pin4Features }
        };
    }

    const EventSupportInfo MipNodeFeatures::getEventActionInfo() const
    {
        return m_nodeInfo.eventActionInfo();
    }

    const EventSupportInfo MipNodeFeatures::getEventTriggerInfo() const
    {
        return m_nodeInfo.eventTriggerInfo();
    }
}
