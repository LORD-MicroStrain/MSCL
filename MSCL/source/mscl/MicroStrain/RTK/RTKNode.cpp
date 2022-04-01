/*****************************************************************************************
**          Copyright(c) 2015-2022 Parker Hannifin Corp. All rights reserved.           **
**                                                                                      **
**    MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.    **
*****************************************************************************************/

#include "stdafx.h"
#include "RTKNode.h"

#include "mscl/Types.h"
#include "mscl/MicroStrain/MIP/Commands/MipCommand.h"
#include "mscl/MicroStrain/MIP/Commands/MIP_Commands.h"
#include "mscl/MicroStrain/MIP/MipNodeFeatures.h"
#include "mscl/MicroStrain/MIP/Packets/MipPacket.h"
#include "mscl/MicroStrain/MIP/MipNode_Impl.h"

#include <algorithm>


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
