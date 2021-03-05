/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "WirelessResponsePattern.h"
#include "mscl/MicroStrain/Wireless/Packets/WirelessPacket.h"
#include "mscl/Timestamp.h"

namespace mscl
{
#ifndef SWIG

    //Class: BaseStation_SetBeacon_v2
    //    Contains logic for the base station set (enable/disable) beacon command (v2)
    class BaseStation_SetBeacon_v2
    {
    public:
        BaseStation_SetBeacon_v2() = delete;                                                //default constructor disabled
        BaseStation_SetBeacon_v2(const BaseStation_SetBeacon_v2&) = delete;                //copy constructor disabled
        BaseStation_SetBeacon_v2& operator=(const BaseStation_SetBeacon_v2&) = delete;    //assignement operator disabled

    public:
        //Function: buildCommand
        //    Builds the set beacon command packet, using the passed in seconds as the start time
        //
        //Parameters:
        //    utcTime - The start time for the beacon in UTC seconds from the Unix Epoch (01/01/1970)
        //
        //Returns:
        //    A <ByteStream> containing the base station set beacon command
        static ByteStream buildCommand(WirelessPacket::AsppVersion asppVer, uint32 utcTime);

        //Class: Response
        //    Handles the response to the base station write eeprom command
        class Response : public WirelessResponsePattern
        {
        public:
            //Constructor: Response
            //    Creates a set beacon Response object
            //
            //Parameters:
            //    utcTime - The start time for the beacon in UTC seconds from the Unix Epoch (01/01/1970)
            //    collector - The <ResponseCollector> used to register and unregister the response
            Response(uint32 utcTime, std::weak_ptr<ResponseCollector> collector);

        private:
            //Variable: m_beaconStartTime
            //    The start time that was sent to the beacon.
            uint32 m_beaconStartTime;

        public:
            //Function: beaconStartTime
            //    Gets the start time that was sent to enable the beacon 
            //
            //Returns:
            //    a <Timestamp> representing the start time that was sent to enable the beacon
            Timestamp beaconStartTime() const;

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