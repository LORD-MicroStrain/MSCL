/*****************************************************************************************
**          Copyright(c) 2015-2026 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#pragma once

namespace mscl
{
#ifndef SWIG
    //Class: Sleep
    //    Contains logic for the Sleep Node command
    class Sleep
    {
    public:
        Sleep() = delete;                           //default constructor disabled
        Sleep(const Sleep&) = delete;               //copy constructor disabled
        Sleep& operator=(const Sleep&) = delete;    //assignment operator disabled

        //Function: buildCommand
        //    Builds the Sleep command packet.
        //
        //Parameters:
        //    nodeAddress - The address of the Node to build the command for.
        //
        //Returns:
        //    A <ByteStream> containing the command packet.
        static ByteStream buildCommand(NodeAddress nodeAddress);
    };
#endif // !SWIG
} // namespace mscl
