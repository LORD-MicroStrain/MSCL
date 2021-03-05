/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "mscl/MicroStrain/ByteStream.h"
#include "WirelessResponsePattern.h"
#include "mscl/MicroStrain/Wireless/Packets/WirelessPacket.h"

namespace mscl
{
#ifndef SWIG

    //Class: BaseStation_Ping_v2
    //    Contains logic for the base station Ping command (v2).
    class BaseStation_Ping_v2
    {
    public:
        BaseStation_Ping_v2() = delete;                                         //default constructor disabled
        BaseStation_Ping_v2(const BaseStation_Ping_v2&) = delete;               //copy constuctor disabled
        BaseStation_Ping_v2& operator=(const BaseStation_Ping_v2&) = delete;    //assignement operator disabled

    public:
        //Function: buildCommand
        //    Builds the Ping command packet.
        //
        //Returns:
        //    A <ByteStream> containing the base station Ping command.
        static ByteStream buildCommand(WirelessPacket::AsppVersion asppVer);

        //Class: Response
        //    Handles the response to the base station Ping command.
        class Response : public WirelessResponsePattern
        {
        public:
            //Constructor: Response
            //    Creates a Ping Response object.
            //
            //Parameters:
            //    collector - The <ResponseCollector> used to register and unregister the response.
            explicit Response(std::weak_ptr<ResponseCollector> collector);

        protected:
            //Function: matchSuccessResponse
            //    Checks if the packet passed in matches any response to the Ping command.
            //
            //Parameters:
            //    packet - The <WirelessPacket> to check for a match.
            //
            //Returns:
            //    true if the response pattern was found, false otherwise.
            virtual bool matchSuccessResponse(const WirelessPacket& packet) override;
        };
    };

#endif

}