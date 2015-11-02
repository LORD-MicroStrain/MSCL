//MSCL Example: ParseData
//	This example shows how to parse incoming data from a Wireless Node.
//	This example does not start a Node sampling. To receive data, a Node
//	must be put into a sampling mode (Sync Sampling, Low Duty Cycle, etc.)
//
//Updated: 11/02/2015

#include <iostream>
using namespace std; 


#include "mscl/Communication/Connection.h"		 
#include "mscl/MicroStrain/Wireless/BaseStation.h"	
#include "mscl/MicroStrain/Wireless/WirelessNode.h" 
#include "mscl/Exceptions.h"

int main(int argc, char **argv)
{
	//TODO: change these constants to match your setup
	const string COM_PORT = "COM3"; 

	try
	{
		//create a BaseStation with the connection
		mscl::BaseStation base(mscl::Connection::Serial(COM_PORT));

		//endless loop of reading in data
		while(true)
		{
			//get all the data sweeps that have been collected by the BaseStation, with a timeout of 500 milliseconds
			mscl::DataSweeps sweeps = base.getData(500);

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

					//Print out the channel data as a string. Other methods (ie. as_float, as_uint16) are also available.
					//Note: The storedAs() function describes how the data is actually stored
					cout << dataPoint.as_string() << " ";	
				}
				cout << endl;
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