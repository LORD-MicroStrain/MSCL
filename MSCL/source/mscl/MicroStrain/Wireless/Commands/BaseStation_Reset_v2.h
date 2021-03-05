/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/

#pragma once

#include "mscl/MicroStrain/ByteStream.h"
#include "WirelessResponsePattern.h"

namespace mscl
{
    class WirelessPacket;

    //Class: BaseStation_Reset_v2
    //    Contains logic for the BaseStation_Reset_v2 command
    class BaseStation_Reset_v2
    {
    public:
        BaseStation_Reset_v2() = delete;                                        //default constructor disabled
        BaseStation_Reset_v2(const BaseStation_Reset_v2&) = delete;             //copy constructor disabled
        BaseStation_Reset_v2& operator=(const BaseStation_Reset_v2&) = delete;  //assignment operator disabled

        enum ResetType
        {
            resetType_hard = 1,
            resetType_soft = 2
        };

    public:
        //Function: buildCommand
        //    Builds the BaseStation_Reset_v2 command packet
        //
        //Parameters:
        //    resetType - The <ResetType>
        //
        //Returns:
        //    A <ByteStream> containing the BaseStation_Reset_v2 command packet
        static ByteStream buildCommand(ResetType resetType);

        //Class: Response
        //    Handles the response to the BaseStation_Reset_v2 Node command
        class Response : public WirelessResponsePattern
        {
        public:
            //Constructor: Response
            //    Creates a BaseStation_Reset_v2 Response object
            //
            //Parameters:
            //    resetType - The <ResetType> to match in the response.
            //    collector - The <ResponseCollector> used to register and unregister the response
            Response(ResetType resetType, std::weak_ptr<ResponseCollector> collector);

        private:
            //Variable: m_resetType
            //  The <ResetType> to match in the response.
            ResetType m_resetType;

        protected:
            //Function: matchSuccessResponse
            //    Checks if the <WirelessPacket> passed in matches the expected response pattern's bytes
            //
            //Parameters:
            //    packet - The <WirelessPacket> in which to try to find the pattern
            //
            //Returns:
            //    true if the packet matches a response pattern, false otherwise
            virtual bool matchSuccessResponse(const WirelessPacket& packet) override;
        };
    };
}