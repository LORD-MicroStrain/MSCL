/*****************************************************************************************
**          Copyright(c) 2015-2026 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#pragma once

#ifdef _WIN32
    #include "mscl/Communication/NativeSerialPort_Win32.h"
#else
    #include "mscl/Communication/NativeSerialPort_linux.h"
#endif // _WIN32
