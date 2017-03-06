/*******************************************************************************
Copyright(c) 2015-2017 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"

#include "BaseStation.h"
#include "BaseStation_Impl.h"
#include "mscl/MicroStrain/ByteStream.h"
#include "mscl/MicroStrain/ResponsePattern.h"
#include "Configuration/BaseStationEepromHelper.h"
#include "Configuration/BaseStationConfig.h"
#include "Features/BaseStationFeatures.h"
#include "Commands/AutoCal.h"
#include "Commands/AutoCalInfo.h"
#include "Commands/GetDatalogSessionInfo.h"

namespace mscl
{
    //Constructor
    BaseStation::BaseStation(Connection& connection, uint64 baseTimeout): //baseTimeout=BASE_COMMANDS_DEFAULT_TIMEOUT
        m_impl(std::make_shared<BaseStation_Impl>(connection, baseTimeout))
    {
    }

    BaseStation::BaseStation(std::shared_ptr<BaseStation_Impl> impl):
        m_impl(impl)
    {
    }

    BaseStationEepromHelper& BaseStation::eepromHelper() const
    {
        return m_impl->eeHelper();
    }

    bool BaseStation::doCommand(ResponsePattern& response, const ByteStream& cmdBytes, uint64 timeout)
    {
        return m_impl->doCommand(response, cmdBytes, timeout);
    }

    bool BaseStation::operator==(const BaseStation& src) const
    {
        return (m_impl == src.m_impl);
    }

    bool BaseStation::operator!=(const BaseStation& src) const
    {
        return (m_impl != src.m_impl);
    }

    std::string BaseStation::deviceName(const std::string& serial)
    {
        //replace any unsupported sensorcloud characters
        std::string sensorcloudFilteredName = "base-" + serial;
        Utils::filterSensorcloudName(sensorcloudFilteredName);

        return sensorcloudFilteredName;
    }

    Connection& BaseStation::connection()
    {
        return m_impl->connection();
    }

    const BaseStationFeatures& BaseStation::features() const
    {
        return m_impl->features();
    }

    const Timestamp& BaseStation::lastCommunicationTime() const
    {
        return m_impl->lastCommunicationTime();
    }

    void BaseStation::useEepromCache(bool useCache)
    { 
        m_impl->useEepromCache(useCache); 
    }

    void BaseStation::readWriteRetries(uint8 numRetries)
    {
        m_impl->setReadWriteRetries(numRetries);
    }

    uint8 BaseStation::readWriteRetries() const
    {
        return m_impl->getReadWriteRetries();
    }

    void BaseStation::clearEepromCache()
    {
        m_impl->clearEepromCache();
    }

    WirelessTypes::Frequency BaseStation::frequency() const
    { 
        return m_impl->frequency(); 
    }

    Version BaseStation::firmwareVersion() const
    {
        return m_impl->firmwareVersion();
    }

    WirelessModels::BaseModel BaseStation::model() const
    {
        return m_impl->model();
    }

    std::string BaseStation::serial() const
    {
        return m_impl->serial();
    }

    std::string BaseStation::name() const
    {
        return deviceName(serial());
    }

    WirelessTypes::MicroControllerType BaseStation::microcontroller() const
    {
        return m_impl->microcontroller();
    }

    WirelessTypes::RegionCode BaseStation::regionCode() const
    {
        return m_impl->regionCode();
    }

    uint32 BaseStation::totalData()
    { 
        return m_impl->totalData(); 
    }

    NodeDiscoveries BaseStation::getNodeDiscoveries()
    { 
        return m_impl->getNodeDiscoveries(); 
    }

    void BaseStation::timeout(uint64 timeout)
    { 
        m_impl->timeout(timeout);
    }

    uint64 BaseStation::timeout() const
    { 
        return m_impl->timeout();
    }

    DataSweeps BaseStation::getData(uint32 timeout, uint32 maxSweeps)
    {
        DataSweeps sweeps;
        m_impl->getData(sweeps, timeout, maxSweeps);
        return sweeps;
    }


    //================================================================================================
    //                                    BASE STATION COMMANDS
    //================================================================================================

    bool BaseStation::ping()                                                            
    { 
        return m_impl->ping(); 
    }

    uint16 BaseStation::readEeprom(uint16 eepromAddress) const
    {
        return m_impl->readEeprom(eepromAddress); 
    }

    void BaseStation::writeEeprom(uint16 eepromAddress, uint16 value)
    { 
        m_impl->writeEeprom(eepromAddress, value);
    }

    Timestamp BaseStation::enableBeacon()
    { 
        return m_impl->enableBeacon();
    }

    Timestamp BaseStation::enableBeacon(uint32 utcTime)
    { 
        return m_impl->enableBeacon(utcTime);
    }

    void BaseStation::disableBeacon()
    { 
        m_impl->disableBeacon();
    }

    BeaconStatus BaseStation::beaconStatus()
    {
        return m_impl->beaconStatus();
    }

    void BaseStation::cyclePower(bool checkComm)
    { 
        m_impl->cyclePower(checkComm);
    }

    void BaseStation::startRfSweepMode()
    {
        m_impl->startRfSweepMode();
    }

    void BaseStation::startRfSweepMode(uint32 minFreq, uint32 maxFreq, uint32 interval, uint16 options)
    {
        m_impl->startRfSweepMode(minFreq, maxFreq, interval, options);
    }

    void BaseStation::resetRadio()
    {
        m_impl->resetRadio();
    }

    void BaseStation::changeFrequency(WirelessTypes::Frequency frequency)
    { 
        m_impl->changeFrequency(frequency);
    }

    SetToIdleStatus BaseStation::broadcastSetToIdle()
    {
        return node_setToIdle(BROADCAST_NODE_ADDRESS);
    }

    bool BaseStation::verifyConfig(const BaseStationConfig& config, ConfigIssues& outIssues) const
    {
        return m_impl->verifyConfig(config, outIssues);
    }

    void BaseStation::applyConfig(const BaseStationConfig& config)
    {
        m_impl->applyConfig(config);
    }

    WirelessTypes::TransmitPower BaseStation::getTransmitPower() const
    {
        return m_impl->getTransmitPower();
    }

    BaseStationButton BaseStation::getButtonLongPress(uint8 buttonNumber) const
    {
        return m_impl->getButtonLongPress(buttonNumber);
    }

    BaseStationButton BaseStation::getButtonShortPress(uint8 buttonNumber) const
    {
        return m_impl->getButtonShortPress(buttonNumber);
    }

    bool BaseStation::getAnalogPairingEnabled() const
    {
        return m_impl->getAnalogPairingEnabled();
    }

    uint16 BaseStation::getAnalogTimeoutTime() const
    {
        return m_impl->getAnalogTimeoutTime();
    }

    float BaseStation::getAnalogTimeoutVoltage() const
    {
        return m_impl->getAnalogTimeoutVoltage();
    }

    bool BaseStation::getAnalogExceedanceEnabled() const
    {
        return m_impl->getAnalogExceedanceEnabled();
    }

    BaseStationAnalogPair BaseStation::getAnalogPair(uint8 portNumber) const
    {
        return m_impl->getAnalogPair(portNumber);
    }

    //================================================================================================
    //                                        NODE COMMANDS
    //================================================================================================
    bool BaseStation::node_shortPing(NodeAddress nodeAddress)
    { 
        return m_impl->node_shortPing(nodeAddress);
    }

    PingResponse BaseStation::node_ping(NodeAddress nodeAddress)
    { 
        return m_impl->node_ping(nodeAddress);
    }

    bool BaseStation::node_sleep(NodeAddress nodeAddress)
    { 
        return m_impl->node_sleep(nodeAddress);
    }

    SetToIdleStatus BaseStation::node_setToIdle(NodeAddress nodeAddress)
    { 
        return m_impl->node_setToIdle(nodeAddress, *this);
    }

    bool BaseStation::node_readEeprom(const WirelessProtocol& protocol, NodeAddress nodeAddress, uint16 eepromAddress, uint16& eepromValue)
    { 
        return m_impl->node_readEeprom(protocol, nodeAddress, eepromAddress, eepromValue);
    }

    bool BaseStation::node_writeEeprom(const WirelessProtocol& protocol, NodeAddress nodeAddress, uint16 eepromAddress, uint16 value)
    { 
        return m_impl->node_writeEeprom(protocol, nodeAddress, eepromAddress, value);
    }

    bool BaseStation::node_pageDownload(const WirelessProtocol& protocol, NodeAddress nodeAddress, uint16 pageIndex, ByteStream& data)
    { 
        return m_impl->node_pageDownload(protocol, nodeAddress, pageIndex, data);
    }

    bool BaseStation::node_getDatalogSessionInfo(const WirelessProtocol& protocol, NodeAddress nodeAddress, DatalogSessionInfoResult& result)
    {
        return m_impl->node_getDatalogSessionInfo(protocol, nodeAddress, result);
    }

    bool BaseStation::node_getDatalogData(const WirelessProtocol& protocol, NodeAddress nodeAddress, uint32 flashAddress, ByteStream& result)
    {
        return m_impl->node_getDatalogData(protocol, nodeAddress, flashAddress, result);
    }

    bool BaseStation::node_erase(const WirelessProtocol& protocol, NodeAddress nodeAddress)
    {
        return m_impl->node_erase(protocol, nodeAddress);
    }

    bool BaseStation::node_startSyncSampling(NodeAddress nodeAddress)
    { 
        return m_impl->node_startSyncSampling(nodeAddress);
    }

    bool BaseStation::node_startNonSyncSampling(const WirelessProtocol& protocol, NodeAddress nodeAddress)
    { 
        return m_impl->node_startNonSyncSampling(protocol, nodeAddress);
    }

    bool BaseStation::node_armForDatalogging(NodeAddress nodeAddress, const std::string& message)
    {
        return m_impl->node_armForDatalogging(nodeAddress, message);
    }

    void BaseStation::node_triggerArmedDatalogging(NodeAddress nodeAddress)
    {
        return m_impl->node_triggerArmedDatalogging(nodeAddress);
    }

    bool BaseStation::node_autoBalance(const WirelessProtocol& protocol, NodeAddress nodeAddress, uint8 channelNumber, float targetPercent, AutoBalanceResult& result)
    {
        return m_impl->node_autoBalance(protocol, nodeAddress, channelNumber, targetPercent, result);
    }

    bool BaseStation::node_autocal_shm(NodeAddress nodeAddress, AutoCalResult& result)
    {
        return m_impl->node_autocal_shm(nodeAddress, result);
    }

    bool BaseStation::node_autoShuntCal(NodeAddress nodeAddress,
                                        const ShuntCalCmdInfo& commandInfo,
                                        uint8 chNum,
                                        WirelessModels::NodeModel nodeType,
                                        WirelessTypes::ChannelType chType,
                                        AutoCalResult& result)
    {
        return m_impl->node_autoShuntCal(nodeAddress, commandInfo, chNum, nodeType, chType, result);
    }

    bool BaseStation::node_readSingleSensor(NodeAddress nodeAddress, uint8 channelNumber, uint16& result)
    {
        return m_impl->node_readSingleSensor(nodeAddress, channelNumber, result);
    }

    bool BaseStation::node_getDiagnosticInfo(NodeAddress nodeAddress, ChannelData& result)
    {
        return m_impl->node_getDiagnosticInfo(nodeAddress, result);
    }
}
