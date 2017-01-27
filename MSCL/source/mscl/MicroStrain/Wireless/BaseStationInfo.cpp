/*******************************************************************************
Copyright(c) 2015-2017 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"
#include "BaseStationInfo.h"
#include "BaseStation_Impl.h"

namespace mscl
{
    //read the required information from the BaseStation and store in the BaseStationInfo
    BaseStationInfo::BaseStationInfo(const BaseStation_Impl* base) :
        m_basestation(base)
    {
    }

    BaseStationInfo::BaseStationInfo(Version fw, WirelessModels::BaseModel model, WirelessTypes::RegionCode region):
        m_firmwareVersion(fw),
        m_model(model),
        m_regionCode(region)
    {
    }

    Version BaseStationInfo::firmwareVersion() const
    {
        if(!static_cast<bool>(m_firmwareVersion))
        {
            m_firmwareVersion = m_basestation->firmwareVersion();
        }

        return *m_firmwareVersion;
    }

    WirelessModels::BaseModel BaseStationInfo::model() const
    {
        if(!static_cast<bool>(m_model))
        {
            m_model = m_basestation->model();
        }

        return *m_model;
    }

    WirelessTypes::RegionCode BaseStationInfo::regionCode() const
    {
        if(!static_cast<bool>(m_regionCode))
        {
            m_regionCode = m_basestation->regionCode();
        }

        return *m_regionCode;
    }

}