#pragma once

#include "mscl/mscl.h"

//Example: Parse Data
//  Shows how to parse incoming data from a Displacement Device.
//  Note that this example does not start a Node sampling (assumes it already is).
static void parseData(mscl::DisplacementNode& node)
{
    //endless loop of reading in data
    while(true)
    {
        //get all the data packets from the node, with a timeout of 500 milliseconds
        mscl::MipDataPackets packets = node.getDataPackets(500);

        for(mscl::MipDataPacket packet : packets)
        {
            //print out the data
            cout << "Packet Received: ";

            //get the data in the packet
            mscl::MipDataPoints data = packet.data();
            mscl::MipDataPoint dataPoint;

            //loop through all the data points in the packet
            for(unsigned int itr = 0; itr < data.size(); itr++)
            {
                dataPoint = data[itr];

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