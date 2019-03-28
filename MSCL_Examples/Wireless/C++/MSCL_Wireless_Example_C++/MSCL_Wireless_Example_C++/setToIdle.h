#pragma once

#include "mscl/mscl.h"

static void setToIdle(mscl::WirelessNode& node)
{
    //call the set to idle function and get the resulting SetToIdleStatus object
    //  Note: This starts the set to idle node command, which is an ongoing operation. The SetToIdleStatus should be queried for progress.
    mscl::SetToIdleStatus status = node.setToIdle();

    cout << "Setting Node to Idle";

    //using the SetToIdleStatus object, check if the Set to Idle operation is complete.
    //Note: we are specifying a timeout of 300 milliseconds here which is the maximum
    //      amount of time that the complete function will block if the Set to Idle
    //      operation has not finished. Leaving this blank defaults to a timeout of 10ms.
    while(!status.complete(300))
    {
        //Note: the Set to Idle operation can be canceled by calling status.cancel()
        cout << ".";
    }

    //at this point, the Set to Idle operation has completed

    //check the result of the Set to Idle operation
    switch(status.result())
    {
        //completed successfully
        case mscl::SetToIdleStatus::setToIdleResult_success:
            cout << "Successfully set to idle!" << endl;
            break;

        //canceled by the user
        case mscl::SetToIdleStatus::setToIdleResult_canceled:
            cout << "Set to Idle was canceled!" << endl;
            break;

        //failed to perform the operation
        case mscl::SetToIdleStatus::setToIdleResult_failed:
        default:
            cout << "Set to Idle has failed!" << endl;
            break;
    }
}