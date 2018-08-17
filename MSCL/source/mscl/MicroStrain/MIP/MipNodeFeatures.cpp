/*******************************************************************************
Copyright(c) 2015-2018 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
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

    const HeadingUpdateOptionsList MipNodeFeatures::supportedHeadingUpdateOptions() const
    {
        if (!supportsCommand(mscl::MipTypes::Command::CMD_EF_HEADING_UPDATE_CTRL))
        {
            return{ HeadingUpdateOptions(InertialTypes::HeadingUpdateEnableOption::ENABLE_NONE) };
        }

        InertialModels::NodeModel model = InertialModels::nodeFromModelString(m_nodeInfo.deviceInfo().modelNumber);
        switch (model)
        {
        case InertialModels::node_3dm_gx4_45:
        case InertialModels::node_3dm_gx3_45:
        case InertialModels::node_3dm_gq4_45:
            return{
                HeadingUpdateOptions(InertialTypes::HeadingUpdateEnableOption::ENABLE_NONE),
                HeadingUpdateOptions(InertialTypes::HeadingUpdateEnableOption::ENABLE_INTERNAL_MAGNETOMETER),
                HeadingUpdateOptions(InertialTypes::HeadingUpdateEnableOption::ENABLE_INTERNAL_GNSS),
                HeadingUpdateOptions(InertialTypes::HeadingUpdateEnableOption::ENABLE_EXTERNAL_MESSAGES)
            };

        case InertialModels::node_3dm_gx5_25:
        case InertialModels::node_3dm_gx4_25:
        case InertialModels::node_3dm_cv5_25:
            return{
                HeadingUpdateOptions(InertialTypes::HeadingUpdateEnableOption::ENABLE_NONE),
                HeadingUpdateOptions(InertialTypes::HeadingUpdateEnableOption::ENABLE_INTERNAL_MAGNETOMETER),
                HeadingUpdateOptions(InertialTypes::HeadingUpdateEnableOption::ENABLE_EXTERNAL_MESSAGES)
            };

        case InertialModels::node_3dm_rq1_45:
            return{
                HeadingUpdateOptions(InertialTypes::HeadingUpdateEnableOption::ENABLE_NONE),
                HeadingUpdateOptions(InertialTypes::HeadingUpdateEnableOption::ENABLE_INTERNAL_GNSS),
                HeadingUpdateOptions(InertialTypes::HeadingUpdateEnableOption::ENABLE_EXTERNAL_MESSAGES)
            };

        case InertialModels::node_3dm_gx5_15:
        case InertialModels::node_3dm_cv5_15:
            return{
                HeadingUpdateOptions(InertialTypes::HeadingUpdateEnableOption::ENABLE_NONE),
                HeadingUpdateOptions(InertialTypes::HeadingUpdateEnableOption::ENABLE_EXTERNAL_MESSAGES)
            };

        case InertialModels::node_3dm_gx5_45:
        case InertialModels::node_3dm_gx5_35:
        case InertialModels::node_3dm_gx5_10:
        case InertialModels::node_3dm_gx4_15:
        case InertialModels::node_3dm_gx3_15:
        case InertialModels::node_3dm_gx3_25:
        case InertialModels::node_3dm_gx3_35:
        case InertialModels::node_3dm_gx2:
        case InertialModels::node_3dm_cv5_45:
        case InertialModels::node_3dm_cv5_10:
        case InertialModels::node_3dm:
        case InertialModels::node_fasA:
        case InertialModels::node_3dm_dh3:
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

        InertialModels::NodeModel model = InertialModels::nodeFromModelString(m_nodeInfo.deviceInfo().modelNumber);
        switch (model)
        {
        case InertialModels::node_3dm_gx5_15:
        case InertialModels::node_3dm_gx4_25:
        case InertialModels::node_3dm_gx4_15:
        case InertialModels::node_3dm_gx3_45:
        case InertialModels::node_3dm_cv5_25:
        case InertialModels::node_3dm_cv5_15:
            return EstimationControlOptions(
                InertialTypes::EstimationControlOption::ENABLE_GYRO_BIAS_ESTIMATION
            );

        case InertialModels::node_3dm_gx4_45:
        case InertialModels::node_3dm_rq1_45:
        case InertialModels::node_3dm_gq4_45:
            return EstimationControlOptions(
                InertialTypes::EstimationControlOption::ENABLE_GYRO_BIAS_ESTIMATION |
                InertialTypes::EstimationControlOption::ENABLE_ACCEL_BIAS_ESTIMATION |
                InertialTypes::EstimationControlOption::ENABLE_GYRO_SCALE_FACTOR_ESTIMATION |
                InertialTypes::EstimationControlOption::ENABLE_ACCEL_SCALE_FACTOR_ESTIMATION |
                InertialTypes::EstimationControlOption::ENABLE_GNSS_ANTENNA_OFFSET_ESTIMATION
            );

        case InertialModels::node_3dm_gx5_25:
            return EstimationControlOptions(
                InertialTypes::EstimationControlOption::ENABLE_GYRO_BIAS_ESTIMATION |
                InertialTypes::EstimationControlOption::ENABLE_HARD_IRON_AUTO_CALIBRATION |
                InertialTypes::EstimationControlOption::ENABLE_SOFT_IRON_AUTO_CALIBRATION
            );

        case InertialModels::node_3dm_gx5_45:
        case InertialModels::node_3dm_gx5_35:
        case InertialModels::node_3dm_gx5_10:
        case InertialModels::node_3dm_gx3_15:
        case InertialModels::node_3dm_gx3_25:
        case InertialModels::node_3dm_gx3_35:
        case InertialModels::node_3dm_gx2:
        case InertialModels::node_3dm_cv5_45:
        case InertialModels::node_3dm_cv5_10:
        case InertialModels::node_3dm:
        case InertialModels::node_fasA:
        case InertialModels::node_3dm_dh3:
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

        InertialModels::NodeModel model = InertialModels::nodeFromModelString(m_nodeInfo.deviceInfo().modelNumber);
        switch (model)
        {
            case InertialModels::node_3dm_gx4_45:
            case InertialModels::node_3dm_gx4_25:
            case InertialModels::node_3dm_gx4_15:
            case InertialModels::node_3dm_gx3_45:
            case InertialModels::node_3dm_gx3_35:
            case InertialModels::node_3dm_gx3_25:
            case InertialModels::node_3dm_gx3_15:
            case InertialModels::node_3dm_gx2:
            case InertialModels::node_3dm_rq1_45:
            case InertialModels::node_3dm_gq4_45:
            case InertialModels::node_3dm:
            case InertialModels::node_fasA:
            case InertialModels::node_3dm_dh3:
                return {
                    InertialTypes::AdaptiveMeasurementMode::ADAPTIVE_MEASUREMENT_DISABLE,
                    InertialTypes::AdaptiveMeasurementMode::ADAPTIVE_MEASUREMENT_ENABLE_FIXED 
                };

            case InertialModels::node_3dm_gx5_45:
            case InertialModels::node_3dm_gx5_35:
            case InertialModels::node_3dm_gx5_25:
            case InertialModels::node_3dm_gx5_15:
            case InertialModels::node_3dm_gx5_10:
            case InertialModels::node_3dm_cv5_45:
            case InertialModels::node_3dm_cv5_25:
            case InertialModels::node_3dm_cv5_15:
            case InertialModels::node_3dm_cv5_10:
            default:
                return {
                    InertialTypes::AdaptiveMeasurementMode::ADAPTIVE_MEASUREMENT_DISABLE,
                    InertialTypes::AdaptiveMeasurementMode::ADAPTIVE_MEASUREMENT_ENABLE_FIXED, 
                    InertialTypes::AdaptiveMeasurementMode::ADAPTIVE_MEASUREMENT_ENABLE_AUTO
                };
        }
    }
}