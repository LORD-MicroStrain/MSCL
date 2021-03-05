/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "EepromLocation.h"
#include "mscl/MicroStrain/Wireless/WirelessModels.h"

namespace mscl
{
    //Class: NodeEepromMap
    //    Contains information on every EEPROM available on Wireless Nodes
    class NodeEepromMap
    {
    private:
        NodeEepromMap() = delete;                                   //disabled default constructor
        NodeEepromMap(const NodeEepromMap&) = delete;               //disabled copy constructor
        NodeEepromMap& operator=(const NodeEepromMap&) = delete;    //disabled assignement operator

    public:
        //Function: canUseCache_read
        //    Gets whether or not the specified eeprom location can use the eeprom cache for reading, or should always be read from the Node.
        //
        //Parameters:
        //    eepromLocation - The eepromLocation that is in question
        //
        //Returns:
        //    true if the location can use the cache for reading, false if the location should be read from the Node.
        static bool canUseCache_read(uint16 eepromLocation);

        //Function: canUseCache_write
        //    Gets whether or not the specified eeprom location can use the eeprom cache for writing, or should always be written to the Node.
        //
        //Parameters:
        //    eepromLocation - The eepromLocation that is in question
        //
        //Returns:
        //    true if the location can use the cache for writing, false if the location should always be written to the Node.
        static bool canUseCache_write(uint16 eepromLocation);

        //Function: getOffsetEeprom
        //    Finds the offset <EepromLocation> that goes with the given slope <EepromLocation>.
        //
        //Parameters:
        //    slopeEeprom - The slope <EepromLocation> that the offset eeprom goes with.
        //
        //Returns:
        //    The offset <EepromLocation>.
        static EepromLocation getOffsetEeprom(const EepromLocation& slopeEeprom);

        //Function: getEventTriggerEeproms
        //  Finds the eeproms for Event Driven Triggering.
        //
        //Parameters:
        //  triggerIndex - The trigger number that is being requested.
        //  isFloatVal - Whether the event trigger uses floating point for values, or uint16.
        //  channel - Holds the result <EepromLocation> for the channel number.
        //  type - Holds the result <EepromLocation> for the event type.
        //  value - Holds the result <EepromLocation> for the event value.
        static void getEventTriggerEeproms(uint8 triggerIndex, bool isFloatVal, EepromLocation& channel, EepromLocation& type, EepromLocation& value);

        //Constants: Eeprom Locations
        //  CURRENT_LOG_PAGE                - The next flash page to be used for datalogging
        //  CURRENT_PAGE_OFFSET             - The byte offset location for the next datalogging session
        //  DATA_SETS_STORED                - The # of datalogging sessions (triggers) stored in flash memory
        //  FLASH_ID                        - The flash ID
        //  STORAGE_LIMIT_MODE              - The storage limit mode.
        //  ACTIVE_CHANNEL_MASK             - The channels that are enabled/disabled and will be sampled
        //  DATALOG_SAMPLE_RATE             - The sample rate for Armed Datalogging sampling
        //  NUM_SWEEPS                      - The # of sweeps (samples per data set) to sample for
        //  DEFAULT_MODE                    - The default mode to allow the node to perform different operations on startup and after timeout
        //  SERIAL_ID                       - The serial ID for the node. Combine with the model number for the full serial number
        //  SAMPLING_MODE                   - The sampling mode of the node (Sync Sampling, Non-Sync Sampling, Armed Datalogging, etc.)
        //  HW_OFFSET_1                     - The hardware offset of channel 1
        //  HW_OFFSET_2                     - The hardware offset of channel 2
        //  HW_OFFSET_3                     - The hardware offset of channel 3
        //  HW_OFFSET_4                     - The hardware offset of channel 4
        //  HW_OFFSET_5                     - The hardware offset of channel 5
        //  HW_OFFSET_6                     - The hardware offset of channel 6
        //  HW_OFFSET_7                     - The hardware offset of channel 7
        //  HW_OFFSET_8                     - The hardware offset of channel 8
        //  SAMPLING_DELAY                  - The sampling delay (amount of time between sensor excitation power up and A/D sampling
        //  TDMA_ADDRESS                    - The TDMA network address used for Synchronized Sampling
        //  COLLECTION_MODE                 - The data collection mode (log, transmit) that affects standard sampling modes
        //  NUM_BUFF_PACKETS                - The # of buffered packets
        //  NUM_RETRAN_ATTEMPTS             - The # of retransmit attempts
        //  NODE_ADDRESS                    - The node address of the wireless node
        //  SLEEP_INTERVAL                  - The listen-for-wakeup interval for the node
        //  INACTIVE_TIMEOUT                - The length of time necessary before a node enters sleep mode, if no user activity
        //  SAMPLE_RATE                     - The sample rate for standard sampling modes (Synchronized Sampling, LDC)
        //  DATA_FORMAT                     - The packet format (uint16, float, etc.) of sampled data
        //  SNIFF_DURATION                  - The amount of time that the node listens for a wake packets 
        //  FREQUENCY                       - The radio frequency channel
        //  TX_POWER_LEVEL                  - The transmit output power of the radio
        //  UNLIMITED_SAMPLING              - The unlimited sampling flag for standard sampling modes
        //  UNLIMITED_DATALOG               - The unlimited sampling flag for Armed Datalogging sampling
        //  FIRMWARE_VER                    - The firmware version of the node (part 1)
        //  FIRMWARE_VER2                   - The firmware version of the node (part 2)
        //  MODEL_NUMBER                    - The model number of the node    
        //  MODEL_OPTION                    - The model option of the node
        //  LEGACY_MODEL_NUMBER             - The (legacy) model number of the node
        //  LEGACY_SERIAL_ID                - The (legacy) serial ID for the node. Combine with the model number for the full serial number
        //  MAX_MEMORY                      - The maximum number of pages available on the flash memory
        //  MICROCONTROLLER                 - The ID of the microcontroller
        //  FW_ARCH_VER                     - The firmware architecture version
        //  ASPP_VER                        - The ASPP version the node supports
        //  HW_GAIN_1                       - The hardware gain of channel 1
        //  HW_GAIN_2                       - The hardware gain of channel 2
        //  HW_GAIN_3                       - The hardware gain of channel 3
        //  HW_GAIN_4                       - The hardware gain of channel 4
        //  HW_GAIN_5                       - The hardware gain of channel 5
        //  HW_GAIN_6                       - The hardware gain of channel 6
        //  HW_GAIN_7                       - The hardware gain of channel 7
        //  HW_GAIN_8                       - The hardware gain of channel 8
        //  CH_ACTION_ID_1                  - The channel action ID of channel 1
        //  CH_ACTION_SLOPE_1               - The channel action slope of channel 1
        //  CH_ACTION_OFFSET_1              - The channel action offset of channel 1
        //  CH_ACTION_ID_2                  - The channel action ID of channel 2
        //  CH_ACTION_SLOPE_2               - The channel action slope of channel 2
        //  CH_ACTION_OFFSET_2              - The channel action offset of channel 2
        //  CH_ACTION_ID_3                  - The channel action ID of channel 3
        //  CH_ACTION_SLOPE_3               - The channel action slope of channel 3
        //  CH_ACTION_OFFSET_3              - The channel action offset of channel 3
        //  CH_ACTION_ID_4                  - The channel action ID of channel 4
        //  CH_ACTION_SLOPE_4               - The channel action slope of channel 4
        //  CH_ACTION_OFFSET_4              - The channel action offset of channel 4
        //  CH_ACTION_ID_5                  - The channel action ID of channel 5
        //  CH_ACTION_SLOPE_5               - The channel action slope of channel 5
        //  CH_ACTION_OFFSET_5              - The channel action offset of channel 5
        //  CH_ACTION_ID_6                  - The channel action ID of channel 6
        //  CH_ACTION_SLOPE_6               - The channel action slope of channel 6
        //  CH_ACTION_OFFSET_6              - The channel action offset of channel 6
        //  CH_ACTION_ID_7                  - The channel action ID of channel 7
        //  CH_ACTION_SLOPE_7               - The channel action slope of channel 7
        //  CH_ACTION_OFFSET_7              - The channel action offset of channel 7
        //  CH_ACTION_ID_8                  - The channel action ID of channel 8
        //  CH_ACTION_SLOPE_8               - The channel action slope of channel 8
        //  CH_ACTION_OFFSET_8              - The channel action offset of channel 8
        //  CH_ACTION_ID_9                  - The channel action ID of channel 9
        //  CH_ACTION_SLOPE_9               - The channel action slope of channel 9
        //  CH_ACTION_OFFSET_9              - The channel action offset of channel 9
        //  CH_ACTION_ID_10                 - The channel action ID of channel 10
        //  CH_ACTION_SLOPE_10              - The channel action slope of channel 10
        //  CH_ACTION_OFFSET_10             - The channel action offset of channel 10
        //  CH_ACTION_ID_11                 - The channel action ID of channel 11
        //  CH_ACTION_SLOPE_11              - The channel action slope of channel 11
        //  CH_ACTION_OFFSET_11             - The channel action offset of channel 11
        //  CH_ACTION_ID_12                 - The channel action ID of channel 12
        //  CH_ACTION_SLOPE_12              - The channel action slope of channel 12
        //  CH_ACTION_OFFSET_12             - The channel action offset of channel 12
        //  CH_ACTION_ID_13                 - The channel action ID of channel 13
        //  CH_ACTION_SLOPE_13              - The channel action slope of channel 13
        //  CH_ACTION_OFFSET_13             - The channel action offset of channel 13
        //  CH_ACTION_ID_14                 - The channel action ID of channel 14
        //  CH_ACTION_SLOPE_14              - The channel action slope of channel 14
        //  CH_ACTION_OFFSET_14             - The channel action offset of channel 14
        //  CH_ACTION_ID_15                 - The channel action ID of channel 15
        //  CH_ACTION_SLOPE_15              - The channel action slope of channel 15
        //  CH_ACTION_OFFSET_15             - The channel action offset of channel 15
        //  CH_ACTION_ID_16                 - The channel action ID of channel 16
        //  CH_ACTION_SLOPE_16              - The channel action slope of channel 16
        //  CH_ACTION_OFFSET_16             - The channel action offset of channel 16
        //  LEGACY_BOOTLOAD_PAGE            - The bootloader page address (Legacy)
        //  LEGACY_BOOTLOAD_ENABLE_FLAG     - The bootloader enable flag (Legacy)
        //  LEGACY_BOOTLOAD_CHECKSUM        - The bootloader checksum (Legacy)
        //  LEGACY_BOOTLOADER_VER           - The bootloader version (Legacy)
        //  LEGACY_BOOTLOADER_OPTIONS       - The bootloader options (Legacy)
        //  LEGACY_BOOTLOADER_COUNTER       - The bootloader counter (Legacy)
        //  RESET_COUNTER                   - The number of times the node has been turned on
        //  CYCLE_POWER                     - Used to soft reset the node or the radio on the node
        //  RADIO_OPTIONS                   - The options of the current radio (XR enabled or not, etc.)
        //  LOST_BEACON_TIMEOUT             - The time for a node to wait before entering a low power state when no longer hearing a beacon in Sync Sampling
        //  SYNC_SAMPLE_SETTING             - The Synchronized Sampling mode (Burst, Continuous, etc.)
        //  TX_PER_GROUP                    - The transmissions per group for Synchronized Sampling
        //  GROUP_SIZE                      - The group size for Synchronized Sampling
        //  TIME_BETW_SESSIONS              - The time between each burst for Synchronized Sampling
        //  NODE_RETRANSMIT                 - Node retranmission enable/disable (for Lossless)
        //  MAX_RETRANS_PACKET              - The max retransmits per packet
        //  MAX_RETRANS_BURST               - The max retransmits per burst
        //  REGION_CODE                     - The region code for the device
        //  DATA_MODE                       - The data mode (raw, math, etc) as a mask
        //  DERIVED_DATA_RATE               - The sample rate for the Math channels
        //  DERIVED_RMS_MASK                - Derived - RMS channel mask
        //  DERIVED_P2P_MASK                - Derived - Peak to Peak channel mask
        //  DERIVED_VELOCITY_MASK           - Derived - Velocity channel mask
        //  DERIVED_CREST_FACTOR_MASK       - Derived - Crest Factor channel mask
        //  DERIVED_MEAN_MASK               - Derived - Mean channel mask
        //  DERIVED_VELOCITY_UNIT           - Derived - Velocity Unit
        //  DATA_PACKET_FORMAT              - The format of the data packet that will be sent out
        //  DIAGNOSTIC_INTERVAL             - The interval at which the Diagnostic Packet is sent
        //  EVENT_SAMPLE_RATE               - Event Driven Sampling: Sample Rate
        //  EVENT_TRIGGER_MASK              - Event Driven Sampling: Trigger Mask
        //  EVENT_PRE_DURATION              - Event Driven Sampling: Pre-Event Duration
        //  EVENT_POST_DURATION             - Event Driven Sampling: Post-Event Duration
        //  EVENT_SRC_1                     - Event Driven Sampling: The source for Event 1
        //  EVENT_OPER_1                    - Event Driven Sampling: The operation for Event 1
        //  EVENT_VAL1_1                    - Event Driven Sampling: Value 1 for Event 1
        //  EVENT_VAL2_1                    - Event Driven Sampling: Value 2 for Event 1
        //  EVENT_SRC_2                     - Event Driven Sampling: The source for Event 2
        //  EVENT_OPER_2                    - Event Driven Sampling: The operation for Event 2
        //  EVENT_VAL1_2                    - Event Driven Sampling: Value 1 for Event 2
        //  EVENT_VAL2_2                    - Event Driven Sampling: Value 2 for Event 2
        //  EVENT_SRC_3                     - Event Driven Sampling: The source for Event 3
        //  EVENT_OPER_3                    - Event Driven Sampling: The operation for Event 3
        //  EVENT_VAL1_3                    - Event Driven Sampling: Value 1 for Event 3
        //  EVENT_VAL2_3                    - Event Driven Sampling: Value 2 for Event 3
        //  EVENT_SRC_4                     - Event Driven Sampling: The source for Event 4
        //  EVENT_OPER_4                    - Event Driven Sampling: The operation for Event 4
        //  EVENT_VAL1_4                    - Event Driven Sampling: Value 1 for Event 4
        //  EVENT_VAL2_4                    - Event Driven Sampling: Value 2 for Event 4
        //  EVENT_SRC_5                     - Event Driven Sampling: The source for Event 5
        //  EVENT_OPER_5                    - Event Driven Sampling: The operation for Event 5
        //  EVENT_VAL1_5                    - Event Driven Sampling: Value 1 for Event 5
        //  EVENT_VAL2_5                    - Event Driven Sampling: Value 2 for Event 5
        //  EVENT_SRC_6                     - Event Driven Sampling: The source for Event 6
        //  EVENT_OPER_6                    - Event Driven Sampling: The operation for Event 6
        //  EVENT_VAL1_6                    - Event Driven Sampling: Value 1 for Event 6
        //  EVENT_VAL2_6                    - Event Driven Sampling: Value 2 for Event 6
        //  EVENT_SRC_7                     - Event Driven Sampling: The source for Event 7
        //  EVENT_OPER_7                    - Event Driven Sampling: The operation for Event 7
        //  EVENT_VAL1_7                    - Event Driven Sampling: Value 1 for Event 7
        //  EVENT_VAL2_7                    - Event Driven Sampling: Value 2 for Event 7
        //  EVENT_SRC_8                     - Event Driven Sampling: The source for Event 8
        //  EVENT_OPER_8                    - Event Driven Sampling: The operation for Event 8
        //  EVENT_VAL1_8                    - Event Driven Sampling: Value 1 for Event 8
        //  EVENT_VAL2_8                    - Event Driven Sampling: Value 2 for Event 8
        //  EXCITATION_VOLTAGE              - Excitation Voltage
        //  DEBOUNCE_FILTER                 - Debounce Filter
        //  INTERNAL_PULLUP_RESISTOR        - Internal Pull-up Resistor
        //  ANTI_ALIASING_FILTER_1          - The anti-aliasing filter for channels (1).
        //  ANTI_ALIASING_FILTER_2          - The anti-aliasing filter for channels (2).
        //  ANTI_ALIASING_FILTER_3          - The anti-aliasing filter for channels (3).
        //  ANTI_ALIASING_FILTER_4          - The anti-aliasing filter for channels (4).
        //  LOW_PASS_FILTER_1               - The low-pass filter for channels (1).
        //  LOW_PASS_FILTER_2               - The low-pass filter for channels (2).
        //  LOW_PASS_FILTER_3               - The low-pass filter for channels (3).
        //  LOW_PASS_FILTER_4               - The low-pass filter for channels (4).
        //  HIGH_PASS_FILTER_1              - The high-pass filter for channels (1).
        //  HIGH_PASS_FILTER_2              - The high-pass filter for channels (2).
        //  HIGH_PASS_FILTER_3              - The high-pass filter for channels (3).
        //  HIGH_PASS_FILTER_4              - The high-pass filter for channels (4).
        //  MIN_SOFT_VER_MAJOR              - The minimum software version for support of this device (major)
        //  MIN_SOFT_VER_MINOR              - The minimum software version for support of this device (minor)
        //  GAUGE_FACTOR_1                  - The Gauge Factor (1)
        //  GAUGE_FACTOR_2                  - The Gauge Factor (2)
        //  GAUGE_FACTOR_3                  - The Gauge Factor (3)
        //  GAUGE_FACTOR_4                  - The Gauge Factor (4)
        //  GAUGE_RESISTANCE                - The Gauge Resistance
        //  NUM_ACTIVE_GAUGES               - The Number of Active Gauges
        //  LOW_BATTERY_THRESHOLD           - The threshold at which the low battery flag is sent
        //  THERMOCPL_TYPE                  - The thermocouple type for nodes with thermocouple capabilities (ie. TC-Link)
        //  FILTER_1                        - The first filter value for nodes with filter capabilities (ie. TC-Link)
        //  FILTER_2                        - The second filter value for nodes with 2 filter capabilities (ie. ENV-Link-Pro)
        //  LEGACY_DAMAGE_ANGLE_1           - The first damage angle (legacy).
        //  LEGACY_DAMAGE_ANGLE_2           - The second damage angle (legacy).
        //  LEGACY_DAMAGE_ANGLE_3           - The third damage angle (legacy).
        //  BIN_SIZE                        - The size of each bin in the histogram.
        //  RESET_BINS                      - Used to reset the histogram bin data.
        //  BIN_START                       - The start of the bins.
        //  PEAK_VALLEY_THRES               - The peak/valley threshold.
        //  SNCURVE_LOGA_1                  - logA of the first SN Curve.
        //  SNCURVE_M_1                     - m of the first SN Curve.
        //  SNCURVE_LOGA_2                  - logA of the second SN Curve.
        //  SNCURVE_M_2                     - m of the second SN Curve.
        //  SNCURVE_LOGA_3                  - logA of the third SN Curve.
        //  SNCURVE_M_3                     - m of the third SN Curve.
        //  SNCURVE_LOGA_4                  - logA of the fourth SN Curve.
        //  SNCURVE_M_4                     - m of the fourth SN Curve.
        //  SNCURVE_LOGA_5                  - logA of the fifth SN Curve.
        //  SNCURVE_M_5                     - m of the fifth SN Curve.
        //  YOUNGS_MODULUS                  - The youngs modulus.
        //  POISSONS_RATIO                  - The poissons ratio.
        //  HISTOGRAM_SAMPLE_RATE           - The same rate of the histogram.
        //  DAMAGE_ANGLE_1                  - The first damage angle.
        //  DAMAGE_ANGLE_2                  - The second damage angle.
        //  DAMAGE_ANGLE_3                  - The third damage angle.
        //  FATIGUE_MODE                    - SHM 3-angle mode vs Distributed Angle mode vs Raw Gauge Strain mode.
        //  DIST_ANGLE_NUM_ANGLES           - The number of angles for Distributed Angle Mode.
        //  DIST_ANGLE_LOWER_BOUND          - The lower bound for Distributed Angle Mode.
        //  DIST_ANGLE_UPPER_BOUND          - The upper bound for Distributed Angle Mode.
        //  HISTOGRAM_RAW_FLAG              - Raw mode enable/disable.
        //  ACT_SENSE_ENABLE                - Activity Sense enable/disable.
        //  ACT_SENSE_ACTIVE_THRES          - Activity Sense activity threshold.
        //  ACT_SENSE_INACTIVE_TIMEOUT      - Activity Sense inactivity timeout.
        //  ACT_SENSE_ACTIVE_TIME           - Activity Sense activity time.
        //  ACT_SENSE_INACTIVE_THRES        - Activity Sense inactivity threshold.
        //  HISTOGRAM_ENABLE                - Histogram enable/disable.
        //  COMM_PROTOCOL                   - Communication Protocol.
        //  BOOTLOADER_VER                  - The bootloader version.
        //  FIRMWARE_UPGRADE_FLAGS          - The firmware upgrade flags.
        //  BOOTLOADER_FLASH_ADDRESS        - The bootloader flash address to store firmware upgrades.
        //  TEMP_SENSOR_CONFIG_1            - Reserved for future use.
        //  TEMP_SENSOR_CONFIG_2            - Reserved for future use.
        //  TEMP_SENSOR_CONFIG_3            - Reserved for future use.
        //  TEMP_SENSOR_CONFIG_4            - Reserved for future use.
        //  TEMP_SENSOR_CONFIG_5            - Reserved for future use.
        //  TEMP_SENSOR_CONFIG_6            - Reserved for future use.
        //  TEMP_SENSOR_CONFIG_7            - Reserved for future use.
        //  TEMP_SENSOR_CONFIG_8            - Reserved for future use.
        //  TEMP_SENSOR_CONFIG_9            - Reserved for future use.
        //  TEMP_SENSOR_CONFIG_10           - Reserved for future use.
        //  TEMP_SENSOR_CONFIG_11           - Reserved for future use.
        //  TEMP_SENSOR_CONFIG_12           - Reserved for future use.
        //  TEMP_SENSOR_CONFIG_13           - Reserved for future use.
        //  TEMP_SENSOR_CONFIG_14           - Reserved for future use.
        //  TEMP_SENSOR_CONFIG_15           - Reserved for future use.
        //  TEMP_SENSOR_CONFIG_16           - Reserved for future use.
        //  FACTORY_CH_ACTION_ID_1          - The factory-calibrated channel action ID of channel 1
        //  FACTORY_CH_ACTION_SLOPE_1       - The factory-calibrated channel action slope of channel 1
        //  FACTORY_CH_ACTION_OFFSET_1      - The factory-calibrated channel action offset of channel 1
        //  FACTORY_CH_ACTION_ID_2          - The factory-calibrated channel action ID of channel 2
        //  FACTORY_CH_ACTION_SLOPE_2       - The factory-calibrated channel action slope of channel 2
        //  FACTORY_CH_ACTION_OFFSET_2      - The factory-calibrated channel action offset of channel 2
        //  FACTORY_CH_ACTION_ID_3          - The factory-calibrated channel action ID of channel 3
        //  FACTORY_CH_ACTION_SLOPE_3       - The factory-calibrated channel action slope of channel 3
        //  FACTORY_CH_ACTION_OFFSET_3      - The factory-calibrated channel action offset of channel 3
        //  FACTORY_CH_ACTION_ID_4          - The factory-calibrated channel action ID of channel 4
        //  FACTORY_CH_ACTION_SLOPE_4       - The factory-calibrated channel action slope of channel 4
        //  FACTORY_CH_ACTION_OFFSET_4      - The factory-calibrated channel action offset of channel 4
        //  FACTORY_CH_ACTION_ID_5          - The factory-calibrated channel action ID of channel 5
        //  FACTORY_CH_ACTION_SLOPE_5       - The factory-calibrated channel action slope of channel 5
        //  FACTORY_CH_ACTION_OFFSET_5      - The factory-calibrated channel action offset of channel 5
        //  FACTORY_CH_ACTION_ID_6          - The factory-calibrated channel action ID of channel 6
        //  FACTORY_CH_ACTION_SLOPE_6       - The factory-calibrated channel action slope of channel 6
        //  FACTORY_CH_ACTION_OFFSET_6      - The factory-calibrated channel action offset of channel 6
        //  FACTORY_CH_ACTION_ID_7          - The factory-calibrated channel action ID of channel 7
        //  FACTORY_CH_ACTION_SLOPE_7       - The factory-calibrated channel action slope of channel 7
        //  FACTORY_CH_ACTION_OFFSET_7      - The factory-calibrated channel action offset of channel 7
        //  FACTORY_CH_ACTION_ID_8          - The factory-calibrated channel action ID of channel 8
        //  FACTORY_CH_ACTION_SLOPE_8       - The factory-calibrated channel action slope of channel 8
        //  FACTORY_CH_ACTION_OFFSET_8      - The factory-calibrated channel action offset of channel 8
        static const EepromLocation CURRENT_LOG_PAGE;
        static const EepromLocation CURRENT_PAGE_OFFSET;
        static const EepromLocation DATA_SETS_STORED;
        static const EepromLocation ACTIVE_CHANNEL_MASK;
        static const EepromLocation DATALOG_SAMPLE_RATE;
        static const EepromLocation NUM_SWEEPS;
        static const EepromLocation DEFAULT_MODE;
        static const EepromLocation SERIAL_ID;
        static const EepromLocation SAMPLING_MODE;
        static const EepromLocation HW_OFFSET_1;
        static const EepromLocation HW_OFFSET_2;
        static const EepromLocation HW_OFFSET_3;
        static const EepromLocation HW_OFFSET_4;
        static const EepromLocation HW_OFFSET_5;
        static const EepromLocation HW_OFFSET_6;
        static const EepromLocation HW_OFFSET_7;
        static const EepromLocation HW_OFFSET_8;
        static const EepromLocation SAMPLING_DELAY;
        static const EepromLocation TDMA_ADDRESS;
        static const EepromLocation COLLECTION_MODE;
        static const EepromLocation NUM_BUFF_PACKETS;
        static const EepromLocation NUM_RETRAN_ATTEMPTS;
        static const EepromLocation NODE_ADDRESS;
        static const EepromLocation SLEEP_INTERVAL;
        static const EepromLocation INACTIVE_TIMEOUT;
        static const EepromLocation SAMPLE_RATE;
        static const EepromLocation DATA_FORMAT;
        static const EepromLocation SNIFF_DURATION;
        static const EepromLocation FREQUENCY;
        static const EepromLocation TX_POWER_LEVEL;
        static const EepromLocation UNLIMITED_SAMPLING;
        static const EepromLocation UNLIMITED_DATALOG;
        static const EepromLocation FIRMWARE_VER;
        static const EepromLocation FIRMWARE_VER2;
        static const EepromLocation MODEL_NUMBER;
        static const EepromLocation MODEL_OPTION;
        static const EepromLocation LEGACY_MODEL_NUMBER;
        static const EepromLocation LEGACY_SERIAL_ID;
        static const EepromLocation MAX_MEMORY;
        static const EepromLocation MICROCONTROLLER;
        static const EepromLocation FW_ARCH_VER;
        static const EepromLocation ASPP_VER_LXRS;
        static const EepromLocation ASPP_VER_LXRS_PLUS;
        static const EepromLocation HW_GAIN_1;
        static const EepromLocation HW_GAIN_2;
        static const EepromLocation HW_GAIN_3;
        static const EepromLocation HW_GAIN_4;
        static const EepromLocation HW_GAIN_5;
        static const EepromLocation HW_GAIN_6;
        static const EepromLocation HW_GAIN_7;
        static const EepromLocation HW_GAIN_8;
        static const EepromLocation FLASH_ID;
        static const EepromLocation STORAGE_LIMIT_MODE;
        static const EepromLocation CH_ACTION_ID_1;
        static const EepromLocation CH_ACTION_SLOPE_1;
        static const EepromLocation CH_ACTION_OFFSET_1;
        static const EepromLocation CH_ACTION_ID_2;
        static const EepromLocation CH_ACTION_SLOPE_2;
        static const EepromLocation CH_ACTION_OFFSET_2;
        static const EepromLocation CH_ACTION_ID_3;
        static const EepromLocation CH_ACTION_SLOPE_3;
        static const EepromLocation CH_ACTION_OFFSET_3;
        static const EepromLocation CH_ACTION_ID_4;
        static const EepromLocation CH_ACTION_SLOPE_4;
        static const EepromLocation CH_ACTION_OFFSET_4;
        static const EepromLocation CH_ACTION_ID_5;
        static const EepromLocation CH_ACTION_SLOPE_5;
        static const EepromLocation CH_ACTION_OFFSET_5;
        static const EepromLocation CH_ACTION_ID_6;
        static const EepromLocation CH_ACTION_SLOPE_6;
        static const EepromLocation CH_ACTION_OFFSET_6;
        static const EepromLocation CH_ACTION_ID_7;
        static const EepromLocation CH_ACTION_SLOPE_7;
        static const EepromLocation CH_ACTION_OFFSET_7;
        static const EepromLocation CH_ACTION_ID_8;
        static const EepromLocation CH_ACTION_SLOPE_8;
        static const EepromLocation CH_ACTION_OFFSET_8;
        static const EepromLocation CH_ACTION_ID_9;
        static const EepromLocation CH_ACTION_SLOPE_9;
        static const EepromLocation CH_ACTION_OFFSET_9;
        static const EepromLocation CH_ACTION_ID_10;
        static const EepromLocation CH_ACTION_SLOPE_10;
        static const EepromLocation CH_ACTION_OFFSET_10;
        static const EepromLocation CH_ACTION_ID_11;
        static const EepromLocation CH_ACTION_SLOPE_11;
        static const EepromLocation CH_ACTION_OFFSET_11;
        static const EepromLocation CH_ACTION_ID_12;
        static const EepromLocation CH_ACTION_SLOPE_12;
        static const EepromLocation CH_ACTION_OFFSET_12;
        static const EepromLocation CH_ACTION_ID_13;
        static const EepromLocation CH_ACTION_SLOPE_13;
        static const EepromLocation CH_ACTION_OFFSET_13;
        static const EepromLocation CH_ACTION_ID_14;
        static const EepromLocation CH_ACTION_SLOPE_14;
        static const EepromLocation CH_ACTION_OFFSET_14;
        static const EepromLocation CH_ACTION_ID_15;
        static const EepromLocation CH_ACTION_SLOPE_15;
        static const EepromLocation CH_ACTION_OFFSET_15;
        static const EepromLocation CH_ACTION_ID_16;
        static const EepromLocation CH_ACTION_SLOPE_16;
        static const EepromLocation CH_ACTION_OFFSET_16;
        static const EepromLocation LEGACY_BOOTLOAD_PAGE;
        static const EepromLocation LEGACY_BOOTLOAD_ENABLE_FLAG;
        static const EepromLocation LEGACY_BOOTLOAD_CHECKSUM;
        static const EepromLocation LEGACY_BOOTLOADER_VER;
        static const EepromLocation LEGACY_BOOTLOADER_OPTIONS;
        static const EepromLocation LEGACY_BOOTLOADER_COUNTER;
        static const EepromLocation RESET_COUNTER;
        static const EepromLocation CYCLE_POWER;
        static const EepromLocation RADIO_OPTIONS;
        static const EepromLocation LOST_BEACON_TIMEOUT;
        static const EepromLocation SYNC_SAMPLE_SETTING;
        static const EepromLocation TX_PER_GROUP;
        static const EepromLocation GROUP_SIZE;
        static const EepromLocation TIME_BETW_SESSIONS;
        static const EepromLocation NODE_RETRANSMIT;
        static const EepromLocation MAX_RETRANS_PACKET;
        static const EepromLocation MAX_RETRANS_BURST;
        static const EepromLocation REGION_CODE;
        static const EepromLocation DATA_MODE;
        static const EepromLocation DERIVED_DATA_RATE;
        static const EepromLocation DERIVED_RMS_MASK;
        static const EepromLocation DERIVED_P2P_MASK;
        static const EepromLocation DERIVED_VELOCITY_MASK;
        static const EepromLocation DERIVED_CREST_FACTOR_MASK;
        static const EepromLocation DERIVED_MEAN_MASK;
        static const EepromLocation DERIVED_VELOCITY_UNIT;
        static const EepromLocation DATA_PACKET_FORMAT;
        static const EepromLocation DIAGNOSTIC_INTERVAL;
        static const EepromLocation EVENT_SAMPLE_RATE;
        static const EepromLocation EVENT_TRIGGER_MASK;
        static const EepromLocation EVENT_PRE_DURATION;
        static const EepromLocation EVENT_POST_DURATION;
        static const EepromLocation EVENT_SRC_1;
        static const EepromLocation EVENT_OPER_1;
        static const EepromLocation EVENT_VAL1_1;
        static const EepromLocation EVENT_VAL2_1;
        static const EepromLocation EVENT_SRC_2;
        static const EepromLocation EVENT_OPER_2;
        static const EepromLocation EVENT_VAL1_2;
        static const EepromLocation EVENT_VAL2_2;
        static const EepromLocation EVENT_SRC_3;
        static const EepromLocation EVENT_OPER_3;
        static const EepromLocation EVENT_VAL1_3;
        static const EepromLocation EVENT_VAL2_3;
        static const EepromLocation EVENT_SRC_4;
        static const EepromLocation EVENT_OPER_4;
        static const EepromLocation EVENT_VAL1_4;
        static const EepromLocation EVENT_VAL2_4;
        static const EepromLocation EVENT_SRC_5;
        static const EepromLocation EVENT_OPER_5;
        static const EepromLocation EVENT_VAL1_5;
        static const EepromLocation EVENT_VAL2_5;
        static const EepromLocation EVENT_SRC_6;
        static const EepromLocation EVENT_OPER_6;
        static const EepromLocation EVENT_VAL1_6;
        static const EepromLocation EVENT_VAL2_6;
        static const EepromLocation EVENT_SRC_7;
        static const EepromLocation EVENT_OPER_7;
        static const EepromLocation EVENT_VAL1_7;
        static const EepromLocation EVENT_VAL2_7;
        static const EepromLocation EVENT_SRC_8;
        static const EepromLocation EVENT_OPER_8;
        static const EepromLocation EVENT_VAL1_8;
        static const EepromLocation EVENT_VAL2_8;
        static const EepromLocation EXCITATION_VOLTAGE;
        static const EepromLocation DEBOUNCE_FILTER;
        static const EepromLocation INTERNAL_PULLUP_RESISTOR;
        static const EepromLocation SENSOR_MODE;
        static const EepromLocation ANTI_ALIASING_FILTER_1;
        static const EepromLocation ANTI_ALIASING_FILTER_2;
        static const EepromLocation ANTI_ALIASING_FILTER_3;
        static const EepromLocation ANTI_ALIASING_FILTER_4;
        static const EepromLocation LOW_PASS_FILTER_1;
        static const EepromLocation LOW_PASS_FILTER_2;
        static const EepromLocation LOW_PASS_FILTER_3;
        static const EepromLocation LOW_PASS_FILTER_4;
        static const EepromLocation HIGH_PASS_FILTER_1;
        static const EepromLocation HIGH_PASS_FILTER_2;
        static const EepromLocation HIGH_PASS_FILTER_3;
        static const EepromLocation HIGH_PASS_FILTER_4;
        static const EepromLocation MIN_SOFT_VER_MAJOR;
        static const EepromLocation MIN_SOFT_VER_MINOR;
        static const EepromLocation GAUGE_FACTOR_1;
        static const EepromLocation GAUGE_FACTOR_2;
        static const EepromLocation GAUGE_FACTOR_3;
        static const EepromLocation GAUGE_FACTOR_4;
        static const EepromLocation GAUGE_RESISTANCE;
        static const EepromLocation NUM_ACTIVE_GAUGES;
        static const EepromLocation LOW_BATTERY_THRESHOLD;
        static const EepromLocation THERMOCPL_TYPE;
        static const EepromLocation FILTER_1;
        static const EepromLocation FILTER_2;
        static const EepromLocation LEGACY_DAMAGE_ANGLE_1;
        static const EepromLocation LEGACY_DAMAGE_ANGLE_2;
        static const EepromLocation LEGACY_DAMAGE_ANGLE_3;
        static const EepromLocation BIN_SIZE;
        static const EepromLocation RESET_BINS;
        static const EepromLocation BIN_START;
        static const EepromLocation PEAK_VALLEY_THRES;
        static const EepromLocation SNCURVE_LOGA_1;
        static const EepromLocation SNCURVE_M_1;
        static const EepromLocation SNCURVE_LOGA_2;
        static const EepromLocation SNCURVE_M_2;
        static const EepromLocation SNCURVE_LOGA_3;
        static const EepromLocation SNCURVE_M_3;
        static const EepromLocation SNCURVE_LOGA_4;
        static const EepromLocation SNCURVE_M_4;
        static const EepromLocation SNCURVE_LOGA_5;
        static const EepromLocation SNCURVE_M_5;
        static const EepromLocation YOUNGS_MODULUS;
        static const EepromLocation POISSONS_RATIO;
        static const EepromLocation HISTOGRAM_SAMPLE_RATE;
        static const EepromLocation DAMAGE_ANGLE_1;
        static const EepromLocation DAMAGE_ANGLE_2;
        static const EepromLocation DAMAGE_ANGLE_3;
        static const EepromLocation FATIGUE_MODE;
        static const EepromLocation DIST_ANGLE_NUM_ANGLES;
        static const EepromLocation DIST_ANGLE_LOWER_BOUND;
        static const EepromLocation DIST_ANGLE_UPPER_BOUND;
        static const EepromLocation HISTOGRAM_RAW_FLAG;
        static const EepromLocation ACT_SENSE_ENABLE;
        static const EepromLocation ACT_SENSE_ACTIVE_THRES;
        static const EepromLocation ACT_SENSE_INACTIVE_TIMEOUT;
        static const EepromLocation ACT_SENSE_ACTIVE_TIME;
        static const EepromLocation ACT_SENSE_INACTIVE_THRES;
        static const EepromLocation HISTOGRAM_ENABLE;
        static const EepromLocation COMM_PROTOCOL;
        static const EepromLocation BOOTLOADER_VER;
        static const EepromLocation FIRMWARE_UPGRADE_FLAGS;
        static const EepromLocation BOOTLOADER_FLASH_ADDRESS;
        static const EepromLocation TEMP_SENSOR_CONFIG_1;
        static const EepromLocation TEMP_SENSOR_CONFIG_2;
        static const EepromLocation TEMP_SENSOR_CONFIG_3;
        static const EepromLocation TEMP_SENSOR_CONFIG_4;
        static const EepromLocation TEMP_SENSOR_CONFIG_5;
        static const EepromLocation TEMP_SENSOR_CONFIG_6;
        static const EepromLocation TEMP_SENSOR_CONFIG_7;
        static const EepromLocation TEMP_SENSOR_CONFIG_8;
        static const EepromLocation TEMP_SENSOR_CONFIG_9;
        static const EepromLocation TEMP_SENSOR_CONFIG_10;
        static const EepromLocation TEMP_SENSOR_CONFIG_11;
        static const EepromLocation TEMP_SENSOR_CONFIG_12;
        static const EepromLocation TEMP_SENSOR_CONFIG_13;
        static const EepromLocation TEMP_SENSOR_CONFIG_14;
        static const EepromLocation TEMP_SENSOR_CONFIG_15;
        static const EepromLocation TEMP_SENSOR_CONFIG_16;
        static const EepromLocation FACTORY_CH_ACTION_ID_1;
        static const EepromLocation FACTORY_CH_ACTION_SLOPE_1;
        static const EepromLocation FACTORY_CH_ACTION_OFFSET_1;
        static const EepromLocation FACTORY_CH_ACTION_ID_2;
        static const EepromLocation FACTORY_CH_ACTION_SLOPE_2;
        static const EepromLocation FACTORY_CH_ACTION_OFFSET_2;
        static const EepromLocation FACTORY_CH_ACTION_ID_3;
        static const EepromLocation FACTORY_CH_ACTION_SLOPE_3;
        static const EepromLocation FACTORY_CH_ACTION_OFFSET_3;
        static const EepromLocation FACTORY_CH_ACTION_ID_4;
        static const EepromLocation FACTORY_CH_ACTION_SLOPE_4;
        static const EepromLocation FACTORY_CH_ACTION_OFFSET_4;
        static const EepromLocation FACTORY_CH_ACTION_ID_5;
        static const EepromLocation FACTORY_CH_ACTION_SLOPE_5;
        static const EepromLocation FACTORY_CH_ACTION_OFFSET_5;
        static const EepromLocation FACTORY_CH_ACTION_ID_6;
        static const EepromLocation FACTORY_CH_ACTION_SLOPE_6;
        static const EepromLocation FACTORY_CH_ACTION_OFFSET_6;
        static const EepromLocation FACTORY_CH_ACTION_ID_7;
        static const EepromLocation FACTORY_CH_ACTION_SLOPE_7;
        static const EepromLocation FACTORY_CH_ACTION_OFFSET_7;
        static const EepromLocation FACTORY_CH_ACTION_ID_8;
        static const EepromLocation FACTORY_CH_ACTION_SLOPE_8;
        static const EepromLocation FACTORY_CH_ACTION_OFFSET_8;
    };
}