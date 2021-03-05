/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/

#pragma once

#include "mscl/Version.h"
#include "WirelessModels.h"
#include "WirelessTypes.h"
#include "RadioFeatures.h"
#include "Commands/WirelessProtocol.h"

#include <boost/optional.hpp>

namespace mscl
{
    class BaseStation_Impl;    //forward declarations

    //API Struct: BaseStationInfo
    //    Holds information about a <BaseStation>.
    struct BaseStationInfo
    {
    public:

#ifndef SWIG
        //Constructor: BaseStationInfo
        //    Creates a BaseStationInfo object from a <BaseStation>.
        //
        //Parameters:
        //    base - The <BaseStation_Impl> to get the info for.
        //
        //Exceptions:
        //    - <Error_Communication>: Failed to read the value from the BaseStation.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        BaseStationInfo(const BaseStation_Impl* base);
#endif
        
        //API Constructor: BaseStationInfo
        //    Creates a BaseStationInfo object.
        //
        //Parameters:
        //    fw - The firmware <Version> of the BaseStation.
        //    model - The <WirelessModels::BaseModel> of the BaseStation.
        //    region - The <WirelessTypes::RegionCode> of the BaseStation.
        //    asppVer_lxrs - The ASPP <Version> for the LXRS protocol.
        //    asppVer_lxrsPlus - The ASPP <Version> for the LXRS+ protocol.
        BaseStationInfo(Version fw, WirelessModels::BaseModel model, WirelessTypes::RegionCode region, const Version& asppVer_lxrs, const Version& asppVer_lxrsPlus);

    private:
        //Variable: m_basestation
        //  The <BaseStation_Impl> to use for lazy loading information for if its not already populated.
        const BaseStation_Impl* m_basestation;

    private:
        //Variable: m_firmwareVersion
        //    The firmware <Version> of the BaseStation.
        mutable boost::optional<Version> m_firmwareVersion;

        //Variable: m_model
        //    The <WirelessModels::BaseModel> of the BaseStation.
        mutable boost::optional<WirelessModels::BaseModel> m_model;

        //Variable: m_regionCode
        //    The <WirelessTypes::RegionCode> of the BaseStation.
        mutable boost::optional<WirelessTypes::RegionCode> m_regionCode;

        //Variable: m_protocol_lxrs
        //  The <WirelessProtocol> of the BaseStation for the LXRS Radio Configuration.
        mutable boost::optional<WirelessProtocol> m_protocol_lxrs;

        //Variable: m_protocol_lxrsPlus
        //  The <WirelessProtocol> of the BaseStation for the LXRS+ Radio Configuration.
        mutable boost::optional<WirelessProtocol> m_protocol_lxrsPlus;

    public:
#ifndef SWIG
        Version firmwareVersion() const;
        WirelessModels::BaseModel model() const;
        WirelessTypes::RegionCode regionCode() const;
        const WirelessProtocol& protocol(WirelessTypes::CommProtocol commProtocol) const;
#endif
    };
}