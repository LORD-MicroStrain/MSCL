/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
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