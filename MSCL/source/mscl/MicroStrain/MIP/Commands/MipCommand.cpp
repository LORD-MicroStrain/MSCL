/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "mscl/MicroStrain/MIP/Commands/MipCommand.h"

namespace mscl
{
    /////  MipCommand  /////

    std::shared_ptr<GenericMipCommand::Response> MipCommand::createResponse(std::weak_ptr<ResponseCollector> collector)
    {
        std::shared_ptr<GenericMipCommand::Response> responseToSend(new GenericMipCommand::Response(commandType(),
            collector, true, responseExpected(), commandName(), buildMatchData(), fieldDataByte()));
        return responseToSend;
    }

    MipCommand::operator ByteStream() const
    {
        ByteStream command;

        if (MipCommand::supportsFunctionSelector(m_commandId, m_functionSelector)
            || (!isKnownCommand() && m_functionSelector != MipTypes::FunctionSelector(0))) // allows undefined commands to be manually sent with fn selectors (ex: for save as startup)
        {
            command.append_uint8(static_cast<uint8>(m_functionSelector));
        }

        for (Value val : m_data)
        {
            ValueType type = val.storedAs();
            switch (type)
            {
                case valueType_bool:
                {
                    command.append_uint8((val.as_bool() ? 1 : 0));
                    break;
                }
                case valueType_uint8:
                {
                    command.append_uint8(val.as_uint8());
                    break;
                }
                case valueType_uint16:
                {
                    command.append_uint16(val.as_uint16());
                    break;
                }
                case valueType_uint32:
                {
                    command.append_uint32(val.as_uint32());
                    break;
                }
                case valueType_uint64:
                {
                    command.append_uint64(val.as_uint64());
                    break;
                }
                case valueType_int8:
                {
                    command.append_int8(val.as_int8());
                    break;
                }
                case valueType_float:
                {
                    command.append_float(val.as_float());
                    break;
                }
                case valueType_double:
                {
                    command.append_double(val.as_double());
                    break;
                }
                case valueType_string:
                {
                    std::string str = val.as_string();
                    command.append_string(str);
                    break;
                }
                default:
                {
                    break;
                }
            }
        }

        return GenericMipCommand::buildCommand(commandType(), command.data());
    }

    MipFieldValues MipCommand::getGenericResponseData(const GenericMipCmdResponse& response)
    {
        MipFieldFormat responseFormat = MipCommand::getResponseFieldFormat(m_commandId);
        DataBuffer buffer(response.data());
        MipFieldValues data;

        populateGenericResponseData(m_commandId, buffer, responseFormat, data);

        return data;
    }

    std::string MipCommand::commandName() const
    {
        return MipCommand::getCommandName(m_commandId);
    }

    bool MipCommand::isKnownCommand() const
    {
        return MipCommand::getCommandName(m_commandId) != "";
    }

    MipFunctionSelectors MipCommand::supportedFunctionSelectors(MipTypes::Command cmd)
    {
        switch (cmd)
        {
            // 0x0C
            case MipTypes::CMD_POLL:
            case MipTypes::CMD_GET_BASE_RATE:
            case MipTypes::CMD_FACTORY_STREAMING:
            case MipTypes::CMD_SUPPORTED_SENSOR_RANGES:
            // 0x0D
            case MipTypes::CMD_EF_RUN_FILTER:
            case MipTypes::CMD_EF_EXTERN_SPEED_UPDATE:
            // Ox0E
            case MipTypes::CMD_GNSS_RECEIVER_INFO:
            // 0x13
            case MipTypes::CMD_AIDING_POS_ECEF:
            case MipTypes::CMD_AIDING_POS_LLH:
            case MipTypes::CMD_AIDING_HEIGHT_ABOVE_ELLIPSOID:
            case MipTypes::CMD_AIDING_VEL_ECEF:
            case MipTypes::CMD_AIDING_VEL_NED:
            case MipTypes::CMD_AIDING_VEL_BODY_FRAME:
            case MipTypes::CMD_AIDING_HEADING_TRUE:
            case MipTypes::CMD_AIDING_MAGNETIC_FIELD:
            case MipTypes::CMD_AIDING_PRESSURE:
            {
                return {};
            }

            /****   Read, Write     ****/
            // 0x0C
            case MipTypes::CMD_GPIO_STATE:
            {
                return {
                    MipTypes::FunctionSelector::USE_NEW_SETTINGS,
                    MipTypes::FunctionSelector::READ_BACK_CURRENT_SETTINGS
                };
            }

            /****   Read, Write, Save, Load, Default    ****/
            // 0x01
            case MipTypes::CMD_COMM_PORT_SPEED:
            // 0x0C
            case MipTypes::CMD_NMEA_MESSAGE_FORMAT:
            case MipTypes::CMD_MESSAGE_FORMAT:
            case MipTypes::CMD_CONTINUOUS_DATA_STREAM:
            case MipTypes::CMD_PPS_SOURCE:
            case MipTypes::CMD_EVENT_CONTROL:
            case MipTypes::CMD_EVENT_TRIGGER_CONFIGURATION:
            case MipTypes::CMD_EVENT_ACTION_CONFIGURATION:
            case MipTypes::CMD_EF_SENS_VEHIC_FRAME_TRANSFORM_EULER:
            case MipTypes::CMD_EF_SENS_VEHIC_FRAME_TRANSFORM_QUAT:
            case MipTypes::CMD_EF_SENS_VEHIC_FRAME_TRANSFORM_DCM:
            case MipTypes::CMD_GPIO_CONFIGURATION:
            case MipTypes::CMD_ODOMETER_SETTINGS:
            case MipTypes::CMD_SENSOR_RANGE:
            case MipTypes::CMD_LOWPASS_ANTIALIASING_FILTER:
            // 0x0D
            case MipTypes::CMD_EF_SENS_VEHIC_FRAME_ROTATION_DCM:
            case MipTypes::CMD_EF_SENS_VEHIC_FRAME_ROTATION_QUAT:
            case MipTypes::CMD_EF_AIDING_MEASUREMENT_ENABLE:
            case MipTypes::CMD_EF_ADAPTIVE_FILTER_OPTIONS:
            case MipTypes::CMD_EF_MULTI_ANTENNA_OFFSET:
            case MipTypes::CMD_EF_RELATIVE_POSITION_REF:
            case MipTypes::CMD_EF_LEVER_ARM_OFFSET_REF:
            case MipTypes::CMD_EF_SPEED_MEASUREMENT_OFFSET:
            case MipTypes::CMD_EF_VERTICAL_GYRO_CONSTRAINT:
            case MipTypes::CMD_EF_WHEELED_VEHICLE_CONSTRAINT:
            case MipTypes::CMD_EF_GNSS_ANTENNA_LEVER_ARM_CAL:
            // 0x0E
            case MipTypes::CMD_GNSS_SIGNAL_CONFIG:
            case MipTypes::CMD_GNSS_RTK_CONFIG:
            case MipTypes::CMD_GNSS_SPARTN_CONFIG:
            // 0x13
            case MipTypes::CMD_AIDING_FRAME_CONFIG:
            case MipTypes::CMD_AIDING_ECHO_CONTROL:
            {
                return {
                    MipTypes::FunctionSelector::USE_NEW_SETTINGS,
                    MipTypes::FunctionSelector::READ_BACK_CURRENT_SETTINGS,
                    MipTypes::FunctionSelector::SAVE_CURRENT_SETTINGS,
                    MipTypes::FunctionSelector::LOAD_STARTUP_SETTINGS,
                    MipTypes::FunctionSelector::RESET_TO_DEFAULT
                };
            }
            default:
            {
                return {};
            }
        }
    }

    bool MipCommand::supportsFunctionSelector(MipTypes::Command cmd, MipTypes::FunctionSelector fn)
    {
        MipFunctionSelectors fns = MipCommand::supportedFunctionSelectors(cmd);
        return std::find(fns.begin(), fns.end(), fn) != fns.end();
    }

    uint8 MipCommand::fieldDataByte() const
    {
        return MipCommand::getFieldDataByte(m_commandId);
    }

    bool MipCommand::responseExpected() const
    {
        return m_functionSelector == MipTypes::READ_BACK_CURRENT_SETTINGS
            || m_responseExpected;
    }

    MipResponseMatchValues MipCommand::buildMatchData() const
    {
        MipResponseMatchValues matchData;

        if (m_data.size() <= 0)
        {
            return matchData;
        }

        switch (m_commandId)
        {
            // 0x0C
            case MipTypes::CMD_CONTINUOUS_DATA_STREAM:
            case MipTypes::CMD_GET_BASE_RATE:
            case MipTypes::CMD_MESSAGE_FORMAT:
            case MipTypes::CMD_EVENT_CONTROL:
            case MipTypes::CMD_EVENT_TRIGGER_CONFIGURATION:
            case MipTypes::CMD_EVENT_ACTION_CONFIGURATION:
            case MipTypes::CMD_SENSOR_RANGE:
            case MipTypes::CMD_SUPPORTED_SENSOR_RANGES:
            case MipTypes::CMD_LOWPASS_ANTIALIASING_FILTER:
            // 0x0D
            case MipTypes::CMD_EF_LEVER_ARM_OFFSET_REF:
            //0x13
            case MipTypes::CMD_AIDING_FRAME_CONFIG:
            {
                // check that the identifier is echoed back in the response
                matchData.emplace(0, m_data[0]);
                break;
            }

                // 0x13
            case MipTypes::CMD_AIDING_POS_ECEF:
            case MipTypes::CMD_AIDING_POS_LLH:
            case MipTypes::CMD_AIDING_HEIGHT_ABOVE_ELLIPSOID:
            case MipTypes::CMD_AIDING_VEL_ECEF:
            case MipTypes::CMD_AIDING_VEL_NED:
            case MipTypes::CMD_AIDING_VEL_BODY_FRAME:
            case MipTypes::CMD_AIDING_HEADING_TRUE:
            case MipTypes::CMD_AIDING_MAGNETIC_FIELD:
            case MipTypes::CMD_AIDING_PRESSURE:
            {
                // check that the frame id is echoed back in the response
                matchData.emplace(10, m_data[3]);
                break;
            }
            default:
            {
                break;
            }
        }

        return matchData;
    }

    std::string MipCommand::getCommandName(MipTypes::Command id)
    {
        switch (id)
        {
            // 0x01
            case MipTypes::CMD_COMM_PORT_SPEED:
            {
                return "CommPortSpeed";
            }

            // 0x0C
            case MipTypes::CMD_NMEA_MESSAGE_FORMAT:
            {
                return "NmeaMessageFormat";
            }
            case MipTypes::CMD_POLL:
            {
                return "PollData";
            }
            case MipTypes::CMD_GET_BASE_RATE:
            {
                return "GetDataBaseRate";
            }
            case MipTypes::CMD_MESSAGE_FORMAT:
            {
                return "MessageFormat";
            }
            case MipTypes::CMD_FACTORY_STREAMING:
            {
                return "FactoryStreaming";
            }
            case MipTypes::CMD_CONTINUOUS_DATA_STREAM:
            {
                return "ContinuousDataStream";
            }
            case MipTypes::CMD_EF_SENS_VEHIC_FRAME_TRANSFORM_EULER:
            {
                return "SensorToVehicleFrameTransformationEulerAngles";
            }
            case MipTypes::CMD_EF_SENS_VEHIC_FRAME_TRANSFORM_QUAT:
            {
                return "SensorToVehicleFrameTransformationQuaternion";
            }
            case MipTypes::CMD_EF_SENS_VEHIC_FRAME_TRANSFORM_DCM:
            {
                return "SensorToVehicleFrameTransformationDCM";
            }
            case MipTypes::CMD_PPS_SOURCE:
            {
                return "PpsSource";
            }
            case MipTypes::CMD_EVENT_SUPPORT:
            {
                return "EventSupport";
            }
            case MipTypes::CMD_EVENT_CONTROL:
            {
                return "EventControl";
            }
            case MipTypes::CMD_EVENT_TRIGGER_STATUS:
            {
                return "EventTriggerStatus";
            }
            case MipTypes::CMD_EVENT_ACTION_STATUS:
            {
                return "EventActionStatus";
            }
            case MipTypes::CMD_EVENT_TRIGGER_CONFIGURATION:
            {
                return "EventTriggerConfiguration";
            }
            case MipTypes::CMD_EVENT_ACTION_CONFIGURATION:
            {
                return "EventActionConfiguration";
            }
            case MipTypes::CMD_GPIO_CONFIGURATION:
            {
                return "GpioConfiguration";
            }
            case MipTypes::CMD_GPIO_STATE:
            {
                return "GpioState";
            }
            case MipTypes::CMD_ODOMETER_SETTINGS:
            {
                return "OdometerSettings";
            }
            case MipTypes::CMD_SENSOR_RANGE:
            {
                return "SensorRange";
            }
            case MipTypes::CMD_SUPPORTED_SENSOR_RANGES:
            {
                return "SupportedSensorRanges";
            }
            case MipTypes::CMD_LOWPASS_ANTIALIASING_FILTER:
            {
                return "LowPassAntiAliasingFilter";
            }

            // 0x0D
            case MipTypes::CMD_EF_RUN_FILTER:
            {
                return "RunEstimationFilter";
            }
            case MipTypes::CMD_EF_SENS_VEHIC_FRAME_ROTATION_DCM:
            {
                return "SensorToVehicleFrameRotationDCM";
            }
            case MipTypes::CMD_EF_SENS_VEHIC_FRAME_ROTATION_QUAT:
            {
                return "SensorToVehicleFrameRotationQuaternion";
            }
            case MipTypes::CMD_EF_AIDING_MEASUREMENT_ENABLE:
            {
                return "AidingMeasurementEnable";
            }
            case MipTypes::CMD_EF_ADAPTIVE_FILTER_OPTIONS:
            {
                return "AdaptiveFilterOptions";
            }
            case MipTypes::CMD_EF_MULTI_ANTENNA_OFFSET:
            {
                return "MultiAntennaOffset";
            }
            case MipTypes::CMD_EF_RELATIVE_POSITION_REF:
            {
                return "RelativePositionReference";
            }
            case MipTypes::CMD_EF_LEVER_ARM_OFFSET_REF:
            {
                return "LeverArmOffsetReference";
            }
            case MipTypes::CMD_EF_EXTERN_SPEED_UPDATE:
            {
                return "ExternalSpeedMeasurementUpdate";
            }
            case MipTypes::CMD_EF_SPEED_MEASUREMENT_OFFSET:
            {
                return "SpeedMeasurementLeverArmOffset";
            }
            case MipTypes::CMD_EF_VERTICAL_GYRO_CONSTRAINT:
            {
                return "VerticalGyroConstraint";
            }
            case MipTypes::CMD_EF_WHEELED_VEHICLE_CONSTRAINT:
            {
                return "WheeledVehicleConstraint";
            }
            case MipTypes::CMD_EF_GNSS_ANTENNA_LEVER_ARM_CAL:
            {
                return "GnssAntennaLeverArmCalibration";
            }

            // 0x0E
            case MipTypes::CMD_GNSS_RECEIVER_INFO:
            {
                return "GnssReceiverInfo";
            }
            case MipTypes::CMD_GNSS_SIGNAL_CONFIG:
            {
                return "GnssSignalConfiguration";
            }
            case MipTypes::CMD_GNSS_RTK_CONFIG:
            {
                return "GnssRtkConfiguration";
            }
            case MipTypes::CMD_GNSS_SPARTN_CONFIG:
            {
                return "GnssSpartnConfiguration";
            }

            // 0x13
            case MipTypes::CMD_AIDING_FRAME_CONFIG:
            {
                return "AidingMeasurementReferenceFrameConfig";
            }
            case MipTypes::CMD_AIDING_ECHO_CONTROL:
            {
                return "AidingMeasurementEchoControl";
            }
            case MipTypes::CMD_AIDING_POS_ECEF:
            {
                return "AidingMeasurementEcefPosition";
            }
            case MipTypes::CMD_AIDING_POS_LLH:
            {
                return "AidingMeasurementLlhPosition";
            }
            case MipTypes::CMD_AIDING_HEIGHT_ABOVE_ELLIPSOID:
            {
                return "AidingMeasurementHeightAboveEllipsoid";
            }
            case MipTypes::CMD_AIDING_VEL_ECEF:
            {
                return "AidingMeasurementEcefVelocity";
            }
            case MipTypes::CMD_AIDING_VEL_NED:
            {
                return "AidingMeasurementNedVelocity";
            }
            case MipTypes::CMD_AIDING_VEL_BODY_FRAME:
            {
                return "AidingMeasurementVehicelFrameVelocity";
            }
            case MipTypes::CMD_AIDING_HEADING_TRUE:
            {
                return "AidingMeasurementTrueHeading";
            }
            case MipTypes::CMD_AIDING_MAGNETIC_FIELD:
            {
                return "AidingMeasurementMagneticField";
            }
            case MipTypes::CMD_AIDING_PRESSURE:
            {
                return "AidingMeasurementPressure";
            }
            default:
            {
                return "";
            }
        }
    }

    uint8 MipCommand::getFieldDataByte(MipTypes::Command id)
    {
        switch (id)
        {
            // 0x0C
            case MipTypes::CMD_CONTINUOUS_DATA_STREAM:
            {
                return 0x85;
            }
            case MipTypes::CMD_EVENT_SUPPORT:
            {
                return 0xB4;
            }
            case MipTypes::CMD_EVENT_CONTROL:
            {
                return 0xB5;
            }
            case MipTypes::CMD_EVENT_TRIGGER_STATUS:
            {
                return 0xB6;
            }
            case MipTypes::CMD_EVENT_ACTION_STATUS:
            {
                return 0xB7;
            }
            case MipTypes::CMD_EVENT_TRIGGER_CONFIGURATION:
            {
                return 0xB8;
            }
            case MipTypes::CMD_EVENT_ACTION_CONFIGURATION:
            {
                return 0xB9;
            }

            // 0x0D
            case MipTypes::CMD_EF_SENS_VEHIC_FRAME_ROTATION_DCM:
            {
                return 0xBE;
            }
            case MipTypes::CMD_EF_SENS_VEHIC_FRAME_ROTATION_QUAT:
            {
                return 0xBF;
            }

            // 0x01
            case MipTypes::CMD_COMM_PORT_SPEED: //0x89
            // 0x0C
            case MipTypes::CMD_NMEA_MESSAGE_FORMAT:                 //0x8C
            case MipTypes::CMD_GET_BASE_RATE:                       //0x8E
            case MipTypes::CMD_MESSAGE_FORMAT:                      //0x8F
            case MipTypes::CMD_PPS_SOURCE:                          //0xA8
            case MipTypes::CMD_EF_SENS_VEHIC_FRAME_TRANSFORM_EULER: //0xB1
            case MipTypes::CMD_EF_SENS_VEHIC_FRAME_TRANSFORM_QUAT:  //0xB2
            case MipTypes::CMD_EF_SENS_VEHIC_FRAME_TRANSFORM_DCM:   //0xB3
            case MipTypes::CMD_GPIO_CONFIGURATION:                  //0xC1
            case MipTypes::CMD_GPIO_STATE:                          //0xC2
            case MipTypes::CMD_ODOMETER_SETTINGS:                   //0xC3
            case MipTypes::CMD_SENSOR_RANGE:                        //0xD2
            case MipTypes::CMD_SUPPORTED_SENSOR_RANGES:             //0xD3
            case MipTypes::CMD_LOWPASS_ANTIALIASING_FILTER:         //0xD4
            // 0x0D
            case MipTypes::CMD_EF_AIDING_MEASUREMENT_ENABLE:  //0xD0
            case MipTypes::CMD_EF_ADAPTIVE_FILTER_OPTIONS:    //0xD3
            case MipTypes::CMD_EF_MULTI_ANTENNA_OFFSET:       //0xD4
            case MipTypes::CMD_EF_RELATIVE_POSITION_REF:      //0xD5
            case MipTypes::CMD_EF_LEVER_ARM_OFFSET_REF:       //0xD6
            case MipTypes::CMD_EF_SPEED_MEASUREMENT_OFFSET:   //0xE1
            case MipTypes::CMD_EF_VERTICAL_GYRO_CONSTRAINT:   //0xE2
            case MipTypes::CMD_EF_WHEELED_VEHICLE_CONSTRAINT: //0xE3
            case MipTypes::CMD_EF_GNSS_ANTENNA_LEVER_ARM_CAL: //0xE4
            // 0x0E
            case MipTypes::CMD_GNSS_RECEIVER_INFO: //0x81
            case MipTypes::CMD_GNSS_SIGNAL_CONFIG: //0x82
            case MipTypes::CMD_GNSS_RTK_CONFIG:    //0x90
            case MipTypes::CMD_GNSS_SPARTN_CONFIG: //0xA0
            // 0x13 - all fields follow pattern
            default:
            {
                // this pattern is not true for all commands - may result in communication failures
                uint8 cmdDesc = Utils::lsb(static_cast<uint16>(id));

                // 0xF0-FF are reserved
                // any command desc over 0x70 cannot follow this pattern and needs to be manually defined
                if (cmdDesc >= 0x70)
                {
                    return 0;
                }

                return cmdDesc | 0x80;
            }
        }
    }

    MipFieldFormat MipCommand::getResponseFieldFormat(MipTypes::Command id)
    {
        switch (id)
        {
            // 0x01
            case MipTypes::CMD_COMM_PORT_SPEED:
            {
                return {
                    ValueType::valueType_uint8,
                    ValueType::valueType_uint32
                };
            }

            // 0x0C
            case MipTypes::CMD_NMEA_MESSAGE_FORMAT:
            {
                return {
                    ValueType::valueType_uint8,
                    ValueType::valueType_Vector
                };
            }
            case MipTypes::CMD_GET_BASE_RATE:
            {
                return {
                    ValueType::valueType_uint8,
                    ValueType::valueType_uint16
                };
            }
            case MipTypes::CMD_MESSAGE_FORMAT:
            {
                return {
                    ValueType::valueType_uint8,
                    ValueType::valueType_uint8,
                    ValueType::valueType_Vector
                };
            }
            case MipTypes::CMD_CONTINUOUS_DATA_STREAM:
            {
                return {
                    ValueType::valueType_uint8,
                    ValueType::valueType_bool
                };
            }
            case MipTypes::CMD_PPS_SOURCE:
            {
                return { ValueType::valueType_uint8 };
            }
            case MipTypes::CMD_EVENT_SUPPORT:
            {
                return {
                    ValueType::valueType_uint8,
                    ValueType::valueType_uint8,
                    ValueType::valueType_uint8,
                    ValueType::valueType_Vector,
                };
            }
            case MipTypes::CMD_EVENT_CONTROL:
            {
                return {
                    ValueType::valueType_uint8,
                    ValueType::valueType_uint8
                };
            }
            case MipTypes::CMD_EVENT_TRIGGER_STATUS:
            {
                return {
                    ValueType::valueType_uint8, // count
                    ValueType::valueType_Vector // status info
                };
            }
            case MipTypes::CMD_EVENT_ACTION_STATUS:
            {
                return {
                    ValueType::valueType_uint8, // count
                    ValueType::valueType_Vector // status info
                };
            }
            case MipTypes::CMD_ODOMETER_SETTINGS:
            {
                return {
                    ValueType::valueType_uint8, // mode
                    ValueType::valueType_float, // scaling
                    ValueType::valueType_float  // uncertainty
                };
            }
            case MipTypes::CMD_SENSOR_RANGE:
            {
                return {
                    ValueType::valueType_uint8, // sensor
                    ValueType::valueType_uint8  // range
                };
            }
            case MipTypes::CMD_SUPPORTED_SENSOR_RANGES:
            {
                return {
                    ValueType::valueType_uint8,
                    ValueType::valueType_uint8,
                    ValueType::valueType_Vector
                };
            }
            case MipTypes::CMD_LOWPASS_ANTIALIASING_FILTER:
            {
                return {
                    ValueType::valueType_uint16,
                    ValueType::valueType_bool,
                    ValueType::valueType_bool,
                    ValueType::valueType_float,
                };
            }
            case MipTypes::CMD_GPIO_CONFIGURATION:
            {
                return {
                    ValueType::valueType_uint8,
                    ValueType::valueType_int8,
                    ValueType::valueType_int8,
                    ValueType::valueType_int8
                };
            }
            case MipTypes::CMD_GPIO_STATE:
            {
                return {
                    ValueType::valueType_uint8,
                    ValueType::valueType_bool
                };
            }

            // 0x0D
            case MipTypes::CMD_EF_AIDING_MEASUREMENT_ENABLE:
            {
                return {
                    ValueType::valueType_uint16,
                    ValueType::valueType_bool
                };
            }
            case MipTypes::CMD_EF_ADAPTIVE_FILTER_OPTIONS:
            {
                return {
                    ValueType::valueType_uint8,
                    ValueType::valueType_uint16
                };
            }
            case MipTypes::CMD_EF_MULTI_ANTENNA_OFFSET:
            {
                return {
                    ValueType::valueType_uint8,
                    ValueType::valueType_float,
                    ValueType::valueType_float,
                    ValueType::valueType_float
                };
            }
            case MipTypes::CMD_EF_RELATIVE_POSITION_REF:
            {
                return {
                    ValueType::valueType_uint8,
                    ValueType::valueType_uint8,
                    ValueType::valueType_double,
                    ValueType::valueType_double,
                    ValueType::valueType_double
                };
            }
            case MipTypes::CMD_EF_LEVER_ARM_OFFSET_REF:
            {
                return {
                    ValueType::valueType_uint8,
                    ValueType::valueType_float,
                    ValueType::valueType_float,
                    ValueType::valueType_float,
                };
            }
            case MipTypes::CMD_EF_SPEED_MEASUREMENT_OFFSET:
            {
                return {
                    ValueType::valueType_uint8,
                    ValueType::valueType_float,
                    ValueType::valueType_float,
                    ValueType::valueType_float,
                };
            }

            case MipTypes::CMD_EF_GNSS_ANTENNA_LEVER_ARM_CAL:
            {
                return {
                    ValueType::valueType_bool,
                    ValueType::valueType_float
                };
            }

            // 0x0E
            case MipTypes::CMD_GNSS_RECEIVER_INFO:
            {
                return {
                    ValueType::valueType_uint8, // num receivers
                    ValueType::valueType_Vector // receiver info
                };
            }
            case MipTypes::CMD_GNSS_SIGNAL_CONFIG:
            {
                return {
                    ValueType::valueType_uint8,
                    ValueType::valueType_uint8,
                    ValueType::valueType_uint8,
                    ValueType::valueType_uint8
                };
            }
            case MipTypes::CMD_GNSS_SPARTN_CONFIG:
            {
                return {
                    ValueType::valueType_uint8,  // enable
                    ValueType::valueType_uint8,  // type
                    ValueType::valueType_uint32, // current key TOW
                    ValueType::valueType_uint16, // current key week
                    ValueType::valueType_string, // ascii description of current key in HEX
                    ValueType::valueType_uint32, // next key TOW
                    ValueType::valueType_uint16, // next key week
                    ValueType::valueType_string  // ascii description of next key in HEX
                };
            }

            // 0x13
            case MipTypes::CMD_AIDING_FRAME_CONFIG:
            {
                return {
                    ValueType::valueType_uint8, // frame id
                    ValueType::valueType_uint8, // format
                    ValueType::valueType_bool,  // error tracking enabled
                    ValueType::valueType_float, // translation
                    ValueType::valueType_float,
                    ValueType::valueType_float,
                    ValueType::valueType_Vector, // rotation (ve3 for euler, vec4 for quat)
                };
            }
            case MipTypes::CMD_AIDING_ECHO_CONTROL:
            {
                return {
                    ValueType::valueType_uint8
                };
            }
            // case MipTypes::CMD_AIDING_POS_LOCAL:
            // {
            //     return {};
            // }
            case MipTypes::CMD_AIDING_POS_ECEF:
            case MipTypes::CMD_AIDING_POS_LLH:
            {
                return {
                    ValueType::valueType_uint8,  // timebase
                    ValueType::valueType_uint8,  // reserved
                    ValueType::valueType_uint64, // nanoseconds since timebase epoch

                    ValueType::valueType_uint8, // frame id

                    ValueType::valueType_double, // pos
                    ValueType::valueType_double,
                    ValueType::valueType_double,
                    ValueType::valueType_float, // unc
                    ValueType::valueType_float,
                    ValueType::valueType_float,

                    ValueType::valueType_uint16, // valid flags
                };
            }
            case MipTypes::CMD_AIDING_HEIGHT_ABOVE_ELLIPSOID:
            {
                return {
                    ValueType::valueType_uint8,  // timebase
                    ValueType::valueType_uint8,  // reserved
                    ValueType::valueType_uint64, // nanoseconds since timebase epoch

                    ValueType::valueType_uint8, // frame id

                    ValueType::valueType_float, // height
                    ValueType::valueType_float, // unc

                    ValueType::valueType_uint16, // valid flags
                };
            }
            // case MipTypes::CMD_AIDING_HEIGHT_REL:
            // {
            //     return {};
            // }
            case MipTypes::CMD_AIDING_VEL_ECEF:
            case MipTypes::CMD_AIDING_VEL_NED:
            case MipTypes::CMD_AIDING_VEL_BODY_FRAME:
            {
                return {
                    ValueType::valueType_uint8,  // timebase
                    ValueType::valueType_uint8,  // reserved
                    ValueType::valueType_uint64, // nanoseconds since timebase epoch

                    ValueType::valueType_uint8, // frame id

                    ValueType::valueType_float, // vel
                    ValueType::valueType_float,
                    ValueType::valueType_float,
                    ValueType::valueType_float, // unc
                    ValueType::valueType_float,
                    ValueType::valueType_float,

                    ValueType::valueType_uint16, // valid flags
                };
            }
            // case MipTypes::CMD_AIDING_WHEELSPEED:
            // {
            //     return {};
            // }
            case MipTypes::CMD_AIDING_HEADING_TRUE:
            {
                return {
                    ValueType::valueType_uint8,  // timebase
                    ValueType::valueType_uint8,  // reserved
                    ValueType::valueType_uint64, // nanoseconds since timebase epoch

                    ValueType::valueType_uint8, // frame id

                    ValueType::valueType_float, // heading
                    ValueType::valueType_float, // unc

                    ValueType::valueType_uint16, // valid flags
                };
            }
            case MipTypes::CMD_AIDING_MAGNETIC_FIELD:
            {
                return {
                    ValueType::valueType_uint8,  // timebase
                    ValueType::valueType_uint8,  // reserved
                    ValueType::valueType_uint64, // nanoseconds since timebase epoch

                    ValueType::valueType_uint8, // frame id

                    ValueType::valueType_float, // mag field
                    ValueType::valueType_float,
                    ValueType::valueType_float,
                    ValueType::valueType_float, // unc
                    ValueType::valueType_float,
                    ValueType::valueType_float,

                    ValueType::valueType_uint16, // valid flags
                };
            }
            case MipTypes::CMD_AIDING_PRESSURE:
            {
                return {
                    ValueType::valueType_uint8,  // timebase
                    ValueType::valueType_uint8,  // reserved
                    ValueType::valueType_uint64, // nanoseconds since timebase epoch

                    ValueType::valueType_uint8, // frame id

                    ValueType::valueType_float, // pressure
                    ValueType::valueType_float, // unc

                    ValueType::valueType_uint16, // valid flags
                };
            }
            // case MipTypes::CMD_AIDING_DELTA_POSITION:
            // {
            //     return {};
            // }
            // case MipTypes::CMD_AIDING_DELTA_ATTITUDE:
            // {
            //     return {};
            // }
            // case MipTypes::CMD_AIDING_ANGULAR_RATE_LOCAL:
            // {
            //     return {};
            // }
            case MipTypes::CMD_EF_VERTICAL_GYRO_CONSTRAINT:
            case MipTypes::CMD_EF_WHEELED_VEHICLE_CONSTRAINT:
            case MipTypes::CMD_GNSS_RTK_CONFIG:
            {
                return {
                    ValueType::valueType_bool
                };
            }
            case MipTypes::CMD_EF_SENS_VEHIC_FRAME_TRANSFORM_EULER:
            {
                return {
                    ValueType::valueType_float,
                    ValueType::valueType_float,
                    ValueType::valueType_float
                };
            }
            case MipTypes::CMD_EF_SENS_VEHIC_FRAME_TRANSFORM_DCM:
            case MipTypes::CMD_EF_SENS_VEHIC_FRAME_ROTATION_DCM:
            {
                return {
                    ValueType::valueType_float,
                    ValueType::valueType_float,
                    ValueType::valueType_float,

                    ValueType::valueType_float,
                    ValueType::valueType_float,
                    ValueType::valueType_float,

                    ValueType::valueType_float,
                    ValueType::valueType_float,
                    ValueType::valueType_float
                };
            }
            case MipTypes::CMD_EF_SENS_VEHIC_FRAME_TRANSFORM_QUAT:
            case MipTypes::CMD_EF_SENS_VEHIC_FRAME_ROTATION_QUAT:
            {
                return {
                    ValueType::valueType_float,
                    ValueType::valueType_float,
                    ValueType::valueType_float,
                    ValueType::valueType_float
                };
            }
            default:
            {
                // no defined format, read out vector of uint8
                return {
                    ValueType::valueType_Vector
                };
            }
        }
    }

    MipFieldFormat MipCommand::getResponseVectorPartFormat(MipTypes::Command id, uint8 nestedLevel, uint8 sequenceCount)
    {
        switch (id)
        {
            case MipTypes::CMD_NMEA_MESSAGE_FORMAT:
            {
                return {
                    ValueType::valueType_uint8,
                    ValueType::valueType_uint8,
                    ValueType::valueType_uint8,
                    ValueType::valueType_uint16
                };
            }
            case MipTypes::CMD_MESSAGE_FORMAT:
            {
                return {
                    ValueType::valueType_uint8,
                    ValueType::valueType_uint16
                };
            }
            case MipTypes::CMD_EVENT_SUPPORT:
            {
                return {
                    ValueType::valueType_uint8,
                    ValueType::valueType_uint8
                };
            }
            case MipTypes::CMD_GNSS_RECEIVER_INFO:
            {
                return {
                    ValueType::valueType_uint8, // receiver id
                    ValueType::valueType_uint8, // associated data set
                    ValueType::valueType_string // ascii description of receiver
                };
            }
            case MipTypes::CMD_EVENT_TRIGGER_STATUS:
            {
                return {
                    ValueType::valueType_uint8, // type
                    ValueType::valueType_uint8  // status
                };
            }
            case MipTypes::CMD_EVENT_ACTION_STATUS:
            {
                return {
                    ValueType::valueType_uint8, // type
                    ValueType::valueType_uint8  // status
                };
            }
            case MipTypes::CMD_SUPPORTED_SENSOR_RANGES:
            {
                return {
                    ValueType::valueType_uint8,
                    ValueType::valueType_float
                };
            }
            case MipTypes::CMD_AIDING_FRAME_CONFIG:
            {
                return {
                    ValueType::valueType_float
                };
            }
            default:
            {
                // no defined format, read out vector of uint8
                return {
                    ValueType::valueType_uint8
                };
            }
        }
    }

    int MipCommand::stringLength(MipTypes::Command id)
    {
        switch (id)
        {
            case MipTypes::CMD_GNSS_RECEIVER_INFO:
            case MipTypes::CMD_GNSS_SPARTN_CONFIG:
            {
                return 32;
            }
            default:
            {
                return -1;
            }
        }
    }

    void MipCommand::populateGenericResponseData(MipTypes::Command id, DataBuffer& buffer, const MipFieldFormat& format, MipFieldValues& outData, uint8 vectorNestedLevel, uint8 vectorSequenceCount)
    {
        for (ValueType type : format)
        {
            switch (type)
            {
                case valueType_bool:
                {
                    outData.push_back(Value::BOOL((buffer.read_uint8() > 0)));
                    break;
                }
                case valueType_uint8:
                {
                    outData.push_back(Value::UINT8(buffer.read_uint8()));
                    break;
                }
                case valueType_uint16:
                {
                    outData.push_back(Value::UINT16(buffer.read_uint16()));
                    break;
                }
                case valueType_uint32:
                {
                    outData.push_back(Value::UINT32(buffer.read_uint32()));
                    break;
                }
                case valueType_uint64:
                {
                    outData.push_back(Value::UINT64(buffer.read_uint64()));
                    break;
                }
                case valueType_int8:
                {
                    outData.push_back(Value::INT8(buffer.read_int8()));
                    break;
                }
                case valueType_float:
                {
                    outData.push_back(Value::FLOAT(buffer.read_float()));
                    break;
                }
                case valueType_double:
                {
                    outData.push_back(Value::DOUBLE(buffer.read_double()));
                    break;
                }
                case valueType_string:
                {
                    size_t count = stringLength(id);
                    if (count <= 0)
                    {
                        // no count - read until end of buffer
                        count = buffer.size();
                    }

                    std::string str;
                    for (size_t i = 0; i < count; i++)
                    {
                        str += static_cast<char>(buffer.read_uint8());
                    }

                    outData.push_back(Value(ValueType::valueType_string, str));

                    break;
                }
                case valueType_Vector:
                {
                    MipFieldFormat vectorFormat = MipCommand::getResponseVectorPartFormat(id, vectorNestedLevel, vectorSequenceCount);
                    size_t count = 0;
                    bool hasCount = false;
                    if (outData.size() > 0)
                    {
                        // assume previous value is count if exists and is uint8
                        Value last = outData.back();
                        if (last.storedAs() == valueType_uint8)
                        {
                            count = last.as_uint8();
                            hasCount = true;
                        }
                    }

                    if (count == 0 && !hasCount)
                    {
                        // no count - read element format until end of buffer
                        size_t elementSize = 0;
                        for (ValueType t : vectorFormat)
                        {
                            elementSize += Utils::valueTypeSize(t);
                        }

                        size_t remainingBytes = buffer.size() - buffer.readPosition();
                        count = remainingBytes / elementSize;
                    }

                    for (size_t i = 0; i < count; i++)
                    {
                        MipCommand::populateGenericResponseData(id, buffer, vectorFormat, outData);
                    }

                    break;
                }
                default:
                {
                    break;
                }
            }
        }
    }
} // namespace mscl
