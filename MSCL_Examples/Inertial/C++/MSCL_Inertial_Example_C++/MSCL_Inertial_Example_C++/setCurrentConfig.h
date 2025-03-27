#pragma once

// MSCL common code header (typically used as a precompiled header)
#include <mscl/stdafx.h>

#include <mscl/MicroStrain/Inertial/InertialNode.h>

static void setCurrentConfig(mscl::InertialNode& node)
{
    // Many other settings are available than shown below
    // Reference the documentation for the full list of commands

    // If the node supports AHRS/IMU
    if (node.features().supportsCategory(mscl::MipTypes::CLASS_AHRS_IMU))
    {
        mscl::MipChannels ahrsImuChs;
        ahrsImuChs.push_back(mscl::MipChannel(mscl::MipTypes::CH_FIELD_SENSOR_SCALED_ACCEL_VEC, mscl::SampleRate::Hertz(500)));
        ahrsImuChs.push_back(mscl::MipChannel(mscl::MipTypes::CH_FIELD_SENSOR_SCALED_GYRO_VEC, mscl::SampleRate::Hertz(100)));

        // Apply to the node
        node.setActiveChannelFields(mscl::MipTypes::CLASS_AHRS_IMU, ahrsImuChs);
    }

    // If the node supports Estimation Filter
    if (node.features().supportsCategory(mscl::MipTypes::CLASS_ESTFILTER))
    {
        mscl::MipChannels estFilterChs;
        estFilterChs.push_back(mscl::MipChannel(mscl::MipTypes::CH_FIELD_ESTFILTER_ESTIMATED_GYRO_BIAS, mscl::SampleRate::Hertz(100)));

        // Apply to the node
        node.setActiveChannelFields(mscl::MipTypes::CLASS_ESTFILTER, estFilterChs);
    }

    // If the node supports GNSS
    if (node.features().supportsCategory(mscl::MipTypes::CLASS_GNSS))
    {
        mscl::MipChannels gnssChs;
        gnssChs.push_back(mscl::MipChannel(mscl::MipTypes::CH_FIELD_GNSS_LLH_POSITION, mscl::SampleRate::Hertz(1)));

        // Apply to the node
        node.setActiveChannelFields(mscl::MipTypes::CLASS_GNSS, gnssChs);
    }

    node.setPitchRollAid(true);

    node.setAltitudeAid(false);

    mscl::PositionOffset offset(0.0f, 0.0f, 0.0f);
    node.setAntennaOffset(offset);
}
