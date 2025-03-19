/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "mscl/MicroStrain/Wireless/BaseStation_Impl.h"

#include "mscl/MicroStrain/ResponseCollector.h"
#include "mscl/MicroStrain/Wireless/BaseStation.h"
#include "mscl/MicroStrain/Wireless/BaseStationInfo.h"
#include "mscl/MicroStrain/Wireless/Configuration/BaseStationConfig.h"
#include "mscl/MicroStrain/Wireless/Configuration/BaseStationEeprom.h"
#include "mscl/MicroStrain/Wireless/Configuration/BaseStationEepromHelper.h"
#include "mscl/MicroStrain/Wireless/Configuration/BaseStationEepromMap.h"
#include "mscl/MicroStrain/Wireless/Features/BaseStationFeatures.h"
#include "mscl/MicroStrain/Wireless/NodeCommTimes.h"
#include "mscl/MicroStrain/Wireless/WirelessParser.h"
#include "mscl/ScopeHelper.h"

//Base Station commands
#include "mscl/MicroStrain/Wireless/Commands/BaseStation_BeaconStatus.h"
#include "mscl/MicroStrain/Wireless/Commands/BaseStation_Ping.h"
#include "mscl/MicroStrain/Wireless/Commands/BaseStation_Ping_v2.h"
#include "mscl/MicroStrain/Wireless/Commands/BaseStation_ReadEeprom.h"
#include "mscl/MicroStrain/Wireless/Commands/BaseStation_ReadEeprom_v2.h"
#include "mscl/MicroStrain/Wireless/Commands/BaseStation_Reset_v2.h"
#include "mscl/MicroStrain/Wireless/Commands/BaseStation_RfSweepStart.h"
#include "mscl/MicroStrain/Wireless/Commands/BaseStation_SetBeacon.h"
#include "mscl/MicroStrain/Wireless/Commands/BaseStation_SetBeacon_v2.h"
#include "mscl/MicroStrain/Wireless/Commands/BaseStation_WriteEeprom.h"
#include "mscl/MicroStrain/Wireless/Commands/BaseStation_WriteEeprom_v2.h"
#include "mscl/MicroStrain/Wireless/Commands/WirelessProtocol.h"

//Node commands
#include "mscl/MicroStrain/Wireless/Commands/ArmForDatalogging.h"
#include "mscl/MicroStrain/Wireless/Commands/AutoBalance.h"
#include "mscl/MicroStrain/Wireless/Commands/AutoBalance_v2.h"
#include "mscl/MicroStrain/Wireless/Commands/BatchEepromRead.h"
#include "mscl/MicroStrain/Wireless/Commands/Erase.h"
#include "mscl/MicroStrain/Wireless/Commands/Erase_v2.h"
#include "mscl/MicroStrain/Wireless/Commands/GetDatalogSessionInfo.h"
#include "mscl/MicroStrain/Wireless/Commands/GetDiagnosticInfo.h"
#include "mscl/MicroStrain/Wireless/Commands/GetLoggedData.h"
#include "mscl/MicroStrain/Wireless/Commands/LongPing.h"
#include "mscl/MicroStrain/Wireless/Commands/PageDownload.h"
#include "mscl/MicroStrain/Wireless/Commands/Poll.h"
#include "mscl/MicroStrain/Wireless/Commands/ReadEeprom.h"
#include "mscl/MicroStrain/Wireless/Commands/ReadEeprom_v2.h"
#include "mscl/MicroStrain/Wireless/Commands/ReadSingleSensor.h"
#include "mscl/MicroStrain/Wireless/Commands/Reset_v2.h"
#include "mscl/MicroStrain/Wireless/Commands/SetToIdle.h"
#include "mscl/MicroStrain/Wireless/Commands/SetToIdle_v2.h"
#include "mscl/MicroStrain/Wireless/Commands/Sleep.h"
#include "mscl/MicroStrain/Wireless/Commands/Sleep_v2.h"
#include "mscl/MicroStrain/Wireless/Commands/StartNonSyncSampling.h"
#include "mscl/MicroStrain/Wireless/Commands/StartNonSyncSampling_v2.h"
#include "mscl/MicroStrain/Wireless/Commands/StartSyncSampling.h"
#include "mscl/MicroStrain/Wireless/Commands/TestNodeCommProtocol.h"
#include "mscl/MicroStrain/Wireless/Commands/TriggerArmedDatalogging.h"
#include "mscl/MicroStrain/Wireless/Commands/WriteEeprom.h"
#include "mscl/MicroStrain/Wireless/Commands/WriteEeprom_v2.h"

namespace mscl
{
    //Constructor
    BaseStation_Impl::BaseStation_Impl(Connection connection, uint64 baseTimeout) :
        m_connection(connection),
        m_responseCollector(std::make_shared<ResponseCollector>()),
        m_baseCommandsTimeout(0),
        m_nodeCommandsTimeout(0),
        m_frequency(WirelessTypes::freq_unknown),
        m_eeprom(new BaseStationEeprom(this)),
        m_eepromHelper(new BaseStationEepromHelper(this))
    {
        //set the base and node timeouts
        timeout(baseTimeout);

        m_responseCollector->setConnection(&m_connection);

        //build the parser with the base station's packet collector and response collector
        m_parser.reset(new WirelessParser(m_packetCollector, m_responseCollector, m_rawBytePacketCollector));

        //register the parse function with the connection
        m_connection.registerParser(std::bind(&BaseStation_Impl::parseData, this, std::placeholders::_1));
    }

    BaseStation_Impl::BaseStation_Impl(Connection connection) :
        m_connection(connection),
        m_responseCollector(std::make_shared<ResponseCollector>()),
        m_frequency(WirelessTypes::freq_unknown),
        m_eeprom(new BaseStationEeprom(this)),
        m_eepromHelper(new BaseStationEepromHelper(this))
    {
        uint64 tempTimeout;

        //no timeout provided, create it based on the connection type
        switch(connection.type())
        {
            case Connection::connectionType_serial:
            case Connection::connectionType_unixSocket:
                tempTimeout = BaseStation::BASE_COMMANDS_DEFAULT_TIMEOUT;
                break;

            case Connection::connectionType_tcp:
            case Connection::connectionType_webSocket:
            default:
                tempTimeout = BaseStation::ETHERNET_BASE_COMMANDS_DEFAULT_TIMEOUT;
                break;
        }

        //set the base and node timeouts
        timeout(tempTimeout);

        m_responseCollector->setConnection(&m_connection);

        //build the parser with the base station's packet collector and response collector
        m_parser.reset(new WirelessParser(m_packetCollector, m_responseCollector, m_rawBytePacketCollector));

        //register the parse function with the connection
        m_connection.registerParser(std::bind(&BaseStation_Impl::parseData, this, std::placeholders::_1));
    }

    //Destructor
    BaseStation_Impl::~BaseStation_Impl()
    {
        //unregister the parse functions with the connection, which stops the IO Thread
        m_connection.unregisterParser();
    }

    void BaseStation_Impl::determineProtocols() const
    {
        Version asppVersion_lxrs;
        Version asppVersion_lxrsPlus;

        uint8 origRetries = m_eeprom->getNumRetries();

        //when this goes out of scope, the number of retries will be changed back to what it was before
        ScopeHelper writebackRetries(std::bind(&BaseStationEeprom::setNumRetries, m_eeprom.get(), origRetries));

        m_eeprom->setNumRetries(0);

        rec_mutex_lock_guard lock(m_protocolMutex);

        //=========================================================================
        // Determine the firmware version by attempting to use multiple protocols
        try
        {
            //try reading with protocol v1.1 (has read eeprom v2)
            m_protocol_lxrs = WirelessProtocol::v1_1();
            m_protocol_lxrsPlus = WirelessProtocol::v1_1();
            m_commProtocol.reset(new WirelessTypes::CommProtocol(WirelessTypes::commProtocol_lxrs));

            asppVersion_lxrs = m_eepromHelper->read_asppVersion(WirelessTypes::commProtocol_lxrs);
            asppVersion_lxrsPlus = m_eepromHelper->read_asppVersion(WirelessTypes::commProtocol_lxrsPlus);
            m_commProtocol.reset(new WirelessTypes::CommProtocol(m_eepromHelper->read_commProtocol()));
        }
        catch(Error_Communication&)
        {
            //Failed reading with protocol v1.1 - Now try v1.0 (has read eeprom v1)

            try
            {
                //try reading with protocol v1.0
                m_protocol_lxrs = WirelessProtocol::v1_0();
                m_protocol_lxrsPlus = WirelessProtocol::v1_0();

                asppVersion_lxrs = m_eepromHelper->read_asppVersion(WirelessTypes::commProtocol_lxrs);
                asppVersion_lxrsPlus = m_eepromHelper->read_asppVersion(WirelessTypes::commProtocol_lxrsPlus);
                m_commProtocol.reset(new WirelessTypes::CommProtocol(m_eepromHelper->read_commProtocol()));
            }
            catch(Error_Communication&)
            {
                //we failed to determine the protocol
                //need to clear out the protocol
                m_protocol_lxrs.reset();
                m_protocol_lxrsPlus.reset();
                m_commProtocol.reset();

                //rethrow the exception
                throw;
            }
        }
        //=========================================================================

        m_protocol_lxrs = WirelessProtocol::getProtocol(asppVersion_lxrs);
        m_protocol_lxrsPlus = WirelessProtocol::getProtocol(asppVersion_lxrsPlus);
    }

    BaseStationEepromHelper& BaseStation_Impl::eeHelper() const
    {
        return *m_eepromHelper.get();
    }

    bool BaseStation_Impl::doCommand(WirelessResponsePattern& response, const ByteStream& cmdBytes, uint64 timeout)
    {
        RawBytePacket rawBytePacket;
        rawBytePacket.payload(cmdBytes.data());
        rawBytePacket.source(RawBytePacket::FROM_SEND);
        rawBytePacket.type(RawBytePacket::COMMAND_PACKET);

        m_rawBytePacketCollector.addRawBytePacket(rawBytePacket);

        //set the response collector of the ResponsePattern (registers response as well)
        response.setResponseCollector(m_responseCollector);

        //send the command to the base station
        m_connection.write(cmdBytes);

        //wait for the response or a timeout
        response.wait(timeout);

        if(response.baseReceived() && !response.fullyMatched())
        {
            //base received the command and sent to node, wait for the new timeout for the Node's response
            response.wait(response.baseReceivedWaitTime() + timeoutToAdd());
        }

        //return the result of the command/response
        return response.success();
    }

    const BaseStationFeatures& BaseStation_Impl::features() const
    {
        //if the features variable hasn't been set yet
        if(m_features == NULL)
        {
            //create the BaseStationInfo to give to the features
            BaseStationInfo info(this);

            //set the features variable by creating a new BaseStationFeatures pointer
            m_features = BaseStationFeatures::create(info);
        }

        return *m_features.get();
    }

    Connection& BaseStation_Impl::connection()
    {
        return m_connection;
    }

    const WirelessProtocol& BaseStation_Impl::protocol(WirelessTypes::CommProtocol commProtocol) const
    {
        rec_mutex_lock_guard lock(m_protocolMutex);

        //if the protocol variable hasn't been set yet
        if(m_protocol_lxrs == NULL || m_protocol_lxrsPlus == NULL)
        {
            //determine and assign the protocols for this BaseStation
            determineProtocols();
        }

        switch(commProtocol)
        {
            case WirelessTypes::commProtocol_lxrsPlus:
                return *m_protocol_lxrsPlus.get();

            case WirelessTypes::commProtocol_lxrs:
                return *m_protocol_lxrs.get();

            default:
                throw Error("Invalid CommProtocol (" + Utils::toStr(commProtocol) + ")");
        }
    }

    const Timestamp& BaseStation_Impl::lastCommunicationTime() const
    {
        if(m_lastCommTime.nanoseconds() == 0)
        {
            throw Error_NoData("The BaseStation has not yet been communicated with.");
        }

        return m_lastCommTime;
    }

    void BaseStation_Impl::parseData(DataBuffer& data)
    {
        //send the readBuffer to the parser to parse all the bytes
        m_parser->parse(data, m_frequency);

        m_lastCommTime.setTimeNow();

        //shift any extra bytes that weren't parsed, back to the front of the buffer
        std::size_t bytesShifted = data.shiftExtraToStart();

        if(bytesShifted > 0)
        {
            //subtract the bytes shifted from each command already waiting on a response
            m_responseCollector->adjustResponsesMinBytePos(bytesShifted);
        }
    }

    void BaseStation_Impl::useEepromCache(bool useCache)
    {
        m_eeprom->useCache(useCache);
    }

    void BaseStation_Impl::setReadWriteRetries(uint8 numRetries)
    {
        m_eeprom->setNumRetries(numRetries);
    }

    uint8 BaseStation_Impl::getReadWriteRetries() const
    {
        return m_eeprom->getNumRetries();
    }

    void BaseStation_Impl::clearEepromCache()
    {
        rec_mutex_lock_guard lock(m_protocolMutex);

        m_eeprom->clearCache();

        //features may need to be reset if firmware version or model changed
        if(m_features != NULL)
        {
            m_features.reset();
        }

        //protocol may need to be reset if ASPP or firmware version changed
        if(m_protocol_lxrs != NULL)
        {
            m_protocol_lxrs.reset();
        }
        if(m_protocol_lxrsPlus != NULL)
        {
            m_protocol_lxrsPlus.reset();
        }

        if(m_commProtocol != nullptr)
        {
            m_commProtocol.reset();
        }
    }

    WirelessTypes::Frequency BaseStation_Impl::frequency() const
    {
        //if the frequency is unknown
        if(m_frequency == WirelessTypes::freq_unknown)
        {
            //read the frequency from eeprom
            m_frequency = static_cast<WirelessTypes::Frequency>(readEeprom(BaseStationEepromMap::FREQUENCY).as_uint16());
        }

        return m_frequency;
    }

    WirelessTypes::CommProtocol BaseStation_Impl::communicationProtocol() const
    {
        rec_mutex_lock_guard lock(m_protocolMutex);

        m_commProtocol.reset(new WirelessTypes::CommProtocol(m_eepromHelper->read_commProtocol()));
        return *m_commProtocol;
    }

    WirelessTypes::RegionCode BaseStation_Impl::regionCode() const
    {
        return m_eepromHelper->read_regionCode();
    }

    Version BaseStation_Impl::firmwareVersion() const
    {
        return m_eepromHelper->read_fwVersion();
    }

    WirelessModels::BaseModel BaseStation_Impl::model() const
    {
        return m_eepromHelper->read_model();
    }

    std::string BaseStation_Impl::serial() const
    {
        return m_eepromHelper->read_serial();
    }

    WirelessTypes::MicroControllerType BaseStation_Impl::microcontroller() const
    {
        return m_eepromHelper->read_microcontroller();
    }

    void BaseStation_Impl::getData(std::vector<DataSweep>& sweeps, uint32 timeout, uint32 maxSweeps)
    {
        //check if a connection error has occurred
        m_connection.throwIfError();

        return m_packetCollector.getDataSweeps(sweeps, timeout, maxSweeps);
    }

    void BaseStation_Impl::getRawBytePackets(RawBytePackets& packets, uint32 timeout, uint32 maxPackets)//maxPackets=0
    {
        //check if a connection error has occurred
        m_connection.throwIfError();

        return m_rawBytePacketCollector.getRawBytePackets(packets, timeout, maxPackets);
    }

    uint32 BaseStation_Impl::totalData()
    {
        return m_packetCollector.totalSweeps();
    }

    NodeDiscoveries BaseStation_Impl::getNodeDiscoveries()
    {
        //check if a connection error has occurred
        m_connection.throwIfError();

        return m_packetCollector.getNodeDiscoveries();
    }

    //getTimeForBeacon
    //    Gets the system time in seconds, as close to 0 milliseconds as possible
    uint32 BaseStation_Impl::getTimeForBeacon()
    {
        //get the current system time in UTC nanoseconds
        uint64 timeNow = Utils::getCurrentSystemTime();

        //get the current milliseconds of the time
        int milliseconds = timeNow % TimeSpan::NANOSECONDS_PER_SECOND / TimeSpan::NANOSECONDS_PER_MILLISECOND;

        //keep track of the closest milliseconds value to 0 milliseconds
        int closestMilli = milliseconds;

        bool sendCommand = false;
        int currentMilli;

        while(!sendCommand)
        {
            //get the current system time again
            timeNow = Utils::getCurrentSystemTime();

            //get the current milliseconds of the time again
            currentMilli = timeNow % TimeSpan::NANOSECONDS_PER_SECOND / TimeSpan::NANOSECONDS_PER_MILLISECOND;

            //if we got closer to 0 milliseconds
            if(currentMilli >= closestMilli)
            {
                //keep track of this new millisecond value
                closestMilli = currentMilli;

                //sleep for 1 millisecond
                Utils::threadSleep(1);
            }
            else
            {
                //we got as close as possible to 0 milliseconds, so send the command
                sendCommand = true;
            }
        }

        //get the current time in seconds
        uint32 timeNowInSeconds = static_cast<uint32>(timeNow / 1000000000);

        return timeNowInSeconds;
    }

    void BaseStation_Impl::timeout(uint64 timeout)
    {
        m_baseCommandsTimeout = timeout;

        //add more time for communication between Nodes and Bases
        m_nodeCommandsTimeout = timeout + timeout / 2 + 50;
    }

    uint64 BaseStation_Impl::timeout() const
    {
        return m_baseCommandsTimeout;
    }


    //================================================================================================
    //                                    BASE STATION COMMANDS
    //================================================================================================

    bool BaseStation_Impl::ping()
    {
        try
        {
            return protocol(communicationProtocol()).m_pingBase(this);
        }
        catch(Error&)
        {
            //treat errors (such as failing to determine protocol) as if it failed to ping
            return false;
        }
    }

    bool BaseStation_Impl::read(uint16 eepromAddress, uint16& result)
    {
        rec_mutex_lock_guard lock(m_protocolMutex);

        //if the radioMode value hasn't been set yet
        if(m_commProtocol == nullptr)
        {
            determineProtocols();
        }

        //always use the cached radioMode value here so that we don't get in an infinite loop:
        //  protocol( communicationProtocol() )
        //      read_communicationProtocol()
        //          readEeprom()
        //              protocol( communicationProtocol() )

        return protocol(*m_commProtocol).m_readBaseEeprom(this, eepromAddress, result);
    }

    bool BaseStation_Impl::write(uint16 eepromAddress, uint16 value)
    {
        return protocol(communicationProtocol()).m_writeBaseEeprom(this, eepromAddress, value);
    }

    Timestamp BaseStation_Impl::enableBeacon()
    {
        //return the result of the enableBeacon function given the current system time as the start time
        return protocol(communicationProtocol()).m_enableBeacon(this, getTimeForBeacon());
    }

    Timestamp BaseStation_Impl::enableBeacon(uint32 utcTime)
    {
        return protocol(communicationProtocol()).m_enableBeacon(this, utcTime);
    }

    void BaseStation_Impl::disableBeacon()
    {
        try
        {
            //call the enableBeacon command with 0xFFFFFFFF for the timestamp to disable it
            protocol(communicationProtocol()).m_enableBeacon(this, 0xFFFFFFFF);
        }
        catch(Error_Communication&)
        {
            //want to rethrow the same exception with different text
            throw Error_Communication("The Disable Beacon command has failed");
        }
    }

    BeaconStatus BaseStation_Impl::beaconStatus()
    {
        //verify the basestation support beacon status
        if(!features().supportsBeaconStatus())
        {
            throw Error_NotSupported("The Beacon Status command is not supported by this BaseStation.");
        }

        return protocol(communicationProtocol()).m_beaconStatus(this);
    }

    void BaseStation_Impl::startRfSweepMode()
    {
        //verify rf sweep mode is supported
        if(!features().supportsRfSweepMode())
        {
            throw Error_NotSupported("RF Sweep Mode is not supported by this BaseStation.");
        }

        return protocol(communicationProtocol()).m_startRfSweep(this, 0, 0, 0, 0);
    }

    void BaseStation_Impl::startRfSweepMode(uint32 minFreq, uint32 maxFreq, uint32 interval, uint16 options)
    {
        //verify rf sweep mode is supported
        if(!features().supportsCustomRfSweepMode())
        {
            throw Error_NotSupported("Custom RF Sweep Mode is not supported by this BaseStation.");
        }

        return protocol(communicationProtocol()).m_startRfSweep(this, minFreq, maxFreq, interval, options);
    }

    uint16 BaseStation_Impl::timeoutToAdd()
    {
        switch(m_connection.type())
        {
            case Connection::connectionType_tcp:
            case Connection::connectionType_webSocket:
                return 250;

            default:
                return 75;
        }
    }

    bool BaseStation_Impl::doBaseCommand(const ByteStream& command, WirelessResponsePattern& response, uint64 minTimeout)
    {
        //write the command
        m_connection.write(command);

        //wait for the response
        response.wait(std::max(m_baseCommandsTimeout, minTimeout));

        return response.success();
    }

    bool BaseStation_Impl::doNodeCommand(NodeAddress nodeAddress, const ByteStream& command, WirelessResponsePattern& response, uint64 minTimeout)
    {
        //write the command
        m_connection.write(command);

        //wait for the response
        response.wait(std::max(m_nodeCommandsTimeout, minTimeout));

        if(response.baseReceived() && !response.fullyMatched())
        {
            //base received the command and sent to node, wait for the new timeout for the Node's response
            response.wait(std::max(response.baseReceivedWaitTime() + timeoutToAdd(), minTimeout));
        }

        if(response.success())
        {
            //update node last comm time
            NodeCommTimes::updateCommTime(nodeAddress);

            //update the device state to idle
            //Note: this isn't always true, as the command that was just sent could have put the node to sleep or started
            //      it sampling, but those commands will update the device state separately immediately after this function
            NodeCommTimes::updateDeviceState(nodeAddress, DeviceState::deviceState_idle);

            return true;
        }

        return false;
    }

    bool BaseStation_Impl::protocol_ping_v1()
    {
        //create the response for the BaseStation_Ping command
        BaseStation_Ping::Response response(m_responseCollector);

        ByteStream command = BaseStation_Ping::buildCommand();

        return doBaseCommand(command, response);
    }

    bool BaseStation_Impl::protocol_ping_v2(WirelessPacket::AsppVersion asppVer)
    {
        //create the response for the BaseStation_Ping command
        BaseStation_Ping_v2::Response response(m_responseCollector);

        ByteStream command = BaseStation_Ping_v2::buildCommand(asppVer);

        return doBaseCommand(command, response);
    }

    void BaseStation_Impl::protocol_hardReset_v2()
    {
        BaseStation_Reset_v2::Response response(BaseStation_Reset_v2::resetType_hard, m_responseCollector);

        ByteStream command = BaseStation_Reset_v2::buildCommand(BaseStation_Reset_v2::resetType_hard);

        if(!doBaseCommand(command, response))
        {
            throw Error_Communication("Failed to reset the BaseStation");
        }
    }

    void BaseStation_Impl::protocol_softReset_v2()
    {
        BaseStation_Reset_v2::Response response(BaseStation_Reset_v2::resetType_soft, m_responseCollector);

        ByteStream command = BaseStation_Reset_v2::buildCommand(BaseStation_Reset_v2::resetType_soft);

        if(!doBaseCommand(command, response))
        {
            throw Error_Communication("Failed to reset the BaseStation");
        }
    }

    bool BaseStation_Impl::protocol_read_v1(uint16 eepromAddress, uint16& result)
    {
        //create the response for the BaseStation_ReadEeprom command
        BaseStation_ReadEeprom::Response response(m_responseCollector);

        ByteStream command = BaseStation_ReadEeprom::buildCommand(eepromAddress);

        if(doBaseCommand(command, response))
        {
            //get the eeprom value that we read
            result = response.result();

            return true;
        }

        return false;
    }

    bool BaseStation_Impl::protocol_read_v2(WirelessPacket::AsppVersion asppVer, uint16 eepromAddress, uint16& result)
    {
        //create the response for the BaseStation_ReadEeprom command
        BaseStation_ReadEeprom_v2::Response response(eepromAddress, m_responseCollector);

        ByteStream command = BaseStation_ReadEeprom_v2::buildCommand(asppVer, eepromAddress);
        if(doBaseCommand(command, response))
        {
            //get the eeprom value that we read
            result = response.result();

            return true;
        }

        //throw an exception if we need to
        WirelessPacket::throwEepromResponseError(response.errorCode(), eepromAddress);
        return false;
    }

    bool BaseStation_Impl::protocol_write_v1(uint16 eepromAddress, uint16 value)
    {
        //create the response for the BaseStation_WriteEeprom command
        BaseStation_WriteEeprom::Response response(value, m_responseCollector);

        ByteStream command = BaseStation_WriteEeprom::buildCommand(eepromAddress, value);

        return doBaseCommand(command, response);
    }

    bool BaseStation_Impl::protocol_write_v2(WirelessPacket::AsppVersion asppVer, uint16 eepromAddress, uint16 value)
    {
        //create the response for the BaseStation_WriteEeprom command
        BaseStation_WriteEeprom_v2::Response response(value, eepromAddress, m_responseCollector);

        ByteStream command = BaseStation_WriteEeprom_v2::buildCommand(asppVer, eepromAddress, value);
        if(!doBaseCommand(command, response))
        {
            //throw an exception if we need to
            WirelessPacket::throwEepromResponseError(response.errorCode(), eepromAddress);
            return false;
        }

        return true;
    }

    Timestamp BaseStation_Impl::protocol_enableBeacon_v1(uint32 utcTime)
    {
        static const uint64 MIN_TIMEOUT = 1100;

        //create the response for the BaseStation_SetBeacon command
        BaseStation_SetBeacon::Response response(utcTime, m_responseCollector);

        ByteStream command = BaseStation_SetBeacon::buildCommand(utcTime);

        if(doBaseCommand(command, response, MIN_TIMEOUT))
        {
            return response.beaconStartTime();
        }

        //throw an exception so that the user cannot ignore a failure
        throw Error_Communication("The Enable Beacon command has failed");
    }

    Timestamp BaseStation_Impl::protocol_enableBeacon_v2(WirelessPacket::AsppVersion asppVer, uint32 utcTime)
    {
        static const uint64 MIN_TIMEOUT = 1100;

        //create the response for the BaseStation_SetBeacon command
        BaseStation_SetBeacon_v2::Response response(utcTime, m_responseCollector);

        ByteStream command = BaseStation_SetBeacon_v2::buildCommand(asppVer, utcTime);
        if(doBaseCommand(command, response, MIN_TIMEOUT))
        {
            return response.beaconStartTime();
        }

        //throw an exception so that the user cannot ignore a failure
        throw Error_Communication("The Enable Beacon command has failed");
    }

    BeaconStatus BaseStation_Impl::protocol_beaconStatus_v1(WirelessPacket::AsppVersion asppVer)
    {
        //create the response for the command
        BaseStation_BeaconStatus::Response response(m_responseCollector);

        ByteStream command = BaseStation_BeaconStatus::buildCommand(asppVer);
        if(doBaseCommand(command, response))
        {
            //return the result of the response
            return response.result();
        }

        //throw an exception so that the user cannot ignore a failure
        throw Error_Communication("The Beacon Status command has failed");
    }

    void BaseStation_Impl::protocol_startRfSweepMode_v1(WirelessPacket::AsppVersion asppVersion, uint32 minFreq, uint32 maxFreq, uint32 interval, uint16 options)
    {
        //create the response for the BaseStation_Ping command
        BaseStation_RfSweepStart::Response response(m_responseCollector, minFreq, maxFreq, interval, options);

        ByteStream command = BaseStation_RfSweepStart::buildCommand(asppVersion, minFreq, maxFreq, interval, options);
        if(!doBaseCommand(command, response))
        {
            //throw an exception so that the user cannot ignore a failure
            throw Error_Communication("Failed to start RF Sweep Mode.");
        }
    }

    bool BaseStation_Impl::protocol_node_pageDownload_v1(NodeAddress nodeAddress, uint16 pageIndex, ByteStream& data)
    {
        //create the response for the PageDownload command
        PageDownload::Response response(m_responseCollector);

        ByteStream command = PageDownload::buildCommand(nodeAddress, pageIndex);

        if(doNodeCommand(nodeAddress, command, response))
        {
            //get the data points and store them in the data parameter
            data = response.dataPoints();
            return true;
        }

        return false;
    }

    bool BaseStation_Impl::protocol_node_datalogInfo_v1(WirelessPacket::AsppVersion asppVer, NodeAddress nodeAddress, DatalogSessionInfoResult& result)
    {
        static const uint64 MIN_TIMEOUT = 200;

        //create the response for the command
        GetDatalogSessionInfo::Response response(nodeAddress, m_responseCollector);

        ByteStream command = GetDatalogSessionInfo::buildCommand(asppVer, nodeAddress);

        if(doNodeCommand(nodeAddress, command, response, MIN_TIMEOUT))
        {
            result = response.result();
            return true;
        }

        return false;
    }

    bool BaseStation_Impl::protocol_node_getDatalogData_v1(WirelessPacket::AsppVersion asppVer, NodeAddress nodeAddress, uint32 flashAddress, ByteStream& data, uint16& numBytesDownloaded)
    {
        numBytesDownloaded = 0;

        //create the response for the command
        GetLoggedData::Response response(nodeAddress, flashAddress, m_responseCollector);

        ByteStream command = GetLoggedData::buildCommand(asppVer, nodeAddress, flashAddress);

        if(doNodeCommand(nodeAddress, command, response))
        {
            numBytesDownloaded = static_cast<uint16>(response.data().size());

            //append the bytes we read to the passed in ByteStream
            data.appendByteStream(response.data());

            return true;
        }

        return false;
    }

    PingResponse BaseStation_Impl::protocol_node_longPing_v1(WirelessPacket::AsppVersion asppVer, NodeAddress nodeAddress)
    {
        //create the response for the LongPing command with the node address
        LongPing::Response response(nodeAddress, m_responseCollector);

        ByteStream command = LongPing::buildCommand(asppVer, nodeAddress);

        doNodeCommand(nodeAddress, command, response);

        //return the result of the response
        return response.result();
    }

    void BaseStation_Impl::protocol_node_hardReset_v2(NodeAddress nodeAddress)
    {
        Reset_v2::Response response(nodeAddress, Reset_v2::resetType_hard, m_responseCollector);

        ByteStream command = Reset_v2::buildCommand(nodeAddress, Reset_v2::resetType_hard);

        if(!doNodeCommand(nodeAddress, command, response))
        {
            throw Error_NodeCommunication(nodeAddress, "Failed to reset the Node");
        }
    }

    void BaseStation_Impl::protocol_node_softReset_v2(NodeAddress nodeAddress)
    {
        Reset_v2::Response response(nodeAddress, Reset_v2::resetType_soft, m_responseCollector);

        ByteStream command = Reset_v2::buildCommand(nodeAddress, Reset_v2::resetType_soft);

        if(!doNodeCommand(nodeAddress, command, response))
        {
            throw Error_NodeCommunication(nodeAddress, "Failed to reset the Node");
        }
    }

    bool BaseStation_Impl::protocol_node_sleep_v1(NodeAddress nodeAddress)
    {
        ByteStream command = Sleep::buildCommand(nodeAddress);

        //send the sleep command to the base station
        m_connection.write(command);

        //we don't have a success packet for this command
        return true;
    }

    bool BaseStation_Impl::protocol_node_sleep_v2(WirelessPacket::AsppVersion asppVer, NodeAddress nodeAddress)
    {
        ByteStream command = Sleep_v2::buildCommand(asppVer, nodeAddress);

        Sleep_v2::Response response(nodeAddress, m_responseCollector);

        return doNodeCommand(nodeAddress, command, response);
    }

    SetToIdleStatus BaseStation_Impl::protocol_node_setToIdle_v1(NodeAddress nodeAddress, const BaseStation& base)
    {
        //attempt to ping the Base Station before starting set to idle
        bool pingSuccess = false;
        static const uint8 MAX_RETRIES = 5;
        uint8 retries = 0;
        do
        {
            pingSuccess = ping();
            retries++;
        }
        while(!pingSuccess && retries < MAX_RETRIES);

        if(!pingSuccess)
        {
            throw Error_Communication("Failed to communicate with the Base Station.");
        }

        //create the response for the Set to Idle command
        std::shared_ptr<SetToIdle::Response> response(std::make_shared<SetToIdle::Response>(nodeAddress, m_responseCollector, base));

        //build the set to idle command to send
        ByteStream setToIdleCmd = SetToIdle::buildCommand(nodeAddress);

        //send the command to the base station
        m_connection.write(setToIdleCmd);

        //build the status to return to the user
        SetToIdleStatus status(response);

        return status;
    }

    SetToIdleStatus BaseStation_Impl::protocol_node_setToIdle_v2(WirelessPacket::AsppVersion asppVer, NodeAddress nodeAddress, const BaseStation& base)
    {
        //attempt to ping the Base Station before starting set to idle
        bool pingSuccess = false;
        static const uint8 MAX_RETRIES = 5;
        uint8 retries = 0;
        do
        {
            pingSuccess = ping();
            retries++;
        }
        while(!pingSuccess && retries < MAX_RETRIES);

        if(!pingSuccess)
        {
            throw Error_Communication("Failed to communicate with the Base Station.");
        }

        //create the response for the Set to Idle command
        std::shared_ptr<SetToIdle_v2::Response> response(std::make_shared<SetToIdle_v2::Response>(nodeAddress, m_responseCollector, base));

        //build the set to idle command to send
        ByteStream setToIdleCmd;

        switch(asppVer)
        {
            case WirelessPacket::aspp_v3:
                setToIdleCmd = SetToIdle_v2::buildCommand_aspp3(nodeAddress);
                break;

            default:
                setToIdleCmd = SetToIdle_v2::buildCommand(nodeAddress);
                break;
        }

        //send the command to the base station
        m_connection.write(setToIdleCmd);

        //wait for the initial response or timeout
        response->wait(m_baseCommandsTimeout);

        if(!response->started())
        {
            throw Error_Communication("Failed to start the Set to Idle process.");
        }

        //build the status to return to the user
        SetToIdleStatus status(response);

        return status;
    }

    bool BaseStation_Impl::protocol_node_readEeprom_v1(NodeAddress nodeAddress, uint16 eepromAddress, uint16& eepromValue)
    {
        //create the response for the ReadEeprom command
        ReadEeprom::Response response(nodeAddress, m_responseCollector);

        //build the command to send
        ByteStream readCommand = ReadEeprom::buildCommand(nodeAddress, eepromAddress);

        if(doNodeCommand(nodeAddress, readCommand, response))
        {
            //set the eeprom value to the result
            eepromValue = response.eepromValue();
            return true;
        }

        return false;
    }

    bool BaseStation_Impl::protocol_node_readEeprom_v2(WirelessPacket::AsppVersion asppVer, NodeAddress nodeAddress, uint16 eepromAddress, uint16& eepromValue)
    {
        //create the response for the ReadEeprom command
        ReadEeprom_v2::Response response(nodeAddress, eepromAddress, m_responseCollector);

        //build the command to send
        ByteStream readCommand = ReadEeprom_v2::buildCommand(asppVer, nodeAddress, eepromAddress);

        if(doNodeCommand(nodeAddress, readCommand, response))
        {
            //set the eeprom value to the result
            eepromValue = response.eepromValue();
            return true;
        }

        //throw an exception if we need to
        WirelessPacket::throwEepromResponseError(response.errorCode(), eepromAddress);
        return false;
    }

    bool BaseStation_Impl::protocol_node_writeEeprom_v1(NodeAddress nodeAddress, uint16 eepromAddress, uint16 value)
    {
        //create the response for the WriteEeprom command
        WriteEeprom::Response response(nodeAddress, m_responseCollector);

        //build the command to send
        ByteStream writeCommand = WriteEeprom::buildCommand(nodeAddress, eepromAddress, value);

        return doNodeCommand(nodeAddress, writeCommand, response);
    }

    bool BaseStation_Impl::protocol_node_writeEeprom_v2(WirelessPacket::AsppVersion asppVer, NodeAddress nodeAddress, uint16 eepromAddress, uint16 value)
    {
        //create the response for the WriteEeprom_v2 command
        WriteEeprom_v2::Response response(nodeAddress, eepromAddress, value, m_responseCollector);

        //build the command to send
        ByteStream writeCommand = WriteEeprom_v2::buildCommand(asppVer, nodeAddress, eepromAddress, value);

        if(!doNodeCommand(nodeAddress, writeCommand, response))
        {
            //throw an exception if we need to
            WirelessPacket::throwEepromResponseError(response.errorCode(), eepromAddress);
            return false;
        }

        return true;
    }

    bool BaseStation_Impl::protocol_node_autoBalance_v1(NodeAddress nodeAddress, uint8 channelNumber, float targetPercent, AutoBalanceResult& result)
    {
        //determine the target value to send to the autobalance command (max bits is always 4096 for this command)
        uint16 targetVal = static_cast<uint16>(4096 * targetPercent / 100.0f);

        //build the command to send
        ByteStream command = AutoBalance::buildCommand(nodeAddress, channelNumber, targetVal);

        //send the command to the base station
        m_connection.write(command);

        //this command doesn't have a response (no info), so set the error code to legacy
        result.m_errorCode = WirelessTypes::autobalance_legacyNone;

        //don't know the actual status, have to assume success
        return true;
    }

    bool BaseStation_Impl::protocol_node_autoBalance_v2(WirelessPacket::AsppVersion asppVer, NodeAddress nodeAddress, uint8 channelNumber, float targetPercent, AutoBalanceResult& result)
    {
        static const uint64 MIN_TIMEOUT = 1100;

        //create the response for the AutoBalance_v2 command
        AutoBalance_v2::Response response(nodeAddress, channelNumber, targetPercent, m_responseCollector);

        //build the command to send
        ByteStream command = AutoBalance_v2::buildCommand(asppVer, nodeAddress, channelNumber, targetPercent);

        bool success = doNodeCommand(nodeAddress, command, response, MIN_TIMEOUT);

        result = response.result();

        return success;
    }

    bool BaseStation_Impl::protocol_node_autocal_shm_v1(WirelessPacket::AsppVersion asppVer, NodeAddress nodeAddress, AutoCalResult& result)
    {
        //create the response
        AutoCal::ShmResponse response(nodeAddress, m_responseCollector);

        ByteStream cmd = AutoCal::buildCommand_shmLink(asppVer, nodeAddress);

        return node_autocal(nodeAddress, cmd, response, result);
    }

    bool BaseStation_Impl::protocol_node_autocal_shm201_v1(WirelessPacket::AsppVersion asppVer, NodeAddress nodeAddress, AutoCalResult& result)
    {
        //create the response
        AutoCal::Shm201Response response(nodeAddress, m_responseCollector);

        ByteStream cmd = AutoCal::buildCommand_shmLink201(asppVer, nodeAddress);

        return node_autocal(nodeAddress, cmd, response, result);
    }

    bool BaseStation_Impl::protocol_node_autoshuntcal_v1(WirelessPacket::AsppVersion asppVer, NodeAddress nodeAddress, const AutoCalCmdDetails& commandDetails, AutoCalResult& result)
    {
        //create the response
        AutoCal::ShuntCalResponse response(nodeAddress, m_responseCollector, commandDetails.chNum);

        ByteStream cmd = AutoCal::buildCommand_shuntCal(asppVer, nodeAddress, commandDetails);

        return node_autocal(nodeAddress, cmd, response, result);
    }

    bool BaseStation_Impl::protocol_node_getDiagnosticInfo_v1(WirelessPacket::AsppVersion asppVer, NodeAddress nodeAddress, ChannelData& result)
    {
        //create the response
        GetDiagnosticInfo::Response response(nodeAddress, m_responseCollector);

        ByteStream command = GetDiagnosticInfo::buildCommand(asppVer, nodeAddress);

        if(doNodeCommand(nodeAddress, command, response))
        {
            result = response.result();
            return true;
        }

        return false;
    }

    bool BaseStation_Impl::protocol_node_erase_v1(NodeAddress nodeAddress)
    {
        //create the response for the Erase command
        Erase::Response response(m_responseCollector);

        ByteStream command = Erase::buildCommand(nodeAddress);

        return doNodeCommand(nodeAddress, command, response);
    }

    bool BaseStation_Impl::protocol_node_erase_v2(WirelessPacket::AsppVersion asppVer, NodeAddress nodeAddress)
    {
        //create the response for the Erase command
        Erase_v2::Response response(nodeAddress, m_responseCollector);

        ByteStream command = Erase_v2::buildCommand(asppVer, nodeAddress);

        return doNodeCommand(nodeAddress, command, response);
    }

    bool BaseStation_Impl::protocol_node_startSync_v1(WirelessPacket::AsppVersion asppVer, NodeAddress nodeAddress)
    {
        //create the response for the StartSyncSampling command
        StartSyncSampling::Response response(nodeAddress, m_responseCollector);

        //build the command to send
        ByteStream command = StartSyncSampling::buildCommand(asppVer, nodeAddress);

        return doNodeCommand(nodeAddress, command, response);
    }

    bool BaseStation_Impl::protocol_node_startNonSync_v1(NodeAddress nodeAddress)
    {
        //build the command to send
        ByteStream command = StartNonSyncSampling::buildCommand(nodeAddress);

        //send the command to the base station
        m_connection.write(command);

        //no response for this command

        //send the command a few extra times for good measure
        Utils::threadSleep(50);
        m_connection.write(command);

        Utils::threadSleep(50);
        m_connection.write(command);

        return true;
    }

    bool BaseStation_Impl::protocol_node_startNonSync_v2(WirelessPacket::AsppVersion asppVer, NodeAddress nodeAddress)
    {
        //create the response for the command
        StartNonSyncSampling_v2::Response response(nodeAddress, m_responseCollector);

        //build the command to send
        ByteStream command = StartNonSyncSampling_v2::buildCommand(asppVer, nodeAddress);

        return doNodeCommand(nodeAddress, command, response);
    }

    bool BaseStation_Impl::protocol_node_batchEepromRead_v1(NodeAddress nodeAddress, uint16 startEeprom, std::map<uint16, uint16>& result)
    {
        BatchEepromRead::Response response(nodeAddress, m_responseCollector);

        ByteStream command = BatchEepromRead::buildCommand(nodeAddress, startEeprom);

        if(doNodeCommand(nodeAddress, command, response))
        {
            //get the data points and store them in the data parameter
            result = response.eepromMap();
            return true;
        }

        return false;
    }

    bool BaseStation_Impl::protocol_node_testCommProtocol(WirelessPacket::AsppVersion asppVer, NodeAddress nodeAddress, WirelessTypes::CommProtocol protocol)
    {
        TestNodeCommProtocol::Response response(nodeAddress, protocol, m_responseCollector);

        ByteStream command = TestNodeCommProtocol::buildCommand(asppVer, nodeAddress, protocol);

        return doNodeCommand(nodeAddress, command, response);
    }

    bool BaseStation_Impl::protocol_node_poll(WirelessPacket::AsppVersion asppVer, NodeAddress nodeAddress, const ChannelMask& chs, WirelessPollData& result)
    {
        Poll::Response response(nodeAddress, m_responseCollector);

        ByteStream command = Poll::buildCommand(asppVer, nodeAddress, chs);

        //send the command
        m_connection.write(command);

        //wait for the response or timeout
        response.wait(m_nodeCommandsTimeout);

        if(response.baseReceived() && !response.fullyMatched())
        {
            //base received the command and sent to node, wait for the new timeout for the Node's response
            response.wait(response.baseReceivedWaitTime() + timeoutToAdd());
        }

        //if the poll process has started, but not completed
        if(response.started() && !response.fullyMatched())
        {
            //update last comm times
            NodeCommTimes::updateCommTime(nodeAddress);

            //the Node tells us how much time it takes to complete, so ask for that and
            //convert the seconds to milliseconds, and add some extra buffer time
            uint64 timeToWait = static_cast<uint64>(response.timeToComplete() * 1000.0) + 500;

            response.wait(timeToWait);
        }

        //if the poll process has finished
        if(response.fullyMatched())
        {
            //update last comm times
            NodeCommTimes::updateCommTime(nodeAddress);

            //give the response data to the result object
            result = response.result();
        }

        return response.success();
    }

    Value BaseStation_Impl::readEeprom(const EepromLocation& location) const
    {
        try
        {
            return m_eeprom->readEeprom(location);
        }
        catch(Error_Communication&)
        {
            throw Error_Communication("Failed to read the " + location.description() + " from the BaseStation");
        }
        catch(Error_NotSupported&)
        {
            throw Error_NotSupported("The BaseStation does not support reading the " + location.description());
        }
    }

    void BaseStation_Impl::writeEeprom(const EepromLocation& location, const Value& val)
    {
        try
        {
            m_eeprom->writeEeprom(location, val);
        }
        catch(Error_Communication&)
        {
            throw Error_Communication("Failed to write the " + location.description() + " to the BaseStation");
        }
        catch(Error_NotSupported&)
        {
            throw Error_NotSupported("The BaseStation does not support writing the " + location.description());
        }
    }

    uint16 BaseStation_Impl::readEeprom(uint16 eepromAddress) const
    {
        return m_eeprom->readEeprom(eepromAddress);
    }

    void BaseStation_Impl::writeEeprom(uint16 eepromAddress, uint16 value)
    {
        m_eeprom->writeEeprom(eepromAddress, value);
    }

    void BaseStation_Impl::cyclePower(bool checkComm)
    {
        if(protocol(communicationProtocol()).supportsBaseHardReset())
        {
            protocol(communicationProtocol()).m_hardBaseReset(this);
        }
        else
        {
            static const uint16 RESET_BASE = 0x01;

            //store the original timeout that is currently set
            uint64 originalTimeout = timeout();
            uint8 originalRetries = getReadWriteRetries();

            //when this goes out of scope, it will write back the original timeout (need cast for overloaded ambiguity)
            ScopeHelper writebackTimeout(std::bind(static_cast<void(BaseStation_Impl::*)(uint64)>(&BaseStation_Impl::timeout), this, originalTimeout));

            //when this goes out of scope, it will write back the original retries
            ScopeHelper writebackRetries(std::bind(&BaseStation_Impl::setReadWriteRetries, this, originalRetries));

            try
            {
                //this command doesn't have a response, change to a quick timeout and no retries
                timeout(0);
                setReadWriteRetries(0);

                //write a 0x01 to the CYCLE_POWER eeprom location on the base station
                writeEeprom(BaseStationEepromMap::CYCLE_POWER, Value::UINT16(RESET_BASE));
            }
            catch(Error_Communication&)
            {
                //an exception will be thrown due to no response, continue on
            }

            //change the original timeout/retries back (and cancel the scope helpers)
            timeout(originalTimeout);
            writebackTimeout.cancel();
            setReadWriteRetries(originalRetries);
            writebackRetries.cancel();
        }

        if(checkComm)
        {
            Utils::threadSleep(100);

            //attempt to ping the base a few times to see if its back online
            bool pingSuccess = false;
            uint8 retries = 0;
            while(!pingSuccess && retries <= 5)
            {
                pingSuccess = ping();
                retries++;
            }
        }
    }

    void BaseStation_Impl::resetRadio()
    {
        if(protocol(communicationProtocol()).supportsBaseSoftReset())
        {
            protocol(communicationProtocol()).m_softBaseReset(this);
        }
        else
        {
            static const uint16 RESET_RADIO = 0x02;

            //write a 0x02 to the CYCLE_POWER eeprom location on the base station
            writeEeprom(BaseStationEepromMap::CYCLE_POWER, Value::UINT16(RESET_RADIO));
        }

        Utils::threadSleep(100);
    }

    void BaseStation_Impl::changeFrequency(WirelessTypes::Frequency frequency)
    {
        //make sure the frequency is within the correct range, change if not
        Utils::checkBounds_min(frequency, WirelessTypes::freq_11);
        Utils::checkBounds_max(frequency, WirelessTypes::freq_26);

        //write the new frequency value to the base station
        writeEeprom(BaseStationEepromMap::FREQUENCY, Value::UINT16(static_cast<uint16>(frequency)));

        //reset the radio on the base station to commit the change
        resetRadio();

        //update the cached frequency
        m_frequency = frequency;
    }

    bool BaseStation_Impl::verifyConfig(const BaseStationConfig& config, ConfigIssues& outIssues) const
    {
        return config.verify(features(), eeHelper(), outIssues);
    }

    void BaseStation_Impl::applyConfig(const BaseStationConfig& config)
    {
        //reset the hasWritten flag so that we can tell if
        //eeproms were actually changed (and not ignored due to the cache).
        m_eeprom->resetHasWritten();

        config.apply(features(), eeHelper());

        //if an actual eeprom has been written
        if(m_eeprom->didWrite())
        {
            uint8 retries = 0;
            bool success = false;
            while(!success && retries <= 3)
            {
                try
                {
                    //if we can just reset the radio to commit the changes
                    if(features().supportsEepromCommitViaRadioReset())
                    {
                        resetRadio();
                        success = true;
                    }
                    else
                    {
                        cyclePower();
                        success = true;
                    }
                }
                catch(Error_Communication&)
                {
                    retries++;
                }
            }
        }
    }

    WirelessTypes::TransmitPower BaseStation_Impl::getTransmitPower() const
    {
        return m_eepromHelper->read_transmitPower();
    }

    BaseStationButton BaseStation_Impl::getButtonLongPress(uint8 buttonNumber) const
    {
        return m_eepromHelper->read_button(buttonNumber, BaseStationButton::action_longPress);
    }

    BaseStationButton BaseStation_Impl::getButtonShortPress(uint8 buttonNumber) const
    {
        return m_eepromHelper->read_button(buttonNumber, BaseStationButton::action_shortPress);
    }

    bool BaseStation_Impl::getAnalogPairingEnabled() const
    {
        return m_eepromHelper->read_analogPairingEnabled();
    }

    uint16 BaseStation_Impl::getAnalogTimeoutTime() const
    {
        return m_eepromHelper->read_analogTimeoutTime();
    }

    float BaseStation_Impl::getAnalogTimeoutVoltage() const
    {
        return m_eepromHelper->read_analogTimeoutVoltage();
    }

    bool BaseStation_Impl::getAnalogExceedanceEnabled() const
    {
        return m_eepromHelper->read_analogExceedanceEnabled();
    }

    BaseStationAnalogPair BaseStation_Impl::getAnalogPair(uint8 portNumber) const
    {
        return m_eepromHelper->read_analogPair(portNumber);
    }

    //================================================================================================
    //                                        NODE COMMANDS
    //================================================================================================

    PingResponse BaseStation_Impl::node_ping(const WirelessProtocol& nodeProtocol, NodeAddress nodeAddress)
    {
        return nodeProtocol.m_longPing(this, nodeAddress);
    }

    void BaseStation_Impl::node_hardReset(const WirelessProtocol& nodeProtocol, NodeAddress nodeAddress)
    {
        nodeProtocol.m_hardReset(this, nodeAddress);
    }

    void BaseStation_Impl::node_softReset(const WirelessProtocol& nodeProtocol, NodeAddress nodeAddress)
    {
        nodeProtocol.m_softReset(this, nodeAddress);
    }

    bool BaseStation_Impl::node_sleep(const WirelessProtocol& nodeProtocol, NodeAddress nodeAddress)
    {
        //make sure we have good node communication by attempting to ping the node
        if(!node_ping(nodeProtocol, nodeAddress).success())
        {
            //don't attempt a sleep command
            return false;
        }

        if(nodeProtocol.m_sleep(this, nodeAddress))
        {
            NodeCommTimes::updateDeviceState(nodeAddress, DeviceState::deviceState_sleep);
            return true;
        }

        return false;
    }

    SetToIdleStatus BaseStation_Impl::node_setToIdle(NodeAddress nodeAddress, const BaseStation& base)
    {
        //this just depends on the protocol of the Base Station, not the Node
        return protocol(communicationProtocol()).m_setToIdle(this, nodeAddress, base);
    }

    bool BaseStation_Impl::node_readEeprom(const WirelessProtocol& nodeProtocol, NodeAddress nodeAddress, uint16 eepromAddress, uint16& eepromValue)
    {
        return nodeProtocol.m_readNodeEeprom(this, nodeAddress, eepromAddress, eepromValue);
    }

    bool BaseStation_Impl::node_writeEeprom(const WirelessProtocol& nodeProtocol, NodeAddress nodeAddress, uint16 eepromAddress, uint16 value)
    {
        return nodeProtocol.m_writeNodeEeprom(this, nodeAddress, eepromAddress, value);
    }

    bool BaseStation_Impl::node_pageDownload(const WirelessProtocol& nodeProtocol, NodeAddress nodeAddress, uint16 pageIndex, ByteStream& data)
    {
        return nodeProtocol.m_pageDownload(this, nodeAddress, pageIndex, data);
    }

    bool BaseStation_Impl::node_batchEepromRead(const WirelessProtocol& nodeProtocol, NodeAddress nodeAddress, uint16 startEeprom, std::map<uint16, uint16>& result)
    {
        return nodeProtocol.m_batchEepromRead(this, nodeAddress, startEeprom, result);
    }

    bool BaseStation_Impl::node_getDatalogSessionInfo(const WirelessProtocol& nodeProtocol, NodeAddress nodeAddress, DatalogSessionInfoResult& result)
    {
        return nodeProtocol.m_datalogSessionInfo(this, nodeAddress, result);
    }

    bool BaseStation_Impl::node_getDatalogData(const WirelessProtocol& nodeProtocol, NodeAddress nodeAddress, uint32 flashAddress, ByteStream& result, uint16& numBytesRead)
    {
        return nodeProtocol.m_getDatalogData(this, nodeAddress, flashAddress, result, numBytesRead);
    }

    bool BaseStation_Impl::node_erase(const WirelessProtocol& nodeProtocol, NodeAddress nodeAddress)
    {
        return nodeProtocol.m_erase(this, nodeAddress);
    }

    bool BaseStation_Impl::node_startSyncSampling(const WirelessProtocol& nodeProtocol, NodeAddress nodeAddress)
    {
        return nodeProtocol.m_startSyncSampling(this, nodeAddress);
    }

    bool BaseStation_Impl::node_startNonSyncSampling(const WirelessProtocol& nodeProtocol, NodeAddress nodeAddress)
    {
        return nodeProtocol.m_startNonSyncSampling(this, nodeAddress);
    }

    bool BaseStation_Impl::node_armForDatalogging(NodeAddress nodeAddress, const std::string& message)
    {
        //arm for datalogging only has 1 version (doesn't need to check protocol)

        //create the response for the ArmForDatalogging command
        ArmForDatalogging::Response response(nodeAddress, m_responseCollector);

        //build the command to send
        ByteStream command = ArmForDatalogging::buildCommand(nodeAddress, message);

        //send the command to the base station
        m_connection.write(command);

        //wait for the response
        response.wait(m_nodeCommandsTimeout);

        if(response.baseReceived() && !response.fullyMatched())
        {
            //base received the command and sent to node, wait for the new timeout for the Node's response
            response.wait(response.baseReceivedWaitTime() + timeoutToAdd());
        }

        if(response.success())
        {
            //update node last comm time
            NodeCommTimes::updateCommTime(nodeAddress);
        }

        //return the result of the response
        return response.success();
    }

    void BaseStation_Impl::node_triggerArmedDatalogging(NodeAddress nodeAddress)
    {
        //trigger armed datalogging only has 1 version (doesn't need to check protocol)

        //build the command to send
        ByteStream command = TriggerArmedDatalogging::buildCommand(nodeAddress);

        //send the command to the base station
        m_connection.write(command);

        //no response for this command
    }

    bool BaseStation_Impl::node_autoBalance(const WirelessProtocol& nodeProtocol, NodeAddress nodeAddress, uint8 channelNumber, float targetPercent, AutoBalanceResult& result)
    {
        return nodeProtocol.m_autoBalance(this, nodeAddress, channelNumber, targetPercent, result);
    }

    bool BaseStation_Impl::node_autocal_shm(const WirelessProtocol& nodeProtocol, NodeAddress nodeAddress, AutoCalResult& result)
    {
        return nodeProtocol.m_autoCal_shm(this, nodeAddress, result);
    }

    bool BaseStation_Impl::node_autocal_shm201(const WirelessProtocol& nodeProtocol, NodeAddress nodeAddress, AutoCalResult& result)
    {
        return nodeProtocol.m_autoCal_shm201(this, nodeAddress, result);
    }

    bool BaseStation_Impl::node_autoShuntCal(const WirelessProtocol& nodeProtocol,
                                             const AutoCalCmdDetails& commandDetails,
                                             AutoCalResult& result)
    {
        return nodeProtocol.m_autoShuntCal(this, commandDetails.nodeAddress, commandDetails, result);
    }

    bool BaseStation_Impl::node_readSingleSensor(NodeAddress nodeAddress, uint8 channelNumber, uint16& result)
    {
        //read single sensor command only has 1 version (doesn't need to check protocol)

        //create the response for the Erase command
        ReadSingleSensor::Response response(m_responseCollector);

        //send the erase command to the base station
        m_connection.write(ReadSingleSensor::buildCommand(nodeAddress, channelNumber));

        //wait for the response or timeout
        response.wait(m_nodeCommandsTimeout);

        if(response.baseReceived() && !response.fullyMatched())
        {
            //base received the command and sent to node, wait for the new timeout for the Node's response
            response.wait(response.baseReceivedWaitTime() + timeoutToAdd());
        }

        if(response.success())
        {
            result = response.sensorValue();

            //update node last comm time
            NodeCommTimes::updateCommTime(nodeAddress);
        }

        //return the result of the response
        return response.success();
    }

    bool BaseStation_Impl::node_getDiagnosticInfo(const WirelessProtocol& nodeProtocol, NodeAddress nodeAddress, ChannelData& result)
    {
        return nodeProtocol.m_getDiagnosticInfo(this, nodeAddress, result);
    }

    bool BaseStation_Impl::node_testCommProtocol(NodeAddress nodeAddress, WirelessTypes::CommProtocol commProtocol)
    {
        if(!features().supportsCommunicationProtocol(commProtocol))
        {
            throw Error_NotSupported("The Communication Protocol is not supported by this BaseStation.");
        }

        if(!protocol(communicationProtocol()).supportsTestCommProtocol())
        {
            throw Error_NotSupported("The Test Communication Protocol function is not supported by this BaseStation.");
        }

        //this depends on the protocol of the Base Station, not the Node
        return protocol(communicationProtocol()).m_testNodeCommProtocol(this, nodeAddress, commProtocol);
    }

    bool BaseStation_Impl::node_poll(const WirelessProtocol& nodeProtocol, NodeAddress nodeAddress, const ChannelMask& chs, WirelessPollData& result)
    {
        return nodeProtocol.m_poll(this, nodeAddress, chs, result);
    }

    bool BaseStation_Impl::node_autocal(NodeAddress nodeAddress, const ByteStream& command, AutoCal::Response& response, AutoCalResult& result)
    {
        //send the command
        m_connection.write(command);

        //wait for the response or timeout
        response.wait(m_nodeCommandsTimeout);

        if(response.baseReceived() && !response.fullyMatched())
        {
            //base received the command and sent to node, wait for the new timeout for the Node's response
            response.wait(response.baseReceivedWaitTime() + timeoutToAdd());
        }

        //if the autocal process has started, but not completed
        if(response.calStarted() && !response.fullyMatched())
        {
            //update last comm times
            NodeCommTimes::updateCommTime(nodeAddress);

            //the Node tells us how much time it takes to complete, so ask for that and
            //convert the seconds to milliseconds, and add some extra buffer time
            uint64 timeToWait = static_cast<uint64>(response.calTime() * 1000.0) + 500;

            response.wait(timeToWait);
        }

        //if the autocal process has finished
        if(response.fullyMatched())
        {
            //update last comm times
            NodeCommTimes::updateCommTime(nodeAddress);

            //give the response data to the result object
            result.m_completionFlag = response.completionFlag();
            result.parse(response.infoBytes());
        }

        return response.success();
    }
} // namespace mscl
