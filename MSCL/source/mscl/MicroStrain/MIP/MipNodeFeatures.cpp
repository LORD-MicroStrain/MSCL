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
    MipNodeFeatures::MipNodeFeatures(const MipNode_Impl* node):
        m_node(node)
    {}

    std::unique_ptr<MipNodeFeatures> MipNodeFeatures::create(const MipNode_Impl* node)
    {
        return std::unique_ptr<MipNodeFeatures>(new MipNodeFeatures(node));
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
            case MipTypes::CLASS_SYSTEM:
                return true;

            default:
                return false;
        }
    }

    bool MipNodeFeatures::supportsCategory(MipTypes::DataClass dataClass) const
    {
        const auto& descriptors = nodeInfo().descriptors();

        //loop over all the descriptors we have
        for(auto desc : descriptors)
        {
            //if the MSB of the descriptor matches the DataClass being requested
            if(Utils::msb(static_cast<uint16>(desc)) == static_cast<uint16>(dataClass))
            {
                //the device supports this category
                return true;
            }
        }

        //no descriptors found that match the requested category
        return false;
    }

    bool MipNodeFeatures::supportsChannelField(MipTypes::ChannelField fieldId) const
    {
        return !filterSupportedChannelFields({ fieldId }).empty();
    }

    MipTypes::MipChannelFields MipNodeFeatures::filterSupportedChannelFields(const MipTypes::MipChannelFields& fields) const
    {
        MipTypes::MipChannelFields supportedFields;
        std::map<MipTypes::DataClass, MipTypes::MipChannelFields> cacheSupported;
        for (MipTypes::ChannelField fieldId : fields)
        {
            MipTypes::DataClass dataSet = MipTypes::channelFieldToDataClass(fieldId);
            MipTypes::MipChannelFields setFields;
            auto found = cacheSupported.find(dataSet);
            if (found == cacheSupported.end())
            {
                setFields = supportedChannelFields(dataSet);
                cacheSupported.emplace(dataSet, setFields);
            }
            else
            {
                setFields = found->second;
            }

            if (std::find(setFields.begin(), setFields.end(), fieldId) != setFields.end())
            {
                supportedFields.push_back(fieldId);
            }
        }

        return supportedFields;
    }

    MipTypes::MipChannelFields MipNodeFeatures::supportedChannelFields(MipTypes::DataClass dataClass) const
    {
        MipTypes::MipChannelFields result;

        const auto& descriptors = nodeInfo().descriptors();

        //loop over all the descriptors we have
        for(auto desc : descriptors)
        {
            //if the MSB of the descriptor matches the DataClass being requested
            if((dataClass == MipTypes::DataClass(-1) && isChannelField(desc))
                || Utils::msb(static_cast<uint16>(desc)) == static_cast<uint16>(dataClass))
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
        const auto& descriptors = nodeInfo().descriptors();
        return (std::find(descriptors.begin(), descriptors.end(), static_cast<uint16>(commandId)) != descriptors.end());
    }

    MipTypes::MipCommands MipNodeFeatures::supportedCommands() const
    {
        MipTypes::MipCommands result;

        auto& descriptors = nodeInfo().descriptors();

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
        return nodeInfo().supportedSampleRates(dataClass);
    }

    const uint16& MipNodeFeatures::baseDataRate(MipTypes::DataClass dataClass) const
    {
        return nodeInfo().baseDataRate(dataClass);
    }

    const MipNodeInfo& MipNodeFeatures::nodeInfo() const
    {
        //if we haven't initialized the MipNodeInfo
        if (!m_nodeInfo)
        {
            m_nodeInfo.reset(new MipNodeInfo(m_node));
        }

        return (*m_nodeInfo);
    }

    void MipNodeFeatures::resetNodeInfo()
    {
        //if we haven't initialized the MipNodeInfo, no need to reset it
        if (!m_nodeInfo)
        {
            return;
        }

        m_nodeInfo.reset();
    }

    const GnssReceivers& MipNodeFeatures::gnssReceiverInfo() const
    {
        return nodeInfo().gnssReceiverInfo();
    }

    const GnssSources MipNodeFeatures::supportedGnssSources() const
    {
        if (!supportsCommand(mscl::MipTypes::Command::CMD_EF_GNSS_SRC_CTRL))
        {
            return {};
        }

        const MipModel model(nodeInfo().deviceInfo().modelNumber);
        const Version fwVersion(nodeInfo().deviceInfo().fwVersion);

        //TODO: Update version check when GQ7 R3 fw has been released
        if (fwVersion >= Version(1, 1) || fwVersion < Version(1, 0))
        {
            switch (model.baseModel().nodeModel())
            {
            case MipModels::node_3dm_gq7:
                return{
                    InertialTypes::GNSS_Source::INTERNAL_GNSS_ALL,
                    InertialTypes::GNSS_Source::EXTERNAL_GNSS,
                    InertialTypes::GNSS_Source::INTERNAL_GNSS1,
                    InertialTypes::GNSS_Source::INTERNAL_GNSS2
                };
            default:
                return{
                    InertialTypes::GNSS_Source::INTERNAL_GNSS_ALL,
                    InertialTypes::GNSS_Source::EXTERNAL_GNSS
                };
            }
        }

        return{
            InertialTypes::GNSS_Source::INTERNAL_GNSS_ALL,
            InertialTypes::GNSS_Source::EXTERNAL_GNSS
        };
    }

    const SupportedSensorRanges& MipNodeFeatures::supportedSensorRanges() const
    {
        return nodeInfo().supportedSensorRanges();
    }

    const SensorRanges MipNodeFeatures::supportedSensorRanges(SensorRange::Type type) const
    {
        SensorRangeOptions rangeOptions = nodeInfo().supportedSensorRanges().options();
        auto typeEntry = rangeOptions.find(type);
        if (typeEntry == rangeOptions.end())
        {
            std::stringstream message;
            message << "Sensor Range Type (" << type << ") not supported on this device.";
            throw Error_NotSupported(message.str());
        }

        return typeEntry->second;
    }

    const CommPortInfo MipNodeFeatures::getCommPortInfo() const
    {
        MipModel model(nodeInfo().deviceInfo().modelNumber);
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

        MipModel model(nodeInfo().deviceInfo().modelNumber);
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

        MipModel model(nodeInfo().deviceInfo().modelNumber);
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
        MipModel model(nodeInfo().deviceInfo().modelNumber);
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

        MipModel model(nodeInfo().deviceInfo().modelNumber);
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

    const HeadingAlignmentMethod MipNodeFeatures::supportedHeadingAlignmentMethods() const
    {
        if (!supportsCommand(mscl::MipTypes::Command::CMD_EF_INITIALIZATION_CONFIG))
        {
            return HeadingAlignmentMethod(0);
        }
        
        MipModel model(nodeInfo().deviceInfo().modelNumber);
        switch (model.baseModel().nodeModel())
        {
        case MipModels::node_3dm_cv7_ins:
        case MipModels::node_3dm_gv7_ins:
            return HeadingAlignmentMethod(
                HeadingAlignmentOption::GNSS_Kinematic
                | HeadingAlignmentOption::Magnetometer
                | HeadingAlignmentOption::External
            );

        default:
            return HeadingAlignmentMethod(0xFF);
        }
    }

    const EstimationControlOptions MipNodeFeatures::supportedEstimationControlOptions() const
    {
        if (!supportsCommand(mscl::MipTypes::Command::CMD_EF_BIAS_EST_CTRL))
        {
            return{ EstimationControlOptions(0) };
        }

        MipModel model(nodeInfo().deviceInfo().modelNumber);
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

        MipModel model(nodeInfo().deviceInfo().modelNumber);
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

        MipModel model(nodeInfo().deviceInfo().modelNumber);
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
        case MipModels::node_3dm_gv7_ahrs:
        case MipModels::node_3dm_gv7_ar:
        case MipModels::node_3dm_gv7_ins:
        case MipModels::node_3dm_cv7_ins:
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

        MipModel model(nodeInfo().deviceInfo().modelNumber);

        switch(model.baseModel().nodeModel())
        {
            case MipModels::node_3dm_cv7_ahrs:
            case MipModels::node_3dm_gv7_ahrs:
                return{
                    InertialTypes::AidingMeasurementSource::MAGNETOMETER_AIDING,
                    InertialTypes::AidingMeasurementSource::EXTERNAL_HEADING_AIDING
                };

            case MipModels::node_3dm_cv7_ar:
            case MipModels::node_3dm_gv7_ar:
                return {
                    InertialTypes::AidingMeasurementSource::EXTERNAL_HEADING_AIDING
                };

            case MipModels::node_3dm_gv7_ins:
            case MipModels::node_3dm_cv7_ins:
                return{
                    InertialTypes::AidingMeasurementSource::GNSS_POS_VEL_AIDING,
                    InertialTypes::AidingMeasurementSource::ALTIMETER_AIDING,
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

        MipModel model(nodeInfo().deviceInfo().modelNumber);
        switch (model.baseModel().nodeModel())
        {
        case MipModels::node_3dm_cv7_ahrs:
        case MipModels::node_3dm_cv7_ar:
        case MipModels::node_3dm_gv7_ahrs:
        case MipModels::node_3dm_gv7_ar:
        case MipModels::node_3dm_gv7_ins:
        case MipModels::node_3dm_cv7_ins:
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

        if (feature == GpioConfiguration::EVENT_TIMESTAMP_FEATURE) // same modes available for all Event Timestamp behaviors
        {
            return{
                GpioConfiguration::PinModes(0),
                GpioConfiguration::PinModes::PULLUP,
                GpioConfiguration::PinModes::PULLDOWN
            };
        }

        if (feature == GpioConfiguration::UART_FEATURE)
        {
            switch (behavior)
            {
            case GpioConfiguration::UartBehavior::UART_TRANSMIT:
                return{
                    GpioConfiguration::PinModes(0),
                    GpioConfiguration::PinModes::OPEN_DRAIN,
                    GpioConfiguration::PinModes(GpioConfiguration::PinModes::OPEN_DRAIN | GpioConfiguration::PinModes::PULLUP)
                };

            case GpioConfiguration::UartBehavior::UART_RECEIVE:
                return{
                    GpioConfiguration::PinModes(0),
                    GpioConfiguration::PinModes::PULLUP,
                    GpioConfiguration::PinModes::PULLDOWN
                };

            default:
                break;
            }
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
            { GpioConfiguration::GpioBehavior::GPIO_INPUT_BEHAVIOR, supportedGpioPinModes(feature, GpioConfiguration::GpioBehavior::GPIO_INPUT_BEHAVIOR) },
            { GpioConfiguration::GpioBehavior::GPIO_OUTPUT_LOW_BEHAVIOR, supportedGpioPinModes(feature, GpioConfiguration::GpioBehavior::GPIO_OUTPUT_LOW_BEHAVIOR) },
            { GpioConfiguration::GpioBehavior::GPIO_OUTPUT_HIGH_BEHAVIOR, supportedGpioPinModes(feature, GpioConfiguration::GpioBehavior::GPIO_OUTPUT_HIGH_BEHAVIOR) }
            };

        case GpioConfiguration::Feature::PPS_FEATURE:
            return{
                { GpioConfiguration::PpsBehavior::PPS_INPUT, GpioPinModeOptions(0) },
                { GpioConfiguration::PpsBehavior::PPS_OUTPUT, GpioPinModeOptions(0) }
            };

        case GpioConfiguration::Feature::ENCODER_FEATURE:
            return{
                { GpioConfiguration::EncoderBehavior::ENCODER_A, supportedGpioPinModes(feature, GpioConfiguration::EncoderBehavior::ENCODER_A) },
                { GpioConfiguration::EncoderBehavior::ENCODER_B, supportedGpioPinModes(feature, GpioConfiguration::EncoderBehavior::ENCODER_A) }
            };

        case GpioConfiguration::Feature::EVENT_TIMESTAMP_FEATURE:
            return{
                { GpioConfiguration::EventTimestampBehavior::EVENT_TIMESTAMP_RISING, supportedGpioPinModes(feature, 0) },
                { GpioConfiguration::EventTimestampBehavior::EVENT_TIMESTAMP_FALLING, supportedGpioPinModes(feature, 0) },
                { GpioConfiguration::EventTimestampBehavior::EVENT_TIMESTAMP_EDGE, supportedGpioPinModes(feature, 0) }
            };

        case GpioConfiguration::Feature::UART_FEATURE:
        {
            MipModel model(nodeInfo().deviceInfo().modelNumber);
            switch (model.baseModel().nodeModel())
            {
            case MipModels::node_3dm_gv7_ins:
            case MipModels::node_3dm_cv7_ins:
                // technically Transmit is also supported, but the device won't actually output anything so no reason to configure it
                return{
                    { GpioConfiguration::UartBehavior::UART_RECEIVE, supportedGpioPinModes(feature, GpioConfiguration::UartBehavior::UART_RECEIVE) }
                };

            default:
                return{
                    { GpioConfiguration::UartBehavior::UART_TRANSMIT, supportedGpioPinModes(feature, GpioConfiguration::UartBehavior::UART_TRANSMIT) },
                    { GpioConfiguration::UartBehavior::UART_RECEIVE, supportedGpioPinModes(feature, GpioConfiguration::UartBehavior::UART_RECEIVE) }
                };
            }
        }

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

        const MipModel model(nodeInfo().deviceInfo().modelNumber);
        const MipModels::NodeModel nodeModel = model.baseModel().nodeModel();

        // get supported pin IDs
        std::vector<uint8> supportedPins;
        switch (nodeModel)
        {
        case MipModels::node_3dm_gv7_ahrs:
        case MipModels::node_3dm_gv7_ar:
        case MipModels::node_3dm_gv7_ins:
            supportedPins = { 1, 2 };
            break;

        // gq7, cv7
        default:
            supportedPins = { 1, 2, 3, 4 };
            break;
        }

        // get all available to avoid re-calling supportedGpioBehaviors() for a behavior type
        const GpioFeatureBehaviors availableBehaviors = {
                { GpioConfiguration::Feature::GPIO_FEATURE, supportedGpioBehaviors(GpioConfiguration::Feature::GPIO_FEATURE) },
                { GpioConfiguration::Feature::PPS_FEATURE, supportedGpioBehaviors(GpioConfiguration::Feature::PPS_FEATURE) },
                { GpioConfiguration::Feature::EVENT_TIMESTAMP_FEATURE, supportedGpioBehaviors(GpioConfiguration::Feature::EVENT_TIMESTAMP_FEATURE) },
                { GpioConfiguration::Feature::ENCODER_FEATURE, supportedGpioBehaviors(GpioConfiguration::Feature::ENCODER_FEATURE) },
                { GpioConfiguration::Feature::UART_FEATURE, supportedGpioBehaviors(GpioConfiguration::Feature::UART_FEATURE) }
        };
        
        // build pin options
        GpioPinOptions pinOptions;
        for (uint8 pinId : supportedPins)
        {
            // add features shared for all pins across all devices
            GpioFeatureBehaviors features = {
                { GpioConfiguration::Feature::UNUSED_FEATURE,{} },
                { GpioConfiguration::Feature::GPIO_FEATURE, availableBehaviors.at(GpioConfiguration::Feature::GPIO_FEATURE) }
            };

            // add device- and pin-specific features
            switch (nodeModel)
            {
            case MipModels::node_3dm_cv7_ahrs:
            case MipModels::node_3dm_cv7_ar:
            case MipModels::node_3dm_gv7_ahrs:
            case MipModels::node_3dm_gv7_ar:
            case MipModels::node_3dm_gv7_ins:
            case MipModels::node_3dm_cv7_ins:
                // CV7 and GV7 all pins support the same features (PPS, Event Timestamp)
                features.emplace(GpioConfiguration::Feature::PPS_FEATURE, availableBehaviors.at(GpioConfiguration::Feature::PPS_FEATURE));
                features.emplace(GpioConfiguration::Feature::EVENT_TIMESTAMP_FEATURE, availableBehaviors.at(GpioConfiguration::Feature::EVENT_TIMESTAMP_FEATURE));
                features.emplace(GpioConfiguration::Feature::UART_FEATURE, availableBehaviors.at(GpioConfiguration::Feature::UART_FEATURE));
                break;

            case MipModels::node_3dm_gq7:
                // GQ7 feature support varies across pins
                switch (pinId)
                {
                case 1:
                    features.emplace(GpioConfiguration::Feature::PPS_FEATURE, availableBehaviors.at(GpioConfiguration::Feature::PPS_FEATURE));
                    features.emplace(GpioConfiguration::Feature::ENCODER_FEATURE, availableBehaviors.at(GpioConfiguration::Feature::ENCODER_FEATURE));
                    break;
                case 2:
                    features.emplace(GpioConfiguration::Feature::ENCODER_FEATURE, availableBehaviors.at(GpioConfiguration::Feature::ENCODER_FEATURE));
                    break;
                case 3:
                    features.emplace(GpioConfiguration::Feature::PPS_FEATURE, availableBehaviors.at(GpioConfiguration::Feature::PPS_FEATURE));
                    break;
                default:
                    break;
                }
                break;

            default:
                break;
            }
            
            // add features for target id to pin options
            pinOptions.emplace(pinId, features);
        }

        return pinOptions;
    }

    GnssSignalConfigOptions MipNodeFeatures::supportedGnssSignalConfigurations() const
    {
        const MipModel model(nodeInfo().deviceInfo().modelNumber);

        switch (model.baseModel().nodeModel())
        {
        case MipModels::node_3dm_gq7:
        {
            const Version version(nodeInfo().deviceInfo().fwVersion);

            // Version 1.1.01 and above only supports both or no signal configurations for each constellation
            // Report all supported on dev versions for flexibility on dev devices
            if (version > Version(1, 0, 10))
            {
                return{
                    { MipChannelIdentifier::GPS, { 0, GnssSignalConfiguration::GpsSignal::L1CA | GnssSignalConfiguration::GpsSignal::L2C } },
                    { MipChannelIdentifier::GLONASS, { 0, GnssSignalConfiguration::GlonassSignal::L1OF | GnssSignalConfiguration::GlonassSignal::L2OF } },
                    { MipChannelIdentifier::GALILEO, { 0, GnssSignalConfiguration::GalileoSignal::E1 | GnssSignalConfiguration::GalileoSignal::E5B } },
                    { MipChannelIdentifier::BEIDOU, { 0, GnssSignalConfiguration::BeiDouSignal::B1 | GnssSignalConfiguration::BeiDouSignal::B2 } }
                };
            }
        }
        default:
            // Any configuration supported
            return {
                { MipChannelIdentifier::GPS, {
                    0,
                    GnssSignalConfiguration::GpsSignal::L1CA,
                    GnssSignalConfiguration::GpsSignal::L2C,
                    GnssSignalConfiguration::GpsSignal::L1CA | GnssSignalConfiguration::GpsSignal::L2C
                } },
                { MipChannelIdentifier::GLONASS, {
                    0,
                    GnssSignalConfiguration::GlonassSignal::L1OF,
                    GnssSignalConfiguration::GlonassSignal::L2OF,
                    GnssSignalConfiguration::GlonassSignal::L1OF | GnssSignalConfiguration::GlonassSignal::L2OF
                } },
                { MipChannelIdentifier::GALILEO, {
                    0,
                    GnssSignalConfiguration::GalileoSignal::E1,
                    GnssSignalConfiguration::GalileoSignal::E5B,
                    GnssSignalConfiguration::GalileoSignal::E1 | GnssSignalConfiguration::GalileoSignal::E5B,
                } },
                { MipChannelIdentifier::BEIDOU, {
                    0,
                    GnssSignalConfiguration::BeiDouSignal::B1,
                    GnssSignalConfiguration::BeiDouSignal::B2,
                    GnssSignalConfiguration::BeiDouSignal::B1 | GnssSignalConfiguration::BeiDouSignal::B2,
                } }
            };
        }
    }

    GeographicSources MipNodeFeatures::supportedDeclinationSources() const
    {
        const MipModel model(nodeInfo().deviceInfo().modelNumber);
        switch (model.baseModel().nodeModel())
        {
        case MipModels::node_3dm_cv7_ahrs:
        case MipModels::node_3dm_cv7_ar:
        case MipModels::node_3dm_gv7_ahrs:
        case MipModels::node_3dm_gv7_ar:
        case MipModels::node_3dm_gv7_ins:
        case MipModels::node_3dm_cv7_ins:
            return{
                InertialTypes::GeographicSourceOption::NONE,
                InertialTypes::GeographicSourceOption::MANUAL
            };

        case MipModels::node_3dm_gq7:
            return{
                InertialTypes::GeographicSourceOption::WORLD_MAGNETIC_MODEL,
                InertialTypes::GeographicSourceOption::MANUAL
            };

        default:
            return{
                InertialTypes::GeographicSourceOption::NONE,
                InertialTypes::GeographicSourceOption::WORLD_MAGNETIC_MODEL,
                InertialTypes::GeographicSourceOption::MANUAL
            };
        }
    }

    GeographicSources MipNodeFeatures::supportedInclinationSources() const
    {
        const MipModel model(nodeInfo().deviceInfo().modelNumber);
        switch (model.baseModel().nodeModel())
        {
        case MipModels::node_3dm_cv7_ahrs:
        case MipModels::node_3dm_cv7_ar:
        case MipModels::node_3dm_gv7_ahrs:
        case MipModels::node_3dm_gv7_ar:
        case MipModels::node_3dm_gv7_ins:
        case MipModels::node_3dm_cv7_ins:
            return{
                InertialTypes::GeographicSourceOption::NONE,
                InertialTypes::GeographicSourceOption::MANUAL
            };

        case MipModels::node_3dm_gq7:
            return{
                InertialTypes::GeographicSourceOption::WORLD_MAGNETIC_MODEL,
                InertialTypes::GeographicSourceOption::MANUAL
            };

        default:
            return{
                InertialTypes::GeographicSourceOption::NONE,
                InertialTypes::GeographicSourceOption::WORLD_MAGNETIC_MODEL,
                InertialTypes::GeographicSourceOption::MANUAL
            };
        }
    }

    GeographicSources MipNodeFeatures::supportedMagneticMagnitudeSources() const
    {
        const MipModel model(nodeInfo().deviceInfo().modelNumber);
        switch (model.baseModel().nodeModel())
        {
        case MipModels::node_3dm_cv7_ahrs:
        case MipModels::node_3dm_cv7_ar:
        case MipModels::node_3dm_gv7_ahrs:
        case MipModels::node_3dm_gv7_ar:
        case MipModels::node_3dm_gv7_ins:
        case MipModels::node_3dm_cv7_ins:
            return{
                InertialTypes::GeographicSourceOption::NONE,
                InertialTypes::GeographicSourceOption::MANUAL
            };

        case MipModels::node_3dm_gq7:
            return{
                InertialTypes::GeographicSourceOption::WORLD_MAGNETIC_MODEL,
                InertialTypes::GeographicSourceOption::MANUAL
            };

        default:
            return{
                InertialTypes::GeographicSourceOption::NONE,
                InertialTypes::GeographicSourceOption::WORLD_MAGNETIC_MODEL,
                InertialTypes::GeographicSourceOption::MANUAL
            };
        }
    }

    MipTypes::ChannelFieldQualifiers MipNodeFeatures::supportedEventThresholdChannels() const
    {
        if (!supportsCommand(mscl::MipTypes::Command::CMD_EVENT_TRIGGER_CONFIGURATION))
        {
            return{ MipTypes::ChannelFieldQualifiers() };
        }

        const MipModel model(nodeInfo().deviceInfo().modelNumber);

        MipTypes::MipChannelFields possibleFields;

        switch (model.baseModel().nodeModel())
        {
        case MipModels::node_3dm_cv7_ahrs:
        case MipModels::node_3dm_cv7_ar:
        case MipModels::node_3dm_gv7_ahrs:
        case MipModels::node_3dm_gv7_ar:
        case MipModels::node_3dm_gv7_ins:
        case MipModels::node_3dm_cv7_ins:
        default:
            possibleFields = {
                // 0x80: Sensor Data

                // (0x80, 0x04)
                MipTypes::CH_FIELD_SENSOR_SCALED_ACCEL_VEC,
                // (0x80, 0x05)
                MipTypes::CH_FIELD_SENSOR_SCALED_GYRO_VEC,
                // (0x80, 0x06)
                MipTypes::CH_FIELD_SENSOR_SCALED_MAG_VEC,
                // (0x80, 0x09)
                MipTypes::CH_FIELD_SENSOR_ORIENTATION_MATRIX,
                // (0x80, 0x0A)
                MipTypes::CH_FIELD_SENSOR_ORIENTATION_QUATERNION,
                // (0x80, 0x0C)
                MipTypes::CH_FIELD_SENSOR_EULER_ANGLES,
                // (0x80, 0x17)
                MipTypes::CH_FIELD_SENSOR_SCALED_AMBIENT_PRESSURE,
                // (0x80, 0xD3)
                MipTypes::CH_FIELD_SENSOR_SHARED_GPS_TIMESTAMP,
                // (0x80, 0xD5)
                MipTypes::CH_FIELD_SENSOR_SHARED_REFERENCE_TIMESTAMP,
                // (0x80, 0xD7)
                MipTypes::CH_FIELD_SENSOR_SHARED_EXTERNAL_TIMESTAMP,


                // 0x82 Filter Data

                // (0x82, 0x03)
                MipTypes::CH_FIELD_ESTFILTER_ESTIMATED_ORIENT_QUATERNION,
                // (0x82, 0x05)
                MipTypes::CH_FIELD_ESTFILTER_ESTIMATED_ORIENT_EULER,
                // (0x82, 0x06)
                MipTypes::CH_FIELD_ESTFILTER_ESTIMATED_GYRO_BIAS,
                // (0x82, 0x07)
                MipTypes::CH_FIELD_ESTFILTER_ESTIMATED_ACCEL_BIAS,
                // (0x82, 0x0A)
                MipTypes::CH_FIELD_ESTFILTER_ESTIMATED_ATT_UNCERT_EULER,
                // (0x82, 0x0B)
                MipTypes::CH_FIELD_ESTFILTER_ESTIMATED_GYRO_BIAS_UNCERT,
                // (0x82, 0x0C)
                MipTypes::CH_FIELD_ESTFILTER_ESTIMATED_ACCEL_BIAS_UNCERT,
                // (0x82, 0x0D)
                MipTypes::CH_FIELD_ESTFILTER_ESTIMATED_LINEAR_ACCEL,
                // (0x82, 0x0E)
                MipTypes::CH_FIELD_ESTFILTER_ESTIMATED_ANGULAR_RATE,
                // (0x82, 0x10)
                MipTypes::CH_FIELD_ESTFILTER_FILTER_STATUS,
                // (0x82, 0x12)
                MipTypes::CH_FIELD_ESTFILTER_ESTIMATED_ATT_UNCERT_QUAT,
                // (0x82, 0x13)
                MipTypes::CH_FIELD_ESTFILTER_ESTIMATED_GRAVITY_VECTOR,
                // (0x82, 0x1C)
                MipTypes::CH_FIELD_ESTFILTER_COMPENSATED_ACCEL,
                // (0x82, 0x21)
                MipTypes::CH_FIELD_ESTFILTER_PRESSURE_ALTITUDE,
                // (0x82, 0xD3)
                MipTypes::CH_FIELD_ESTFILTER_SHARED_GPS_TIMESTAMP,
                // (0x82, 0xD5)
                MipTypes::CH_FIELD_ESTFILTER_SHARED_REFERENCE_TIMESTAMP,
                // (0x82, 0xD7)
                MipTypes::CH_FIELD_ESTFILTER_SHARED_EXTERNAL_TIMESTAMP,


                // 0xA0 System Data

                // (0xA0, 0x01)
                //MipTypes::CH_FIELD_SYSTEM_BUILT_IN_TEST,
                // (0xA0, 0x02)
                MipTypes::CH_FIELD_SYSTEM_TIME_SYNC_STATUS,
                // (0xA0, 0x03)
                MipTypes::CH_FIELD_SYSTEM_GPIO_STATE,
                // (0xA0, 0xD3)
                MipTypes::CH_FIELD_SYSTEM_SHARED_GPS_TIMESTAMP,
                // (0xA0, 0xD5)
                MipTypes::CH_FIELD_SYSTEM_SHARED_REFERENCE_TIMESTAMP,
                // (0xA0, 0xD7)
                MipTypes::CH_FIELD_SYSTEM_SHARED_EXTERNAL_TIMESTAMP
            };
        }

        MipTypes::MipChannelFields supportedThresholdFields = filterSupportedChannelFields(possibleFields);
        return MipTypes::channelFieldQualifiers(supportedThresholdFields);
    }

    const EventSupportInfo MipNodeFeatures::supportedEventActionInfo() const
    {
        return nodeInfo().eventActionInfo();
    }

    const EventSupportInfo MipNodeFeatures::supportedEventTriggerInfo() const
    {
        return nodeInfo().eventTriggerInfo();
    }

    const bool MipNodeFeatures::supportsNorthCompensation() const
    {
        const MipModel model(nodeInfo().deviceInfo().modelNumber);

        switch (model.baseModel().nodeModel())
        {
        case MipModels::node_3dm_gx3_15:

        case MipModels::node_3dm_gx4_15:

        case MipModels::node_3dm_gx5_15:
        case MipModels::node_3dm_gx5_10:

        case MipModels::node_3dm_cv5_15:
        case MipModels::node_3dm_cv5_10:

        case MipModels::node_3dm_cx5_15:
        case MipModels::node_3dm_cx5_10:

        case MipModels::node_3dm_cl5_15:

        case MipModels::node_3dm_cv7_ar:
        case MipModels::node_3dm_gv7_ar:
            return false;

        default:
            return true;
        }
    }

    MipTypes::MipChannelFields MipNodeFeatures::supportedLowPassFilterChannelFields() const
    {
        const bool supportsLegacy = supportsCommand(MipTypes::CMD_LOWPASS_FILTER_SETTINGS);
        const bool supportsNew = supportsCommand(MipTypes::CMD_LOWPASS_ANTIALIASING_FILTER);

        MipTypes::MipChannelFields chs;
        if (supportsLegacy || supportsNew)
        {
            chs.insert(chs.end(), {
                MipTypes::ChannelField::CH_FIELD_SENSOR_SCALED_ACCEL_VEC,
                MipTypes::ChannelField::CH_FIELD_SENSOR_SCALED_GYRO_VEC,
                MipTypes::ChannelField::CH_FIELD_SENSOR_SCALED_MAG_VEC,
                MipTypes::ChannelField::CH_FIELD_SENSOR_SCALED_AMBIENT_PRESSURE
            });

            if (supportsNew)
            {
                chs.insert(chs.end(), {
                    MipTypes::ChannelField::CH_FIELD_ESTFILTER_ESTIMATED_LINEAR_ACCEL,
                    MipTypes::ChannelField::CH_FIELD_ESTFILTER_ESTIMATED_ANGULAR_RATE,
                    MipTypes::ChannelField::CH_FIELD_ESTFILTER_COMPENSATED_ACCEL
                });
            }

            chs = filterSupportedChannelFields(chs);
        }

        return chs;
    }
}
