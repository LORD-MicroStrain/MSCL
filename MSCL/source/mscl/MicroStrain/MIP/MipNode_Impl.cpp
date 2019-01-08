/*******************************************************************************
Copyright(c) 2015-2019 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"
#include "MipNode_Impl.h"

#include "mscl/Utils.h"
#include "mscl/ScopeHelper.h"
#include "MipParser.h"
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
#include "mscl/MicroStrain/Inertial/Commands/AccelBias.h"
#include "mscl/MicroStrain/Inertial/Commands/AdaptiveMeasurement.h"
#include "mscl/MicroStrain/Inertial/Commands/AdvancedLowPassFilterSettings.h"
#include "mscl/MicroStrain/Inertial/Commands/CaptureGyroBias.h"
#include "mscl/MicroStrain/Inertial/Commands/ComplementaryFilterSettings.h"
#include "mscl/MicroStrain/Inertial/Commands/ConingAndScullingEnable.h"
#include "mscl/MicroStrain/Inertial/Commands/ContinuousDataStream.h"
#include "mscl/MicroStrain/Inertial/Commands/DeviceStartupSettings.h"
#include "mscl/MicroStrain/Inertial/Commands/DeviceStatus.h"
#include "mscl/MicroStrain/Inertial/Commands/EstimationControlFlags.h"
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
#include "mscl/MicroStrain/Inertial/Commands/System_Commands.h"
#include "mscl/MicroStrain/Inertial/Commands/UARTBaudRate.h"
#include "mscl/MicroStrain/Inertial/Commands/VehicleDynamicsMode.h"

namespace mscl
{
    MipNode_Impl::MipNode_Impl(Connection connection): 
        m_connection(connection),
        m_commandsTimeout(COMMANDS_DEFAULT_TIMEOUT),
        m_sensorRateBase(0),
        m_gnssRateBase(0),
        m_estfilterRateBase(0),
        m_lastDeviceState(deviceState_unknown)
    {
        //create the response collector
        m_responseCollector.reset(new ResponseCollector);

        m_responseCollector->setConnection(&m_connection);

        //want to get notified of data packets
        m_packetCollector.requestDataAddedNotification(std::bind(&MipNode_Impl::onDataPacketAdded, this));

        //build the parser with the MipNode_Impl's packet collector and response collector
        m_parser.reset(new MipParser(&m_packetCollector, m_responseCollector));

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
        //if we haven't initialized the MipNodeInfo
        if(!m_nodeInfo)
        {
            m_nodeInfo.reset(new MipNodeInfo(this));
        }

        return (*m_nodeInfo);
    }

    void MipNode_Impl::onDataPacketAdded()
    {
        m_lastDeviceState = DeviceState::deviceState_sampling;
    }

    const MipNodeFeatures& MipNode_Impl::features() const
    {
        //if the features variable hasn't been set yet
        if(m_features == NULL)
        {
            //set the features variable by creating a new NodeFeatures pointer
            m_features = MipNodeFeatures::create(info());
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
        //send the readBuffer to the parser to parse all the bytes
        m_parser->parse(data);

        //update InertialNode last comm time
        m_lastCommTime.setTimeNow();

        //shift any extra bytes that weren't parsed, back to the front of the buffer
        std::size_t bytesShifted = data.shiftExtraToStart();

        if(bytesShifted > 0)
        {
            //subtract the bytes shifted from each command already waiting on a response
            m_responseCollector->adjustResponsesMinBytePos(bytesShifted);
        }
    }

    void MipNode_Impl::getDataPackets(std::vector<MipDataPacket>& packets, uint32 timeout, uint32 maxPackets)//maxPackets=0
    {
        //check if a connection error has occurred
        m_connection.throwIfError();

        return m_packetCollector.getDataPackets(packets, timeout, maxPackets);
    }

    uint32 MipNode_Impl::totalPackets()
    {
        return m_packetCollector.totalPackets();
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

        //send the command and wait for the resposne
        doCommand(r, Resume::buildCommand(), false);
    }

    void MipNode_Impl::saveSettingsAsStartup()
    {
        DeviceStartupSettings::Response r(m_responseCollector);

        doCommand(r, DeviceStartupSettings::buildCommand_saveAsStartup(), false);
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
        DeviceStartupSettings::Response r(m_responseCollector);

        doCommand(r, DeviceStartupSettings::buildCommand_loadDefault(), false);
    }

    void MipNode_Impl::pollData(MipTypes::DataClass dataClass, const MipTypes::MipChannelFields& fields)
    {
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

    uint16 MipNode_Impl::getDataRateBase(MipTypes::DataClass dataClass) const
    {
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

    MipChannels MipNode_Impl::getMessageFormat(MipTypes::DataClass type)
    {
        //get the sample rate base for this category
        uint16 sampleRateBase = getDataRateBase(type);

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

    uint8 MipNode_Impl::getCommunicationMode()
    {
        //set the expected response
        CommunicationMode::Response r(m_responseCollector, true);

        //send the command, wait for the response, and parse the result
        return r.parseResponse(doCommand(r, CommunicationMode::buildCommand_get()));
    }

    void MipNode_Impl::setCommunicationMode(uint8 communicationMode)
    {
        //set the expected response
        CommunicationMode::Response r(m_responseCollector, false);

        //send the command and wait for the response
        doCommand(r, CommunicationMode::buildCommand_set(communicationMode), false);

        //reset the node info because we are switching contexts
        m_nodeInfo.reset();
    }

    void MipNode_Impl::enableDataStream(MipTypes::DataClass dataClass, bool enable)
    {
        //set the expected response
        ContinuousDataStream::Response r(m_responseCollector, false, dataClass);

        //send the command and wait for the response
        doCommand(r, ContinuousDataStream::buildCommand_set(dataClass, enable));
    }

    void MipNode_Impl::resetFilter()
    {
        ResetFilter::Response r(m_responseCollector);

        doCommand(r, ResetFilter::buildCommand());
    }

    bool MipNode_Impl::getAutoInitialization()
    {
        AutoInitializeControl::Response r(m_responseCollector, true);

        return r.parseResponse(doCommand(r, AutoInitializeControl::buildCommand_get()));
    }

    void MipNode_Impl::setAutoInitialization(bool enable)
    {
        AutoInitializeControl::Response r(m_responseCollector, false);

        doCommand(r, AutoInitializeControl::buildCommand_set(enable));
    }

    bool MipNode_Impl::getAltitudeAid()
    {
        AltitudeAidControl::Response r(m_responseCollector, true);

        return r.parseResponse(doCommand(r, AltitudeAidControl::buildCommand_get()));
    }

    void MipNode_Impl::setAltitudeAid(bool enable)
    {
        AltitudeAidControl::Response r(m_responseCollector, false);

        doCommand(r, AltitudeAidControl::buildCommand_set(enable));
    }

    bool MipNode_Impl::getPitchRollAid()
    {
        PitchRollAidControl::Response r(m_responseCollector, true);

        return r.parseResponse(doCommand(r, PitchRollAidControl::buildCommand_get()));
    }

    void MipNode_Impl::setPitchRollAid(bool enable)
    {
        PitchRollAidControl::Response r(m_responseCollector, false);

        doCommand(r, PitchRollAidControl::buildCommand_set(enable));
    }

    ZUPTSettingsData MipNode_Impl::getVelocityZUPT()
    {
        VelocityZUPTControl::Response r(m_responseCollector, true);

        return r.parseResponse(doCommand(r, VelocityZUPTControl::buildCommand_get()));
    }

    void MipNode_Impl::setVelocityZUPT(const ZUPTSettingsData& ZUPTSettings)
    {
        VelocityZUPTControl::Response r(m_responseCollector, false);

        doCommand(r, VelocityZUPTControl::buildCommand_set(ZUPTSettings));
    }

    ZUPTSettingsData MipNode_Impl::getAngularRateZUPT()
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

    EulerAngles MipNode_Impl::getSensorToVehicleTransformation()
    {
        SensorToVehicFrameTrans::Response r(m_responseCollector, true);

        return r.parseResponse(doCommand(r, SensorToVehicFrameTrans::buildCommand_get()));
    }

    void MipNode_Impl::setSensorToVehicleTransformation(const EulerAngles& angles)
    {
        SensorToVehicFrameTrans::Response r(m_responseCollector, false);

        doCommand(r, SensorToVehicFrameTrans::buildCommand_set(angles));
    }

    PositionOffset MipNode_Impl::getSensorToVehicleOffset()
    {
        SensorToVehicFrameOffset::Response r(m_responseCollector, true);

        return r.parseResponse(doCommand(r, SensorToVehicFrameOffset::buildCommand_get()));
    }

    void MipNode_Impl::setSensorToVehicleOffset(const PositionOffset& offset)
    {
        SensorToVehicFrameOffset::Response r(m_responseCollector, false);

        doCommand(r, SensorToVehicFrameOffset::buildCommand_set(offset));
    }

    PositionOffset MipNode_Impl::getAntennaOffset()
    {
        AntennaOffset::Response r(m_responseCollector, true);

        return r.parseResponse(doCommand(r, AntennaOffset::buildCommand_get()));
    }

    void MipNode_Impl::setAntennaOffset(const PositionOffset& offset)
    {
        AntennaOffset::Response r(m_responseCollector, false);

        doCommand(r, AntennaOffset::buildCommand_set(offset));
    }

    bool MipNode_Impl::getGNSSAssistedFixControl()
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

    ConstellationSettingsData MipNode_Impl::getConstellationSettings()
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

    SBASSettingsData MipNode_Impl::getSBASSettings()
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

    GeometricVector MipNode_Impl::getAccelerometerBias()
    {
        AccelBias accelBiasCmd = AccelBias::MakeGetCommand();
        GenericMipCmdResponse response = SendCommand(accelBiasCmd);
        return accelBiasCmd.getResponseData(response);
    }

    GeometricVector MipNode_Impl::getGyroBias()
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
        // 5 second response timeout for this command, to allow for 1-3 sec processing on device.
        const uint64 originalTimeout = timeout();
        const uint64 temporaryTimeout = 5000;

        CaptureGyroBias captureGyroBiasCmd = CaptureGyroBias::MakeCommand(samplingTime);
        std::shared_ptr<GenericMipCommand::Response> responsePtr = captureGyroBiasCmd.createResponse(m_responseCollector);
        timeout(temporaryTimeout);
        GenericMipCmdResponse response = doCommand(*responsePtr, captureGyroBiasCmd);
        timeout(originalTimeout);
        return captureGyroBiasCmd.getResponseData(response);
    }

    void MipNode_Impl::setMagnetometerSoftIronMatrix(const Matrix_3x3& biasVector)
    {
        MagnetometerSoftIronMatrix magnetometerSoftIronMatrix = MagnetometerSoftIronMatrix::MakeSetCommand(biasVector);
        SendCommand(magnetometerSoftIronMatrix);
    }

    Matrix_3x3 MipNode_Impl::getMagnetometerSoftIronMatrix()
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

    GeometricVector MipNode_Impl::getMagnetometerHardIronOffset()
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

    bool MipNode_Impl::getConingAndScullingEnable()
    {
        ConingAndScullingEnable coningAndScullingEnable = ConingAndScullingEnable::MakeGetCommand();
        GenericMipCmdResponse response = SendCommand(coningAndScullingEnable);
        return coningAndScullingEnable.getResponseData(response);
    }

    void MipNode_Impl::setUARTBaudRate(uint32 baudRate)
    {
        UARTBaudRate baudRateCmd = UARTBaudRate::MakeSetCommand(baudRate);
        SendCommand(baudRateCmd);
    }

    uint32 MipNode_Impl::getUARTBaudRate()
    {
        UARTBaudRate baudRateCmd = UARTBaudRate::MakeGetCommand();
        GenericMipCmdResponse response = SendCommand(baudRateCmd);
        return baudRateCmd.getResponseData(response);
    }

    void MipNode_Impl::setAdvancedLowPassFilterSettings(const AdvancedLowPassFilterData& data)
    {
        AdvancedLowPassFilterSettings lowPassFilterCmd = AdvancedLowPassFilterSettings::MakeSetCommand(data);
        SendCommand(lowPassFilterCmd);
    }

    AdvancedLowPassFilterData MipNode_Impl::getAdvancedLowPassFilterSettings(const MipTypes::ChannelField& dataDescriptor)
    {
        AdvancedLowPassFilterSettings lowPassFilterCmd = AdvancedLowPassFilterSettings::MakeGetCommand(dataDescriptor);
        GenericMipCmdResponse response = SendCommand(lowPassFilterCmd);
        return lowPassFilterCmd.getResponseData(response);
    }

    void MipNode_Impl::setComplementaryFilterSettings(const ComplementaryFilterData& data)
    {
        ComplementaryFilterSettings compFilterCmd = ComplementaryFilterSettings::MakeSetCommand(data);
        SendCommand(compFilterCmd);
    }

    ComplementaryFilterData MipNode_Impl::getComplementaryFilterSettings()
    {
        ComplementaryFilterSettings compFilterCmd = ComplementaryFilterSettings::MakeGetCommand();
        GenericMipCmdResponse response = SendCommand(compFilterCmd);
        return compFilterCmd.getResponseData(response);
    }

    DeviceStatusData MipNode_Impl::getBasicDeviceStatus()
    {
        DeviceStatus deviceStatus = DeviceStatus::MakeBasicStatusCommand();
        GenericMipCmdResponse response = SendCommand(deviceStatus);
        return deviceStatus.getResponseData(response);
    }

    DeviceStatusData MipNode_Impl::getDiagnosticDeviceStatus()
    {
        DeviceStatus deviceStatus = DeviceStatus::MakeDiagnosticStatusCommand();
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

    InertialTypes::VehicleModeType MipNode_Impl::getVehicleDynamicsMode()
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

    EstimationControlOptions MipNode_Impl::getEstimationControlFlags()
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

    GeographicSourceOptions MipNode_Impl::getInclinationSource()
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

    GeographicSourceOptions MipNode_Impl::getDeclinationSource()
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

    GeographicSourceOptions MipNode_Impl::getMagneticFieldMagnitudeSource()
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

    InertialTypes::GNSS_Source MipNode_Impl::getGNSS_SourceControl()
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

    HeadingUpdateOptions MipNode_Impl::getHeadingUpdateControl()
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

    AdaptiveMeasurementData MipNode_Impl::getAdaptiveMeasurement(MipTypes::Command cmd)
    {
        AdaptiveMeasurement command = AdaptiveMeasurement::MakeGetCommand(cmd);
        GenericMipCmdResponse response = SendCommand(command);
        return command.getResponseData(response);
    }

    void MipNode_Impl::setGeometricVectors(MipTypes::Command cmd, const GeometricVectors& data)
    {
        GeometricVectorCommand command = GeometricVectorCommand::MakeSetCommand(cmd, data);
        SendCommand(command);
    }

    GeometricVectors MipNode_Impl::getGeometricVectors(MipTypes::Command cmd)
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

    Matrix_3x3s MipNode_Impl::getMatrix3x3s(MipTypes::Command cmd)
    {
        Matrix3x3Command command = Matrix3x3Command::MakeGetCommand(cmd);
        GenericMipCmdResponse response = SendCommand(command);
        return command.getResponseData(response);
    }

    void MipNode_Impl::setFloats(MipTypes::Command cmd, const std::vector<float>& data)
    {
        FloatCommand command = FloatCommand::MakeSetCommand(cmd, data);
        SendCommand(command);
    }

    std::vector<float> MipNode_Impl::getFloats(MipTypes::Command cmd)
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

    FixedReferencePositionData MipNode_Impl::getFixedReferencePosition()
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

    //==============================SendCommand==============================

    GenericMipCmdResponse MipNode_Impl::SendCommand(MipCommand& command)
    {
        std::shared_ptr<GenericMipCommand::Response> responsePtr = command.createResponse(m_responseCollector);
        return doCommand(*responsePtr, command);
    }
    //=======================================================================
}