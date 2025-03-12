/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "mscl/MicroStrain/RTK/RTKNode.h"

#include "mscl/MicroStrain/MIP/MipNode_Impl.h"

namespace mscl
{
    uint8 RTKNode::getCommunicationMode()
    {
        return 1;
    }

    void RTKNode::setCommunicationMode(uint8 communicationMode)
    {
        throw Error_NotSupported("Set communication mode (0x7F10) not supported.");
    }

    RTKDeviceStatusFlags RTKNode::getDeviceStatusFlags() const
    {
        return m_impl->getDeviceStatusFlags();
    }

    std::string RTKNode::getActivationCode() const
    {
        return m_impl->getActivationCode();
    }

    uint8 RTKNode::getStatusBitfieldVersion() const
    {
        return getDeviceStatusFlags().version();
    }
}
