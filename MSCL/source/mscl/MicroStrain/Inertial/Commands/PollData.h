/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#pragma once

#include "mscl/MicroStrain/MIP/Commands/MipCommand.h"

namespace mscl
{
    //Title: PollData

    //Class: PollImuData
    //    Contains the logic for the Poll IMU Data command
    class PollImuData
    {
    public:
        //Constants: Packet Bytes
        //  CMD_ID  - CMD_POLL_SENSOR_DATA  - The <MipTypes::Command> for this command
        static const MipTypes::Command CMD_ID = MipTypes::CMD_POLL_SENSOR_DATA;

        PollImuData() = delete;    //disabled default constructor

        //Function: buildCommand
        //  Builds the bytes in the command
        //
        //Parameters:
        //  fields - The <MipTypes::MipChannelFields> to poll. If this is empty, the message format stored on the device will be used.
        //
        //Returns:
        //  A <ByteStream> that holds the bytes that make up the command
        static ByteStream buildCommand(const MipTypes::MipChannelFields& fields);

        //Class: Response
        //    Handles the response to the command
        //
        //See Also:
        //    <GenericMipCommand::Response>
        class Response: public GenericMipCommand::Response
        {
        public:
            //Constructor: Response
            //    Creates the Response object
            Response(std::weak_ptr<ResponseCollector> collector);
        };
    };




    //Class: PollGnssData
    //    Contains the logic for the Poll GNSS Data command
    class PollGnssData
    {
    public:
        //Constants: Packet Bytes
        //  CMD_ID  - CMD_POLL_GNSS_DATA  - The <MipTypes::Command> for this command
        static const MipTypes::Command CMD_ID = MipTypes::CMD_POLL_GNSS_DATA;

        PollGnssData() = delete;    //disabled default constructor

        //Function: buildCommand
        //  Builds the bytes in the command
        //
        //Parameters:
        //  fields - The <MipTypes::MipChannelFields> to poll. If this is empty, the message format stored on the device will be used.
        //
        //Returns:
        //  A <ByteStream> that holds the bytes that make up the command
        static ByteStream buildCommand(const MipTypes::MipChannelFields& fields);

        //Class: Response
        //    Handles the response to the command
        //
        //See Also:
        //    <GenericMipCommand::Response>
        class Response: public GenericMipCommand::Response
        {
        public:
            //Constructor: Response
            //    Creates the Response object
            Response(std::weak_ptr<ResponseCollector> collector);
        };
    };




    //Class: PollEstFilterData
    //    Contains the logic for the Poll Estimation Filter Data command
    class PollEstFilterData
    {
    public:
        //Constants: Packet Bytes
        //  CMD_ID              - CMD_POLL_EF_DATA  - The <MipTypes::Command> for this command
        static const MipTypes::Command CMD_ID = MipTypes::CMD_POLL_EF_DATA;

        PollEstFilterData() = delete;    //disabled default constructor

        //Function: buildCommand
        //  Builds the bytes in the command
        //
        //Parameters:
        //  fields - The <MipTypes::MipChannelFields> to poll. If this is empty, the message format stored on the device will be used.
        //
        //Returns:
        //  A <ByteStream> that holds the bytes that make up the command
        static ByteStream buildCommand(const MipTypes::MipChannelFields& fields);

        //Class: Response
        //    Handles the response to the command
        //
        //See Also:
        //    <GenericMipCommand::Response>
        class Response: public GenericMipCommand::Response
        {
        public:
            //Constructor: Response
            //    Creates the Response object
            Response(std::weak_ptr<ResponseCollector> collector);
        };
    };
}
