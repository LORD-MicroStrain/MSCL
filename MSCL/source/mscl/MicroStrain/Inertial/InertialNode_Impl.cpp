/*******************************************************************************
Copyright(c) 2015-2017 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"
#include "InertialNode_Impl.h"

#include "mscl/Utils.h"
#include "InertialParser.h"
#include "InertialNodeInfo.h"
#include "Commands/ContinuousDataStream.h"
#include "Commands/EstFilter_Commands.h"
#include "Commands/GetDeviceDescriptorSets.h"
#include "Commands/GetExtendedDeviceDescriptorSets.h"
#include "Commands/GNSS_Commands.h"
#include "Commands/Inertial_SetToIdle.h"
#include "Commands/Resume.h"
#include "Commands/Sensor_Commands.h"
#include "Commands/System_Commands.h"
#include "Features/InertialNodeFeatures.h"

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

    GenericInertialCommandResponse InertialNode_Impl::doInertialCmd(GenericInertialCommand::Response& response, const ByteStream& command, InertialTypes::Command commandId, bool verifySupported) const
    {
        if(verifySupported)
        {
            //verify that this command is supported
            if(!features().supportsCommand(commandId))
            {
                throw Error_NotSupported("The command (" + Utils::toStr(commandId) + ") is not supported.");
            }
        }

        //send the command to the device
        m_connection.write(command);

        //wait for the response
        response.wait(m_inertialCommandsTimeout);

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
        Ping::Response r(m_responseCollector);

        try
        {
            //send the command and wait for the response
            return doInertialCmd(r, Ping::buildCommand(), Ping::CMD_ID, false).success();
        }
        catch(Error_InertialCmdFailed&)
        {
            return false;
        }
        catch(Error_Communication&)
        {
            return false;
        }
    }

    void InertialNode_Impl::setToIdle()
    {
        //set the expected response
        Inertial_SetToIdle::Response r(m_responseCollector);

        //send the command and wait for the response
        doInertialCmd(r, Inertial_SetToIdle::buildCommand(), Inertial_SetToIdle::CMD_ID, false);
    }

    void InertialNode_Impl::resume()
    {
        //set the expected response
        Resume::Response r(m_responseCollector);

        //send the command and wait for the resposne
        doInertialCmd(r, Resume::buildCommand(), Resume::CMD_ID, false);
    }

    InertialDeviceInfo InertialNode_Impl::getDeviceInfo() const
    {
        //create the response for the GetDeviceInfo command
        GetDeviceInfo::Response r(m_responseCollector);

        //send the command, wait for the response, and parse the result
        return r.parseResponse(doInertialCmd(r, GetDeviceInfo::buildCommand(), GetDeviceInfo::CMD_ID, false));
    }

    std::vector<uint16> InertialNode_Impl::getDescriptorSets() const
    {
        std::vector<uint16> descriptors;

        //create the response for the GetDeviceDescriptorSets command
        GetDeviceDescriptorSets::Response r(m_responseCollector);

        //append the descriptors to the container
        r.parseResponse(doInertialCmd(r, GetDeviceDescriptorSets::buildCommand(), GetDeviceDescriptorSets::CMD_ID, false), descriptors);

        if(std::find(descriptors.begin(), descriptors.end(), InertialTypes::CMD_GET_EXT_DESCRIPTOR_SETS) != descriptors.end())
        {
            //create the response for the GetExtendedDeviceDescriptorSets command
            GetExtendedDeviceDescriptorSets::Response r2(m_responseCollector);

            //append the extended descriptors to the container
            r2.parseResponse(doInertialCmd(r2, GetExtendedDeviceDescriptorSets::buildCommand(), GetExtendedDeviceDescriptorSets::CMD_ID, false), descriptors);
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
                    m_sensorRateBase = r.parseResponse(doInertialCmd(r, GetSensorDataRateBase::buildCommand(), GetSensorDataRateBase::CMD_ID));
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
                    m_gnssRateBase = r.parseResponse(doInertialCmd(r, GetGnssDataRateBase::buildCommand(), GetGnssDataRateBase::CMD_ID));
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
                    m_estfilterRateBase = r.parseResponse(doInertialCmd(r, GetEstFilterDataRateBase::buildCommand(), GetEstFilterDataRateBase::CMD_ID));
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
                return r.parseResponse(doInertialCmd(r, SensorMessageFormat::buildCommand_get(), SensorMessageFormat::CMD_ID), sampleRateBase);
            }

            case InertialTypes::CATEGORY_GNSS:
            {
                //set the expected response
                GnssMessageFormat::Response r(m_responseCollector, true);

                //send the command, wait for the response, and parse the result
                return r.parseResponse(doInertialCmd(r, GnssMessageFormat::buildCommand_get(), GnssMessageFormat::CMD_ID), sampleRateBase);
            }

            case InertialTypes::CATEGORY_ESTFILTER:
            default:
            {
                //set the expected response
                EstFilterMessageFormat::Response r(m_responseCollector, true);

                //send the command, wait for the response, and parse the result
                return r.parseResponse(doInertialCmd(r, EstFilterMessageFormat::buildCommand_get(), EstFilterMessageFormat::CMD_ID), sampleRateBase);
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
                doInertialCmd(r, SensorMessageFormat::buildCommand_set(channels, sampleRateBase), SensorMessageFormat::CMD_ID);
                break;
            }

            case InertialTypes::CATEGORY_GNSS:
            {
                //set the expected response
                GnssMessageFormat::Response r(m_responseCollector, false);

                //send the command and wait for the response
                doInertialCmd(r, GnssMessageFormat::buildCommand_set(channels, sampleRateBase), GnssMessageFormat::CMD_ID);
                break;
            }

            case InertialTypes::CATEGORY_ESTFILTER:
            default:
            {
                //set the expected response
                EstFilterMessageFormat::Response r(m_responseCollector, false);

                //send the command and wait for the response
                doInertialCmd(r, EstFilterMessageFormat::buildCommand_set(channels, sampleRateBase), EstFilterMessageFormat::CMD_ID);
                break;
            }
        }
    }

    uint8 InertialNode_Impl::getCommunicationMode()
    {
        //set the expected response
        CommunicationMode::Response r(m_responseCollector, true);

        //send the command, wait for the response, and parse the result
        return r.parseResponse(doInertialCmd(r, CommunicationMode::buildCommand_get(), CommunicationMode::CMD_ID));
    }

    void InertialNode_Impl::setCommunicationMode(uint8 communicationMode)
    {
        //set the expected response
        CommunicationMode::Response r(m_responseCollector, false);

        //send the command and wait for the response
        doInertialCmd(r, CommunicationMode::buildCommand_set(communicationMode), CommunicationMode::CMD_ID, false);

        //reset the node info because we are switching contexts
        m_nodeInfo.reset();
    }

    void InertialNode_Impl::enableDataStream(InertialTypes::InertialCategory category, bool enable)
    {
        //set the expected response
        ContinuousDataStream::Response r(m_responseCollector, false, category);

        //send the command and wait for the response
        doInertialCmd(r, ContinuousDataStream::buildCommand_set(category, enable), ContinuousDataStream::CMD_ID);
    }

    void InertialNode_Impl::resetFilter()
    {
        ResetFilter::Response r(m_responseCollector);

        doInertialCmd(r, ResetFilter::buildCommand(), ResetFilter::CMD_ID);
    }

    bool InertialNode_Impl::getAutoInitialization()
    {
        AutoInitializeControl::Response r(m_responseCollector, true);

        return r.parseResponse(doInertialCmd(r, AutoInitializeControl::buildCommand_get(), AutoInitializeControl::CMD_ID));
    }

    void InertialNode_Impl::setAutoInitialization(bool enable)
    {
        AutoInitializeControl::Response r(m_responseCollector, false);

        doInertialCmd(r, AutoInitializeControl::buildCommand_set(enable), AutoInitializeControl::CMD_ID);
    }

    void InertialNode_Impl::setInitialAttitude(const EulerAngles& attitude)
    {
        SetInitialAttitude::Response r(m_responseCollector);

        doInertialCmd(r, SetInitialAttitude::buildCommand(attitude), SetInitialAttitude::CMD_ID);
    }

    void InertialNode_Impl::setInitialHeading(float heading)
    {
        SetInitialHeading::Response r(m_responseCollector);

        doInertialCmd(r, SetInitialHeading::buildCommand(heading), SetInitialHeading::CMD_ID);
    }

    EulerAngles InertialNode_Impl::getSensorToVehicleTransformation()
    {
        SensorToVehicFrameTrans::Response r(m_responseCollector, true);

        return r.parseResponse(doInertialCmd(r, SensorToVehicFrameTrans::buildCommand_get(), SensorToVehicFrameTrans::CMD_ID));
    }

    void InertialNode_Impl::setSensorToVehicleTransformation(const EulerAngles& angles)
    {
        SensorToVehicFrameTrans::Response r(m_responseCollector, false);

        doInertialCmd(r, SensorToVehicFrameTrans::buildCommand_set(angles), SensorToVehicFrameTrans::CMD_ID);
    }

    PositionOffset InertialNode_Impl::getSensorToVehicleOffset()
    {
        SensorToVehicFrameOffset::Response r(m_responseCollector, true);

        return r.parseResponse(doInertialCmd(r, SensorToVehicFrameOffset::buildCommand_get(), SensorToVehicFrameOffset::CMD_ID));
    }

    void InertialNode_Impl::setSensorToVehicleOffset(const PositionOffset& offset)
    {
        SensorToVehicFrameOffset::Response r(m_responseCollector, false);

        doInertialCmd(r, SensorToVehicFrameOffset::buildCommand_set(offset), SensorToVehicFrameOffset::CMD_ID);
    }

    PositionOffset InertialNode_Impl::getAntennaOffset()
    {
        AntennaOffset::Response r(m_responseCollector, true);

        return r.parseResponse(doInertialCmd(r, AntennaOffset::buildCommand_get(), AntennaOffset::CMD_ID));
    }

    void InertialNode_Impl::setAntennaOffset(const PositionOffset& offset)
    {
        AntennaOffset::Response r(m_responseCollector, false);

        doInertialCmd(r, AntennaOffset::buildCommand_set(offset), AntennaOffset::CMD_ID);
    }
//============================================================================
}