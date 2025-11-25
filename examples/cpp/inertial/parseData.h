#pragma once

// MSCL common code header (used as precompiled header)
#include <mscl/stdafx.h>

#include <mscl/MicroStrain/Inertial/InertialNode.h>

//Example: Parse Data
//  Shows how to parse incoming data from an Inertial Device.
//  Note that this example does not start a Node sampling (assumes it already is).
static void parseData(mscl::InertialNode& node)
{
    // Endless loop of reading in data
    while (true)
    {
        // Loop through all the data packets from the node, with a timeout of 500 milliseconds
        for (const mscl::MipDataPacket& packet : node.getDataPackets(500))
        {
            // Print out the data
            printf("Packet Received: ");

            // Loop through all the data points in the packet
            for (const mscl::MipDataPoint& dataPoint : packet.data())
            {
                printf("%s: ", dataPoint.channelName().c_str());

                // Print out the channel data
                // Note: The as_string() function is being used here for simplicity.
                //      Other methods (i.e., as_float, as_uint16, as_Vector) are also available.
                //      To determine the format that a dataPoint is stored in, use dataPoint.storedAs().
                printf("%s ", dataPoint.as_string().c_str());

                // If the dataPoint is invalid
                if (!dataPoint.valid())
                {
                    printf("[Invalid] ");
                }
            }

            printf("\n");
        }
    }
}
