/*****************************************************************************************
**          Copyright(c) 2015-2022 Parker Hannifin Corp. All rights reserved.           **
**                                                                                      **
**    MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.    **
*****************************************************************************************/

#include "stdafx.h"
#include "MipNode_Impl.h"

#include "mscl/Utils.h"
#include "mscl/ScopeHelper.h"
#include "MipParser.h"
#include "NMEA/NmeaParser.h"
#include "MipNodeInfo.h"
#include "MipNodeFeatures.h"
#include "Commands/CyclePower.h"
#include "Commands/GetDeviceDescriptorSets.h"
#include "Commands/GetExtendedDeviceDescriptorSets.h"
#include "Commands/GPSTimeUpdate.h"
#include "Commands/Mip_SetToIdle.h"
#include "Commands/Resume.h"
#include "mscl/MicroStrain/Displacement/Commands/DeviceTime.h"
#include "mscl/MicroStrain/Displacement/Commands/DisplacementOutputDataRate.h"
#include "mscl/MicroStrain/Displacement/Commands/GetAnalogToDisplacementCals.h"
#include "mscl/MicroStrain/RTK/Commands/DeviceStatusFlags.h"
#include "mscl/MicroStrain/RTK/Commands/ActivationCode.h"
#include "mscl/MicroStrain/Inertial/Commands/AccelBias.h"
#include "mscl/MicroStrain/Inertial/Commands/AdaptiveMeasurement.h"
#include "mscl/MicroStrain/Inertial/Commands/AdvancedLowPassFilterSettings.h"
#include "mscl/MicroStrain/Inertial/Commands/CaptureGyroBias.h"
#include "mscl/MicroStrain/Inertial/Commands/MagnetometerCaptureAutoCalibration.h"
#include "mscl/MicroStrain/Inertial/Commands/ComplementaryFilterSettings.h"
#include "mscl/MicroStrain/Inertial/Commands/ConingAndScullingEnable.h"
#include "mscl/MicroStrain/Inertial/Commands/ContinuousDataStream.h"
#include "mscl/MicroStrain/Inertial/Commands/DeviceStartupSettings.h"
#include "mscl/MicroStrain/Inertial/Commands/DeviceStatus.h"
#include "mscl/MicroStrain/Inertial/Commands/EstimationControlFlags.h"
#include "mscl/MicroStrain/Inertial/Commands/FilterInitializationConfig.h"
#include "mscl/MicroStrain/Inertial/Commands/GeographicSource.h"
#include "mscl/MicroStrain/Inertial/Commands/EstFilter_Commands.h"
#include "mscl/MicroStrain/Inertial/Commands/ExternalGNSSUpdate.h"
#include "mscl/MicroStrain/Inertial/Commands/ExternalHeadingUpdate.h"
#include "mscl/MicroStrain/Inertial/Commands/ExternalHeadingUpdateWithTimestamp.h"
#include "mscl/MicroStrain/Inertial/Commands/FloatCommand.h"
#include "mscl/MicroStrain/Inertial/Commands/GeometricVectorCommand.h"
#include "mscl/MicroStrain/Inertial/Commands/GNSS_AssistedFixControl.h"
#include "mscl/MicroStrain/Inertial/Commands/GNSS_AssistTimeUpdate.h"
#include "mscl/MicroStrain/Inertial/Commands/GNSS_Commands.h"
#include "mscl/MicroStrain/Inertial/Commands/GNSS_ConstellationSettings.h"
#include "mscl/MicroStrain/Inertial/Commands/GNSS_SBASSettings.h"
#include "mscl/MicroStrain/Inertial/Commands/GNSS_SourceControl.h"
#include "mscl/MicroStrain/Inertial/Commands/GyroBias.h"
#include "mscl/MicroStrain/Inertial/Commands/HeadingUpdateControl.h"
#include "mscl/MicroStrain/Inertial/Commands/MagnetometerHardIronOffset.h"
#include "mscl/MicroStrain/Inertial/Commands/MagnetometerSoftIronMatrix.h"
#include "mscl/MicroStrain/Inertial/Commands/Matrix3x3Command.h"
#include "mscl/MicroStrain/Inertial/Commands/PollData.h"
#include "mscl/MicroStrain/Inertial/Commands/RawRTCM_2_3Message.h"
#include "mscl/MicroStrain/Inertial/Commands/Sensor_Commands.h"
#include "mscl/MicroStrain/Inertial/Commands/SetReferencePosition.h"
#include "mscl/MicroStrain/Inertial/Commands/SignalConditioningSettings.h"
#include "mscl/MicroStrain/Inertial/Commands/System_Commands.h"
#include "mscl/MicroStrain/Inertial/Commands/UARTBaudRate.h"
#include "mscl/MicroStrain/Inertial/Commands/Uint8Command.h"
#include "mscl/MicroStrain/Inertial/Commands/Uint16Command.h"
#include "mscl/MicroStrain/Inertial/Commands/VehicleDynamicsMode.h"

namespace mscl
{
    MipNode_Impl::MipNode_Impl(Connection connection): 
        m_connection(connection),
        m_commandsTimeout(COMMANDS_DEFAULT_TIMEOUT),
        m_sensorRateBase(0),
        m_gnssRateBase(0),
        m_estfilterRateBase(0),
        m_lastDeviceState(deviceState_unknown),
        m_parseNmea(false)
    {
        //create the response collector
        m_responseCollector.reset(new ResponseCollector);

        m_responseCollector->setConnection(&m_connection);

        //want to get notified of data packets
        m_packetCollector.requestDataAddedNotification(std::bind(&MipNode_Impl::onDataPacketAdded, this));

        //build the parser with the MipNode_Impl's packet collector and response collector
        m_parser.reset(new MipParser(&m_packetCollector, m_responseCollector, &m_rawBytePacketCollector));

        //build the NMEA parser with the MipNode_Impl's packet collector and response collector
        m_nmeaParser.reset(new NmeaParser(&m_nmeaPacketCollector));

        //register the parse function with the connection
        m_connection.registerParser(std::bind(&MipNode_Impl::parseData, this, std::placeholders::_1));
    }

    MipNode_Impl::~MipNode_Impl()
    {
        //unregister the parse functions with the connection, which stops the IO Thread
        m_connection.unregisterParser();
    }

    const Timestamp& MipNode_Impl::lastCommunicationTime() const
    {
        if(m_lastCommTime.nanoseconds() == 0)
        {
            throw Error_NoData("The Inertial Node has not yet been communicated with.");
        }

        return m_lastCommTime;
    }

    DeviceState MipNode_Impl::lastDeviceState() const
    {
        return m_lastDeviceState;
    }

    void MipNode_Impl::setLastDeviceState(DeviceState state)
    {
        m_lastDeviceState = state;
    }

    void MipNode_Impl::resetNodeInfo()
    {
        //if the features variable hasn't been set yet, no need to reset
        if (m_features == nullptr)
        {
            return;
        }

        m_features->resetNodeInfo();
    }

    Version MipNode_Impl::firmwareVersion() const
    {
        return info().deviceInfo().fwVersion;
    }

    std::string MipNode_Impl::modelName() const
    {
        return info().deviceInfo().modelName;
    }

    std::string MipNode_Impl::modelNumber() const
    {
        return info().deviceInfo().modelNumber;
    }

    std::string MipNode_Impl::serialNumber() const
    {
        return info().deviceInfo().serialNumber;
    }

    std::string MipNode_Impl::lotNumber() const
    {
        return info().deviceInfo().lotNumber;
    }

    std::string MipNode_Impl::deviceOptions() const
    {
        return info().deviceInfo().deviceOptions;
    }

    const MipNodeInfo& MipNode_Impl::info() const
    {
        return features().nodeInfo();
    }

    void MipNode_Impl::onDataPacketAdded()
    {
        m_lastDeviceState = DeviceState::deviceState_sampling;
    }

    const MipNodeFeatures& MipNode_Impl::features() const
    {
        //if the features variable hasn't been set yet
        if(m_features == nullptr)
        {
            //set the features variable by creating a new NodeFeatures pointer
            m_features = MipNodeFeatures::create(this);
        }

        return *(m_features.get());
    }

    Connection& MipNode_Impl::connection()
    {
        return m_connection;
    }

    SampleRates MipNode_Impl::supportedSampleRates(MipTypes::DataClass dataClass) const
    {
        SampleRates result;

        //get the sample rate's base rate for this category from the Node
        uint16 baseRate = getDataRateBase(dataClass);

        for(uint16 decimator = baseRate; decimator > 0; --decimator)
        {
            //if this decimator divides evenly into the base rate
            if(baseRate % decimator == 0)
            {
                //add the Sample Rate to the list of supported rates
                result.push_back(SampleRate::Hertz(baseRate / decimator));
            }
        }

        return result;
    }

    void MipNode_Impl::parseData(DataBuffer& data)
    {
        ReadBufferSavePoint beginData(&data);

        //send the readBuffer to the parser to parse all the bytes
        m_parser->parse(data);

        if (m_parseNmea)
        {
            // set back to beginning of data and run through NMEA parser
            beginData.revert();
            m_nmeaParser->parse(data);
            beginData.commit();
        }

        //update InertialNode last comm time
        m_lastCommTime.setTimeNow();

        //shift out all bytes, parsers hold onto copies of whatever they need
        data.skipBytes(data.bytesRemaining());
        std::size_t bytesShifted = data.shiftExtraToStart();

        if(bytesShifted > 0)
        {
            //subtract the bytes shifted from each command already waiting on a response
            m_responseCollector->adjustResponsesMinBytePos(bytesShifted);
        }
    }

    void MipNode_Impl::getDataPackets(MipDataPackets& packets, uint32 timeout, uint32 maxPackets)//maxPackets=0
    {
        //check if a connection error has occurred
        m_connection.throwIfError();

        return m_packetCollector.getDataPackets(packets, timeout, maxPackets);
    }

    void MipNode_Impl::getNmeaPackets(NmeaPackets& packets, uint32 timeout, uint32 maxPackets)//maxPackets=0
    {
        //check if a connection error has occurred
        m_connection.throwIfError();

        return m_nmeaPacketCollector.getPackets(packets, timeout, maxPackets);
    }

    void MipNode_Impl::getRawBytePackets(RawBytePackets& packets, uint32 timeout, uint32 maxPackets)//maxPackets=0
    {
        //check if a connection error has occurred
        m_connection.throwIfError();

        return m_rawBytePacketCollector.getRawBytePackets(packets, timeout, maxPackets);
    }

    uint32 MipNode_Impl::totalPackets()
    {
        return m_packetCollector.totalPackets();
    }

    void MipNode_Impl::enableNmeaParsing(bool enable)
    {
        m_parseNmea = enable;
    }

    void MipNode_Impl::timeout(uint64 timeout)
    {
        m_commandsTimeout = timeout;
    }

    uint64 MipNode_Impl::timeout()
    {
        return m_commandsTimeout;
    }

    GenericMipCmdResponse MipNode_Impl::doCommand(GenericMipCommand::Response& response, const ByteStream& command, bool verifySupported) const
    {
        RawBytePacket rawBytePacket;
        rawBytePacket.payload(command.data());
        rawBytePacket.source(RawBytePacket::FROM_SEND);
        rawBytePacket.type(RawBytePacket::COMMAND_PACKET);

        m_rawBytePacketCollector.addRawBytePacket(rawBytePacket);
        response.setResponseCollector(m_responseCollector);
        
        if(verifySupported)
        {
            //verify that this command is supported
            if(!features().supportsCommand(response.m_command))
            {
                throw Error_NotSupported("The command (" + Utils::toStr(response.m_command) + ") is not supported.");
            }
        }

        //send the command to the device
        m_connection.write(command);

        //wait for the response
        response.wait(m_commandsTimeout);

        //get the result from the response
        GenericMipCmdResponse result = response.result();

        //throw an exception if not successful
        result.throwIfFailed();

        return result;
    }

    Bytes MipNode_Impl::doCommand(uint8 descriptorSet, uint8 cmdDescriptor, const Bytes& fieldData, bool ackNackResponse, bool dataResponse, uint8 responseDataDescriptor) const
    {
        MipTypes::Command cmdId = static_cast<MipTypes::Command>(Utils::make_uint16(descriptorSet, cmdDescriptor));
        GenericMipCommand::Response response(cmdId, m_responseCollector, ackNackResponse, dataResponse, "", responseDataDescriptor);

        ByteStream command = GenericMipCommand::buildCommand(cmdId, fieldData);

        RawBytePacket rawBytePacket;
        rawBytePacket.payload(command.data());
        rawBytePacket.source(RawBytePacket::FROM_SEND);
        rawBytePacket.type(RawBytePacket::COMMAND_PACKET);

        m_rawBytePacketCollector.addRawBytePacket(rawBytePacket);

        //send the command to the device
        m_connection.write(command);

        //wait for the response
        response.wait(m_commandsTimeout);

        //get the result from the response
        GenericMipCmdResponse result = response.result();

        //throw an exception if not successful
        result.throwIfFailed();

        return result.data().data();
    }

//============================================================================
//=========================INERTIAL COMMANDS==================================
    bool MipNode_Impl::ping()
    {
        //create the response for the Ping command
        Ping::Response response (m_responseCollector);

        try
        {
            //send the command and wait for the response
            return doCommand(response, Ping::buildCommand(), false).success();
        }
        catch (Error_MipCmdFailed&)
        {
            return false;
        }
        catch (Error_Communication&)
        {
            return false;
        }
    }

    void MipNode_Impl::setToIdle()
    {
        //set the expected response
        Mip_SetToIdle::Response r(m_responseCollector);

        //send the command and wait for the response
        doCommand(r, Mip_SetToIdle::buildCommand(), false);

        m_lastDeviceState = DeviceState::deviceState_idle;
    }

    bool MipNode_Impl::cyclePower()
    {
        CyclePower::Response response (m_responseCollector);

        try
        {
            //send the command and wait for the response
            return doCommand(response, CyclePower::buildCommand(), false).success();
        }
        catch (Error_MipCmdFailed&)
        {
            return false;
        }
        catch (Error_Communication&)
        {
            return false;
        }
    }

    void MipNode_Impl::resume()
    {
        //set the expected response
        Resume::Response r(m_responseCollector);

        //send the command and wait for the response
        doCommand(r, Resume::buildCommand(), false);
    }

    void MipNode_Impl::saveSettingsAsStartup()
    {
        // if combined command supported, use that
        if (features().supportsCommand(MipTypes::Command::CMD_SAVE_STARTUP_SETTINGS))
        {
            uint64 tempTimeout = timeout();

            //when this goes out of scope, it will write back the original timeout (need cast for overloaded ambiguity)
            ScopeHelper writebackTimeout(std::bind(static_cast<void(MipNode_Impl::*)(uint64)>(&MipNode_Impl::timeout), this, tempTimeout));

            //change the timeout to a minimum of 2.5s
            Utils::checkBounds_min(tempTimeout, static_cast<uint64>(2500));
            timeout(tempTimeout);

            DeviceStartupSettings::Response r(m_responseCollector);
            doCommand(r, DeviceStartupSettings::buildCommand_saveAsStartup(), false);
            return;
        }

        // otherwise loop through supported descriptors and run each manually
        MipTypes::MipCommands cmds = features().supportedCommands();
        for (MipTypes::Command cmd : cmds)
        {
            if (MipCommand::supportsFunctionSelector(cmd, MipTypes::SAVE_CURRENT_SETTINGS))
            {
                saveAsStartup(cmd);
            }
        }
    }

    void MipNode_Impl::loadStartupSettings()
    {
        uint64 originalTimeout = timeout();

        //when this goes out of scope, it will write back the original timeout (need cast for overloaded ambiguity)
        ScopeHelper writebackTimeout(std::bind(static_cast<void(MipNode_Impl::*)(uint64)>(&MipNode_Impl::timeout), this, originalTimeout));

        //change the timeout to a minimum of 1200
        uint64 newTimeout = originalTimeout;
        Utils::checkBounds_min(newTimeout, static_cast<uint64>(1200));
        timeout(newTimeout);

        DeviceStartupSettings::Response r(m_responseCollector);

        doCommand(r, DeviceStartupSettings::buildCommand_loadStartup(), false);
    }

    void MipNode_Impl::loadFactoryDefaultSettings()
    {
        uint64 tempTimeout = timeout();

        //when this goes out of scope, it will write back the original timeout (need cast for overloaded ambiguity)
        ScopeHelper writebackTimeout(std::bind(static_cast<void(MipNode_Impl::*)(uint64)>(&MipNode_Impl::timeout), this, tempTimeout));

        //change the timeout to a minimum of 1200
        Utils::checkBounds_min(tempTimeout, static_cast<uint64>(1200));
        timeout(tempTimeout);

        DeviceStartupSettings::Response r(m_responseCollector);

        doCommand(r, DeviceStartupSettings::buildCommand_loadDefault(), false);
    }

    void MipNode_Impl::pollData(MipTypes::DataClass dataClass, const MipTypes::MipChannelFields& fields)
    {
        if (features().supportsCommand(MipTypes::CMD_POLL)) // Use generic poll if supported
        {
            MipFieldValues params;
            params.push_back(Value::UINT8(static_cast<uint8>(dataClass)));
            params.push_back(Value::BOOL(false)); // don't suppress ACK/NACK
            params.push_back(Value::UINT8(static_cast<uint8>(fields.size())));

            for (MipTypes::ChannelField ch : fields)
            {
                uint8 desc = Utils::lsb(static_cast<uint16>(ch));
                params.push_back(Value::UINT8(desc));
            }

            set(MipTypes::CMD_POLL, params);
            return;
        }

        switch(dataClass)
        {
            case MipTypes::CLASS_AHRS_IMU:
            {
                PollImuData::Response r(m_responseCollector);
                doCommand(r, PollImuData::buildCommand(fields), false);
                break;
            }

            case MipTypes::CLASS_GNSS:
            {
                PollGnssData::Response r(m_responseCollector);
                doCommand(r, PollGnssData::buildCommand(fields), false);
                break;
            }

            case MipTypes::CLASS_ESTFILTER:
            {
                PollEstFilterData::Response r(m_responseCollector);
                doCommand(r, PollEstFilterData::buildCommand(fields), false);
                break;
            }

            default:
                throw Error_NotSupported("Unsupported DataClass");
        }
    }

    MipDeviceInfo MipNode_Impl::getDeviceInfo() const
    {
        //create the response for the GetDeviceInfo command
        GetDeviceInfo::Response r(m_responseCollector);

        //send the command, wait for the response, and parse the result
        return r.parseResponse(doCommand(r, GetDeviceInfo::buildCommand(), false));
    }

    GnssReceivers MipNode_Impl::getGnssReceiverInfo() const
    {
        MipFieldValues ret = get(MipTypes::Command::CMD_GNSS_RECEIVER_INFO);

        uint8 count = ret[0].as_uint8();
        GnssReceivers receivers;
        for (uint8 i = 0; i < count; i++)
        {
            uint8 index = (i * 3) + 1; // three values per element, first value count
            receivers.push_back(GnssReceiverInfo(
                ret[index].as_uint8(),                                       // receiver id
                static_cast<MipTypes::DataClass>(ret[index + 1].as_uint8()), // associated data set
                ret[index + 2].as_string()));                                // ascii desc
        }

        return receivers;
    }

    SupportedSensorRanges MipNode_Impl::getSupportedSensorRanges() const
    {
        if (!features().supportsCommand(MipTypes::Command::CMD_SUPPORTED_SENSOR_RANGES))
        {
            return SupportedSensorRanges();
        }

        const uint8 FIRST_RANGE_INDEX = 2;
        const uint8 RANGE_ENTRY_SIZE = 2;
        const SensorRange::Type sensorTypes[] = {
            SensorRange::ACCEL_G,
            SensorRange::GYRO_DPS,
            SensorRange::MAG_GAUSS,
            SensorRange::PRESSURE_HPA
        };

        SupportedSensorRanges supported;
        for (SensorRange::Type type : sensorTypes)
        {
            try
            {
                MipFieldValues ret = get(MipTypes::Command::CMD_SUPPORTED_SENSOR_RANGES, { Value::UINT8(static_cast<uint8>(type)) });

                if (ret.size() < FIRST_RANGE_INDEX)
                {
                    continue;
                }

                uint8 count = ret[1].as_uint8();
                size_t minSize = (FIRST_RANGE_INDEX + (count * RANGE_ENTRY_SIZE));
                if (ret.size() < minSize)
                {
                    continue;
                }

                SensorRanges typeRanges;
                for (size_t i = 0; i < count; i++)
                {
                    size_t index = FIRST_RANGE_INDEX + (i * RANGE_ENTRY_SIZE);

                    // 1-indexed option id
                    uint8 optionId = ret[index].as_uint8();

                    // range value
                    float range = ret[index + 1].as_float();

                    //add to list
                    typeRanges.push_back(SensorRange(type, optionId, range));
                }

                if (typeRanges.size() <= 0)
                {
                    continue;
                }

                supported.m_options.emplace(type, typeRanges);
            }
            catch(const Error_MipCmdFailed&)
            {/*ignore*/ }
        }

        return supported;
    }

    std::vector<uint16> MipNode_Impl::getDescriptorSets() const
    {
        std::vector<uint16> descriptors;

        //create the response for the GetDeviceDescriptorSets command

        GetDeviceDescriptorSets::Response r(m_responseCollector);

        //append the descriptors to the container
        r.parseResponse(doCommand(r, GetDeviceDescriptorSets::buildCommand(), false), descriptors);

        if(std::find(descriptors.begin(), descriptors.end(), MipTypes::CMD_GET_EXT_DESCRIPTOR_SETS) != descriptors.end())
        {
            //create the response for the GetExtendedDeviceDescriptorSets command
            GetExtendedDeviceDescriptorSets::Response r2(m_responseCollector);

            //append the extended descriptors to the container
            r2.parseResponse(doCommand(r2, GetExtendedDeviceDescriptorSets::buildCommand(), false), descriptors);
        }

        //send the command, wait for the response, and parse the result
        return descriptors;
    }

    MipCommandParameters MipNode_Impl::getRequiredParameterDefaults(MipTypes::Command cmd, bool useAllParam) const
    {
        MipTypes::MipCommands cmds = { cmd };
        return getRequiredParameterDefaults(cmds, useAllParam);
    }

    MipCommandParameters MipNode_Impl::getRequiredParameterDefaults(const MipTypes::MipCommands& cmds, bool useAllParam) const
    {
        const std::vector<MipTypes::DataClass> dataClasses = {
            MipTypes::DataClass::CLASS_AHRS_IMU,
            MipTypes::DataClass::CLASS_GNSS,
            MipTypes::DataClass::CLASS_ESTFILTER,
            MipTypes::DataClass::CLASS_DISPLACEMENT,
            MipTypes::DataClass::CLASS_GNSS1,
            MipTypes::DataClass::CLASS_GNSS2,
            MipTypes::DataClass::CLASS_GNSS3, // RTK
            MipTypes::DataClass::CLASS_GNSS4,
            MipTypes::DataClass::CLASS_GNSS5,
            MipTypes::DataClass::CLASS_SYSTEM
        };

        MipCommandParameters params;
        
        //all param will not work for any device that uses legacy data set identifiers for datastream control
        bool legacyDevice = features().useLegacyIdsForEnableDataStream();
        bool allParam = useAllParam && !legacyDevice;
        for (MipTypes::Command cmd : cmds)
        {
            switch (cmd)
            {
            case MipTypes::CMD_CONTINUOUS_DATA_STREAM:
            {
                if (allParam)
                {
                    params.push_back({ cmd, {Value::UINT8(0)} });
                    break;
                }

                for (MipTypes::DataClass option : dataClasses)
                {
                    if (features().supportsCategory(option))
                    {
                        uint8 desc = legacyDevice ? ContinuousDataStream::getDeviceSelector(option) : static_cast<uint8>(option);
                        params.push_back({ cmd, { Value::UINT8(static_cast<uint8>(desc)) } });
                    }
                }

                break;
            }
            case MipTypes::CMD_DATA_STREAM_FORMAT:
            case MipTypes::CMD_POWER_STATES:
            {
                params.push_back({ cmd, {Value::UINT8(InertialTypes::DeviceSelector::DEVICE_AHRS)} });
                params.push_back({ cmd, {Value::UINT8(InertialTypes::DeviceSelector::DEVICE_GPS)} });
                break;
            }
            case MipTypes::CMD_COMM_PORT_SPEED:
            {
                /* this is not supported in the currently released GQ7 fw - can probably be added in eventually
                if (allParam)
                {
                    params.push_back({ cmd,{ Value::UINT8(0) } });
                    break;
                }*/

                CommPortInfo ports = features().getCommPortInfo();
                for (DeviceCommPort& port : ports)
                {
                    params.push_back({ cmd, { Value::UINT8(port.id) } });
                }
                break;
            }
            case MipTypes::CMD_LOWPASS_FILTER_SETTINGS:
            {
                if (allParam)
                {
                    params.push_back({ cmd,{ Value::UINT8(0) } });
                    break;
                }

                MipTypes::MipChannelFields lowpassFilterChannels = features().supportedLowPassFilterChannelFields();

                for (size_t j = 0; j < lowpassFilterChannels.size(); j++)
                {
                    MipTypes::ChannelField f = lowpassFilterChannels[j];

                    // legacy command only supports 0x80 fields
                    if ((MipTypes::DataClass)Utils::msb(static_cast<uint16>(f)) != MipTypes::CLASS_AHRS_IMU)
                    {
                        continue;
                    }

                    params.push_back({ cmd, {Value::UINT8(static_cast<uint8>(f))} });
                }

                break;
            }
            case MipTypes::CMD_LOWPASS_ANTIALIASING_FILTER:
            {
                if (allParam)
                {
                    params.push_back({ cmd,{ Value::UINT16(0) } });
                    break;
                }

                MipTypes::MipChannelFields lowpassFilterChannels = features().supportedLowPassFilterChannelFields();

                for (size_t j = 0; j < lowpassFilterChannels.size(); j++)
                {
                    params.push_back({ cmd,{ Value::UINT16(static_cast<uint16>(lowpassFilterChannels[j])) } });
                }

                break;
            }
            case MipTypes::CMD_MESSAGE_FORMAT:
            {
                /* this is not supported in the currently released GQ7 fw - can probably be added in eventually
                if (allParam)
                {
                    params.push_back({ cmd,{ Value::UINT8(0) } });
                    break;
                }*/

                for (MipTypes::DataClass option : dataClasses)
                {
                    if (features().supportsCategory(option))
                    {
                        params.push_back({ cmd, { Value::UINT8(static_cast<uint8>(option)) } });
                    }
                }
                break;
            }
            case MipTypes::CMD_EF_AIDING_MEASUREMENT_ENABLE:
            {
                if (allParam)
                {
                    params.push_back({ cmd,{ Value::UINT16(InertialTypes::ALL_AIDING_MEASUREMENTS) } });
                    break;
                }

                AidingMeasurementSourceOptions options = features().supportedAidingMeasurementOptions();
                for (InertialTypes::AidingMeasurementSource option : options)
                {
                    params.push_back({ cmd, { Value::UINT16(static_cast<uint16>(option)) } });
                }

                break;
            }
            case MipTypes::CMD_EF_MULTI_ANTENNA_OFFSET:
            {
                GnssReceivers supportedReceivers = features().gnssReceiverInfo();
                for (GnssReceiverInfo info : supportedReceivers)
                {
                    params.push_back({ cmd, { Value::UINT8(info.id) } });
                }

                break;
            }
            case MipTypes::CMD_EF_LEVER_ARM_OFFSET_REF:
            case MipTypes::CMD_EF_SPEED_MEASUREMENT_OFFSET:
            {
                MipFieldValues reserved = { Value::UINT8(1) };
                params.push_back({ cmd, reserved });
                break;
            }
            case MipTypes::CMD_GPIO_CONFIGURATION:
            {
                if (allParam)
                {
                    params.push_back({ cmd,{ Value::UINT8(0) } });
                    break;
                }

                GpioPinOptions gpioOptions = features().supportedGpioConfigurations();
                for (auto& kv : gpioOptions)
                {
                    params.push_back({ cmd, { Value::UINT8(static_cast<uint8>(kv.first)) } });
                }

                break;
            }
            case MipTypes::CMD_SENSOR_RANGE:
            {
                if (allParam)
                {
                    params.push_back({ cmd,{ Value::UINT8(SensorRange::ALL) } });
                    break;
                }

                SupportedSensorRanges supportedRanges = features().supportedSensorRanges();
                for (auto& kv : supportedRanges.options())
                {
                    params.push_back({ cmd, { Value::UINT8(static_cast<uint8>(kv.first)) } });
                }

                break;
            }
            case MipTypes::CMD_EVENT_TRIGGER_CONFIGURATION:
            case MipTypes::CMD_EVENT_CONTROL:
            {
                if (allParam)
                {
                    params.push_back({ cmd,{ Value::UINT8(0) } });
                    break;
                }

                EventSupportInfo info = features().supportedEventTriggerInfo();
                for (uint8_t id = 1; id <= info.maxInstances; id++)
                {
                    params.push_back({ cmd, { Value::UINT8(id) } });
                }
                break;
            }
            case MipTypes::CMD_EVENT_ACTION_CONFIGURATION:
            {
                if (allParam)
                {
                    params.push_back({ cmd,{ Value::UINT8(0) } });
                    break;
                }

                EventSupportInfo info = features().supportedEventActionInfo();
                for (uint8_t id = 1; id <= info.maxInstances; id++)
                {
                    params.push_back({ cmd, { Value::UINT8(id) } });
                }
                break;
            }
            default:
                params.push_back({ cmd, {} });
                break;
            }
        }

        return params;
    }

    MipCommandParameters MipNode_Impl::getReservedWriteValues(MipTypes::Command cmd) const
    {
        MipTypes::MipCommands cmds = { cmd };
        return getReservedWriteValues(cmds);
    }

    MipCommandParameters MipNode_Impl::getReservedWriteValues(const MipTypes::MipCommands& cmds) const
    {
        MipCommandParameters params;
        for (MipTypes::Command cmd : cmds)
        {
            switch (cmd)
            {
            case MipTypes::CMD_SENSOR_SIG_COND_SETTINGS:
                params.push_back({ cmd, { Value::UINT16(0) } });
                break;
            case MipTypes::CMD_LOWPASS_FILTER_SETTINGS:
                params.push_back({ cmd, { Value::UINT8(0) } });
                break;
            case MipTypes::CMD_GNSS_SIGNAL_CONFIG:
                params.push_back({ cmd, { Value::UINT32(0) } });
                break;
            case MipTypes::CMD_GNSS_RTK_CONFIG:
                params.push_back({ cmd, {
                    Value::UINT8(0),
                    Value::UINT8(0),
                    Value::UINT8(0)
                } });
                break;
            default:
                break;
            }
        }

        return params;
    }

    MipCommandSet MipNode_Impl::getConfigCommandBytes() const
    {
        MipCommandSet setCmds;

        std::vector<uint16> descriptors = info().descriptors();

        // build command set in numeric order by command id
        std::sort(descriptors.begin(), descriptors.end());
        
        for (size_t i = 0; i < descriptors.size(); i++)
        {
            // only add commands
            if (MipNodeFeatures::isChannelField(descriptors[i])) { continue; }

            MipTypes::Command cmd = static_cast<MipTypes::Command>(descriptors[i]);

            try
            {
                switch (cmd)
                {
                case MipTypes::CMD_SENSOR_MESSAGE_FORMAT:
                {
                    MipTypes::DataClass dc = MipTypes::DataClass::CLASS_AHRS_IMU;
                    uint16 sampleRateBase = getDataRateBase(dc);
                    MipChannels chs = getMessageFormat(dc);
                    ByteStream s = SensorMessageFormat::buildCommand_set(chs, sampleRateBase);
                    setCmds.push_back(MipCommandBytes(cmd, s.data()));
                }
                break;
                case MipTypes::CMD_GNSS_MESSAGE_FORMAT:
                {
                    MipTypes::DataClass dc = MipTypes::DataClass::CLASS_GNSS;
                    uint16 sampleRateBase = getDataRateBase(dc);
                    MipChannels chs = getMessageFormat(dc);
                    ByteStream s = GnssMessageFormat::buildCommand_set(chs, sampleRateBase);
                    setCmds.push_back(MipCommandBytes(cmd, s.data()));
                }
                break;
                case MipTypes::CMD_EF_MESSAGE_FORMAT:
                {
                    MipTypes::DataClass dc = MipTypes::DataClass::CLASS_ESTFILTER;
                    uint16 sampleRateBase = getDataRateBase(dc);
                    MipChannels chs = getMessageFormat(dc);
                    ByteStream s = EstFilterMessageFormat::buildCommand_set(chs, sampleRateBase);
                    setCmds.push_back(MipCommandBytes(cmd, s.data()));
                }
                break;
                case MipTypes::CMD_CONTINUOUS_DATA_STREAM:
                {
                    MipCommandBytes cmdBytes(cmd);

                    if (features().useLegacyIdsForEnableDataStream())
                    {
                        const std::vector<MipTypes::DataClass> dataClasses = {
                            MipTypes::DataClass::CLASS_AHRS_IMU,
                            MipTypes::DataClass::CLASS_GNSS,
                            MipTypes::DataClass::CLASS_ESTFILTER,
                            MipTypes::DataClass::CLASS_DISPLACEMENT,
                            MipTypes::DataClass::CLASS_GNSS1,
                            MipTypes::DataClass::CLASS_GNSS2,
                            MipTypes::DataClass::CLASS_GNSS3, // RTK
                            MipTypes::DataClass::CLASS_GNSS4,
                            MipTypes::DataClass::CLASS_GNSS5,
                            MipTypes::DataClass::CLASS_SYSTEM
                        };

                        for (MipTypes::DataClass option : dataClasses)
                        {
                            if (features().supportsCategory(option))
                            {
                                bool enabled = isDataStreamEnabled(option);
                                ByteStream s = ContinuousDataStream::buildCommand_set(option, enabled);
                                cmdBytes.add(s.data());
                            }
                        }
                    }
                    else
                    {
                        MipCommandParameters requiredParams = getRequiredParameterDefaults(cmd, false);
                        std::vector<MipFieldValues> specifiers;
                        for (std::pair<MipTypes::Command, MipFieldValues> paramEntry : requiredParams)
                        {
                            specifiers.push_back(paramEntry.second);
                        }

                        cmdBytes = buildMipCommandBytes(cmd, specifiers);
                    }

                    if (cmdBytes.valid())
                    {
                        setCmds.push_back(cmdBytes);
                    }
                }
                break;
                case MipTypes::CMD_GNSS_CONSTELLATION_SETTINGS:
                {
                    ConstellationSettingsData data = getConstellationSettings();
                    GNSS_ConstellationSettings set = GNSS_ConstellationSettings::MakeSetCommand(data);
                    ByteStream s = (ByteStream)set;
                    setCmds.push_back(MipCommandBytes(cmd, s.data()));
                }
                break;
                case MipTypes::CMD_GNSS_SBAS_SETTINGS:
                {
                    SBASSettingsData data = getSBASSettings();
                    SBASSettings set = SBASSettings::MakeSetCommand(data);
                    ByteStream s = (ByteStream)set;
                    setCmds.push_back(MipCommandBytes(cmd, s.data()));
                }
                break;
                case MipTypes::CMD_GNSS_ASSIST_FIX_CONTROL:
                {
                    bool enable = getGNSSAssistedFixControl();
                    ByteStream s = GNSS_AssistedFixControl::buildCommand_set(enable);
                    setCmds.push_back(MipCommandBytes(cmd, s.data()));
                }
                break;
                case MipTypes::CMD_GPS_DYNAMICS_MODE:
                {
                    std::vector<uint8> data = getUint8s(cmd);
                    Uint8Command set = Uint8Command::MakeSetCommand(cmd, data);
                    ByteStream s = (ByteStream)set;
                    setCmds.push_back(MipCommandBytes(cmd, s.data()));
                }
                break;
                case MipTypes::CMD_DATA_STREAM_FORMAT:
                case MipTypes::CMD_POWER_STATES:
                {
                    std::vector<uint8> params;

                    params.push_back(static_cast<uint8>(InertialTypes::DeviceSelector::DEVICE_AHRS));
                    std::vector<uint8> data = getUint8s(cmd, params);
                    Uint8Command set = Uint8Command::MakeSetCommand(cmd, data);
                    ByteStream s = (ByteStream)set;
                    setCmds.push_back(MipCommandBytes(cmd, s.data()));

                    params.clear();

                    params.push_back(static_cast<uint8>(InertialTypes::DeviceSelector::DEVICE_GPS));
                    data = getUint8s(cmd, params);
                    set = Uint8Command::MakeSetCommand(cmd, data);
                    s = (ByteStream)set;
                    setCmds.push_back(MipCommandBytes(cmd, s.data()));
                }
                break;
                case MipTypes::CMD_EF_ENABLE_DISABLE_MEASUREMENTS:
                {
                    std::vector<uint16> data = getUint16s(cmd);
                    Uint16Command set = Uint16Command::MakeSetCommand(cmd, data);
                    ByteStream s = (ByteStream)set;
                    setCmds.push_back(MipCommandBytes(cmd, s.data()));
                }
                break;
                case MipTypes::CMD_SENSOR_SIG_COND_SETTINGS:
                {
                    SignalConditioningValues data = getSignalConditioningSettings();
                    SignalConditioningSettings set = SignalConditioningSettings::MakeSetCommand(data);
                    ByteStream s = (ByteStream)set;
                    setCmds.push_back(MipCommandBytes(cmd, s.data()));
                }
                break;
                case MipTypes::CMD_ACCEL_BIAS:
                {
                    GeometricVector data = getAccelerometerBias();
                    AccelBias set = AccelBias::MakeSetCommand(data);
                    ByteStream s = (ByteStream)set;
                    setCmds.push_back(MipCommandBytes(cmd, s.data()));
                }
                break;
                case MipTypes::CMD_GYRO_BIAS:
                {
                    GeometricVector data = getGyroBias();
                    GyroBias set = GyroBias::MakeSetCommand(data);
                    ByteStream s = (ByteStream)set;
                    setCmds.push_back(MipCommandBytes(cmd, s.data()));
                }
                break;
                case MipTypes::CMD_MAG_HARD_IRON_OFFSET:
                {
                    GeometricVector data = getMagnetometerHardIronOffset();
                    MagnetometerHardIronOffset set = MagnetometerHardIronOffset::MakeSetCommand(data);
                    ByteStream s = (ByteStream)set;
                    setCmds.push_back(MipCommandBytes(cmd, s.data()));
                }
                break;
                case MipTypes::CMD_MAG_SOFT_IRON_MATRIX:
                {
                    Matrix_3x3 data = getMagnetometerSoftIronMatrix();
                    MagnetometerSoftIronMatrix set = MagnetometerSoftIronMatrix::MakeSetCommand(data);
                    ByteStream s = (ByteStream)set;
                    setCmds.push_back(MipCommandBytes(cmd, s.data()));
                }
                break;
                case MipTypes::CMD_CONING_SCULLING:
                {
                    bool data = getConingAndScullingEnable();
                    ConingAndScullingEnable set = ConingAndScullingEnable::MakeSetCommand(data);
                    ByteStream s = (ByteStream)set;
                    setCmds.push_back(MipCommandBytes(cmd, s.data()));
                }
                break;
                case MipTypes::CMD_UART_BAUD_RATE:
                {
                    uint32 data = getUARTBaudRate();
                    UARTBaudRate set = UARTBaudRate::MakeSetCommand(data);
                    ByteStream s = (ByteStream)set;
                    setCmds.push_back(MipCommandBytes(cmd, s.data()));
                }
                break;
                case MipTypes::CMD_LOWPASS_FILTER_SETTINGS:
                {
                    // if new command is supported, don't export legacy to avoid potential float -> u16 truncation issues
                    if (features().supportsCommand(MipTypes::CMD_LOWPASS_ANTIALIASING_FILTER))
                    {
                        break;
                    }

                    MipCommandBytes cmdBytes(cmd);
                    MipTypes::MipChannelFields lowpassFilterChannels = features().supportedLowPassFilterChannelFields();

                    for (size_t j = 0; j < lowpassFilterChannels.size(); j++)
                    {
                        LowPassFilterData data = getLowPassFilterSettings(lowpassFilterChannels[j]);
                        AdvancedLowPassFilterSettings set = AdvancedLowPassFilterSettings::MakeSetCommand(data);
                        ByteStream s = (ByteStream)set;
                        cmdBytes.add(s.data());
                    }

                    setCmds.push_back(cmdBytes);
                }
                break;
                case MipTypes::CMD_COMPLEMENTARY_FILTER_SETTINGS:
                {
                    ComplementaryFilterData data = getComplementaryFilterSettings();
                    ComplementaryFilterSettings set = ComplementaryFilterSettings::MakeSetCommand(data);
                    ByteStream s = (ByteStream)set;
                    setCmds.push_back(MipCommandBytes(cmd, s.data()));
                }
                break;
                case MipTypes::CMD_EF_VEHIC_DYNAMICS_MODE:
                {
                    InertialTypes::VehicleModeType data = getVehicleDynamicsMode();
                    VehicleDynamicsMode set = VehicleDynamicsMode::MakeSetCommand(data);
                    ByteStream s = (ByteStream)set;
                    setCmds.push_back(MipCommandBytes(cmd, s.data()));
                }
                break;
                case MipTypes::CMD_EF_SENS_VEHIC_FRAME_ROTATION_EULER:
                {
                    EulerAngles data = getSensorToVehicleRotation();
                    ByteStream s = SensorToVehicFrameTrans::buildCommand_set(data);
                    setCmds.push_back(MipCommandBytes(cmd, s.data()));
                }
                break;
                case MipTypes::CMD_EF_SENS_VEHIC_FRAME_OFFSET:
                {
                    PositionOffset data = getSensorToVehicleOffset();
                    ByteStream s = SensorToVehicFrameOffset::buildCommand_set(data);
                    setCmds.push_back(MipCommandBytes(cmd, s.data()));
                }
                break;
                case MipTypes::CMD_EF_ANTENNA_OFFSET:
                {
                    PositionOffset data = getAntennaOffset();
                    ByteStream s = AntennaOffset::buildCommand_set(data);
                    setCmds.push_back(MipCommandBytes(cmd, s.data()));
                }
                break;
                case MipTypes::CMD_EF_BIAS_EST_CTRL:
                {
                    EstimationControlOptions data = getEstimationControlFlags();
                    EstimationControlFlags set = EstimationControlFlags::MakeSetCommand(data.AsUint16());
                    ByteStream s = (ByteStream)set;
                    setCmds.push_back(MipCommandBytes(cmd, s.data()));
                }
                break;
                case MipTypes::CMD_EF_GNSS_SRC_CTRL:
                {
                    InertialTypes::GNSS_Source data = getGNSS_SourceControl();
                    GNSS_SourceControl set = GNSS_SourceControl::MakeSetCommand(data);
                    ByteStream s = (ByteStream)set;
                    setCmds.push_back(MipCommandBytes(cmd, s.data()));
                }
                break;
                case MipTypes::CMD_EF_HEADING_UPDATE_CTRL:
                {
                    HeadingUpdateOptions data = getHeadingUpdateControl();
                    HeadingUpdateControl set = HeadingUpdateControl::MakeSetCommand(data);
                    ByteStream s = (ByteStream)set;
                    setCmds.push_back(MipCommandBytes(cmd, s.data()));
                }
                break;
                case MipTypes::CMD_EF_AUTO_INIT_CTRL:
                {
                    bool data = getAutoInitialization();
                    ByteStream s = AutoInitializeControl::buildCommand_set(data);
                    setCmds.push_back(MipCommandBytes(cmd, s.data()));
                }
                break;
                case MipTypes::CMD_EF_ACCEL_WHT_NSE_STD_DEV:
                case MipTypes::CMD_EF_GYRO_WHT_NSE_STD_DEV:
                case MipTypes::CMD_EF_ACCEL_BIAS_MODEL_PARAMS:
                case MipTypes::CMD_EF_GYRO_BIAS_MODEL_PARAMS:
                case MipTypes::CMD_EF_GRAVITY_NOISE_STD_DEV:
                case MipTypes::CMD_EF_HARD_IRON_OFFSET_PROCESS_NOISE:
                case MipTypes::CMD_EF_MAG_NOISE_STD_DEV:
                case MipTypes::CMD_EF_GRAVITY_NOISE_MINIMUM:
                {
                    GeometricVectors data = getGeometricVectors(cmd);
                    GeometricVectorCommand set = GeometricVectorCommand::MakeSetCommand(cmd, data);
                    ByteStream s = (ByteStream)set;
                    setCmds.push_back(MipCommandBytes(cmd, s.data()));
                }
                break;
                case MipTypes::CMD_EF_ZERO_VEL_UPDATE_CTRL:
                {
                    ZUPTSettingsData data = getVelocityZUPT();
                    ByteStream s = VelocityZUPTControl::buildCommand_set(data);
                    setCmds.push_back(MipCommandBytes(cmd, s.data()));
                }
                break;
                case MipTypes::CMD_EF_ZERO_ANG_RATE_UPDATE_CTRL:
                {
                    ZUPTSettingsData data = getAngularRateZUPT();
                    ByteStream s = AngularRateZUPTControl::buildCommand_set(data);
                    setCmds.push_back(MipCommandBytes(cmd, s.data()));
                }
                break;
                case MipTypes::CMD_EF_SET_REF_POSITION:
                {
                    FixedReferencePositionData data = getFixedReferencePosition();
                    SetReferencePosition set = SetReferencePosition::MakeSetCommand(data);
                    ByteStream s = (ByteStream)set;
                    setCmds.push_back(MipCommandBytes(cmd, s.data()));
                }
                break;
                case MipTypes::CMD_EF_PRESS_ALT_NOISE_STD_DEV:
                {
                    std::vector<float> data = getFloats(cmd);
                    FloatCommand set = FloatCommand::MakeSetCommand(cmd, data);
                    ByteStream s = (ByteStream)set;
                    setCmds.push_back(MipCommandBytes(cmd, s.data()));
                }
                break;
                case MipTypes::CMD_EF_SOFT_IRON_OFFSET_PROCESS_NOISE:
                {
                    Matrix_3x3s data = getMatrix3x3s(cmd);
                    Matrix3x3Command set = Matrix3x3Command::MakeSetCommand(cmd, data);
                    ByteStream s = (ByteStream)set;
                    setCmds.push_back(MipCommandBytes(cmd, s.data()));
                }
                break;
                case MipTypes::CMD_EF_DECLINATION_SRC:
                {
                    GeographicSourceOptions data = getDeclinationSource();
                    GeographicSource set = DeclinationSource::MakeSetCommand(data);
                    ByteStream s = (ByteStream)set;
                    setCmds.push_back(MipCommandBytes(cmd, s.data()));
                }
                break;
                case MipTypes::CMD_EF_GRAV_MAGNITUDE_ERR_ADAPT_MEASURE:
                case MipTypes::CMD_EF_MAG_MAGNITUDE_ERR_ADAPT_MEASURE:
                case MipTypes::CMD_EF_MAG_DIP_ANGLE_ERR_ADAPT_MEASURE:
                {
                    AdaptiveMeasurementData data = getAdaptiveMeasurement(cmd);
                    AdaptiveMeasurement set = AdaptiveMeasurement::MakeSetCommand(cmd, data);
                    ByteStream s = (ByteStream)set;
                    setCmds.push_back(MipCommandBytes(cmd, s.data()));
                }
                break;
                case MipTypes::CMD_EF_ALTITUDE_AID_CTRL:
                {
                    bool data = getAltitudeAid();
                    ByteStream s = AltitudeAidControl::buildCommand_set(data);
                    setCmds.push_back(MipCommandBytes(cmd, s.data()));
                }
                break;
                case MipTypes::CMD_EF_PITCH_ROLL_AID_CTRL:
                {
                    bool data = getPitchRollAid();
                    ByteStream s = PitchRollAidControl::buildCommand_set(data);
                    setCmds.push_back(MipCommandBytes(cmd, s.data()));
                }
                break;
                case MipTypes::CMD_EF_INCLINATION_SRC:
                {
                    GeographicSourceOptions data = getInclinationSource();
                    GeographicSource set = InclinationSource::MakeSetCommand(data);
                    ByteStream s = (ByteStream)set;
                    setCmds.push_back(MipCommandBytes(cmd, s.data()));
                }
                break;
                case MipTypes::CMD_EF_FIELD_MAGNITUDE_SRC:
                {
                    GeographicSourceOptions data = getMagneticFieldMagnitudeSource();
                    GeographicSource set = MagneticFieldMagnitudeSource::MakeSetCommand(data);
                    ByteStream s = (ByteStream)set;
                    setCmds.push_back(MipCommandBytes(cmd, s.data()));
                }
                break;
                case MipTypes::CMD_COMMUNICATION_MODE:
                {
                    uint8 data = getCommunicationMode();
                    ByteStream s = CommunicationMode::buildCommand_set(data);
                    setCmds.push_back(MipCommandBytes(cmd, s.data()));
                }
                break;
                case MipTypes::CMD_EF_INITIALIZATION_CONFIG:
                {
                    FilterInitializationValues data = getInitialFilterConfiguration();
                    FilterInitializationConfig set = FilterInitializationConfig::MakeSetCommand(data);
                    ByteStream s = (ByteStream)set;
                    setCmds.push_back(MipCommandBytes(cmd, s.data()));
                }
                break;
                // Do nothing for commands not to be included in settings
                case MipTypes::CMD_GPIO_STATE:
                {
                    break;
                }
                default:
                {
                    MipCommandParameters requiredParams = getRequiredParameterDefaults(cmd, false);
                    std::vector<MipFieldValues> specifiers;
                    for (std::pair<MipTypes::Command, MipFieldValues> paramEntry : requiredParams)
                    {
                        specifiers.push_back(paramEntry.second);
                    }

                    MipCommandParameters reservedParams = getReservedWriteValues(cmd);
                    MipFieldValues reserved;
                    if (reservedParams.size() > 0)
                    {
                        reserved = reservedParams[0].second;
                    }

                    MipCommandBytes cmdBytes = buildMipCommandBytes(cmd, specifiers, reserved);
                    if (cmdBytes.valid())
                    {
                        setCmds.push_back(cmdBytes);
                    }

                    break;
                }
                }
            }
            catch (const Error_MipCmdFailed&)
            {
                // if failed to read device for this command indicate failure and move on
                MipCommandBytes add(cmd);
                add.buildCmdFailed = true;
                setCmds.push_back(add);
            }
        }

        return setCmds;
    }

    MipCommandBytes MipNode_Impl::buildMipCommandBytes(MipTypes::Command cmd, std::vector<MipFieldValues> specifiers, MipFieldValues trailingReserved) const
    {
        // if this command does not support read and write it is not a setting
        if (!(MipCommand::supportsFunctionSelector(cmd, MipTypes::USE_NEW_SETTINGS)
            && MipCommand::supportsFunctionSelector(cmd, MipTypes::READ_BACK_CURRENT_SETTINGS)))
        {
            // return empty command bytes (will not be included)
            return MipCommandBytes(cmd);
        }

        MipCommandBytes cmdBytes(cmd);

        for (MipFieldValues specifier : specifiers)
        {
            MipFieldValues data;
            try
            {
                // get data to set
                data = get(cmd, specifier);
            }
            catch (const Error_MipCmdFailed&)
            {
                // if failed to read device for this specifier
                // indicate at least one failure on cmd and move on
                cmdBytes.buildCmdFailed = true;
                continue;
            }

            // insert hard-coded reserved values at end
            if (trailingReserved.size() > 0)
            {
                data.insert(data.end(), trailingReserved.begin(), trailingReserved.end());
            }

            // build set command
            MipCommand set = MipCommand(cmd,
                MipTypes::FunctionSelector::USE_NEW_SETTINGS,
                data);
            ByteStream s = (ByteStream)set;
            cmdBytes.add(s.data());
        }

        return cmdBytes;
    }

    void MipNode_Impl::sendCommandBytes(MipCommandSet& cmdSet)
    {
        // if CMD_UART_BAUD_RATE or CMD_COMM_PORT_SPEED are included, store a reference and set it last
        //  command seems to run long, and avoid interrupting connection
        MipCommandBytes* uartBaudRate = nullptr;
        MipCommandBytes* commPortSpeed = nullptr;

        for (size_t i = 0; i < cmdSet.size(); i++)
        {
            MipCommandBytes& cmds = cmdSet[i];
            if (cmds.id == MipTypes::CMD_UART_BAUD_RATE)
            {
                uartBaudRate = &cmds;
                continue;
            }
            else if (cmds.id == MipTypes::CMD_COMM_PORT_SPEED)
            {
                commPortSpeed = &cmds;
                continue;
            }

            processMipCommandBytes(cmds);
        }

        if (commPortSpeed != nullptr)
        {
            processMipCommandBytes(*commPortSpeed);
        }

        if (uartBaudRate != nullptr)
        {
            processMipCommandBytes(*uartBaudRate);
        }
    }

    void MipNode_Impl::sendCommandBytes(MipCommandBytes& cmd)
    {
        processMipCommandBytes(cmd);
    }

    uint16 MipNode_Impl::getDataRateBase(MipTypes::DataClass dataClass) const
    {
        if (features().supportsCommand(MipTypes::CMD_GET_BASE_RATE))
        {
            MipFieldValues data = get(MipTypes::CMD_GET_BASE_RATE,
                { Value::UINT8(static_cast<uint8>(dataClass)) });

            // skip first value - echo data class
            return data[1].as_uint16();
        }

        switch(dataClass)
        {
            case MipTypes::CLASS_AHRS_IMU:
            {
                //if we don't already have it stored
                if(m_sensorRateBase == 0)
                {
                    //set the expected response
                    GetSensorDataRateBase::Response r(m_responseCollector);

                    //send the command, wait for the response, and parse the result
                    m_sensorRateBase = r.parseResponse(doCommand(r, GetSensorDataRateBase::buildCommand()));
                }

                return m_sensorRateBase;
            }

            case MipTypes::CLASS_GNSS:
            {
                //if we don't already have it stored
                if(m_gnssRateBase == 0)
                {
                    //set the expected response
                    GetGnssDataRateBase::Response r(m_responseCollector);

                    //send the command, wait for the response, and parse the result
                    m_gnssRateBase = r.parseResponse(doCommand(r, GetGnssDataRateBase::buildCommand()));
                }

                return m_gnssRateBase;
            }

            case MipTypes::CLASS_ESTFILTER:
            default:
            {
                //if we don't already have it stored
                if(m_estfilterRateBase == 0)
                {
                    //set the expected response
                    GetEstFilterDataRateBase::Response r(m_responseCollector);

                    //send the command, wait for the response, and parse the result
                    m_estfilterRateBase = r.parseResponse(doCommand(r, GetEstFilterDataRateBase::buildCommand()));
                }

                return m_estfilterRateBase;
            }
        }
    }

    MipChannels MipNode_Impl::getMessageFormat(MipTypes::DataClass type) const
    {
        //get the sample rate base for this category
        uint16 sampleRateBase = getDataRateBase(type);

        if (features().supportsCommand(MipTypes::CMD_MESSAGE_FORMAT))
        {
            MipFieldValues data = get(MipTypes::CMD_MESSAGE_FORMAT,
                { Value::UINT8(static_cast<uint8>(type)) });

            MipChannels chs;
            uint8 descSet = data[0].as_uint8();
            uint8 count = data[1].as_uint8();
            for (uint8 i = 0; i < count; i++)
            {
                uint8 index = 2 + (i * 2);
                uint8 desc = data[index].as_uint8();
                uint16 decimation = data[index + 1].as_uint16();

                MipTypes::ChannelField channelId = static_cast<MipTypes::ChannelField>(Utils::make_uint16(descSet, desc));
                chs.push_back(MipChannel(channelId,
                    SampleRate::FromInertialRateDecimationInfo(sampleRateBase, decimation)));
            }

            return chs;
        }

        switch(type)
        {
            case MipTypes::CLASS_AHRS_IMU:
            {
                //set the expected response
                SensorMessageFormat::Response r(m_responseCollector, true);

                //send the command, wait for the response, and parse the result
                return r.parseResponse(doCommand(r, SensorMessageFormat::buildCommand_get()), sampleRateBase);
            }

            case MipTypes::CLASS_GNSS:
            {
                //set the expected response
                GnssMessageFormat::Response r(m_responseCollector, true);

                //send the command, wait for the response, and parse the result
                return r.parseResponse(doCommand(r, GnssMessageFormat::buildCommand_get()), sampleRateBase);
            }

            case MipTypes::CLASS_ESTFILTER:
            default:
            {
                //set the expected response
                EstFilterMessageFormat::Response r(m_responseCollector, true);

                //send the command, wait for the response, and parse the result
                return r.parseResponse(doCommand(r, EstFilterMessageFormat::buildCommand_get()), sampleRateBase);
            }
        }
    }

    void MipNode_Impl::setMessageFormat(MipTypes::DataClass dataClass, const MipChannels& channels)
    {
        //get the sample rate base set for this category
        uint16 sampleRateBase = getDataRateBase(dataClass);

        if (features().supportsCommand(MipTypes::CMD_MESSAGE_FORMAT))
        {
            MipFieldValues params;
            params.push_back(Value::UINT8(static_cast<uint8>(dataClass)));
            params.push_back(Value::UINT8(static_cast<uint8>(channels.size())));

            for (MipChannel ch : channels)
            {
                if(static_cast<MipTypes::DataClass>(ch.descriptorSet()) != dataClass)
                {
                    throw Error("MipChannel (" + Utils::toStr(ch.channelField()) + ") is not in the Sensor descriptor set");
                }

                params.push_back(Value::UINT8(ch.fieldDescriptor()));
                params.push_back(Value::UINT16(ch.rateDecimation(sampleRateBase)));
            }

            set(MipTypes::CMD_MESSAGE_FORMAT, params);

            return;
        }

        switch(dataClass)
        {
            case MipTypes::CLASS_AHRS_IMU:
            {
                //set the expected response
                SensorMessageFormat::Response r(m_responseCollector, false);

                //send the command and wait for the response
                doCommand(r, SensorMessageFormat::buildCommand_set(channels, sampleRateBase));
                break;
            }

            case MipTypes::CLASS_GNSS:
            {
                //set the expected response
                GnssMessageFormat::Response r(m_responseCollector, false);

                //send the command and wait for the response
                doCommand(r, GnssMessageFormat::buildCommand_set(channels, sampleRateBase));
                break;
            }

            case MipTypes::CLASS_ESTFILTER:
            default:
            {
                //set the expected response
                EstFilterMessageFormat::Response r(m_responseCollector, false);

                //send the command and wait for the response
                doCommand(r, EstFilterMessageFormat::buildCommand_set(channels, sampleRateBase));
                break;
            }
        }
    }

    void MipNode_Impl::saveMessageFormat(MipTypes::DataClass type)
    {
        if (features().supportsCommand(MipTypes::CMD_MESSAGE_FORMAT))
        {
            saveAsStartup(MipTypes::CMD_MESSAGE_FORMAT,
                { Value::UINT8(static_cast<uint8>(type)) });
            return;
        }

        switch (type)
        {
            case MipTypes::CLASS_AHRS_IMU:
            {
                //set the expected response
                SensorMessageFormat::Response r(m_responseCollector, false);

                //send the command, wait for the response, and parse the result
                doCommand(r, SensorMessageFormat::buildCommand_save());
                break;
            }

            case MipTypes::CLASS_GNSS:
            {
                //set the expected response
                GnssMessageFormat::Response r(m_responseCollector, false);

                //send the command, wait for the response, and parse the result
                doCommand(r, GnssMessageFormat::buildCommand_save());
                break;
            }

            case MipTypes::CLASS_ESTFILTER:
            default:                
            {
                //set the expected response
                EstFilterMessageFormat::Response r(m_responseCollector, false);

                //send the command, wait for the response, and parse the result
                doCommand(r, EstFilterMessageFormat::buildCommand_save());
                break;
            }
        }
    }

    uint8 MipNode_Impl::getCommunicationMode() const
    {
        //set the expected response
        CommunicationMode::Response r(m_responseCollector, true);

        //send the command, wait for the response, and parse the result
        return r.parseResponse(doCommand(r, CommunicationMode::buildCommand_get(), false));
    }

    void MipNode_Impl::setCommunicationMode(uint8 communicationMode)
    {
        //set the expected response
        CommunicationMode::Response r(m_responseCollector, false);

        //send the command and wait for the response
        doCommand(r, CommunicationMode::buildCommand_set(communicationMode), false);

        //reset the node info because we are switching contexts
        resetNodeInfo();
    }

    bool MipNode_Impl::isDataStreamEnabled(MipTypes::DataClass dataClass) const
    {
        if (features().useLegacyIdsForEnableDataStream())
        {
            //set the expected response
            ContinuousDataStream::Response r(m_responseCollector, true, dataClass);

            //send the command, wait for the response, and parse the result
            return r.parseResponse(doCommand(r, ContinuousDataStream::buildCommand_get(dataClass)));
        }

        // ignore first return value - echoed data class
        return get(MipTypes::Command::CMD_CONTINUOUS_DATA_STREAM,
        { Value::UINT8(static_cast<uint8>(dataClass)) })[1].as_bool();
    }

    void MipNode_Impl::enableDataStream(MipTypes::DataClass dataClass, bool enable)
    {
        if (features().useLegacyIdsForEnableDataStream())
        {
            //set the expected response
            ContinuousDataStream::Response r(m_responseCollector, false, dataClass);

            //send the command and wait for the response
            doCommand(r, ContinuousDataStream::buildCommand_set(dataClass, enable));
            return;
        }

        set(MipTypes::Command::CMD_CONTINUOUS_DATA_STREAM,
        {
            Value::UINT8(static_cast<uint8>(dataClass)),
            Value::BOOL(enable)
        });
    }

    void MipNode_Impl::resetFilter()
    {
        ResetFilter::Response r(m_responseCollector);

        doCommand(r, ResetFilter::buildCommand());
    }

    bool MipNode_Impl::getAutoInitialization() const
    {
        AutoInitializeControl::Response r(m_responseCollector, true);

        return r.parseResponse(doCommand(r, AutoInitializeControl::buildCommand_get()));
    }

    void MipNode_Impl::setAutoInitialization(bool enable)
    {
        AutoInitializeControl::Response r(m_responseCollector, false);

        doCommand(r, AutoInitializeControl::buildCommand_set(enable));
    }

    bool MipNode_Impl::getAltitudeAid() const
    {
        AltitudeAidControl::Response r(m_responseCollector, true);

        return r.parseResponse(doCommand(r, AltitudeAidControl::buildCommand_get()));
    }

    void MipNode_Impl::setAltitudeAid(bool enable)
    {
        AltitudeAidControl::Response r(m_responseCollector, false);

        doCommand(r, AltitudeAidControl::buildCommand_set(enable));
    }

    bool MipNode_Impl::getPitchRollAid() const
    {
        PitchRollAidControl::Response r(m_responseCollector, true);

        return r.parseResponse(doCommand(r, PitchRollAidControl::buildCommand_get()));
    }

    void MipNode_Impl::setPitchRollAid(bool enable)
    {
        PitchRollAidControl::Response r(m_responseCollector, false);

        doCommand(r, PitchRollAidControl::buildCommand_set(enable));
    }

    ZUPTSettingsData MipNode_Impl::getVelocityZUPT() const
    {
        VelocityZUPTControl::Response r(m_responseCollector, true);

        return r.parseResponse(doCommand(r, VelocityZUPTControl::buildCommand_get()));
    }

    void MipNode_Impl::setVelocityZUPT(const ZUPTSettingsData& ZUPTSettings)
    {
        VelocityZUPTControl::Response r(m_responseCollector, false);

        doCommand(r, VelocityZUPTControl::buildCommand_set(ZUPTSettings));
    }

    void MipNode_Impl::tareOrientation(const TareAxisValues& axisValue) {
        TareOrientation::Response r(m_responseCollector, false);
        
        doCommand(r, TareOrientation::buildCommand_set(axisValue));
    }

    ZUPTSettingsData MipNode_Impl::getAngularRateZUPT() const
    {
        AngularRateZUPTControl::Response r(m_responseCollector, true);

        return r.parseResponse(doCommand(r, AngularRateZUPTControl::buildCommand_get()));
    }

    void MipNode_Impl::setAngularRateZUPT(const ZUPTSettingsData& ZUPTSettings)
    {
        AngularRateZUPTControl::Response r(m_responseCollector, false);

        doCommand(r, AngularRateZUPTControl::buildCommand_set(ZUPTSettings));
    }

    void MipNode_Impl::setInitialAttitude(const EulerAngles& attitude)
    {
        SetInitialAttitude::Response r(m_responseCollector);

        doCommand(r, SetInitialAttitude::buildCommand(attitude));
    }

    void MipNode_Impl::setInitialHeading(float heading)
    {
        SetInitialHeading::Response r(m_responseCollector);

        doCommand(r, SetInitialHeading::buildCommand(heading));
    }

    FilterInitializationValues MipNode_Impl::getInitialFilterConfiguration() const
    {
        FilterInitializationConfig getConfig = FilterInitializationConfig::MakeGetCommand();
        GenericMipCmdResponse response = SendCommand(getConfig);
        return getConfig.getResponseData(response);
    }

    void MipNode_Impl::setInitialFilterConfiguration(FilterInitializationValues filterConfig)
    {
        FilterInitializationConfig setConfig = FilterInitializationConfig::MakeSetCommand(filterConfig);
        SendCommand(setConfig);
    }

    void MipNode_Impl::cmdedVelZUPT()
    {
        CmdedVelZupt::Response r(m_responseCollector, false);

        doCommand(r, CmdedVelZupt::buildCommand_get());
    }

    void MipNode_Impl::cmdedAngRateZUPT()
    {
        CmdedAngularZupt::Response r(m_responseCollector, false);

        doCommand(r, CmdedAngularZupt::buildCommand_get());
    }

    EulerAngles MipNode_Impl::getSensorToVehicleRotation() const
    {
        SensorToVehicFrameTrans::Response r(m_responseCollector, true);

        return r.parseResponse(doCommand(r, SensorToVehicFrameTrans::buildCommand_get()));
    }

    void MipNode_Impl::setSensorToVehicleRotation(const EulerAngles& angles)
    {
        SensorToVehicFrameTrans::Response r(m_responseCollector, false);

        doCommand(r, SensorToVehicFrameTrans::buildCommand_set(angles));
    }

    PositionOffset MipNode_Impl::getSensorToVehicleOffset() const
    {
        SensorToVehicFrameOffset::Response r(m_responseCollector, true);

        return r.parseResponse(doCommand(r, SensorToVehicFrameOffset::buildCommand_get()));
    }

    void MipNode_Impl::setSensorToVehicleOffset(const PositionOffset& offset)
    {
        SensorToVehicFrameOffset::Response r(m_responseCollector, false);

        doCommand(r, SensorToVehicFrameOffset::buildCommand_set(offset));
    }

    PositionOffset MipNode_Impl::getAntennaOffset() const
    {
        AntennaOffset::Response r(m_responseCollector, true);

        return r.parseResponse(doCommand(r, AntennaOffset::buildCommand_get()));
    }

    void MipNode_Impl::setAntennaOffset(const PositionOffset& offset)
    {
        AntennaOffset::Response r(m_responseCollector, false);

        doCommand(r, AntennaOffset::buildCommand_set(offset));
    }

    bool MipNode_Impl::getGNSSAssistedFixControl() const
    {
        GNSS_AssistedFixControl::Response response(m_responseCollector, true, true);

        return response.parseResponse(doCommand(response, GNSS_AssistedFixControl::buildCommand_get()));
    }

    void MipNode_Impl::setGNSSAssistedFixControl(bool enableAssistedFix)
    {
        GNSS_AssistedFixControl::Response response(m_responseCollector, true, false);

        doCommand(response, GNSS_AssistedFixControl::buildCommand_set(enableAssistedFix));
    }

    TimeUpdate MipNode_Impl::getGNSSAssistTimeUpdate()
    {
        GNSS_AssistTimeUpdate assistTimeUpdate;
        GNSS_AssistTimeUpdate::Response response(m_responseCollector, true, true);

        return response.parseResponse(doCommand(response, assistTimeUpdate.buildCommand_get()));
    }

    void MipNode_Impl::setGNSSAssistTimeUpdate(TimeUpdate update)
    {
        GNSS_AssistTimeUpdate assistTimeUpdate;
        GNSS_AssistTimeUpdate::Response response(m_responseCollector, true, false);

        doCommand(response, assistTimeUpdate.buildCommand_set(update));
    }

    uint32 MipNode_Impl::getGPSTimeUpdateWeeks()
    {
        GPSTimeUpdate gpsTimeUpdate;
        GPSTimeUpdate::Response weekResponse(GPSTimeUpdate::FIELD_DATA_BYTE_WEEKS, m_responseCollector, true, true);

        return weekResponse.parseResponse(doCommand(weekResponse, gpsTimeUpdate.GetWeekValue()));
    }

    uint32 MipNode_Impl::getGPSTimeUpdateSeconds()
    {
        GPSTimeUpdate gpsTimeUpdate;
        GPSTimeUpdate::Response secondsResponse(GPSTimeUpdate::FIELD_DATA_BYTE_SECONDS, m_responseCollector, true, true);

        return secondsResponse.parseResponse(doCommand(secondsResponse, gpsTimeUpdate.GetSecondsValue()));
    }

    void MipNode_Impl::setGPSTimeUpdate(MipTypes::TimeFrame timeFrame, uint32 timeData)
    {
        if (timeFrame == MipTypes::TIME_FRAME_WEEKS)
        {
            GPSTimeUpdate gpsTimeUpdate;
            GPSTimeUpdate::Response response(GPSTimeUpdate::FIELD_DATA_BYTE_WEEKS, m_responseCollector, true, false);
            doCommand(response, gpsTimeUpdate.SetWeekValue (timeData));
        }
        else
        {
            GPSTimeUpdate gpsTimeUpdate;
            GPSTimeUpdate::Response response(GPSTimeUpdate::FIELD_DATA_BYTE_SECONDS, m_responseCollector, true, false);
            doCommand(response, gpsTimeUpdate.SetSecondsValue (timeData));
        }
    }

    void MipNode_Impl::setConstellationSettings(const ConstellationSettingsData& dataToUse)
    {
        GNSS_ConstellationSettings constellationSettings = GNSS_ConstellationSettings::MakeSetCommand(dataToUse);
        SendCommand(constellationSettings);
    }

    ConstellationSettingsData MipNode_Impl::getConstellationSettings() const
    {
        GNSS_ConstellationSettings constellationSettings = GNSS_ConstellationSettings::MakeGetCommand();
        GenericMipCmdResponse response = SendCommand(constellationSettings);
        return constellationSettings.getResponseData(response);
    }

    void MipNode_Impl::setSBASSettings(const SBASSettingsData& dataToUse)
    {
        SBASSettings sbasSettings = SBASSettings::MakeSetCommand(dataToUse);
        SendCommand(sbasSettings);
    }

    SBASSettingsData MipNode_Impl::getSBASSettings() const
    {
        SBASSettings sbasSettings = SBASSettings::MakeGetCommand();
        GenericMipCmdResponse response = SendCommand(sbasSettings);
        return sbasSettings.getResponseData(response);
    }

    void MipNode_Impl::setAccelerometerBias(const GeometricVector& biasVector)
    {
        AccelBias accelBiasSettings = AccelBias::MakeSetCommand(biasVector);
        SendCommand(accelBiasSettings);
    }

    GeometricVector MipNode_Impl::getAccelerometerBias() const
    {
        AccelBias accelBiasCmd = AccelBias::MakeGetCommand();
        GenericMipCmdResponse response = SendCommand(accelBiasCmd);
        return accelBiasCmd.getResponseData(response);
    }

    GeometricVector MipNode_Impl::getGyroBias() const
    {
        GyroBias gyroBiasCmd = GyroBias::MakeGetCommand();
        GenericMipCmdResponse response = SendCommand(gyroBiasCmd);
        return gyroBiasCmd.getResponseData(response);
    }

    void MipNode_Impl::setGyroBias(const GeometricVector& biasVector)
    {
        GyroBias gyroBiasSettings = GyroBias::MakeSetCommand(biasVector);
        SendCommand(gyroBiasSettings);
    }

    GeometricVector MipNode_Impl::captureGyroBias(const uint16& samplingTime)
    {
        // TODO - up to 30 s is a long timeout - should we ignore the response and just let the user
        //      query the gyro bias command afterwards on their own? We would not know about failures in this case.
        //      Maybe parameterize whether or not we should wait for a response?

        // increase timeout to sampling time with additional buffer (at least as long as currently set timeout) to allow for processing on device.
        const uint64 originalTimeout = timeout();
        const uint64 temporaryTimeout = samplingTime + (originalTimeout > 2000 ? originalTimeout : 2000);

        //when this goes out of scope, it will write back the original timeout (need cast for overloaded ambiguity)
        ScopeHelper writebackTimeout(std::bind(static_cast<void(MipNode_Impl::*)(uint64)>(&MipNode_Impl::timeout), this, originalTimeout));

        CaptureGyroBias captureGyroBiasCmd = CaptureGyroBias::MakeCommand(samplingTime);
        std::shared_ptr<GenericMipCommand::Response> responsePtr = captureGyroBiasCmd.createResponse(m_responseCollector);
        timeout(temporaryTimeout);
        GenericMipCmdResponse response = doCommand(*responsePtr, captureGyroBiasCmd);
        return captureGyroBiasCmd.getResponseData(response);
    }

    void MipNode_Impl::findMagnetometerCaptureAutoCalibration()
    {
        MagnetometerCaptureAutoCalibration magnetometerCaptureAutoCalibrationCmd = MagnetometerCaptureAutoCalibration::MakeCommand();
        SendCommand(magnetometerCaptureAutoCalibrationCmd);
    }

    void MipNode_Impl::saveMagnetometerCaptureAutoCalibration()
    {
        MagnetometerCaptureAutoCalibration magnetometerCaptureAutoCalibrationCmd = MagnetometerCaptureAutoCalibration::MakeSaveCommand();
        SendCommand(magnetometerCaptureAutoCalibrationCmd);
    }

    void MipNode_Impl::setMagnetometerSoftIronMatrix(const Matrix_3x3& biasVector)
    {
        MagnetometerSoftIronMatrix magnetometerSoftIronMatrix = MagnetometerSoftIronMatrix::MakeSetCommand(biasVector);
        SendCommand(magnetometerSoftIronMatrix);
    }

    Matrix_3x3 MipNode_Impl::getMagnetometerSoftIronMatrix() const
    {
        MagnetometerSoftIronMatrix magnetometerSoftIronMatrixCmd = MagnetometerSoftIronMatrix::MakeGetCommand();
        GenericMipCmdResponse response = SendCommand(magnetometerSoftIronMatrixCmd);
        return magnetometerSoftIronMatrixCmd.getResponseData(response);
    }

    void MipNode_Impl::setMagnetometerHardIronOffset(const GeometricVector& offsetVector)
    {
        MagnetometerHardIronOffset magnetometerSettings = MagnetometerHardIronOffset::MakeSetCommand(offsetVector);
        SendCommand(magnetometerSettings);
    }

    GeometricVector MipNode_Impl::getMagnetometerHardIronOffset() const
    {
        MagnetometerHardIronOffset magnetometerHIOCmd = MagnetometerHardIronOffset::MakeGetCommand();
        GenericMipCmdResponse response = SendCommand(magnetometerHIOCmd);
        return magnetometerHIOCmd.getResponseData(response);
    }

    void MipNode_Impl::setConingAndScullingEnable(bool enable)
    {
        ConingAndScullingEnable coningAndScullingEnable = ConingAndScullingEnable::MakeSetCommand(enable);
        SendCommand(coningAndScullingEnable);
    }

    bool MipNode_Impl::getConingAndScullingEnable() const
    {
        ConingAndScullingEnable coningAndScullingEnable = ConingAndScullingEnable::MakeGetCommand();
        GenericMipCmdResponse response = SendCommand(coningAndScullingEnable);
        return coningAndScullingEnable.getResponseData(response);
    }

    void MipNode_Impl::setUARTBaudRate(uint32 baudRate, bool resetConnection)
    {
        setUARTBaudRate(baudRate, 1, resetConnection);
    }

    void MipNode_Impl::setUARTBaudRate(uint32 baudRate, uint8 portId, bool resetConnection)
    {
        if (features().supportsCommand(MipTypes::Command::CMD_COMM_PORT_SPEED))
        {
            set(MipTypes::CMD_COMM_PORT_SPEED, {
                Value::UINT8(portId),
                Value::UINT32(baudRate)
            });
        }
        else
        {
            UARTBaudRate baudRateCmd = UARTBaudRate::MakeSetCommand(baudRate);
            SendCommand(baudRateCmd);
        }

        if (resetConnection)
        {
            // .25 second delay before device accepts commands at new baud rate
            Utils::threadSleep(250);

            // update connection to new baud rate
            m_connection.updateBaudRate(baudRate);
        }
    }

    uint32 MipNode_Impl::getUARTBaudRate(uint8 portId) const
    {
        if (features().supportsCommand(MipTypes::Command::CMD_COMM_PORT_SPEED))
        {
            return get(MipTypes::CMD_COMM_PORT_SPEED, {
                Value::UINT8(portId)
            })[1].as_uint32(); // first value echoes portId
        }
        else
        {
            UARTBaudRate baudRateCmd = UARTBaudRate::MakeGetCommand();
            GenericMipCmdResponse response = SendCommand(baudRateCmd);
            return baudRateCmd.getResponseData(response);
        }
    }

    void MipNode_Impl::setLowPassFilterSettings(const LowPassFilterData& data) const
    {
        // only use legacy command if updated not supported
        if (features().supportsCommand(MipTypes::CMD_LOWPASS_FILTER_SETTINGS)
            && !features().supportsCommand(MipTypes::CMD_LOWPASS_ANTIALIASING_FILTER))
        {
            AdvancedLowPassFilterSettings lowPassFilterCmd = AdvancedLowPassFilterSettings::MakeSetCommand(data);
            SendCommand(lowPassFilterCmd);
            return;
        }

        MipFieldValues params = {
            Value::UINT16(static_cast<uint16>(data.dataDescriptor)),
            Value::BOOL(data.applyLowPassFilter),
            Value::BOOL(data.manualFilterBandwidthConfig == LowPassFilterData::USER_SPECIFIED_CUTOFF_FREQ),
            Value::FLOAT(data.cutoffFrequency)
        };

        set(MipTypes::CMD_LOWPASS_ANTIALIASING_FILTER, params);
    }

    LowPassFilterData MipNode_Impl::getLowPassFilterSettings(const MipTypes::ChannelField& dataDescriptor) const
    {
        // only use legacy command if updated not supported
        if (features().supportsCommand(MipTypes::CMD_LOWPASS_FILTER_SETTINGS)
            && !features().supportsCommand(MipTypes::CMD_LOWPASS_ANTIALIASING_FILTER))
        {
            AdvancedLowPassFilterSettings lowPassFilterCmd = AdvancedLowPassFilterSettings::MakeGetCommand(dataDescriptor);
            GenericMipCmdResponse response = SendCommand(lowPassFilterCmd);
            return lowPassFilterCmd.getResponseData(response);
        }

        MipFieldValues params = { Value::UINT16(static_cast<uint16>(dataDescriptor)) };
        MipFieldValues resData = get(MipTypes::CMD_LOWPASS_ANTIALIASING_FILTER, params);

        LowPassFilterData config;
        config.dataDescriptor = dataDescriptor; // parser confirms match to element 0
        config.applyLowPassFilter = resData[1].as_bool();
        config.manualFilterBandwidthConfig = resData[2].as_bool() ? LowPassFilterData::USER_SPECIFIED_CUTOFF_FREQ : LowPassFilterData::SET_TO_HALF_REPORTING_RATE;
        config.cutoffFrequency = resData[3].as_float();

        return config;
    }

    void MipNode_Impl::setComplementaryFilterSettings(const ComplementaryFilterData& data)
    {
        ComplementaryFilterSettings compFilterCmd = ComplementaryFilterSettings::MakeSetCommand(data);
        SendCommand(compFilterCmd);
    }

    ComplementaryFilterData MipNode_Impl::getComplementaryFilterSettings() const
    {
        ComplementaryFilterSettings compFilterCmd = ComplementaryFilterSettings::MakeGetCommand();
        GenericMipCmdResponse response = SendCommand(compFilterCmd);
        return compFilterCmd.getResponseData(response);
    }

    DeviceStatusData MipNode_Impl::getBasicDeviceStatus()
    {
        DeviceStatus deviceStatus = DeviceStatus::MakeGetBasicCommand(MipModel(modelNumber()).baseModel().nodeModel());
        GenericMipCmdResponse response = SendCommand(deviceStatus);
        return deviceStatus.getResponseData(response);
    }

    DeviceStatusData MipNode_Impl::getDiagnosticDeviceStatus()
    {
        DeviceStatus deviceStatus = DeviceStatus::MakeGetDiagnosticCommand(MipModel(modelNumber()).baseModel().nodeModel());
        GenericMipCmdResponse response = SendCommand(deviceStatus);
        return deviceStatus.getResponseData(response);
    }

    void MipNode_Impl::sendRawRTCM_2_3Message(const RTCMMessage& theMessage)
    {
        RawRTCM_2_3Message messageCmd = RawRTCM_2_3Message::MakeCommand(theMessage);
        SendCommand(messageCmd);
    }

    void MipNode_Impl::setVehicleDynamicsMode(const InertialTypes::VehicleModeType& mode)
    {
        VehicleDynamicsMode vehicleMode = VehicleDynamicsMode::MakeSetCommand(mode);
        SendCommand(vehicleMode);
    }

    InertialTypes::VehicleModeType MipNode_Impl::getVehicleDynamicsMode() const
    {
        VehicleDynamicsMode vehicleMode = VehicleDynamicsMode::MakeGetCommand();
        GenericMipCmdResponse response = SendCommand(vehicleMode);
        return vehicleMode.getResponseData(response);
    }

    void MipNode_Impl::setEstimationControlFlags(const EstimationControlOptions& flags)
    {
        EstimationControlFlags estimationControlFlags = EstimationControlFlags::MakeSetCommand(flags.AsUint16());
        SendCommand(estimationControlFlags);
    }

    EstimationControlOptions MipNode_Impl::getEstimationControlFlags() const
    {
        EstimationControlFlags estimationControlFlags = EstimationControlFlags::MakeGetCommand();
        GenericMipCmdResponse response = SendCommand(estimationControlFlags);
        return estimationControlFlags.getResponseData(response);
    }

    void MipNode_Impl::setInclinationSource(const GeographicSourceOptions& options)
    {
        GeographicSource inclinationSource = InclinationSource::MakeSetCommand(options);
        SendCommand(inclinationSource);
    }

    GeographicSourceOptions MipNode_Impl::getInclinationSource() const
    {
        GeographicSource inclinationSource = InclinationSource::MakeGetCommand();
        GenericMipCmdResponse response = SendCommand(inclinationSource);
        return inclinationSource.getResponseData(response);
    }

    void MipNode_Impl::setDeclinationSource(const GeographicSourceOptions& options)
    {
        GeographicSource declinationSource = DeclinationSource::MakeSetCommand(options);
        SendCommand(declinationSource);
    }

    GeographicSourceOptions MipNode_Impl::getDeclinationSource() const
    {
        GeographicSource declinationSource = DeclinationSource::MakeGetCommand();
        GenericMipCmdResponse response = SendCommand(declinationSource);
        return declinationSource.getResponseData(response);
    }

    void MipNode_Impl::setMagneticFieldMagnitudeSource(const GeographicSourceOptions& options)
    {
        GeographicSource magneticFieldMagnitudeSource = MagneticFieldMagnitudeSource::MakeSetCommand(options);
        SendCommand(magneticFieldMagnitudeSource);
    }

    GeographicSourceOptions MipNode_Impl::getMagneticFieldMagnitudeSource() const
    {
        GeographicSource magneticFieldMagnitudeSource = MagneticFieldMagnitudeSource::MakeGetCommand();
        GenericMipCmdResponse response = SendCommand(magneticFieldMagnitudeSource);
        return magneticFieldMagnitudeSource.getResponseData(response);
    }

    void MipNode_Impl::setGNSS_SourceControl(const InertialTypes::GNSS_Source& gnssSource)
    {
        GNSS_SourceControl gnssSourceCtrl = GNSS_SourceControl::MakeSetCommand(gnssSource);
        SendCommand(gnssSourceCtrl);
    }

    InertialTypes::GNSS_Source MipNode_Impl::getGNSS_SourceControl() const
    {
        GNSS_SourceControl gnssSourceCtrl = GNSS_SourceControl::MakeGetCommand();
        GenericMipCmdResponse response = SendCommand(gnssSourceCtrl);
        return gnssSourceCtrl.getResponseData(response);
    }

    void MipNode_Impl::sendExternalGNSSUpdate(const ExternalGNSSUpdateData& gnssUpdateData)
    {
        ExternalGNSSUpdate externalGNSSUpdate = ExternalGNSSUpdate::MakeCommand(gnssUpdateData);
        SendCommand(externalGNSSUpdate);
    }

    void MipNode_Impl::setHeadingUpdateControl(const HeadingUpdateOptions& headingUpdateOptions)
    {
        HeadingUpdateControl headingUpdateControl = HeadingUpdateControl::MakeSetCommand(headingUpdateOptions);
        SendCommand(headingUpdateControl);
    }

    HeadingUpdateOptions MipNode_Impl::getHeadingUpdateControl() const
    {
        HeadingUpdateControl headingUpdateControl = HeadingUpdateControl::MakeGetCommand();
        GenericMipCmdResponse response = SendCommand(headingUpdateControl);
        return headingUpdateControl.getResponseData(response);
    }

    void MipNode_Impl::setAdaptiveMeasurement(MipTypes::Command cmd, const AdaptiveMeasurementData& data)
    {
        AdaptiveMeasurement command = AdaptiveMeasurement::MakeSetCommand(cmd, data);
        SendCommand(command);
    }

    AdaptiveMeasurementData MipNode_Impl::getAdaptiveMeasurement(MipTypes::Command cmd) const
    {
        AdaptiveMeasurement command = AdaptiveMeasurement::MakeGetCommand(cmd);
        GenericMipCmdResponse response = SendCommand(command);
        return command.getResponseData(response);
    }

    void MipNode_Impl::setSignalConditioningSettings(const SignalConditioningValues& data)
    {
        SignalConditioningSettings command = SignalConditioningSettings::MakeSetCommand(data);
        SendCommand(command);
    }

    SignalConditioningValues MipNode_Impl::getSignalConditioningSettings() const
    {
        SignalConditioningSettings command = SignalConditioningSettings::MakeGetCommand();
        GenericMipCmdResponse response = SendCommand(command);
        return command.getResponseData(response);
    }

    void MipNode_Impl::setGeometricVectors(MipTypes::Command cmd, const GeometricVectors& data)
    {
        GeometricVectorCommand command = GeometricVectorCommand::MakeSetCommand(cmd, data);
        SendCommand(command);
    }

    GeometricVectors MipNode_Impl::getGeometricVectors(MipTypes::Command cmd) const
    {
        GeometricVectorCommand command = GeometricVectorCommand::MakeGetCommand(cmd);
        GenericMipCmdResponse response = SendCommand(command);
        return command.getResponseData(response);
    }

    void MipNode_Impl::setMatrix3x3s(MipTypes::Command cmd, const Matrix_3x3s& data)
    {
        Matrix3x3Command command = Matrix3x3Command::MakeSetCommand(cmd, data);
        SendCommand(command);
    }

    Matrix_3x3s MipNode_Impl::getMatrix3x3s(MipTypes::Command cmd) const
    {
        Matrix3x3Command command = Matrix3x3Command::MakeGetCommand(cmd);
        GenericMipCmdResponse response = SendCommand(command);
        return command.getResponseData(response);
    }

    void MipNode_Impl::setUint8s(MipTypes::Command cmd, const std::vector<uint8>& data)
    {
        Uint8Command command = Uint8Command::MakeSetCommand(cmd, data);
        SendCommand(command);
    }

    std::vector<uint8> MipNode_Impl::getUint8s(MipTypes::Command cmd) const
    {
        Uint8Command command = Uint8Command::MakeGetCommand(cmd);
        GenericMipCmdResponse response = SendCommand(command);
        return command.getResponseData(response);
    }

    std::vector<uint8> MipNode_Impl::getUint8s(MipTypes::Command cmd, const std::vector<uint8>& addlParams) const
    {
        Uint8Command command = Uint8Command::MakeGetCommand(cmd, addlParams);
        GenericMipCmdResponse response = SendCommand(command);
        return command.getResponseData(response);
    }

    void MipNode_Impl::setUint16s(MipTypes::Command cmd, const std::vector<uint16>& data)
    {
        Uint16Command command = Uint16Command::MakeSetCommand(cmd, data);
        SendCommand(command);
    }

    std::vector<uint16> MipNode_Impl::getUint16s(MipTypes::Command cmd) const
    {
        Uint16Command command = Uint16Command::MakeGetCommand(cmd);
        GenericMipCmdResponse response = SendCommand(command);
        return command.getResponseData(response);
    }

    std::vector<uint16> MipNode_Impl::getUint16s(MipTypes::Command cmd, const std::vector<uint16>& addlParams) const
    {
        Uint16Command command = Uint16Command::MakeGetCommand(cmd, addlParams);
        GenericMipCmdResponse response = SendCommand(command);
        return command.getResponseData(response);
    }

    void MipNode_Impl::setFloats(MipTypes::Command cmd, const std::vector<float>& data)
    {
        FloatCommand command = FloatCommand::MakeSetCommand(cmd, data);
        SendCommand(command);
    }

    std::vector<float> MipNode_Impl::getFloats(MipTypes::Command cmd) const
    {
        FloatCommand command = FloatCommand::MakeGetCommand(cmd);
        GenericMipCmdResponse response = SendCommand(command);
        return command.getResponseData(response);
    }

    void MipNode_Impl::setFixedReferencePosition(const FixedReferencePositionData& data)
    {
        SetReferencePosition command = SetReferencePosition::MakeSetCommand(data);
        SendCommand(command);
    }

    FixedReferencePositionData MipNode_Impl::getFixedReferencePosition() const
    {
        SetReferencePosition command = SetReferencePosition::MakeGetCommand();
        GenericMipCmdResponse response = SendCommand(command);
        return command.getResponseData(response);
    }

    void MipNode_Impl::sendExternalHeadingUpdate(const HeadingData& headingData)
    {
        ExternalHeadingUpdate externalGNSSUpdate = ExternalHeadingUpdate::MakeCommand(headingData);
        SendCommand(externalGNSSUpdate);
    }

    void MipNode_Impl::sendExternalHeadingUpdate(const HeadingData& headingData, const TimeUpdate& timestamp)
    {
        ExternalHeadingUpdateWithTimestamp externalGNSSUpdate = ExternalHeadingUpdateWithTimestamp::MakeCommand(headingData, timestamp);
        SendCommand(externalGNSSUpdate);
    }

    SampleRate MipNode_Impl::getDisplacementOutputDataRate() const
    {
        DisplacementOutputDataRate::Response r(m_responseCollector, true);

        return r.parseResponse(doCommand(r, DisplacementOutputDataRate::buildCommand_get()));
    }

    LinearEquation MipNode_Impl::getAnalogToDisplacementCal() const
    {
        GetAnalogToDisplacementCals::Response r(m_responseCollector);

        return r.parseResponse(doCommand(r, GetAnalogToDisplacementCals::buildCommand_get()));
    }

    void MipNode_Impl::setDeviceTime()
    {
        setDeviceTime(Utils::getCurrentSystemTime());
    }

    void MipNode_Impl::setDeviceTime(uint64 nanoseconds)
    {
        DeviceTime::Response r(m_responseCollector, false);

        doCommand(r, DeviceTime::buildCommand_get(nanoseconds));
    }

    RTKDeviceStatusFlags MipNode_Impl::getDeviceStatusFlags() const
    {
        DeviceStatusFlags::Response r(m_responseCollector);

        return r.parseResponse(doCommand(r, DeviceStatusFlags::buildCommand_get()));
    }

    std::string MipNode_Impl::getActivationCode() const
    {
        ActivationCode::Response r(m_responseCollector);

        return r.parseResponse(doCommand(r, ActivationCode::buildCommand_get()));
    }

    EventSupportInfo MipNode_Impl::getEventInfo(const EventSupportInfo::Query query) const
    {
        const MipFieldValues response = get(MipTypes::Command::CMD_EVENT_SUPPORT,
                    { Value::UINT8(static_cast<uint8>(query)) }
        );

        EventSupportInfo info{};

        info.query = static_cast<EventSupportInfo::Query>(response[0].as_uint8());
        info.maxInstances = response[1].as_uint8();

        const uint8 numEntries = response[2].as_uint8();

        // Response index starts at 3 and each entry has 2 data values
        for (int index = 3; index < numEntries * 2 + 3; index += 2)
        {
            info.entries.push_back(
                EventTypeInfo(response[index].as_uint8(), response[index + 1].as_uint8())
            );
        }

        return info;
    }

    MipFieldValues MipNode_Impl::get(MipTypes::Command cmdId) const
    {
        MipCommand command = MipCommand(cmdId,
            MipTypes::FunctionSelector::READ_BACK_CURRENT_SETTINGS);
        GenericMipCmdResponse response = SendCommand(command);
        return command.getGenericResponseData(response);
    }

    MipFieldValues MipNode_Impl::get(MipTypes::Command cmdId, MipFieldValues specifier) const
    {
        MipCommand command = MipCommand(cmdId,
            MipTypes::FunctionSelector::READ_BACK_CURRENT_SETTINGS,
            specifier);
        GenericMipCmdResponse response = SendCommand(command);
        return command.getGenericResponseData(response);
    }

    ByteStream MipNode_Impl::get_RawResponseData(MipTypes::Command cmdId, MipFieldValues specifier) const
    {
        MipCommand command = MipCommand(cmdId,
            MipTypes::FunctionSelector::READ_BACK_CURRENT_SETTINGS,
            specifier);
        const GenericMipCmdResponse response = SendCommand(command);
        return response.data();
    }

    void MipNode_Impl::set(MipTypes::Command cmdId, MipFieldValues values) const
    {
        MipCommand command = MipCommand(cmdId,
            MipTypes::FunctionSelector::USE_NEW_SETTINGS,
            values);
        SendCommand(command);
    }

    void MipNode_Impl::saveAsStartup(MipTypes::Command cmdId) const
    {
        MipCommand command = MipCommand(cmdId,
            MipTypes::FunctionSelector::SAVE_CURRENT_SETTINGS);
        SendCommand(command);
    }

    void MipNode_Impl::saveAsStartup(MipTypes::Command cmdId, MipFieldValues specifier) const
    {
        MipCommand command = MipCommand(cmdId,
            MipTypes::FunctionSelector::SAVE_CURRENT_SETTINGS,
            specifier);
        SendCommand(command);
    }

    void MipNode_Impl::loadStartup(MipTypes::Command cmdId) const
    {
        MipCommand command = MipCommand(cmdId,
            MipTypes::FunctionSelector::LOAD_STARTUP_SETTINGS);
        SendCommand(command);
    }

    void MipNode_Impl::loadStartup(MipTypes::Command cmdId, MipFieldValues specifier) const
    {
        MipCommand command = MipCommand(cmdId,
            MipTypes::FunctionSelector::LOAD_STARTUP_SETTINGS,
            specifier);
        SendCommand(command);
    }

    void MipNode_Impl::loadDefault(MipTypes::Command cmdId) const
    {
        MipCommand command = MipCommand(cmdId,
            MipTypes::FunctionSelector::RESET_TO_DEFAULT);
        SendCommand(command);
    }

    void MipNode_Impl::loadDefault(MipTypes::Command cmdId, MipFieldValues specifier) const
    {
        MipCommand command = MipCommand(cmdId,
            MipTypes::FunctionSelector::RESET_TO_DEFAULT,
            specifier);
        SendCommand(command);
    }

    void MipNode_Impl::run(MipTypes::Command cmdId, bool ackNackExpected) const
    {
        MipCommand command = MipCommand(cmdId, false, ackNackExpected);
        SendCommand(command);
    }

    void MipNode_Impl::run(MipTypes::Command cmdId, MipFieldValues specifier, bool ackNackExpected) const
    {
        MipCommand command = MipCommand(cmdId, specifier, false, ackNackExpected);
        SendCommand(command);
    }

    //==============================SendCommand==============================

    GenericMipCmdResponse MipNode_Impl::SendCommand(MipCommand& command) const
    {
        std::shared_ptr<GenericMipCommand::Response> responsePtr = command.createResponse(m_responseCollector);
        return doCommand(*responsePtr, command);
    }
    //=======================================================================

    void MipNode_Impl::processMipCommandBytes(MipCommandBytes& cmd)
    {
        for (size_t i = 0; i < cmd.commands.size(); i++)
        {
            try
            {
                switch (cmd.id)
                {
                // detect set UART Baud Rate so that connection baud rate can be updated
                case MipTypes::Command::CMD_UART_BAUD_RATE:
                case MipTypes::Command::CMD_COMM_PORT_SPEED:
                {
                    MipTypes::FunctionSelector fn = GenericMipCommand::peekFunctionSelector(cmd.commands[i]);
                    if (fn == MipTypes::FunctionSelector::USE_NEW_SETTINGS)
                    {
                        uint8 portId = 1;
                        uint32 baudRate;
                        if (cmd.id == MipTypes::Command::CMD_UART_BAUD_RATE)
                        {
                            baudRate = UARTBaudRate::peekParameterValue(cmd.commands[i]);
                        }
                        else // CMD_COMM_PORT_SPEED
                        {
                            DataBuffer d(cmd.commands[i]);
                            d.skipBytes(GenericMipCommand::CMD_FN_SELCTOR_INDEX + 1);// read params after fn selector
                            portId = d.read_uint8();
                            baudRate = d.read_uint32();
                        }

                        setUARTBaudRate(baudRate, portId);
                        break;
                    }

                    // if this is not a 'set' call, fall through and run the command normally
                }

                default:
                    std::stringstream cmdId;
                    cmdId << std::hex << cmd.id;
                    GenericMipCommand::Response r(cmd.id, m_responseCollector, true, false, cmdId.str());
                    doCommand(r, ByteStream(cmd.commands[i]));
                    break;
                }

                cmd.sendCmdFailed = false;
            }
            catch (Error e)
            {
                cmd.sendCmdFailed = true;
            }
        }
    }
}