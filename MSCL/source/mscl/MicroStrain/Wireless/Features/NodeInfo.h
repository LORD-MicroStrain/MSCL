/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/

#pragma once

#include "mscl/Utils.h"
#include "mscl/Version.h"
#include "mscl/MicroStrain/Wireless/WirelessModels.h"
#include "mscl/MicroStrain/Wireless/WirelessTypes.h"
#include "mscl/MicroStrain/Wireless/RadioFeatures.h"

namespace mscl
{
    class WirelessNode_Impl;    //forward declarations

    //Struct: NodeInfo
    //    Holds information (read from eeprom) about a <WirelessNode>.
    struct NodeInfo
    {
    public:
#ifndef SWIG
        //Constructor: NodeInfo
        //    Creates a NodeInfo object from a <WirelessNode>.
        //
        //Parameters:
        //    node - The <WirelessNode_Impl> to get the info for.
        //
        //Exceptions:
        //    - <Error_NodeCommunication>: Failed to communicate with the Node.
        //    - <Error_Connection>: A connection error has occurred with the parent BaseStation.
        NodeInfo(const WirelessNode_Impl* node);
#endif
        
        //Constructor: NodeInfo
        //    Creates a NodeInfo object.
        //
        //Parameters:
        //    fw - The firmware <Version> of the Node.
        //    model - The <WirelessModels::NodeModel> of the Node.
        //    region - The <WirelessTypes::RegionCode> of the Node.
        NodeInfo(const Version& fw, WirelessModels::NodeModel model, WirelessTypes::RegionCode region);

    private:
        NodeInfo();        //disabled default constructor

        //Variable: m_node
        //  The <WirelessNode_Impl> to use for lazy loading of values.
        const WirelessNode_Impl* m_node;

    private:
        //Variable: m_firmwareVersion
        //    The firmware <Version> of the node (lazy loaded).
        Utils::Lazy<Version> m_firmwareVersion;

        //Variable: m_model
        //    The <WirelessModels::NodeModel> of the node (lazy loaded).
        Utils::Lazy<WirelessModels::NodeModel> m_model;

        //Variable: m_regionCode
        //    The <WirelessTypes::RegionCode> of the node (lazy loaded).
        Utils::Lazy<WirelessTypes::RegionCode> m_regionCode;

    public:
#ifndef SWIG
        //Function: firmwareVersion
        //  Gets the firmware <Version> of the Node.
        Version firmwareVersion() const;

        //Function: model
        //  Gets the <WirelessModels::NodeModel> of the Node.
        WirelessModels::NodeModel model() const;

        //Function: regionCode
        //  Gets the <WirelessTypes::RegionCode> of the Node.
        WirelessTypes::RegionCode regionCode() const;
#endif
    };
}