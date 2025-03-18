/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "mscl/MicroStrain/Wireless/WirelessChannel.h"

namespace mscl
{
    WirelessChannel::WirelessChannel() :
        m_chNumber(0),
        m_id(channel_unknown),
        m_type(WirelessTypes::chType_none),
        m_description(""),
        m_adcResolution(0)
    {}

    WirelessChannel::WirelessChannel(uint8 chNumber, ChannelId id, WirelessTypes::ChannelType type, const std::string& description) :
        m_chNumber(chNumber),
        m_id(id),
        m_type(type),
        m_description(description + " (ch" + Utils::toStr(chNumber) + ")"),
        m_adcResolution(0)
    {}

    WirelessChannel::WirelessChannel(uint8 chNumber, ChannelId id, WirelessTypes::ChannelType type, const std::string& description, uint8 adcResolution) :
        m_chNumber(chNumber),
        m_id(id),
        m_type(type),
        m_description(description + " (ch" + Utils::toStr(chNumber) + ")"),
        m_adcResolution(adcResolution)
    {}

    uint8 WirelessChannel::channelNumber() const
    {
        return m_chNumber;
    }

    WirelessChannel::ChannelId WirelessChannel::id() const
    {
        return m_id;
    }

    WirelessTypes::ChannelType WirelessChannel::type() const
    {
        return m_type;
    }

    std::string WirelessChannel::name() const
    {
        return channelName(id());
    }

    std::string WirelessChannel::description() const
    {
        return m_description;
    }

    uint8 WirelessChannel::adcResolution() const
    {
        return m_adcResolution;
    }

    uint32 WirelessChannel::adcMaxValue() const
    {
        return static_cast<uint32>(std::pow(2, m_adcResolution));
    }

    std::string WirelessChannel::channelName(ChannelId channelId)
    {
        switch(channelId)
        {
            case channel_1:                         return "ch1";
            case channel_2:                         return "ch2";
            case channel_3:                         return "ch3";
            case channel_4:                         return "ch4";
            case channel_5:                         return "ch5";
            case channel_6:                         return "ch6";
            case channel_7:                         return "ch7";
            case channel_8:                         return "ch8";
            case channel_9:                         return "ch9";
            case channel_10:                        return "ch10";
            case channel_11:                        return "ch11";
            case channel_12:                        return "ch12";
            case channel_13:                        return "ch13";
            case channel_14:                        return "ch14";
            case channel_15:                        return "ch15";
            case channel_16:                        return "ch16";

            case channel_digital_1:                 return "digital1";
            case channel_digital_2:                 return "digital2";
            case channel_digital_3:                 return "digital3";
            case channel_digital_4:                 return "digital4";
            case channel_digital_5:                 return "digital5";
            case channel_digital_6:                 return "digital6";
            case channel_digital_7:                 return "digital7";
            case channel_digital_8:                 return "digital8";
            case channel_digital_9:                 return "digital9";
            case channel_digital_10:                return "digital10";
            case channel_digital_11:                return "digital11";
            case channel_digital_12:                return "digital12";
            case channel_digital_13:                return "digital13";
            case channel_digital_14:                return "digital14";
            case channel_digital_15:                return "digital15";
            case channel_digital_16:                return "digital16";

            case channel_structuralHealth:          return "structuralHealth";

            case channel_hcl_rawBase_mag1_x:            return "hcl_rawBase_mag1_x";
            case channel_hcl_rawBase_mag1_y:            return "hcl_rawBase_mag1_y";
            case channel_hcl_rawBase_mag1_z:            return "hcl_rawBase_mag1_z";
            case channel_hcl_rawBase_mag2_x:            return "hcl_rawBase_mag2_x";
            case channel_hcl_rawBase_mag2_y:            return "hcl_rawBase_mag2_y";
            case channel_hcl_rawBase_mag2_z:            return "hcl_rawBase_mag2_z";
            case channel_hcl_rawBase_mag3_x:            return "hcl_rawBase_mag3_x";
            case channel_hcl_rawBase_mag3_y:            return "hcl_rawBase_mag3_y";
            case channel_hcl_rawBase_mag3_z:            return "hcl_rawBase_mag3_z";
            case channel_hcl_rawBase_mag4_x:            return "hcl_rawBase_mag4_x";
            case channel_hcl_rawBase_mag4_y:            return "hcl_rawBase_mag4_y";
            case channel_hcl_rawBase_mag4_z:            return "hcl_rawBase_mag4_z";
            case channel_hcl_rawBase_mag5_x:            return "hcl_rawBase_mag5_x";
            case channel_hcl_rawBase_mag5_y:            return "hcl_rawBase_mag5_y";
            case channel_hcl_rawBase_mag5_z:            return "hcl_rawBase_mag5_z";
            case channel_hcl_rawBase_mag6_x:            return "hcl_rawBase_mag6_x";
            case channel_hcl_rawBase_mag6_y:            return "hcl_rawBase_mag6_y";
            case channel_hcl_rawBase_mag6_z:            return "hcl_rawBase_mag6_z";
            case channel_hcl_rawBase_mag7_x:            return "hcl_rawBase_mag7_x";
            case channel_hcl_rawBase_mag7_y:            return "hcl_rawBase_mag7_y";
            case channel_hcl_rawBase_mag7_z:            return "hcl_rawBase_mag7_z";
            case channel_hcl_rawBase_mag8_x:            return "hcl_rawBase_mag8_x";
            case channel_hcl_rawBase_mag8_y:            return "hcl_rawBase_mag8_y";
            case channel_hcl_rawBase_mag8_z:            return "hcl_rawBase_mag8_z";
            case channel_hcl_rawBase_gyro_x:            return "hcl_rawBase_gyro_x";
            case channel_hcl_rawBase_gyro_y:            return "hcl_rawBase_gyro_y";
            case channel_hcl_rawBase_gyro_z:            return "hcl_rawBase_gyro_z";
            case channel_hcl_rawStrain_BL30:            return "hcl_rawStrain_BL30";
            case channel_hcl_rawStrain_BL120:           return "hcl_rawStrain_BL120";
            case channel_hcl_rawStrain_A60:             return "hcl_rawStrain_A60";
            case channel_hcl_rawStrain_A150:            return "hcl_rawStrain_A150";
            case channel_hcl_rawStrain_AL30:            return "hcl_rawStrain_AL30";
            case channel_hcl_rawStrain_AL120:           return "hcl_rawStrain_AL120";
            case channel_hcl_rawStrain_BR60:            return "hcl_rawStrain_BR60";
            case channel_hcl_rawStrain_BR150:           return "hcl_rawStrain_BR150";
            case channel_hcl_rawStrain_B30:             return "hcl_rawStrain_B30";
            case channel_hcl_rawStrain_T120:            return "hcl_rawStrain_T120";
            case channel_hcl_rawStrain_AR60:            return "hcl_rawStrain_AR60";
            case channel_hcl_rawStrain_AR150:           return "hcl_rawStrain_AR150";
            case channel_hcl_rawStrain_A30:             return "hcl_rawStrain_A30";
            case channel_hcl_rawStrain_A120:            return "hcl_rawStrain_A120";
            case channel_hcl_rawStrain_BL90:            return "hcl_rawStrain_BL90";
            case channel_hcl_rawStrain_BL180:           return "hcl_rawStrain_BL180";
            case channel_hcl_rawStrain_BR30:            return "hcl_rawStrain_BR30";
            case channel_hcl_rawStrain_BR120:           return "hcl_rawStrain_BR120";
            case channel_hcl_rawStrain_AL90:            return "hcl_rawStrain_AL90";
            case channel_hcl_rawStrain_AL180:           return "hcl_rawStrain_AL180";
            case channel_hcl_rawStrain_AR30:            return "hcl_rawStrain_AR30";
            case channel_hcl_rawStrain_AR120:           return "hcl_rawStrain_AR120";
            case channel_hcl_rawStrain_B90:             return "hcl_rawStrain_B90";
            case channel_hcl_rawStrain_T0:              return "hcl_rawStrain_T0";
            case channel_hcl_rawStrain_BL60:            return "hcl_rawStrain_BL60";
            case channel_hcl_rawStrain_BL150:           return "hcl_rawStrain_BL150";
            case channel_hcl_rawStrain_A90:             return "hcl_rawStrain_A90";
            case channel_hcl_rawStrain_A0:              return "hcl_rawStrain_A0";
            case channel_hcl_rawStrain_AL60:            return "hcl_rawStrain_AL60";
            case channel_hcl_rawStrain_AL150:           return "hcl_rawStrain_AL150";
            case channel_hcl_rawStrain_BR90:            return "hcl_rawStrain_BR90";
            case channel_hcl_rawStrain_BR0:             return "hcl_rawStrain_BR0";
            case channel_hcl_rawStrain_T60:             return "hcl_rawStrain_T60";
            case channel_hcl_rawStrain_B150:            return "hcl_rawStrain_B150";
            case channel_hcl_rawStrain_AR90:            return "hcl_rawStrain_AR90";
            case channel_hcl_rawStrain_AR0:             return "hcl_rawStrain_AR0";
            case channel_hcl_rawInertial_accel1:        return "hcl_rawInertial_accel1";
            case channel_hcl_rawInertial_accel2:        return "hcl_rawInertial_accel2";
            case channel_hcl_rawInertial_accel3:        return "hcl_rawInertial_accel3";
            case channel_hcl_rawInertial_accel4:        return "hcl_rawInertial_accel4";
            case channel_hcl_rawInertial_accel5:        return "hcl_rawInertial_accel5";
            case channel_hcl_rawInertial_accel6:        return "hcl_rawInertial_accel6";
            case channel_hcl_rawInertial_accel7:        return "hcl_rawInertial_accel7";
            case channel_hcl_rawInertial_accel8:        return "hcl_rawInertial_accel8";
            case channel_hcl_rawInertial_gyroX:         return "hcl_rawInertial_gyroX";
            case channel_hcl_rawInertial_gyroY:         return "hcl_rawInertial_gyroY";
            case channel_hcl_rawInertial_gyroZ:         return "hcl_rawInertial_gyroZ";
            case channel_hcl_axialLoadX:                return "hcl_axialLoadX";
            case channel_hcl_axialLoadY:                return "hcl_axialLoadY";
            case channel_hcl_axialLoadZ:                return "hcl_axialLoadZ";
            case channel_hcl_bendingMomentFlap:         return "hcl_bendingMomentFlap";
            case channel_hcl_bendingMomentLag:          return "hcl_bendingMomentLag";
            case channel_hcl_bendingMomentPitch:        return "hcl_bendingMomentPitch";
            case channel_hcl_motionFlap_mag:            return "hcl_motionFlap_mag";
            case channel_hcl_motionLag_mag:             return "hcl_motionLag_mag";
            case channel_hcl_motionPitch_mag:           return "hcl_motionPitch_mag";
            case channel_hcl_motionFlap_inertial:       return "hcl_motionFlap_inertial";
            case channel_hcl_motionLag_inertial:        return "hcl_motionLag_inertial";
            case channel_hcl_motionPitch_inertial:      return "hcl_motionPitch_inertial";
            case channel_hcl_cockingStiffness_mag:      return "hcl_cockingStiffness_mag";
            case channel_hcl_cockingStiffness_inertial: return "hcl_cockingStiffness_inertial";
            case channel_hcl_temperature:               return "hcl_temperature";

            case channel_rawAngleStrain:            return "rawAngleStrain";
            case channel_beaconEcho:                return "beaconEcho";
            case channel_beaconConflict:            return "beaconConflict";
            case channel_rfSweep:                   return "rfSweep";
            case channel_error_code:                return "errorCode";
            case channel_diag_state:                return "diagnostic_state";
            case channel_diag_runtime_idle:         return "diagnostic_runtime_idle";
            case channel_diag_runtime_sleep:        return "diagnostic_runtime_sleep";
            case channel_diag_runtime_activeRun:    return "diagnostic_runtime_activeRun";
            case channel_diag_runtime_inactiveRun:  return "diagnostic_runtime_inactiveRun";
            case channel_diag_resetCounter:         return "diagnostic_resetCounter";
            case channel_diag_lowBatteryFlag:       return "diagnostic_lowBatteryFlag";
            case channel_diag_sweepIndex:           return "diagnostic_sweepIndex";
            case channel_diag_badSweepCount:        return "diagnostic_badSweepCount";
            case channel_diag_totalTx:              return "diagnostic_totalTx";
            case channel_diag_totalReTx:            return "diagnostic_totalReTx";
            case channel_diag_totalDroppedPackets:  return "diagnostic_totalDroppedPackets";
            case channel_diag_builtInTestResult:    return "diagnostic_builtInTestResult";
            case channel_diag_eventIndex:           return "diagnostic_eventTriggerIndex";
            case channel_diag_externalPower:        return "diagnostic_externalPower";
            case channel_diag_internalTemp:         return "diagnostic_internalTemp";
            case channel_diag_syncAttempts:         return "diagnostic_syncAttempts";
            case channel_diag_syncFailures:         return "diagnostic_syncFailures";
            case channel_diag_secsSinceLastSync:    return "diagnostic_secsSinceLastSync";
            case channel_diag_memoryFull:           return "diagnostic_memoryFull";
            case channel_1_rms:                     return "ch1_rms";
            case channel_2_rms:                     return "ch2_rms";
            case channel_3_rms:                     return "ch3_rms";
            case channel_4_rms:                     return "ch4_rms";
            case channel_5_rms:                     return "ch5_rms";
            case channel_6_rms:                     return "ch6_rms";
            case channel_7_rms:                     return "ch7_rms";
            case channel_8_rms:                     return "ch8_rms";
            case channel_9_rms:                     return "ch9_rms";
            case channel_10_rms:                    return "ch10_rms";
            case channel_11_rms:                    return "ch11_rms";
            case channel_12_rms:                    return "ch12_rms";
            case channel_13_rms:                    return "ch13_rms";
            case channel_14_rms:                    return "ch14_rms";
            case channel_15_rms:                    return "ch15_rms";
            case channel_16_rms:                    return "ch16_rms";
            case channel_1_peakToPeak:              return "ch1_peakToPeak";
            case channel_2_peakToPeak:              return "ch2_peakToPeak";
            case channel_3_peakToPeak:              return "ch3_peakToPeak";
            case channel_4_peakToPeak:              return "ch4_peakToPeak";
            case channel_5_peakToPeak:              return "ch5_peakToPeak";
            case channel_6_peakToPeak:              return "ch6_peakToPeak";
            case channel_7_peakToPeak:              return "ch7_peakToPeak";
            case channel_8_peakToPeak:              return "ch8_peakToPeak";
            case channel_9_peakToPeak:              return "ch9_peakToPeak";
            case channel_10_peakToPeak:             return "ch10_peakToPeak";
            case channel_11_peakToPeak:             return "ch11_peakToPeak";
            case channel_12_peakToPeak:             return "ch12_peakToPeak";
            case channel_13_peakToPeak:             return "ch13_peakToPeak";
            case channel_14_peakToPeak:             return "ch14_peakToPeak";
            case channel_15_peakToPeak:             return "ch15_peakToPeak";
            case channel_16_peakToPeak:             return "ch16_peakToPeak";
            case channel_1_ips:                     return "ch1_ips";
            case channel_2_ips:                     return "ch2_ips";
            case channel_3_ips:                     return "ch3_ips";
            case channel_4_ips:                     return "ch4_ips";
            case channel_5_ips:                     return "ch5_ips";
            case channel_6_ips:                     return "ch6_ips";
            case channel_7_ips:                     return "ch7_ips";
            case channel_8_ips:                     return "ch8_ips";
            case channel_9_ips:                     return "ch9_ips";
            case channel_10_ips:                    return "ch10_ips";
            case channel_11_ips:                    return "ch11_ips";
            case channel_12_ips:                    return "ch12_ips";
            case channel_13_ips:                    return "ch13_ips";
            case channel_14_ips:                    return "ch14_ips";
            case channel_15_ips:                    return "ch15_ips";
            case channel_16_ips:                    return "ch16_ips";
            case channel_1_crestFactor:             return "ch1_crestFactor";
            case channel_2_crestFactor:             return "ch2_crestFactor";
            case channel_3_crestFactor:             return "ch3_crestFactor";
            case channel_4_crestFactor:             return "ch4_crestFactor";
            case channel_5_crestFactor:             return "ch5_crestFactor";
            case channel_6_crestFactor:             return "ch6_crestFactor";
            case channel_7_crestFactor:             return "ch7_crestFactor";
            case channel_8_crestFactor:             return "ch8_crestFactor";
            case channel_9_crestFactor:             return "ch9_crestFactor";
            case channel_10_crestFactor:            return "ch10_crestFactor";
            case channel_11_crestFactor:            return "ch11_crestFactor";
            case channel_12_crestFactor:            return "ch12_crestFactor";
            case channel_13_crestFactor:            return "ch13_crestFactor";
            case channel_14_crestFactor:            return "ch14_crestFactor";
            case channel_15_crestFactor:            return "ch15_crestFactor";
            case channel_16_crestFactor:            return "ch16_crestFactor";
            case channel_1_mean:                    return "ch1_mean";
            case channel_2_mean:                    return "ch2_mean";
            case channel_3_mean:                    return "ch3_mean";
            case channel_4_mean:                    return "ch4_mean";
            case channel_5_mean:                    return "ch5_mean";
            case channel_6_mean:                    return "ch6_mean";
            case channel_7_mean:                    return "ch7_mean";
            case channel_8_mean:                    return "ch8_mean";
            case channel_9_mean:                    return "ch9_mean";
            case channel_10_mean:                   return "ch10_mean";
            case channel_11_mean:                   return "ch11_mean";
            case channel_12_mean:                   return "ch12_mean";
            case channel_13_mean:                   return "ch13_mean";
            case channel_14_mean:                   return "ch14_mean";
            case channel_15_mean:                   return "ch15_mean";
            case channel_16_mean:                   return "ch16_mean";
            case channel_1_mmps:                    return "ch1_mmps";
            case channel_2_mmps:                    return "ch2_mmps";
            case channel_3_mmps:                    return "ch3_mmps";
            case channel_4_mmps:                    return "ch4_mmps";
            case channel_5_mmps:                    return "ch5_mmps";
            case channel_6_mmps:                    return "ch6_mmps";
            case channel_7_mmps:                    return "ch7_mmps";
            case channel_8_mmps:                    return "ch8_mmps";
            case channel_9_mmps:                    return "ch9_mmps";
            case channel_10_mmps:                   return "ch10_mmps";
            case channel_11_mmps:                   return "ch11_mmps";
            case channel_12_mmps:                   return "ch12_mmps";
            case channel_13_mmps:                   return "ch13_mmps";
            case channel_14_mmps:                   return "ch14_mmps";
            case channel_15_mmps:                   return "ch15_mmps";
            case channel_16_mmps:                   return "ch16_mmps";

            default:
                assert(false);
                return "unknown_" + Utils::toStr(channelId);
        }
    }
}
