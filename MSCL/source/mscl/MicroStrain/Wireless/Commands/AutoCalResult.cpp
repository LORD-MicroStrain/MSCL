/*******************************************************************************
Copyright(c) 2015 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"
#include "AutoCalResult.h"

namespace mscl
{
	AutoCalResult::AutoCalResult():
		m_completionFlag(WirelessTypes::autocal_notComplete)
	{
	}

	WirelessTypes::AutoCalCompletionFlag AutoCalResult::completionFlag() const
	{
		return m_completionFlag;
	}

	//=====================================================
	//AutoCalResult_shmLink
	//=====================================================
	AutoCalResult_shmLink::AutoCalResult_shmLink():
		AutoCalResult(),
		m_errorFlagCh1(WirelessTypes::autocalError_none),
		m_errorFlagCh2(WirelessTypes::autocalError_none),
		m_errorFlagCh3(WirelessTypes::autocalError_none),
		m_offsetCh1(0.0f),
		m_offsetCh2(0.0f),
		m_offsetCh3(0.0f),
		m_temperature(0.0f)
	{
	}

	WirelessTypes::AutoCalErrorFlag AutoCalResult_shmLink::errorFlagCh1() const
	{
		return m_errorFlagCh1;
	}

	WirelessTypes::AutoCalErrorFlag AutoCalResult_shmLink::errorFlagCh2() const
	{
		return m_errorFlagCh2;
	}

	WirelessTypes::AutoCalErrorFlag AutoCalResult_shmLink::errorFlagCh3() const
	{
		return m_errorFlagCh3;
	}

	float AutoCalResult_shmLink::offsetCh1() const
	{
		return m_offsetCh1;
	}

	float AutoCalResult_shmLink::offsetCh2() const
	{
		return m_offsetCh2;
	}

	float AutoCalResult_shmLink::offsetCh3() const
	{
		return m_offsetCh3;
	}

	float AutoCalResult_shmLink::temperature() const
	{
		return m_temperature;
	}

	void AutoCalResult_shmLink::parse(const Bytes& autoCalInfo)
	{
		if(autoCalInfo.size() < 19)
		{
			assert(false);
			return;
		}

		typedef WirelessTypes WT;

		DataBuffer data(autoCalInfo);
		
		//Ch1 error flag and offset
		m_errorFlagCh1 = static_cast<WT::AutoCalErrorFlag>(data.read_uint8());
		m_offsetCh1 = data.read_float();

		//Ch2 error flag and offset
		m_errorFlagCh2 = static_cast<WT::AutoCalErrorFlag>(data.read_uint8());
		m_offsetCh2 = data.read_float();

		//Ch3 error flag and offset
		m_errorFlagCh3 = static_cast<WT::AutoCalErrorFlag>(data.read_uint8());
		m_offsetCh3 = data.read_float();

		//temperature at time of cal
		m_temperature = data.read_float();
	}
}