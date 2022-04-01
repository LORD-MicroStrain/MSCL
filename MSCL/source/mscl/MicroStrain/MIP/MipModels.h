/*****************************************************************************************
**          Copyright(c) 2015-2022 Parker Hannifin Corp. All rights reserved.           **
**                                                                                      **
**    MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.    **
*****************************************************************************************/

#pragma once

#include <string>

namespace mscl
{
    class MipModel;

    //API Class: MipModels
    //    Contains the model number information of MIP devices.
    class MipModels
    {
    public:
        //=========================================================================
        //API Enum: NodeModel
        //  The base model numbers for each of the MIP devices.
        //  Ex: 6284-4220 (3DM-GQ7) NodeModel is 6284
        //
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
        //  node_3dm_cv7_ahrs   - 6286 - 3DM-CV7-AHRS
        //  node_3dm_cv7_ar     - 6287 - 3DM-CV7-AR
        //=========================================================================
        enum NodeModel
        {
            node_3dm_dh3 = 6219,     //3DM-DH3
            node_3dm_gx3_15 = 6227,     //3DM-GX3-15
            node_3dm_gx3_25 = 6223,     //3DM-GX3-25
            node_3dm_gx3_35 = 6225,     //3DM-GX3-35
            node_3dm_gx3_45 = 6228,     //3DM-GX3-45
            node_3dm_rq1_45_lt = 6232,     //3DM-RQ1-45-LT
            node_3dm_gx4_15 = 6233,     //3DM-GX4-15
            node_3dm_gx4_25 = 6234,     //3DM-GX4-25
            node_3dm_gx4_45 = 6236,     //3DM-GX4-45
            node_3dm_rq1_45_st = 6239,     //3DM-RQ1-45-ST
            node_mv5_ar = 6243,     //MV5-AR
            node_3dm_gx5_10 = 6255,     //3DM-GX5-10
            node_3dm_gx5_15 = 6254,     //3DM-GX5-15
            node_3dm_gx5_25 = 6253,     //3DM-GX5-25
            node_3dm_gx5_35 = 6252,     //3DM-GX5-35
            node_3dm_gx5_45 = 6251,     //3DM-GX5-45
            node_3dm_cv5_10 = 6259,     //3DM-CV5-10
            node_3dm_cv5_15 = 6258,     //3DM-CV5-15
            node_3dm_cv5_25 = 6257,     //3DM-CV5-25
            node_3dm_cv5_45 = 6256,     //3DM-CV5-45
            node_3dm_gq4_45 = 6250,     //3DM-GQ4-45
            node_3dm_cx5_45 = 6271,     //3DM-CX5-45
            node_3dm_cx5_35 = 6272,     //3DM-CX5-35
            node_3dm_cx5_25 = 6273,     //3DM-CX5-25
            node_3dm_cx5_15 = 6274,     //3DM-CX5-15
            node_3dm_cx5_10 = 6275,     //3DM-CX5-10
            node_3dm_cl5_15 = 6280,     //3DM-CL5-15
            node_3dm_cl5_25 = 6281,     //3DM-CL5-25
            node_3dm_gq7 = 6284,     //3DM-GQ7
            node_3dm_rtk = 6285,     //3DM-RTK
            node_3dm_cv7_ahrs = 6286, //3DM-CV7-AHRS
            node_3dm_cv7_ar   = 6287  //3DM-CV7-AR
        };

        //=========================================================================
        //API Enum: Modifier
        //  The modifier options for MIP devices.
        //  Ex: 6285-0100 (3DM-RTK) Modifier is 0100
        //  This list does not define modifiers for all devices. The placeholder value (9999) will match to any value read from the device when comparing <MipModel> objects.
        //
        //  placeholder_matchAll    - 9999 - Placeholder value to use in full ModelNumber and const <MipModel> definitions
        //  rtk_v1                  - 0000 - 3DM-RTK v1
        //  rtk_v2                  - 0100 - 3DM-RTK
        //=========================================================================
        enum Modifier
        {
            //placeholder
            placeholder_matchAll = 9999,

            //rtk
            rtk_v1 = 0000,
            rtk_v2 = 0100
        };

        //=========================================================================
        //API Enum: ModelNumber
        //  The combined node model and modifier numbers for each of the MIP devices.
        //  Ex: Model = 6285, Modifiers = RTK v2 (0100) - NodeModel = 62580100
        //  Most models have 9999 placeholder modifier values because there is no significant interface difference between the different versions of the same base model.
        //  This placeholder value will match to any modifier value read from the device when comparing <MipModel> objects.
        //
        //  model_3dm_dh3        - 62199999 - 3DM-DH3
        //  model_3dm_gx3_15     - 62279999 - 3DM-GX3-15
        //  model_3dm_gx3_25     - 62239999 - 3DM-GX3-25
        //  model_3dm_gx3_35     - 62259999 - 3DM-GX3-35
        //  model_3dm_gx3_45     - 62289999 - 3DM-GX3-45
        //  model_3dm_rq1_45_lt  - 62329999 - 3DM-RQ1-45-LT
        //  model_3dm_gx4_15     - 62339999 - 3DM-GX4-15
        //  model_3dm_gx4_25     - 62349999 - 3DM-GX4-25
        //  model_3dm_gx4_45     - 62369999 - 3DM-GX4-45
        //  model_3dm_rq1_45_st  - 62399999 - 3DM-RQ1-45-ST
        //  model_mv5_ar         - 62439999 - MV5-AR
        //  model_3dm_gx5_10     - 62559999 - 3DM-GX5-10
        //  model_3dm_gx5_15     - 62549999 - 3DM-GX5-15
        //  model_3dm_gx5_25     - 62539999 - 3DM-GX5-25
        //  model_3dm_gx5_35     - 62529999 - 3DM-GX5-35
        //  model_3dm_gx5_45     - 62519999 - 3DM-GX5-45
        //  model_3dm_cv5_10     - 62599999 - 3DM-CV5-10
        //  model_3dm_cv5_15     - 62589999 - 3DM-CV5-15
        //  model_3dm_cv5_25     - 62579999 - 3DM-CV5-25
        //  model_3dm_cv5_45     - 62569999 - 3DM-CV5-45
        //  model_3dm_gq4_45     - 62509999 - 3DM-GQ4-45
        //  model_3dm_cx5_45     - 62719999 - 3DM-CX5-45
        //  model_3dm_cx5_35     - 62729999 - 3DM-CX5-35
        //  model_3dm_cx5_25     - 62739999 - 3DM-CX5-25
        //  model_3dm_cx5_15     - 62749999 - 3DM-CX5-15
        //  model_3dm_cx5_10     - 62759999 - 3DM-CX5-10
        //  model_3dm_cl5_15     - 62809999 - 3DM-CL5-15
        //  model_3dm_cl5_25     - 62819999 - 3DM-CL5-25
        //  model_3dm_gq7        - 62849999 - 3DM-GQ7
        //  model_3dm_rtk_v1     - 62850000 - 3DM-RTK v1
        //  model_3dm_rtk        - 62850100 - 3DM-RTK
        //  model_3dm_cv7_ahrs   - 62869999 - 3DM-CV7-AHRS
        //  model_3dm_cv7_ar     - 62879999 - 3DM-CV7-AR
        //=========================================================================
        enum ModelNumber
        {
            model_3dm_dh3        = 62199999, // 3DM-DH3
            model_3dm_gx3_15     = 62279999, // 3DM-GX3-15
            model_3dm_gx3_25     = 62239999, // 3DM-GX3-25
            model_3dm_gx3_35     = 62259999, // 3DM-GX3-35
            model_3dm_gx3_45     = 62289999, // 3DM-GX3-45
            model_3dm_rq1_45_lt  = 62329999, // 3DM-RQ1-45-LT
            model_3dm_gx4_15     = 62339999, // 3DM-GX4-15
            model_3dm_gx4_25     = 62349999, // 3DM-GX4-25
            model_3dm_gx4_45     = 62369999, // 3DM-GX4-45
            model_3dm_rq1_45_st  = 62399999, // 3DM-RQ1-45-ST
            model_mv5_ar         = 62439999, // MV5-AR
            model_3dm_gx5_10     = 62559999, // 3DM-GX5-10
            model_3dm_gx5_15     = 62549999, // 3DM-GX5-15
            model_3dm_gx5_25     = 62539999, // 3DM-GX5-25
            model_3dm_gx5_35     = 62529999, // 3DM-GX5-35
            model_3dm_gx5_45     = 62519999, // 3DM-GX5-45
            model_3dm_cv5_10     = 62599999, // 3DM-CV5-10
            model_3dm_cv5_15     = 62589999, // 3DM-CV5-15
            model_3dm_cv5_25     = 62579999, // 3DM-CV5-25
            model_3dm_cv5_45     = 62569999, // 3DM-CV5-45
            model_3dm_gq4_45     = 62509999, // 3DM-GQ4-45
            model_3dm_cx5_45     = 62719999, // 3DM-CX5-45
            model_3dm_cx5_35     = 62729999, // 3DM-CX5-35
            model_3dm_cx5_25     = 62739999, // 3DM-CX5-25
            model_3dm_cx5_15     = 62749999, // 3DM-CX5-15
            model_3dm_cx5_10     = 62759999, // 3DM-CX5-10
            model_3dm_cl5_15     = 62809999, // 3DM-CL5-15
            model_3dm_cl5_25     = 62819999, // 3DM-CL5-25
            model_3dm_gq7        = 62849999, // 3DM-GQ7
            model_3dm_rtk_v1     = 62850000, // 3DM-RTK v1
            model_3dm_rtk        = 62850100, // 3DM-RTK
            model_3dm_cv7_ahrs   = 62869999, // 3DM-CV7-AHRS
            model_3dm_cv7_ar     = 62879999, // 3DM-CV7-AR
        };

        //API Function: modelNumberEqual
        //  Compare two <MipModels::ModelNumber> enum values (functionally the same as == operator overload for two MipModels::ModelNumber values).
        //
        //  Parameters:
        //    model1 - the first MipModels::ModelNumber value to compare
        //    model2 - the second MipModels::ModelNumber value to compare
        //
        //  Returns:
        //    bool - true if both the <NodeModel> and <Modifier> sections of the full model number are equal or either <Modifier> is the placeholder value (9999)
        static bool modelNumbersEqual(ModelNumber model1, ModelNumber model2);

        //API Function: modelNumberFromStr
        //  Returns a full ModelNumber integer value parsed from a model number string.
        //
        //  Parameters:
        //    modelNumberString - model number string formatted as it is read from a MIP device (ex: "6284-4220")
        //
        //  Returns:
        //    <ModelNumber> - integer form of model number cast as a ModelNumber enum value (ex: "6284-4220" -> 62844220)
        static ModelNumber modelNumberFromStr(const std::string& modelNumberString);

        //API Function: modelNumberFromParts
        //  Constructs a full ModelNumber integer from node model and modifier sections. Ex: nodeModel: 6284, modifier: 4220 -> 62844220
        //
        //  Parameters:
        //    nodeModel - <NodeModel> value, the first part of the full model number (ex: 6284 of "6284-4220")
        //    modifier - <Modifier> value, the second part of the full model number (ex: 4220 of "6284-4220")
        //
        //  Returns:
        //    <ModelNumber> integer form of model number cast as a ModelNumber enum value
        static ModelNumber modelNumberFromParts(NodeModel nodeModel, Modifier modifier);

        //API Function: nodeModelFromStr
        //  Returns the NodeModel section of a ModelNumber as an integer value parsed from a model number string.
        //
        //  Parameters:
        //    modelNumberString - model number string formatted as it is read from a MIP device (ex: "6284-4220")
        //
        //  Returns:
        //    <NodeModel> - integer form of the first part of a model number cast as a NodeModel enum value (ex: "6284-4220" -> 6284)
        static NodeModel nodeModelFromStr(const std::string& modelNumberString);

        //Function: modifierFromStr
        //  Returns the Modifier section of a ModelNumber as an integer value parsed from a model number string.
        //
        //  Parameters:
        //    modelNumberString - model number string formatted as it is read from a MIP device (ex: "6284-4220")
        //
        //  Returns:
        //    <uint32> - integer form of the second part of a model number (ex: "6284-4220" -> 4220)
        static uint32 modifierFromStr(const std::string& modelNumberString);

        //Function: nodeModelFromModelNumber
        //  Returns the NodeModel section of a full ModelNumber integer.
        //
        //  Parameters:
        //    modelNumber - <ModelNumber> model number integer i.e. 62844220 ("6284-4220")
        //
        //  Returns:
        //    <NodeModel> - integer form of the first part of a model number cast as a NodeModel enum value (ex: 62844220 -> 6284)
        static NodeModel nodeModelFromModelNumber(ModelNumber modelNumber);

        //Function: modifierFromModelNumber
        //  Returns the Modifier section of a full ModelNumber integer.
        //
        //  Parameters:
        //    modelNumber - <ModelNumber> model number integer i.e. 62844220 ("6284-4220")
        //
        //  Returns:
        //    <uint32> - integer form of the second part of a model number (ex: 62844220 -> 4220)
        static uint32 modifierFromModelNumber(ModelNumber modelNumber);

        //Function stringFromModelNumber
        //  Returns a model number string formatted as it's read from a MIP device from the full ModelNumber integer value.
        //
        //  Parameters:
        //    modelNumber - full model number integer as a <ModelNumber> enum value (ex: 62844220)
        //
        //  Returns:
        //    string - model number string formatted as it would be read from a MIP device (ex: 62844220 -> "6284-4220")
        static std::string stringFromModelNumber(MipModels::ModelNumber modelNumber);

    private:
        // the value to multiply the node model section of a model number before adding the modifier
        static const int MODIFIER_MULTIPLIER = 10000;

        //the length the first part of a MIP model number
        static const std::size_t MODEL_NUM_LEN = 4;

        //the starting index of the modifier section of a MIP model number str
        static const std::size_t MODIFIER_START = MODEL_NUM_LEN + 1;
    };

    //API Class: MipModel
    //    Contains the model information of MIP devices.
    class MipModel
    {
    public:
        //=========================================================================
        //API Const: MipModel Constants
        //  Constant <MipModel> object definitions for each known MIP device.
        //  Most models have 9999 placeholder modifier values because there is no significant interface difference between the different versions of the same base model.
        //  This placeholder value will match to any modifier value read from the device when comparing <MipModel> objects.
        //
        //  mip_model_none           - 00000000 - undefined placeholder
        //  mip_model_3dm_dh3        - 62199999 - 3DM-DH3
        //  mip_model_3dm_gx3_15     - 62279999 - 3DM-GX3-15
        //  mip_model_3dm_gx3_25     - 62239999 - 3DM-GX3-25
        //  mip_model_3dm_gx3_35     - 62259999 - 3DM-GX3-35
        //  mip_model_3dm_gx3_45     - 62289999 - 3DM-GX3-45
        //  mip_model_3dm_rq1_45_lt  - 62329999 - 3DM-RQ1-45-LT
        //  mip_model_3dm_gx4_15     - 62339999 - 3DM-GX4-15
        //  mip_model_3dm_gx4_25     - 62349999 - 3DM-GX4-25
        //  mip_model_3dm_gx4_45     - 62369999 - 3DM-GX4-45
        //  mip_model_3dm_rq1_45_st  - 62399999 - 3DM-RQ1-45-ST
        //  mip_model_mv5_ar         - 62439999 - MV5-AR
        //  mip_model_3dm_gx5_10     - 62559999 - 3DM-GX5-10
        //  mip_model_3dm_gx5_15     - 62549999 - 3DM-GX5-15
        //  mip_model_3dm_gx5_25     - 62539999 - 3DM-GX5-25
        //  mip_model_3dm_gx5_35     - 62529999 - 3DM-GX5-35
        //  mip_model_3dm_gx5_45     - 62519999 - 3DM-GX5-45
        //  mip_model_3dm_cv5_10     - 62599999 - 3DM-CV5-10
        //  mip_model_3dm_cv5_15     - 62589999 - 3DM-CV5-15
        //  mip_model_3dm_cv5_25     - 62579999 - 3DM-CV5-25
        //  mip_model_3dm_cv5_45     - 62569999 - 3DM-CV5-45
        //  mip_model_3dm_gq4_45     - 62509999 - 3DM-GQ4-45
        //  mip_model_3dm_cx5_45     - 62719999 - 3DM-CX5-45
        //  mip_model_3dm_cx5_35     - 62729999 - 3DM-CX5-35
        //  mip_model_3dm_cx5_25     - 62739999 - 3DM-CX5-25
        //  mip_model_3dm_cx5_15     - 62749999 - 3DM-CX5-15
        //  mip_model_3dm_cx5_10     - 62759999 - 3DM-CX5-10
        //  mip_model_3dm_cl5_15     - 62809999 - 3DM-CL5-15
        //  mip_model_3dm_cl5_25     - 62819999 - 3DM-CL5-25
        //  mip_model_3dm_gq7        - 62849999 - 3DM-GQ7
        //  mip_model_3dm_rtk_v1     - 62850000 - 3DM-RTK v1
        //  mip_model_3dm_rtk        - 62850100 - 3DM-RTK
        //  mip_model_3dm_cv7_ahrs   - 62869999 - 3DM-CV7-AHRS
        //  mip_model_3dm_cv7_ar     - 62879999 - 3DM-CV7-AR
        //=========================================================================
        static const MipModel mip_model_none;           //undefined
        static const MipModel mip_model_3dm_dh3;        //3DM-DH3
        static const MipModel mip_model_3dm_gx3_15;     //3DM-GX3-15
        static const MipModel mip_model_3dm_gx3_25;     //3DM-GX3-25
        static const MipModel mip_model_3dm_gx3_35;     //3DM-GX3-35
        static const MipModel mip_model_3dm_gx3_45;     //3DM-GX3-45
        static const MipModel mip_model_3dm_rq1_45_lt;  //3DM-RQ1-45-LT
        static const MipModel mip_model_3dm_rq1_45_st;  //3DM-RQ1-45-ST
        static const MipModel mip_model_3dm_gx4_15;     //3DM-GX4-15
        static const MipModel mip_model_3dm_gx4_25;     //3DM-GX4-25
        static const MipModel mip_model_3dm_gx4_45;     //3DM-GX4-45
        static const MipModel mip_model_mv5_ar;         //MV5-AR
        static const MipModel mip_model_3dm_gx5_10;     //3DM-GX5-10
        static const MipModel mip_model_3dm_gx5_15;     //3DM-GX5-15
        static const MipModel mip_model_3dm_gx5_25;     //3DM-GX5-25
        static const MipModel mip_model_3dm_gx5_35;     //3DM-GX5-35
        static const MipModel mip_model_3dm_gx5_45;     //3DM-GX5-45
        static const MipModel mip_model_3dm_cv5_10;     //3DM-CV5-10
        static const MipModel mip_model_3dm_cv5_15;     //3DM-CV5-15
        static const MipModel mip_model_3dm_cv5_25;     //3DM-CV5-25
        static const MipModel mip_model_3dm_cv5_45;     //3DM-CV5-45
        static const MipModel mip_model_3dm_gq4_45;     //3DM-GQ4-45
        static const MipModel mip_model_3dm_cx5_45;     //3DM-CX5-45
        static const MipModel mip_model_3dm_cx5_35;     //3DM-CX5-35
        static const MipModel mip_model_3dm_cx5_25;     //3DM-CX5-25
        static const MipModel mip_model_3dm_cx5_15;     //3DM-CX5-15
        static const MipModel mip_model_3dm_cx5_10;     //3DM-CX5-10
        static const MipModel mip_model_3dm_cl5_15;     //3DM-CL5-15
        static const MipModel mip_model_3dm_cl5_25;     //3DM-CL5-25
        static const MipModel mip_model_3dm_gq7;        //3DM-GQ7
        static const MipModel mip_model_3dm_rtk_v1;     //3DM-RTK v1
        static const MipModel mip_model_3dm_rtk;        //3DM-RTK
        static const MipModel mip_model_3dm_cv7_ahrs;   //3DM-CV7-AHRS
        static const MipModel mip_model_3dm_cv7_ar;     //3DM-CV7-AR

    private:
        MipModel(); // hide default constructor

        //Constructor: MipModel (not documented)
        //  Creates a MipModel object from a <MipModels::ModelNumber> value.
        //  This is used for instantiating known MipModel constants
        //
        //  Parameters:
        //    modelNumber - the <MipModels::ModelNumber> that represents this object
        MipModel(MipModels::ModelNumber modelNumber);

    public:
        //API Constructor: MipModel
        //  Creates a MipModel object from the model string read from a MIP device (inertial, RTK)
        //
        //  Parameters:
        //    modelNumberStr - the model number string as read from the device, example format: "6284-4220"
        MipModel(const std::string& modelNumberStr);

        //API Constructor: MipModel
        //  Creates a MipModel object based on another MipModel object
        //
        //  Parameters:
        //    copy - the MipModel object to copy values from
        MipModel(const MipModel& copy);

#ifndef SWIG
        //API Operator: == (MipModel, C++ only)
        //  Define == behavior when comparing two MipModel objects (functionally the same as MipModel::equals()).
        //
        //  Parameters:
        //    compare - the MipModel object to compare this to
        //
        //  Returns:
        //    bool - true if both the <NodeModel> and <Modifier> sections of the full model number are equal or either <Modifier> is the placeholder value (9999)
        bool operator==(const MipModel& compare) const;

        //API Operator: != (MipModel, C++ only)
        //  Define != behavior when comparing two MipModel objects (functionally the same as MipModel::equals()).
        //
        //  Parameters:
        //    compare - the MipModel object to compare this to
        //
        //  Returns:
        //    bool - false if both the <NodeModel> and <Modifier> sections of the full model number are equal or either <Modifier> is the placeholder value (9999)
        bool operator!=(const MipModel& compare) const;

        //API Operator: == (<MipModels::ModelNumber, C++ only)
        //  Define == behavior when comparing two MipModel objects (functionally the same as MipModel::equals()).
        //
        //  Parameters:
        //    compare - the <ModelNumber> value to compare this to
        //
        //  Returns:
        //    bool - true if both the <NodeModel> and <Modifier> sections of the full model number are equal or either <Modifier> is the placeholder value (9999)
        bool operator==(const MipModels::ModelNumber& compare) const;

        //API Operator: != (<MipModels::ModelNumber, C++ only)
        //  Define != behavior when comparing two MipModel objects (functionally the same as MipModel::equals()).
        //
        //  Parameters:
        //    compare - the <ModelNumber> value to compare this to
        //
        //  Returns:
        //    bool - false if both the <NodeModel> and <Modifier> sections of the full model number are equal or either <Modifier> is the placeholder value (9999)
        bool operator!=(const MipModels::ModelNumber& compare) const;

        //API Operator: std::string (C++ only)
        //  Define behavior when casting a MipModel to std::string (funtionally the same as MipModel::str()).
        //
        //  Returns:
        //    string - model string formatted as it would be read from the device (ex: 6284-4220)
        operator std::string() const;
#endif
        //API Function: equals
        //  Function to compare two MipModel objects for equality (functionally the same as overloaded == operator).
        //
        //  Parameters:
        //    compare - the MipModel object to compare this to
        //
        //  Returns:
        //    bool - true if both the <NodeModel> and <Modifier> sections of the full model number are equal or either <Modifier> is the placeholder value (9999)
        bool equals(const MipModel& compare) const;

    private:
        // m_modelStr
        //  the model string formatted as it would be read from the device
        std::string m_modelStr;

        // m_first
        //  the NodeModel portion of the full model number (ex 6284 from 6284-4220)
        uint32 m_first;

        // m_second
        //  the Modifier portion of the full model number (ex 4220 from 6284-4220)
        uint32 m_second;

    public:
        //API Function: str
        //  Get the model string formatted as it would be read from the device (ex: 6284-4220) (funtionally the same as std::string overloaded operator).
        //
        //  Returns:
        //    string - model string formatted as it would be read from the device (ex: 6284-4220)
        const std::string str() const { return m_modelStr; }

        //API Function: nodeModel
        //  Get the <NodeModel> value for this model number. Ex: str: "6284-4220", nodeModel: 6284
        //
        //  Returns:
        //    <NodeModel> - the first part of the model number
        MipModels::NodeModel nodeModel() const { return static_cast<MipModels::NodeModel>(m_first); }

        //API Function: modifier
        //  Get the modifier value for this model number. Ex: str: "6284-4220", modifier: 4220
        //  Note: most actual modifier values are not defined in the <Modifier> enum - actual value read from the device likely won't match.
        //
        //  Returns:
        //    uint32 - the second part of the model number
        uint32 modifier() const { return m_second; }

        //API Function: modelNumber
        //  Get the full <ModelNumber> value for this model number. Ex: str: "6284-4220", modelNumber: 62844220
        //  Note: most values in the <ModelNumber> enum use the placeholder modifier - actual value read from the device likely won't match.
        //
        //  Returns:
        //    <ModelNumber> - the full model number integer
        MipModels::ModelNumber modelNumber() const;

    private:
        // Empty map to hold info to match custom model numbers to base models for feature checking, etc.
        static std::map<uint32, const MipModel&> BASE_MODEL_MAP;

    public:
#ifndef SWIG
        //Function: setBaseModelMap (not documented, C++ only)
        //  Sets the BASE_MODEL_MAP to map custom model definitions to base models with known features.
        //
        //  Parameters:
        //    baseModels - the [uint32, <MipModel>&] map where the uint32 key is an integer version of the custom  model and the MipModel entry is the base
        static void setBaseModelMap(std::map<uint32, const MipModel&> baseModels) { BASE_MODEL_MAP = baseModels; }

        //Function: baseModelLookup (not documented, C++ only)
        //  Finds the base model for the specified model as defined by the BASE_MODEL_MAP. The specified model is returned without changes if no base model is found.
        //
        //  Parameters:
        //    model - the <MipModel> to find the base model of and default return if base model entry not found.
        static const MipModel& baseModelLookup(const MipModel& model);
#endif

        //Function: baseModel (not documented)
        //  Get the base model for this device.
        //  This function is present with the intent it will be overloaded for custom model number functionality.
        //
        //  Returns:
        //    <MipModel> - returns reference to itself if custom entry not defined in BASE_MODEL_MAP
        virtual const MipModel& baseModel() const { return baseModelLookup(*this); }
    };

#ifndef SWIG
    //API Operator: == (<MipModels::ModelNumber>, <MipModel> object, C++ only)
    //  Define == behavior when comparing a <MipModels::ModelNumber> enum value and <MipModel> object (functionally the same as comparing the MipModel::modelNumber() value with MipModels::modelNumbersEqual()).
    //
    //  Parameters:
    //    model1 - the first MipModels::ModelNumber value to compare
    //    model2 - the second MipModel object to compare
    //
    //  Returns:
    //    bool - true if both the <NodeModel> and <Modifier> sections of the full model number are equal or either <Modifier> is the placeholder value (9999)
    bool operator==(MipModels::ModelNumber model1, const MipModel& model2);

    //API Operator: != (<MipModels::ModelNumber>, <MipModel> object, C++ only)
    //  Define != behavior when comparing a <MipModels::ModelNumber> enum value and <MipModel> object (functionally the same as comparing the MipModel::modelNumber() value with MipModels::modelNumbersEqual()).
    //
    //  Parameters:
    //    model1 - the first MipModels::ModelNumber value to compare
    //    model2 - the second MipModel object to compare
    //
    //  Returns:
    //    bool - false if both the <NodeModel> and <Modifier> sections of the full model number are equal or either <Modifier> is the placeholder value (9999)
    bool operator!=(MipModels::ModelNumber model1, const MipModel& model2);
#endif
}