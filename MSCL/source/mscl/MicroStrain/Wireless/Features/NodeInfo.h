/*******************************************************************************
Copyright(c) 2015-2017 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/

#pragma once

#include "mscl/Version.h"
#include "mscl/MicroStrain/Wireless/WirelessModels.h"
#include "mscl/MicroStrain/Wireless/WirelessTypes.h"
#include "mscl/MicroStrain/Wireless/RadioFeatures.h"

#include <boost/optional.hpp>

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
        
        //Constructor: NodeInfo
        //    Creates a NodeInfo object.
        //
        //Parameters:
        //    fw - The firmware <Version> of the Node.
        //    model - The <WirelessModels::NodeModel> of the Node.
        //    storageSize - The maximum number of bytes that can be stored to the Node.
        //    region - The <WirelessTypes::RegionCode> of the Node.
        NodeInfo(const Version& fw, WirelessModels::NodeModel model, uint64 storageSize, WirelessTypes::RegionCode region);
#endif

    private:
        NodeInfo();        //disabled default constructor

        const WirelessNode_Impl* m_node;

    private:
        //Variable: firmwareVersion
        //    The firmware <Version> of the node.
        mutable boost::optional<Version> m_firmwareVersion;

        //Variable: model
        //    The <WirelessModels::NodeModel> of the node.
        mutable boost::optional<WirelessModels::NodeModel> m_model;

        //Variable: dataStorageSize
        //    The maximum number of bytes that can be stored to the node.
        mutable boost::optional<uint64> m_dataStorageSize;

        //Variable: regionCode
        //    The <WirelessTypes::RegionCode> of the node.
        mutable boost::optional<WirelessTypes::RegionCode> m_regionCode;

    public:
        Version firmwareVersion() const;
        WirelessModels::NodeModel model() const;
        uint64 dataStorageSize() const;
        WirelessTypes::RegionCode regionCode() const;
    };
}