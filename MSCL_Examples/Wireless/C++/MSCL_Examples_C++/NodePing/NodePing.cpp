//MSCL Example: NodePing
//	This example shows how to open a connection with a BaseStation,
//	ping a Node, and get the result and its information.
//
//Updated: 09/12/2014

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
	const int NODE_ADDRESS = 31849;
	 
	try
	{
		//create a SerialConnection with the COM port
		mscl::Connection connection = mscl::Connection::Serial(COM_PORT);

		//create a BaseStation with the SerialConnection
		mscl::BaseStation baseStation(connection);

		//create a WirelessNode with the BaseStation
		mscl::WirelessNode node(NODE_ADDRESS, baseStation);

		cout << "Attempting to ping the Node..." << endl;

		//ping the Node
		mscl::PingResponse response = node.ping();

		//if the ping response was a success
		if(response.success()) 
		{
			//get some details from the response
			cout << "Successfully pinged Node " << NODE_ADDRESS << endl;
			cout << "Base Station RSSI: " << response.baseRssi() << endl;
			cout << "Node RSSI: " << response.nodeRssi() << endl;
		}
		else
		{
			cout << "Failed to ping Node " << NODE_ADDRESS << endl;
		}

	}
	catch(mscl::Error& e)
	{
		cout << "Error: " << e.what() << endl;
	}

	system("pause");
	return 0;
}