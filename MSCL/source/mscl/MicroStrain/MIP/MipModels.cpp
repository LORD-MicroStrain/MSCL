/*****************************************************************************************
**          Copyright(c) 2015-2022 Parker Hannifin Corp. All rights reserved.           **
**                                                                                      **
**    MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.    **
*****************************************************************************************/

#include "stdafx.h"

#include "MipModels.h"
#include "mscl/Utils.h"

#include<math.h>

namespace mscl
{
    bool MipModels::modelNumbersEqual(MipModels::ModelNumber model1, MipModels::ModelNumber model2)
    {
        uint32 m1 = static_cast<uint32>(model1);
        uint32 m2 = static_cast<uint32>(model2);

        // if values exactly equal return true
        if (m1 == m2)
        {
            return true;
        }

        // if first part equal...
        if (m1 / MODIFIER_MULTIPLIER == m2 / MODIFIER_MULTIPLIER)
        {
            // if either second part is placeholder (9999) return true
            if (m1 % MODIFIER_MULTIPLIER == MipModels::Modifier::placeholder_matchAll)
            {
                return true;
            }

            if (m2 % MODIFIER_MULTIPLIER == MipModels::Modifier::placeholder_matchAll)
            {
                return true;
            }
        }

        return false;
    }

    MipModels::ModelNumber MipModels::modelNumberFromStr(const std::string& modelNumberString)
    {
        return modelNumberFromParts(nodeModelFromStr(modelNumberString), static_cast<Modifier>(modifierFromStr(modelNumberString)));
    }

    MipModels::ModelNumber MipModels::modelNumberFromParts(MipModels::NodeModel nodeModel, MipModels::Modifier modifier)
    {
        return static_cast<ModelNumber>((nodeModel * MODIFIER_MULTIPLIER) + modifier);
    }

    MipModels::NodeModel MipModels::nodeModelFromStr(const std::string& modelNumberString)
    {
        //get model number string
        std::string modelStr = modelNumberString;
        Utils::strTrim(modelStr);
        modelStr = modelStr.substr(0, MODEL_NUM_LEN);

        uint32 model = 0;
        try
        {
            //convert the string to an integer
            model = static_cast<uint32>(std::stoi(modelStr));
        }
        catch (...)
        {
            model = 0;
        }

        return static_cast<NodeModel>(model);
    }

    uint32 MipModels::modifierFromStr(const std::string& modelNumberString)
    {
        //get modifier string
        std::string modifierStr = modelNumberString;
        Utils::strTrim(modifierStr);
        modifierStr = modifierStr.substr(MODIFIER_START);

        uint32 modifier = 0;
        try
        {
            // convert string to integer
            modifier = static_cast<uint32>(std::stoi(modifierStr));
        }
        catch (...)
        {
            modifier = 0;
        }

        return modifier;
    }

    MipModels::NodeModel MipModels::nodeModelFromModelNumber(MipModels::ModelNumber modelNumber)
    {
        return static_cast<NodeModel>(modelNumber / MODIFIER_MULTIPLIER);
    }

    uint32 MipModels::modifierFromModelNumber(MipModels::ModelNumber modelNumber)
    {
        return static_cast<uint32>(modelNumber) % MODIFIER_MULTIPLIER;
    }

    std::string MipModels::stringFromModelNumber(MipModels::ModelNumber modelNumber)
    {
        uint32 model = nodeModelFromModelNumber(modelNumber);
        uint32 modifier = modifierFromModelNumber(modelNumber);
        std::stringstream str;
        str << std::setfill('0') << std::setw(4) << model
            << "-"
            << std::setfill('0') << std::setw(4) << modifier;

        return str.str();
    }

    bool operator==(MipModels::ModelNumber model1, const MipModel& model2)
    {
        return MipModels::modelNumbersEqual(model1, model2.modelNumber());
    }

    bool operator!=(MipModels::ModelNumber model1, const MipModel& model2)
    {
        return !MipModels::modelNumbersEqual(model1, model2.modelNumber());
    }

    const MipModel MipModel::mip_model_none("0000-0000");                                          // undefined placeholder
    const MipModel MipModel::mip_model_3dm_dh3(MipModels::ModelNumber::model_3dm_dh3);             // 3DM-DH3
    const MipModel MipModel::mip_model_3dm_gx3_15(MipModels::ModelNumber::model_3dm_gx3_15);       // 3DM-GX3-15
    const MipModel MipModel::mip_model_3dm_gx3_25(MipModels::ModelNumber::model_3dm_gx3_25);       // 3DM-GX3-25
    const MipModel MipModel::mip_model_3dm_gx3_35(MipModels::ModelNumber::model_3dm_gx3_35);       // 3DM-GX3-35
    const MipModel MipModel::mip_model_3dm_gx3_45(MipModels::ModelNumber::model_3dm_gx3_45);       // 3DM-GX3-45
    const MipModel MipModel::mip_model_3dm_rq1_45_lt(MipModels::ModelNumber::model_3dm_rq1_45_lt); // 3DM-RQ1-45-LT
    const MipModel MipModel::mip_model_3dm_rq1_45_st(MipModels::ModelNumber::model_3dm_rq1_45_st); // 3DM-RQ1-45-ST
    const MipModel MipModel::mip_model_3dm_gx4_15(MipModels::ModelNumber::model_3dm_gx4_15);       // 3DM-GX4-15
    const MipModel MipModel::mip_model_3dm_gx4_25(MipModels::ModelNumber::model_3dm_gx4_25);       // 3DM-GX4-25
    const MipModel MipModel::mip_model_3dm_gx4_45(MipModels::ModelNumber::model_3dm_gx4_45);       // 3DM-GX4-45
    const MipModel MipModel::mip_model_mv5_ar(MipModels::ModelNumber::model_mv5_ar);               // MV5-AR
    const MipModel MipModel::mip_model_3dm_gx5_10(MipModels::ModelNumber::model_3dm_gx5_10);       // 3DM-GX5-10
    const MipModel MipModel::mip_model_3dm_gx5_15(MipModels::ModelNumber::model_3dm_gx5_15);       // 3DM-GX5-15
    const MipModel MipModel::mip_model_3dm_gx5_25(MipModels::ModelNumber::model_3dm_gx5_25);       // 3DM-GX5-25
    const MipModel MipModel::mip_model_3dm_gx5_35(MipModels::ModelNumber::model_3dm_gx5_35);       // 3DM-GX5-35
    const MipModel MipModel::mip_model_3dm_gx5_45(MipModels::ModelNumber::model_3dm_gx5_45);       // 3DM-GX5-45
    const MipModel MipModel::mip_model_3dm_cv5_10(MipModels::ModelNumber::model_3dm_cv5_10);       // 3DM-CV5-10
    const MipModel MipModel::mip_model_3dm_cv5_15(MipModels::ModelNumber::model_3dm_cv5_15);       // 3DM-CV5-15
    const MipModel MipModel::mip_model_3dm_cv5_25(MipModels::ModelNumber::model_3dm_cv5_25);       // 3DM-CV5-25
    const MipModel MipModel::mip_model_3dm_cv5_45(MipModels::ModelNumber::model_3dm_cv5_45);       // 3DM-CV5-45
    const MipModel MipModel::mip_model_3dm_gq4_45(MipModels::ModelNumber::model_3dm_gq4_45);       // 3DM-GQ4-45
    const MipModel MipModel::mip_model_3dm_cx5_45(MipModels::ModelNumber::model_3dm_cx5_45);       // 3DM-CX5-45
    const MipModel MipModel::mip_model_3dm_cx5_35(MipModels::ModelNumber::model_3dm_cx5_35);       // 3DM-CX5-35
    const MipModel MipModel::mip_model_3dm_cx5_25(MipModels::ModelNumber::model_3dm_cx5_25);       // 3DM-CX5-25
    const MipModel MipModel::mip_model_3dm_cx5_15(MipModels::ModelNumber::model_3dm_cx5_15);       // 3DM-CX5-15
    const MipModel MipModel::mip_model_3dm_cx5_10(MipModels::ModelNumber::model_3dm_cx5_10);       // 3DM-CX5-10
    const MipModel MipModel::mip_model_3dm_cl5_15(MipModels::ModelNumber::model_3dm_cl5_15);       // 3DM-CL5-15
    const MipModel MipModel::mip_model_3dm_cl5_25(MipModels::ModelNumber::model_3dm_cl5_25);       // 3DM-CL5-25
    const MipModel MipModel::mip_model_3dm_gq7(MipModels::ModelNumber::model_3dm_gq7);             // 3DM-GQ7
    const MipModel MipModel::mip_model_3dm_rtk_v1(MipModels::ModelNumber::model_3dm_rtk_v1);       // 3DM-RTK v1
    const MipModel MipModel::mip_model_3dm_rtk(MipModels::ModelNumber::model_3dm_rtk);             // 3DM-RTK
    const MipModel MipModel::mip_model_3dm_cv7_ahrs(MipModels::ModelNumber::model_3dm_cv7_ahrs);   // 3DM-CV7-AHRS
    const MipModel MipModel::mip_model_3dm_cv7_ar(MipModels::ModelNumber::model_3dm_cv7_ar);       // 3DM-CV7-AR
    const MipModel MipModel::mip_model_3dm_gv7_ahrs(MipModels::ModelNumber::model_3dm_gv7_ahrs);   // 3DM-GV7-AHRS
    const MipModel MipModel::mip_model_3dm_gv7_ar(MipModels::ModelNumber::model_3dm_gv7_ar);       // 3DM-GV7-AR

    MipModel::MipModel() :
        m_modelStr(""),
        m_first(0),
        m_second(0)
    {}

    MipModel::MipModel(const std::string& modelNumberStr) :
        m_first(MipModels::nodeModelFromStr(modelNumberStr)),
        m_second(MipModels::modifierFromStr(modelNumberStr))
    {
        m_modelStr = modelNumberStr;
        Utils::strTrim(m_modelStr);
    }

    MipModel::MipModel(const MipModel& copy) :
        m_modelStr(copy.str()),
        m_first(copy.nodeModel()),
        m_second(copy.modifier())
    {}

#ifndef SWIG
    MipModel::MipModel(MipModels::ModelNumber modelNumber) :
        m_first(MipModels::nodeModelFromModelNumber(modelNumber)),
        m_second(MipModels::modifierFromModelNumber(modelNumber)),
        m_modelStr(MipModels::stringFromModelNumber(modelNumber))
    {}
#endif

    bool MipModel::operator==(const MipModel& compare) const
    {
        return equals(compare);
    }

    bool MipModel::operator!=(const MipModel& compare) const
    {
        return !equals(compare);
    }

    bool MipModel::operator==(const MipModels::ModelNumber& compare) const
    {
        return MipModels::modelNumbersEqual(modelNumber(), compare);
    }

    bool MipModel::operator!=(const MipModels::ModelNumber& compare) const
    {
        return !MipModels::modelNumbersEqual(modelNumber(), compare);
    }

    MipModel::operator std::string() const
    {
        return str();
    }

    bool MipModel::equals(const MipModel& compare) const
    {
        return MipModels::modelNumbersEqual(compare.modelNumber(), modelNumber());
    }

    MipModels::ModelNumber MipModel::modelNumber() const
    {
        return MipModels::modelNumberFromParts(
            static_cast<MipModels::NodeModel>(m_first),
            static_cast<MipModels::Modifier>(m_second));
    }

    std::map<uint32, const MipModel&> MipModel::BASE_MODEL_MAP = {};

    const MipModel& MipModel::baseModelLookup(const MipModel& model)
    {
        uint32 modelInt = static_cast<uint32>(model.modelNumber());
        if (BASE_MODEL_MAP.find(modelInt) == BASE_MODEL_MAP.end())
        {
            return model;
        }

        return BASE_MODEL_MAP.at(modelInt);
    }
}
