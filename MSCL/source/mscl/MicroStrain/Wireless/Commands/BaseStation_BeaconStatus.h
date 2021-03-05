/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/

#pragma once

#include "WirelessResponsePattern.h"
#include "mscl/MicroStrain/Wireless/Packets/WirelessPacket.h"
#include "mscl/Timestamp.h"
#include "BeaconStatus.h"

namespace mscl
{
#ifndef SWIG

    //Class: BaseStation_BeaconStatus
    //    Contains logic for the base station Get Beacon Status command.
    class BaseStation_BeaconStatus
    {
    public:
        BaseStation_BeaconStatus() = delete;                                            //default constructor disabled
        BaseStation_BeaconStatus(const BaseStation_BeaconStatus&) = delete;             //copy constructor disabled
        BaseStation_BeaconStatus& operator=(const BaseStation_BeaconStatus&) = delete;  //assignement operator disabled

    public:
        //Function: buildCommand
        //    Builds the beacon status command.
        //
        //Returns:
        //    A <ByteStream> containing the base station beacon status command.
        static ByteStream buildCommand(WirelessPacket::AsppVersion asppVer);

        //Class: Response
        //    Handles the response to the command
        class Response : public WirelessResponsePattern
        {
        public:
            //Constructor: Response
            //    Creates a get beacon status Response object
            //
            //Parameters:
            //    collector - The <ResponseCollector> used to register and unregister the response
            Response(std::weak_ptr<ResponseCollector> collector);

        private:
            //Variable: m_result
            //    The <BeaconStatus> that holds the result of the command.
            BeaconStatus m_result;

        public:
            //Function: result
            //    Gets the <BeaconStatus> that holds the result of the response.
            BeaconStatus result();

        protected:
            //Function: matchSuccessResponse
            //    Checks if the packet passed in matches the success response.
            //
            //Parameters:
            //    packet - The <WirelessPacket> to try to match.
            //
            //Returns:
            //    true if the success response pattern was found, false otherwise
            bool matchSuccessResponse(const WirelessPacket& packet) override;

            //Function: matchFailResponse
            //    Checks if the packet passed in matches the failure response.
            //
            //Parameters:
            //    packet - The <WirelessPacket> to try to match.
            //
            //Returns:
            //    true if the failure response pattern was found, false otherwise
            bool matchFailResponse(const WirelessPacket& packet) override;
        };
    };

#endif

}