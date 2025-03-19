/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "mscl/MicroStrain/Wireless/WirelessTypes.h"

namespace mscl
{
    uint16 WirelessTypes::dataTypeSize(DataType type)
    {
        switch(type)
        {
            case dataType_uint16_12bitRes:
            case dataType_uint16:
            case dataType_uint16_shifted:
            case dataType_uint16_18bitTrunc:
            case dataType_uint16_24bitTrunc:
            case dataType_int16_20bitTrunc:
            case dataType_int16_x10:
                return 2;

            case dataType_float32:
            case dataType_float32_noCals:
            case dataType_uint32:
                return 4;

            case dataType_uint24:
            case dataType_uint24_18bitRes:
            case dataType_int24_20bit:
                return 3;

            default:
                assert(false);    //need to add support for a new DataType if this assert is hit
                return 2;
        }
    }

    ValueType WirelessTypes::dataTypeToValueType(DataType type)
    {
        //check the DataType
        switch(type)
        {
            //data types that are unsigned shorts
            case dataType_uint16_12bitRes:
            case dataType_uint16:
            case dataType_uint16_shifted:
                return valueType_uint16;

            case dataType_uint32:
            case dataType_uint24:               //uint24 is stored as a uint32 in mscl
            case dataType_uint24_18bitRes:
            case dataType_uint16_18bitTrunc:    //uint16 from 18-bit node is stored as a uint32 in mscl
            case dataType_uint16_24bitTrunc:    //uint16 from 24-bit node is stored as a uint32 in mscl
                return valueType_uint32;

            case dataType_int16_20bitTrunc:     //int16 from 20-bit node is stored as an int32 in mscl
            case dataType_int24_20bit:          //int24 from 20-bit node is stored as an int32 in mscl
                return valueType_int32;

            //data types that are floats
            case dataType_float32:
            case dataType_float32_noCals:
            case dataType_int16_x10:            //int16 stored as a float in mscl
                return valueType_float;

            default:
                assert(false);    //need to add support for a new DataType if this assert is hit
                return valueType_uint16;
        }
    }

    uint8 WirelessTypes::dataFormatSize(DataFormat dataFormat)
    {
        switch(dataFormat)
        {
        case dataFormat_cal_float:
            return 4;

        case dataFormat_raw_uint24:
        case dataFormat_raw_int24:
            return 3;

        case dataFormat_raw_uint16:
        case dataFormat_raw_int16:
        case dataFormat_cal_int16_x10:
        default:
            return 2;
        }
    }

    bool WirelessTypes::isCalApplied(DataType dataType)
    {
        switch(dataType)
        {
            case dataType_float32:
            case dataType_int16_x10:
                return true;

            default:
                return false;
        }
    }

    uint16 WirelessTypes::settlingTime(SettlingTime time)
    {
        switch(time)
        {
            case settling_4ms:            return 4;
            case settling_8ms:            return 8;
            case settling_16ms:            return 16;
            case settling_32ms:            return 32;
            case settling_40ms:            return 40;
            case settling_48ms:            return 50;
            case settling_60ms:            return 60;
            case settling_101ms_90db:    return 101;
            case settling_120ms_80db:    return 120;
            case settling_120ms_65db:    return 120;
            case settling_160ms_69db:    return 160;
            case settling_200ms:        return 200;

            default:                        return 0;
        }
    }

    WirelessTypes::WirelessSampleRate WirelessTypes::dataloggingRateToSampleRate(uint16 eepromValue)
    {
        //build the map of datalogging eeprom values to sample rates
        static const std::map<uint16, WirelessSampleRate> dataloggingMap = {
                {0, sampleRate_4096Hz},
                {1, sampleRate_2048Hz},
                {2, sampleRate_1024Hz},
                {3, sampleRate_512Hz},
                {4, sampleRate_256Hz},
                {5, sampleRate_128Hz},
                {6, sampleRate_64Hz},
                {7, sampleRate_32Hz}};

        //try to find the eeprom value in the map
        std::map<uint16, WirelessSampleRate>::const_iterator itr = dataloggingMap.find(eepromValue);

        //if we found the value
        if(itr != dataloggingMap.end())
        {
            //return the rate
            return itr->second;
        }

        //cast and return the value
        return static_cast<WirelessSampleRate>(eepromValue);
    }

    uint16 WirelessTypes::sampleRateToDataloggingRate(WirelessSampleRate rate)
    {
        //build the map of sample rates to datalogging eeprom values
        static const std::map<WirelessSampleRate, uint16> dataloggingMap = {
                {sampleRate_4096Hz, 0},
                {sampleRate_2048Hz, 1},
                {sampleRate_1024Hz, 2},
                {sampleRate_512Hz, 3},
                {sampleRate_256Hz, 4},
                {sampleRate_128Hz, 5},
                {sampleRate_64Hz, 6},
                {sampleRate_32Hz, 7}};

        //try to find the sample rate in the map
        std::map<WirelessSampleRate, uint16>::const_iterator itr = dataloggingMap.find(rate);

        //if we found the value
        if(itr != dataloggingMap.end())
        {
            //return the rate
            return itr->second;
        }

        //cast and return the value
        return static_cast<uint16>(rate);
    }

    WirelessTypes::TransmitPower WirelessTypes::legacyToTransmitPower(LegacyTransmitPower legacyVal)
    {
        switch(legacyVal)
        {
            case legacyPower_5dBm:
                return power_5dBm;

            case legacyPower_0dBm:
                return power_0dBm;

            case legacyPower_10dBm:
                return power_10dBm;

            case legacyPower_16dBm:
                return power_16dBm;

            default:
                return static_cast<TransmitPower>(legacyVal);
        }
    }

    WirelessTypes::LegacyTransmitPower WirelessTypes::transmitPowerToLegacy(TransmitPower power)
    {
        switch(power)
        {
            case power_5dBm:
                return legacyPower_5dBm;

            case power_0dBm:
                return legacyPower_0dBm;

            case power_10dBm:
                return legacyPower_10dBm;

            case power_16dBm:
                return legacyPower_16dBm;

            default:
                throw Error("Attempting to convert a transmit power (" + Utils::toStr(power) + ") without a legacy equivalent.");
        }
    }

    uint8 WirelessTypes::bytesPerDerivedAlgorithmId(DerivedDataPacketAlgorithmId id)
    {
        switch(id)
        {
            case derivedAlgId_rms:
            case derivedAlgId_peakToPeak:
            case derivedAlgId_ips:
            case derivedAlgId_mmps:
            case derivedAlgId_crestFactor:
            case derivedAlgId_mean:
                return 4;

            default:
                throw Error_NotSupported("Invalid Derived Channel ID ( " + Utils::toStr(id) + ")");
        }
    }

    uint8 WirelessTypes::bytesPerDerivedChannelOption(DerivedCategory category)
    {
        switch(category)
        {
            case derivedCategory_rms:
            case derivedCategory_peakToPeak:
            case derivedCategory_velocity:
            case derivedCategory_crestFactor:
            case derivedCategory_mean:
                return 4;

            default:
                throw Error_NotSupported("Invalid DerivedCategory ( " + Utils::toStr(category) + ")");
        }
    }

    uint32 WirelessTypes::derivedBytesPerSweep(const DerivedChannelMasks& derivedChannelMasks)
    {
        uint32 sweepSize = 0;
        uint8 count = 0;
        for(const auto& ch : derivedChannelMasks)
        {
            count = ch.second.count();

            if(count > 0)
            {
                sweepSize += count * bytesPerDerivedChannelOption(ch.first);
            }
        }

        return sweepSize;
    }
} // namespace mscl
