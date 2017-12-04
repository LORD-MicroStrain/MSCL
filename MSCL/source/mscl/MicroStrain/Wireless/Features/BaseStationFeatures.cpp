/*******************************************************************************
Copyright(c) 2015-2017 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"
#include "BaseStationFeatures.h"

#include "BaseStationFeatures_analog.h"
#include "BaseStationFeatures_rs232.h"
#include "BaseStationFeatures_usb.h"
#include "BaseStationFeatures_usb200.h"
#include "BaseStationFeatures_wsda.h"
#include "mscl/MicroStrain/Wireless/WirelessModels.h"

namespace mscl
{
    BaseStationFeatures::BaseStationFeatures(const BaseStationInfo& info) :
        m_baseInfo(info)
    {
    }

    std::unique_ptr<BaseStationFeatures> BaseStationFeatures::create(const BaseStationInfo& info)
    {
        switch(info.model())
        {
            case WirelessModels::base_wsdaBase_200_legacy:    // (TODO: remove)
            case WirelessModels::base_wsdaBase_200:
            case WirelessModels::base_wsdaBase_200_extAntenna:
            case WirelessModels::base_wsi_104:
                return std::unique_ptr<BaseStationFeatures>(new BaseStationFeatures_usb200(info));

            case WirelessModels::base_wsdaBase_104_usb:
                return std::unique_ptr<BaseStationFeatures>(new BaseStationFeatures_usb(info));

            case WirelessModels::base_wsdaBase_101_analog:
                return std::unique_ptr<BaseStationFeatures>(new BaseStationFeatures_analog(info));

            case WirelessModels::base_wsdaBase_102_rs232:
                return std::unique_ptr<BaseStationFeatures>(new BaseStationFeatures_rs232(info));

            case WirelessModels::base_wsda_1000:
            case WirelessModels::base_wsda_1500:
            case WirelessModels::base_wsda_2000:
                return std::unique_ptr<BaseStationFeatures>(new BaseStationFeatures_wsda(info));

            default:
                //we don't know anything about this node, throw an exception
                throw Error_NotSupported("The BaseStation model (" + Utils::toStr(info.model()) + ") is not supported by MSCL.");
        }
    }

    bool BaseStationFeatures::supportsTransmitPower(WirelessTypes::TransmitPower power) const
    {
        //get the supported powers
        const WirelessTypes::TransmitPowers supportedPowers = transmitPowers();

        //return the result of trying to find the power in the vector
        return (std::find(supportedPowers.begin(), supportedPowers.end(), power) != supportedPowers.end());
    }

    bool BaseStationFeatures::supportsCommunicationProtocol(WirelessTypes::CommProtocol protocol) const
    {
        const WirelessTypes::CommProtocols supportedProtocols = commProtocols();
        return (std::find(supportedProtocols.begin(), supportedProtocols.end(), protocol) != supportedProtocols.end());
    }

    bool BaseStationFeatures::supportsButtons() const
    {
        return (buttonCount() > 0);
    }

    bool BaseStationFeatures::supportsAnalogPairing() const
    {
        return (analogPortCount() > 0);
    }

    bool BaseStationFeatures::supportsBeaconStatus() const
    {
        //just checking if beacon status is supported for one of the radio modes
        //all other modes should follow suit
        return m_baseInfo.protocol(WirelessTypes::commProtocol_lxrs).supportsBeaconStatus();
    }

    bool BaseStationFeatures::supportsRfSweepMode() const
    {
        static const Version MIN_RF_SWEEP_FW(4, 30448);

        return (m_baseInfo.firmwareVersion() >= MIN_RF_SWEEP_FW);
    }

    bool BaseStationFeatures::supportsCustomRfSweepMode() const
    {
        return false;
    }

    uint8 BaseStationFeatures::analogPortCount() const
    {
        return 0;
    }

    uint8 BaseStationFeatures::buttonCount() const
    {
        return 0;
    }

    const WirelessTypes::TransmitPowers BaseStationFeatures::transmitPowers() const
    {
        WirelessTypes::TransmitPowers result;

        //find the max transmit power for the node's region code
        WirelessTypes::TransmitPower maxPower = WirelessTypes::maxTransmitPower(m_baseInfo.regionCode());

        //add the power levels based on the max power we determined above
        if(maxPower >= WirelessTypes::power_20dBm && supportsNewTransmitPowers())
        {
            result.push_back(WirelessTypes::power_20dBm);
        }

        if(maxPower >= WirelessTypes::power_16dBm)
        {
            result.push_back(WirelessTypes::power_16dBm);
        }

        if(maxPower >= WirelessTypes::power_10dBm)
        {
            result.push_back(WirelessTypes::power_10dBm);
        }

        if(maxPower >= WirelessTypes::power_5dBm)
        {
            result.push_back(WirelessTypes::power_5dBm);
        }

        if(maxPower >= WirelessTypes::power_0dBm)
        {
            result.push_back(WirelessTypes::power_0dBm);
        }

        return result;
    }

    const WirelessTypes::CommProtocols BaseStationFeatures::commProtocols() const
    {
        WirelessTypes::CommProtocols result;

        result.push_back(WirelessTypes::commProtocol_lxrs);

        static const Version MIN_LXRS_PLUS_FW(5, 0);
        if(m_baseInfo.firmwareVersion() >= MIN_LXRS_PLUS_FW)
        {
            result.push_back(WirelessTypes::commProtocol_lxrsPlus);
        }

        return result;
    }

    bool BaseStationFeatures::supportsNewTransmitPowers() const
    {
        static const Version MIN_NEW_TX_POWER_FW(4, 0);

        return (m_baseInfo.firmwareVersion() >= MIN_NEW_TX_POWER_FW);
    }

    bool BaseStationFeatures::supportsEepromCommitViaRadioReset() const
    {
        static const Version MIN_EEPROM_COMMIT_RADIO_FW(4, 0);

        return (m_baseInfo.firmwareVersion() >= MIN_EEPROM_COMMIT_RADIO_FW);
    }

    bool BaseStationFeatures::supportsEeprom1024AndAbove() const
    {
        static const Version HIGH_EEPROM_FW(4, 0);

        return (m_baseInfo.firmwareVersion() >= HIGH_EEPROM_FW);
    }

    bool BaseStationFeatures::supportsCommProtocolEeprom() const
    {
        static const Version MIN_LXRS_PLUS_FW(5, 0);

        return (m_baseInfo.firmwareVersion() >= MIN_LXRS_PLUS_FW);
    }
}