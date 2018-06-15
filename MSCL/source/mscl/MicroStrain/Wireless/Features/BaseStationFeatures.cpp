/*******************************************************************************
Copyright(c) 2015-2018 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"
#include "BaseStationFeatures.h"

#include "BaseStationFeatures_analog.h"
#include "BaseStationFeatures_rs232.h"
#include "BaseStationFeatures_usb.h"
#include "BaseStationFeatures_usb200.h"
#include "BaseStationFeatures_wsda.h"
#include "BaseStationFeatures_wsda2000.h"
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
                return std::unique_ptr<BaseStationFeatures>(new BaseStationFeatures_wsda(info));

            case WirelessModels::base_wsda_2000:
                return std::unique_ptr<BaseStationFeatures>(new BaseStationFeatures_wsda2000(info));

            default:
                //we don't know anything about this node, throw an exception
                throw Error_NotSupported("The BaseStation model (" + Utils::toStr(info.model()) + ") is not supported by MSCL.");
        }
    }

    bool BaseStationFeatures::supportsTransmitPower(WirelessTypes::TransmitPower power, WirelessTypes::CommProtocol commProtocol) const
    {
        //get the supported powers
        const WirelessTypes::TransmitPowers supportedPowers = transmitPowers(commProtocol);

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

    const WirelessTypes::TransmitPowers BaseStationFeatures::transmitPowers(WirelessTypes::CommProtocol commProtocol) const
    {
        WirelessTypes::TransmitPowers result{
            WirelessTypes::power_20dBm,
            WirelessTypes::power_16dBm,
            WirelessTypes::power_10dBm,
            WirelessTypes::power_5dBm,
            WirelessTypes::power_0dBm
        };

        //find the max transmit power for the node's region code
        WirelessTypes::TransmitPower maxPower = maxTransmitPower(m_baseInfo.regionCode(), commProtocol);
        WirelessTypes::TransmitPower minPower = minTransmitPower(m_baseInfo.regionCode(), commProtocol);

        narrowDownTxPowers(result, minPower, maxPower);

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

    WirelessTypes::TransmitPower BaseStationFeatures::maxTransmitPower(WirelessTypes::RegionCode region, WirelessTypes::CommProtocol commProtocol) const
    {
        //determine the max power based on the region code
        switch(region)
        {
            case WirelessTypes::region_japan:
                return WirelessTypes::power_10dBm;

            case WirelessTypes::region_europe:
            case WirelessTypes::region_other:
                return WirelessTypes::power_10dBm;

            case WirelessTypes::region_usa:
            case WirelessTypes::region_brazil:
            case WirelessTypes::region_china:
            default:
            {
                if(supportsNewTransmitPowers())
                {
                    return WirelessTypes::power_20dBm;
                }
                else
                {
                    return WirelessTypes::power_16dBm;
                }
            }
        }
    }

    WirelessTypes::TransmitPower BaseStationFeatures::minTransmitPower(WirelessTypes::RegionCode region, WirelessTypes::CommProtocol commProtocol) const
    {
        switch(region)
        {
            case WirelessTypes::region_japan:
                return WirelessTypes::power_5dBm;

            default:
                return WirelessTypes::power_0dBm;
        }
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

    void BaseStationFeatures::narrowDownTxPowers(WirelessTypes::TransmitPowers& txPowers, WirelessTypes::TransmitPower min, WirelessTypes::TransmitPower max)
    {
        auto outOfRange = [min, max](WirelessTypes::TransmitPower power) { return (power < min || power > max); };
        
        Utils::eraseIf(txPowers, outOfRange);
    }
}