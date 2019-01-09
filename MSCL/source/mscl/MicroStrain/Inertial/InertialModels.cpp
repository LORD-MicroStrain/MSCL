/*******************************************************************************
Copyright(c) 2015-2019 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"

#include "InertialModels.h"
#include "mscl/Utils.h"

namespace mscl
{
    InertialModels::NodeModel InertialModels::nodeFromModelString(const std::string& modelNumberString)
    {
        std::string trimmedString = modelNumberString;

        //trim off any whitespace on the left of the string
        Utils::strTrimLeft(trimmedString);

        //the length of an Inertial Model Number
        static const std::size_t MODEL_NUM_LEN = 4;
        
        //trim off everything except for the first part of the model number
        trimmedString = trimmedString.substr(0, MODEL_NUM_LEN);

        int modelNum = 0;
        try
        {
            //convert the string to an integer
            modelNum = std::stoi(trimmedString);
        }
        catch(...)
        {
            modelNum = 0;
        }

        //cast to a NodeModel and return
        return static_cast<InertialModels::NodeModel>(modelNum);
    }
}