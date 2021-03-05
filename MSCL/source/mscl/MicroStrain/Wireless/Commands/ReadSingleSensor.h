/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "mscl/MicroStrain/ByteStream.h"
#include "WirelessResponsePattern.h"
#include "mscl/Types.h"

namespace mscl
{

#ifndef SWIG

    //Class: ReadSingleSensor
    //    Contains logic for the Read Single Sensor Node command
    class ReadSingleSensor
    {
    private:
        ReadSingleSensor();                                        //default constructor disabled
        ReadSingleSensor(const ReadSingleSensor&);                //copy constructor disabled
        ReadSingleSensor& operator=(const ReadSingleSensor&);    //assignment operator disabled

    public:
        //Function: buildCommand
        //    Builds the ReadSingleSensor command packet.
        //
        //Parameters:
        //    nodeAddress - The address of the Node to build the command for.
        //
        //Returns:
        //    A <ByteStream> containing the command packet.
        static ByteStream buildCommand(NodeAddress nodeAddress, uint8 channelNumber);

        //Class: Response
        //    Handles the response to the ReadSingleSensor node command
        class Response : public WirelessResponsePattern
        {
        private:
            //Variable: m_sensorValue
            //    The value read from the sensor.
            uint16 m_sensorValue;

        public:
            //Constructor: Response
            //    Creates a ReadSingleSensor Response object
            //
            //Parameters:
            //    collector - The <ResponseCollector> used to register and unregister the response
            explicit Response(std::weak_ptr<ResponseCollector> collector);

        protected:
            //Function: match
            //    Checks if the bytes passed in match the response pattern from their current read position
            //
            //Parameters:
            //    data - The <DataBuffer> containing the bytes in which to try to find the pattern
            //
            //Returns:
            //    true if the response pattern was found, false otherwise
            virtual bool matchSuccessResponse(DataBuffer& data) override;

        public:
            //Function: sensorValue
            //    Gets the sensor value that was in the response to the read single sensor command.
            uint16 sensorValue() const;
        };
    };

#endif
}