using System;

namespace MSCL_Inertial_Example_CSharp
{
    class Example2
    {
        public static void setCurrentConfig(mscl.InertialNode node)
        {
            //many other settings are available than shown below
            //reference the documentation for the full list of commands

            //if the node supports AHRS/IMU
            if (node.features().supportsCategory(mscl.MipTypes.DataClass.CLASS_AHRS_IMU))
            {
                mscl.MipChannels ahrsImuChs = new mscl.MipChannels();
                ahrsImuChs.Add(new mscl.MipChannel(mscl.MipTypes.ChannelField.CH_FIELD_SENSOR_SCALED_ACCEL_VEC, mscl.SampleRate.Hertz(500)));
                ahrsImuChs.Add(new mscl.MipChannel(mscl.MipTypes.ChannelField.CH_FIELD_SENSOR_SCALED_GYRO_VEC, mscl.SampleRate.Hertz(100)));

                //apply to the node
                node.setActiveChannelFields(mscl.MipTypes.DataClass.CLASS_AHRS_IMU, ahrsImuChs);
            }

            //if the node supports Estimation Filter
            if (node.features().supportsCategory(mscl.MipTypes.DataClass.CLASS_ESTFILTER))
            {
                mscl.MipChannels estFilterChs = new mscl.MipChannels();
                estFilterChs.Add(new mscl.MipChannel(mscl.MipTypes.ChannelField.CH_FIELD_ESTFILTER_ESTIMATED_GYRO_BIAS, mscl.SampleRate.Hertz(100)));

                //apply to the node
                node.setActiveChannelFields(mscl.MipTypes.DataClass.CLASS_ESTFILTER, estFilterChs);
            }

            //if the node supports GNSS
            if (node.features().supportsCategory(mscl.MipTypes.DataClass.CLASS_GNSS))
            {
                mscl.MipChannels gnssChs = new mscl.MipChannels();
                gnssChs.Add(new mscl.MipChannel(mscl.MipTypes.ChannelField.CH_FIELD_GNSS_LLH_POSITION, mscl.SampleRate.Hertz(1)));

                //apply to the node
                node.setActiveChannelFields(mscl.MipTypes.DataClass.CLASS_GNSS, gnssChs);
            }

            node.setPitchRollAid(true);

            node.setAltitudeAid(false);

            mscl.PositionOffset offset = new mscl.PositionOffset(0.0f, 0.0f, 0.0f);
            node.setAntennaOffset(offset);
        }
    }
}