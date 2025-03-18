/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "mscl/MicroStrain/Inertial/Commands/DeviceStatus.h"

namespace mscl
{
    DeviceStatus::DeviceStatus(MipModels::NodeModel model, DeviceStatusData::StatusSelector status_selector) :
        m_model(model),
        m_statusSelector(status_selector)
    { }

    DeviceStatus DeviceStatus::MakeGetCommand(MipModels::NodeModel model, DeviceStatusData::StatusSelector statusSelector)
    {
        return DeviceStatus(model, statusSelector);
    }

    DeviceStatus DeviceStatus::MakeGetBasicCommand(MipModels::NodeModel model)
    {
        return DeviceStatus(model, DeviceStatusData::BASIC_STATUS_STRUCTURE);
    }

    DeviceStatus DeviceStatus::MakeGetDiagnosticCommand(MipModels::NodeModel model)
    {
        return DeviceStatus(model, DeviceStatusData::DIAGNOSTIC_STATUS_STRUCTURE);
    }

    bool DeviceStatus::responseExpected() const
    {
        return true;
    }

    DeviceStatusData DeviceStatus::getResponseData(const GenericMipCmdResponse& response)
    {
        DataBuffer dataBuffer(response.data());
        DeviceStatusData returnData;

        returnData.modelNumber = dataBuffer.read_uint16();
        MipModels::NodeModel model = static_cast<MipModels::NodeModel>(returnData.modelNumber);
        returnData.statusStructure = static_cast<DeviceStatusData::StatusSelector>(dataBuffer.read_uint8());
        dataBuffer.read_uint32();   // Status flags are unused as of this writing, so just drop this on the floor.

        switch (model)
        {
        case MipModels::node_3dm_gq4_45:
        {
            returnData.systemState(static_cast<DeviceStatusData::SystemState>(dataBuffer.read_uint16()));
            returnData.systemTimerInMS = dataBuffer.read_uint32();

            if (returnData.statusStructure == DeviceStatusData::StatusSelector::BASIC_STATUS_STRUCTURE)
            {
                return returnData;
            }

            returnData.gnssPowerStateOn((dataBuffer.read_uint8() == MipTypes::ENABLED));

            PpsPulseInfo gnss;
            gnss.count = dataBuffer.read_uint32();
            gnss.lastTimeinMS = dataBuffer.read_uint32();
            returnData.gnss1PpsPulseInfo(gnss);

            StreamInfo imuStream;
            StreamInfo gnssStream;
            StreamInfo efStream;

            imuStream.enabled = (dataBuffer.read_uint8() == MipTypes::ENABLED);
            gnssStream.enabled = (dataBuffer.read_uint8() == MipTypes::ENABLED);
            efStream.enabled = (dataBuffer.read_uint8() == MipTypes::ENABLED);

            imuStream.outgoingPacketsDropped = dataBuffer.read_uint32();
            gnssStream.outgoingPacketsDropped = dataBuffer.read_uint32();
            efStream.outgoingPacketsDropped = dataBuffer.read_uint32();

            returnData.imuStreamInfo(imuStream);
            returnData.gnssStreamInfo(gnssStream);
            returnData.estimationFilterStreamInfo(efStream);

            PortInfo com;
            com.bytesWritten = dataBuffer.read_uint32();
            com.bytesRead = dataBuffer.read_uint32();
            com.overrunsOnWrite = dataBuffer.read_uint32();
            com.overrunsOnRead = dataBuffer.read_uint32();
            returnData.comPortInfo(com);

            DeviceMessageInfo imuMessages;
            imuMessages.messageParsingErrors = dataBuffer.read_uint32();
            imuMessages.messagesRead = dataBuffer.read_uint32();
            imuMessages.lastMessageReadinMS = dataBuffer.read_uint32();
            returnData.imuMessageInfo(imuMessages);

            DeviceMessageInfo gnssMessages;
            gnssMessages.messageParsingErrors = dataBuffer.read_uint32();
            gnssMessages.messagesRead = dataBuffer.read_uint32();
            gnssMessages.lastMessageReadinMS = dataBuffer.read_uint32();
            returnData.gnssMessageInfo(gnssMessages);

            returnData.magnetometerInitializationFailed((dataBuffer.read_uint8() == 0x01));
            returnData.pressureInitializationFailed((dataBuffer.read_uint8() == 0x01));
            returnData.gnssReceiverInitializationFailed((dataBuffer.read_uint8() == 0x01));
        }
        break;

        case MipModels::node_3dm_rq1_45_lt:
        case MipModels::node_3dm_rq1_45_st:
        {
            returnData.systemState(static_cast<DeviceStatusData::SystemState>(dataBuffer.read_uint16()));
            returnData.systemTimerInMS = dataBuffer.read_uint32();

            if (returnData.statusStructure == DeviceStatusData::StatusSelector::BASIC_STATUS_STRUCTURE)
            {
                return returnData;
            }

            returnData.gnssPowerStateOn((dataBuffer.read_uint8() == MipTypes::ENABLED));
            returnData.coldStartOnPowerOn((dataBuffer.read_uint8() == MipTypes::ENABLED));

            TemperatureInfo temp;
            temp.onBoardTemp = dataBuffer.read_float();
            temp.lastReadInMS = dataBuffer.read_uint32();
            returnData.temperatureInfo(temp);

            PpsPulseInfo gnss;
            gnss.count = dataBuffer.read_uint32();
            gnss.lastTimeinMS = dataBuffer.read_uint32();
            returnData.gnss1PpsPulseInfo(gnss);

            StreamInfo imuStream;
            StreamInfo gnssStream;
            StreamInfo efStream;

            imuStream.enabled = (dataBuffer.read_uint8() == MipTypes::ENABLED);
            gnssStream.enabled = (dataBuffer.read_uint8() == MipTypes::ENABLED);
            efStream.enabled = (dataBuffer.read_uint8() == MipTypes::ENABLED);

            imuStream.outgoingPacketsDropped = dataBuffer.read_uint32();
            gnssStream.outgoingPacketsDropped = dataBuffer.read_uint32();
            efStream.outgoingPacketsDropped = dataBuffer.read_uint32();

            returnData.imuStreamInfo(imuStream);
            returnData.gnssStreamInfo(gnssStream);
            returnData.estimationFilterStreamInfo(efStream);

            PortInfo com;
            com.bytesWritten = dataBuffer.read_uint32();
            com.bytesRead = dataBuffer.read_uint32();
            com.overrunsOnWrite = dataBuffer.read_uint32();
            com.overrunsOnRead = dataBuffer.read_uint32();
            returnData.comPortInfo(com);

            DeviceMessageInfo imuMessages;
            imuMessages.messageParsingErrors = dataBuffer.read_uint32();
            imuMessages.messagesRead = dataBuffer.read_uint32();
            imuMessages.lastMessageReadinMS = dataBuffer.read_uint32();
            returnData.imuMessageInfo(imuMessages);

            DeviceMessageInfo gnssMessages;
            gnssMessages.messageParsingErrors = dataBuffer.read_uint32();
            gnssMessages.messagesRead = dataBuffer.read_uint32();
            gnssMessages.lastMessageReadinMS = dataBuffer.read_uint32();
            returnData.gnssMessageInfo(gnssMessages);
        }
        break;

        case MipModels::node_3dm_gx5_10:
        case MipModels::node_3dm_cx5_10:
        case MipModels::node_3dm_cv5_10:
        {
            returnData.systemTimerInMS = dataBuffer.read_uint32();

            if (returnData.statusStructure == DeviceStatusData::StatusSelector::BASIC_STATUS_STRUCTURE)
            {
                return returnData;
            }

            returnData.hasMagnetometer(dataBuffer.read_uint8() == MipTypes::ENABLED);
            returnData.hasPressure(dataBuffer.read_uint8() == MipTypes::ENABLED);
            returnData.powerState(static_cast<InertialTypes::PowerState>(dataBuffer.read_uint8()));
            returnData.gyroRange(dataBuffer.read_uint16());
            returnData.accelRange(dataBuffer.read_uint16());

            //reserved bytes, ignore value
            dataBuffer.read_uint32();

            TemperatureInfo temp;
            temp.onBoardTemp = dataBuffer.read_float();
            temp.lastReadInMS = dataBuffer.read_uint32();
            temp.error = dataBuffer.read_uint8();
            returnData.temperatureInfo(temp);

            PpsPulseInfo gnss;
            gnss.count = dataBuffer.read_uint32();
            gnss.lastTimeinMS = dataBuffer.read_uint32();
            returnData.gnss1PpsPulseInfo(gnss);

            StreamInfo imu;
            imu.enabled = (dataBuffer.read_uint8() == MipTypes::ENABLED);
            imu.outgoingPacketsDropped = dataBuffer.read_uint32();
            returnData.imuStreamInfo(imu);

            PortInfo com;
            com.bytesWritten = dataBuffer.read_uint32();
            com.bytesRead = dataBuffer.read_uint32();
            com.overrunsOnWrite = dataBuffer.read_uint32();
            com.overrunsOnRead = dataBuffer.read_uint32();
            returnData.comPortInfo(com);
        }
        break;

        case MipModels::node_3dm_gx5_15:
        case MipModels::node_3dm_gx5_25:
        case MipModels::node_3dm_cx5_15:
        case MipModels::node_3dm_cx5_25:
        case MipModels::node_3dm_cv5_15:
        case MipModels::node_3dm_cv5_25:
        case MipModels::node_3dm_cl5_15:
        case MipModels::node_3dm_cl5_25:
        {
            returnData.systemState(static_cast<DeviceStatusData::SystemState>(dataBuffer.read_uint16()));
            returnData.systemTimerInMS = dataBuffer.read_uint32();

            if (returnData.statusStructure == DeviceStatusData::StatusSelector::BASIC_STATUS_STRUCTURE)
            {
                return returnData;
            }

            StreamInfo imuStream;
            StreamInfo efStream;

            imuStream.enabled = (dataBuffer.read_uint8() == MipTypes::ENABLED);
            efStream.enabled = (dataBuffer.read_uint8() == MipTypes::ENABLED);

            imuStream.outgoingPacketsDropped = dataBuffer.read_uint32();
            efStream.outgoingPacketsDropped = dataBuffer.read_uint32();

            returnData.imuStreamInfo(imuStream);
            returnData.estimationFilterStreamInfo(efStream);

            PortInfo com;
            com.bytesWritten = dataBuffer.read_uint32();
            com.bytesRead = dataBuffer.read_uint32();
            com.overrunsOnWrite = dataBuffer.read_uint32();
            com.overrunsOnRead = dataBuffer.read_uint32();
            returnData.comPortInfo(com);

            DeviceMessageInfo imuMessages;
            imuMessages.messageParsingErrors = dataBuffer.read_uint32();
            imuMessages.messagesRead = dataBuffer.read_uint32();
            imuMessages.lastMessageReadinMS = dataBuffer.read_uint32();
            returnData.imuMessageInfo(imuMessages);
        }
        break;

        case MipModels::node_3dm_gx4_15:
        case MipModels::node_3dm_gx4_25:
        {
            returnData.systemTimerInMS = dataBuffer.read_uint32();

            if (returnData.statusStructure == DeviceStatusData::StatusSelector::BASIC_STATUS_STRUCTURE)
            {
                return returnData;
            }

            PpsPulseInfo gnss;
            gnss.count = dataBuffer.read_uint32();
            gnss.lastTimeinMS = dataBuffer.read_uint32();
            returnData.gnss1PpsPulseInfo(gnss);

            StreamInfo imuStream;
            StreamInfo efStream;

            imuStream.enabled = (dataBuffer.read_uint8() == MipTypes::ENABLED);
            efStream.enabled = (dataBuffer.read_uint8() == MipTypes::ENABLED);

            imuStream.outgoingPacketsDropped = dataBuffer.read_uint32();
            efStream.outgoingPacketsDropped = dataBuffer.read_uint32();

            returnData.imuStreamInfo(imuStream);
            returnData.estimationFilterStreamInfo(efStream);

            PortInfo com;
            com.bytesWritten = dataBuffer.read_uint32();
            com.bytesRead = dataBuffer.read_uint32();
            com.overrunsOnWrite = dataBuffer.read_uint32();
            com.overrunsOnRead = dataBuffer.read_uint32();
            returnData.comPortInfo(com);

            PortInfo usb;
            usb.bytesWritten = dataBuffer.read_uint32();
            usb.bytesRead = dataBuffer.read_uint32();
            usb.overrunsOnWrite = dataBuffer.read_uint32();
            usb.overrunsOnRead = dataBuffer.read_uint32();
            returnData.usbPortInfo(usb);

            DeviceMessageInfo imuMessages;
            imuMessages.messageParsingErrors = dataBuffer.read_uint32();
            imuMessages.messagesRead = dataBuffer.read_uint32();
            imuMessages.lastMessageReadinMS = dataBuffer.read_uint32();
            returnData.imuMessageInfo(imuMessages);
        }
        break;

        case MipModels::node_3dm_gx5_35:
        case MipModels::node_3dm_gx5_45:
        case MipModels::node_3dm_cx5_35:
        case MipModels::node_3dm_cx5_45:
        case MipModels::node_3dm_gx4_45:
        {
            returnData.systemState(static_cast<DeviceStatusData::SystemState>(dataBuffer.read_uint16()));
            returnData.systemTimerInMS = dataBuffer.read_uint32();

            if (returnData.statusStructure == DeviceStatusData::StatusSelector::BASIC_STATUS_STRUCTURE)
            {
                return returnData;
            }

            returnData.gnssPowerStateOn((dataBuffer.read_uint8() == MipTypes::ENABLED));

            PpsPulseInfo gnss;
            gnss.count = dataBuffer.read_uint32();
            gnss.lastTimeinMS = dataBuffer.read_uint32();
            returnData.gnss1PpsPulseInfo(gnss);

            StreamInfo imuStream;
            StreamInfo gnssStream;
            StreamInfo efStream;

            imuStream.enabled = (dataBuffer.read_uint8() == MipTypes::ENABLED);
            gnssStream.enabled = (dataBuffer.read_uint8() == MipTypes::ENABLED);
            efStream.enabled = (dataBuffer.read_uint8() == MipTypes::ENABLED);

            imuStream.outgoingPacketsDropped = dataBuffer.read_uint32();
            gnssStream.outgoingPacketsDropped = dataBuffer.read_uint32();
            efStream.outgoingPacketsDropped = dataBuffer.read_uint32();

            returnData.imuStreamInfo(imuStream);
            returnData.gnssStreamInfo(gnssStream);
            returnData.estimationFilterStreamInfo(efStream);

            PortInfo com;
            com.bytesWritten = dataBuffer.read_uint32();
            com.bytesRead = dataBuffer.read_uint32();
            com.overrunsOnWrite = dataBuffer.read_uint32();
            com.overrunsOnRead = dataBuffer.read_uint32();
            returnData.comPortInfo(com);

            DeviceMessageInfo imuMessages;
            imuMessages.messageParsingErrors = dataBuffer.read_uint32();
            imuMessages.messagesRead = dataBuffer.read_uint32();
            imuMessages.lastMessageReadinMS = dataBuffer.read_uint32();
            returnData.imuMessageInfo(imuMessages);

            DeviceMessageInfo gnssMessages;
            gnssMessages.messageParsingErrors = dataBuffer.read_uint32();
            gnssMessages.messagesRead = dataBuffer.read_uint32();
            gnssMessages.lastMessageReadinMS = dataBuffer.read_uint32();
            returnData.gnssMessageInfo(gnssMessages);
        }
        break;

        default:
            throw Error_NotSupported("MSCL support for Device Status (0x0C, 0x64) is not currently implemented for this device. Model number: " + std::to_string(returnData.modelNumber));
        }

        return returnData;
    }

    DeviceStatus::operator ByteStream() const
    {
        ByteStream byteCommand;
        byteCommand.append_uint16(static_cast<uint16>(m_model));
        byteCommand.append_uint8(static_cast<uint8>(m_statusSelector));
        return GenericMipCommand::buildCommand(commandType(), byteCommand.data());
    }

}
