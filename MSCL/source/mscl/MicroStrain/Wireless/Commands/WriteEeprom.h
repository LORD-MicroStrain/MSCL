/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#pragma once

#include "mscl/MicroStrain/Wireless/Commands/WirelessResponsePattern.h"

namespace mscl
{
#ifndef SWIG
    //Class: WriteEeprom
    //    Contains logic for the WriteEeprom Node command
    class WriteEeprom
    {
        WriteEeprom();                                //default constructor disabled
        WriteEeprom(const WriteEeprom&);                //copy constructor disabled
        WriteEeprom& operator=(const WriteEeprom&);    //assignment operator disabled

    public:
        //Function: buildCommand
        //    Builds the WriteEeprom command packet
        //
        //Parameters:
        //    nodeAddress - the address of the Node to build the command for
        //    eepromAddress - the Eeprom address to write to
        //    valueToWrite - the value to write to the Eeprom
        //
        //Returns:
        //    A <ByteStream> containing the command packet
        static ByteStream buildCommand(NodeAddress nodeAddress, uint16 eepromAddress, uint16 valueToWrite);

        //Class: Response
        //    Handles the response to the WriteEeprom Node command
        class Response : public WirelessResponsePattern
        {
        public:
            //Constructor: Response
            //    Creates a WriteEeprom Response object
            //
            //Parameters:
            //    nodeAddress - the node address to check for
            //    collector - The <ResponseCollector> used to register and unregister the response
            Response(NodeAddress nodeAddress, std::weak_ptr<ResponseCollector> collector);

        private:
            //Variable: m_nodeAddress
            //    The node address to look for in the WriteEeprom response
            NodeAddress m_nodeAddress;

        public:
            //Function: matchSuccessResponse
            //    Checks if the <WirelessPacket> passed in matches the expected response pattern's bytes
            //
            //Parameters:
            //    packet - The <WirelessPacket> in which to try to find the pattern
            //
            //Returns:
            //    true if the packet matches a response pattern, false otherwise
            bool matchSuccessResponse(const WirelessPacket& packet) override;
        };
    };
#endif // !SWIG
} // namespace mscl
