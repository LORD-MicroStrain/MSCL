//MSCL Example: BaseStationBeacon
//	This example shows how to Enable and Disable the 
//	beacon (used for Synchronized Sampling) on a BaseStation.
//
//Updated: 10/01/2014

#include <iostream>
#include <chrono>
#include <thread>
using namespace std; 

#include "mscl/Communication/Connection.h"
#include "mscl/MicroStrain/Wireless/BaseStation.h"
#include "mscl/Exceptions.h"

int main(int argc, char **argv)
{
	//TODO: change these constants to match your setup
	const string COM_PORT = "COM3"; 
	 
	try
	{
		//create a BaseStation with the connection
		mscl::BaseStation base(mscl::Connection::Serial(COM_PORT));

		//make sure we can ping the base station
		if(!base.ping())
		{
			cout << "Failed to ping the Base Station" << endl;
		}

		cout << "Attempting to enable the beacon..." << endl;

		//enable the beacon on the Base Station using the PC time
		mscl::Timestamp beaconTime = base.enableBeacon();

		//if we got here, no exception was thrown, so enableBeacon was successful
		cout << "Successfully enabled the beacon on the Base Station" << endl;
		cout << "Beacon's initial Timestamp: " << beaconTime.str() << endl;

		cout << "Beacon is active" << endl << "Sleeping for 3 seconds..." << endl;
		
		std::this_thread::sleep_for(std::chrono::seconds(3));

		//disable the beacon on the Base Station
		base.disableBeacon();

		//if we got here, no exception was thrown, so disableBeacon was successful
		cout << "Successfully disabled the beacon on the Base Station" << endl;
	}
	catch(mscl::Error& e)
	{
		cout << "Error: " << e.what() << endl;
	}

	system("pause");
	return 0;
}