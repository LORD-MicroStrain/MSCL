/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#pragma once

namespace mscl
{
    //Class: ScopeHelper
    //    Class that allows a function to be run when this object goes out of scope.
    class ScopeHelper
    {
        //Variable: m_outOfScopeFunction
        //    The function to run when the ScopeHelper goes out of scope.
        std::function<void()> m_outOfScopeFunction;

        //Variable: m_canceled
        //    Whether the scope function has been canceled or not.
        bool m_canceled;

        ScopeHelper();                                //default constructor disabled
        ScopeHelper(const ScopeHelper&);            //copy constructor disabled
        ScopeHelper& operator=(const ScopeHelper&);    //assignment operator disabled

    public:
        //Constructor: ScopeHelper
        //    Creates a ScopeHelper object.
        //
        //Parameters:
        //    scopeFunction - The function to run when the ScopeHelper object is destroyed.
        ScopeHelper(std::function<void()> scopeFunction);

        //Destructor: ScopeHelper
        //    Runs whatever function was assigned in the creation of the ScopeHelper.
        ~ScopeHelper();

        //Function: cancel
        //    Sets a flag that indicates the originally set function should NOT be run when
        //    the ScopeHelper is destroyed.
        void cancel();
    };
} // namespace mscl
