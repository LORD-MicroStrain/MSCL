/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#pragma once

namespace mscl
{
#ifndef SWIG
    //Class: StartNonSyncSampling
    //    Contains logic for the StartNonSyncSampling Node command
    class StartNonSyncSampling
    {
        StartNonSyncSampling();                                          //default constructor disabled
        StartNonSyncSampling(const StartNonSyncSampling&);               //copy constructor disabled
        StartNonSyncSampling& operator=(const StartNonSyncSampling&);    //assignment operator disabled

    public:
        //Function: buildCommand
        //    Builds the StartNonSyncSampling command packet
        //
        //Parameters:
        //    nodeAddress - the address of the Node to build the command for
        //
        //Returns:
        //    A <ByteStream> containing the command packet
        static ByteStream buildCommand(NodeAddress nodeAddress);
    };
#endif // !SWIG
} // namespace mscl
