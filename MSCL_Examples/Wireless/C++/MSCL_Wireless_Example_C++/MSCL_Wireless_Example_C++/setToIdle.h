#pragma once

// MSCL common code header (typically used as a precompiled header)
#include <mscl/stdafx.h>

#include <mscl/MicroStrain/Wireless/WirelessNode.h>

static void setToIdle(mscl::WirelessNode& node)
{
    // Call the set to idle function and get the resulting SetToIdleStatus object
    //  Note: This starts the set to idle node command, which is an ongoing operation. The SetToIdleStatus should be queried for progress.
    mscl::SetToIdleStatus status = node.setToIdle();

    printf("Setting Node to Idle");

    // Using the SetToIdleStatus object, check if the Set to Idle operation is complete.
    // Note: we are specifying a timeout of 300 milliseconds here which is the maximum
    //      amount of time that the complete function will block if the Set to Idle
    //      operation has not finished. Leaving this blank defaults to a timeout of 10ms.
    while (!status.complete(300))
    {
        // Note: the Set to Idle operation can be canceled by calling status.cancel()
        printf(".");
    }

    // At this point, the Set to Idle operation has completed

    // Check the result of the Set to Idle operation
    switch (status.result())
    {
        // Completed successfully
        case mscl::SetToIdleStatus::setToIdleResult_success:
        {
            printf("Successfully set to idle!\n");
            break;
        }
        // Canceled by the user
        case mscl::SetToIdleStatus::setToIdleResult_canceled:
        {
            printf("Set to Idle was canceled!\n");
            break;
        }
        // Failed to perform the operation
        case mscl::SetToIdleStatus::setToIdleResult_failed:
        default:
        {
            printf("Set to Idle has failed!\n");
            break;
        }
    }
}
