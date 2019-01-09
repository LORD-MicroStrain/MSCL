//MSCL Example: ConfigureNode
//	This example shows how to get and set the configuration options for a Wireless Node.
//	Warning: Running this example will change the configuration on the Wireless Node.
//
//Updated: 11/02/2015

#include <iostream>
using namespace std; 

#include "mscl/Communication/Connection.h"
#include "mscl/MicroStrain/Wireless/BaseStation.h"
#include "mscl/MicroStrain/Wireless/WirelessNode.h"
#include "mscl/MicroStrain/Wireless/Features/NodeFeatures.h"
#include "mscl/MicroStrain/Wireless/Configuration/WirelessNodeConfig.h"
#include "mscl/Exceptions.h"

//Function: getCurrentConfig
//	This function demonstrates how to obtain the current configuration
//	settings of a Wireless Node with MSCL.
//
//	Note:	More settings are available than are demoed here. 
//			Reference the documentation for the full list of functions.
void getCurrentConfig(const mscl::WirelessNode& node)
{
	cout << "Current Configuration Settings" << endl;

	//read some of the current configuration settings on the node
	cout << "# of Triggers: " << node.getNumDatalogSessions() << endl;
	cout << "User Inactivity Timeout: " << node.getInactivityTimeout() << " seconds" << endl;
	cout << "Total active channels: " << node.getActiveChannels().count() << endl;
	cout << "# of sweeps: " << node.getNumSweeps() << endl;

	//If a configuration function requires a ChannelMask parameter, this indicates that the
	//option may affect 1 or more channels on the Node. For instance, a hardware gain may
	//affect ch1 and ch2 with just 1 setting. If you know the mask for your Node, you can just provide
	//that mask when asking for the configuration. If you want to programatically determine
	//the mask for each setting, you can ask for the Node's ChannelGroups. See below.

	//get the ChannelGroups that the node supports
	mscl::ChannelGroups chGroups = node.features().channelGroups();

	//iterate over each channel group
	for(const auto& group : chGroups)
	{
		//get all of the settings for this group (ie. may contain linear equation and hardware gain).
		mscl::WirelessTypes::ChannelGroupSettings groupSettings = group.settings();

		//iterate over each setting for this group
		for(auto setting : groupSettings)
		{
			//if the group contains the linear equation setting
			if(setting == mscl::WirelessTypes::chSetting_linearEquation)
			{
				//we can now pass the channel mask (group.channels()) for this group to the node.getLinearEquation function.
				//Note: once this channel mask is known for a specific node (+ fw version), it should never change
				mscl::LinearEquation le = node.getLinearEquation(group.channels());

				cout << "Linear Equation for: " << group.name() << endl;
				cout << "Slope: " << le.slope() << endl;
				cout << "Offset: " << le.offset() << endl;
			}
		}
	}
}


//Function: setCurrentConfig
//	This function demonstrates how to change the configuration
//	settings of a Wireless Node with MSCL.
//
//	Note:	More settings are available than are demoed here. 
//			Reference the documentation for the full list of functions.
void setCurrentConfig(mscl::WirelessNode& node)
{
	cout << endl << "Changing configuration settings...";

	//create a WirelessNodeConfig which is used to set all node configuration options
	mscl::WirelessNodeConfig config;

	//set the configuration options that we want to change 
	config.defaultMode(mscl::WirelessTypes::defaultMode_idle);
	config.inactivityTimeout(7200);
	config.samplingMode(mscl::WirelessTypes::samplingMode_sync);
	config.sampleRate(mscl::WirelessTypes::sampleRate_256Hz);
	config.unlimitedDuration(true);

	//attempt to verify the configuration with the Node we want to apply it to
	//	Note that this step is not required before applying, however the apply will throw an
	//	Error_InvalidNodeConfig exception if the config fails to verify.
	mscl::ConfigIssues issues;
	if(!node.verifyConfig(config, issues))
	{
		cout << "Failed to verify the configuration. The following issues were found:" << endl;

		//print out all of the issues that were found
		for(const auto& issue : issues)
		{
			cout << issue.description() << endl;
		}

		cout << "Configuration will not be applied." << endl;
	}
	else
	{
		//apply the configuration to the Node
		//	Note that this writes multiple options to the Node.
		//	If an Error_NodeCommunication exception is thrown, it is possible that
		//	some options were successfully applied, while others failed. 
		//	It is recommended to keep calling applyConfig until no exception is thrown.
		node.applyConfig(config);
	}

	cout << "Done." << endl;
}

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

		//run the example showing how to retrieve the Node's current configuration
		getCurrentConfig(node);

		//run the example showing how to update/change the Node's current configuration
		setCurrentConfig(node);
	}
	catch(mscl::Error& e)
	{
		cout << "Error: " << e.what() << endl;
	}

	system("pause");
	return 0;
}