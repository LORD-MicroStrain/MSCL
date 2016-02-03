/*******************************************************************************
Copyright(c) 2015-2016 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"

#include <functional>
#include <memory>

#include "InertialNodeFeatures.h"
#include "InertialNodeFeatures_3dm.h"
#include "InertialNodeFeatures_3dm_gx2.h"
#include "InertialNodeFeatures_3dm_dh3.h"
#include "InertialNodeFeatures_3dm_gx3_15.h"
#include "InertialNodeFeatures_3dm_gx3_25.h"
#include "InertialNodeFeatures_3dm_gx3_35.h"
#include "InertialNodeFeatures_3dm_gx3_45.h"
#include "InertialNodeFeatures_3dm_gx4_15.h"
#include "InertialNodeFeatures_3dm_gx4_25.h"
#include "InertialNodeFeatures_3dm_gx4_45.h"
#include "InertialNodeFeatures_3dm_rq1_45.h"
#include "InertialNodeFeatures_fasA.h"

namespace mscl
{
    InertialNodeFeatures::InertialNodeFeatures(const InertialNodeInfo& info):
        m_nodeInfo(info)
    {
    }

    std::unique_ptr<InertialNodeFeatures> InertialNodeFeatures::create(const InertialNodeInfo& info)
    {
        switch(info.model())
        {
            case InertialModels::node_3dm:
                return std::unique_ptr<InertialNodeFeatures>(new InertialNodeFeatures_3dm(info));

            case InertialModels::node_fasA:
                return std::unique_ptr<InertialNodeFeatures>(new InertialNodeFeatures_fasA(info));

            case InertialModels::node_3dm_gx2:
                return std::unique_ptr<InertialNodeFeatures>(new InertialNodeFeatures_3dm_gx2(info));

            case InertialModels::node_3dm_dh3:
                return std::unique_ptr<InertialNodeFeatures>(new InertialNodeFeatures_3dm_dh3(info));

            case InertialModels::node_3dm_gx3_15:
                return std::unique_ptr<InertialNodeFeatures>(new InertialNodeFeatures_3dm_gx3_15(info));

            case InertialModels::node_3dm_gx3_25:
                return std::unique_ptr<InertialNodeFeatures>(new InertialNodeFeatures_3dm_gx3_25(info));

            case InertialModels::node_3dm_gx3_35:
                return std::unique_ptr<InertialNodeFeatures>(new InertialNodeFeatures_3dm_gx3_35(info));

            case InertialModels::node_3dm_gx3_45:
                return std::unique_ptr<InertialNodeFeatures>(new InertialNodeFeatures_3dm_gx3_45(info));

            case InertialModels::node_3dm_gx4_15:
                return std::unique_ptr<InertialNodeFeatures>(new InertialNodeFeatures_3dm_gx4_15(info));

            case InertialModels::node_3dm_gx4_25:
                return std::unique_ptr<InertialNodeFeatures>(new InertialNodeFeatures_3dm_gx4_25(info));

            case InertialModels::node_3dm_gx4_45:
                return std::unique_ptr<InertialNodeFeatures>(new InertialNodeFeatures_3dm_gx4_45(info));

            case InertialModels::node_3dm_rq1_45:
                return std::unique_ptr<InertialNodeFeatures>(new InertialNodeFeatures_3dm_rq1_45(info));

            default:
                //we don't know anything about this node, throw an exception
                throw Error_NotSupported("The Inertial Node model (" + Utils::toStr(info.model()) + ", " + info.modelName() + " ) is not supported by MSCL.");
        }
    }
}