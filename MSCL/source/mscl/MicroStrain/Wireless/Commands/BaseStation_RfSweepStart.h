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

    //Class: BaseStation_RfSweepStart
    //    Contains logic for the base station Start RF Sweep command.
    class BaseStation_RfSweepStart
    {
    public:
        BaseStation_RfSweepStart() = delete;                                             //default constructor disabled
        BaseStation_RfSweepStart(const BaseStation_RfSweepStart&) = delete;              //copy constructor disabled
        BaseStation_RfSweepStart& operator=(const BaseStation_RfSweepStart&) = delete;   //assignement operator disabled

    public:
        //Function: buildCommand
        //    Builds the beacon status command.
        //
        //Parameters:
        //    min - The minimum sweep frequency in kHz (2400000 = 2.4GHz).
        //    max - The maximum sweep frequency in kHz (2400000 = 2.4GHz).
        //    interval - The sweep interval in kHz.
        //    options - The options to send with the command (advanced, used internally).
        //
        //Returns:
        //    A <ByteStream> containing the base station beacon status command.        
        static ByteStream buildCommand(WirelessPacket::AsppVersion asppVer, uint32 min, uint32 max, uint32 interval, uint16 options);

        //Class: Response
        //    Handles the response to the command
        class Response : public WirelessResponsePattern
        {
        private:
            //Variable: m_min;
            //  The min frequency to match in the response.
            uint32 m_min;

            //Variable: m_max;
            //  The max frequency to match in the response.
            uint32 m_max;

            //Variable: m_interval;
            //  The interval to match in the response.
            uint32 m_interval;

            //Variable: m_options
            //  The options to send with the command.
            uint16 m_options;

        public:
            //Constructor: Response
            //    Creates a get beacon status Response object
            //
            //Parameters:
            //    collector - The <ResponseCollector> used to register and unregister the response
            //    min - The minimum sweep frequency to match.
            //    max - The maximum sweep frequency to match.
            //    interval - The sweep interval to match.
            //    options - The advanced options to match.
            Response(std::weak_ptr<ResponseCollector> collector, uint32 min, uint32 max, uint32 interval, uint16 options);

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
        };
    };

}