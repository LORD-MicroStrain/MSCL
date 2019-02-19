#pragma once

#include "mscl/mscl.h"

static void parseData(mscl::BaseStation& base)
{
    //endless loop of reading in data
    while(true)
    {
        //get all the data sweeps that have been collected by the BaseStation, with a timeout of 10 milliseconds
        mscl::DataSweeps sweeps = base.getData(10);

        for(mscl::DataSweep sweep : sweeps)
        {
            //print out information about the sweep
            cout << "Packet Received:  ";
            cout << "Node " << sweep.nodeAddress() << " ";
            cout << "Timestamp: " << sweep.timestamp().str() << " ";
            cout << "Tick: " << sweep.tick() << " ";
            cout << "Sample Rate: " << sweep.sampleRate().prettyStr() << " ";
            cout << "Base RSSI: " << sweep.baseRssi() << " ";
            cout << "Node RSSI: " << sweep.nodeRssi() << " ";

            //get the vector of data in the sweep
            mscl::ChannelData data = sweep.data();

            cout << "DATA: ";
            //iterate over each point in the sweep
            for(auto dataPoint : data)
            {
                //print out the channel name
                cout << dataPoint.channelName() << ": ";

                //print out the channel data
                //Note: The as_string() function is being used here for simplicity. 
                //      Other methods (ie. as_float, as_uint16, as_Vector) are also available.
                //      To determine the format that a dataPoint is stored in, use dataPoint.storedAs().
                cout << dataPoint.as_string() << " ";
            }
            cout << endl;
        }
    }
}