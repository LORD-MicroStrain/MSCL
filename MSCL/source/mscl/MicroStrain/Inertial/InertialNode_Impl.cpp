/*******************************************************************************
Copyright(c) 2015-2017 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"
#include "InertialNode_Impl.h"

#include "mscl/Utils.h"
#include "mscl/ScopeHelper.h"
#include "InertialParser.h"
#include "InertialNodeInfo.h"
#include "Commands/ContinuousDataStream.h"
#include "Commands/EstFilter_Commands.h"
#include "Commands/DeviceStartupSettings.h"
#include "Commands/GetDeviceDescriptorSets.h"
#include "Commands/GetExtendedDeviceDescriptorSets.h"
#include "Commands/GNSS_Commands.h"
#include "Commands/Inertial_CyclePower.h"
#include "Commands/Inertial_SetToIdle.h"
#include "Commands/Resume.h"
#include "Commands/Sensor_Commands.h"
#include "Commands/System_Commands.h"
#include "Features/InertialNodeFeatures.h"
#include "Commands/GNSS_AssistedFixControl.h"
#include "Commands/GNSS_AssistTimeUpdate.h"
#include "Commands/GPSTimeUpdate.h"
#include "mscl/MicroStrain/Inertial/Commands/GNSS_SBASSettings.h"
#include "mscl/MicroStrain/Inertial/Commands/GNSS_ConstellationSettings.h"
#include "mscl/MicroStrain/Inertial/Commands/AccelBias.h"
#include "mscl/MicroStrain/Inertial/Commands/GyroBias.h"
#include "mscl/MicroStrain/Inertial/Commands/CaptureGyroBias.h"
#include "mscl/MicroStrain/Inertial/Commands/MagnetometerSoftIronMatrix.h"
#include "mscl/MicroStrain/Inertial/Commands/MagnetometerHardIronOffset.h"
#include "mscl/MicroStrain/Inertial/Commands/ConingAndScullingEnable.h"
#include "mscl/MicroStrain/Inertial/Commands/UARTBaudRate.h"
#include "mscl/MicroStrain/Inertial/Commands/AdvancedLowPassFilterSettings.h"
#include "mscl/MicroStrain/Inertial/Commands/ComplementaryFilterSettings.h"
#include "mscl/MicroStrain/Inertial/Commands/DeviceStatus.h"
#include "mscl/MicroStrain/Inertial/Commands/RawRTCM_2_3Message.h"
#include "mscl/MicroStrain/Inertial/Commands/VehicleDynamicsMode.h"
#include "mscl/MicroStrain/Inertial/Commands/EstimationControlFlags.h"
#include "mscl/MicroStrain/Inertial/Commands/GNSS_SourceControl.h"
#include "mscl/MicroStrain/Inertial/Commands/ExternalGNSSUpdate.h"
#include "mscl/MicroStrain/Inertial/Commands/HeadingUpdateControl.h"
#include "mscl/MicroStrain/Inertial/Commands/ExternalHeadingUpdate.h"
#include "mscl/MicroStrain/Inertial/Commands/ExternalHeadingUpdateWithTimestamp.h"



namespace mscl
{
    InertialNode_Impl::InertialNode_Impl(Connection connection): 
        m_connection(connection),
        m_inertialCommandsTimeout(COMMANDS_DEFAULT_TIMEOUT),
        m_sensorRateBase(0),
        m_gnssRateBase(0),
        m_estfilterRateBase(0)
    {
        //create the response collector
        m_responseCollector.reset(new ResponseCollector);

        m_responseCollector->setConnection(&m_connection);

        //build the parser with the InertialNode_Impl's packet collector and response collector
        m_parser.reset(new InertialParser(&m_packetCollector, m_responseCollector));

        //register the parse function with the connection
        m_connection.registerParser(std::bind(&InertialNode_Impl::parseData, this, std::placeholders::_1));
    }

    InertialNode_Impl::~InertialNode_Impl()
    {
        //unregister the parse functions with the connection, which stops the IO Thread
        m_connection.unregisterParser();
    }

    const Timestamp& InertialNode_Impl::lastCommunicationTime() const
    {
        if(m_lastCommTime.nanoseconds() == 0)
        {
            throw Error_NoData("The Inertial Node has not yet been communicated with.");
        }

        return m_lastCommTime;
    }

    Version InertialNode_Impl::firmwareVersion() const
    {
        return info().deviceInfo().fwVersion;
    }

    InertialModels::NodeModel InertialNode_Impl::model() const
    {
        return info().deviceInfo().model;
    }

    std::string InertialNode_Impl::modelName() const
    {
        return info().deviceInfo().modelName;
    }

    std::string InertialNode_Impl::modelNumber() const
    {
        return info().deviceInfo().modelNumber;
    }

    std::string InertialNode_Impl::serialNumber() const
    {
        return info().deviceInfo().serialNumber;
    }

    std::string InertialNode_Impl::lotNumber() const
    {
        return info().deviceInfo().lotNumber;
    }

    std::string InertialNode_Impl::deviceOptions() const
    {
        return info().deviceInfo().deviceOptions;
    }

    const InertialNodeInfo& InertialNode_Impl::info() const
    {
        //if we haven't initialized the InertialNodeInfo
        if(!m_nodeInfo)
        {
            m_nodeInfo.reset(new InertialNodeInfo(this));
        }

        return (*m_nodeInfo);
    }

    const InertialNodeFeatures& InertialNode_Impl::features() const
    {
        //if the features variable hasn't been set yet
        if(m_features == NULL)
        {
            //set the features variable by creating a new NodeFeatures pointer
            m_features = InertialNodeFeatures::create(info());
        }

        return *(m_features.get());
    }

    Connection& InertialNode_Impl::connection()
    {
        return m_connection;
    }

    SampleRates InertialNode_Impl::supportedSampleRates(InertialTypes::InertialCategory category) const
    {
        SampleRates result;

        //get the sample rate's base rate for this category from the Node
        uint16 baseRate = getDataRateBase(category);

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

    void InertialNode_Impl::parseData(DataBuffer& data)
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

    void InertialNode_Impl::getDataPackets(std::vector<InertialDataPacket>& packets, uint32 timeout, uint32 maxPackets)//maxPackets=0
    {
        //check if a connection error has occurred
        m_connection.throwIfError();

        return m_packetCollector.getDataPackets(packets, timeout, maxPackets);
    }

    uint32 InertialNode_Impl::totalPackets()
    {
        return m_packetCollector.totalPackets();
    }

    void InertialNode_Impl::timeout(uint64 timeout)
    {
        m_inertialCommandsTimeout = timeout;
    }

    uint64 InertialNode_Impl::timeout()
    {
        return m_inertialCommandsTimeout;
    }

    GenericInertialCommandResponse InertialNode_Impl::doCommand(GenericInertialCommand::Response& response, const ByteStream& command, bool verifySupported) const
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
        response.wait(m_inertialCommandsTimeout); // m_inertialCommandsTimeout));

        //get the result from the response
        GenericInertialCommandResponse result = response.result();

        //throw an exception if not successful
        result.throwIfFailed();

        return result;
    }

//============================================================================
//=========================INERTIAL COMMANDS==================================
    bool InertialNode_Impl::ping()
    {
        //create the response for the Ping command
        Ping::Response response (m_responseCollector);

        try
        {
            //send the command and wait for the response
            return doCommand(response, Ping::buildCommand(), false).success();
        }
        catch (Error_InertialCmdFailed&)
        {
            return false;
        }
        catch (Error_Communication&)
        {
            return false;
        }
    }

    void InertialNode_Impl::setToIdle()
    {
        //set the expected response
        Inertial_SetToIdle::Response r(m_responseCollector);

        //send the command and wait for the response
        doCommand(r, Inertial_SetToIdle::buildCommand(), false);
    }

    bool InertialNode_Impl::cyclePower()
    {
        Inertial_CyclePower::Response response (m_responseCollector);

        try
        {
            //send the command and wait for the response
            return doCommand(response, Inertial_CyclePower::buildCommand(), false).success();
        }
        catch (Error_InertialCmdFailed&)
        {
            return false;
        }
        catch (Error_Communication&)
        {
            return false;
        }
	}

    void InertialNode_Impl::resume()
    {
        //set the expected response
        Resume::Response r(m_responseCollector);

        //send the command and wait for the resposne
        doCommand(r, Resume::buildCommand(), false);
    }

    void InertialNode_Impl::saveSettingsAsStartup()
    {
        DeviceStartupSettings::Response r(m_responseCollector);

        doCommand(r, DeviceStartupSettings::buildCommand_saveAsStartup(), false);
    }

    void InertialNode_Impl::loadStartupSettings()
    {
        uint64 originalTimeout = timeout();

        //when this goes out of scope, it will write back the original timeout (need cast for overloaded ambiguity)
        ScopeHelper writebackTimeout(std::bind(static_cast<void(InertialNode_Impl::*)(uint64)>(&InertialNode_Impl::timeout), this, originalTimeout));

        //change the timeout to a minimum of 1200
        uint64 newTimeout = originalTimeout;
        Utils::checkBounds_min(newTimeout, static_cast<uint64>(1200));
        timeout(newTimeout);

        DeviceStartupSettings::Response r(m_responseCollector);

        doCommand(r, DeviceStartupSettings::buildCommand_loadStartup(), false);
    }

    void InertialNode_Impl::loadFactoryDefaultSettings()
    {
        DeviceStartupSettings::Response r(m_responseCollector);

        doCommand(r, DeviceStartupSettings::buildCommand_loadDefault(), false);
    }

    InertialDeviceInfo InertialNode_Impl::getDeviceInfo() const
    {
        //create the response for the GetDeviceInfo command
        GetDeviceInfo::Response r(m_responseCollector);

        //send the command, wait for the response, and parse the result
        return r.parseResponse(doCommand(r, GetDeviceInfo::buildCommand(), false));
    }

    std::vector<uint16> InertialNode_Impl::getDescriptorSets() const
    {
        std::vector<uint16> descriptors;

        //create the response for the GetDeviceDescriptorSets command
        GetDeviceDescriptorSets::Response r(m_responseCollector);

        //append the descriptors to the container
        r.parseResponse(doCommand(r, GetDeviceDescriptorSets::buildCommand(), false), descriptors);

        if(std::find(descriptors.begin(), descriptors.end(), InertialTypes::CMD_GET_EXT_DESCRIPTOR_SETS) != descriptors.end())
        {
            //create the response for the GetExtendedDeviceDescriptorSets command
            GetExtendedDeviceDescriptorSets::Response r2(m_responseCollector);

            //append the extended descriptors to the container
            r2.parseResponse(doCommand(r2, GetExtendedDeviceDescriptorSets::buildCommand(), false), descriptors);
        }

        //send the command, wait for the response, and parse the result
        return descriptors;
    }

    uint16 InertialNode_Impl::getDataRateBase(InertialTypes::InertialCategory category) const
    {
        switch(category)
        {
            case InertialTypes::CATEGORY_SENSOR:
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

            case InertialTypes::CATEGORY_GNSS:
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

            case InertialTypes::CATEGORY_ESTFILTER:
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

    InertialChannels InertialNode_Impl::getMessageFormat(InertialTypes::InertialCategory type)
    {
        //get the sample rate base for this category
        uint16 sampleRateBase = getDataRateBase(type);

        switch(type)
        {
            case InertialTypes::CATEGORY_SENSOR:
            {
                //set the expected response
                SensorMessageFormat::Response r(m_responseCollector, true);

                //send the command, wait for the response, and parse the result
                return r.parseResponse(doCommand(r, SensorMessageFormat::buildCommand_get()), sampleRateBase);
            }

            case InertialTypes::CATEGORY_GNSS:
            {
                //set the expected response
                GnssMessageFormat::Response r(m_responseCollector, true);

                //send the command, wait for the response, and parse the result
                return r.parseResponse(doCommand(r, GnssMessageFormat::buildCommand_get()), sampleRateBase);
            }

            case InertialTypes::CATEGORY_ESTFILTER:
            default:
            {
                //set the expected response
                EstFilterMessageFormat::Response r(m_responseCollector, true);

                //send the command, wait for the response, and parse the result
                return r.parseResponse(doCommand(r, EstFilterMessageFormat::buildCommand_get()), sampleRateBase);
            }
        }
    }

    void InertialNode_Impl::setMessageFormat(InertialTypes::InertialCategory category, const InertialChannels& channels)
    {
        //get the sample rate base set for this category
        uint16 sampleRateBase = getDataRateBase(category);

        switch(category)
        {
            case InertialTypes::CATEGORY_SENSOR:
            {
                //set the expected response
                SensorMessageFormat::Response r(m_responseCollector, false);

                //send the command and wait for the response
                doCommand(r, SensorMessageFormat::buildCommand_set(channels, sampleRateBase));
                break;
            }

            case InertialTypes::CATEGORY_GNSS:
            {
                //set the expected response
                GnssMessageFormat::Response r(m_responseCollector, false);

                //send the command and wait for the response
                doCommand(r, GnssMessageFormat::buildCommand_set(channels, sampleRateBase));
                break;
            }

            case InertialTypes::CATEGORY_ESTFILTER:
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

    void InertialNode_Impl::saveMessageFormat(InertialTypes::InertialCategory type)
    {
        switch (type)
        {
            case InertialTypes::CATEGORY_SENSOR:
            {
                //set the expected response
                SensorMessageFormat::Response r(m_responseCollector, false);

                //send the command, wait for the response, and parse the result
                doCommand(r, SensorMessageFormat::buildCommand_save());
                break;
            }

            case InertialTypes::CATEGORY_GNSS:
            {
                //set the expected response
                GnssMessageFormat::Response r(m_responseCollector, false);

                //send the command, wait for the response, and parse the result
                doCommand(r, GnssMessageFormat::buildCommand_save());
                break;
            }

            case InertialTypes::CATEGORY_ESTFILTER:
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

    uint8 InertialNode_Impl::getCommunicationMode()
    {
        //set the expected response
        CommunicationMode::Response r(m_responseCollector, true);

        //send the command, wait for the response, and parse the result
        return r.parseResponse(doCommand(r, CommunicationMode::buildCommand_get()));
    }

    void InertialNode_Impl::setCommunicationMode(uint8 communicationMode)
    {
        //set the expected response
        CommunicationMode::Response r(m_responseCollector, false);

        //send the command and wait for the response
        doCommand(r, CommunicationMode::buildCommand_set(communicationMode), false);

        //reset the node info because we are switching contexts
        m_nodeInfo.reset();
    }

    void InertialNode_Impl::enableDataStream(InertialTypes::InertialCategory category, bool enable)
    {
        //set the expected response
        ContinuousDataStream::Response r(m_responseCollector, false, category);

        //send the command and wait for the response
        doCommand(r, ContinuousDataStream::buildCommand_set(category, enable));
    }

    void InertialNode_Impl::resetFilter()
    {
        ResetFilter::Response r(m_responseCollector);

        doCommand(r, ResetFilter::buildCommand());
    }

    bool InertialNode_Impl::getAutoInitialization()
    {
        AutoInitializeControl::Response r(m_responseCollector, true);

        return r.parseResponse(doCommand(r, AutoInitializeControl::buildCommand_get()));
    }

    void InertialNode_Impl::setAutoInitialization(bool enable)
    {
        AutoInitializeControl::Response r(m_responseCollector, false);

        doCommand(r, AutoInitializeControl::buildCommand_set(enable));
    }

    void InertialNode_Impl::setInitialAttitude(const EulerAngles& attitude)
    {
        SetInitialAttitude::Response r(m_responseCollector);

        doCommand(r, SetInitialAttitude::buildCommand(attitude));
    }

    void InertialNode_Impl::setInitialHeading(float heading)
    {
        SetInitialHeading::Response r(m_responseCollector);

        doCommand(r, SetInitialHeading::buildCommand(heading));
    }

    EulerAngles InertialNode_Impl::getSensorToVehicleTransformation()
    {
        SensorToVehicFrameTrans::Response r(m_responseCollector, true);

        return r.parseResponse(doCommand(r, SensorToVehicFrameTrans::buildCommand_get()));
    }

    void InertialNode_Impl::setSensorToVehicleTransformation(const EulerAngles& angles)
    {
        SensorToVehicFrameTrans::Response r(m_responseCollector, false);

        doCommand(r, SensorToVehicFrameTrans::buildCommand_set(angles));
    }

    PositionOffset InertialNode_Impl::getSensorToVehicleOffset()
    {
        SensorToVehicFrameOffset::Response r(m_responseCollector, true);

        return r.parseResponse(doCommand(r, SensorToVehicFrameOffset::buildCommand_get()));
    }

    void InertialNode_Impl::setSensorToVehicleOffset(const PositionOffset& offset)
    {
        SensorToVehicFrameOffset::Response r(m_responseCollector, false);

        doCommand(r, SensorToVehicFrameOffset::buildCommand_set(offset));
    }

    PositionOffset InertialNode_Impl::getAntennaOffset()
    {
        AntennaOffset::Response r(m_responseCollector, true);

        return r.parseResponse(doCommand(r, AntennaOffset::buildCommand_get()));
    }

    void InertialNode_Impl::setAntennaOffset(const PositionOffset& offset)
    {
        AntennaOffset::Response r(m_responseCollector, false);

        doCommand(r, AntennaOffset::buildCommand_set(offset));
    }

    bool InertialNode_Impl::getGNSSAssistedFixControl()
    {
        GNSS_AssistedFixControl::Response response(m_responseCollector, true, true);

        return response.parseResponse(doCommand(response, GNSS_AssistedFixControl::buildCommand_get()));
    }

    void InertialNode_Impl::setGNSSAssistedFixControl(bool enableAssistedFix)
    {
        GNSS_AssistedFixControl::Response response(m_responseCollector, true, false);

        doCommand(response, GNSS_AssistedFixControl::buildCommand_set(enableAssistedFix));
    }

    TimeUpdate InertialNode_Impl::getGNSSAssistTimeUpdate()
    {
        GNSS_AssistTimeUpdate assistTimeUpdate;
        GNSS_AssistTimeUpdate::Response response(m_responseCollector, true, true);

        return response.parseResponse(doCommand(response, assistTimeUpdate.buildCommand_get()));
    }

    void InertialNode_Impl::setGNSSAssistTimeUpdate(TimeUpdate update)
    {
        GNSS_AssistTimeUpdate assistTimeUpdate;
        GNSS_AssistTimeUpdate::Response response(m_responseCollector, true, false);

        doCommand(response, assistTimeUpdate.buildCommand_set(update));
    }

    uint32 InertialNode_Impl::getGPSTimeUpdateWeeks()
    {
        GPSTimeUpdate gpsTimeUpdate;
        GPSTimeUpdate::Response weekResponse(GPSTimeUpdate::FIELD_DATA_BYTE_WEEKS, m_responseCollector, true, true);

        return weekResponse.parseResponse(doCommand(weekResponse, gpsTimeUpdate.GetWeekValue()));
    }

    uint32 InertialNode_Impl::getGPSTimeUpdateSeconds()
    {
        GPSTimeUpdate gpsTimeUpdate;
        GPSTimeUpdate::Response secondsResponse(GPSTimeUpdate::FIELD_DATA_BYTE_SECONDS, m_responseCollector, true, true);

        return secondsResponse.parseResponse(doCommand(secondsResponse, gpsTimeUpdate.GetSecondsValue()));
    }

    void InertialNode_Impl::setGPSTimeUpdate(InertialTypes::TimeFrame timeFrame, uint32 timeData)
    {
        if (timeFrame == InertialTypes::TIME_FRAME_WEEKS)
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

    void InertialNode_Impl::setConstellationSettings(const ConstellationSettingsData& dataToUse)
    {
        GNSS_ConstellationSettings constellationSettings = GNSS_ConstellationSettings::MakeSetCommand(dataToUse);
        SendCommand(constellationSettings);
    }

    ConstellationSettingsData InertialNode_Impl::getConstellationSettings()
    {
        GNSS_ConstellationSettings constellationSettings = GNSS_ConstellationSettings::MakeGetCommand();
        GenericInertialCommandResponse response = SendCommand(constellationSettings);
        return constellationSettings.getResponseData(response);
    }

    void InertialNode_Impl::setSBASSettings(const SBASSettingsData& dataToUse)
    {
        SBASSettings sbasSettings = SBASSettings::MakeSetCommand(dataToUse);
        SendCommand(sbasSettings);
    }

    SBASSettingsData InertialNode_Impl::getSBASSettings()
    {
        SBASSettings sbasSettings = SBASSettings::MakeGetCommand();
        GenericInertialCommandResponse response = SendCommand(sbasSettings);
        return sbasSettings.getResponseData(response);
    }

    void InertialNode_Impl::setAccelerometerBias(const GeometricVector& biasVector)
    {
        AccelBias accelBiasSettings = AccelBias::MakeSetCommand(biasVector);
        SendCommand(accelBiasSettings);
    }

    GeometricVector InertialNode_Impl::getAccelerometerBias()
    {
        AccelBias accelBiasCmd = AccelBias::MakeGetCommand();
        GenericInertialCommandResponse response = SendCommand(accelBiasCmd);
        return accelBiasCmd.getResponseData(response);
    }

    GeometricVector InertialNode_Impl::getGyroBias()
    {
        GyroBias gyroBiasCmd = GyroBias::MakeGetCommand();
        GenericInertialCommandResponse response = SendCommand(gyroBiasCmd);
        return gyroBiasCmd.getResponseData(response);
    }

    void InertialNode_Impl::setGyroBias(const GeometricVector& biasVector)
    {
        GyroBias gyroBiasSettings = GyroBias::MakeSetCommand(biasVector);
        SendCommand(gyroBiasSettings);
    }

    GeometricVector InertialNode_Impl::captureGyroBias(const uint16& samplingTime)
    {
        // 5 second response timeout for this command, to allow for 1-3 sec processing on device.
        const uint64 originalTimeout = timeout();
        const uint64 temporaryTimeout = 5000;

        CaptureGyroBias captureGyroBiasCmd = CaptureGyroBias::MakeCommand(samplingTime);
        std::shared_ptr<GenericInertialCommand::Response> responsePtr = captureGyroBiasCmd.createResponse(m_responseCollector);
        timeout(temporaryTimeout);
        GenericInertialCommandResponse response = doCommand(*responsePtr, captureGyroBiasCmd);
        timeout(originalTimeout);
        return captureGyroBiasCmd.getResponseData(response);
    }

    void InertialNode_Impl::setMagnetometerSoftIronMatrix(const Matrix_3x3& biasVector)
    {
        MagnetometerSoftIronMatrix magnetometerSoftIronMatrix = MagnetometerSoftIronMatrix::MakeSetCommand(biasVector);
        SendCommand(magnetometerSoftIronMatrix);
    }

    Matrix_3x3 InertialNode_Impl::getMagnetometerSoftIronMatrix()
    {
        MagnetometerSoftIronMatrix magnetometerSoftIronMatrixCmd = MagnetometerSoftIronMatrix::MakeGetCommand();
        GenericInertialCommandResponse response = SendCommand(magnetometerSoftIronMatrixCmd);
        return magnetometerSoftIronMatrixCmd.getResponseData(response);
    }

    void InertialNode_Impl::setMagnetometerHardIronOffset(const GeometricVector& offsetVector)
    {
        MagnetometerHardIronOffset magnetometerSettings = MagnetometerHardIronOffset::MakeSetCommand(offsetVector);
        SendCommand(magnetometerSettings);
    }

    GeometricVector InertialNode_Impl::getMagnetometerHardIronOffset()
    {
        MagnetometerHardIronOffset magnetometerHIOCmd = MagnetometerHardIronOffset::MakeGetCommand();
        GenericInertialCommandResponse response = SendCommand(magnetometerHIOCmd);
        return magnetometerHIOCmd.getResponseData(response);
    }

    void InertialNode_Impl::setConingAndScullingEnable(bool enable)
    {
        ConingAndScullingEnable coningAndScullingEnable = ConingAndScullingEnable::MakeSetCommand(enable);
        SendCommand(coningAndScullingEnable);
    }

    bool InertialNode_Impl::getConingAndScullingEnable()
    {
        ConingAndScullingEnable coningAndScullingEnable = ConingAndScullingEnable::MakeGetCommand();
        GenericInertialCommandResponse response = SendCommand(coningAndScullingEnable);
        return coningAndScullingEnable.getResponseData(response);
    }

    void InertialNode_Impl::setUARTBaudRate(uint32 baudRate)
    {
        UARTBaudRate baudRateCmd = UARTBaudRate::MakeSetCommand(baudRate);
        SendCommand(baudRateCmd);
    }

    uint32 InertialNode_Impl::getUARTBaudRate()
    {
        UARTBaudRate baudRateCmd = UARTBaudRate::MakeGetCommand();
        GenericInertialCommandResponse response = SendCommand(baudRateCmd);
        return baudRateCmd.getResponseData(response);
    }

    void InertialNode_Impl::setAdvancedLowPassFilterSettings(const AdvancedLowPassFilterData& data)
    {
        AdvancedLowPassFilterSettings lowPassFilterCmd = AdvancedLowPassFilterSettings::MakeSetCommand(data);
        SendCommand(lowPassFilterCmd);
    }

    AdvancedLowPassFilterData InertialNode_Impl::getAdvancedLowPassFilterSettings(const AdvancedLowPassFilterData& data)
    {
        AdvancedLowPassFilterSettings lowPassFilterCmd = AdvancedLowPassFilterSettings::MakeGetCommand(data);
        GenericInertialCommandResponse response = SendCommand(lowPassFilterCmd);
        return lowPassFilterCmd.getResponseData(response);
    }

    void InertialNode_Impl::setComplementaryFilterSettings(const ComplementaryFilterData& data)
    {
        ComplementaryFilterSettings compFilterCmd = ComplementaryFilterSettings::MakeSetCommand(data);
        SendCommand(compFilterCmd);
    }

    ComplementaryFilterData InertialNode_Impl::getComplementaryFilterSettings()
    {
        ComplementaryFilterSettings compFilterCmd = ComplementaryFilterSettings::MakeGetCommand();
        GenericInertialCommandResponse response = SendCommand(compFilterCmd);
        return compFilterCmd.getResponseData(response);
    }

    DeviceStatusData InertialNode_Impl::getBasicDeviceStatus()
    {
        DeviceStatus deviceStatus = DeviceStatus::MakeBasicStatusCommand();
        GenericInertialCommandResponse response = SendCommand(deviceStatus);
        return deviceStatus.getResponseData(response);
    }

    DeviceStatusData InertialNode_Impl::getDiagnosticDeviceStatus()
    {
        DeviceStatus deviceStatus = DeviceStatus::MakeDiagnosticStatusCommand();
        GenericInertialCommandResponse response = SendCommand(deviceStatus);
        return deviceStatus.getResponseData(response);
    }

    void InertialNode_Impl::sendRawRTCM_2_3Message(const RTCMMessage& theMessage)
    {
        RawRTCM_2_3Message messageCmd = RawRTCM_2_3Message::MakeCommand(theMessage);
        SendCommand(messageCmd);
    }

    void InertialNode_Impl::setVehicleDynamicsMode(const VehicleModeType& mode)
    {
        VehicleDynamicsMode vehicleMode = VehicleDynamicsMode::MakeSetCommand(mode);
        SendCommand(vehicleMode);
    }

    VehicleModeType InertialNode_Impl::getVehicleDynamicsMode()
    {
        VehicleDynamicsMode vehicleMode = VehicleDynamicsMode::MakeGetCommand();
        GenericInertialCommandResponse response = SendCommand(vehicleMode);
        return vehicleMode.getResponseData(response);
    }

    void InertialNode_Impl::setEstimationControlFlags(const uint16& flags)
    {
        EstimationControlFlags estimationControlFlags = EstimationControlFlags::MakeSetCommand(flags);
        SendCommand(estimationControlFlags);
    }

    uint16 InertialNode_Impl::getEstimationControlFlags()
    {
        EstimationControlFlags estimationControlFlags = EstimationControlFlags::MakeGetCommand();
        GenericInertialCommandResponse response = SendCommand(estimationControlFlags);
        return estimationControlFlags.getResponseData(response);
    }

    void InertialNode_Impl::setGNSS_SourceControl(const GNSS_Source& gnssSource)
    {
        GNSS_SourceControl gnssSourceCtrl = GNSS_SourceControl::MakeSetCommand(gnssSource);
        SendCommand(gnssSourceCtrl);
    }

    GNSS_Source InertialNode_Impl::getGNSS_SourceControl()
    {
        GNSS_SourceControl gnssSourceCtrl = GNSS_SourceControl::MakeGetCommand();
        GenericInertialCommandResponse response = SendCommand(gnssSourceCtrl);
        return gnssSourceCtrl.getResponseData(response);
    }

    void InertialNode_Impl::sendExternalGNSSUpdate(const ExternalGNSSUpdateData& gnssUpdateData)
    {
        ExternalGNSSUpdate externalGNSSUpdate = ExternalGNSSUpdate::MakeCommand(gnssUpdateData);
        SendCommand(externalGNSSUpdate);
    }

    void InertialNode_Impl::setHeadingUpdateControl(const HeadingUpdateOptions& headingUpdateOptions)
    {
        HeadingUpdateControl headingUpdateControl = HeadingUpdateControl::MakeSetCommand(headingUpdateOptions);
        SendCommand(headingUpdateControl);
    }

    HeadingUpdateOptions InertialNode_Impl::getHeadingUpdateControl()
    {
        HeadingUpdateControl headingUpdateControl = HeadingUpdateControl::MakeGetCommand();
        GenericInertialCommandResponse response = SendCommand(headingUpdateControl);
        return headingUpdateControl.getResponseData(response);
    }

    void InertialNode_Impl::sendExternalHeadingUpdate(const HeadingData& headingData)
    {
        ExternalHeadingUpdate externalGNSSUpdate = ExternalHeadingUpdate::MakeCommand(headingData);
        SendCommand(externalGNSSUpdate);
    }

    void InertialNode_Impl::sendExternalHeadingUpdate(const HeadingData& headingData, const TimeUpdate& timestamp)
    {
        ExternalHeadingUpdateWithTimestamp externalGNSSUpdate = ExternalHeadingUpdateWithTimestamp::MakeCommand(headingData, timestamp);
        SendCommand(externalGNSSUpdate);
    }

    //==============================SendCommand==============================

    GenericInertialCommandResponse InertialNode_Impl::SendCommand(InertialCommand& command)
    {
        std::shared_ptr<GenericInertialCommand::Response> responsePtr = command.createResponse(m_responseCollector);
        return doCommand(*responsePtr, command);
    }
    //=======================================================================
}