using System;

namespace MSCL_Inertial_Example_CSharp
{
    class Example1
    {
        public static void getCurrentConfig(mscl.InertialNode node)
        {
            //many other settings are available than shown below
            //reference the documentation for the full list of commands

            //if the node supports AHRS/IMU
            if (node.features().supportsCategory(mscl.MipTypes.DataClass.CLASS_AHRS_IMU))
            {
                //get a list of the AHRS/IMU channels currently active on the Node
                mscl.MipChannels ahrsImuActiveChs = node.getActiveChannelFields(mscl.MipTypes.DataClass.CLASS_AHRS_IMU);

                Console.WriteLine("AHRS/IMU Channels");
                Console.WriteLine("-----------------");
                foreach (mscl.MipChannel ch in ahrsImuActiveChs)
                {
                    Console.WriteLine("Channel Field: " + ch.channelField().ToString("X"));
                    Console.WriteLine("Sample Rate: " + ch.sampleRate().prettyStr());
                }
            }

            //if the node supports Estimation Filter
            if (node.features().supportsCategory(mscl.MipTypes.DataClass.CLASS_ESTFILTER))
            {
                //get a list of the Estimation Filter channels currently active on the Node
                mscl.MipChannels estFilterActiveChs = node.getActiveChannelFields(mscl.MipTypes.DataClass.CLASS_ESTFILTER);

                Console.WriteLine();
                Console.WriteLine("Estimation Filter Channels");
                Console.WriteLine("--------------------------");
                foreach (mscl.MipChannel ch in estFilterActiveChs)
                {
                    Console.WriteLine("Channel Field: " + ch.channelField().ToString("X"));
                    Console.WriteLine("Sample Rate: " + ch.sampleRate().prettyStr());
                }
            }

            //if the node supports GNSS
            if (node.features().supportsCategory(mscl.MipTypes.DataClass.CLASS_GNSS))
            {
                //get a list of the GNSS channels currently active on the Node
                mscl.MipChannels gnssActiveChs = node.getActiveChannelFields(mscl.MipTypes.DataClass.CLASS_GNSS);

                Console.WriteLine();
                Console.WriteLine("GNSS Channels");
                Console.WriteLine("--------------------------");
                foreach (mscl.MipChannel ch in gnssActiveChs)
                {
                    Console.WriteLine("Channel Field: " + ch.channelField().ToString("X"));
                    Console.WriteLine("Sample Rate: " + ch.sampleRate().prettyStr());
                }
            }

            Console.WriteLine("Altitude Aiding enabled?: " + node.getAltitudeAid().ToString());

            mscl.PositionOffset offset = node.getAntennaOffset();
            Console.WriteLine("Antenna Offset: x=" + offset.x().ToString() + " y=" + offset.y().ToString() + " z=" + offset.z().ToString());

            Console.WriteLine("Pitch/Roll Aiding enabled?: " + node.getPitchRollAid().ToString());
        }
    }
}