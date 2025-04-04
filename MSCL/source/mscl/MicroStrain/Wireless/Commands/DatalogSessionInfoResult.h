/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#pragma once

namespace mscl
{
    //Struct: DatalogSessionInfoResult
    //  Object to represent the result of a DatalogSessionInfo request.
    struct DatalogSessionInfoResult
    {
        //Variable: sessionCount
        //  The total number of sessions logged on the Node.
        uint16 sessionCount;

        //Variable: startAddress
        //  The flash address of the first log header.
        uint32 startAddress;

        //Variable: maxLoggedBytes
        //  The max number of logged bytes.
        uint32 maxLoggedBytes;

        DatalogSessionInfoResult():
            sessionCount(0),
            startAddress(0),
            maxLoggedBytes(0)
        {}
    };
} // namespace mscl
