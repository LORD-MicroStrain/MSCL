/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/

#pragma once

#include <memory>
#include "mscl/Types.h"

namespace mscl
{
    namespace SetToIdle { class Response; }    //forward declaration

    //API Class: SetToIdleStatus
    //    Holds the status information of the Set to Idle command.
    class SetToIdleStatus
    {
    public:
        //API Enums: SetToIdleResult
        //    The result of the Set To Idle command once the operation has ceased.
        //
        //setToIdleResult_success       - 0 - The Node has been successfully set to idle.
        //setToIdleResult_canceled      - 1 - The Set to Idle operation has been canceled by the user.
        //setToIdleResult_failed        - 2 - The Set to Idle operation has failed. The state of the Node is unknown.
        //setToIdleResult_notCompleted  - 3 - The Set to Idle operation has not yet completed.
        enum SetToIdleResult
        {
            setToIdleResult_success         = 0,
            setToIdleResult_canceled        = 1,
            setToIdleResult_failed          = 2,
            setToIdleResult_notCompleted    = 3
        };

    private:
        SetToIdleStatus();    //default constructor disabled

    public:
#ifndef SWIG
        //Constructor: SetToIdleStatus
        //    Creates a SetToIdleStatus object
        //
        //Parameters:
        //    response - A shared_ptr to the <SetToIdle::Response> that this status pertains to.
        SetToIdleStatus(std::shared_ptr<SetToIdle::Response> response);
#endif

    private:
        //Variable: m_response
        //    A shared_ptr to the <SetToIdle::Response> that this status pertains to.
        std::shared_ptr<SetToIdle::Response> m_response;

        //Variable: m_complete
        //    Whether or not the Stop Node command has come to a completion.
        bool m_complete;

    public:
        //API Function: result
        //    Gets the <SetToIdleResult> representing the result of the Stop Node command (success, fail, canceled, etc.).
        //    After <complete> is true, this should be called to discover how the command completed.
        //
        //Returns:
        //    A <SetToIdleResult> representing the result of the Stop Node command.
        SetToIdleResult result();

        //API Function: complete
        //    Gets whether the Stop Node command has completed or not, waiting for the specified amount of time before returning.
        //
        //Parameters:
        //    timeout - A timeout (in milliseconds) which determines how long the command may take to return (default of 10 milliseconds).
        //              For example, called with a timeout of 1 second, this function will block for up to 1 second if the Stop Node command has not completed.
        //
        //Returns:
        //    true if the Stop Node command has finished, false if it is still running.
        bool complete(uint64 timeout = 10);

        //API Function: cancel
        //    Cancels the Stop Node operation that this SetToIdleResult belongs to. 
        //    If the Stop Node operation has already been completed/canceled, this will have no effect.
        //
        //Exceptions:
        //    - <Error_Connection>: A connection error has occurred with the BaseStation.
        void cancel();
    };
}