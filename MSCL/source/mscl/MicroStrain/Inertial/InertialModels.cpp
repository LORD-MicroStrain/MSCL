/*****************************************************************************
Copyright(c) 2015 LORD Corporation. All rights reserved.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the included
LICENSE.txt file for a copy of the full GNU General Public License.
*****************************************************************************/
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