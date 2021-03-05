/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "OperatingSystemErrorCodes.h"
#include "mscl/Utils.h"
#include "mscl/Exceptions.h"

//Note: most of this code has been taken from the boost file: win_iocp_serial_port_service.ipp under the function "open"

namespace mscl
{
    //Title: NativeSerialPort_Win32

    //Function: getNativeSerialPort
    //    opens a connection to the specified port, sets the correct Byte Size, and gets the handle to it
    //
    //Parameters:
    //    portName - the name of the port to be opened ("COM26")
    //
    //Returns:
    //    The handle to the port as a boost::asio::serial_port::native_handle_type
    //
    //Exceptions:
    //    - <Error_InvalidSerialPort>: the specified com port is invalid
    //    - <Error_Connection>: failed to get or set com port parameters
    boost::asio::serial_port::native_handle_type getNativeSerialPort(const std::string& portName)
    {
        // For convenience, add a leading \\.\ sequence if not already present.
        std::string name = (portName[0] == '\\') ? portName : "\\\\.\\" + portName;

        bool success = false;
        uint16 retryCount = 0;
        DWORD last_error = 0;
        ::HANDLE handle = NULL;
        static const uint16 MAX_RETRIES = 300;

        while(!success && retryCount < MAX_RETRIES)
        {
            // Open a handle to the serial port.
            handle = ::CreateFileA(    name.c_str(),
                                    GENERIC_READ | GENERIC_WRITE,
                                    0,
                                    0,
                                    OPEN_EXISTING,
                                    FILE_FLAG_OVERLAPPED,
                                    0);

            //verify that the handle is valid
            if (handle == INVALID_HANDLE_VALUE)
            {
                //throw an invalid com port exception
                last_error = ::GetLastError();

                //if the error is ACCESS_DENIED
                if(last_error == osErrorCodes::ACCESS_DENIED)
                {
                    //this may be the port is still being closed from a previous close request, we need to retry
                    retryCount++;

                    //sleep for 1 millisecond
                    Utils::threadSleep(1);

                    continue;
                }
                else
                {
                    //any other errors we need to throw an exception
                    throw Error_InvalidSerialPort(last_error);
                }
            }
            else
            {
                //opened the port successfully
                success = true;
            }            
        }

        //if we retried the max times and still didn't succeed
        if(!success)
        {
            throw Error_InvalidSerialPort(last_error);
        }


        // Determine the initial serial port parameters.
        ::DCB dcb;
        std::memset(&dcb, 0, sizeof(DCB));
        dcb.DCBlength = sizeof(DCB);

        //get the current comm state
        if (!::GetCommState(handle, &dcb))
        {
            last_error = ::GetLastError();

            ::CloseHandle(handle);

            //throw a communication error
            throw Error_Connection(last_error);
        }

        //need to set the byte size to 8 
        //This is the whole reason for creating this function. Boost doesn't do this and at some points
        //the bytesize is set to a default of 7, which causes SetCommState to hang
        dcb.ByteSize = 8;

        // Set some default serial port parameters. This implementation does not
        // support changing these, so they might as well be in a known state.
        dcb.fBinary = TRUE;                // Win32 only supports binary mode.
        dcb.fDsrSensitivity = FALSE;
        dcb.fNull = FALSE;                // Do not ignore NULL characters.
        dcb.fAbortOnError = FALSE;        // Ignore serial framing errors.

        //update the comm state with our new values
        if (!::SetCommState(handle, &dcb))
        {
            last_error = ::GetLastError();

            ::CloseHandle(handle);

            //throw a communication error
            throw Error_Connection(last_error);
        }

        //Reads wait for 1ms between bytes, up to a maximum of 8ms (to achieve 120Hz).
        //Write return once everything is out the door.
        //::COMMTIMEOUTS timeouts;
        //timeouts.ReadIntervalTimeout = 1;                //The time (milliseconds) allowed between each byte before the read will return
        //timeouts.ReadTotalTimeoutMultiplier = 0;        //The total timeout (milliseconds) multiplier [m in total = (m * #bytestoread) + b]
        //timeouts.ReadTotalTimeoutConstant = 1;        //The total timeout (milliseconds) constant [b in total = (m * #bytestoread) + b]
        //timeouts.WriteTotalTimeoutMultiplier = 0;
        //timeouts.WriteTotalTimeoutConstant = 0;

        // Set up timeouts so that the serial port will behave similarly to a
        // network socket. Reads wait for at least one byte, then return with
        // whatever they have. Writes return once everything is out the door.
        ::COMMTIMEOUTS timeouts;
        timeouts.ReadIntervalTimeout = MAXDWORD;            //The time (milliseconds) allowed between each byte before the read will return
        timeouts.ReadTotalTimeoutMultiplier = MAXDWORD;        //The total timeout (milliseconds) multiplier [m in total = (m * #bytestoread) + b]
        timeouts.ReadTotalTimeoutConstant = MAXDWORD - 1;    //The total timeout (milliseconds) constant [b in total = (m * #bytestoread) + b]
        timeouts.WriteTotalTimeoutMultiplier = 0;
        timeouts.WriteTotalTimeoutConstant = 0;

        if (!::SetCommTimeouts(handle, &timeouts))
        {
            last_error = ::GetLastError();

            ::CloseHandle(handle);
            
            throw Error_Connection(last_error);
        }

        //return the comm port handle
        return handle;
    }

}