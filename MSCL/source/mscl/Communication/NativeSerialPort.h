/*****************************************************************************************
**          Copyright(c) 2015-2024 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#pragma once

#ifdef _WIN32
    #include "NativeSerialPort_Win32.h"
#else
    #include "NativeSerialPort_linux.h"
#endif
