/*******************************************************************************
Copyright(c) 2015-2017 LORD Corporation. All rights reserved.

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
        m_errorFlagCh1(WirelessTypes::autocalShmError_none),
        m_errorFlagCh2(WirelessTypes::autocalShmError_none),
        m_errorFlagCh3(WirelessTypes::autocalShmError_none),
        m_offsetCh1(0.0f),
        m_offsetCh2(0.0f),
        m_offsetCh3(0.0f),
        m_temperature(0.0f)
    {
    }

    WirelessTypes::AutoCalShmErrorFlag AutoCalResult_shmLink::errorFlagCh1() const
    {
        return m_errorFlagCh1;
    }

    WirelessTypes::AutoCalShmErrorFlag AutoCalResult_shmLink::errorFlagCh2() const
    {
        return m_errorFlagCh2;
    }

    WirelessTypes::AutoCalShmErrorFlag AutoCalResult_shmLink::errorFlagCh3() const
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
        m_errorFlagCh1 = static_cast<WT::AutoCalShmErrorFlag>(data.read_uint8());
        m_offsetCh1 = data.read_float();

        //Ch2 error flag and offset
        m_errorFlagCh2 = static_cast<WT::AutoCalShmErrorFlag>(data.read_uint8());
        m_offsetCh2 = data.read_float();

        //Ch3 error flag and offset
        m_errorFlagCh3 = static_cast<WT::AutoCalShmErrorFlag>(data.read_uint8());
        m_offsetCh3 = data.read_float();

        //temperature at time of cal
        m_temperature = data.read_float();
    }


    //=====================================================
    //AutoCalResult_shunt
    //=====================================================
    AutoShuntCalResult::AutoShuntCalResult():
        AutoCalResult(),
        m_errorFlag(WirelessTypes::autoshuntcalError_none),
        m_slope(1.0f),
        m_offset(0.0f),
        m_baseMedian(0.0f),
        m_baseMin(0.0f),
        m_baseMax(0.0f),
        m_shuntMedian(0.0f),
        m_shuntMin(0.0f),
        m_shuntMax(0.0f)
    {
    }

    WirelessTypes::AutoShuntCalErrorFlag AutoShuntCalResult::errorFlag() const
    {
        return m_errorFlag;
    }

    float AutoShuntCalResult::slope() const
    {
        return m_slope;
    }

    float AutoShuntCalResult::offset() const
    {
        return m_offset;
    }

    float AutoShuntCalResult::baseMedian() const
    {
        return m_baseMedian;
    }

    float AutoShuntCalResult::baseMin() const
    {
        return m_baseMin;
    }

    float AutoShuntCalResult::baseMax() const
    {
        return m_baseMax;
    }

    float AutoShuntCalResult::shuntMedian() const
    {
        return m_shuntMedian;
    }

    float AutoShuntCalResult::shuntMin() const
    {
        return m_shuntMin;
    }

    float AutoShuntCalResult::shuntMax() const
    {
        return m_shuntMax;
    }

    void AutoShuntCalResult::parse(const Bytes& autoCalInfo)
    {
        if(autoCalInfo.size() != 34)
        {
            assert(false);
            return;
        }

        typedef WirelessTypes WT;

        DataBuffer data(autoCalInfo);

        data.skipBytes(1);  //skip the channel number, not important in result
        m_errorFlag = static_cast<WT::AutoShuntCalErrorFlag>(data.read_uint8());
        m_slope = data.read_float();
        m_offset = data.read_float();
        m_baseMedian = data.read_float();
        m_baseMin = data.read_float();
        m_baseMax = data.read_float();
        m_shuntMedian = data.read_float();
        m_shuntMin = data.read_float();
        m_shuntMax = data.read_float();
    }
}