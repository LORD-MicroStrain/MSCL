#include "stdafx.h"
#include "DeviceStatus.h"
#include "mscl/MicroStrain/Inertial/InertialDataField.h"
#include "mscl/MicroStrain/Inertial/Packets/InertialPacketBuilder.h"
#include "mscl/MicroStrain/Inertial/InertialTypes.h"
#include "Inertial_Commands.h"

namespace mscl
{
    DeviceStatus::DeviceStatus(InertialTypes::StatusSelector status_selector) :
        m_StatusSelector(status_selector)
    { }

    DeviceStatus DeviceStatus::MakeBasicStatusCommand()
    {
        return DeviceStatus(InertialTypes::BASIC_STATUS_STRUCTURE);
    }

    DeviceStatus DeviceStatus::MakeDiagnosticStatusCommand()
    {
        return DeviceStatus(InertialTypes::DIAGNOSTIC_STATUS_STRUCTURE);
    }

    bool DeviceStatus::responseExpected() const
    {
        return true;
    }

    DeviceStatusData DeviceStatus::getResponseData(const GenericInertialCommandResponse& response)
    {
        DataBuffer dataBuffer(response.data());
        DeviceStatusData returnData;
        if (dataBuffer.read_uint16() != InertialTypes::GX5_45_MODEL_NUMBER)
            throw mscl::Error_NotSupported("This command is currently only implemented for the GX5-45 device.");

        InertialTypes::StatusSelector statusSelector = static_cast<InertialTypes::StatusSelector>(dataBuffer.read_uint8());
        dataBuffer.read_uint32();   // Status flags are unused as of this writing, so just drop this on the floor.
        returnData.systemState = dataBuffer.read_uint16();
        returnData.systemTimerInMS = dataBuffer.read_uint32();

        //for a basic structure, we're done.  Diagnostic structures have more data.
        if (statusSelector == InertialTypes::BASIC_STATUS_STRUCTURE)
            return returnData;

        returnData.gnssPowerStateOn = (dataBuffer.read_uint8() == InertialTypes::ENABLED) ? true : false;
        returnData.numberof1PPSPulses = dataBuffer.read_uint32();
        returnData.last1PPSInMS = dataBuffer.read_uint32();
        returnData.imuStreamIsEnabled = (dataBuffer.read_uint8() == InertialTypes::ENABLED) ? true : false;
        returnData.gnssStreamIsEnabled = (dataBuffer.read_uint8() == InertialTypes::ENABLED) ? true : false;
        returnData.estimationFilterStreamIsEnabled = (dataBuffer.read_uint8() == InertialTypes::ENABLED) ? true : false;
        returnData.outgoingIMUDroppedPacketCount = dataBuffer.read_uint32();
        returnData.outgoingGnssDroppedPacketCount = dataBuffer.read_uint32();
        returnData.outgoingEstimationFilterDroppedPacketCount = dataBuffer.read_uint32();
        returnData.numOfBytesWrittenToComPort = dataBuffer.read_uint32();
        returnData.numOfBytesWrittenFromComPort = dataBuffer.read_uint32();
        returnData.numOfOverrunsOnWriteToComPort = dataBuffer.read_uint32();
        returnData.numOfIMUParsingErrors = dataBuffer.read_uint32();
        returnData.totalIMUMessagesRead = dataBuffer.read_uint32();
        returnData.lastIMUMessageReadInMS = dataBuffer.read_uint32();
        returnData.numOfGnssParsingErrors = dataBuffer.read_uint32();
        returnData.totalGnssMessagesRead = dataBuffer.read_uint32();
        returnData.lastGnssMessageReadInMS = dataBuffer.read_uint32();

        return returnData;
    }

    DeviceStatus::operator ByteStream() const
    {
        ByteStream byteCommand;
        byteCommand.append_uint16(InertialTypes::GX5_45_MODEL_NUMBER);
        byteCommand.append_uint8(static_cast<uint8>(m_StatusSelector));
        return GenericInertialCommand::buildCommand(commandType(), byteCommand.data());
    }

}