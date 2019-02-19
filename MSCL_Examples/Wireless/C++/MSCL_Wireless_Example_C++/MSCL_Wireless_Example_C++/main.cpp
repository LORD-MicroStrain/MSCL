#include <iostream>
using namespace std;

#include "mscl/mscl.h"

#include "enableDisableBeacon.h"
#include "getCurrentConfig.h"
#include "parseData.h"
#include "pingNode.h"
#include "setCurrentConfig.h"
#include "setToIdle.h"
#include "startSyncSampling.h"

int main(int argc, char **argv)
{
    //TODO: change these constants to match your setup
    const string COM_PORT = "COM3";
    const int NODE_ADDRESS = 65364;

    try
    {
        //create a SerialConnection with the COM port
        mscl::Connection connection = mscl::Connection::Serial(COM_PORT);

        //create a BaseStation with the SerialConnection
        mscl::BaseStation baseStation(connection);

        //create a WirelessNode with the BaseStation
        mscl::WirelessNode node(NODE_ADDRESS, baseStation);

        //TODO: add as many other WirelessNode objects here as you want (used in the startSyncSampling example)
        std::vector<mscl::WirelessNode> networkNodes;
        networkNodes.push_back(node);

        //due to the nature of wireless devices, it is possible to lose packets over the air.
        //MSCL has a built in way of performing retries whenever an eeprom address is attempted to be read.
        //By default, this value is set to 0. You may wish to keep it at 0 and handle retries yourself depending on your application.
        baseStation.readWriteRetries(3);
        node.readWriteRetries(3);

        //TODO: Uncomment the lines below to run the examples

        //Example: Ping Node
        //pingNode(node);

        //Example: Get Configuration
        //getCurrentConfig(node);

        //Example: Set Configuration
        //setCurrentConfig(node);       //Warning: this example changes settings on your Node!

        //Example: Start Sampling
        //startSyncSampling(baseStation, networkNodes);

        //Example: Set to Idle
        //setToIdle(node);

        //Example: Parse Data
        //parseData(baseStation);

        //Example: Enable and Disable beacon
        //enableDisableBeacon(baseStation);
    }
    catch(mscl::Error& e)
    {
        cout << "Error: " << e.what() << endl;
    }

    system("pause");
    return 0;
}