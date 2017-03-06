/*******************************************************************************
Copyright(c) 2015-2017 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/

#pragma once

#include <memory>

#include "mscl/MicroStrain/Inertial/InertialNodeInfo.h"
#include "mscl/MicroStrain/Inertial/InertialTypes.h"
#include "mscl/MicroStrain/SampleRate.h"

namespace mscl
{    
    //API Class: InertialNodeFeatures
    //    Contains information on which features are supported by an <InertialNode>.
    class InertialNodeFeatures
    {
    private:
        InertialNodeFeatures();                                            //disabled default constructor
        InertialNodeFeatures(const InertialNodeFeatures&);                //disabled copy constructor
        InertialNodeFeatures& operator=(const InertialNodeFeatures&);    //disable assignment operator

    public:
        virtual ~InertialNodeFeatures() {};

    protected:
        //Constructor: InertialNodeFeatures
        //    Creates a InertialNodeFeatures object.
        //
        //Parameters:
        //    info - An <InertialNodeInfo> object representing standard information of the <InertialNode>.
        InertialNodeFeatures(const InertialNodeInfo& info);

        //Variable: m_nodeInfo
        //    The <InertialNodeInfo> object containing basic information retreived from eeprom about the <InertialNode>.
        InertialNodeInfo m_nodeInfo;

    public:
#ifndef SWIG
        //Function: create
        //    Builds and returns a InertialNodeFeatures pointer based on the given parameters.
        //
        //Parameters:
        //    info - An <InertialNodeInfo> object representing standard information of the device.
        //
        //Returns:
        //    An InertialNodeFeatures unique_ptr.
        //
        //Exceptions:
        //    - <Error_NotSupported>: The Node model is not supported by MSCL.
        static std::unique_ptr<InertialNodeFeatures> create(const InertialNodeInfo& info);
#endif

    private:
        //Function: isChannelField
        //  Checks if the uint16 descriptor value is a Channel field or not.
        //
        //Returns:
        //  true if the descriptor is a data channel field, false otherwise.
        static bool isChannelField(uint16 descriptor);

    public:
        //API Function: supportsCategory
        //    Checks whether or not a given <InertialTypes::InertialCategory> is supported by the InertialNode.
        //
        //Parameters:
        //    category - The <InertialTypes::InertialCategory> to check if supported.
        bool supportsCategory(InertialTypes::InertialCategory category) const;

        //API Function: supportsCommand
        //    Checks whether or not the given <InertialTypes::Command> is supported by the InertialNode.
        //
        //Parameters:
        //    commandId - The <InertialTypes::Command> to check if supported.
        //
        //Returns:
        //    true if the <InertialFieldId::ID> is supported by the InertialNode, false otherwise.
        bool supportsCommand(InertialTypes::Command commandId) const;

        //API Function: supportedCommands
        //  Gets a list of the supported <InertialTypes::InertialCommands> that are supported by the InertialNode.
        //
        //Returns:
        //  The <InertialTypes::InertialCommands> supported by the InertialNode.
        InertialTypes::InertialCommands supportedCommands() const;

        //API Function: supportedChannelFields
        //    Gets a list of the supported channel fields for a given <InertialTypes::InertialCategory>.
        //
        //Parameters:
        //    category - The <InertialTypes::InertialCategory> to get the list of supported channels for.
        //
        //Returns:
        //    A <InertialTypes::ChannelFields> object containing the list of supported channel fields.
        //
        //Exceptions:
        //    - <Error_InertialCmdFailed>: The command has failed.
        //    - <Error_Communication>: Timed out waiting for a response.
        //    - <Error_NotSupported>: The <InertialTypes::InertialCategory> is not supported by this node.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        InertialTypes::InertialChannelFields supportedChannelFields(InertialTypes::InertialCategory category) const;

        //API Function: supportedSampleRates
        //    Gets a list of the supported sample rates for a given <InertialTypes::InertialCategory>.
        //
        //Parameters:
        //    category - The <InertialTypes::InertialCategory> to get the sample rate list for.
        //
        //Returns:
        //    A <SampleRates> list containing all the supported sample rates for the provided channel.
        //
        //Exceptions:
        //    - <Error_InertialCmdFailed>: The command has failed.
        //    - <Error_Communication>: Timed out waiting for a response.
        //    - <Error_NotSupported>: The <InertialTypes::InertialCategory> is not supported by this node.
        //    - <Error_Connection>: A connection error has occurred with the InertialNode.
        const SampleRates& supportedSampleRates(InertialTypes::InertialCategory category) const;
    };
}