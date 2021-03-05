/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "mscl/MicroStrain/MIP/Commands/GenericMipCommand.h"
#include "mscl/MicroStrain/MIP/MipTypes.h"

namespace mscl
{
    //Title: System_Commands

    //Class: CommunicationMode
    //    Contains the logic for the "Communication Mode" command
    //
    //See Also:
    //    <GenericMipCommand>
    class CommunicationMode
    {
    public:
        //Constants: Packet Bytes
        //    CMD_ID                - CMD_GET_SENSOR_RATE_BASE    - The <MipTypes::Command> for this command
        //  FIELD_DATA_BYTE        - 0x90                        - The Data Field Descriptor byte
        static const MipTypes::Command CMD_ID    = MipTypes::CMD_COMMUNICATION_MODE;
        static const uint8 FIELD_DATA_BYTE            = 0x90;
        
    private:
        CommunicationMode();    //disabled default constructor

    public:
        //Function: buildCommand_get
        //    Builds the bytes for the "get" command
        //
        //Returns:
        //    A <ByteStream> that holds the bytes that make up the command
        static ByteStream buildCommand_get();

        //Function: buildCommand_set
        //    Builds the bytes for the "set" command. 
        //
        //Parameters:
        //    communicationMode - The communication mode to set. This is an advanced command, and therefore the communication modes for your device should be researched to determine what each communication mode is.
        //
        //Returns:
        //    A <ByteStream> that holds the bytes that make up the command
        //
        //Exceptions:
        //    - <Error>: An <MipChannel> in the channels parameter is not part of the Sensor descriptor set
        static ByteStream buildCommand_set(uint8 communicationMode);

        class Response : public GenericMipCommand::Response
        {
        protected:
            virtual uint8 fieldDataByte() const    { return FIELD_DATA_BYTE; }

        public:
            Response(std::weak_ptr<ResponseCollector> collector, bool dataResponse);
            uint8 parseResponse(const GenericMipCmdResponse& response) const;
        };
    };
}