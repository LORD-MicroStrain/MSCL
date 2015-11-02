/*******************************************************************************
Copyright(c) 2015 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"

#include "WirelessNode.h"
#include "WirelessNode_Impl.h"
#include "BaseStation.h"
#include "mscl/Utils.h"
#include "Features/NodeInfo.h"
#include "Features/NodeFeatures.h"
#include "Configuration/NodeEepromHelper.h"
#include "Configuration/WirelessNodeConfig.h"

namespace mscl
{
	WirelessNode::WirelessNode(uint16 nodeAddress, const BaseStation& basestation):
		m_impl(std::make_shared<WirelessNode_Impl>(nodeAddress, basestation))
	{
	}

	void WirelessNode::setImpl(std::shared_ptr<WirelessNode_Impl> impl)
	{
		m_impl = impl;
	}

	NodeEepromHelper& WirelessNode::eepromHelper() const
	{
		return m_impl->eeHelper();
	}

	const WirelessProtocol& WirelessNode::protocol() const
	{
		return m_impl->protocol();
	}

	std::string WirelessNode::deviceName(uint16 nodeAddress)
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
		m_impl->readWriteRetries(numRetries);
	}

	void WirelessNode::useEepromCache(bool useCache)											
	{ 
		m_impl->useEepromCache(useCache); 
	}

	void WirelessNode::clearEepromCache()
	{
		m_impl->clearEepromCache();
	}

	uint16 WirelessNode::nodeAddress() const
	{ 
		return m_impl->nodeAddress(); 
	}

	WirelessTypes::Frequency WirelessNode::frequency() const
	{ 
		return m_impl->frequency(); 
	}

	bool WirelessNode::quickPing()
	{
		return m_impl->quickPing();
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

	void WirelessNode::startNonSyncSampling()													
	{ 
		m_impl->startNonSyncSampling(); 
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

	uint16 WirelessNode::readEeprom(uint16 location) const
	{ 
		return m_impl->readEeprom(location); 
	}

	void WirelessNode::writeEeprom(uint16 location, uint16 value)
	{ 
		m_impl->writeEeprom(location, value); 
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

	double WirelessNode::getHardwareGain(const ChannelMask& mask) const
	{
		return m_impl->getHardwareGain(mask);
	}

	uint16 WirelessNode::getHardwareOffset(const ChannelMask& mask) const
	{
		return m_impl->getHardwareOffset(mask);
	}

	float WirelessNode::getGaugeFactor(const ChannelMask& mask) const
	{
		return m_impl->getGaugeFactor(mask);
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

	WirelessTypes::SettlingTime WirelessNode::getFilterSettlingTime(const ChannelMask& mask) const
	{
		return m_impl->getFilterSettlingTime(mask);
	}

	WirelessTypes::ThermocoupleType WirelessNode::getThermocoupleType(const ChannelMask& mask) const
	{
		return m_impl->getThermocoupleType(mask);
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
}