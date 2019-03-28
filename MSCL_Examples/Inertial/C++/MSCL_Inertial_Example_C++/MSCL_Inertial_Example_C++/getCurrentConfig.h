#pragma once

#include "mscl/mscl.h"

//Example: Get Current Configuration
//  Shows how to read current configuration settings an Inertial Device.
static void getCurrentConfig(mscl::InertialNode& node)
{
    //many other settings are available than shown below
    //reference the documentation for the full list of commands

    //if the node supports AHRS/IMU
    if(node.features().supportsCategory(mscl::MipTypes::CLASS_AHRS_IMU))
    {
        //get a list of the AHRS/IMU channels currently active on the Node
        mscl::MipChannels ahrsImuActiveChs = node.getActiveChannelFields(mscl::MipTypes::CLASS_AHRS_IMU);

        cout << "AHRS/IMU Channels" << endl;
        cout << "-----------------" << endl;
        for(mscl::MipChannel ch : ahrsImuActiveChs)
        {
            cout << "Channel Field: " << std::hex << ch.channelField() << endl;
            cout << "Sample Rate: " << ch.sampleRate().prettyStr() << endl << endl;
        }
    }

    //if the node supports Estimation Filter
    if(node.features().supportsCategory(mscl::MipTypes::CLASS_ESTFILTER))
    {
        //get a list of the Estimation Filter channels currently active on the Node
        mscl::MipChannels estFilterActiveChs = node.getActiveChannelFields(mscl::MipTypes::CLASS_ESTFILTER);

        cout << endl;
        cout << "Estimation Filter Channels" << endl;
        cout << "--------------------------" << endl;
        for(mscl::MipChannel ch : estFilterActiveChs)
        {
            cout << "Channel Field: " << std::hex << ch.channelField() << endl;
            cout << "Sample Rate: " << ch.sampleRate().prettyStr() << endl << endl;
        }
    }

    //if the node supports GNSS
    if(node.features().supportsCategory(mscl::MipTypes::CLASS_GNSS))
    {
        //get a list of the GNSS channels currently active on the Node
        mscl::MipChannels gnssActiveChs = node.getActiveChannelFields(mscl::MipTypes::CLASS_GNSS);

        cout << endl;
        cout << "GNSS Channels" << endl;
        cout << "-------------" << endl;
        for(mscl::MipChannel ch : gnssActiveChs)
        {
            cout << "Channel Field: " << std::hex << ch.channelField() << endl;
            cout << "Sample Rate: " << ch.sampleRate().prettyStr() << endl << endl;
        }
    }

    cout << "Altitude Aiding enabled?: " << node.getAltitudeAid() << endl;

    mscl::PositionOffset offset = node.getAntennaOffset();
    cout << "Antenna Offset: x=" << offset.x() << " y=" << offset.y() << " z=" << offset.z() << endl;

    cout << "Pitch/Roll Aiding enabled?: " << node.getPitchRollAid() << endl;
}