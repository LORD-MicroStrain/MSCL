/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "mscl/MicroStrain/Wireless/Configuration/NodeEepromMap.h"

namespace mscl
{
    const EepromLocation NodeEepromMap::CURRENT_LOG_PAGE                (0, valueType_uint16, "Datalog Page Index");
    const EepromLocation NodeEepromMap::CURRENT_PAGE_OFFSET             (2, valueType_uint16, "Datalog Page Offset");
    const EepromLocation NodeEepromMap::DATA_SETS_STORED                (4, valueType_uint16, "Number of Datalogging Sessions");
    const EepromLocation NodeEepromMap::ACTIVE_CHANNEL_MASK             (12, valueType_uint16, "Active Channel Mask");
    const EepromLocation NodeEepromMap::DATALOG_SAMPLE_RATE             (14, valueType_uint16, "Datalogging Sample Rate");
    const EepromLocation NodeEepromMap::NUM_SWEEPS                      (16, valueType_uint16, "Number of Sweeps");
    const EepromLocation NodeEepromMap::DEFAULT_MODE                    (18, valueType_uint16, "Default Mode");
    const EepromLocation NodeEepromMap::SERIAL_ID                       (20, valueType_uint32, "Serial ID");
    const EepromLocation NodeEepromMap::SAMPLING_MODE                   (24, valueType_uint16, "Sampling Mode");
    const EepromLocation NodeEepromMap::HW_OFFSET_1                     (26, valueType_uint16, "Hardware Offset");
    const EepromLocation NodeEepromMap::HW_OFFSET_2                     (28, valueType_uint16, "Hardware Offset");
    const EepromLocation NodeEepromMap::HW_OFFSET_3                     (30, valueType_uint16, "Hardware Offset");
    const EepromLocation NodeEepromMap::HW_OFFSET_4                     (32, valueType_uint16, "Hardware Offset");
    const EepromLocation NodeEepromMap::SAMPLING_DELAY                  (34, valueType_uint16, "Sampling Delay");
    const EepromLocation NodeEepromMap::TDMA_ADDRESS                    (36, valueType_uint16, "TDMA Address");
    const EepromLocation NodeEepromMap::COLLECTION_MODE                 (38, valueType_uint16, "Collection Mode");
    const EepromLocation NodeEepromMap::NUM_BUFF_PACKETS                (40, valueType_uint16, "Number of Buffered Packets");
    const EepromLocation NodeEepromMap::NUM_RETRAN_ATTEMPTS             (44, valueType_uint16, "Number of Retransmissions");
    const EepromLocation NodeEepromMap::MODEL_NUMBER                    (46, valueType_uint16, "Model Number");
    const EepromLocation NodeEepromMap::MODEL_OPTION                    (48, valueType_uint16, "Model Option");
    const EepromLocation NodeEepromMap::NODE_ADDRESS                    (50, valueType_uint16, "Node Address");
    const EepromLocation NodeEepromMap::SLEEP_INTERVAL                  (66, valueType_uint16, "Sleep Interval");
    const EepromLocation NodeEepromMap::INACTIVE_TIMEOUT                (70, valueType_uint16, "Inactivity Timeout");
    const EepromLocation NodeEepromMap::SAMPLE_RATE                     (72, valueType_uint16, "Sample Rate");
    const EepromLocation NodeEepromMap::DATA_FORMAT                     (76, valueType_uint16, "Data Format");
    const EepromLocation NodeEepromMap::SNIFF_DURATION                  (78, valueType_uint16, "Sniff Duration");
    const EepromLocation NodeEepromMap::FREQUENCY                       (90, valueType_uint16, "Frequency");
    const EepromLocation NodeEepromMap::TX_POWER_LEVEL                  (94, valueType_int16, "Transmit Power");
    const EepromLocation NodeEepromMap::UNLIMITED_SAMPLING              (100, valueType_uint16, "Unlimited Sampling Flag");
    const EepromLocation NodeEepromMap::UNLIMITED_DATALOG               (102, valueType_uint16, "Unlimited Datalogging Flag");
    const EepromLocation NodeEepromMap::FIRMWARE_VER                    (108, valueType_uint16, "Firmware Version");
    const EepromLocation NodeEepromMap::FIRMWARE_VER2                   (110, valueType_uint16, "Firmware Version");
    const EepromLocation NodeEepromMap::LEGACY_MODEL_NUMBER             (112, valueType_uint16, "Model Number");
    const EepromLocation NodeEepromMap::LEGACY_SERIAL_ID                (114, valueType_uint16, "Serial ID");
    const EepromLocation NodeEepromMap::MAX_MEMORY                      (116, valueType_uint16, "Max Memory");
    const EepromLocation NodeEepromMap::MICROCONTROLLER                 (120, valueType_uint16, "Microcontroller");
    const EepromLocation NodeEepromMap::FW_ARCH_VER                     (122, valueType_uint16, "Firmware Arch Version");
    const EepromLocation NodeEepromMap::ASPP_VER_LXRS                   (124, valueType_uint16, "LXRS Protocol Version");
    const EepromLocation NodeEepromMap::ASPP_VER_LXRS_PLUS              (126, valueType_uint16, "LXRS+ Protocol Version");
    const EepromLocation NodeEepromMap::HW_GAIN_1                       (128, valueType_uint16, "Hardware Gain");
    const EepromLocation NodeEepromMap::HW_GAIN_2                       (130, valueType_uint16, "Hardware Gain");
    const EepromLocation NodeEepromMap::FILTER_1                        (130, valueType_uint16, "Filter");
    const EepromLocation NodeEepromMap::HW_GAIN_3                       (132, valueType_uint16, "Hardware Gain");
    const EepromLocation NodeEepromMap::HW_GAIN_4                       (134, valueType_uint16, "Hardware Gain");
    const EepromLocation NodeEepromMap::FILTER_2                        (134, valueType_uint16, "Filter");
    const EepromLocation NodeEepromMap::FLASH_ID                        (136, valueType_uint16, "Flash ID");
    const EepromLocation NodeEepromMap::STORAGE_LIMIT_MODE              (138, valueType_uint16, "Storage Limit Mode");
    const EepromLocation NodeEepromMap::CH_ACTION_ID_1                  (150, valueType_uint16, "Channel Action ID");
    const EepromLocation NodeEepromMap::CH_ACTION_SLOPE_1               (152, valueType_float, "Channel Slope");
    const EepromLocation NodeEepromMap::CH_ACTION_OFFSET_1              (156, valueType_float, "Channel Offset");
    const EepromLocation NodeEepromMap::CH_ACTION_ID_2                  (160, valueType_uint16, "Channel Action ID");
    const EepromLocation NodeEepromMap::CH_ACTION_SLOPE_2               (162, valueType_float, "Channel Slope");
    const EepromLocation NodeEepromMap::CH_ACTION_OFFSET_2              (166, valueType_float, "Channel Offset");
    const EepromLocation NodeEepromMap::CH_ACTION_ID_3                  (170, valueType_uint16, "Channel Action ID");
    const EepromLocation NodeEepromMap::CH_ACTION_SLOPE_3               (172, valueType_float, "Channel Slope");
    const EepromLocation NodeEepromMap::CH_ACTION_OFFSET_3              (176, valueType_float, "Channel Offset");
    const EepromLocation NodeEepromMap::CH_ACTION_ID_4                  (180, valueType_uint16, "Channel Action ID");
    const EepromLocation NodeEepromMap::CH_ACTION_SLOPE_4               (182, valueType_float, "Channel Slope");
    const EepromLocation NodeEepromMap::CH_ACTION_OFFSET_4              (186, valueType_float, "Channel Offset");
    const EepromLocation NodeEepromMap::CH_ACTION_ID_5                  (190, valueType_uint16, "Channel Action ID");
    const EepromLocation NodeEepromMap::CH_ACTION_SLOPE_5               (192, valueType_float, "Channel Slope");
    const EepromLocation NodeEepromMap::CH_ACTION_OFFSET_5              (196, valueType_float, "Channel Offset");
    const EepromLocation NodeEepromMap::CH_ACTION_ID_6                  (200, valueType_uint16, "Channel Action ID");
    const EepromLocation NodeEepromMap::CH_ACTION_SLOPE_6               (202, valueType_float, "Channel Slope");
    const EepromLocation NodeEepromMap::CH_ACTION_OFFSET_6              (206, valueType_float, "Channel Offset");
    const EepromLocation NodeEepromMap::CH_ACTION_ID_7                  (210, valueType_uint16, "Channel Action ID");
    const EepromLocation NodeEepromMap::CH_ACTION_SLOPE_7               (212, valueType_float, "Channel Slope");
    const EepromLocation NodeEepromMap::CH_ACTION_OFFSET_7              (216, valueType_float, "Channel Offset");
    const EepromLocation NodeEepromMap::CH_ACTION_ID_8                  (220, valueType_uint16, "Channel Action ID");
    const EepromLocation NodeEepromMap::CH_ACTION_SLOPE_8               (222, valueType_float, "Channel Slope");
    const EepromLocation NodeEepromMap::CH_ACTION_OFFSET_8              (226, valueType_float, "Channel Offset");
    const EepromLocation NodeEepromMap::LEGACY_BOOTLOAD_PAGE            (230, valueType_uint16, "Bootloader Page");
    const EepromLocation NodeEepromMap::LEGACY_BOOTLOAD_ENABLE_FLAG     (232, valueType_uint16, "Bootloader Enable Flag");
    const EepromLocation NodeEepromMap::LEGACY_BOOTLOAD_CHECKSUM        (234, valueType_uint16, "Bootloader Checksum");
    const EepromLocation NodeEepromMap::LEGACY_BOOTLOADER_VER           (236, valueType_uint16, "Bootloader Version");
    const EepromLocation NodeEepromMap::LEGACY_BOOTLOADER_OPTIONS       (238, valueType_uint16, "Bootloader Options");
    const EepromLocation NodeEepromMap::LEGACY_BOOTLOADER_COUNTER       (240, valueType_uint16, "Bootloader Counter");
    const EepromLocation NodeEepromMap::RESET_COUNTER                   (246, valueType_uint16, "Reset Counter");
    const EepromLocation NodeEepromMap::CYCLE_POWER                     (250, valueType_uint16, "Cycle Power");
    const EepromLocation NodeEepromMap::RADIO_OPTIONS                   (258, valueType_uint16, "Radio Options");
    const EepromLocation NodeEepromMap::LOST_BEACON_TIMEOUT             (260, valueType_uint16, "Lost Beacon Timeout");
    const EepromLocation NodeEepromMap::SYNC_SAMPLE_SETTING             (262, valueType_uint16, "Sync Sampling Setting");
    const EepromLocation NodeEepromMap::TX_PER_GROUP                    (264, valueType_uint16, "Transmissions Per Group");
    const EepromLocation NodeEepromMap::GROUP_SIZE                      (266, valueType_uint16, "Group Size");
    const EepromLocation NodeEepromMap::TIME_BETW_SESSIONS              (268, valueType_uint16, "Time Between Sessions");
    const EepromLocation NodeEepromMap::NODE_RETRANSMIT                 (272, valueType_uint16, "Node Retransmission");
    const EepromLocation NodeEepromMap::MAX_RETRANS_PACKET              (274, valueType_uint16, "Max Retransmissions per Packet");
    const EepromLocation NodeEepromMap::MAX_RETRANS_BURST               (276, valueType_uint16, "Max Retransmissions per Burst");
    const EepromLocation NodeEepromMap::REGION_CODE                     (280, valueType_uint16, "Region Code");
    const EepromLocation NodeEepromMap::DATA_MODE                       (282, valueType_uint16, "Data Mode");
    const EepromLocation NodeEepromMap::DERIVED_DATA_RATE               (284, valueType_uint16, "Derived Data Rate");
    const EepromLocation NodeEepromMap::DERIVED_RMS_MASK                (286, valueType_uint16, "Derived RMS Mask");
    const EepromLocation NodeEepromMap::DERIVED_P2P_MASK                (288, valueType_uint16, "Derived P2P Mask");
    const EepromLocation NodeEepromMap::DERIVED_VELOCITY_MASK           (290, valueType_uint16, "Derived Velocity Mask");
    const EepromLocation NodeEepromMap::DATA_PACKET_FORMAT              (292, valueType_uint16, "Data Packet Format");
    const EepromLocation NodeEepromMap::DERIVED_CREST_FACTOR_MASK       (294, valueType_uint16, "Derived Crest Factor Mask");
    const EepromLocation NodeEepromMap::DERIVED_MEAN_MASK               (296, valueType_uint16, "Derived Mean Mask");
    const EepromLocation NodeEepromMap::DIAGNOSTIC_INTERVAL             (300, valueType_uint16, "Diagnostic Interval");
    const EepromLocation NodeEepromMap::THERMOCPL_TYPE                  (306, valueType_uint16, "Thermocouple Type");
    const EepromLocation NodeEepromMap::DERIVED_VELOCITY_UNIT           (310, valueType_uint16, "Derived Velocity Unit");
    const EepromLocation NodeEepromMap::EVENT_SAMPLE_RATE               (328, valueType_uint16, "Event Sampling Rate");
    const EepromLocation NodeEepromMap::EVENT_TRIGGER_MASK              (330, valueType_uint16, "Event Trigger Mask");
    const EepromLocation NodeEepromMap::EVENT_PRE_DURATION              (332, valueType_uint16, "Event Pre Duration");
    const EepromLocation NodeEepromMap::EVENT_POST_DURATION             (334, valueType_uint16, "Event Post Duration");
    const EepromLocation NodeEepromMap::EVENT_SRC_1                     (336, valueType_uint16, "Event Source");
    const EepromLocation NodeEepromMap::EVENT_OPER_1                    (338, valueType_uint16, "Event Operation");
    const EepromLocation NodeEepromMap::EVENT_VAL1_1                    (340, valueType_uint16, "Event Value");
    const EepromLocation NodeEepromMap::EVENT_VAL2_1                    (342, valueType_uint16, "Event Value");
    const EepromLocation NodeEepromMap::EVENT_SRC_2                     (344, valueType_uint16, "Event Source");
    const EepromLocation NodeEepromMap::EVENT_OPER_2                    (346, valueType_uint16, "Event Operation");
    const EepromLocation NodeEepromMap::EVENT_VAL1_2                    (348, valueType_uint16, "Event Value");
    const EepromLocation NodeEepromMap::EVENT_VAL2_2                    (350, valueType_uint16, "Event Value");
    const EepromLocation NodeEepromMap::EVENT_SRC_3                     (352, valueType_uint16, "Event Source");
    const EepromLocation NodeEepromMap::EVENT_OPER_3                    (354, valueType_uint16, "Event Operation");
    const EepromLocation NodeEepromMap::EVENT_VAL1_3                    (356, valueType_uint16, "Event Value");
    const EepromLocation NodeEepromMap::EVENT_VAL2_3                    (358, valueType_uint16, "Event Value");
    const EepromLocation NodeEepromMap::EVENT_SRC_4                     (360, valueType_uint16, "Event Source");
    const EepromLocation NodeEepromMap::EVENT_OPER_4                    (362, valueType_uint16, "Event Operation");
    const EepromLocation NodeEepromMap::EVENT_VAL1_4                    (364, valueType_uint16, "Event Value");
    const EepromLocation NodeEepromMap::EVENT_VAL2_4                    (366, valueType_uint16, "Event Value");
    const EepromLocation NodeEepromMap::EVENT_SRC_5                     (368, valueType_uint16, "Event Source");
    const EepromLocation NodeEepromMap::EVENT_OPER_5                    (370, valueType_uint16, "Event Operation");
    const EepromLocation NodeEepromMap::EVENT_VAL1_5                    (372, valueType_uint16, "Event Value");
    const EepromLocation NodeEepromMap::EVENT_VAL2_5                    (374, valueType_uint16, "Event Value");
    const EepromLocation NodeEepromMap::EVENT_SRC_6                     (376, valueType_uint16, "Event Source");
    const EepromLocation NodeEepromMap::EVENT_OPER_6                    (378, valueType_uint16, "Event Operation");
    const EepromLocation NodeEepromMap::EVENT_VAL1_6                    (380, valueType_uint16, "Event Value");
    const EepromLocation NodeEepromMap::EVENT_VAL2_6                    (382, valueType_uint16, "Event Value");
    const EepromLocation NodeEepromMap::EVENT_SRC_7                     (384, valueType_uint16, "Event Source");
    const EepromLocation NodeEepromMap::EVENT_OPER_7                    (386, valueType_uint16, "Event Operation");
    const EepromLocation NodeEepromMap::EVENT_VAL1_7                    (388, valueType_uint16, "Event Value");
    const EepromLocation NodeEepromMap::EVENT_VAL2_7                    (390, valueType_uint16, "Event Value");
    const EepromLocation NodeEepromMap::EVENT_SRC_8                     (392, valueType_uint16, "Event Source");
    const EepromLocation NodeEepromMap::EVENT_OPER_8                    (394, valueType_uint16, "Event Operation");
    const EepromLocation NodeEepromMap::EVENT_VAL1_8                    (396, valueType_uint16, "Event Value");
    const EepromLocation NodeEepromMap::EVENT_VAL2_8                    (398, valueType_uint16, "Event Value");
    const EepromLocation NodeEepromMap::EXCITATION_VOLTAGE              (410, valueType_uint16, "Excitation Voltage");
    const EepromLocation NodeEepromMap::DEBOUNCE_FILTER                 (430, valueType_uint16, "Debounce Filter");
    const EepromLocation NodeEepromMap::INTERNAL_PULLUP_RESISTOR        (432, valueType_uint16, "Internal Pull-up Resistor");
    const EepromLocation NodeEepromMap::SENSOR_MODE                     (438, valueType_uint16, "Sensor Mode");
    const EepromLocation NodeEepromMap::ANTI_ALIASING_FILTER_1          (440, valueType_uint16, "Anti-Aliasing Filter");
    const EepromLocation NodeEepromMap::ANTI_ALIASING_FILTER_2          (442, valueType_uint16, "Anti-Aliasing Filter");
    const EepromLocation NodeEepromMap::ANTI_ALIASING_FILTER_3          (444, valueType_uint16, "Anti-Aliasing Filter");
    const EepromLocation NodeEepromMap::ANTI_ALIASING_FILTER_4          (446, valueType_uint16, "Anti-Aliasing Filter");
    const EepromLocation NodeEepromMap::LOW_PASS_FILTER_1               (448, valueType_uint16, "Low Pass Filter");
    const EepromLocation NodeEepromMap::LOW_PASS_FILTER_2               (450, valueType_uint16, "Low Pass Filter");
    const EepromLocation NodeEepromMap::LOW_PASS_FILTER_3               (452, valueType_uint16, "Low Pass Filter");
    const EepromLocation NodeEepromMap::LOW_PASS_FILTER_4               (454, valueType_uint16, "Low Pass Filter");
    const EepromLocation NodeEepromMap::HW_GAIN_5                       (456, valueType_uint16, "Hardware Gain");
    const EepromLocation NodeEepromMap::HW_GAIN_6                       (458, valueType_uint16, "Hardware Gain");
    const EepromLocation NodeEepromMap::HW_GAIN_7                       (460, valueType_uint16, "Hardware Gain");
    const EepromLocation NodeEepromMap::HW_GAIN_8                       (462, valueType_uint16, "Hardware Gain");
    const EepromLocation NodeEepromMap::HIGH_PASS_FILTER_1              (464, valueType_uint16, "High Pass Filter");
    const EepromLocation NodeEepromMap::HIGH_PASS_FILTER_2              (466, valueType_uint16, "High Pass Filter");
    const EepromLocation NodeEepromMap::HIGH_PASS_FILTER_3              (468, valueType_uint16, "High Pass Filter");
    const EepromLocation NodeEepromMap::HIGH_PASS_FILTER_4              (470, valueType_uint16, "High Pass Filter");
    const EepromLocation NodeEepromMap::MIN_SOFT_VER_MAJOR              (480, valueType_uint16, "Min Software Version");
    const EepromLocation NodeEepromMap::MIN_SOFT_VER_MINOR              (482, valueType_uint16, "Min Software Version");
    const EepromLocation NodeEepromMap::HW_OFFSET_5                     (504, valueType_uint16, "Hardware Offset");
    const EepromLocation NodeEepromMap::HW_OFFSET_6                     (506, valueType_uint16, "Hardware Offset");
    const EepromLocation NodeEepromMap::HW_OFFSET_7                     (508, valueType_uint16, "Hardware Offset");
    const EepromLocation NodeEepromMap::HW_OFFSET_8                     (510, valueType_uint16, "Hardware Offset");
    const EepromLocation NodeEepromMap::LEGACY_DAMAGE_ANGLE_1           (676, valueType_uint16, "Damage Angle");
    const EepromLocation NodeEepromMap::LEGACY_DAMAGE_ANGLE_2           (678, valueType_uint16, "Damage Angle");
    const EepromLocation NodeEepromMap::LEGACY_DAMAGE_ANGLE_3           (680, valueType_uint16, "Damage Angle");
    const EepromLocation NodeEepromMap::BIN_SIZE                        (682, valueType_uint16, "Bin Size");
    const EepromLocation NodeEepromMap::RESET_BINS                      (684, valueType_uint16, "Reset Bins");
    const EepromLocation NodeEepromMap::BIN_START                       (686, valueType_uint16, "Bin Start");
    const EepromLocation NodeEepromMap::PEAK_VALLEY_THRES               (688, valueType_uint16, "Peak Valley Threshold");
    const EepromLocation NodeEepromMap::SNCURVE_LOGA_1                  (700, valueType_float, "SN Curve Log A");
    const EepromLocation NodeEepromMap::SNCURVE_M_1                     (704, valueType_float, "SN Curve M");
    const EepromLocation NodeEepromMap::SNCURVE_LOGA_2                  (708, valueType_float, "SN Curve Log A");
    const EepromLocation NodeEepromMap::SNCURVE_M_2                     (712, valueType_float, "SN Curve M");
    const EepromLocation NodeEepromMap::SNCURVE_LOGA_3                  (716, valueType_float, "SN Curve Log A");
    const EepromLocation NodeEepromMap::SNCURVE_M_3                     (720, valueType_float, "SN Curve M");
    const EepromLocation NodeEepromMap::YOUNGS_MODULUS                  (724, valueType_float, "Youngs Modulus");
    const EepromLocation NodeEepromMap::POISSONS_RATIO                  (728, valueType_float, "Poissons Ratio");
    const EepromLocation NodeEepromMap::HISTOGRAM_SAMPLE_RATE           (732, valueType_uint16, "Histogram Sample Rate");
    const EepromLocation NodeEepromMap::DAMAGE_ANGLE_1                  (734, valueType_float, "Damage Angle 1");
    const EepromLocation NodeEepromMap::DAMAGE_ANGLE_2                  (738, valueType_float, "Damage Angle 2");
    const EepromLocation NodeEepromMap::DAMAGE_ANGLE_3                  (742, valueType_float, "Damage Angle 3");
    const EepromLocation NodeEepromMap::FATIGUE_MODE                    (746, valueType_uint16, "Fatigue Mode");
    const EepromLocation NodeEepromMap::DIST_ANGLE_NUM_ANGLES           (748, valueType_uint16, "Distributed Number of Angles");
    const EepromLocation NodeEepromMap::DIST_ANGLE_LOWER_BOUND          (750, valueType_float, "Distributed Lower Bound");
    const EepromLocation NodeEepromMap::DIST_ANGLE_UPPER_BOUND          (754, valueType_float, "Distributed Upper Bound");
    const EepromLocation NodeEepromMap::SNCURVE_LOGA_4                  (758, valueType_float, "SN Curve Log A");
    const EepromLocation NodeEepromMap::SNCURVE_M_4                     (762, valueType_float, "SN Curve M");
    const EepromLocation NodeEepromMap::SNCURVE_LOGA_5                  (766, valueType_float, "SN Curve Log A");
    const EepromLocation NodeEepromMap::SNCURVE_M_5                     (770, valueType_float, "SN Curve M");
    const EepromLocation NodeEepromMap::GAUGE_FACTOR_1                  (782, valueType_float, "Gauge Factor");
    const EepromLocation NodeEepromMap::GAUGE_FACTOR_2                  (786, valueType_float, "Gauge Factor");
    const EepromLocation NodeEepromMap::GAUGE_FACTOR_3                  (790, valueType_float, "Gauge Factor");
    const EepromLocation NodeEepromMap::GAUGE_FACTOR_4                  (794, valueType_float, "Gauge Factor");
    const EepromLocation NodeEepromMap::HISTOGRAM_RAW_FLAG              (826, valueType_uint16, "Histogram Raw Flag");
    const EepromLocation NodeEepromMap::ACT_SENSE_ENABLE                (834, valueType_uint16, "Activity Sense Flag");
    const EepromLocation NodeEepromMap::ACT_SENSE_ACTIVE_THRES          (836, valueType_float, "Activity Sense Active Threshold");
    const EepromLocation NodeEepromMap::ACT_SENSE_INACTIVE_TIMEOUT      (840, valueType_float, "Activity Sense Inactive Timeout");
    const EepromLocation NodeEepromMap::ACT_SENSE_ACTIVE_TIME           (844, valueType_float, "Activity Sense Active Time");
    const EepromLocation NodeEepromMap::ACT_SENSE_INACTIVE_THRES        (848, valueType_float, "Activity Sense Inactive Threshold");
    const EepromLocation NodeEepromMap::HISTOGRAM_ENABLE                (852, valueType_uint16, "Histogram Enable Flag");
    const EepromLocation NodeEepromMap::GAUGE_RESISTANCE                (854, valueType_uint16, "Gauge Resistance");
    const EepromLocation NodeEepromMap::NUM_ACTIVE_GAUGES               (864, valueType_uint16, "Number of Active Gauges");
    const EepromLocation NodeEepromMap::LOW_BATTERY_THRESHOLD           (866, valueType_float, "Low Battery Threshold");
    const EepromLocation NodeEepromMap::CH_ACTION_ID_9                  (900, valueType_uint16, "Channel Action ID");
    const EepromLocation NodeEepromMap::CH_ACTION_SLOPE_9               (902, valueType_float, "Channel Slope");
    const EepromLocation NodeEepromMap::CH_ACTION_OFFSET_9              (906, valueType_float, "Channel Offset");
    const EepromLocation NodeEepromMap::CH_ACTION_ID_10                 (910, valueType_uint16, "Channel Action ID");
    const EepromLocation NodeEepromMap::CH_ACTION_SLOPE_10              (912, valueType_float, "Channel Slope");
    const EepromLocation NodeEepromMap::CH_ACTION_OFFSET_10             (916, valueType_float, "Channel Offset");
    const EepromLocation NodeEepromMap::CH_ACTION_ID_11                 (920, valueType_uint16, "Channel Action ID");
    const EepromLocation NodeEepromMap::CH_ACTION_SLOPE_11              (922, valueType_float, "Channel Slope");
    const EepromLocation NodeEepromMap::CH_ACTION_OFFSET_11             (926, valueType_float, "Channel Offset");
    const EepromLocation NodeEepromMap::CH_ACTION_ID_12                 (930, valueType_uint16, "Channel Action ID");
    const EepromLocation NodeEepromMap::CH_ACTION_SLOPE_12              (932, valueType_float, "Channel Slope");
    const EepromLocation NodeEepromMap::CH_ACTION_OFFSET_12             (936, valueType_float, "Channel Offset");
    const EepromLocation NodeEepromMap::CH_ACTION_ID_13                 (940, valueType_uint16, "Channel Action ID");
    const EepromLocation NodeEepromMap::CH_ACTION_SLOPE_13              (942, valueType_float, "Channel Slope");
    const EepromLocation NodeEepromMap::CH_ACTION_OFFSET_13             (946, valueType_float, "Channel Offset");
    const EepromLocation NodeEepromMap::CH_ACTION_ID_14                 (950, valueType_uint16, "Channel Action ID");
    const EepromLocation NodeEepromMap::CH_ACTION_SLOPE_14              (952, valueType_float, "Channel Slope");
    const EepromLocation NodeEepromMap::CH_ACTION_OFFSET_14             (956, valueType_float, "Channel Offset");
    const EepromLocation NodeEepromMap::CH_ACTION_ID_15                 (960, valueType_uint16, "Channel Action ID");
    const EepromLocation NodeEepromMap::CH_ACTION_SLOPE_15              (962, valueType_float, "Channel Slope");
    const EepromLocation NodeEepromMap::CH_ACTION_OFFSET_15             (966, valueType_float, "Channel Offset");
    const EepromLocation NodeEepromMap::CH_ACTION_ID_16                 (970, valueType_uint16, "Channel Action ID");
    const EepromLocation NodeEepromMap::CH_ACTION_SLOPE_16              (972, valueType_float, "Channel Slope");
    const EepromLocation NodeEepromMap::CH_ACTION_OFFSET_16             (976, valueType_float, "Channel Offset");
    const EepromLocation NodeEepromMap::COMM_PROTOCOL                   (1024, valueType_uint16, "Communication Protocol");
    const EepromLocation NodeEepromMap::BOOTLOADER_VER                  (1030, valueType_uint16, "Bootloader Version");
    const EepromLocation NodeEepromMap::FIRMWARE_UPGRADE_FLAGS          (1032, valueType_uint16, "Firmware Upgrade Flags");
    const EepromLocation NodeEepromMap::BOOTLOADER_FLASH_ADDRESS        (1036, valueType_uint32, "Bootloader Flash Address");
    const EepromLocation NodeEepromMap::TEMP_SENSOR_CONFIG_1            (1100, valueType_uint16, "Temp Sensor Config");
    const EepromLocation NodeEepromMap::TEMP_SENSOR_CONFIG_2            (1102, valueType_uint16, "Temp Sensor Config");
    const EepromLocation NodeEepromMap::TEMP_SENSOR_CONFIG_3            (1104, valueType_uint16, "Temp Sensor Config");
    const EepromLocation NodeEepromMap::TEMP_SENSOR_CONFIG_4            (1106, valueType_uint16, "Temp Sensor Config");
    const EepromLocation NodeEepromMap::TEMP_SENSOR_CONFIG_5            (1108, valueType_uint16, "Temp Sensor Config");
    const EepromLocation NodeEepromMap::TEMP_SENSOR_CONFIG_6            (1110, valueType_uint16, "Temp Sensor Config");
    const EepromLocation NodeEepromMap::TEMP_SENSOR_CONFIG_7            (1112, valueType_uint16, "Temp Sensor Config");
    const EepromLocation NodeEepromMap::TEMP_SENSOR_CONFIG_8            (1114, valueType_uint16, "Temp Sensor Config");
    const EepromLocation NodeEepromMap::TEMP_SENSOR_CONFIG_9            (1116, valueType_uint16, "Temp Sensor Config");
    const EepromLocation NodeEepromMap::TEMP_SENSOR_CONFIG_10           (1118, valueType_uint16, "Temp Sensor Config");
    const EepromLocation NodeEepromMap::TEMP_SENSOR_CONFIG_11           (1120, valueType_uint16, "Temp Sensor Config");
    const EepromLocation NodeEepromMap::TEMP_SENSOR_CONFIG_12           (1122, valueType_uint16, "Temp Sensor Config");
    const EepromLocation NodeEepromMap::TEMP_SENSOR_CONFIG_13           (1124, valueType_uint16, "Temp Sensor Config");
    const EepromLocation NodeEepromMap::TEMP_SENSOR_CONFIG_14           (1126, valueType_uint16, "Temp Sensor Config");
    const EepromLocation NodeEepromMap::TEMP_SENSOR_CONFIG_15           (1128, valueType_uint16, "Temp Sensor Config");
    const EepromLocation NodeEepromMap::TEMP_SENSOR_CONFIG_16           (1130, valueType_uint16, "Temp Sensor Config");
    const EepromLocation NodeEepromMap::FACTORY_CH_ACTION_ID_1          (1140, valueType_uint16, "Channel Factory Action ID");
    const EepromLocation NodeEepromMap::FACTORY_CH_ACTION_SLOPE_1       (1142, valueType_float, "Factory Channel Slope");
    const EepromLocation NodeEepromMap::FACTORY_CH_ACTION_OFFSET_1      (1146, valueType_float, "Factory Channel Offset");
    const EepromLocation NodeEepromMap::FACTORY_CH_ACTION_ID_2          (1150, valueType_uint16, "Factory Channel Action ID");
    const EepromLocation NodeEepromMap::FACTORY_CH_ACTION_SLOPE_2       (1152, valueType_float, "Factory Channel Slope");
    const EepromLocation NodeEepromMap::FACTORY_CH_ACTION_OFFSET_2      (1156, valueType_float, "Factory Channel Offset");
    const EepromLocation NodeEepromMap::FACTORY_CH_ACTION_ID_3          (1160, valueType_uint16, "Factory Channel Action ID");
    const EepromLocation NodeEepromMap::FACTORY_CH_ACTION_SLOPE_3       (1162, valueType_float, "Factory Channel Slope");
    const EepromLocation NodeEepromMap::FACTORY_CH_ACTION_OFFSET_3      (1166, valueType_float, "Factory Channel Offset");
    const EepromLocation NodeEepromMap::FACTORY_CH_ACTION_ID_4          (1170, valueType_uint16, "Factory Channel Action ID");
    const EepromLocation NodeEepromMap::FACTORY_CH_ACTION_SLOPE_4       (1172, valueType_float, "Factory Channel Slope");
    const EepromLocation NodeEepromMap::FACTORY_CH_ACTION_OFFSET_4      (1176, valueType_float, "Factory Channel Offset");
    const EepromLocation NodeEepromMap::FACTORY_CH_ACTION_ID_5          (1180, valueType_uint16, "Factory Channel Action ID");
    const EepromLocation NodeEepromMap::FACTORY_CH_ACTION_SLOPE_5       (1182, valueType_float, "Factory Channel Slope");
    const EepromLocation NodeEepromMap::FACTORY_CH_ACTION_OFFSET_5      (1186, valueType_float, "Factory Channel Offset");
    const EepromLocation NodeEepromMap::FACTORY_CH_ACTION_ID_6          (1190, valueType_uint16, "Factory Channel Action ID");
    const EepromLocation NodeEepromMap::FACTORY_CH_ACTION_SLOPE_6       (1192, valueType_float, "Factory Channel Slope");
    const EepromLocation NodeEepromMap::FACTORY_CH_ACTION_OFFSET_6      (1196, valueType_float, "Factory Channel Offset");
    const EepromLocation NodeEepromMap::FACTORY_CH_ACTION_ID_7          (1200, valueType_uint16, "Factory Channel Action ID");
    const EepromLocation NodeEepromMap::FACTORY_CH_ACTION_SLOPE_7       (1202, valueType_float, "Factory Channel Slope");
    const EepromLocation NodeEepromMap::FACTORY_CH_ACTION_OFFSET_7      (1206, valueType_float, "Factory Channel Offset");
    const EepromLocation NodeEepromMap::FACTORY_CH_ACTION_ID_8          (1210, valueType_uint16, "Factory Channel Action ID");
    const EepromLocation NodeEepromMap::FACTORY_CH_ACTION_SLOPE_8       (1212, valueType_float, "Factory Channel Slope");
    const EepromLocation NodeEepromMap::FACTORY_CH_ACTION_OFFSET_8      (1216, valueType_float, "Factory Channel Offset");

    bool NodeEepromMap::canUseCache_read(uint16 eepromLocation)
    {
        switch(eepromLocation)
        {
            //eeprom locations that should always be updated by reading from the device when requested
            case 0:         //CURRENT_LOG_PAGE
            case 2:         //CURRENT_PAGE_OFFSET
            case 4:         //DATA_SETS_STORED
            case 246:       //RESET_COUNTER
            case 1030:
            case 1040:      //BUILT_IN_TEST
                return false;

            //all other eeprom locations can be cached reliably
            default:
                return true;
        }
    }

    bool NodeEepromMap::canUseCache_write(uint16 eepromLocation)
    {
        switch(eepromLocation)
        {
            //eeprom locations that should always be written to the device, never using the cache to check if its the same value
            case 250:    //CYCLE_POWER
            case 90:     //FREQUENCY
            case 684:    //RESET_BINS
            case 1024:   //RADIO_MODE
            case 1030:
                return false;

            //all other eeprom locations can use the cache
            default:
                return true;
        }
    }

    EepromLocation NodeEepromMap::getOffsetEeprom(const EepromLocation& slopeEeprom)
    {
        //difference between eeprom locations (slope to offset)
        static const uint16 eepromDiff = CH_ACTION_OFFSET_1.location() - CH_ACTION_SLOPE_1.location();

        //difference between ids (slope to offset)
        static const uint16 idDiff = CH_ACTION_OFFSET_1.id() - CH_ACTION_SLOPE_1.id();

        return EepromLocation(slopeEeprom.id() + idDiff, slopeEeprom.location() + eepromDiff, CH_ACTION_OFFSET_1.valueType(), CH_ACTION_OFFSET_1.description());
    }

    void NodeEepromMap::getEventTriggerEeproms(uint8 triggerIndex, bool isFloatVal, EepromLocation& channel, EepromLocation& type, EepromLocation& value)
    {
        //difference between trigger groups
        const uint16 eepromDiff = (EVENT_SRC_2.location() - EVENT_SRC_1.location()) * triggerIndex;

        //difference between trigger ids
        const uint16 idDiff = (EVENT_SRC_2.id() - EVENT_SRC_1.id()) * triggerIndex;

        //older nodes use this as a uint16, new nodes use the location as a float
        ValueType eventValType = valueType_uint16;
        if(isFloatVal)
        {
            eventValType = valueType_float;
        }

        //build the eeproms using the offsets
        EepromLocation channelEeprom(EVENT_SRC_1.id() + idDiff, EVENT_SRC_1.location() + eepromDiff, EVENT_SRC_1.valueType(), EVENT_SRC_1.description());
        EepromLocation typeEeprom(EVENT_OPER_1.id() + idDiff, EVENT_OPER_1.location() + eepromDiff, EVENT_OPER_1.valueType(), EVENT_OPER_1.description());
        EepromLocation valueEeprom(EVENT_VAL1_1.id() + idDiff, EVENT_VAL1_1.location() + eepromDiff, eventValType, EVENT_VAL1_1.description());

        //reassign the results
        channel = channelEeprom;
        type = typeEeprom;
        value = valueEeprom;
    }
}
