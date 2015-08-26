//MSCL Example: StopNode
//	This example shows how to "stop" a Wireless Node, taking the Node
//	out of its sampling or sleeping mode and putting it into its
//	idle state so that it can be communicated with. 
//	Note: Stopping a Node usually takes a few seconds, but may take up to 2 minutes.
//
//Updated: 09/15/2014

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

		//call the stop function and get the resulting StopNodeStatus object
		//	Note: This starts the stop node command, which is an ongoing operation. The StopNodeStatus should be queried for progress.
		mscl::StopNodeStatus stopStatus = node.stop();

		cout << "Stopping Node";

		//using the StopNodeStatus object, check if the Stop Node operation is complete.
		//	Note: we are specifying a timeout of 300 millisecond here which is the maximum
		//		  amount of time that the complete function will block if the Stop Node
		//		  operation has not finished. Leaving this blank defaults to a timeout of 10ms.
		while(!stopStatus.complete(300))
		{
			//Note: the Stop Node operation can be canceled by calling stopStatus.cancel()
			cout << ".";
		}

		//at this point, the Stop Node operation has completed

		//check the result of the Stop Node operation
		switch(stopStatus.result())
		{
		//Stop Node completed successfully
		case mscl::StopNodeStatus::stopNodeResult_success:
			cout << "Successfully stopped the Node!" << endl;
			break;

		//Stop Node has been canceled by the user
		case mscl::StopNodeStatus::stopNodeResult_canceled:
			cout << "Stop Node was canceled!" << endl;
			break;

		//Failed to perform the Stop Node operation
		case mscl::StopNodeStatus::stopNodeResult_failed:
		default:
			cout << "Stop Node has failed!" << endl;
			break;
		}
	}
	catch(mscl::Error& e)
	{
		cout << "Error: " << e.what() << endl;
	}

	system("pause");
	return 0;
}