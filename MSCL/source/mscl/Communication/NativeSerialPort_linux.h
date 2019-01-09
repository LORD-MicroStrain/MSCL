/*******************************************************************************
Copyright(c) 2015-2019 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "mscl/Exceptions.h"

namespace mscl
{
    //Title: NativeSerialPort_linux

    //Function: getNativeSerialPort
    //    Just returns the string passed in (no special case needed for Linux, but necessary for Windows)
    //
    //Parameters:
    //    portName - the name of the port to be opened ("COM26")
    //
    //Returns:
    //    The port name string passed in
    std::string getNativeSerialPort(const std::string& portName)
    {
        return portName;
    }
}