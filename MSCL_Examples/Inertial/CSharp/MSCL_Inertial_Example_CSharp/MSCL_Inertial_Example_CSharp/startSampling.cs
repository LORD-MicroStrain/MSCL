using System;

namespace MSCL_Inertial_Example_CSharp
{
    class Example3
    {
        public static void startSampling(mscl.InertialNode node)
        {
            //each class/category is separated into its own command.
            //you can enable them individually if, say, you only wanted the Estimation Filter channels to be streamed

            if (node.features().supportsCategory(mscl.MipTypes.DataClass.CLASS_AHRS_IMU))
            {
                node.enableDataStream(mscl.MipTypes.DataClass.CLASS_AHRS_IMU);
            }

            if (node.features().supportsCategory(mscl.MipTypes.DataClass.CLASS_ESTFILTER))
            {
                node.enableDataStream(mscl.MipTypes.DataClass.CLASS_ESTFILTER);
            }

            if (node.features().supportsCategory(mscl.MipTypes.DataClass.CLASS_GNSS))
            {
                node.enableDataStream(mscl.MipTypes.DataClass.CLASS_GNSS);
            }
        }
    }
}