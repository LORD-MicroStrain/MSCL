/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/

#pragma once

#include "mscl/Types.h"

namespace mscl
{
    //API Class: BaseStationButton
    //    Represents a single button on a BaseStation
    class BaseStationButton
    {
    public:
        //=====================================================================================================
        //API Enums: Command
        //    Represents the types of commands that a <BaseStationButton> can perform.
        //
        //    btn_nodeSleep                - 0    - Puts a Node into sleep mode.
        //    btn_nodeStop                - 1 - Puts a Node into idle mode by stopping/waking it.
        //    btn_enableBeacon            - 2 - Enables the Beacon on the BaseStation
        //    btn_disableBeacon            - 3 - Disable the Beacon on the BaseStation
        //    btn_nodeNonSyncSampling        - 4 - Starts a Node sampling in Non-Synchronized mode.
        //    btn_nodeSyncSampling        - 5 - Starts a Node sampling in Synchronized mode.
        //    btn_nodeArmedDatalogging    - 6 - Starts a Node sampling in Armed Datalogging mode.
        //    btn_cyclePower                - 7 - Cycles the power on the BaseStation.
        //    btn_disabled                - 65535 - Disables the button functionality.
        //=====================================================================================================
        enum Command
        {
            btn_nodeSleep               = 0,
            btn_nodeStop                = 1,
            btn_enableBeacon            = 2,
            btn_disableBeacon           = 3,
            btn_nodeNonSyncSampling     = 4,
            btn_nodeSyncSampling        = 5,
            btn_nodeArmedDatalogging    = 6,
            btn_cyclePower              = 7,
            btn_disabled                = 65535
        };

#ifndef SWIG
        //=====================================================================================================
        //Enums: UserAction
        //    Represents the user action that can be performed to cause a <BaseStationButton> to perform its command.
        //
        //    action_shortPress    - 0 - A Short Press of the button
        //    action_longPress    - 1 - A Long Press of the button
        //=====================================================================================================
        enum UserAction
        {
            action_shortPress    = 0,
            action_longPress    = 1
        };
#endif

    public:
        //API Class: BaseStationButton
        //    Creates a default constructed BaseStationButton object.
        BaseStationButton();

        //API Class: BaseStationButton
        //    Creates a BaseStationButton object.
        //
        //Parameters:
        //    cmd - The <BaseStationButton::Command> to set.
        //    nodeAddress - The node address to target from the button's command, if applicable (defaults to 0, no node).
        BaseStationButton(Command cmd, uint16 nodeAddress = 0);

    private:
        //Variable: m_command
        //    The <Command> of the button.
        Command m_command;

        //Variable: m_nodeAddress
        //    The node address that the button's function pertains to, if applicable.
        uint16 m_nodeAddress;

    public:
        //API Function: command
        //    Gets the <Command> that is currently set in this object.
        //
        //Returns:
        //    A <BaseStationButton::Command> that is currently set in this object.
        BaseStationButton::Command command() const;

        //API Function: command
        //    Sets the <Command> of this BaseStationButton object.
        //
        //Parameters:
        //    cmd - The <BaseStationButton::Command> to set.
        void command(Command cmd);

        //API Function: nodeAddress
        //    Gets the node address that the button's command targets that is currently set in this object.
        //    This is ignored if the command doesn't pertain to a node.
        //    Note: To target all nodes on the frequency, set the node address to 65535.
        //
        //Returns:
        //    The node address that the button's command targets.
        uint16 nodeAddress() const;

        //API Function: nodeAddress
        //    Sets the node address to target from the button's command.
        //    This is ignored if the command doesn't pertain to a node.
        //    Note: To target all nodes on the frequency, set the node address to 65535.
        //
        //Parameters:
        //    address - The node address to target from the button's command.
        void nodeAddress(uint16 address);
    };
}