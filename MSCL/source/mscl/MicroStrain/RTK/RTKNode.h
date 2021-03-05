/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/

#pragma once

#include "mscl/MicroStrain/MIP/MipNode.h"
#include "mscl/MicroStrain/LinearEquation.h"

namespace mscl
{
    //API Class: RTKNode
    //    A class representing a MicroStrain RTK Node
    class RTKNode : public MipNode
    {
    private:
        RTKNode();        //default constructor disabled

    public:
        //API Constructor: RTKNode
        //    Creates an RTKNode object.
        //
        //Parameters:
        //    connection - The Connection object used for communication.
        //
        //Exceptions:
        //    - <Error_Connection>: A problem occurred with the Connection.
        explicit RTKNode(Connection connection) : MipNode(connection) {};

        virtual ~RTKNode() {}

#ifndef SWIG
        RTKNode(std::shared_ptr<MipNode_Impl> impl) : MipNode(impl) {}; //constructor with direct underlying implementation for this class.
#endif

        //API Function: getCommunicationMode
        //    Gets the current communication mode that the node is in.
        //
        //Returns:
        //    The communication mode the node is in. This is an advanced command, and therefore the communication modes for your device should be researched to determine what each communication mode is.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command or <MipTypes::DataClass> is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the RTKNode.
        uint8 getCommunicationMode() override;

        //API Function: setCommunicationMode
        //    Sets the communication mode for the node. 
        //    Note: The node info will be reset when doing this and therefore will require being fetched again the next time it is requested.
        //
        //Parameters:
        //    communicationMode - The communication mode to set. This is an advanced command, and therefore the communication modes for your device should be researched to determine what each communication mode is.
        //
        //Exceptions:
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the RTKNode.
        //    - <Error_NotSupported>: The command is not supported.
        void setCommunicationMode(uint8 communicationMode) override;

        //API Function: getDeviceStatusFlags
        //  Gets the status flags for the RTK device.
        //
        //Returns:
        //  RTKDeviceStatusFlags - The struct containing modem and client connection status.
        //
        //Exceptions:
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the RTKNode.
        RTKDeviceStatusFlags getDeviceStatusFlags() const;

        //API Function: getActivationCode
        //    Gets the Activation Code of the RTK device.
        //
        //Returns:
        //    The 32 character Activation Code for the device.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The command is not supported by this Node.
        //    - <Error_Communication>: There was no response to the command. The command timed out.
        //    - <Error_MipCmdFailed>: The command has failed. Check the error code for more details.
        //    - <Error_Connection>: A connection error has occurred with the RTKNode.
        std::string getActivationCode() const;
    };
}
