/*****************************************************************************************
**          Copyright(c) 2015-2026 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#pragma once

namespace mscl
{
    //Title: NativeSerialPort_linux

    //Function: getNativeSerialPort
    //    Just returns the string passed in (no special case needed for Linux, but necessary for Windows)
    //
    //Parameters:
    //    portName - the name of the port to be opened ("/dev/ttyUSB0")
    //
    //Returns:
    //    The port name string passed in
    inline std::string getNativeSerialPort(const std::string& portName)
    {
        return portName;
    }
} // namespace mscl
