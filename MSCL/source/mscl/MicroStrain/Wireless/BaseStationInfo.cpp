/*****************************************************************************************
**          Copyright(c) 2015-2024 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

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

    BaseStationInfo::BaseStationInfo(Version fw, WirelessModels::BaseModel model, WirelessTypes::RegionCode region, const Version& asppVer_lxrs, const Version& asppVer_lxrsPlus):
        m_firmwareVersion(fw),
        m_model(model),
        m_regionCode(region),
        m_protocol_lxrs(*WirelessProtocol::getProtocol(asppVer_lxrs)),
        m_protocol_lxrsPlus(*WirelessProtocol::getProtocol(asppVer_lxrsPlus))
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

    const WirelessProtocol& BaseStationInfo::protocol(WirelessTypes::CommProtocol commProtocol) const
    {
        if(commProtocol == WirelessTypes::commProtocol_lxrs)
        {
            if(!static_cast<bool>(m_protocol_lxrs))
            {
                m_protocol_lxrs = m_basestation->protocol(commProtocol);
            }

            return *m_protocol_lxrs;
        }
        else if(commProtocol == WirelessTypes::commProtocol_lxrsPlus)
        {
            if(!static_cast<bool>(m_protocol_lxrsPlus))
            {
                m_protocol_lxrsPlus = m_basestation->protocol(commProtocol);
            }

            return *m_protocol_lxrsPlus;
        }

        throw Error("Invalid CommProtocol (" + Utils::toStr(commProtocol) + ")");
    }
}
