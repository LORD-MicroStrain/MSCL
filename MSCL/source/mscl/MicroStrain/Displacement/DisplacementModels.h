/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/

#pragma once

#include <string>

namespace mscl
{
    //API Class: DisplacementModels
    //    Contains the models of Displacement hardware.
    class DisplacementModels
    {
    public:
        //=========================================================================
        //API Enum: NodeModel
        //  The model numbers for each of the Displacement Nodes.
        //
        //  node_digitalDemod   - 6130 - Digital Demod
        //=========================================================================
        enum NodeModel
        {
            node_digitalDemod   = 6130  //Digital Demod
        };

#ifndef SWIG
        
        //Function: nodeFromModelString
        //    Converts the model number string received from an InertialNode to a <NodeModel> enum.
        //
        //Parameters:
        //    modelNumberString - The model number string recieved in an InertialNode's Get Device Info packet.
        //
        //Returns:
        //    A <NodeModel> enum created from the string.
        static NodeModel nodeFromModelString(const std::string& modelNumberString);
#endif
    };
}