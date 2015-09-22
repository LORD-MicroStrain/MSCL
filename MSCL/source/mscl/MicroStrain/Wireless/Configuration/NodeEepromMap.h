/*****************************************************************************
Copyright(c) 2015 LORD Corporation. All rights reserved.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the included
LICENSE.txt file for a copy of the full GNU General Public License.
*****************************************************************************/
#pragma once

#include "EepromLocation.h"
#include "mscl/MicroStrain/Wireless/WirelessModels.h"

namespace mscl
{
	//Class: NodeEepromMap
	//	Contains information on every EEPROM available on Wireless Nodes
	class NodeEepromMap
	{
	private:
		NodeEepromMap();								//disabled default constructor
		NodeEepromMap(const NodeEepromMap&);			//disabled copy constructor
		NodeEepromMap& operator=(const NodeEepromMap&);	//disabled assignement operator

	public:
		//Function: canUseCache_read
		//	Gets whether or not the specified eeprom location can use the eeprom cache for reading, or should always be read from the Node.
		//
		//Parameters:
		//	eepromLocation - The eepromLocation that is in question
		//
		//Returns:
		//	true if the location can use the cache for reading, false if the location should be read from the Node.
		static bool canUseCache_read(uint16 eepromLocation);

		//Function: canUseCache_write
		//	Gets whether or not the specified eeprom location can use the eeprom cache for writing, or should always be written to the Node.
		//
		//Parameters:
		//	eepromLocation - The eepromLocation that is in question
		//
		//Returns:
		//	true if the location can use the cache for writing, false if the location should always be written to the Node.
		static bool canUseCache_write(uint16 eepromLocation);

		//Function: getOffsetEeprom
		//	Finds the offset <EepromLocation> that goes with the given slope <EepromLocation>.
		//
		//Parameters:
		//	slopeEeprom - The slope <EepromLocation> that the offset eeprom goes with.
		//
		//Returns:
		//	The offset <EepromLocation>.
		static EepromLocation getOffsetEeprom(const EepromLocation& slopeEeprom);

		//=======================================================================================================================
		//Constants: Eeprom Locations
		//
		//	CURRENT_LOG_PAGE		-The next flash page to be used for datalogging
		//	CURRENT_PAGE_OFFSET		-The byte offset location for the next datalogging session
		//	DATA_SETS_STORED		-The # of datalogging sessions (triggers) stored in flash memory
		//	ACTIVE_CHANNEL_MASK		-The channels that are enabled/disabled and will be sampled
		//	DATALOG_SAMPLE_RATE		-The sample rate for Armed Datalogging sampling
		//	NUM_SWEEPS				-The # of sweeps (samples per data set) to sample for
		//	DEFAULT_MODE			-The default mode to allow the node to perform different operations on startup and after timeout
		//	SERIAL_ID				-The serial ID for the node. Combine with the model number for the full serial number
		//	SAMPLING_MODE			-The sampling mode of the node (Sync Sampling, Non-Sync Sampling, Armed Datalogging, etc.)
		//	HW_OFFSET_1				-The hardware offset of channel 1
		//	HW_OFFSET_2				-The hardware offset of channel 2
		//	HW_OFFSET_3				-The hardware offset of channel 3
		//	HW_OFFSET_4				-The hardware offset of channel 4
		//	HW_OFFSET_5				-The hardware offset of channel 5
		//	HW_OFFSET_6				-The hardware offset of channel 6
		//	HW_OFFSET_7				-The hardware offset of channel 7
		//	HW_OFFSET_8				-The hardware offset of channel 8
		//	SAMPLING_DELAY			-The sampling delay (amount of time between sensor excitation power up and A/D sampling
		//	TDMA_ADDRESS			-The TDMA network address used for Synchronized Sampling
		//	COLLECTION_MODE			-The data collection mode (log, transmit) that affects standard sampling modes
		//	NUM_BUFF_PACKETS		-The # of buffered packets
		//	NUM_RETRAN_ATTEMPTS		-The # of retransmit attempts
		//	NODE_ADDRESS			-The node address of the wireless node
		//	SLEEP_INTERVAL			-The listen-for-wakeup interval for the node
		//	INACTIVE_TIMEOUT		-The length of time necessary before a node enters sleep mode, if no user activity
		//	SAMPLE_RATE				-The sample rate for standard sampling modes (Synchronized Sampling, LDC)
		//	DATA_FORMAT				-The packet format (uint16, float, etc.) of sampled data
		//	SNIFF_DURATION			-The amount of time that the node listens for a wake packets 
		//	FREQUENCY				-The radio frequency channel
		//	TX_POWER_LEVEL			-The transmit output power of the radio
		//	UNLIMITED_SAMPLING		-The unlimited sampling flag for standard sampling modes
		//	UNLIMITED_DATALOG		-The unlimited sampling flag for Armed Datalogging sampling
		//	FIRMWARE_VER			-The firmware version of the node (part 1)
		//	FIRMWARE_VER2			-The firmware version of the node (part 2)
		//	MODEL_NUMBER			-The model number of the node	
		//	MODEL_OPTION			-The model option of the node
		//	LEGACY_MODEL_NUMBER		-The (legacy) model number of the node
		//	LEGACY_SERIAL_ID		-The (legacy) serial ID for the node. Combine with the model number for the full serial number
		//	MAX_MEMORY				-The maximum number of pages available on the flash memory
		//	MICROCONTROLLER			-The ID of the microcontroller
		//	FW_ARCH_VER				-The firmware architecture version
		//	HW_GAIN_1				-The hardware gain of channel 1
		//	HW_GAIN_2				-The hardware gain of channel 2
		//	HW_GAIN_3				-The hardware gain of channel 3
		//	HW_GAIN_4				-The hardware gain of channel 4
		//	HW_GAIN_5				-The hardware gain of channel 5
		//	HW_GAIN_6				-The hardware gain of channel 6
		//	HW_GAIN_7				-The hardware gain of channel 7
		//	HW_GAIN_8				-The hardware gain of channel 8
		//	CH_ACTION_ID_1			-The channel action ID of channel 1
		//	CH_ACTION_SLOPE_1		-The channel action slope of channel 1
		//	CH_ACTION_OFFSET_1		-The channel action offset of channel 1
		//	CH_ACTION_ID_2			-The channel action ID of channel 2
		//	CH_ACTION_SLOPE_2		-The channel action slope of channel 2
		//	CH_ACTION_OFFSET_2		-The channel action offset of channel 2
		//	CH_ACTION_ID_3			-The channel action ID of channel 3
		//	CH_ACTION_SLOPE_3		-The channel action slope of channel 3
		//	CH_ACTION_OFFSET_3		-The channel action offset of channel 3
		//	CH_ACTION_ID_4			-The channel action ID of channel 4
		//	CH_ACTION_SLOPE_4		-The channel action slope of channel 4
		//	CH_ACTION_OFFSET_4		-The channel action offset of channel 4
		//	CH_ACTION_ID_5			-The channel action ID of channel 5
		//	CH_ACTION_SLOPE_5		-The channel action slope of channel 5
		//	CH_ACTION_OFFSET_5		-The channel action offset of channel 5
		//	CH_ACTION_ID_6			-The channel action ID of channel 6
		//	CH_ACTION_SLOPE_6		-The channel action slope of channel 6
		//	CH_ACTION_OFFSET_6		-The channel action offset of channel 6
		//	CH_ACTION_ID_7			-The channel action ID of channel 7
		//	CH_ACTION_SLOPE_7		-The channel action slope of channel 7
		//	CH_ACTION_OFFSET_7		-The channel action offset of channel 7
		//	CH_ACTION_ID_8			-The channel action ID of channel 8
		//	CH_ACTION_SLOPE_8		-The channel action slope of channel 8
		//	CH_ACTION_OFFSET_8		-The channel action offset of channel 8
		//	BOOTLOADER_VER			-The bootloader version number
		//	RESET_COUNTER			-The number of times the node has been turned on
		//	CYCLE_POWER				-Used to soft reset the node or the radio on the node
		//	RADIO_OPTIONS			-The options of the current radio (XR enabled or not, etc.)
		//	LOST_BEACON_TIMEOUT		-The time for a node to wait before entering a low power state when no longer hearing a beacon in Sync Sampling
		//	SYNC_SAMPLE_SETTING		-The Synchronized Sampling mode (Burst, Continuous, etc.)
		//	TX_PER_GROUP			-The transmissions per group for Synchronized Sampling
		//	GROUP_SIZE				-The group size for Synchronized Sampling
		//	TIME_BETW_SESSIONS		-The time between each burst for Synchronized Sampling
		//	NODE_RETRANSMIT			-Node retranmission enable/disable (for Lossless)
		//	MAX_RETRANS_PACKET		-The max retransmits per packet
		//	MAX_RETRANS_BURST		-The max retransmits per burst
		//	REGION_CODE				-The region code for the device
		//	EVENT_SAMPLE_RATE		-Event Driven Sampling: Sample Rate
		//	EVENT_CHANNEL_MASK		-Event Driven Sampling: Channel Mask
		//	EVENT_PRE_DURATION		-Event Driven Sampling: Pre-Event Duration
		//	EVENT_POST_DURATION		-Event Driven Sampling: Post-Event Duration
		//	EVENT_SRC_1				-Event Driven Sampling: The source for Event 1
		//	EVENT_OPER_1			-Event Driven Sampling: The operation for Event 1
		//	EVENT_VAL1_1			-Event Driven Sampling: Value 1 for Event 1
		//	EVENT_VAL2_1			-Event Driven Sampling: Value 2 for Event 1
		//	EVENT_SRC_2				-Event Driven Sampling: The source for Event 2
		//	EVENT_OPER_2			-Event Driven Sampling: The operation for Event 2
		//	EVENT_VAL1_2			-Event Driven Sampling: Value 1 for Event 2
		//	EVENT_VAL2_2			-Event Driven Sampling: Value 2 for Event 2
		//	EVENT_SRC_3				-Event Driven Sampling: The source for Event 3
		//	EVENT_OPER_3			-Event Driven Sampling: The operation for Event 3
		//	EVENT_VAL1_3			-Event Driven Sampling: Value 1 for Event 3
		//	EVENT_VAL2_3			-Event Driven Sampling: Value 2 for Event 3
		//	EVENT_SRC_4				-Event Driven Sampling: The source for Event 4
		//	EVENT_OPER_4			-Event Driven Sampling: The operation for Event 4
		//	EVENT_VAL1_4			-Event Driven Sampling: Value 1 for Event 4
		//	EVENT_VAL2_4			-Event Driven Sampling: Value 2 for Event 4
		//	EVENT_SRC_5				-Event Driven Sampling: The source for Event 5
		//	EVENT_OPER_5			-Event Driven Sampling: The operation for Event 5
		//	EVENT_VAL1_5			-Event Driven Sampling: Value 1 for Event 5
		//	EVENT_VAL2_5			-Event Driven Sampling: Value 2 for Event 5
		//	EVENT_SRC_6				-Event Driven Sampling: The source for Event 6
		//	EVENT_OPER_6			-Event Driven Sampling: The operation for Event 6
		//	EVENT_VAL1_6			-Event Driven Sampling: Value 1 for Event 6
		//	EVENT_VAL2_6			-Event Driven Sampling: Value 2 for Event 6
		//	EVENT_SRC_7				-Event Driven Sampling: The source for Event 7
		//	EVENT_OPER_7			-Event Driven Sampling: The operation for Event 7
		//	EVENT_VAL1_7			-Event Driven Sampling: Value 1 for Event 7
		//	EVENT_VAL2_7			-Event Driven Sampling: Value 2 for Event 7
		//	EVENT_SRC_8				-Event Driven Sampling: The source for Event 8
		//	EVENT_OPER_8			-Event Driven Sampling: The operation for Event 8
		//	EVENT_VAL1_8			-Event Driven Sampling: Value 1 for Event 8
		//	EVENT_VAL2_8			-Event Driven Sampling: Value 2 for Event 8
		//	CHANNEL_FILTER			-The channel filter for all channels
		//	MIN_SOFT_VER_MAJOR		-The minimum software version for support of this device (major)
		//	MIN_SOFT_VER_MINOR		-The minimum software version for support of this device (minor)
		//
		//	THERMOCPL_TYPE			-The thermocouple type for nodes with thermocouple capabilities (ie. TC-Link)
		//	FILTER_1				-The first filter value for nodes with filter capabilities (ie. TC-Link)
		//	FILTER_2				-The second filter value for nodes with 2 filter capabilities (ie. ENV-Link-Pro)
		//=======================================================================================================================
		static const EepromLocation CURRENT_LOG_PAGE;		//The next flash page to be used for datalogging
		static const EepromLocation CURRENT_PAGE_OFFSET;	//The byte offset location for the next datalogging session
		static const EepromLocation DATA_SETS_STORED;		//The # of datalogging sessions (triggers) stored in flash memory
		static const EepromLocation ACTIVE_CHANNEL_MASK;	//The channels that are enabled/disabled and will be sampled
		static const EepromLocation DATALOG_SAMPLE_RATE;	//The sample rate for Armed Datalogging sampling
		static const EepromLocation NUM_SWEEPS;				//The # of sweeps (samples per data set) to sample for
		static const EepromLocation DEFAULT_MODE;			//The default mode to allow the node to perform different operations on startup and after timeout
		static const EepromLocation SERIAL_ID;				//The serial ID for the node. Combine with the model number for the full serial number
		static const EepromLocation	SAMPLING_MODE;			//The sampling mode of the node (Sync Sampling, Non-Sync Sampling, Armed Datalogging, etc.)
		static const EepromLocation HW_OFFSET_1;			//The hardware offset of channel 1
		static const EepromLocation HW_OFFSET_2;			//The hardware offset of channel 2
		static const EepromLocation HW_OFFSET_3;			//The hardware offset of channel 3
		static const EepromLocation HW_OFFSET_4;			//The hardware offset of channel 4
		static const EepromLocation HW_OFFSET_5;			//The hardware offset of channel 5
		static const EepromLocation HW_OFFSET_6;			//The hardware offset of channel 6
		static const EepromLocation HW_OFFSET_7;			//The hardware offset of channel 7
		static const EepromLocation HW_OFFSET_8;			//The hardware offset of channel 8
		static const EepromLocation SAMPLING_DELAY;			//The sampling delay (amount of time between sensor excitation power up and A/D sampling)
		static const EepromLocation TDMA_ADDRESS;			//The TDMA network address used for Synchronized Sampling
		static const EepromLocation COLLECTION_MODE;		//The data collection mode (log, transmit) that affects standard sampling modes
		static const EepromLocation NUM_BUFF_PACKETS;		//The # of buffered packets
		static const EepromLocation NUM_RETRAN_ATTEMPTS;	//The # of retransmit attempts
		static const EepromLocation NODE_ADDRESS;			//The node address of the wireless node
		static const EepromLocation SLEEP_INTERVAL;			//The listen-for-wakeup interval for the node
		static const EepromLocation INACTIVE_TIMEOUT;		//The length of time necessary before a node enters sleep mode, if no user activity
		static const EepromLocation SAMPLE_RATE;			//The sample rate for standard sampling modes (Synchronized Sampling, LDC)
		static const EepromLocation DATA_FORMAT;			//The packet format (uint16, float, etc.) of sampled data
		static const EepromLocation SNIFF_DURATION;			//The amount of time that the node listens for a wake packets 
		static const EepromLocation FREQUENCY;				//The radio frequency channel
		static const EepromLocation TX_POWER_LEVEL;			//The transmit output power of the radio
		static const EepromLocation UNLIMITED_SAMPLING;		//The unlimited sampling flag for standard sampling modes
		static const EepromLocation UNLIMITED_DATALOG;		//The unlimited sampling flag for Armed Datalogging sampling
		static const EepromLocation FIRMWARE_VER;			//The firmware version of the node (part 1)
		static const EepromLocation FIRMWARE_VER2;			//The firmware version of the node (part 2)
		static const EepromLocation MODEL_NUMBER;			//The model number of the node
		static const EepromLocation MODEL_OPTION;			//The model option of the node
		static const EepromLocation LEGACY_MODEL_NUMBER;	//The (legacy) model number of the node
		static const EepromLocation LEGACY_SERIAL_ID;		//The (legacy) serial ID for the node. Combine with the model number for the full serial number
		static const EepromLocation MAX_MEMORY;				//The maximum number of pages available on the flash memory
		static const EepromLocation MICROCONTROLLER;		//The ID of the microcontroller
		static const EepromLocation FW_ARCH_VER;			//The firmware architecture version
		static const EepromLocation HW_GAIN_1;				//The hardware gain of channel 1
		static const EepromLocation HW_GAIN_2;				//The hardware gain of channel 2
		static const EepromLocation HW_GAIN_3;				//The hardware gain of channel 3
		static const EepromLocation HW_GAIN_4;				//The hardware gain of channel 4
		static const EepromLocation CH_ACTION_ID_1;			//The channel action ID of channel 1
		static const EepromLocation CH_ACTION_SLOPE_1;		//The channel action slope of channel 1
		static const EepromLocation CH_ACTION_OFFSET_1;		//The channel action offset of channel 1
		static const EepromLocation CH_ACTION_ID_2;			//The channel action ID of channel 2
		static const EepromLocation CH_ACTION_SLOPE_2;		//The channel action slope of channel 2
		static const EepromLocation CH_ACTION_OFFSET_2;		//The channel action offset of channel 2
		static const EepromLocation CH_ACTION_ID_3;			//The channel action ID of channel 3
		static const EepromLocation CH_ACTION_SLOPE_3;		//The channel action slope of channel 3
		static const EepromLocation CH_ACTION_OFFSET_3;		//The channel action offset of channel 3
		static const EepromLocation CH_ACTION_ID_4;			//The channel action ID of channel 4
		static const EepromLocation CH_ACTION_SLOPE_4;		//The channel action slope of channel 4
		static const EepromLocation CH_ACTION_OFFSET_4;		//The channel action offset of channel 4
		static const EepromLocation CH_ACTION_ID_5;			//The channel action ID of channel 5
		static const EepromLocation CH_ACTION_SLOPE_5;		//The channel action slope of channel 5
		static const EepromLocation CH_ACTION_OFFSET_5;		//The channel action offset of channel 5
		static const EepromLocation CH_ACTION_ID_6;			//The channel action ID of channel 6
		static const EepromLocation CH_ACTION_SLOPE_6;		//The channel action slope of channel 6
		static const EepromLocation CH_ACTION_OFFSET_6;		//The channel action offset of channel 6
		static const EepromLocation CH_ACTION_ID_7;			//The channel action ID of channel 7
		static const EepromLocation CH_ACTION_SLOPE_7;		//The channel action slope of channel 7
		static const EepromLocation CH_ACTION_OFFSET_7;		//The channel action offset of channel 7
		static const EepromLocation CH_ACTION_ID_8;			//The channel action ID of channel 8
		static const EepromLocation CH_ACTION_SLOPE_8;		//The channel action slope of channel 8
		static const EepromLocation CH_ACTION_OFFSET_8;		//The channel action offset of channel 8
		static const EepromLocation BOOTLOADER_VER;			//The bootloader version number
		static const EepromLocation RESET_COUNTER;			//The number of times the node has been turned on
		static const EepromLocation CYCLE_POWER;			//Used to soft reset the node or the radio on the node
		static const EepromLocation RADIO_OPTIONS;			//The options of the current radio (XR enabled or not, etc.)
		static const EepromLocation LOST_BEACON_TIMEOUT;	//The time for a node to wait before entering a low power state when no longer hearing a beacon in Sync Sampling
		static const EepromLocation SYNC_SAMPLE_SETTING;	//The Synchronized Sampling mode (Burst, Continuous, etc.)
		static const EepromLocation TX_PER_GROUP;			//The transmissions per group for Synchronized Sampling
		static const EepromLocation GROUP_SIZE;				//The group size for Synchronized Sampling
		static const EepromLocation TIME_BETW_SESSIONS;		//The time between each burst for Synchronized Sampling
		static const EepromLocation NODE_RETRANSMIT;		//Node retranmission enable/disable (for Lossless)
		static const EepromLocation MAX_RETRANS_PACKET;		//The max retransmits per packet
		static const EepromLocation MAX_RETRANS_BURST;		//The max retransmits per burst
		static const EepromLocation REGION_CODE;			//The region code for the device.
		static const EepromLocation EVENT_SAMPLE_RATE;		//Event Driven Sampling: Sample Rate
		static const EepromLocation EVENT_CHANNEL_MASK;		//Event Driven Sampling: Channel Mask
		static const EepromLocation EVENT_PRE_DURATION;		//Event Driven Sampling: Pre-Event Duration
		static const EepromLocation EVENT_POST_DURATION;	//Event Driven Sampling: Post-Event Duration
		static const EepromLocation EVENT_SRC_1;			//Event Driven Sampling: The source for Event 1
		static const EepromLocation EVENT_OPER_1;			//Event Driven Sampling: The operation for Event 1
		static const EepromLocation EVENT_VAL1_1;			//Event Driven Sampling: Value 1 for Event 1
		static const EepromLocation EVENT_VAL2_1;			//Event Driven Sampling: Value 2 for Event 1
		static const EepromLocation EVENT_SRC_2	;			//Event Driven Sampling: The source for Event 2
		static const EepromLocation EVENT_OPER_2;			//Event Driven Sampling: The operation for Event 2
		static const EepromLocation EVENT_VAL1_2;			//Event Driven Sampling: Value 1 for Event 2
		static const EepromLocation EVENT_VAL2_2;			//Event Driven Sampling: Value 2 for Event 2
		static const EepromLocation EVENT_SRC_3	;			//Event Driven Sampling: The source for Event 3
		static const EepromLocation EVENT_OPER_3;			//Event Driven Sampling: The operation for Event 3
		static const EepromLocation EVENT_VAL1_3;			//Event Driven Sampling: Value 1 for Event 3
		static const EepromLocation EVENT_VAL2_3;			//Event Driven Sampling: Value 2 for Event 3
		static const EepromLocation EVENT_SRC_4	;			//Event Driven Sampling: The source for Event 4
		static const EepromLocation EVENT_OPER_4;			//Event Driven Sampling: The operation for Event 4
		static const EepromLocation EVENT_VAL1_4;			//Event Driven Sampling: Value 1 for Event 4
		static const EepromLocation EVENT_VAL2_4;			//Event Driven Sampling: Value 2 for Event 4
		static const EepromLocation EVENT_SRC_5	;			//Event Driven Sampling: The source for Event 5
		static const EepromLocation EVENT_OPER_5;			//Event Driven Sampling: The operation for Event 5
		static const EepromLocation EVENT_VAL1_5;			//Event Driven Sampling: Value 1 for Event 5
		static const EepromLocation EVENT_VAL2_5;			//Event Driven Sampling: Value 2 for Event 5
		static const EepromLocation EVENT_SRC_6	;			//Event Driven Sampling: The source for Event 6
		static const EepromLocation EVENT_OPER_6;			//Event Driven Sampling: The operation for Event 6
		static const EepromLocation EVENT_VAL1_6;			//Event Driven Sampling: Value 1 for Event 6
		static const EepromLocation EVENT_VAL2_6;			//Event Driven Sampling: Value 2 for Event 6
		static const EepromLocation EVENT_SRC_7	;			//Event Driven Sampling: The source for Event 7
		static const EepromLocation EVENT_OPER_7;			//Event Driven Sampling: The operation for Event 7
		static const EepromLocation EVENT_VAL1_7;			//Event Driven Sampling: Value 1 for Event 7
		static const EepromLocation EVENT_VAL2_7;			//Event Driven Sampling: Value 2 for Event 7
		static const EepromLocation EVENT_SRC_8	;			//Event Driven Sampling: The source for Event 8
		static const EepromLocation EVENT_OPER_8;			//Event Driven Sampling: The operation for Event 8
		static const EepromLocation EVENT_VAL1_8;			//Event Driven Sampling: Value 1 for Event 8
		static const EepromLocation EVENT_VAL2_8;			//Event Driven Sampling: Value 2 for Event 8
		static const EepromLocation CHANNEL_FILTER;			//The channel filter for all channels
		static const EepromLocation MIN_SOFT_VER_MAJOR;		//The minimum software version for support of this device (major).
		static const EepromLocation MIN_SOFT_VER_MINOR;		//The minimum software version for support of this device (minor).
		
		static const EepromLocation THERMOCPL_TYPE;			//The thermocouple type for nodes with thermocouple capabilities (ie. TC-Link)
		static const EepromLocation FILTER_1;				//The first filter value for nodes with filter capabilities (ie. TC-Link)
		static const EepromLocation FILTER_2;				//The second filter value for nodes with 2 filter capabilities (ie. ENV-Link-Pro)

		static const EepromLocation DAMAGE_ANGLE_1;
		static const EepromLocation DAMAGE_ANGLE_2;
		static const EepromLocation DAMAGE_ANGLE_3;
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
		static const EepromLocation YOUNGS_MODULUS;
		static const EepromLocation POISSONS_RATIO;
		static const EepromLocation HISTOGRAM_SAMPLE_RATE;
		static const EepromLocation HISTOGRAM_RAW_FLAG;
	};
}