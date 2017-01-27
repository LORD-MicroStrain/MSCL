/*******************************************************************************
Copyright(c) 2015-2017 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"
#include "BaseStationFeatures.h"

#include "BaseStationFeatures_analog.h"
#include "BaseStationFeatures_rs232.h"
#include "BaseStationFeatures_usb.h"
#include "BaseStationFeatures_wsda.h"
#include "BaseStationFeatures_oem.h"
#include "mscl/MicroStrain/Wireless/WirelessModels.h"

namespace mscl
{
    BaseStationFeatures::BaseStationFeatures(BaseStationInfo& info) :
        m_baseInfo(info)
    {
    }

    std::unique_ptr<BaseStationFeatures> BaseStationFeatures::create(BaseStationInfo& info)
    {
        switch(info.model())
        {
            case WirelessModels::base_wsdaBase_104_usb:
            case WirelessModels::base_wsdaBase_200:
                return std::unique_ptr<BaseStationFeatures>(new BaseStationFeatures_usb(info));

            case WirelessModels::base_wsdaBase_101_analog:
                return std::unique_ptr<BaseStationFeatures>(new BaseStationFeatures_analog(info));

            case WirelessModels::base_wsdaBase_102_rs232:
                return std::unique_ptr<BaseStationFeatures>(new BaseStationFeatures_rs232(info));

            case WirelessModels::base_wsdaBase_oem:
                return std::unique_ptr<BaseStationFeatures>(new BaseStationFeatures_oem(info));

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
        static const Version MIN_BEACON_STATUS_FW(4, 0);

        return (m_baseInfo.firmwareVersion() >= MIN_BEACON_STATUS_FW);
    }

    bool BaseStationFeatures::supportsRfSweepMode() const
    {
        static const Version MIN_RF_SWEEP_FW(4, 30448);

        return (m_baseInfo.firmwareVersion() >= MIN_RF_SWEEP_FW);
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
}