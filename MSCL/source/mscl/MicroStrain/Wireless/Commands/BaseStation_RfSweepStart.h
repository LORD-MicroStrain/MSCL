/*******************************************************************************
Copyright(c) 2015-2016 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "mscl/MicroStrain/ResponsePattern.h"
#include "mscl/Timestamp.h"

namespace mscl
{

    //Class: BaseStation_RfSweepStart
    //    Contains logic for the base station Start RF Sweep command.
    class BaseStation_RfSweepStart
    {
    private:
        BaseStation_RfSweepStart();                                             //default constructor disabled
        BaseStation_RfSweepStart(const BaseStation_RfSweepStart&);              //copy constructor disabled
        BaseStation_RfSweepStart& operator=(const BaseStation_RfSweepStart&);   //assignement operator disabled

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
        static ByteStream buildCommand(uint32 min, uint32 max, uint32 interval, uint16 options);

        //Class: Response
        //    Handles the response to the command
        class Response : public ResponsePattern
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

        public:
            //Function: match
            //    Checks if the packet passed in matches either the success or failure response.
            //
            //Parameters:
            //    packet - The <WirelessPacket> to try to match.
            //
            //Returns:
            //    true if the response pattern was found, false otherwise.
            virtual bool match(const WirelessPacket& packet) override;

        private:
            //Function: matchSuccessResponse
            //    Checks if the packet passed in matches the success response.
            //
            //Parameters:
            //    packet - The <WirelessPacket> to try to match.
            //
            //Returns:
            //    true if the success response pattern was found, false otherwise
            bool matchSuccessResponse(const WirelessPacket& packet);
        };
    };

}