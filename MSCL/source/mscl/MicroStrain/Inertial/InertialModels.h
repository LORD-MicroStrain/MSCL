/*******************************************************************************
Copyright(c) 2015-2017 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/

#pragma once

namespace mscl
{
    //API Class: InertialModels
    //    Contains the models of Inertial hardware.
    class InertialModels
    {
    public:
        //=========================================================================
        //API Enum: NodeModel
        //  The model numbers for each of the Inertial Nodes.
        //
        //  node_3dm            - 6201 - 3DM
        //  node_fasA           - 6207 - FAS-A
        //  node_3dm_gx2        - 6215 - 3DM-GX2
        //  node_3dm_dh3        - 6219 - 3DM-DH3
        //  node_3dm_gx3_15     - 6227 - 3DM-GX3-15
        //  node_3dm_gx3_25     - 6223 - 3DM-GX3-25
        //  node_3dm_gx3_35     - 6225 - 3DM-GX3-35
        //  node_3dm_gx3_45     - 6228 - 3DM-GX3-45
        //  node_3dm_rq1_45     - 6232 - 3DM-RQ1-45
        //  node_3dm_gx4_15     - 6233 - 3DM-GX4-15
        //  node_3dm_gx4_25     - 6234 - 3DM-GX4-25
        //  node_3dm_gx4_45     - 6236 - 3DM-GX4-45
        //  node_3dm_gx5_10     - 6255 - 3DM-GX5-10
        //  node_3dm_gx5_15     - 6254 - 3DM-GX5-15
        //  node_3dm_gx5_25     - 6253 - 3DM-GX5-25
        //  node_3dm_gx5_35     - 6252 - 3DM-GX5-35
        //  node_3dm_gx5_45     - 6251 - 3DM-GX5-45
        //=========================================================================
        enum NodeModel
        {
            node_3dm            = 6201,     //3DM
            node_fasA           = 6207,     //FAS-A
            node_3dm_gx2        = 6215,     //3DM-GX2
            node_3dm_dh3        = 6219,     //3DM-DH3
            node_3dm_gx3_15     = 6227,     //3DM-GX3-15
            node_3dm_gx3_25     = 6223,     //3DM-GX3-25
            node_3dm_gx3_35     = 6225,     //3DM-GX3-35
            node_3dm_gx3_45     = 6228,     //3DM-GX3-45
            node_3dm_rq1_45     = 6232,     //3DM-RQ1-45
            node_3dm_gx4_15     = 6233,     //3DM-GX4-15
            node_3dm_gx4_25     = 6234,     //3DM-GX4-25
            node_3dm_gx4_45     = 6236,     //3DM-GX4-45
            node_3dm_gx5_10     = 6255,     //3DM-GX5-10
            node_3dm_gx5_15     = 6254,     //3DM-GX5-15
            node_3dm_gx5_25     = 6253,     //3DM-GX5-25
            node_3dm_gx5_35     = 6252,     //3DM-GX5-35
            node_3dm_gx5_45     = 6251,     //3DM-GX5-45
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