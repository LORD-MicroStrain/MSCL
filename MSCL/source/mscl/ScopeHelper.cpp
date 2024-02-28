/*****************************************************************************************
**          Copyright(c) 2015-2024 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "stdafx.h"
#include "ScopeHelper.h"

namespace mscl
{
    ScopeHelper::ScopeHelper(std::function<void()> scopeFunction):
        m_outOfScopeFunction(scopeFunction),
        m_canceled(false)
    {
    }

    ScopeHelper::~ScopeHelper()
    {
        if(!m_canceled)
        {
            m_outOfScopeFunction();
        }
    }

    void ScopeHelper::cancel()
    {
        m_canceled = true;
    }
}
