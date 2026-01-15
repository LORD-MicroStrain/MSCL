/*****************************************************************************************
**          Copyright(c) 2015-2026 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "mscl/MicroStrain/Displacement/DisplacementModels.h"

namespace mscl
{
    DisplacementModels::NodeModel DisplacementModels::nodeFromModelString(const std::string& modelNumberString)
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
        return static_cast<NodeModel>(modelNum);
    }
} // namespace mscl
