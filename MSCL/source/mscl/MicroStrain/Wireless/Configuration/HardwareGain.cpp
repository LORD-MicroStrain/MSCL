/*******************************************************************************
Copyright(c) 2015 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"
#include "HardwareGain.h"

#include "mscl/Utils.h"

namespace mscl
{
    double HardwareGain::bitsToGain_sgLink(uint16 bits)
    {
        return (7.26216 * bits + 1.85185);
    }

    double HardwareGain::bitsToGain_sgLinkOem(uint16 bits)
    {
        return std::pow(2.0, bits + 1) * 10.0;
    }

    double HardwareGain::bitsToGain_sgLinkRgd(uint16 bits)
    {
        return 30.5 * (((bits / 255.0) * 50000.0) + 2700.0) / 2700.0;
    }

    double HardwareGain::bitsToGain_shmLink(uint16 bits)
    {
        return 30.0 * (((bits / 255.0) * 50000.0) + 4300.0) / 1000.0;
    }

    double HardwareGain::bitsToGain_vLink(uint16 bits)
    {
        return 21.0 * (99609.375 / (160.0 + (( (255.0 - bits) / 256.0) * 100000.0)));
    }

    double HardwareGain::bitsToGain_tcLink(uint16 bits)
    {
        return std::pow(2.0, bits);
    }

    double HardwareGain::bitsToGain_mvpervLink(uint16 bits)
    {
        return std::pow(2.0, bits) * 20.0;
    }

    uint16 HardwareGain::gainToBits_sgLink(double gain)
    {
        return static_cast<uint16>( ((0.1377 * gain) - 0.255) + 0.5 );
    }

    uint16 HardwareGain::gainToBits_sgLinkOem(double gain)
    {
        return static_cast<uint16>( Utils::logBase2(gain/10.0) + 0.5 ) - 1;
    }

    uint16 HardwareGain::gainToBits_sgLinkRgd(double gain)
    {
        return static_cast<uint16>( (((2700 / 30.5 * gain) - 2700) * 255 / 50000) + 0.5 );
    }

    uint16 HardwareGain::gainToBits_shmLink(double gain)
    {
        return static_cast<uint16>((17.0 * (gain - 129.0) / 100) + 0.5);
    }

    uint16 HardwareGain::gainToBits_vLink(double gain)
    {
        return static_cast<uint16>( (-1 * (5355.0 / gain)) + 255.41 + 0.5);
    }

    uint16 HardwareGain::gainToBits_tcLink(double gain)
    {
        return static_cast<uint16>(Utils::logBase2(gain) + 0.5);
    }

    uint16 HardwareGain::gainToBits_mvpervLink(double gain)
    {
        return static_cast<uint16>(Utils::logBase2(gain / 20.0) + 0.5);
    }

    double HardwareGain::bitsToGain(uint16 bits, WirelessModels::NodeModel nodeType)
    {
        switch(nodeType)
        {
            case WirelessModels::node_sgLink:
                return bitsToGain_sgLink(bits);

            case WirelessModels::node_sgLink_rgd:
                return bitsToGain_sgLinkRgd(bits);
            
            case WirelessModels::node_sgLink_8ch:
            case WirelessModels::node_shmLink:
                return bitsToGain_shmLink(bits);

            case WirelessModels::node_sgLink_oem:
            case WirelessModels::node_sgLink_oem_S:
            case WirelessModels::node_sgLink_herm:
            case WirelessModels::node_sgLink_herm_2600:
            case WirelessModels::node_sgLink_herm_2700:
            case WirelessModels::node_sgLink_herm_2800:
            case WirelessModels::node_sgLink_micro:
                return bitsToGain_sgLinkOem(bits);

            case WirelessModels::node_tcLink_1ch:
            case WirelessModels::node_tcLink_3ch:
            case WirelessModels::node_tcLink_6ch:
            case WirelessModels::node_tcLink_6ch_ip67:
            case WirelessModels::node_tcLink_6ch_ip67_rht:
            case WirelessModels::node_envLink_mini:
            case WirelessModels::node_envLink_pro:
            case WirelessModels::node_rtdLink:
                return bitsToGain_tcLink(bits);

            case WirelessModels::node_vLink:
            case WirelessModels::node_vLink_legacy:
                return bitsToGain_vLink(bits);

            case WirelessModels::node_mvPerVLink:
                return bitsToGain_mvpervLink(bits);

            default:
                break;
        }

        throw Error_NotSupported("Hardware Gain is not supported by this Node.");
    }

    uint16 HardwareGain::gainToBits(double gain, WirelessModels::NodeModel nodeType)
    {
        switch(nodeType)
        {
            case WirelessModels::node_sgLink:
                return gainToBits_sgLink(gain);

            case WirelessModels::node_sgLink_rgd:
                return gainToBits_sgLinkRgd(gain);

            case WirelessModels::node_sgLink_8ch:
            case WirelessModels::node_shmLink:
                return gainToBits_shmLink(gain);

            case WirelessModels::node_sgLink_oem:
            case WirelessModels::node_sgLink_oem_S:
            case WirelessModels::node_sgLink_herm:
            case WirelessModels::node_sgLink_herm_2600:
            case WirelessModels::node_sgLink_herm_2700:
            case WirelessModels::node_sgLink_herm_2800:
            case WirelessModels::node_sgLink_micro:
                return gainToBits_sgLinkOem(gain);

            case WirelessModels::node_tcLink_1ch:
            case WirelessModels::node_tcLink_3ch:
            case WirelessModels::node_tcLink_6ch:
            case WirelessModels::node_tcLink_6ch_ip67:
            case WirelessModels::node_tcLink_6ch_ip67_rht:
            case WirelessModels::node_envLink_mini:
            case WirelessModels::node_envLink_pro:
            case WirelessModels::node_rtdLink:
                return gainToBits_tcLink(gain);

            case WirelessModels::node_vLink:
            case WirelessModels::node_vLink_legacy:
                return gainToBits_vLink(gain);

            case WirelessModels::node_mvPerVLink:
                return gainToBits_mvpervLink(gain);

            default:
                break;
        }

        throw Error_NotSupported("Hardware Gain is not supported by this Node.");
    }

    double HardwareGain::minGain(WirelessModels::NodeModel nodeType)
    {
        //convert the min bits to gain
        return bitsToGain(MIN_BITS, nodeType);
    }

    double HardwareGain::maxGain(WirelessModels::NodeModel nodeType)
    {
        uint16 maxBits = 0;
        
        //determine the max bits value to use
        switch(nodeType)
        {
            case WirelessModels::node_sgLink_oem:
            case WirelessModels::node_sgLink_oem_S:
            case WirelessModels::node_sgLink_herm:
            case WirelessModels::node_sgLink_herm_2600:
            case WirelessModels::node_sgLink_herm_2700:
            case WirelessModels::node_sgLink_herm_2800:
            case WirelessModels::node_sgLink_micro:
                maxBits = MAX_BITS_SGLINKOEM;
                break;

            case WirelessModels::node_tcLink_1ch:
            case WirelessModels::node_tcLink_3ch:
            case WirelessModels::node_tcLink_6ch:
            case WirelessModels::node_tcLink_6ch_ip67:
            case WirelessModels::node_tcLink_6ch_ip67_rht:
            case WirelessModels::node_envLink_mini:
            case WirelessModels::node_envLink_pro:
            case WirelessModels::node_rtdLink:
                maxBits = MAX_BITS_TCLINK;
                break;

            case WirelessModels::node_mvPerVLink:
                maxBits = MAX_BITS_MVPERVLINK;
                break;

            default:
                maxBits = MAX_BITS;
        }

        //convert the max bits to gain
        return bitsToGain(maxBits, nodeType);
    }

    double HardwareGain::normalizeGain(double gain, WirelessModels::NodeModel nodeType)
    {
        //put the gain within the min and max range
        Utils::checkBounds_min(gain, minGain(nodeType));
        Utils::checkBounds_max(gain, maxGain(nodeType));

        //convert gain to bits
        uint16 bits = HardwareGain::gainToBits(gain, nodeType);

        //convert back from bits to gain
        return HardwareGain::bitsToGain(bits, nodeType);
    }
}