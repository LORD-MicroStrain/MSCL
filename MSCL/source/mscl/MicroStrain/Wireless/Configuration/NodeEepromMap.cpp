/*******************************************************************************
Copyright(c) 2015 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"
#include "NodeEepromMap.h"

#include "mscl/Types.h"

namespace mscl
{
	const EepromLocation NodeEepromMap::CURRENT_LOG_PAGE		(0, valueType_uint16);
	const EepromLocation NodeEepromMap::CURRENT_PAGE_OFFSET		(2, valueType_uint16);
	const EepromLocation NodeEepromMap::DATA_SETS_STORED		(4, valueType_uint16);
	const EepromLocation NodeEepromMap::ACTIVE_CHANNEL_MASK		(12, valueType_uint16);
	const EepromLocation NodeEepromMap::DATALOG_SAMPLE_RATE		(14, valueType_uint16);
	const EepromLocation NodeEepromMap::NUM_SWEEPS				(16, valueType_uint16);
	const EepromLocation NodeEepromMap::DEFAULT_MODE			(18, valueType_uint16);
	const EepromLocation NodeEepromMap::SERIAL_ID				(20, valueType_uint32);
	const EepromLocation NodeEepromMap::SAMPLING_MODE			(24, valueType_uint16);
	const EepromLocation NodeEepromMap::HW_OFFSET_1				(26, valueType_uint16);
	const EepromLocation NodeEepromMap::HW_OFFSET_2				(28, valueType_uint16);
	const EepromLocation NodeEepromMap::HW_OFFSET_3				(30, valueType_uint16);
	const EepromLocation NodeEepromMap::HW_OFFSET_4				(32, valueType_uint16);
	const EepromLocation NodeEepromMap::SAMPLING_DELAY			(34, valueType_uint16);
	const EepromLocation NodeEepromMap::TDMA_ADDRESS			(36, valueType_uint16);
	const EepromLocation NodeEepromMap::COLLECTION_MODE			(38, valueType_uint16);
	const EepromLocation NodeEepromMap::NUM_BUFF_PACKETS		(40, valueType_uint16);
	const EepromLocation NodeEepromMap::NUM_RETRAN_ATTEMPTS		(44, valueType_uint16);
	const EepromLocation NodeEepromMap::MODEL_NUMBER			(46, valueType_uint16);
	const EepromLocation NodeEepromMap::MODEL_OPTION			(48, valueType_uint16);
	const EepromLocation NodeEepromMap::NODE_ADDRESS			(50, valueType_uint16);
	const EepromLocation NodeEepromMap::SLEEP_INTERVAL			(66, valueType_uint16);
	const EepromLocation NodeEepromMap::INACTIVE_TIMEOUT		(70, valueType_uint16);
	const EepromLocation NodeEepromMap::SAMPLE_RATE				(72, valueType_uint16);
	const EepromLocation NodeEepromMap::DATA_FORMAT				(76, valueType_uint16);
	const EepromLocation NodeEepromMap::SNIFF_DURATION			(78, valueType_uint16);
	const EepromLocation NodeEepromMap::FREQUENCY				(90, valueType_uint16);
	const EepromLocation NodeEepromMap::TX_POWER_LEVEL			(94, valueType_uint16);
	const EepromLocation NodeEepromMap::UNLIMITED_SAMPLING		(100, valueType_uint16);
	const EepromLocation NodeEepromMap::UNLIMITED_DATALOG		(102, valueType_uint16);
	const EepromLocation NodeEepromMap::FIRMWARE_VER			(108, valueType_uint16);
	const EepromLocation NodeEepromMap::FIRMWARE_VER2			(110, valueType_uint16);
	const EepromLocation NodeEepromMap::LEGACY_MODEL_NUMBER		(112, valueType_uint16);
	const EepromLocation NodeEepromMap::LEGACY_SERIAL_ID		(114, valueType_uint16);
	const EepromLocation NodeEepromMap::MAX_MEMORY				(116, valueType_uint16);
	const EepromLocation NodeEepromMap::MICROCONTROLLER			(120, valueType_uint16);
	const EepromLocation NodeEepromMap::FW_ARCH_VER				(122, valueType_uint16);
	const EepromLocation NodeEepromMap::HW_GAIN_1				(128, valueType_uint16);
	const EepromLocation NodeEepromMap::HW_GAIN_2				(130, valueType_uint16);
	const EepromLocation NodeEepromMap::HW_GAIN_3				(132, valueType_uint16);
	const EepromLocation NodeEepromMap::HW_GAIN_4				(134, valueType_uint16);
	const EepromLocation NodeEepromMap::CH_ACTION_ID_1			(150, valueType_uint16);
	const EepromLocation NodeEepromMap::CH_ACTION_SLOPE_1		(152, valueType_float);
	const EepromLocation NodeEepromMap::CH_ACTION_OFFSET_1		(156, valueType_float);
	const EepromLocation NodeEepromMap::CH_ACTION_ID_2			(160, valueType_uint16);
	const EepromLocation NodeEepromMap::CH_ACTION_SLOPE_2		(162, valueType_float);
	const EepromLocation NodeEepromMap::CH_ACTION_OFFSET_2		(166, valueType_float);
	const EepromLocation NodeEepromMap::CH_ACTION_ID_3			(170, valueType_uint16);
	const EepromLocation NodeEepromMap::CH_ACTION_SLOPE_3		(172, valueType_float);
	const EepromLocation NodeEepromMap::CH_ACTION_OFFSET_3		(176, valueType_float);
	const EepromLocation NodeEepromMap::CH_ACTION_ID_4			(180, valueType_uint16);
	const EepromLocation NodeEepromMap::CH_ACTION_SLOPE_4		(182, valueType_float);
	const EepromLocation NodeEepromMap::CH_ACTION_OFFSET_4		(186, valueType_float);
	const EepromLocation NodeEepromMap::CH_ACTION_ID_5			(190, valueType_uint16);
	const EepromLocation NodeEepromMap::CH_ACTION_SLOPE_5		(192, valueType_float);
	const EepromLocation NodeEepromMap::CH_ACTION_OFFSET_5		(196, valueType_float);
	const EepromLocation NodeEepromMap::CH_ACTION_ID_6			(200, valueType_uint16);
	const EepromLocation NodeEepromMap::CH_ACTION_SLOPE_6		(202, valueType_float);
	const EepromLocation NodeEepromMap::CH_ACTION_OFFSET_6		(206, valueType_float);
	const EepromLocation NodeEepromMap::CH_ACTION_ID_7			(210, valueType_uint16);
	const EepromLocation NodeEepromMap::CH_ACTION_SLOPE_7		(212, valueType_float);
	const EepromLocation NodeEepromMap::CH_ACTION_OFFSET_7		(216, valueType_float);
	const EepromLocation NodeEepromMap::CH_ACTION_ID_8			(220, valueType_uint16);
	const EepromLocation NodeEepromMap::CH_ACTION_SLOPE_8		(222, valueType_float);
	const EepromLocation NodeEepromMap::CH_ACTION_OFFSET_8		(226, valueType_float);
	const EepromLocation NodeEepromMap::BOOTLOADER_VER			(236, valueType_uint16);
	const EepromLocation NodeEepromMap::RESET_COUNTER			(246, valueType_uint16);
	const EepromLocation NodeEepromMap::CYCLE_POWER				(250, valueType_uint16);
	const EepromLocation NodeEepromMap::RADIO_OPTIONS			(258, valueType_uint16);
	const EepromLocation NodeEepromMap::LOST_BEACON_TIMEOUT		(260, valueType_uint16);
	const EepromLocation NodeEepromMap::SYNC_SAMPLE_SETTING		(262, valueType_uint16);
	const EepromLocation NodeEepromMap::TX_PER_GROUP			(264, valueType_uint16);
	const EepromLocation NodeEepromMap::GROUP_SIZE				(266, valueType_uint16);
	const EepromLocation NodeEepromMap::TIME_BETW_SESSIONS		(268, valueType_uint16);
	const EepromLocation NodeEepromMap::NODE_RETRANSMIT			(272, valueType_uint16);
	const EepromLocation NodeEepromMap::MAX_RETRANS_PACKET		(274, valueType_uint16);
	const EepromLocation NodeEepromMap::MAX_RETRANS_BURST		(276, valueType_uint16);
	const EepromLocation NodeEepromMap::REGION_CODE				(280, valueType_uint16);
	const EepromLocation NodeEepromMap::EVENT_SAMPLE_RATE		(328, valueType_uint16);
	const EepromLocation NodeEepromMap::EVENT_CHANNEL_MASK		(330, valueType_uint16);
	const EepromLocation NodeEepromMap::EVENT_PRE_DURATION		(332, valueType_uint16);
	const EepromLocation NodeEepromMap::EVENT_POST_DURATION		(334, valueType_uint16);
	const EepromLocation NodeEepromMap::EVENT_SRC_1				(336, valueType_uint16);
	const EepromLocation NodeEepromMap::EVENT_OPER_1			(338, valueType_uint16);
	const EepromLocation NodeEepromMap::EVENT_VAL1_1			(340, valueType_uint16);
	const EepromLocation NodeEepromMap::EVENT_VAL2_1			(342, valueType_uint16);
	const EepromLocation NodeEepromMap::EVENT_SRC_2				(344, valueType_uint16);
	const EepromLocation NodeEepromMap::EVENT_OPER_2			(346, valueType_uint16);
	const EepromLocation NodeEepromMap::EVENT_VAL1_2			(348, valueType_uint16);
	const EepromLocation NodeEepromMap::EVENT_VAL2_2			(350, valueType_uint16);
	const EepromLocation NodeEepromMap::EVENT_SRC_3				(352, valueType_uint16);
	const EepromLocation NodeEepromMap::EVENT_OPER_3			(354, valueType_uint16);
	const EepromLocation NodeEepromMap::EVENT_VAL1_3			(356, valueType_uint16);
	const EepromLocation NodeEepromMap::EVENT_VAL2_3			(358, valueType_uint16);
	const EepromLocation NodeEepromMap::EVENT_SRC_4				(360, valueType_uint16);
	const EepromLocation NodeEepromMap::EVENT_OPER_4			(362, valueType_uint16);
	const EepromLocation NodeEepromMap::EVENT_VAL1_4			(364, valueType_uint16);
	const EepromLocation NodeEepromMap::EVENT_VAL2_4			(366, valueType_uint16);
	const EepromLocation NodeEepromMap::EVENT_SRC_5				(368, valueType_uint16);
	const EepromLocation NodeEepromMap::EVENT_OPER_5			(370, valueType_uint16);
	const EepromLocation NodeEepromMap::EVENT_VAL1_5			(372, valueType_uint16);
	const EepromLocation NodeEepromMap::EVENT_VAL2_5			(374, valueType_uint16);
	const EepromLocation NodeEepromMap::EVENT_SRC_6				(376, valueType_uint16);
	const EepromLocation NodeEepromMap::EVENT_OPER_6			(378, valueType_uint16);
	const EepromLocation NodeEepromMap::EVENT_VAL1_6			(380, valueType_uint16);
	const EepromLocation NodeEepromMap::EVENT_VAL2_6			(382, valueType_uint16);
	const EepromLocation NodeEepromMap::EVENT_SRC_7				(384, valueType_uint16);
	const EepromLocation NodeEepromMap::EVENT_OPER_7			(386, valueType_uint16);
	const EepromLocation NodeEepromMap::EVENT_VAL1_7			(388, valueType_uint16);
	const EepromLocation NodeEepromMap::EVENT_VAL2_7			(390, valueType_uint16);
	const EepromLocation NodeEepromMap::EVENT_SRC_8				(392, valueType_uint16);
	const EepromLocation NodeEepromMap::EVENT_OPER_8			(394, valueType_uint16);
	const EepromLocation NodeEepromMap::EVENT_VAL1_8			(396, valueType_uint16);
	const EepromLocation NodeEepromMap::EVENT_VAL2_8			(398, valueType_uint16);
	const EepromLocation NodeEepromMap::CHANNEL_FILTER			(440, valueType_uint16);
	const EepromLocation NodeEepromMap::MIN_SOFT_VER_MAJOR		(480, valueType_uint16);
	const EepromLocation NodeEepromMap::MIN_SOFT_VER_MINOR		(482, valueType_uint16);
	const EepromLocation NodeEepromMap::HW_OFFSET_5				(504, valueType_uint16);
	const EepromLocation NodeEepromMap::HW_OFFSET_6				(506, valueType_uint16);
	const EepromLocation NodeEepromMap::HW_OFFSET_7				(508, valueType_uint16);
	const EepromLocation NodeEepromMap::HW_OFFSET_8				(510, valueType_uint16);

	const EepromLocation NodeEepromMap::THERMOCPL_TYPE			(306, valueType_uint16);
	const EepromLocation NodeEepromMap::FILTER_1				(130, valueType_uint16);
	const EepromLocation NodeEepromMap::FILTER_2				(134, valueType_uint16);


	const EepromLocation NodeEepromMap::DAMAGE_ANGLE_1			(512, valueType_float);
	const EepromLocation NodeEepromMap::DAMAGE_ANGLE_2			(516, valueType_float);
	const EepromLocation NodeEepromMap::DAMAGE_ANGLE_3			(520, valueType_float);
	const EepromLocation NodeEepromMap::LEGACY_DAMAGE_ANGLE_1	(676, valueType_uint16);
	const EepromLocation NodeEepromMap::LEGACY_DAMAGE_ANGLE_2	(678, valueType_uint16);
	const EepromLocation NodeEepromMap::LEGACY_DAMAGE_ANGLE_3	(680, valueType_uint16);
	const EepromLocation NodeEepromMap::BIN_SIZE				(682, valueType_uint16);
	const EepromLocation NodeEepromMap::RESET_BINS				(684, valueType_uint16);
	const EepromLocation NodeEepromMap::BIN_START				(686, valueType_uint16);
	const EepromLocation NodeEepromMap::PEAK_VALLEY_THRES		(688, valueType_uint16);
	const EepromLocation NodeEepromMap::SNCURVE_LOGA_1			(700, valueType_float);
	const EepromLocation NodeEepromMap::SNCURVE_M_1				(704, valueType_float);
	const EepromLocation NodeEepromMap::SNCURVE_LOGA_2			(708, valueType_float);
	const EepromLocation NodeEepromMap::SNCURVE_M_2				(712, valueType_float);
	const EepromLocation NodeEepromMap::SNCURVE_LOGA_3			(716, valueType_float);
	const EepromLocation NodeEepromMap::SNCURVE_M_3				(720, valueType_float);
	const EepromLocation NodeEepromMap::YOUNGS_MODULUS			(724, valueType_float);
	const EepromLocation NodeEepromMap::POISSONS_RATIO			(728, valueType_float);
	const EepromLocation NodeEepromMap::HISTOGRAM_SAMPLE_RATE	(732, valueType_uint16);
	const EepromLocation NodeEepromMap::HISTOGRAM_RAW_FLAG		(734, valueType_uint16);

	bool NodeEepromMap::canUseCache_read(uint16 eepromLocation)
	{
		switch(eepromLocation)
		{
			//eeprom locations that should always be updated by reading from the device when requested
			case 246:	//RESET_COUNTER
			case 0:		//CURRENT_LOG_PAGE
			case 2:		//CURRENT_PAGE_OFFSET
			case 4:		//DATA_SETS_STORED
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
			case 250:	//CYCLE_POWER
			case 90:	//FREQUENCY
			case 684:	//RESET_BINS
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

		return EepromLocation(slopeEeprom.id() + idDiff, slopeEeprom.location() + eepromDiff, CH_ACTION_OFFSET_1.valueType());
	}
}