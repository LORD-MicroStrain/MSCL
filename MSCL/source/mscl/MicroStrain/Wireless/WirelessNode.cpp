/*******************************************************************************
Copyright(c) 2015-2020 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"

#include "WirelessNode.h"
#include "MockWirelessNode_Impl.h"
#include "WirelessNode_Impl.h"
#include "BaseStation.h"
#include "mscl/Utils.h"
#include "Features/NodeInfo.h"
#include "Features/NodeFeatures.h"
#include "Configuration/NodeEepromHelper.h"
#include "Configuration/WirelessNodeConfig.h"
#include "Commands/AutoCalInfo.h"

namespace mscl
{
    WirelessNode::WirelessNode(NodeAddress nodeAddress, const BaseStation& basestation):
        m_impl(std::make_shared<WirelessNode_Impl>(nodeAddress, basestation))
    {
    }

    WirelessNode::WirelessNode(std::shared_ptr<WirelessNode_Impl> impl):
        m_impl(impl)
    {
    }

    WirelessNode WirelessNode::Mock(NodeAddress nodeAddress, const BaseStation& basestation, const NodeInfo& info)
    {
        return WirelessNode(std::make_shared<MockWirelessNode_Impl>(nodeAddress, basestation, info));
    }

    WirelessNode WirelessNode::Mock(NodeAddress nodeAddress, const BaseStation& basestation, const NodeInfo& info, const WirelessTypes::EepromMap& initialEepromCache)
    {
        auto nodeImpl = std::make_shared<MockWirelessNode_Impl>(nodeAddress, basestation, info);
        nodeImpl->importEepromCache(initialEepromCache);

        return WirelessNode(nodeImpl);
    }

    void WirelessNode::setImpl(std::shared_ptr<WirelessNode_Impl> impl)
    {
        m_impl = impl;
    }

    NodeEepromHelper& WirelessNode::eepromHelper() const
    {
        return m_impl->eeHelper();
    }

    const WirelessProtocol& WirelessNode::protocol(WirelessTypes::CommProtocol commProtocol) const
    {
        return m_impl->protocol(commProtocol);
    }

    std::string WirelessNode::deviceName(NodeAddress nodeAddress)
    {
        //replace any unsupported sensorcloud characters
        std::string sensorcloudFilteredName = Utils::toStr(nodeAddress);
        Utils::filterSensorcloudName(sensorcloudFilteredName);

        //the name for WirelessNode's is just the node address
        return sensorcloudFilteredName;
    }

    const NodeFeatures& WirelessNode::features() const
    {
        return m_impl->features();
    }

    const Timestamp& WirelessNode::lastCommunicationTime() const
    {
        return m_impl->lastCommunicationTime();
    }

    DeviceState WirelessNode::lastDeviceState() const
    {
        return m_impl->lastDeviceState();
    }

    void WirelessNode::setBaseStation(const BaseStation& basestation)
    {
        m_impl->setBaseStation(basestation);
    }

    BaseStation& WirelessNode::getBaseStation()
    {
        return m_impl->getBaseStation();
    }

    bool WirelessNode::hasBaseStation(const BaseStation& basestation) const
    {
        return m_impl->hasBaseStation(basestation);
    }

    void WirelessNode::useGroupRead(bool useGroup)
    {
        m_impl->useGroupRead(useGroup);
    }

    void WirelessNode::readWriteRetries(uint8 numRetries)
    {
        m_impl->setReadWriteRetries(numRetries);
    }

    uint8 WirelessNode::readWriteRetries() const
    {
        return m_impl->getReadWriteRetries();
    }

    void WirelessNode::useEepromCache(bool useCache)
    {
        m_impl->useEepromCache(useCache);
    }

    void WirelessNode::clearEepromCache()
    {
        m_impl->clearEepromCache();
    }

    void WirelessNode::updateEepromCacheFromNodeDiscovery(const NodeDiscovery& nodeDisovery)
    {
        m_impl->updateEepromCacheFromNodeDiscovery(nodeDisovery);
    }

    WirelessTypes::EepromMap WirelessNode::getEepromCache() const
    {
        return m_impl->getEepromCache();
    }

    NodeAddress WirelessNode::nodeAddress() const
    {
        return m_impl->nodeAddress();
    }

    WirelessTypes::Frequency WirelessNode::frequency() const
    {
        return m_impl->frequency();
    }

    WirelessTypes::CommProtocol WirelessNode::communicationProtocol() const
    {
        return m_impl->communicationProtocol();
    }

    PingResponse WirelessNode::ping()
    {
        return m_impl->ping();
    }

    bool WirelessNode::sleep()
    {
        return m_impl->sleep();
    }

    void WirelessNode::cyclePower()
    {
        m_impl->cyclePower();
    }

    void WirelessNode::resetRadio()
    {
        m_impl->resetRadio();
    }

    void WirelessNode::changeFrequency(WirelessTypes::Frequency frequency)
    {
        m_impl->changeFrequency(frequency);
    }

    SetToIdleStatus WirelessNode::setToIdle()
    {
        return m_impl->setToIdle();
    }

    void WirelessNode::erase()
    {
        m_impl->erase();
    }

    bool WirelessNode::startNonSyncSampling()
    {
        return m_impl->startNonSyncSampling();
    }

    bool WirelessNode::resendStartSyncSampling()
    {
        return m_impl->startSyncSampling();
    }

    void WirelessNode::clearHistogram()
    {
        m_impl->clearHistogram();
    }

    AutoBalanceResult WirelessNode::autoBalance(const ChannelMask& mask, float targetPercent)
    {
        return m_impl->autoBalance(mask, targetPercent);
    }

    AutoCalResult_shmLink WirelessNode::autoCal_shmLink()
    {
        return m_impl->autoCal_shmLink();
    }

    AutoCalResult_shmLink201 WirelessNode::autoCal_shmLink201()
    {
        return m_impl->autoCal_shmLink201();
    }

    AutoShuntCalResult WirelessNode::autoShuntCal(const ChannelMask& mask, const ShuntCalCmdInfo& commandInfo)
    {
        return m_impl->autoShuntCal(mask, commandInfo);
    }

    WirelessPollData WirelessNode::poll(const ChannelMask& mask)
    {
        return m_impl->poll(mask);
    }

    uint16 WirelessNode::readEeprom(uint16 location) const
    {
        return m_impl->readEeprom(location);
    }

    void WirelessNode::writeEeprom(uint16 location, uint16 value)
    {
        m_impl->writeEeprom(location, value);
    }

    ChannelData WirelessNode::getDiagnosticInfo()
    {
        ChannelData result;
        m_impl->getDiagnosticInfo(result);
        return result;
    }

    bool WirelessNode::testCommunicationProtocol(WirelessTypes::CommProtocol protocol)
    {
        return m_impl->testCommProtocol(protocol);
    }

    Version WirelessNode::firmwareVersion() const
    {
        return m_impl->firmwareVersion();
    }

    WirelessModels::NodeModel WirelessNode::model() const
    {
        return m_impl->model();
    }

    std::string WirelessNode::serial() const
    {
        return m_impl->serial();
    }

    std::string WirelessNode::name() const
    {
        return deviceName(nodeAddress());
    }

    WirelessTypes::MicroControllerType WirelessNode::microcontroller() const
    {
        return m_impl->microcontroller();
    }

    RadioFeatures WirelessNode::radioFeatures() const
    {
        return m_impl->radioFeatures();
    }

    uint64 WirelessNode::dataStorageSize() const
    {
        return m_impl->dataStorageSize();
    }

    WirelessTypes::RegionCode WirelessNode::regionCode() const
    {
        return m_impl->regionCode();
    }

    bool WirelessNode::verifyConfig(const WirelessNodeConfig& config, ConfigIssues& outIssues) const
    {
        return m_impl->verifyConfig(config, outIssues);
    }

    void WirelessNode::applyConfig(const WirelessNodeConfig& config)
    {
        m_impl->applyConfig(config);
    }

    uint16 WirelessNode::getNumDatalogSessions() const
    {
        return m_impl->getNumDatalogSessions();
    }

    float WirelessNode::percentFull() const
    {
        return m_impl->percentFull();
    }

    WirelessTypes::DefaultMode WirelessNode::getDefaultMode() const
    {
        return m_impl->getDefaultMode();
    }

    uint16 WirelessNode::getInactivityTimeout() const
    {
        return m_impl->getInactivityTimeout();
    }

    uint8 WirelessNode::getCheckRadioInterval() const
    {
        return m_impl->getCheckRadioInterval();
    }

    WirelessTypes::TransmitPower WirelessNode::getTransmitPower() const
    {
        return m_impl->getTransmitPower();
    }

    WirelessTypes::SamplingMode WirelessNode::getSamplingMode() const
    {
        return m_impl->getSamplingMode();
    }

    ChannelMask WirelessNode::getActiveChannels() const
    {
        return m_impl->getActiveChannels();
    }

    WirelessTypes::WirelessSampleRate WirelessNode::getSampleRate() const
    {
        return m_impl->getSampleRate();
    }

    uint32 WirelessNode::getNumSweeps() const
    {
        return m_impl->getNumSweeps();
    }

    bool WirelessNode::getUnlimitedDuration() const
    {
        return m_impl->getUnlimitedDuration();
    }

    WirelessTypes::DataFormat WirelessNode::getDataFormat() const
    {
        return m_impl->getDataFormat();
    }

    WirelessTypes::DataCollectionMethod WirelessNode::getDataCollectionMethod() const
    {
        return m_impl->getDataCollectionMethod();
    }

    TimeSpan WirelessNode::getTimeBetweenBursts() const
    {
        return m_impl->getTimeBetweenBursts();
    }

    uint16 WirelessNode::getLostBeaconTimeout() const
    {
        return m_impl->getLostBeaconTimeout();
    }

    WirelessTypes::InputRange WirelessNode::getInputRange(const ChannelMask& mask) const
    {
        return m_impl->getInputRange(mask);
    }

    uint16 WirelessNode::getHardwareOffset(const ChannelMask& mask) const
    {
        return m_impl->getHardwareOffset(mask);
    }

    WirelessTypes::Filter WirelessNode::getAntiAliasingFilter(const ChannelMask& mask) const
    {
        return m_impl->getAntiAliasingFilter(mask);
    }

    WirelessTypes::ChannelFrequencyClass WirelessNode::getCfcFilterConfiguration() const
    {
        return m_impl->getCfcFilterConfiguration();
    }

    WirelessTypes::Filter WirelessNode::getLowPassFilter(const ChannelMask& mask) const
    {
        return m_impl->getLowPassFilter(mask);
    }

    WirelessTypes::HighPassFilter WirelessNode::getHighPassFilter(const ChannelMask& mask) const
    {
        return m_impl->getHighPassFilter(mask);
    }

    uint16 WirelessNode::getDebounceFilter(const ChannelMask& mask) const
    {
        return m_impl->getDebounceFilter(mask);
    }

    bool WirelessNode::getPullUpResistor(const ChannelMask& mask) const
    {
        return m_impl->getPullUpResistor(mask);
    }

    WirelessTypes::SensorOutputMode WirelessNode::getSensorOutputMode() const
    {
        return m_impl->getSensorOutputMode();
    }

    float WirelessNode::getGaugeFactor(const ChannelMask& mask) const
    {
        return m_impl->getGaugeFactor(mask);
    }

    WirelessTypes::Voltage WirelessNode::getExcitationVoltage() const
    {
        return m_impl->getExcitationVoltage();
    }

    WirelessTypes::Voltage WirelessNode::getAdcVoltageRef() const
    {
        return m_impl->getAdcVoltageRef();
    }

    WirelessTypes::Voltage WirelessNode::getGainAmplifierVoltageRef() const
    {
        return m_impl->getGainAmplifierVoltageRef();
    }

    uint16 WirelessNode::getGaugeResistance() const
    {
        return m_impl->getGaugeResistance();
    }

    uint16 WirelessNode::getNumActiveGauges() const
    {
        return m_impl->getNumActiveGauges();
    }

    float WirelessNode::getLowBatteryThreshold() const
    {
        return m_impl->getLowBatteryThreshold();
    }

    LinearEquation WirelessNode::getLinearEquation(const ChannelMask& mask) const
    {
        return m_impl->getLinearEquation(mask);
    }

    WirelessTypes::CalCoef_Unit WirelessNode::getUnit(const ChannelMask& mask) const
    {
        return m_impl->getUnit(mask);
    }

    WirelessTypes::CalCoef_EquationType WirelessNode::getEquationType(const ChannelMask& mask) const
    {
        return m_impl->getEquationType(mask);
    }

    LinearEquation WirelessNode::getFactoryCalibrationLinearEq(const ChannelMask& mask) const
    {
        return m_impl->getFactoryCalibrationLinearEq(mask);
    }

    WirelessTypes::CalCoef_Unit WirelessNode::getFactoryCalibrationUnit(const ChannelMask& mask) const
    {
        return m_impl->getFactoryCalibrationUnit(mask);
    }

    WirelessTypes::CalCoef_EquationType WirelessNode::getFactoryCalibrationEqType(const ChannelMask& mask) const
    {
        return m_impl->getFactoryCalibrationEqType(mask);
    }

    WirelessTypes::SettlingTime WirelessNode::getFilterSettlingTime(const ChannelMask& mask) const
    {
        return m_impl->getFilterSettlingTime(mask);
    }

    WirelessTypes::ThermocoupleType WirelessNode::getThermocoupleType(const ChannelMask& mask) const
    {
        return m_impl->getThermocoupleType(mask);
    }

    TempSensorOptions WirelessNode::getTempSensorOptions(const ChannelMask& mask) const
    {
        return m_impl->getTempSensorOptions(mask);
    }

    FatigueOptions WirelessNode::getFatigueOptions() const
    {
        return m_impl->getFatigueOptions();
    }

    HistogramOptions WirelessNode::getHistogramOptions() const
    {
        return m_impl->getHistogramOptions();
    }

    ActivitySense WirelessNode::getActivitySense() const
    {
        return m_impl->getActivitySense();
    }

    EventTriggerOptions WirelessNode::getEventTriggerOptions() const
    {
        return m_impl->getEventTriggerOptions();
    }

    uint16 WirelessNode::getDiagnosticInterval() const
    {
        return m_impl->getDiagnosticInterval();
    }

    WirelessTypes::StorageLimitMode WirelessNode::getStorageLimitMode() const
    {
        return m_impl->getStorageLimitMode();
    }

    uint32 WirelessNode::getSensorDelay() const
    {
        return m_impl->getSensorDelay();
    }

    WirelessTypes::DataMode WirelessNode::getDataMode() const
    {
        return m_impl->getDataMode();
    }

    WirelessTypes::WirelessSampleRate WirelessNode::getDerivedDataRate() const
    {
        return m_impl->getDerivedDataRate();
    }

    ChannelMask WirelessNode::getDerivedChannelMask(WirelessTypes::DerivedCategory category) const
    {
        return m_impl->getDerivedChannelMask(category);
    }

    WirelessTypes::DerivedVelocityUnit WirelessNode::getDerivedVelocityUnit() const
    {
        return m_impl->getDerivedVelocityUnit();
    }
}