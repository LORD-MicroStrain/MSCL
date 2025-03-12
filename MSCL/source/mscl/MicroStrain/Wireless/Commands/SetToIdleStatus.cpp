/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "mscl/MicroStrain/Wireless/Commands/SetToIdleStatus.h"

#include "mscl/MicroStrain/Wireless/Commands/SetToIdle.h"

namespace mscl
{
    SetToIdleStatus::SetToIdleStatus(std::shared_ptr<SetToIdle::Response> response) :
        m_response(response),
        m_complete(false)
    {
    }

    SetToIdleStatus::SetToIdleResult SetToIdleStatus::result()
    {
        return m_response->result();
    }

    bool SetToIdleStatus::complete(uint64 timeout) //timeout = 10
    {
        //if it hasn't already been known that it completed
        if(!m_complete)
        {
            //perform a wait on the response object for the specified timeout
            m_complete = m_response->wait(timeout);
        }

        //return the result
        return m_complete;
    }

    void SetToIdleStatus::cancel()
    {
        m_response->cancel();

        m_complete = true;
    }
}
