/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/

#pragma once

#include "WirelessTypes.h"

#include <map>
#include <string>
#include <vector>

namespace mscl
{
    //API Class: WirelessChannel
    //    Represents a channel on a WirelessNode. This can be used to gain information about the channel, view current settings that are applied, and update settings on the Node.
    class WirelessChannel
    {
    public:
        //=====================================================================================================
        //API Enums: ChannelId
        //  channel_unknown                         - 0 - Unknown Channel
        //  channel_1                               - 1 - Channel 1
        //  channel_2                               - 2 - Channel 2
        //  channel_3                               - 3 - Channel 3
        //  channel_4                               - 4 - Channel 4
        //  channel_5                               - 5 - Channel 5
        //  channel_6                               - 6 - Channel 6
        //  channel_7                               - 7 - Channel 7
        //  channel_8                               - 8 - Channel 8
        //  channel_9                               - 9 - Channel 9
        //  channel_10                              - 10 - Channel 10
        //  channel_11                              - 11 - Channel 11
        //  channel_12                              - 12 - Channel 12
        //  channel_13                              - 13 - Channel 13
        //  channel_14                              - 14 - Channel 14
        //  channel_15                              - 15 - Channel 15
        //  channel_16                              - 16 - Channel 16
        //  channel_digital_1                       - 17 - Digital Channel 1
        //  channel_digital_2                       - 18 - Digital Channel 2
        //  channel_digital_3                       - 19 - Digital Channel 3
        //  channel_digital_4                       - 20 - Digital Channel 4
        //  channel_digital_5                       - 21 - Digital Channel 5
        //  channel_digital_6                       - 22 - Digital Channel 6
        //  channel_digital_7                       - 23 - Digital Channel 7
        //  channel_digital_8                       - 24 - Digital Channel 8
        //  channel_digital_9                       - 25 - Digital Channel 9
        //  channel_digital_10                      - 26 - Digital Channel 10
        //  channel_digital_11                      - 27 - Digital Channel 11
        //  channel_digital_12                      - 28 - Digital Channel 12
        //  channel_digital_13                      - 29 - Digital Channel 13
        //  channel_digital_14                      - 30 - Digital Channel 14
        //  channel_digital_15                      - 31 - Digital Channel 15
        //  channel_digital_16                      - 32 - Digital Channel 16
        //  channel_structuralHealth                - 33 - Structural Health Channel
        //  channel_hcl_rawBase_mag1_x              - 34 - HCL Smart Bearing Raw Base - Mag 1 - x
        //  channel_hcl_rawBase_mag1_y              - 35 - HCL Smart Bearing Raw Base - Mag 1 - y
        //  channel_hcl_rawBase_mag1_z              - 36 - HCL Smart Bearing Raw Base - Mag 1 - z
        //  channel_hcl_rawBase_mag2_x              - 37 - HCL Smart Bearing Raw Base - Mag 2 - x
        //  channel_hcl_rawBase_mag2_y              - 38 - HCL Smart Bearing Raw Base - Mag 2 - y
        //  channel_hcl_rawBase_mag2_z              - 39 - HCL Smart Bearing Raw Base - Mag 2 - z
        //  channel_hcl_rawBase_mag3_x              - 40 - HCL Smart Bearing Raw Base - Mag 3 - x
        //  channel_hcl_rawBase_mag3_y              - 41 - HCL Smart Bearing Raw Base - Mag 3 - y
        //  channel_hcl_rawBase_mag3_z              - 42 - HCL Smart Bearing Raw Base - Mag 3 - z
        //  channel_hcl_rawBase_mag4_x              - 43 - HCL Smart Bearing Raw Base - Mag 4 - x
        //  channel_hcl_rawBase_mag4_y              - 44 - HCL Smart Bearing Raw Base - Mag 4 - y
        //  channel_hcl_rawBase_mag4_z              - 45 - HCL Smart Bearing Raw Base - Mag 4 - z
        //  channel_hcl_rawBase_mag5_x              - 46 - HCL Smart Bearing Raw Base - Mag 5 - x
        //  channel_hcl_rawBase_mag5_y              - 47 - HCL Smart Bearing Raw Base - Mag 5 - y
        //  channel_hcl_rawBase_mag5_z              - 48 - HCL Smart Bearing Raw Base - Mag 5 - z
        //  channel_hcl_rawBase_mag6_x              - 49 - HCL Smart Bearing Raw Base - Mag 6 - x
        //  channel_hcl_rawBase_mag6_y              - 50 - HCL Smart Bearing Raw Base - Mag 6 - y
        //  channel_hcl_rawBase_mag6_z              - 51 - HCL Smart Bearing Raw Base - Mag 6 - z
        //  channel_hcl_rawBase_mag7_x              - 52 - HCL Smart Bearing Raw Base - Mag 7 - x
        //  channel_hcl_rawBase_mag7_y              - 53 - HCL Smart Bearing Raw Base - Mag 7 - y
        //  channel_hcl_rawBase_mag7_z              - 54 - HCL Smart Bearing Raw Base - Mag 7 - z
        //  channel_hcl_rawBase_mag8_x              - 55 - HCL Smart Bearing Raw Base - Mag 8 - x
        //  channel_hcl_rawBase_mag8_y              - 56 - HCL Smart Bearing Raw Base - Mag 8 - y
        //  channel_hcl_rawBase_mag8_z              - 57 - HCL Smart Bearing Raw Base - Mag 8 - z
        //  channel_hcl_rawBase_gyro_x              - 58 - HCL Smart Bearing Raw Base - Gyro - x
        //  channel_hcl_rawBase_gyro_y              - 59 - HCL Smart Bearing Raw Base - Gyro - y
        //  channel_hcl_rawBase_gyro_z              - 60 - HCL Smart Bearing Raw Base - Gyro - z
        //  channel_error_code                      - 61 - Error Code
        //  channel_hcl_rawStrain_BL30              - 62 - HCL Smart Bearing Raw Strain - BL30
        //  channel_hcl_rawStrain_BL120             - 63 - HCL Smart Bearing Raw Strain - BL120
        //  channel_hcl_rawStrain_A60               - 64 - HCL Smart Bearing Raw Strain - A60
        //  channel_hcl_rawStrain_A150              - 65 - HCL Smart Bearing Raw Strain - A150
        //  channel_hcl_rawStrain_AL30              - 66 - HCL Smart Bearing Raw Strain - AL30
        //  channel_hcl_rawStrain_AL120             - 67 - HCL Smart Bearing Raw Strain - AL120
        //  channel_hcl_rawStrain_BR60              - 68 - HCL Smart Bearing Raw Strain - BR60
        //  channel_hcl_rawStrain_BR150             - 69 - HCL Smart Bearing Raw Strain - BR150
        //  channel_hcl_rawStrain_B30               - 70 - HCL Smart Bearing Raw Strain - B30
        //  channel_hcl_rawStrain_T120              - 71 - HCL Smart Bearing Raw Strain - T120
        //  channel_hcl_rawStrain_AR60              - 72 - HCL Smart Bearing Raw Strain - AR60
        //  channel_hcl_rawStrain_AR150             - 73 - HCL Smart Bearing Raw Strain - AR150
        //  channel_hcl_rawStrain_A30               - 74 - HCL Smart Bearing Raw Strain - A30
        //  channel_hcl_rawStrain_A120              - 75 - HCL Smart Bearing Raw Strain - A120
        //  channel_hcl_rawStrain_BL90              - 76 - HCL Smart Bearing Raw Strain - BL90
        //  channel_hcl_rawStrain_BL180             - 77 - HCL Smart Bearing Raw Strain - BL180
        //  channel_hcl_rawStrain_BR30              - 78 - HCL Smart Bearing Raw Strain - BR30
        //  channel_hcl_rawStrain_BR120             - 79 - HCL Smart Bearing Raw Strain - BR120
        //  channel_hcl_rawStrain_AL90              - 80 - HCL Smart Bearing Raw Strain - AL90
        //  channel_hcl_rawStrain_AL180             - 81 - HCL Smart Bearing Raw Strain - AL180
        //  channel_hcl_rawStrain_AR30              - 82 - HCL Smart Bearing Raw Strain - AR30
        //  channel_hcl_rawStrain_AR120             - 83 - HCL Smart Bearing Raw Strain - AR120
        //  channel_hcl_rawStrain_B90               - 84 - HCL Smart Bearing Raw Strain - B90
        //  channel_hcl_rawStrain_T0                - 85 - HCL Smart Bearing Raw Strain - T0
        //  channel_hcl_rawStrain_BL60              - 86 - HCL Smart Bearing Raw Strain - BL60
        //  channel_hcl_rawStrain_BL150             - 87 - HCL Smart Bearing Raw Strain - BL150
        //  channel_hcl_rawStrain_A90               - 88 - HCL Smart Bearing Raw Strain - A90
        //  channel_hcl_rawStrain_A0                - 89 - HCL Smart Bearing Raw Strain - A0
        //  channel_hcl_rawStrain_AL60              - 90 - HCL Smart Bearing Raw Strain - AL60
        //  channel_hcl_rawStrain_AL150             - 91 - HCL Smart Bearing Raw Strain - AL150
        //  channel_hcl_rawStrain_BR90              - 92 - HCL Smart Bearing Raw Strain - BR90
        //  channel_hcl_rawStrain_BR0               - 93 - HCL Smart Bearing Raw Strain - BR0
        //  channel_hcl_rawStrain_T60               - 94 - HCL Smart Bearing Raw Strain - T60
        //  channel_hcl_rawStrain_B150              - 95 - HCL Smart Bearing Raw Strain - B150
        //  channel_hcl_rawStrain_AR90              - 96 - HCL Smart Bearing Raw Strain - AR90
        //  channel_hcl_rawStrain_AR0               - 97 - HCL Smart Bearing Raw Strain - AR0
        //  channel_hcl_rawInertial_accel1          - 98 - HCL Smart Bearing Raw Inertial - accel 1
        //  channel_hcl_rawInertial_accel2          - 99 - HCL Smart Bearing Raw Inertial - accel 2
        //  channel_hcl_rawInertial_accel3          - 100 - HCL Smart Bearing Raw Inertial - accel 3
        //  channel_hcl_rawInertial_accel4          - 101 - HCL Smart Bearing Raw Inertial - accel 4
        //  channel_hcl_rawInertial_accel5          - 102 - HCL Smart Bearing Raw Inertial - accel 5
        //  channel_hcl_rawInertial_accel6          - 103 - HCL Smart Bearing Raw Inertial - accel 6
        //  channel_hcl_rawInertial_accel7          - 104 - HCL Smart Bearing Raw Inertial - accel 7
        //  channel_hcl_rawInertial_accel8          - 105 - HCL Smart Bearing Raw Inertial - accel 8
        //  channel_hcl_rawInertial_gyroX           - 106 - HCL Smart Bearing Raw Inertial - gyro X
        //  channel_hcl_rawInertial_gyroY           - 107 - HCL Smart Bearing Raw Inertial - gyro Y
        //  channel_hcl_rawInertial_gyroZ           - 108 - HCL Smart Bearing Raw Inertial - gyro Z
        //  channel_rawAngleStrain                  - 109 - Raw Angle Strain
        //  channel_beaconEcho                      - 110 - Beacon Echo
        //  channel_rfSweep                         - 111 - RF Sweep
        //  channel_diag_state                      - 112 - Diagnostic - current state
        //  channel_diag_runtime_idle               - 113 - Diagnostic - idle run time
        //  channel_diag_runtime_sleep              - 114 - Diagnostic - sleep run time
        //  channel_diag_runtime_activeRun          - 115 - Diagnostic - active run run time
        //  channel_diag_runtime_inactiveRun        - 116 - Diagnostic - inactive run run time
        //  channel_diag_resetCounter               - 117 - Diagnostic - reset counter
        //  channel_diag_lowBatteryFlag             - 118 - Diagnostic - low battery indicator
        //  channel_diag_sweepIndex                 - 119 - Diagnostic - sweep index
        //  channel_diag_badSweepCount              - 120 - Diagnostic - bad sweep count
        //  channel_diag_totalTx                    - 121 - Diagnostic - total transmissions
        //  channel_diag_totalReTx                  - 122 - Diagnostic - total retransmissions
        //  channel_diag_totalDroppedPackets        - 123 - Diagnostic - total dropped packets
        //  channel_diag_builtInTestResult          - 124 - Diagnostic - built in test result
        //  channel_diag_eventIndex                 - 125 - Diagnostic - event trigger index
        //  channel_hcl_axialLoadX                  - 126 - HCL Smart Bearing Cal - Axial Load X
        //  channel_hcl_axialLoadY                  - 127 - HCL Smart Bearing Cal - Axial Load Y
        //  channel_hcl_axialLoadZ                  - 128 - HCL Smart Bearing Cal - Axial Load Z
        //  channel_hcl_bendingMomentFlap           - 129 - HCL Smart Bearing Cal - Bending Moment Flag
        //  channel_hcl_bendingMomentLag            - 130 - HCL Smart Bearing Cal - Bending Moment Lead Lag
        //  channel_hcl_bendingMomentPitch          - 131 - HCL Smart Bearing Cal - Bending Moment Pitch
        //  channel_hcl_motionFlap_mag              - 132 - HCL Smart Bearing Cal - Motion Flap (Mag)
        //  channel_hcl_motionLag_mag               - 133 - HCL Smart Bearing Cal - Motion Lead Lag (Mag)
        //  channel_hcl_motionPitch_mag             - 134 - HCL Smart Bearing Cal - Motion Pitch (Mag)
        //  channel_hcl_motionFlap_inertial         - 135 - HCL Smart Bearing Cal - Motion Flap (Inertial)
        //  channel_hcl_motionLag_inertial          - 136 - HCL Smart Bearing Cal - Motion Lead Lag (Inertial)
        //  channel_hcl_motionPitch_inertial        - 137 - HCL Smart Bearing Cal - Motion Pitch (Inertial)
        //  channel_hcl_cockingStiffness_mag        - 138 - HCL Smart Bearing Cal - Cocking Stiffness (Mag)
        //  channel_hcl_cockingStiffness_inertial   - 139 - HCL Smart Bearing Cal - Cocking Stiffness (Inertial)
        //  channel_hcl_temperature                 - 140 - HCL Smart Bearing Cal - Temperature
        //  channel_diag_externalPower              - 141 - Diagnostic - external power
        //  channel_diag_internalTemp               - 142 - Diagnostic - internal temperature
        //  channel_1_rms                           - 143 - Channel 1 RMS
        //  channel_2_rms                           - 144 - Channel 2 RMS
        //  channel_3_rms                           - 145 - Channel 3 RMS
        //  channel_4_rms                           - 146 - Channel 4 RMS
        //  channel_5_rms                           - 147 - Channel 5 RMS
        //  channel_6_rms                           - 148 - Channel 6 RMS
        //  channel_7_rms                           - 149 - Channel 7 RMS
        //  channel_8_rms                           - 150 - Channel 8 RMS
        //  channel_9_rms                           - 151 - Channel 9 RMS
        //  channel_10_rms                          - 152 - Channel 10 RMS
        //  channel_11_rms                          - 153 - Channel 11 RMS
        //  channel_12_rms                          - 154 - Channel 12 RMS
        //  channel_13_rms                          - 155 - Channel 13 RMS
        //  channel_14_rms                          - 156 - Channel 14 RMS
        //  channel_15_rms                          - 157 - Channel 15 RMS
        //  channel_16_rms                          - 158 - Channel 16 RMS
        //  channel_1_peakToPeak                    - 159 - Channel 1 Peak to Peak
        //  channel_2_peakToPeak                    - 160 - Channel 2 Peak to Peak
        //  channel_3_peakToPeak                    - 161 - Channel 3 Peak to Peak
        //  channel_4_peakToPeak                    - 162 - Channel 4 Peak to Peak
        //  channel_5_peakToPeak                    - 163 - Channel 5 Peak to Peak
        //  channel_6_peakToPeak                    - 164 - Channel 6 Peak to Peak
        //  channel_7_peakToPeak                    - 165 - Channel 7 Peak to Peak
        //  channel_8_peakToPeak                    - 166 - Channel 8 Peak to Peak
        //  channel_9_peakToPeak                    - 167 - Channel 9 Peak to Peak
        //  channel_10_peakToPeak                   - 168 - Channel 10 Peak to Peak
        //  channel_11_peakToPeak                   - 169 - Channel 11 Peak to Peak
        //  channel_12_peakToPeak                   - 170 - Channel 12 Peak to Peak
        //  channel_13_peakToPeak                   - 171 - Channel 13 Peak to Peak
        //  channel_14_peakToPeak                   - 172 - Channel 14 Peak to Peak
        //  channel_15_peakToPeak                   - 173 - Channel 15 Peak to Peak
        //  channel_16_peakToPeak                   - 174 - Channel 16 Peak to Peak
        //  channel_1_ips                           - 175 - Channel 1 Inches Per Second
        //  channel_2_ips                           - 176 - Channel 2 Inches Per Second
        //  channel_3_ips                           - 177 - Channel 3 Inches Per Second
        //  channel_4_ips                           - 178 - Channel 4 Inches Per Second
        //  channel_5_ips                           - 179 - Channel 5 Inches Per Second
        //  channel_6_ips                           - 180 - Channel 6 Inches Per Second
        //  channel_7_ips                           - 181 - Channel 7 Inches Per Second
        //  channel_8_ips                           - 182 - Channel 8 Inches Per Second
        //  channel_9_ips                           - 183 - Channel 9 Inches Per Second
        //  channel_10_ips                          - 184 - Channel 10 Inches Per Second
        //  channel_11_ips                          - 185 - Channel 11 Inches Per Second
        //  channel_12_ips                          - 186 - Channel 12 Inches Per Second
        //  channel_13_ips                          - 187 - Channel 13 Inches Per Second
        //  channel_14_ips                          - 188 - Channel 14 Inches Per Second
        //  channel_15_ips                          - 189 - Channel 15 Inches Per Second
        //  channel_16_ips                          - 190 - Channel 16 Inches Per Second
        //  channel_1_crestFactor                   - 191 - Channel 1 Crest Factor
        //  channel_2_crestFactor                   - 192 - Channel 2 Crest Factor
        //  channel_3_crestFactor                   - 193 - Channel 3 Crest Factor
        //  channel_4_crestFactor                   - 194 - Channel 4 Crest Factor
        //  channel_5_crestFactor                   - 195 - Channel 5 Crest Factor
        //  channel_6_crestFactor                   - 196 - Channel 6 Crest Factor
        //  channel_7_crestFactor                   - 197 - Channel 7 Crest Factor
        //  channel_8_crestFactor                   - 198 - Channel 8 Crest Factor
        //  channel_9_crestFactor                   - 199 - Channel 9 Crest Factor
        //  channel_10_crestFactor                  - 200 - Channel 10 Crest Factor
        //  channel_11_crestFactor                  - 201 - Channel 11 Crest Factor
        //  channel_12_crestFactor                  - 202 - Channel 12 Crest Factor
        //  channel_13_crestFactor                  - 203 - Channel 13 Crest Factor
        //  channel_14_crestFactor                  - 204 - Channel 14 Crest Factor
        //  channel_15_crestFactor                  - 205 - Channel 15 Crest Factor
        //  channel_16_crestFactor                  - 206 - Channel 16 Crest Factor
        //  channel_diag_syncAttempts               - 207 - Diagnostic - Synchronization Attempts
        //  channel_diag_syncFailures               - 208 - Diagnostic - Synchronization Failures
        //  channel_diag_secsSinceLastSync          - 209 - Diagnostic - Seconds since last synchronization
        //  channel_beaconConflict                  - 210 - Conflicting Beacon
        //  channel_1_mean                          - 211 - Channel 1 Mean
        //  channel_2_mean                          - 212 - Channel 2 Mean
        //  channel_3_mean                          - 213 - Channel 3 Mean
        //  channel_4_mean                          - 214 - Channel 4 Mean
        //  channel_5_mean                          - 215 - Channel 5 Mean
        //  channel_6_mean                          - 216 - Channel 6 Mean
        //  channel_7_mean                          - 217 - Channel 7 Mean
        //  channel_8_mean                          - 218 - Channel 8 Mean
        //  channel_9_mean                          - 219 - Channel 9 Mean
        //  channel_10_mean                         - 220 - Channel 10 Mean
        //  channel_11_mean                         - 221 - Channel 11 Mean
        //  channel_12_mean                         - 222 - Channel 12 Mean
        //  channel_13_mean                         - 223 - Channel 13 Mean
        //  channel_14_mean                         - 224 - Channel 14 Mean
        //  channel_15_mean                         - 225 - Channel 15 Mean
        //  channel_16_mean                         - 226 - Channel 16 Mean
        //  channel_1_mmps                          - 227 - Channel 1 Millimeters Per Second
        //  channel_2_mmps                          - 228 - Channel 2 Millimeters Per Second
        //  channel_3_mmps                          - 229 - Channel 3 Millimeters Per Second
        //  channel_4_mmps                          - 230 - Channel 4 Millimeters Per Second
        //  channel_5_mmps                          - 231 - Channel 5 Millimeters Per Second
        //  channel_6_mmps                          - 232 - Channel 6 Millimeters Per Second
        //  channel_7_mmps                          - 233 - Channel 7 Millimeters Per Second
        //  channel_8_mmps                          - 234 - Channel 8 Millimeters Per Second
        //  channel_9_mmps                          - 235 - Channel 9 Millimeters Per Second
        //  channel_10_mmps                         - 236 - Channel 10 Millimeters Per Second
        //  channel_11_mmps                         - 237 - Channel 11 Millimeters Per Second
        //  channel_12_mmps                         - 238 - Channel 12 Millimeters Per Second
        //  channel_13_mmps                         - 239 - Channel 13 Millimeters Per Second
        //  channel_14_mmps                         - 240 - Channel 14 Millimeters Per Second
        //  channel_15_mmps                         - 241 - Channel 15 Millimeters Per Second
        //  channel_16_mmps                         - 242 - Channel 16 Millimeters Per Second
        //  channel_diag_memoryFull                 - 243 - Diagnostic - % Datalogging Memory Full
        //=====================================================================================================
        enum ChannelId
        {
            channel_unknown                         = 0,
            channel_1                               = 1,
            channel_2                               = 2,
            channel_3                               = 3,
            channel_4                               = 4,
            channel_5                               = 5,
            channel_6                               = 6,
            channel_7                               = 7,
            channel_8                               = 8,
            channel_9                               = 9,
            channel_10                              = 10,
            channel_11                              = 11,
            channel_12                              = 12,
            channel_13                              = 13,
            channel_14                              = 14,
            channel_15                              = 15,
            channel_16                              = 16,
            channel_digital_1                       = 17,
            channel_digital_2                       = 18,
            channel_digital_3                       = 19,
            channel_digital_4                       = 20,
            channel_digital_5                       = 21,
            channel_digital_6                       = 22,
            channel_digital_7                       = 23,
            channel_digital_8                       = 24,
            channel_digital_9                       = 25,
            channel_digital_10                      = 26,
            channel_digital_11                      = 27,
            channel_digital_12                      = 28,
            channel_digital_13                      = 29,
            channel_digital_14                      = 30,
            channel_digital_15                      = 31,
            channel_digital_16                      = 32,
            channel_structuralHealth                = 33,
            channel_hcl_rawBase_mag1_x              = 34,
            channel_hcl_rawBase_mag1_y              = 35,
            channel_hcl_rawBase_mag1_z              = 36,
            channel_hcl_rawBase_mag2_x              = 37,
            channel_hcl_rawBase_mag2_y              = 38,
            channel_hcl_rawBase_mag2_z              = 39,
            channel_hcl_rawBase_mag3_x              = 40,
            channel_hcl_rawBase_mag3_y              = 41,
            channel_hcl_rawBase_mag3_z              = 42,
            channel_hcl_rawBase_mag4_x              = 43,
            channel_hcl_rawBase_mag4_y              = 44,
            channel_hcl_rawBase_mag4_z              = 45,
            channel_hcl_rawBase_mag5_x              = 46,
            channel_hcl_rawBase_mag5_y              = 47,
            channel_hcl_rawBase_mag5_z              = 48,
            channel_hcl_rawBase_mag6_x              = 49,
            channel_hcl_rawBase_mag6_y              = 50,
            channel_hcl_rawBase_mag6_z              = 51,
            channel_hcl_rawBase_mag7_x              = 52,
            channel_hcl_rawBase_mag7_y              = 53,
            channel_hcl_rawBase_mag7_z              = 54,
            channel_hcl_rawBase_mag8_x              = 55,
            channel_hcl_rawBase_mag8_y              = 56,
            channel_hcl_rawBase_mag8_z              = 57,
            channel_hcl_rawBase_gyro_x              = 58,
            channel_hcl_rawBase_gyro_y              = 59,
            channel_hcl_rawBase_gyro_z              = 60,
            channel_error_code                      = 61,
            channel_hcl_rawStrain_BL30              = 62,
            channel_hcl_rawStrain_BL120             = 63,
            channel_hcl_rawStrain_A60               = 64,
            channel_hcl_rawStrain_A150              = 65,
            channel_hcl_rawStrain_AL30              = 66,
            channel_hcl_rawStrain_AL120             = 67,
            channel_hcl_rawStrain_BR60              = 68,
            channel_hcl_rawStrain_BR150             = 69,
            channel_hcl_rawStrain_B30               = 70,
            channel_hcl_rawStrain_T120              = 71,
            channel_hcl_rawStrain_AR60              = 72,
            channel_hcl_rawStrain_AR150             = 73,
            channel_hcl_rawStrain_A30               = 74,
            channel_hcl_rawStrain_A120              = 75,
            channel_hcl_rawStrain_BL90              = 76,
            channel_hcl_rawStrain_BL180             = 77,
            channel_hcl_rawStrain_BR30              = 78,
            channel_hcl_rawStrain_BR120             = 79,
            channel_hcl_rawStrain_AL90              = 80,
            channel_hcl_rawStrain_AL180             = 81,
            channel_hcl_rawStrain_AR30              = 82,
            channel_hcl_rawStrain_AR120             = 83,
            channel_hcl_rawStrain_B90               = 84,
            channel_hcl_rawStrain_T0                = 85,
            channel_hcl_rawStrain_BL60              = 86,
            channel_hcl_rawStrain_BL150             = 87,
            channel_hcl_rawStrain_A90               = 88,
            channel_hcl_rawStrain_A0                = 89,
            channel_hcl_rawStrain_AL60              = 90,
            channel_hcl_rawStrain_AL150             = 91,
            channel_hcl_rawStrain_BR90              = 92,
            channel_hcl_rawStrain_BR0               = 93,
            channel_hcl_rawStrain_T60               = 94,
            channel_hcl_rawStrain_B150              = 95,
            channel_hcl_rawStrain_AR90              = 96,
            channel_hcl_rawStrain_AR0               = 97,
            channel_hcl_rawInertial_accel1          = 98,
            channel_hcl_rawInertial_accel2          = 99,
            channel_hcl_rawInertial_accel3          = 100,
            channel_hcl_rawInertial_accel4          = 101,
            channel_hcl_rawInertial_accel5          = 102,
            channel_hcl_rawInertial_accel6          = 103,
            channel_hcl_rawInertial_accel7          = 104,
            channel_hcl_rawInertial_accel8          = 105,
            channel_hcl_rawInertial_gyroX           = 106,
            channel_hcl_rawInertial_gyroY           = 107,
            channel_hcl_rawInertial_gyroZ           = 108,
            channel_rawAngleStrain                  = 109,
            channel_beaconEcho                      = 110,
            channel_rfSweep                         = 111,
            channel_diag_state                      = 112,
            channel_diag_runtime_idle               = 113,
            channel_diag_runtime_sleep              = 114,
            channel_diag_runtime_activeRun          = 115,
            channel_diag_runtime_inactiveRun        = 116,
            channel_diag_resetCounter               = 117,
            channel_diag_lowBatteryFlag             = 118,
            channel_diag_sweepIndex                 = 119,
            channel_diag_badSweepCount              = 120,
            channel_diag_totalTx                    = 121,
            channel_diag_totalReTx                  = 122,
            channel_diag_totalDroppedPackets        = 123,
            channel_diag_builtInTestResult          = 124,
            channel_diag_eventIndex                 = 125,
            channel_hcl_axialLoadX                  = 126,
            channel_hcl_axialLoadY                  = 127,
            channel_hcl_axialLoadZ                  = 128,
            channel_hcl_bendingMomentFlap           = 129,
            channel_hcl_bendingMomentLag            = 130,
            channel_hcl_bendingMomentPitch          = 131,
            channel_hcl_motionFlap_mag              = 132,
            channel_hcl_motionLag_mag               = 133,
            channel_hcl_motionPitch_mag             = 134,
            channel_hcl_motionFlap_inertial         = 135,
            channel_hcl_motionLag_inertial          = 136,
            channel_hcl_motionPitch_inertial        = 137,
            channel_hcl_cockingStiffness_mag        = 138,
            channel_hcl_cockingStiffness_inertial   = 139,
            channel_hcl_temperature                 = 140,
            channel_diag_externalPower              = 141,
            channel_diag_internalTemp               = 142,
            channel_1_rms                           = 143,
            channel_2_rms                           = 144,
            channel_3_rms                           = 145,
            channel_4_rms                           = 146,
            channel_5_rms                           = 147,
            channel_6_rms                           = 148,
            channel_7_rms                           = 149,
            channel_8_rms                           = 150,
            channel_9_rms                           = 151,
            channel_10_rms                          = 152,
            channel_11_rms                          = 153,
            channel_12_rms                          = 154,
            channel_13_rms                          = 155,
            channel_14_rms                          = 156,
            channel_15_rms                          = 157,
            channel_16_rms                          = 158,
            channel_1_peakToPeak                    = 159,
            channel_2_peakToPeak                    = 160,
            channel_3_peakToPeak                    = 161,
            channel_4_peakToPeak                    = 162,
            channel_5_peakToPeak                    = 163,
            channel_6_peakToPeak                    = 164,
            channel_7_peakToPeak                    = 165,
            channel_8_peakToPeak                    = 166,
            channel_9_peakToPeak                    = 167,
            channel_10_peakToPeak                   = 168,
            channel_11_peakToPeak                   = 169,
            channel_12_peakToPeak                   = 170,
            channel_13_peakToPeak                   = 171,
            channel_14_peakToPeak                   = 172,
            channel_15_peakToPeak                   = 173,
            channel_16_peakToPeak                   = 174,
            channel_1_ips                           = 175,
            channel_2_ips                           = 176,
            channel_3_ips                           = 177,
            channel_4_ips                           = 178,
            channel_5_ips                           = 179,
            channel_6_ips                           = 180,
            channel_7_ips                           = 181,
            channel_8_ips                           = 182,
            channel_9_ips                           = 183,
            channel_10_ips                          = 184,
            channel_11_ips                          = 185,
            channel_12_ips                          = 186,
            channel_13_ips                          = 187,
            channel_14_ips                          = 188,
            channel_15_ips                          = 189,
            channel_16_ips                          = 190,
            channel_1_crestFactor                   = 191,
            channel_2_crestFactor                   = 192,
            channel_3_crestFactor                   = 193,
            channel_4_crestFactor                   = 194,
            channel_5_crestFactor                   = 195,
            channel_6_crestFactor                   = 196,
            channel_7_crestFactor                   = 197,
            channel_8_crestFactor                   = 198,
            channel_9_crestFactor                   = 199,
            channel_10_crestFactor                  = 200,
            channel_11_crestFactor                  = 201,
            channel_12_crestFactor                  = 202,
            channel_13_crestFactor                  = 203,
            channel_14_crestFactor                  = 204,
            channel_15_crestFactor                  = 205,
            channel_16_crestFactor                  = 206,
            channel_diag_syncAttempts               = 207,
            channel_diag_syncFailures               = 208,
            channel_diag_secsSinceLastSync          = 209,
            channel_beaconConflict                  = 210,
            channel_1_mean                          = 211,
            channel_2_mean                          = 212,
            channel_3_mean                          = 213,
            channel_4_mean                          = 214,
            channel_5_mean                          = 215,
            channel_6_mean                          = 216,
            channel_7_mean                          = 217,
            channel_8_mean                          = 218,
            channel_9_mean                          = 219,
            channel_10_mean                         = 220,
            channel_11_mean                         = 221,
            channel_12_mean                         = 222,
            channel_13_mean                         = 223,
            channel_14_mean                         = 224,
            channel_15_mean                         = 225,
            channel_16_mean                         = 226,
            channel_1_mmps                          = 227,
            channel_2_mmps                          = 228,
            channel_3_mmps                          = 229,
            channel_4_mmps                          = 230,
            channel_5_mmps                          = 231,
            channel_6_mmps                          = 232,
            channel_7_mmps                          = 233,
            channel_8_mmps                          = 234,
            channel_9_mmps                          = 235,
            channel_10_mmps                         = 236,
            channel_11_mmps                         = 237,
            channel_12_mmps                         = 238,
            channel_13_mmps                         = 239,
            channel_14_mmps                         = 240,
            channel_15_mmps                         = 241,
            channel_16_mmps                         = 242,
            channel_diag_memoryFull                 = 243 
        };

        WirelessChannel();    //default constructor

        //Constructor: WirelessChannel
        //    Creates a WirelessChannel object.
        //
        //Parameters:
        //    chNumber - The channel number (ch1 = 1) of the channel.
        //    id - The <WirelessChannel::ChannelId> of the channel.
        //    type - The <WirelessTypes::ChannelType> of the channel.
        //    description - The description of the channel.
        //    adcResolution will be defaulted to 0.
        WirelessChannel(uint8 chNumber, WirelessChannel::ChannelId id, WirelessTypes::ChannelType type, const std::string& description);

        //Constructor: WirelessChannel
        //    Creates a WirelessChannel object.
        //
        //Parameters:
        //    chNumber - The channel number (ch1 = 1) of the channel.
        //    id - The <WirelessChannel::ChannelId> of the channel.
        //    type - The <WirelessTypes::ChannelType> of the channel.
        //    description - The description of the channel.
        //    adcResolution - the ADC resolution of the channel.
        WirelessChannel(uint8 chNumber, WirelessChannel::ChannelId id, WirelessTypes::ChannelType type, const std::string& description, uint8 adcResolution);

    private:
        //Variable: m_chNumber
        //    The channel number (ch1 = 1) of the channel.
        uint8 m_chNumber;

        //Variable: m_id
        //    The <WirelessChannel::ChannelId> of the channel.
        WirelessChannel::ChannelId m_id;

        //Variable: m_type
        //    The <WirelessTypes::ChannelType> of the channel.
        WirelessTypes::ChannelType m_type;

        //Variable: m_description
        //  The description of the channel.
        std::string m_description;

        //Variable: m_adcResolution
        //  The resolution of the A/D Converter for this channel.
        uint8 m_adcResolution;


    public:
        //API Function: channelNumber
        //    Gets the channel number of this channel on the Node.
        //
        //Returns:
        //    The channel number of this channel on the Node.
        uint8 channelNumber() const;

        //API Function: id
        //    Gets the <WirelessChannel::ChannelId> of this channel.
        //    
        //Returns:
        //    The <WirelessChannel::ChannelId> of this channel.
        WirelessChannel::ChannelId id() const;

        //API Function: type
        //    Gets the <WirelessTypes::ChannelType> of this channel.
        //    
        //Returns:
        //    The <WirelessTypes::ChannelType> of this channel.
        WirelessTypes::ChannelType type() const;

        //API Function: description
        //  Gets the description of this channel (ex. "Acceleration X (ch1)" or "CJC Temperature (ch8)").
        //
        //Returns:
        //  A string description of the channel.
        std::string description() const;

        //API Function: adcResolution
        //    Gets the ADC Resolution of this channel (Ex: 18 for 18-bit). 
        //
        //Returns:
        //    The ADC Resolution of this channel.
        uint8 adcResolution() const;

        //API Function: adcMaxValue
        //    Gets the maximum value output from the ADC for this channel (Ex: 2^18 for 18-bit). 
        //
        //Returns:
        //    The maximum value output from the ADC for this channel.
        uint32 adcMaxValue() const;

        //API Function: name
        //    Gets the name of this channel. 
        //    This is the universal name that should be used for uploading to SensorCloud.
        //
        //Returns:
        //    The name of this channel.
        //
        //Exceptions:
        //    - <Error>: Unknown channel.
        std::string name() const;

#ifndef SWIG
        //Function: channelName
        //    Gets the name of the channel. 
        //    This is the universal name that should be used for uploading to SensorCloud.
        //
        //Returns:
        //    The name of the channel.
        //
        //Exceptions:
        //    - <Error>: Unknown channel.
        static std::string channelName(WirelessChannel::ChannelId channelId);
#endif
    };
    
    //API Typedef: WirelessChannels
    //    A typedef for a vector of <WirelessChannel> objects.
    typedef std::vector<WirelessChannel> WirelessChannels;

    //API Typedef: WirelessPollData
    //  A typedef for a map of <WirelessChannel> to float values, used when polling a Wireless Node.
    typedef std::map<WirelessChannel::ChannelId, float> WirelessPollData;
}