using System;

namespace MSCL_Wireless_Example_CSharp
{
    class Example5
    {
        public static void setToIdle(mscl.WirelessNode node)
        {
            //call the set to idle function and get the resulting SetToIdleStatus object
            mscl.SetToIdleStatus status = node.setToIdle();

            Console.Write("Setting Node to Idle");

            //using the SetToIdleStatus object, check if the Set to Idle operation is complete.
            //	Note: we are specifying a timeout of 300 milliseconds here which is the maximum
            //		  amount of time that the complete function will block if the Set to Idle
            //		  operation has not finished. Leaving this blank defaults to a timeout of 10ms.
            while (!status.complete(300))
            {
                //Note: the Set to Idle operation can be canceled by calling status.cancel()
                Console.Write(".");
            }

            //at this point, the Set to Idle operation has completed

            //check the result of the Set to Idle operation
            switch (status.result())
            {
                //completed successfully
                case mscl.SetToIdleStatus.SetToIdleResult.setToIdleResult_success:
                    Console.WriteLine("Successfully set to idle!");
                    break;

                //canceled by the user
                case mscl.SetToIdleStatus.SetToIdleResult.setToIdleResult_canceled:
                    Console.WriteLine("Set to Idle was canceled!");
                    break;

                //Failed to perform the operation
                case mscl.SetToIdleStatus.SetToIdleResult.setToIdleResult_failed:
                default:
                    Console.WriteLine("Set to Idle has failed!");
                    break;
            }
        }
    }
}