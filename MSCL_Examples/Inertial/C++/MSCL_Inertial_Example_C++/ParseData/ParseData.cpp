//MSCL Example: ParseData
//  This example shows how to parse incoming data from an Inertial Device.
//  This example does not start a Node sampling. To receive data, a Node
//  must be put into a sampling mode.
//
//Updated: 01/06/2015

#include <iostream>
using namespace std;

#include "mscl/Communication/Connection.h"
#include "mscl/MicroStrain/Inertial/InertialNode.h"
#include "mscl/Exceptions.h"

int main(int argc, char **argv)
{
	//TODO: change these constants to match your setup
	const string COM_PORT = "COM15";

	try
	{
		//create a SerialConnection with the COM port
		mscl::Connection connection = mscl::Connection::Serial(COM_PORT);

		//create an InertialNode with the connection
		mscl::InertialNode node(connection);

		//endless loop of reading in data
		while(true)
		{
			try
			{
				//This example uses the "getNextDataPacket()" command. This command gets the next InertialDataPacket in the buffer and throws an exception if no data exists.
				//Alternatively, you may use the "getDataPackets()" command to get ALL the InertialDataPackets available in the buffer. If the returned container is empty, no data exists.

				//get the next data packet from the node, with a timeout of 500 milliseconds
				mscl::InertialDataPacket packet = node.getNextDataPacket(500);

				//if we got here, no exception was thrown so data was successfully read in

				//print out the data
				cout << "Packet Received: ";

				//get the data in the packet
				mscl::InertialDataPoints data = packet.data();
				mscl::InertialDataPoint dataPoint;

				//loop through all the data points in the packet
				for(unsigned int itr = 0; itr < data.size(); itr++)
				{
					dataPoint = data[itr];

					//print out the channel data
					cout << dataPoint.str() << ": ";
					cout << dataPoint.as_string() << " "; //Just printing this out as a string. Other methods (ie. as_float, as_uint16, as_Vector) are also available.

					//if the dataPoint is invalid
					if(!dataPoint.valid())
					{
						cout << "[Invalid] ";
					}
				}
				cout << endl;
			}
			catch(mscl::Error_NoData& noData)
			{
				cout << noData.what() << endl;
			}
		}
	}
	catch(mscl::Error& e)
	{
		cout << "Error: " << e.what() << endl;
	}

	system("pause");
	return 0;
}