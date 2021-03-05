/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "mscl/MicroStrain/MIP/Commands/GenericMipCommand.h"

namespace mscl
{

#ifndef SWIG

    //Class: DeviceStartupSettings
    //    Contains the logic for the Inertial "DeviceStartupSettings" command.
    class DeviceStartupSettings
    {
    public:
        //Constants: Packet Bytes
        //    CMD_ID        - CMD_SAVE_STARTUP_SETTINGS    - The <MipTypes::Command> for this command
        static const MipTypes::Command CMD_ID = MipTypes::CMD_SAVE_STARTUP_SETTINGS;

    private:
        DeviceStartupSettings();                                        //default constructor disabled
        DeviceStartupSettings(const DeviceStartupSettings&);            //copy constructor disabled
        DeviceStartupSettings& operator=(const DeviceStartupSettings&); //assignment operator disabled

    public:
        //Function: buildCommand_saveAsStartup
        //    Builds the command packet for saving as startup.
        //
        //Returns:
        //    A <ByteStream> containing the Inertial DeviceStartupSettings command packet.
        static ByteStream buildCommand_saveAsStartup();

        //Function: buildCommand
        //    Builds the command packet for loading the startup settings.
        //
        //Returns:
        //    A <ByteStream> containing the Inertial DeviceStartupSettings command packet.
        static ByteStream buildCommand_loadStartup();

        //Function: buildCommand
        //    Builds the command packet for loading the default settings.
        //
        //Returns:
        //    A <ByteStream> containing the Inertial DeviceStartupSettings command packet.
        static ByteStream buildCommand_loadDefault();

        //Class: Response
        //    Handles the response to the DeviceStartupSettings command.
        class Response : public GenericMipCommand::Response
        {
        public:
            //Constructor: Response
            //    Creates the DeviceStartupSettings::Response object.
            //    
            //Parameters:
            //    collector - The ResponseCollector to register the response with.
            Response(std::weak_ptr<ResponseCollector> collector);
        };
    };

#endif

}