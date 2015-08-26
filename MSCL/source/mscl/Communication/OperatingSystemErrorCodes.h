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
#pragma once

namespace osErrorCodes
{

#ifdef _WIN32
//Windows specific error codes
static const int FILE_NOT_FOUND = 2;
static const int ACCESS_DENIED = 5;



#else
//Linux specific error codes
static const int FILE_NOT_FOUND = 2;

#endif

}