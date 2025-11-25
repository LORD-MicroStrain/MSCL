using System;

namespace MSCL_Displacement_Example_CSharp
{
    class Example2
    {
        public static void setCurrentConfig(mscl.DisplacementNode node)
        {
            //seed the device time with the current PC time
            //Note: you can pass your own time to this function as a
            //      parameter in nanoseconds since unix epoch
            node.setDeviceTime();
        }
    }
}