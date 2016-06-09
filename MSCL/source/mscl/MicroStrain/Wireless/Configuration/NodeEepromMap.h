/*******************************************************************************
Copyright(c) 2015-2016 LORD Corporation. All rights reserved.

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

        static void getEventTriggerEeproms(uint8 triggerIndex, EepromLocation& channel, EepromLocation& type, EepromLocation& value);

        //=======================================================================================================================
        //Constants: Eeprom Locations
        //
        //    CURRENT_LOG_PAGE                -The next flash page to be used for datalogging
        //    CURRENT_PAGE_OFFSET             -The byte offset location for the next datalogging session
        //    DATA_SETS_STORED                -The # of datalogging sessions (triggers) stored in flash memory
        //    FLASH_ID                        -The flash ID
        //    STORAGE_LIMIT_MODE              -The storage limit mode.
        //    ACTIVE_CHANNEL_MASK             -The channels that are enabled/disabled and will be sampled
        //    DATALOG_SAMPLE_RATE             -The sample rate for Armed Datalogging sampling
        //    NUM_SWEEPS                      -The # of sweeps (samples per data set) to sample for
        //    DEFAULT_MODE                    -The default mode to allow the node to perform different operations on startup and after timeout
        //    SERIAL_ID                       -The serial ID for the node. Combine with the model number for the full serial number
        //    SAMPLING_MODE                   -The sampling mode of the node (Sync Sampling, Non-Sync Sampling, Armed Datalogging, etc.)
        //    HW_OFFSET_1                     -The hardware offset of channel 1
        //    HW_OFFSET_2                     -The hardware offset of channel 2
        //    HW_OFFSET_3                     -The hardware offset of channel 3
        //    HW_OFFSET_4                     -The hardware offset of channel 4
        //    HW_OFFSET_5                     -The hardware offset of channel 5
        //    HW_OFFSET_6                     -The hardware offset of channel 6
        //    HW_OFFSET_7                     -The hardware offset of channel 7
        //    HW_OFFSET_8                     -The hardware offset of channel 8
        //    SAMPLING_DELAY                  -The sampling delay (amount of time between sensor excitation power up and A/D sampling
        //    TDMA_ADDRESS                    -The TDMA network address used for Synchronized Sampling
        //    COLLECTION_MODE                 -The data collection mode (log, transmit) that affects standard sampling modes
        //    NUM_BUFF_PACKETS                -The # of buffered packets
        //    NUM_RETRAN_ATTEMPTS             -The # of retransmit attempts
        //    NODE_ADDRESS                    -The node address of the wireless node
        //    SLEEP_INTERVAL                  -The listen-for-wakeup interval for the node
        //    INACTIVE_TIMEOUT                -The length of time necessary before a node enters sleep mode, if no user activity
        //    SAMPLE_RATE                     -The sample rate for standard sampling modes (Synchronized Sampling, LDC)
        //    DATA_FORMAT                     -The packet format (uint16, float, etc.) of sampled data
        //    SNIFF_DURATION                  -The amount of time that the node listens for a wake packets 
        //    FREQUENCY                       -The radio frequency channel
        //    TX_POWER_LEVEL                  -The transmit output power of the radio
        //    UNLIMITED_SAMPLING              -The unlimited sampling flag for standard sampling modes
        //    UNLIMITED_DATALOG               -The unlimited sampling flag for Armed Datalogging sampling
        //    FIRMWARE_VER                    -The firmware version of the node (part 1)
        //    FIRMWARE_VER2                   -The firmware version of the node (part 2)
        //    MODEL_NUMBER                    -The model number of the node    
        //    MODEL_OPTION                    -The model option of the node
        //    LEGACY_MODEL_NUMBER             -The (legacy) model number of the node
        //    LEGACY_SERIAL_ID                -The (legacy) serial ID for the node. Combine with the model number for the full serial number
        //    MAX_MEMORY                      -The maximum number of pages available on the flash memory
        //    MICROCONTROLLER                 -The ID of the microcontroller
        //    FW_ARCH_VER                     -The firmware architecture version
        //    HW_GAIN_1                       -The hardware gain of channel 1
        //    HW_GAIN_2                       -The hardware gain of channel 2
        //    HW_GAIN_3                       -The hardware gain of channel 3
        //    HW_GAIN_4                       -The hardware gain of channel 4
        //    HW_GAIN_5                       -The hardware gain of channel 5
        //    HW_GAIN_6                       -The hardware gain of channel 6
        //    HW_GAIN_7                       -The hardware gain of channel 7
        //    HW_GAIN_8                       -The hardware gain of channel 8
        //    CH_ACTION_ID_1                  -The channel action ID of channel 1
        //    CH_ACTION_SLOPE_1               -The channel action slope of channel 1
        //    CH_ACTION_OFFSET_1              -The channel action offset of channel 1
        //    CH_ACTION_ID_2                  -The channel action ID of channel 2
        //    CH_ACTION_SLOPE_2               -The channel action slope of channel 2
        //    CH_ACTION_OFFSET_2              -The channel action offset of channel 2
        //    CH_ACTION_ID_3                  -The channel action ID of channel 3
        //    CH_ACTION_SLOPE_3               -The channel action slope of channel 3
        //    CH_ACTION_OFFSET_3              -The channel action offset of channel 3
        //    CH_ACTION_ID_4                  -The channel action ID of channel 4
        //    CH_ACTION_SLOPE_4               -The channel action slope of channel 4
        //    CH_ACTION_OFFSET_4              -The channel action offset of channel 4
        //    CH_ACTION_ID_5                  -The channel action ID of channel 5
        //    CH_ACTION_SLOPE_5               -The channel action slope of channel 5
        //    CH_ACTION_OFFSET_5              -The channel action offset of channel 5
        //    CH_ACTION_ID_6                  -The channel action ID of channel 6
        //    CH_ACTION_SLOPE_6               -The channel action slope of channel 6
        //    CH_ACTION_OFFSET_6              -The channel action offset of channel 6
        //    CH_ACTION_ID_7                  -The channel action ID of channel 7
        //    CH_ACTION_SLOPE_7               -The channel action slope of channel 7
        //    CH_ACTION_OFFSET_7              -The channel action offset of channel 7
        //    CH_ACTION_ID_8                  -The channel action ID of channel 8
        //    CH_ACTION_SLOPE_8               -The channel action slope of channel 8
        //    CH_ACTION_OFFSET_8              -The channel action offset of channel 8
        //    BOOTLOADER_VER                  -The bootloader version number
        //    RESET_COUNTER                   -The number of times the node has been turned on
        //    CYCLE_POWER                     -Used to soft reset the node or the radio on the node
        //    RADIO_OPTIONS                   -The options of the current radio (XR enabled or not, etc.)
        //    LOST_BEACON_TIMEOUT             -The time for a node to wait before entering a low power state when no longer hearing a beacon in Sync Sampling
        //    SYNC_SAMPLE_SETTING             -The Synchronized Sampling mode (Burst, Continuous, etc.)
        //    TX_PER_GROUP                    -The transmissions per group for Synchronized Sampling
        //    GROUP_SIZE                      -The group size for Synchronized Sampling
        //    TIME_BETW_SESSIONS              -The time between each burst for Synchronized Sampling
        //    NODE_RETRANSMIT                 -Node retranmission enable/disable (for Lossless)
        //    MAX_RETRANS_PACKET              -The max retransmits per packet
        //    MAX_RETRANS_BURST               -The max retransmits per burst
        //    REGION_CODE                     -The region code for the device
        //    DATA_PACKET_FORMAT              -The format of the data packet that will be sent out.
        //    DIAGNOSTIC_INTERVAL             -The interval at which the Diagnostic Packet is sent.
        //    EVENT_SAMPLE_RATE               -Event Driven Sampling: Sample Rate
        //    EVENT_TRIGGER_MASK              -Event Driven Sampling: Trigger Mask
        //    EVENT_PRE_DURATION              -Event Driven Sampling: Pre-Event Duration
        //    EVENT_POST_DURATION             -Event Driven Sampling: Post-Event Duration
        //    EVENT_SRC_1                     -Event Driven Sampling: The source for Event 1
        //    EVENT_OPER_1                    -Event Driven Sampling: The operation for Event 1
        //    EVENT_VAL1_1                    -Event Driven Sampling: Value 1 for Event 1
        //    EVENT_VAL2_1                    -Event Driven Sampling: Value 2 for Event 1
        //    EVENT_SRC_2                     -Event Driven Sampling: The source for Event 2
        //    EVENT_OPER_2                    -Event Driven Sampling: The operation for Event 2
        //    EVENT_VAL1_2                    -Event Driven Sampling: Value 1 for Event 2
        //    EVENT_VAL2_2                    -Event Driven Sampling: Value 2 for Event 2
        //    EVENT_SRC_3                     -Event Driven Sampling: The source for Event 3
        //    EVENT_OPER_3                    -Event Driven Sampling: The operation for Event 3
        //    EVENT_VAL1_3                    -Event Driven Sampling: Value 1 for Event 3
        //    EVENT_VAL2_3                    -Event Driven Sampling: Value 2 for Event 3
        //    EVENT_SRC_4                     -Event Driven Sampling: The source for Event 4
        //    EVENT_OPER_4                    -Event Driven Sampling: The operation for Event 4
        //    EVENT_VAL1_4                    -Event Driven Sampling: Value 1 for Event 4
        //    EVENT_VAL2_4                    -Event Driven Sampling: Value 2 for Event 4
        //    EVENT_SRC_5                     -Event Driven Sampling: The source for Event 5
        //    EVENT_OPER_5                    -Event Driven Sampling: The operation for Event 5
        //    EVENT_VAL1_5                    -Event Driven Sampling: Value 1 for Event 5
        //    EVENT_VAL2_5                    -Event Driven Sampling: Value 2 for Event 5
        //    EVENT_SRC_6                     -Event Driven Sampling: The source for Event 6
        //    EVENT_OPER_6                    -Event Driven Sampling: The operation for Event 6
        //    EVENT_VAL1_6                    -Event Driven Sampling: Value 1 for Event 6
        //    EVENT_VAL2_6                    -Event Driven Sampling: Value 2 for Event 6
        //    EVENT_SRC_7                     -Event Driven Sampling: The source for Event 7
        //    EVENT_OPER_7                    -Event Driven Sampling: The operation for Event 7
        //    EVENT_VAL1_7                    -Event Driven Sampling: Value 1 for Event 7
        //    EVENT_VAL2_7                    -Event Driven Sampling: Value 2 for Event 7
        //    EVENT_SRC_8                     -Event Driven Sampling: The source for Event 8
        //    EVENT_OPER_8                    -Event Driven Sampling: The operation for Event 8
        //    EVENT_VAL1_8                    -Event Driven Sampling: Value 1 for Event 8
        //    EVENT_VAL2_8                    -Event Driven Sampling: Value 2 for Event 8
        //    LOW_PASS_FILTER_1               -The low pass filter for channels (1).
        //    LOW_PASS_FILTER_2               -The low pass filter for channels (2).
        //    LOW_PASS_FILTER_3               -The low pass filter for channels (3).
        //    LOW_PASS_FILTER_4               -The low pass filter for channels (4).
        //    MIN_SOFT_VER_MAJOR              -The minimum software version for support of this device (major)
        //    MIN_SOFT_VER_MINOR              -The minimum software version for support of this device (minor)
        //    GAUGE_FACTOR_1                  -The Gauge Factor (1)
        //    GAUGE_FACTOR_2                  -The Gauge Factor (2)
        //    GAUGE_FACTOR_3                  -The Gauge Factor (3)
        //    GAUGE_FACTOR_4                  -The Gauge Factor (4)
        //    
        //    THERMOCPL_TYPE                  -The thermocouple type for nodes with thermocouple capabilities (ie. TC-Link)
        //    FILTER_1                        -The first filter value for nodes with filter capabilities (ie. TC-Link)
        //    FILTER_2                        -The second filter value for nodes with 2 filter capabilities (ie. ENV-Link-Pro)

        //    LEGACY_DAMAGE_ANGLE_1           -The first damage angle (legacy).
        //    LEGACY_DAMAGE_ANGLE_2           -The second damage angle (legacy).
        //    LEGACY_DAMAGE_ANGLE_3           -The third damage angle (legacy).
        //    BIN_SIZE                        -The size of each bin in the histogram.
        //    RESET_BINS                      -Used to reset the histogram bin data.
        //    BIN_START                       -The start of the bins.
        //    PEAK_VALLEY_THRES               -The peak/valley threshold.
        //    SNCURVE_LOGA_1                  -logA of the first SN Curve.
        //    SNCURVE_M_1                     -m of the first SN Curve.
        //    SNCURVE_LOGA_2                  -logA of the second SN Curve.
        //    SNCURVE_M_2                     -m of the second SN Curve.
        //    SNCURVE_LOGA_3                  -logA of the third SN Curve.
        //    SNCURVE_M_3                     -m of the third SN Curve.
        //    YOUNGS_MODULUS                  -The youngs modulus.
        //    POISSONS_RATIO                  -The poissons ratio.
        //    HISTOGRAM_SAMPLE_RATE           -The same rate of the histogram.
        //    DAMAGE_ANGLE_1                  -The first damage angle.
        //    DAMAGE_ANGLE_2                  -The second damage angle.
        //    DAMAGE_ANGLE_3                  -The third damage angle.
        //    FATIGUE_MODE                    -SHM 3-angle mode vs Distributed Angle mode vs Raw Gauge Strain mode.
        //    DIST_ANGLE_NUM_ANGLES           -The number of angles for Distributed Angle Mode.
        //    DIST_ANGLE_LOWER_BOUND          -The lower bound for Distributed Angle Mode.
        //    DIST_ANGLE_UPPER_BOUND          -The upper bound for Distributed Angle Mode.

        //    HISTOGRAM_RAW_FLAG              -Raw mode enable/disable.
        //    ACT_SENSE_ENABLE                -Activity Sense enable/disable.
        //    ACT_SENSE_ACTIVE_THRES          -Activity Sense activity threshold.
        //    ACT_SENSE_INACTIVE_TIMEOUT      -Activity Sense inactivity timeout.
        //    ACT_SENSE_ACTIVE_TIME           -Activity Sense activity time.
        //    ACT_SENSE_INACTIVE_THRES        -Activity Sense inactivity threshold.
        //    HISTOGRAM_ENABLE                -Histogram enable/disable.
        //=======================================================================================================================
        static const EepromLocation CURRENT_LOG_PAGE;                //The next flash page to be used for datalogging
        static const EepromLocation CURRENT_PAGE_OFFSET;             //The byte offset location for the next datalogging session
        static const EepromLocation DATA_SETS_STORED;                //The # of datalogging sessions (triggers) stored in flash memory
        static const EepromLocation ACTIVE_CHANNEL_MASK;             //The channels that are enabled/disabled and will be sampled
        static const EepromLocation DATALOG_SAMPLE_RATE;             //The sample rate for Armed Datalogging sampling
        static const EepromLocation NUM_SWEEPS;                      //The # of sweeps (samples per data set) to sample for
        static const EepromLocation DEFAULT_MODE;                    //The default mode to allow the node to perform different operations on startup and after timeout
        static const EepromLocation SERIAL_ID;                       //The serial ID for the node. Combine with the model number for the full serial number
        static const EepromLocation SAMPLING_MODE;                   //The sampling mode of the node (Sync Sampling, Non-Sync Sampling, Armed Datalogging, etc.)
        static const EepromLocation HW_OFFSET_1;                     //The hardware offset of channel 1
        static const EepromLocation HW_OFFSET_2;                     //The hardware offset of channel 2
        static const EepromLocation HW_OFFSET_3;                     //The hardware offset of channel 3
        static const EepromLocation HW_OFFSET_4;                     //The hardware offset of channel 4
        static const EepromLocation HW_OFFSET_5;                     //The hardware offset of channel 5
        static const EepromLocation HW_OFFSET_6;                     //The hardware offset of channel 6
        static const EepromLocation HW_OFFSET_7;                     //The hardware offset of channel 7
        static const EepromLocation HW_OFFSET_8;                     //The hardware offset of channel 8
        static const EepromLocation SAMPLING_DELAY;                  //The sampling delay (amount of time between sensor excitation power up and A/D sampling)
        static const EepromLocation TDMA_ADDRESS;                    //The TDMA network address used for Synchronized Sampling
        static const EepromLocation COLLECTION_MODE;                 //The data collection mode (log, transmit) that affects standard sampling modes
        static const EepromLocation NUM_BUFF_PACKETS;                //The # of buffered packets
        static const EepromLocation NUM_RETRAN_ATTEMPTS;             //The # of retransmit attempts
        static const EepromLocation NODE_ADDRESS;                    //The node address of the wireless node
        static const EepromLocation SLEEP_INTERVAL;                  //The listen-for-wakeup interval for the node
        static const EepromLocation INACTIVE_TIMEOUT;                //The length of time necessary before a node enters sleep mode, if no user activity
        static const EepromLocation SAMPLE_RATE;                     //The sample rate for standard sampling modes (Synchronized Sampling, LDC)
        static const EepromLocation DATA_FORMAT;                     //The packet format (uint16, float, etc.) of sampled data
        static const EepromLocation SNIFF_DURATION;                  //The amount of time that the node listens for a wake packets 
        static const EepromLocation FREQUENCY;                       //The radio frequency channel
        static const EepromLocation TX_POWER_LEVEL;                  //The transmit output power of the radio
        static const EepromLocation UNLIMITED_SAMPLING;              //The unlimited sampling flag for standard sampling modes
        static const EepromLocation UNLIMITED_DATALOG;               //The unlimited sampling flag for Armed Datalogging sampling
        static const EepromLocation FIRMWARE_VER;                    //The firmware version of the node (part 1)
        static const EepromLocation FIRMWARE_VER2;                   //The firmware version of the node (part 2)
        static const EepromLocation MODEL_NUMBER;                    //The model number of the node
        static const EepromLocation MODEL_OPTION;                    //The model option of the node
        static const EepromLocation LEGACY_MODEL_NUMBER;             //The (legacy) model number of the node
        static const EepromLocation LEGACY_SERIAL_ID;                //The (legacy) serial ID for the node. Combine with the model number for the full serial number
        static const EepromLocation MAX_MEMORY;                      //The maximum number of pages available on the flash memory
        static const EepromLocation MICROCONTROLLER;                 //The ID of the microcontroller
        static const EepromLocation FW_ARCH_VER;                     //The firmware architecture version
        static const EepromLocation HW_GAIN_1;                       //The hardware gain of channel 1
        static const EepromLocation HW_GAIN_2;                       //The hardware gain of channel 2
        static const EepromLocation HW_GAIN_3;                       //The hardware gain of channel 3
        static const EepromLocation HW_GAIN_4;                       //The hardware gain of channel 4
        static const EepromLocation FLASH_ID;                        //The flash ID
        static const EepromLocation STORAGE_LIMIT_MODE;              //The storage limit mode.
        static const EepromLocation CH_ACTION_ID_1;                  //The channel action ID of channel 1
        static const EepromLocation CH_ACTION_SLOPE_1;               //The channel action slope of channel 1
        static const EepromLocation CH_ACTION_OFFSET_1;              //The channel action offset of channel 1
        static const EepromLocation CH_ACTION_ID_2;                  //The channel action ID of channel 2
        static const EepromLocation CH_ACTION_SLOPE_2;               //The channel action slope of channel 2
        static const EepromLocation CH_ACTION_OFFSET_2;              //The channel action offset of channel 2
        static const EepromLocation CH_ACTION_ID_3;                  //The channel action ID of channel 3
        static const EepromLocation CH_ACTION_SLOPE_3;               //The channel action slope of channel 3
        static const EepromLocation CH_ACTION_OFFSET_3;              //The channel action offset of channel 3
        static const EepromLocation CH_ACTION_ID_4;                  //The channel action ID of channel 4
        static const EepromLocation CH_ACTION_SLOPE_4;               //The channel action slope of channel 4
        static const EepromLocation CH_ACTION_OFFSET_4;              //The channel action offset of channel 4
        static const EepromLocation CH_ACTION_ID_5;                  //The channel action ID of channel 5
        static const EepromLocation CH_ACTION_SLOPE_5;               //The channel action slope of channel 5
        static const EepromLocation CH_ACTION_OFFSET_5;              //The channel action offset of channel 5
        static const EepromLocation CH_ACTION_ID_6;                  //The channel action ID of channel 6
        static const EepromLocation CH_ACTION_SLOPE_6;               //The channel action slope of channel 6
        static const EepromLocation CH_ACTION_OFFSET_6;              //The channel action offset of channel 6
        static const EepromLocation CH_ACTION_ID_7;                  //The channel action ID of channel 7
        static const EepromLocation CH_ACTION_SLOPE_7;               //The channel action slope of channel 7
        static const EepromLocation CH_ACTION_OFFSET_7;              //The channel action offset of channel 7
        static const EepromLocation CH_ACTION_ID_8;                  //The channel action ID of channel 8
        static const EepromLocation CH_ACTION_SLOPE_8;               //The channel action slope of channel 8
        static const EepromLocation CH_ACTION_OFFSET_8;              //The channel action offset of channel 8
        static const EepromLocation BOOTLOADER_VER;                  //The bootloader version number
        static const EepromLocation RESET_COUNTER;                   //The number of times the node has been turned on
        static const EepromLocation CYCLE_POWER;                     //Used to soft reset the node or the radio on the node
        static const EepromLocation RADIO_OPTIONS;                   //The options of the current radio (XR enabled or not, etc.)
        static const EepromLocation LOST_BEACON_TIMEOUT;             //The time for a node to wait before entering a low power state when no longer hearing a beacon in Sync Sampling
        static const EepromLocation SYNC_SAMPLE_SETTING;             //The Synchronized Sampling mode (Burst, Continuous, etc.)
        static const EepromLocation TX_PER_GROUP;                    //The transmissions per group for Synchronized Sampling
        static const EepromLocation GROUP_SIZE;                      //The group size for Synchronized Sampling
        static const EepromLocation TIME_BETW_SESSIONS;              //The time between each burst for Synchronized Sampling
        static const EepromLocation NODE_RETRANSMIT;                 //Node retranmission enable/disable (for Lossless)
        static const EepromLocation MAX_RETRANS_PACKET;              //The max retransmits per packet
        static const EepromLocation MAX_RETRANS_BURST;               //The max retransmits per burst
        static const EepromLocation REGION_CODE;                     //The region code for the device.
        static const EepromLocation DATA_PACKET_FORMAT;              //The format of the data packets that will sent out.
        static const EepromLocation DIAGNOSTIC_INTERVAL;             //The interval at which the Diagnostic Packet is sent.
        static const EepromLocation EVENT_SAMPLE_RATE;               //Event Driven Sampling: Sample Rate
        static const EepromLocation EVENT_TRIGGER_MASK;              //Event Driven Sampling: Trigger Mask
        static const EepromLocation EVENT_PRE_DURATION;              //Event Driven Sampling: Pre-Event Duration
        static const EepromLocation EVENT_POST_DURATION;             //Event Driven Sampling: Post-Event Duration
        static const EepromLocation EVENT_SRC_1;                     //Event Driven Sampling: The source for Event 1
        static const EepromLocation EVENT_OPER_1;                    //Event Driven Sampling: The operation for Event 1
        static const EepromLocation EVENT_VAL1_1;                    //Event Driven Sampling: Value 1 for Event 1
        static const EepromLocation EVENT_VAL2_1;                    //Event Driven Sampling: Value 2 for Event 1
        static const EepromLocation EVENT_SRC_2;                     //Event Driven Sampling: The source for Event 2
        static const EepromLocation EVENT_OPER_2;                    //Event Driven Sampling: The operation for Event 2
        static const EepromLocation EVENT_VAL1_2;                    //Event Driven Sampling: Value 1 for Event 2
        static const EepromLocation EVENT_VAL2_2;                    //Event Driven Sampling: Value 2 for Event 2
        static const EepromLocation EVENT_SRC_3;                     //Event Driven Sampling: The source for Event 3
        static const EepromLocation EVENT_OPER_3;                    //Event Driven Sampling: The operation for Event 3
        static const EepromLocation EVENT_VAL1_3;                    //Event Driven Sampling: Value 1 for Event 3
        static const EepromLocation EVENT_VAL2_3;                    //Event Driven Sampling: Value 2 for Event 3
        static const EepromLocation EVENT_SRC_4;                     //Event Driven Sampling: The source for Event 4
        static const EepromLocation EVENT_OPER_4;                    //Event Driven Sampling: The operation for Event 4
        static const EepromLocation EVENT_VAL1_4;                    //Event Driven Sampling: Value 1 for Event 4
        static const EepromLocation EVENT_VAL2_4;                    //Event Driven Sampling: Value 2 for Event 4
        static const EepromLocation EVENT_SRC_5;                     //Event Driven Sampling: The source for Event 5
        static const EepromLocation EVENT_OPER_5;                    //Event Driven Sampling: The operation for Event 5
        static const EepromLocation EVENT_VAL1_5;                    //Event Driven Sampling: Value 1 for Event 5
        static const EepromLocation EVENT_VAL2_5;                    //Event Driven Sampling: Value 2 for Event 5
        static const EepromLocation EVENT_SRC_6;                     //Event Driven Sampling: The source for Event 6
        static const EepromLocation EVENT_OPER_6;                    //Event Driven Sampling: The operation for Event 6
        static const EepromLocation EVENT_VAL1_6;                    //Event Driven Sampling: Value 1 for Event 6
        static const EepromLocation EVENT_VAL2_6;                    //Event Driven Sampling: Value 2 for Event 6
        static const EepromLocation EVENT_SRC_7;                     //Event Driven Sampling: The source for Event 7
        static const EepromLocation EVENT_OPER_7;                    //Event Driven Sampling: The operation for Event 7
        static const EepromLocation EVENT_VAL1_7;                    //Event Driven Sampling: Value 1 for Event 7
        static const EepromLocation EVENT_VAL2_7;                    //Event Driven Sampling: Value 2 for Event 7
        static const EepromLocation EVENT_SRC_8;                     //Event Driven Sampling: The source for Event 8
        static const EepromLocation EVENT_OPER_8;                    //Event Driven Sampling: The operation for Event 8
        static const EepromLocation EVENT_VAL1_8;                    //Event Driven Sampling: Value 1 for Event 8
        static const EepromLocation EVENT_VAL2_8;                    //Event Driven Sampling: Value 2 for Event 8
        static const EepromLocation LOW_PASS_FILTER_1;               //The low pass filter for channels (1).
        static const EepromLocation LOW_PASS_FILTER_2;               //The low pass filter for channels (2).
        static const EepromLocation LOW_PASS_FILTER_3;               //The low pass filter for channels (3).
        static const EepromLocation LOW_PASS_FILTER_4;               //The low pass filter for channels (4).
        static const EepromLocation MIN_SOFT_VER_MAJOR;              //The minimum software version for support of this device (major).
        static const EepromLocation MIN_SOFT_VER_MINOR;              //The minimum software version for support of this device (minor).
        static const EepromLocation GAUGE_FACTOR_1;                  //The Gauge Factor (1).
        static const EepromLocation GAUGE_FACTOR_2;                  //The Gauge Factor (2).
        static const EepromLocation GAUGE_FACTOR_3;                  //The Gauge Factor (3).
        static const EepromLocation GAUGE_FACTOR_4;                  //The Gauge Factor (4).
            
        static const EepromLocation THERMOCPL_TYPE;                  //The thermocouple type for nodes with thermocouple capabilities (ie. TC-Link)
        static const EepromLocation FILTER_1;                        //The first filter value for nodes with filter capabilities (ie. TC-Link)
        static const EepromLocation FILTER_2;                        //The second filter value for nodes with 2 filter capabilities (ie. ENV-Link-Pro)
    
        static const EepromLocation LEGACY_DAMAGE_ANGLE_1;           //The first damage angle (legacy).
        static const EepromLocation LEGACY_DAMAGE_ANGLE_2;           //The second damage angle (legacy).
        static const EepromLocation LEGACY_DAMAGE_ANGLE_3;           //The third damage angle (legacy).
        static const EepromLocation BIN_SIZE;                        //The size of each bin in the histogram.
        static const EepromLocation RESET_BINS;                      //Used to reset the histogram bin data.
        static const EepromLocation BIN_START;                       //The start of the bins.
        static const EepromLocation PEAK_VALLEY_THRES;               //The peak/valley threshold.
        static const EepromLocation SNCURVE_LOGA_1;                  //logA of the first SN Curve.
        static const EepromLocation SNCURVE_M_1;                     //m of the first SN Curve.
        static const EepromLocation SNCURVE_LOGA_2;                  //logA of the second SN Curve.
        static const EepromLocation SNCURVE_M_2;                     //m of the second SN Curve.
        static const EepromLocation SNCURVE_LOGA_3;                  //logA of the third SN Curve.
        static const EepromLocation SNCURVE_M_3;                     //m of the third SN Curve.
        static const EepromLocation YOUNGS_MODULUS;                  //The youngs modulus.
        static const EepromLocation POISSONS_RATIO;                  //The poissons ratio.
        static const EepromLocation HISTOGRAM_SAMPLE_RATE;           //The same rate of the histogram.
        static const EepromLocation DAMAGE_ANGLE_1;                  //The first damage angle.
        static const EepromLocation DAMAGE_ANGLE_2;                  //The second damage angle.
        static const EepromLocation DAMAGE_ANGLE_3;                  //The third damage angle.
        static const EepromLocation FATIGUE_MODE;                    //Fatigue 3-angle mode vs Distributed Angle mode vs Raw Gauge Strain mode.
        static const EepromLocation DIST_ANGLE_NUM_ANGLES;           //The number of angles for Distributed Angle Mode.
        static const EepromLocation DIST_ANGLE_LOWER_BOUND;          //The lower bound for Distributed Angle Mode.
        static const EepromLocation DIST_ANGLE_UPPER_BOUND;          //The upper bound for Distributed Angle Mode.
        static const EepromLocation HISTOGRAM_RAW_FLAG;              //Raw mode enable/disable.
        static const EepromLocation ACT_SENSE_ENABLE;                //Activity Sense enable/disable.
        static const EepromLocation ACT_SENSE_ACTIVE_THRES;          //Activity Sense activity threshold.
        static const EepromLocation ACT_SENSE_INACTIVE_TIMEOUT;      //Activity Sense inactivity timeout.
        static const EepromLocation ACT_SENSE_ACTIVE_TIME;           //Activity Sense activity time.
        static const EepromLocation ACT_SENSE_INACTIVE_THRES;        //Activity Sense inactivity threshold.
        static const EepromLocation HISTOGRAM_ENABLE;                //Histogram enable/disable.
        
    };
}