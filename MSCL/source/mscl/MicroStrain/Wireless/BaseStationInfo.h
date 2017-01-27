/*******************************************************************************
Copyright(c) 2015-2017 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/

#pragma once

#include "mscl/Version.h"
#include "WirelessModels.h"
#include "WirelessTypes.h"
#include "RadioFeatures.h"

#include <boost/optional.hpp>

namespace mscl
{
    class BaseStation_Impl;    //forward declarations

    //Struct: BaseStationInfo
    //    Holds information (read from eeprom) about a <BaseStation>.
    struct BaseStationInfo
    {
    public:
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
        
        //Constructor: BaseStationInfo
        //    Creates a BaseStationInfo object.
        //
        //Parameters:
        //    fw - The firmware <Version> of the BaseStation.
        //    model - The <WirelessModels::BaseModel> of the BaseStation.
        //    region - The <WirelessTypes::RegionCode> of the BaseStation.
        BaseStationInfo(Version fw, WirelessModels::BaseModel model, WirelessTypes::RegionCode region);

    private:
        BaseStationInfo();    //disabled default constructor

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

    public:
        Version firmwareVersion() const;
        WirelessModels::BaseModel model() const;
        WirelessTypes::RegionCode regionCode() const;
    };
}