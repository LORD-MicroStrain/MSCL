/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/

#pragma once

#include <string>

namespace mscl
{
    //API Class: MipModels
    //    Contains the models of MIP devices.
    class MipModels
    {
    public:
        //=========================================================================
        //API Enum: NodeModel
        //  The model numbers for each of the MIP devices.
        //
        //  node_3dm            - 6201 - 3DM
        //  node_fasA           - 6207 - FAS-A
        //  node_3dm_gx2        - 6215 - 3DM-GX2
        //  node_3dm_dh3        - 6219 - 3DM-DH3
        //  node_3dm_gx3_15     - 6227 - 3DM-GX3-15
        //  node_3dm_gx3_25     - 6223 - 3DM-GX3-25
        //  node_3dm_gx3_35     - 6225 - 3DM-GX3-35
        //  node_3dm_gx3_45     - 6228 - 3DM-GX3-45
        //  node_3dm_rq1_45_lt  - 6232 - 3DM-RQ1-45-LT
        //  node_3dm_gx4_15     - 6233 - 3DM-GX4-15
        //  node_3dm_gx4_25     - 6234 - 3DM-GX4-25
        //  node_3dm_gx4_45     - 6236 - 3DM-GX4-45
        //  node_3dm_rq1_45_st  - 6239 - 3DM-RQ1-45-ST
        //  node_mv5_ar         - 6243 - MV5-AR
        //  node_3dm_gx5_10     - 6255 - 3DM-GX5-10
        //  node_3dm_gx5_15     - 6254 - 3DM-GX5-15
        //  node_3dm_gx5_25     - 6253 - 3DM-GX5-25
        //  node_3dm_gx5_35     - 6252 - 3DM-GX5-35
        //  node_3dm_gx5_45     - 6251 - 3DM-GX5-45
        //  node_3dm_cv5_10     - 6259 - 3DM-CV5-10
        //  node_3dm_cv5_15     - 6258 - 3DM-CV5-15
        //  node_3dm_cv5_25     - 6257 - 3DM-CV5-25
        //  node_3dm_cv5_45     - 6256 - 3DM-CV5-45
        //  node_3dm_gq4_45     - 6250 - 3DM-GQ4-45
        //  node_3dm_cx5_45     - 6271 - 3DM-CX5-45
        //  node_3dm_cx5_35     - 6272 - 3DM-CX5-35
        //  node_3dm_cx5_25     - 6273 - 3DM-CX5-25
        //  node_3dm_cx5_15     - 6274 - 3DM-CX5-15
        //  node_3dm_cx5_10     - 6275 - 3DM-CX5-10
        //  node_3dm_cl5_15     - 6280 - 3DM-CL5-15
        //  node_3dm_cl5_25     - 6281 - 3DM-CL5-25
        //  node_3dm_gq7        - 6284 - 3DM-GQ7
        //  node_3dm_rtk        - 6285 - 3DM-RTK
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
            node_3dm_rq1_45_lt  = 6232,     //3DM-RQ1-45-LT
            node_3dm_gx4_15     = 6233,     //3DM-GX4-15
            node_3dm_gx4_25     = 6234,     //3DM-GX4-25
            node_3dm_gx4_45     = 6236,     //3DM-GX4-45
            node_3dm_rq1_45_st  = 6239,     //3DM-RQ1-45-ST
            node_mv5_ar         = 6243,     //MV5-AR
            node_3dm_gx5_10     = 6255,     //3DM-GX5-10
            node_3dm_gx5_15     = 6254,     //3DM-GX5-15
            node_3dm_gx5_25     = 6253,     //3DM-GX5-25
            node_3dm_gx5_35     = 6252,     //3DM-GX5-35
            node_3dm_gx5_45     = 6251,     //3DM-GX5-45
            node_3dm_cv5_10     = 6259,     //3DM-CV5-10
            node_3dm_cv5_15     = 6258,     //3DM-CV5-15
            node_3dm_cv5_25     = 6257,     //3DM-CV5-25
            node_3dm_cv5_45     = 6256,     //3DM-CV5-45
            node_3dm_gq4_45     = 6250,     //3DM-GQ4-45
            node_3dm_cx5_45     = 6271,     //3DM-CX5-45
            node_3dm_cx5_35     = 6272,     //3DM-CX5-35
            node_3dm_cx5_25     = 6273,     //3DM-CX5-25
            node_3dm_cx5_15     = 6274,     //3DM-CX5-15
            node_3dm_cx5_10     = 6275,     //3DM-CX5-10
            node_3dm_cl5_15     = 6280,     //3DM-CL5-15
            node_3dm_cl5_25     = 6281,     //3DM-CL5-25
            node_3dm_gq7        = 6284,     //3DM-GQ7
            node_3dm_rtk        = 6285      //3DM-RTK
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