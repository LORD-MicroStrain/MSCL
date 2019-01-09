//MSCL Example: StopNode
//	This example shows how to "stop" a Wireless Node, taking the Node
//	out of its sampling or sleeping mode and putting it into its
//	idle state so that it can be communicated with. 
//	Note: Stopping a Node usually takes a few seconds, but may take up to 2 minutes.
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
	const int NODE_ADDRESS = 31849; 
	 
	try
	{
		//create a SerialConnection with the COM port
		mscl::Connection connection = mscl::Connection::Serial(COM_PORT);

		//create a BaseStation with the SerialConnection
		mscl::BaseStation baseStation(connection);

		//create a WirelessNode with the BaseStation
		mscl::WirelessNode node(NODE_ADDRESS, baseStation);

		//call the set to idle function and get the resulting SetToIdleStatus object
		//	Note: This starts the set to idle node command, which is an ongoing operation. The SetToIdleStatus should be queried for progress.
		mscl::SetToIdleStatus status = node.setToIdle();

		cout << "Setting Node to Idle";

		//using the SetToIdleStatus object, check if the Set to Idle operation is complete.
		//	Note: we are specifying a timeout of 300 milliseconds here which is the maximum
		//		  amount of time that the complete function will block if the Set to Idle
		//		  operation has not finished. Leaving this blank defaults to a timeout of 10ms.
		while(!status.complete(300))
		{
			//Note: the Set to Idle operation can be canceled by calling status.cancel()
			cout << ".";
		}

		//at this point, the Set to Idle operation has completed

		//check the result of the Set to Idle operation
		switch(status.result())
		{
			//completed successfully
			case mscl::SetToIdleStatus::setToIdleResult_success:
			cout << "Successfully set to idle!" << endl;
			break;

			//canceled by the user
			case mscl::SetToIdleStatus::setToIdleResult_canceled:
			cout << "Set to Idle was canceled!" << endl;
			break;

			//failed to perform the operation
			case mscl::SetToIdleStatus::setToIdleResult_failed:
			default:
				cout << "Set to Idle has failed!" << endl;
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