/*******************************************************************************
Copyright(c) 2015 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "mscl/MicroStrain/Wireless/WirelessModels.h"

namespace mscl
{
    //Class: HardwareGain
    //    Contains functions specific to hardware gain for Wireless Nodes.
    class HardwareGain
    {
    private:
        static const uint16 MIN_BITS = 0;
        static const uint16 MAX_BITS = 255;
        static const uint16 MAX_BITS_SGLINKOEM = 7;
        static const uint16 MAX_BITS_TCLINK = 7;
        static const uint16 MAX_BITS_MVPERVLINK = 7;

        //The following functions contain the different formulas for converting
        //bits to gain and gain to bits for various products.
        static double bitsToGain_sgLink(uint16 bits);
        static double bitsToGain_sgLinkOem(uint16 bits);
        static double bitsToGain_sgLinkRgd(uint16 bits);
        static double bitsToGain_shmLink(uint16 bits);
        static double bitsToGain_vLink(uint16 bits);
        static double bitsToGain_tcLink(uint16 bits);
        static double bitsToGain_mvpervLink(uint16 bits);
        static uint16 gainToBits_sgLink(double gain);
        static uint16 gainToBits_sgLinkOem(double gain);
        static uint16 gainToBits_sgLinkRgd(double gain);
        static uint16 gainToBits_shmLink(double gain);
        static uint16 gainToBits_vLink(double gain);
        static uint16 gainToBits_tcLink(double gain);
        static uint16 gainToBits_mvpervLink(double gain);


    public:
        //Function: bitsToGain
        //    Converts the bits value to Hardware Gain value, based on the nodeType.
        //
        //Parameters:
        //    bits - The bits value to convert.
        //    nodeType - The type of node to use for the conversion.
        //
        //Returns:
        //    The converted gain value.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The hardware gain feature is not supported by this Node.
        static double bitsToGain(uint16 bits, WirelessModels::NodeModel nodeType);

        //Function: gainToBits
        //    Converts the gain value to a bits value, based on the nodeType.
        //
        //Parameters:
        //    gain - The hardware gain value to convert.
        //    nodeType - The type of node to use for the conversion.
        //
        //Returns:
        //    The converted bits value.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The hardware gain feature is not supported by this Node.
        static uint16 gainToBits(double gain, WirelessModels::NodeModel nodeType);

        //Function: minGain
        //    Gets the min gain value available for the Node/Channel.
        //
        //Parameters:
        //    nodeType - The type of node to use for the conversion.
        //
        //Returns:
        //    The min gain value available.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The hardware gain feature is not supported by this Node.
        static double minGain(WirelessModels::NodeModel nodeType);

        //Function: maxGain
        //    Gets the max gain value available for the Node/Channel.
        //
        //Parameters:
        //    nodeType - The type of node to use for the conversion.
        //
        //Returns:
        //    The max gain value available.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The hardware gain feature is not supported by this Node.
        static double maxGain(WirelessModels::NodeModel nodeType);

        //Function: normalizeGain
        //    Normalizes the gain value by putting it within range, and converting to bits and then back to gain.
        //
        //Parameters:
        //    gain - The gain value to normalize.
        //    nodeType - The type of node to use for the conversion.
        //
        //Returns:
        //    The normalized gain value.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The hardware gain feature is not supported by this Node.
        static double normalizeGain(double gain, WirelessModels::NodeModel nodeType);
    };
}