/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#ifdef _WIN32
    #include "NativeSerialPort_Win32.h"
#else
    #include "NativeSerialPort_linux.h"
#endif
