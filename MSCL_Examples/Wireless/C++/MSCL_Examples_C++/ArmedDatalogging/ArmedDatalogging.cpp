//MSCL Example: ArmedDatalogging
//	This example shows how to create and start an Armed Datalogging sampling network.
//
//Updated: 09/30/2014

#include <iostream>
using namespace std;

#include "mscl/Communication/Connection.h"
#include "mscl/MicroStrain/Wireless/BaseStation.h"
#include "mscl/MicroStrain/Wireless/WirelessNode.h" 
#include "mscl/MicroStrain/Wireless/ArmedDataloggingNetwork.h"
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

		//create an ArmedDataloggingNetwork object, giving it the BaseStation that will be the master BaseStation for the network
		mscl::ArmedDataloggingNetwork network(baseStation);

		//add a WirelessNode to the network.
		//	Note: The Node must already be configured for Armed Datalogging before adding to the network, or else Error_InvalidConfig will be thrown.
		//TODO: Repeat this for all WirelessNodes that you want in the network
		cout << "Adding node to the network...";
		network.addNode(node, "This is an optional <50-char message.");
		cout << "Done." << endl;

		//start all the nodes in the network sampling.
		cout << "Starting the network...";
		network.startSampling();
		cout << "Done." << endl;
	}
	catch(mscl::Error& e)
	{
		cout << "Error: " << e.what() << endl;
	}

	system("pause");
	return 0;
}