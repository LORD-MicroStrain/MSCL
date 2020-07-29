/*******************************************************************************
Copyright(c) 2015-2020 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/

#pragma once

#include <string>

namespace mscl
{
    //API Class: RTKModels
    //    Contains the models of RTK hardware.
    class RTKModels
    {
    public:
        //=========================================================================
        //API Enum: NodeModel
        //  The model numbers for each of the RTK Nodes.
        //
        //  node_3dm_rtk   - 6285 - 3DM-RTK
        //=========================================================================
        enum NodeModel
        {
            node_3dm_rtk = 6285  //3DM-RTK
        };

#ifndef SWIG
        
        //Function: nodeFromModelString
        //    Converts the model number string received from an InertialNode to a <NodeModel> enum.
        //
        //Parameters:
        //    modelNumberString - The model number string received in an InertialNode's Get Device Info packet.
        //
        //Returns:
        //    A <NodeModel> enum created from the string.
        static NodeModel nodeFromModelString(const std::string& modelNumberString);
#endif
    };
}