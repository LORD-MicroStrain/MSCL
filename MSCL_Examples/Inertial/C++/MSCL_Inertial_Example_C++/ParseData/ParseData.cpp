//MSCL Example: ParseData
//  This example shows how to parse incoming data from an Inertial Device.
//  This example does not start a Node sampling. To receive data, a Node
//  must be put into a sampling mode.
//
//Updated: 12/20/2017

#include <iostream>
using namespace std;

#include "mscl/Types.h"
#include "mscl/MicroStrain/MIP/MipTypes.h"
#include "mscl/Communication/Connection.h"
#include "mscl/MicroStrain/Inertial/InertialNode.h"
#include "mscl/Exceptions.h"

int main(int argc, char **argv)
{
	//TODO: change these constants to match your setup
	const string COM_PORT = "COM15"; //linux: /dev/ttyACM0

	try
	{
		//create a SerialConnection with the COM port
		mscl::Connection connection = mscl::Connection::Serial(COM_PORT);

		//create an InertialNode with the connection
		mscl::InertialNode node(connection);

        //Put the Inertial Node into its idle state
        //  (This is not required but reduces the parsing
        //  burden during initialization and makes visual
        //  confirmation of the commands easier.)
        node.setToIdle();

        //build up the channels to set
        mscl::MipChannels sensorChs;

        //setup Scaled Accelerometer Vector
        sensorChs.push_back(mscl::MipChannel(mscl::MipTypes::CH_FIELD_SENSOR_SCALED_ACCEL_VEC, mscl::SampleRate::Hertz(100)));
        //setup Scaled Gyro Vector
        sensorChs.push_back(mscl::MipChannel(mscl::MipTypes::CH_FIELD_SENSOR_SCALED_GYRO_VEC, mscl::SampleRate::Hertz(100)));
        //set the active channels for the Sensor category on the Node 
        node.setActiveChannelFields(mscl::MipTypes::CLASS_AHRS_IMU, sensorChs);

        //start sampling on the Sensor category of the Node
        node.enableDataStream(mscl::MipTypes::CLASS_AHRS_IMU);

		//endless loop of reading in data
		while(true)
		{
      //get all the data packets from the node, with a timeout of 500 milliseconds
      mscl::MipDataPackets packets = node.getDataPackets(500);

      for(mscl::MipDataPacket packet : packets)
      {
        //print out the data
        cout << "Packet Received: ";

        //get the data in the packet
        mscl::MipDataPoints data = packet.data();
        mscl::MipDataPoint dataPoint;

        //loop through all the data points in the packet
        for(unsigned int itr = 0; itr < data.size(); itr++)
        {
          dataPoint = data[itr];

          //print out the channel data
          cout << dataPoint.as_string() << " "; //Just printing this out as a string. Other methods (ie. as_float, as_uint16, as_Vector) are also available.

          //if the dataPoint is invalid
          if(!dataPoint.valid())
          {
            cout << "[Invalid] ";
          }
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
