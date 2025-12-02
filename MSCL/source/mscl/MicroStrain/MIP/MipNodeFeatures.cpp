/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "mscl/MicroStrain/MIP/MipNodeFeatures.h"

#include "mscl/MicroStrain/MIP/MipModels.h"
#include "mscl/MicroStrain/MIP/MipNodeInfo.h"

namespace mscl
{
    MipNodeFeatures::MipNodeFeatures(const MipNode_Impl* node) :
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
        const std::vector<uint16>& descriptors = nodeInfo().descriptors();

        //loop over all the descriptors we have
        for(uint16 desc : descriptors)
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

        const std::vector<uint16>& descriptors = nodeInfo().descriptors();

        //loop over all the descriptors we have
        for(uint16 desc : descriptors)
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
        const std::vector<uint16>& descriptors = nodeInfo().descriptors();
        return std::find(descriptors.begin(), descriptors.end(), static_cast<uint16>(commandId)) != descriptors.end();
    }

    MipTypes::MipCommands MipNodeFeatures::supportedCommands() const
    {
        MipTypes::MipCommands result;

        const std::vector<uint16>& descriptors = nodeInfo().descriptors();

        for(const uint16& desc : descriptors)
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

        return *m_nodeInfo;
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
        if (!supportsCommand(MipTypes::Command::CMD_EF_GNSS_SRC_CTRL))
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
        const MipModel model(nodeInfo().deviceInfo().modelNumber);

        switch (model.baseModel().nodeModel())
        {
            case MipModels::node_3dm_gq7:
            {
                return{
                    DeviceCommPort(DeviceCommPort::InterfaceId::MAIN),
                    DeviceCommPort(DeviceCommPort::InterfaceId::AUX)
                };
            }

            case MipModels::node_3dm_cv7_ar:
            case MipModels::node_3dm_cv7_ahrs:
            case MipModels::node_3dm_gv7_ar:
            case MipModels::node_3dm_gv7_ahrs:
            {
                return {
                    DeviceCommPort(DeviceCommPort::InterfaceId::MAIN),
                    DeviceCommPort(DeviceCommPort::InterfaceId::UART1),
                    DeviceCommPort(DeviceCommPort::InterfaceId::USB1)
                };
            }
            case MipModels::node_3dm_cv7_ins:
            {
                return {
                    DeviceCommPort(DeviceCommPort::InterfaceId::MAIN),
                    DeviceCommPort(DeviceCommPort::InterfaceId::UART1),
                    DeviceCommPort(DeviceCommPort::InterfaceId::UART2),
                    DeviceCommPort(DeviceCommPort::InterfaceId::UART3),
                    DeviceCommPort(DeviceCommPort::InterfaceId::USB1)
                };
            }
            case MipModels::node_3dm_gv7_ins:
            {
                return {
                    DeviceCommPort(DeviceCommPort::InterfaceId::MAIN),
                    DeviceCommPort(DeviceCommPort::InterfaceId::UART1),
                    DeviceCommPort(DeviceCommPort::InterfaceId::UART2),
                    DeviceCommPort(DeviceCommPort::InterfaceId::USB1)
                };
            }
            case MipModels::node_3dm_cv7_gnss_ins:
            {
                return {
                    DeviceCommPort(DeviceCommPort::InterfaceId::MAIN),
                    DeviceCommPort(DeviceCommPort::InterfaceId::UART1),
                    DeviceCommPort(DeviceCommPort::InterfaceId::UART2),
                    DeviceCommPort(DeviceCommPort::InterfaceId::UART3),
                    DeviceCommPort(DeviceCommPort::InterfaceId::USB1),
                    DeviceCommPort(DeviceCommPort::InterfaceId::USB2)
                };
            }
            default:
            {
                return {
                    DeviceCommPort(DeviceCommPort::InterfaceId::MAIN)
                };
            }
        }
    }

    const VehicleModeTypes MipNodeFeatures::supportedVehicleModeTypes() const
    {
        if (!supportsCommand(MipTypes::Command::CMD_EF_VEHIC_DYNAMICS_MODE))
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

    const StatusSelectors MipNodeFeatures::supportedStatusSelectors() const
    {
        if (!supportsCommand(MipTypes::Command::CMD_DEVICE_STATUS)) {
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
        if (!supportsCommand(MipTypes::Command::CMD_EF_HEADING_UPDATE_CTRL))
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
        if (!supportsCommand(MipTypes::Command::CMD_EF_INITIALIZATION_CONFIG))
        {
            return HeadingAlignmentMethod(0);
        }

        MipModel model(nodeInfo().deviceInfo().modelNumber);
        switch (model.baseModel().nodeModel())
        {
            case MipModels::node_3dm_cv7_ins:
            case MipModels::node_3dm_gv7_ins:
            {
                return HeadingAlignmentMethod(
                    GNSS_Kinematic |
                    Magnetometer |
                    External
                );
            }
            case MipModels::node_3dm_gq7:
            {
                return HeadingAlignmentMethod(
                    GNSS_DualAntenna |
                    GNSS_Kinematic |
                    Magnetometer
                );
            }
            case MipModels::node_3dm_cv7_gnss_ins:
            default:
            {
                return HeadingAlignmentMethod(0xFF);
            }
        }
    }

    const EstimationControlOptions MipNodeFeatures::supportedEstimationControlOptions() const
    {
        if (!supportsCommand(MipTypes::Command::CMD_EF_BIAS_EST_CTRL))
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
        if (!supportsCommand(MipTypes::Command::CMD_EF_GRAV_MAGNITUDE_ERR_ADAPT_MEASURE)
            && !supportsCommand(MipTypes::Command::CMD_EF_MAG_MAGNITUDE_ERR_ADAPT_MEASURE)
            && !supportsCommand(MipTypes::Command::CMD_EF_MAG_DIP_ANGLE_ERR_ADAPT_MEASURE))
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
        if (!supportsCommand(MipTypes::Command::CMD_EF_ADAPTIVE_FILTER_OPTIONS))
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
        case MipModels::node_3dm_cv7_gnss_ins:
        default:
            return{
                InertialTypes::AutoAdaptiveFilteringLevel::FILTERING_OFF,
                InertialTypes::AutoAdaptiveFilteringLevel::FILTERING_CONSERVATIVE,
                InertialTypes::AutoAdaptiveFilteringLevel::FILTERING_MODERATE,
                InertialTypes::AutoAdaptiveFilteringLevel::FILTERING_AGGRESSIVE
            };
        }
    }

    const AidingMeasurementSourceOptions MipNodeFeatures::supportedAidingMeasurementOptions() const
    {
        if (!supportsCommand(MipTypes::Command::CMD_EF_AIDING_MEASUREMENT_ENABLE))
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
                    InertialTypes::AidingMeasurementSource::EXTERNAL_HEADING_AIDING,
                    InertialTypes::AidingMeasurementSource::EXTERNAL_ALTIMETER_AIDING,
                    InertialTypes::AidingMeasurementSource::EXTERNAL_MAGNETOMETER_AIDING,
                    InertialTypes::AidingMeasurementSource::BODY_FRAME_VEL_AIDING
                };

            case MipModels::node_3dm_gq7:
                return{
                    InertialTypes::AidingMeasurementSource::GNSS_POS_VEL_AIDING,
                    InertialTypes::AidingMeasurementSource::GNSS_HEADING_AIDING,
                    InertialTypes::AidingMeasurementSource::ALTIMETER_AIDING,
                    InertialTypes::AidingMeasurementSource::ODOMETER_AIDING,
                    InertialTypes::AidingMeasurementSource::MAGNETOMETER_AIDING,
                    InertialTypes::AidingMeasurementSource::EXTERNAL_HEADING_AIDING
                };

            case MipModels::node_3dm_cv7_gnss_ins:
            default:
                return {
                    InertialTypes::AidingMeasurementSource::GNSS_POS_VEL_AIDING,
                    InertialTypes::AidingMeasurementSource::GNSS_HEADING_AIDING,
                    InertialTypes::AidingMeasurementSource::ALTIMETER_AIDING,
                    InertialTypes::AidingMeasurementSource::ODOMETER_AIDING,
                    InertialTypes::AidingMeasurementSource::MAGNETOMETER_AIDING,
                    InertialTypes::AidingMeasurementSource::EXTERNAL_HEADING_AIDING,
                    InertialTypes::AidingMeasurementSource::EXTERNAL_ALTIMETER_AIDING,
                    InertialTypes::AidingMeasurementSource::EXTERNAL_MAGNETOMETER_AIDING,
                    InertialTypes::AidingMeasurementSource::BODY_FRAME_VEL_AIDING
                };
        }
    }

    const PpsSourceOptions MipNodeFeatures::supportedPpsSourceOptions() const
    {
        if (!supportsCommand(MipTypes::Command::CMD_PPS_SOURCE))
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

        case MipModels::node_3dm_gq7:
        case MipModels::node_3dm_cv7_gnss_ins:
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

    const std::vector<GpioPinId> MipNodeFeatures::supportedGpioPins() const
    {
        const MipModel model(nodeInfo().deviceInfo().modelNumber);
        const MipModels::NodeModel nodeModel = model.baseModel().nodeModel();

        switch (nodeModel)
        {
            case MipModels::node_3dm_gv7_ahrs:
            case MipModels::node_3dm_gv7_ar:
            case MipModels::node_3dm_gv7_ins:
            {
                return { 1, 2 };
            }
            case MipModels::node_3dm_cv7_ahrs:
            case MipModels::node_3dm_cv7_ar:
            case MipModels::node_3dm_cv7_ins:
            case MipModels::node_3dm_cv7_gnss_ins:
            case MipModels::node_3dm_gq7:
            {
                return { 1, 2, 3, 4 };
            }
            // No supported GPIO pins
            default:
            {
                return {};
            }
        }
    }

    const GpioPinModeOptions MipNodeFeatures::supportedGpioPinModes(GpioConfiguration::Feature feature, uint8 behavior) const
    {
        if (!supportsCommand(MipTypes::Command::CMD_GPIO_CONFIGURATION))
        {
            return GpioPinModeOptions();
        }

        if ((feature == GpioConfiguration::ENCODER_FEATURE && behavior != GpioConfiguration::EncoderBehavior::ENCODER_UNUSED)
            || (feature == GpioConfiguration::GPIO_FEATURE && behavior == GpioConfiguration::GpioBehavior::GPIO_INPUT))
        {
            return {
                GpioConfiguration::PinModes::NONE,
                GpioConfiguration::PinModes::PULLDOWN,
                GpioConfiguration::PinModes::PULLUP
            };
        }

        if (feature == GpioConfiguration::GPIO_FEATURE
            && (behavior == GpioConfiguration::GpioBehavior::GPIO_OUTPUT_LOW || behavior == GpioConfiguration::GpioBehavior::GPIO_OUTPUT_HIGH))
        {
            return {
                GpioConfiguration::PinModes::NONE,
                GpioConfiguration::PinModes::OPEN_DRAIN,
                GpioConfiguration::PinModes(GpioConfiguration::PinModes::OPEN_DRAIN | GpioConfiguration::PinModes::PULLUP)
            };
        }

        if (feature == GpioConfiguration::EVENT_TIMESTAMP_FEATURE) // same modes available for all Event Timestamp behaviors
        {
            return {
                GpioConfiguration::PinModes::NONE,
                GpioConfiguration::PinModes::PULLDOWN,
                GpioConfiguration::PinModes::PULLUP
            };
        }

        if (feature == GpioConfiguration::UART_FEATURE)
        {
            switch (behavior)
            {
                case GpioConfiguration::UartBehavior::UART_PORT2_TX:
                {
                    return {
                        GpioConfiguration::PinModes::NONE,
                        GpioConfiguration::PinModes::OPEN_DRAIN
                    };
                }
                case GpioConfiguration::UartBehavior::UART_PORT2_RX:
                {
                    return {
                        GpioConfiguration::PinModes::NONE,
                        GpioConfiguration::PinModes::PULLDOWN,
                        GpioConfiguration::PinModes::PULLUP
                    };
                }
                case GpioConfiguration::UartBehavior::UART_PORT3_TX:
                {
                    return {
                        GpioConfiguration::PinModes::NONE,
                        GpioConfiguration::PinModes::OPEN_DRAIN
                    };
                }
                case GpioConfiguration::UartBehavior::UART_PORT3_RX:
                {
                    return {
                        GpioConfiguration::PinModes::NONE,
                        GpioConfiguration::PinModes::PULLDOWN,
                        GpioConfiguration::PinModes::PULLUP
                    };
                }
                default:
                {
                    break;
                }
            }
        }

        return GpioPinModeOptions();
    }

    const GpioBehaviorModes MipNodeFeatures::supportedGpioBehaviors(GpioConfiguration::Feature feature, GpioPinId pin) const
    {
        if (!supportsCommand(MipTypes::Command::CMD_GPIO_CONFIGURATION) || feature == GpioConfiguration::UNUSED_FEATURE)
        {
            return GpioBehaviorModes();
        }

        // Make sure the pin is supported by the device first
        if (pin != 0)
        {
            const std::vector<GpioPinId> supportedPins = supportedGpioPins();

            if (std::find(supportedPins.begin(), supportedPins.end(), pin) == supportedPins.end())
            {
                return GpioBehaviorModes();
            }
        }

        const MipModels::NodeModel nodeModel = MipModel(nodeInfo().deviceInfo().modelNumber).baseModel().nodeModel();

        switch (feature)
        {
            // GPIO Feature is supported on all available pins
            case GpioConfiguration::Feature::GPIO_FEATURE:
            {
                return {
                    {
                        GpioConfiguration::GpioBehavior::GPIO_INPUT,
                        supportedGpioPinModes(feature, GpioConfiguration::GpioBehavior::GPIO_INPUT)
                    },
                    {
                        GpioConfiguration::GpioBehavior::GPIO_OUTPUT_LOW,
                        supportedGpioPinModes(feature, GpioConfiguration::GpioBehavior::GPIO_OUTPUT_LOW)
                    },
                    {
                        GpioConfiguration::GpioBehavior::GPIO_OUTPUT_HIGH,
                        supportedGpioPinModes(feature, GpioConfiguration::GpioBehavior::GPIO_OUTPUT_HIGH)
                    }
                };
            }
            case GpioConfiguration::Feature::PPS_FEATURE:
            {
                switch (nodeModel)
                {
                    case MipModels::node_3dm_gq7:
                    {
                        if (pin != 1 && pin != 3)
                        {
                            return GpioBehaviorModes();
                        }

                        break;
                    }
                    case MipModels::node_3dm_cv7_ahrs:
                    case MipModels::node_3dm_cv7_ar:
                    case MipModels::node_3dm_cv7_ins:
                    case MipModels::node_3dm_cv7_gnss_ins:
                    case MipModels::node_3dm_gv7_ahrs:
                    case MipModels::node_3dm_gv7_ar:
                    case MipModels::node_3dm_gv7_ins:
                    {
                        break;
                    }
                    default:
                    {
                        return GpioBehaviorModes();
                    }
                }

                return {
                    {
                        GpioConfiguration::PpsBehavior::PPS_INPUT,
                        GpioPinModeOptions()
                    },
                    {
                        GpioConfiguration::PpsBehavior::PPS_OUTPUT,
                        GpioPinModeOptions()
                    }
                };
            }
            case GpioConfiguration::Feature::ENCODER_FEATURE:
            {
                switch (nodeModel)
                {
                    case MipModels::node_3dm_gq7:
                    {
                        if (pin == 1)
                        {
                            return {
                                {
                                    GpioConfiguration::EncoderBehavior::ENCODER_A,
                                    supportedGpioPinModes(feature, GpioConfiguration::EncoderBehavior::ENCODER_A)
                                }
                            };
                        }

                        if (pin == 2)
                        {
                            return {
                                {
                                    GpioConfiguration::EncoderBehavior::ENCODER_B,
                                    supportedGpioPinModes(feature, GpioConfiguration::EncoderBehavior::ENCODER_B)
                                }
                            };
                        }

                        break;
                    }
                    case MipModels::node_3dm_cv7_ins:
                    case MipModels::node_3dm_cv7_gnss_ins:
                    case MipModels::node_3dm_gv7_ins:
                    {
                        if (pin == 3)
                        {
                            return {
                                {
                                    GpioConfiguration::EncoderBehavior::ENCODER_A,
                                    supportedGpioPinModes(feature, GpioConfiguration::EncoderBehavior::ENCODER_A)
                                }
                            };
                        }

                        if (pin == 4)
                        {
                            return {
                                {
                                    GpioConfiguration::EncoderBehavior::ENCODER_B,
                                    supportedGpioPinModes(feature, GpioConfiguration::EncoderBehavior::ENCODER_B)
                                }
                            };
                        }

                        break;
                    }
                    default:
                    {
                        break;
                    }
                }

                return GpioBehaviorModes();
            }
            case GpioConfiguration::Feature::EVENT_TIMESTAMP_FEATURE:
            {
                switch (nodeModel)
                {
                    case MipModels::node_3dm_cv7_ahrs:
                    case MipModels::node_3dm_cv7_ar:
                    case MipModels::node_3dm_cv7_ins:
                    case MipModels::node_3dm_cv7_gnss_ins:
                    case MipModels::node_3dm_gv7_ahrs:
                    case MipModels::node_3dm_gv7_ar:
                    case MipModels::node_3dm_gv7_ins:
                    {
                        return {
                            {
                                GpioConfiguration::EventTimestampBehavior::TIMESTAMP_RISING,
                                supportedGpioPinModes(feature, GpioConfiguration::EventTimestampBehavior::TIMESTAMP_RISING)
                            },
                            {
                                GpioConfiguration::EventTimestampBehavior::TIMESTAMP_FALLING,
                                supportedGpioPinModes(feature, GpioConfiguration::EventTimestampBehavior::TIMESTAMP_FALLING)
                            },
                            {
                                GpioConfiguration::EventTimestampBehavior::TIMESTAMP_EITHER,
                                supportedGpioPinModes(feature, GpioConfiguration::EventTimestampBehavior::TIMESTAMP_EITHER)
                            }
                        };
                    }
                    default:
                    {
                        return GpioBehaviorModes();
                    }
                }
            }
            case GpioConfiguration::Feature::UART_FEATURE:
            {
                switch (nodeModel)
                {
                    case MipModels::node_3dm_cv7_ins:
                    case MipModels::node_3dm_cv7_gnss_ins:
                    case MipModels::node_3dm_gv7_ins:
                    {
                        if (pin == 1 || pin == 2)
                        {
                            return {
                                {
                                    GpioConfiguration::UartBehavior::UART_PORT2_TX,
                                    supportedGpioPinModes(GpioConfiguration::Feature::UART_FEATURE, GpioConfiguration::UartBehavior::UART_PORT2_TX)
                                },
                                {
                                    GpioConfiguration::UartBehavior::UART_PORT2_RX,
                                    supportedGpioPinModes(GpioConfiguration::Feature::UART_FEATURE, GpioConfiguration::UartBehavior::UART_PORT2_RX)
                                }
                            };
                        }

                        return {
                            {
                                GpioConfiguration::UartBehavior::UART_PORT3_TX,
                                supportedGpioPinModes(GpioConfiguration::Feature::UART_FEATURE, GpioConfiguration::UartBehavior::UART_PORT3_TX)
                            },
                            {
                                GpioConfiguration::UartBehavior::UART_PORT3_RX,
                                supportedGpioPinModes(GpioConfiguration::Feature::UART_FEATURE, GpioConfiguration::UartBehavior::UART_PORT3_RX)
                            }
                        };
                    }
                    default:
                    {
                        return GpioBehaviorModes();
                    }
                }
            }
            default:
            {
                return GpioBehaviorModes();
            }
        }
    }

    const GpioFeatureBehaviors MipNodeFeatures::supportedGpioFeatures(uint8 pin) const
    {
        if (!supportsCommand(MipTypes::Command::CMD_GPIO_CONFIGURATION))
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
        if (!supportsCommand(MipTypes::Command::CMD_GPIO_CONFIGURATION))
        {
            return GpioPinOptions();
        }

        // Build pin options
        GpioPinOptions pinOptions;

        // Iterate supported pin IDs
        for (const GpioPinId pinId : supportedGpioPins())
        {
            // Build feature behaviors
            GpioFeatureBehaviors features;

            // All pins support unused behaviors
            const GpioBehaviorModes unusedBehaviors = supportedGpioBehaviors(GpioConfiguration::Feature::UNUSED_FEATURE, pinId);
            features.emplace(GpioConfiguration::Feature::UNUSED_FEATURE, unusedBehaviors);

            const GpioBehaviorModes gpioBehaviors = supportedGpioBehaviors(GpioConfiguration::Feature::GPIO_FEATURE, pinId);
            if (!gpioBehaviors.empty())
            {
                features.emplace(GpioConfiguration::Feature::GPIO_FEATURE, gpioBehaviors);
            }

            const GpioBehaviorModes ppsBehaviors = supportedGpioBehaviors(GpioConfiguration::Feature::PPS_FEATURE, pinId);
            if (!ppsBehaviors.empty())
            {
                features.emplace(GpioConfiguration::Feature::PPS_FEATURE, ppsBehaviors);
            }

            const GpioBehaviorModes encoderBehaviors = supportedGpioBehaviors(GpioConfiguration::Feature::ENCODER_FEATURE, pinId);
            if (!encoderBehaviors.empty())
            {
                features.emplace(GpioConfiguration::Feature::ENCODER_FEATURE, encoderBehaviors);
            }

            const GpioBehaviorModes eventBehaviors = supportedGpioBehaviors(GpioConfiguration::Feature::EVENT_TIMESTAMP_FEATURE, pinId);
            if (!eventBehaviors.empty())
            {
                features.emplace(GpioConfiguration::Feature::EVENT_TIMESTAMP_FEATURE, eventBehaviors);
            }

            const GpioBehaviorModes uartBehaviors = supportedGpioBehaviors(GpioConfiguration::Feature::UART_FEATURE, pinId);
            if (!uartBehaviors.empty())
            {
                features.emplace(GpioConfiguration::Feature::UART_FEATURE, uartBehaviors);
            }

            // Add features for target id to pin options
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

        case MipModels::node_3dm_cv7_gnss_ins:
        {
            return {
                { MipChannelIdentifier::GPS, { 0, GnssSignalConfiguration::GpsSignal::L1CA | GnssSignalConfiguration::GpsSignal::L5 } },
                { MipChannelIdentifier::GLONASS, { 0, GnssSignalConfiguration::GlonassSignal::L1OF } },
                { MipChannelIdentifier::GALILEO, { 0, GnssSignalConfiguration::GalileoSignal::E1 | GnssSignalConfiguration::GalileoSignal::E5A } },
                { MipChannelIdentifier::BEIDOU, { 0, GnssSignalConfiguration::BeiDouSignal::B1 | GnssSignalConfiguration::BeiDouSignal::B2A } }
            };
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
            return{
                InertialTypes::GeographicSourceOption::NONE,
                InertialTypes::GeographicSourceOption::MANUAL
            };

        case MipModels::node_3dm_gq7:
            return{
                InertialTypes::GeographicSourceOption::WORLD_MAGNETIC_MODEL,
                InertialTypes::GeographicSourceOption::MANUAL
            };

        case MipModels::node_3dm_gv7_ins:
        case MipModels::node_3dm_cv7_ins:
        case MipModels::node_3dm_cv7_gnss_ins:
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
            return{
                InertialTypes::GeographicSourceOption::NONE,
                InertialTypes::GeographicSourceOption::MANUAL
            };

        case MipModels::node_3dm_gq7:
            return{
                InertialTypes::GeographicSourceOption::WORLD_MAGNETIC_MODEL,
                InertialTypes::GeographicSourceOption::MANUAL
            };

        case MipModels::node_3dm_gv7_ins:
        case MipModels::node_3dm_cv7_ins:
        case MipModels::node_3dm_cv7_gnss_ins:
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
            return{
                InertialTypes::GeographicSourceOption::NONE,
                InertialTypes::GeographicSourceOption::MANUAL
            };

        case MipModels::node_3dm_gq7:
            return{
                InertialTypes::GeographicSourceOption::WORLD_MAGNETIC_MODEL,
                InertialTypes::GeographicSourceOption::MANUAL
            };

        case MipModels::node_3dm_gv7_ins:
        case MipModels::node_3dm_cv7_ins:
        case MipModels::node_3dm_cv7_gnss_ins:
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
        if (!supportsCommand(MipTypes::Command::CMD_EVENT_TRIGGER_CONFIGURATION))
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
        case MipModels::node_3dm_cv7_gnss_ins:
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

    uint8 MipNodeFeatures::maxMeasurementReferenceFrameId() const
    {
        if (!supportsCommand(MipTypes::CMD_AIDING_FRAME_CONFIG))
        {
            return 0;
        }

        const MipModel model(nodeInfo().deviceInfo().modelNumber);

        switch (model.baseModel().nodeModel())
        {
            case MipModels::node_3dm_cv7_gnss_ins:
            {
                return 3;
            }
            default:
            {
                return 4;
            }
        }
    }
} // namespace mscl
