/*******************************************************************************
Copyright(c) 2015-2016 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
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