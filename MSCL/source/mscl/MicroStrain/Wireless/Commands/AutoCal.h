/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "mscl/Types.h"
#include "mscl/Version.h"
#include "mscl/MicroStrain/ByteStream.h"
#include "WirelessResponsePattern.h"
#include "mscl/MicroStrain/Wireless/WirelessModels.h"
#include "mscl/MicroStrain/Wireless/WirelessTypes.h"
#include "mscl/MicroStrain/Wireless/Packets/WirelessPacket.h"
#include "AutoCalInfo.h"

namespace mscl
{
    class WirelessPacket;
    struct ShuntCalCmdInfo;

    //Struct: AutoCalCmdDetails
    //  Struct used internally to hold details for passing to the AutoCal function.
    //  Contains the ShuntCalCmdInfo that we want user exposed, as well as other internal info.
    struct AutoCalCmdDetails
    {
        NodeAddress nodeAddress;
        ShuntCalCmdInfo commandInfo;
        uint8 chNum;
        WirelessModels::NodeModel nodeType;
        WirelessTypes::ChannelType chType;
        Version firmwareVersion;

        WirelessTypes::Voltage excitationVoltage;
        bool useExcitationVoltage;

        AutoCalCmdDetails():
            nodeAddress(0),
            chNum(0),
            nodeType(static_cast<WirelessModels::NodeModel>(0)),
            chType(WirelessTypes::chType_acceleration),
            firmwareVersion(Version()),
            excitationVoltage(static_cast<WirelessTypes::Voltage>(0)),
            useExcitationVoltage(false)
        {}
    };

    //Class: AutoCal
    //    Contains logic for the AutoCal Node command.
    class AutoCal
    {
    public:
        AutoCal() = delete;                              //default constructor disabled
        AutoCal(const AutoCal&) = delete;                //copy constructor disabled
        AutoCal& operator=(const AutoCal&) = delete;     //assignment operator disabled

    public:
        //Function: buildCommand_shmLink
        //    Builds the AutoCal command packet for the SHM-Link node.
        //
        //Parameters:
        //    asppVer - The <WirelessPacket::AsppVersion> to build the command for.
        //    nodeAddress - The address of the Node to build the command for.
        //
        //Returns:
        //    A <ByteStream> containing the command packet.
        static ByteStream buildCommand_shmLink(WirelessPacket::AsppVersion asppVer, NodeAddress nodeAddress);

        //Function: buildCommand_shmLink201
        //    Builds the AutoCal command packet for the SHM-Link-201 node.
        //
        //Parameters:
        //    asppVer - The <WirelessPacket::AsppVersion> to build the command for.
        //    nodeAddress - The address of the Node to build the command for.
        //
        //Returns:
        //    A <ByteStream> containing the command packet.
        static ByteStream buildCommand_shmLink201(WirelessPacket::AsppVersion asppVer, NodeAddress nodeAddress);

        //Function: buildCommand_shuntCal
        //  Builds the AutoCal command packet for shunt calibration.
        //
        //Parameters:
        //  asppVer - The <WirelessPacket::AsppVersion> to build the command for.
        //  nodeAddress - The address of the Node to build the command for.
        //  details - The <AutoCalCmdDetails> containing all the data for the command.
        //
        //Returns:
        //    A <ByteStream> containing the command packet.
        static ByteStream buildCommand_shuntCal(WirelessPacket::AsppVersion asppVer, NodeAddress nodeAddress, const AutoCalCmdDetails& details);

        //Class: Response
        //    Handles the response to the AutoBalance Node command
        class Response : public WirelessResponsePattern
        {
        public:
            //Constructor: Response
            //    Creates a AutoCal Response object
            //
            //Parameters:
            //    nodeAddress - The node address to check for.
            //    collector - The <ResponseCollector> used to register and unregister the response.
            Response(NodeAddress nodeAddress, std::weak_ptr<ResponseCollector> collector);

        protected:
            //Variable: m_nodeAddress
            //    The node address to look for in the response.
            NodeAddress m_nodeAddress;

            //Variable: m_calStarted
            //    Whether the AutoCal has been successfully started or not (as reported by the Node).
            bool m_calStarted;

            //Variable: m_completionFlag
            //    The <AutoCalCompletionFlag> representing the final autocal status.
            WirelessTypes::AutoCalCompletionFlag m_completionFlag;

            //Variable: m_timeUntilCompletion
            //    The amount of time (in seconds) that the autocal operation will take to complete.
            //    This value gets reported by the Node before starting the calibration.
            float m_timeUntilCompletion;

            //Variable: m_infoBytes
            //    Contains all of the information bytes from the completion response.
            Bytes m_infoBytes;

        public:
            //Function: calStarted
            //    Gets whether the AutoCal operation has started or not.
            //
            //Returns:
            //    true if the Node indicated that the AutoCal operation has started, false otherwise.
            bool calStarted() const;

            //Function: calTime
            //    Gets the total time (in seconds) that the Node reported it will take to complete the AutoCal operation.
            //
            //Returns:
            //    The time (in seconds) that the Node reported it will take to complete AutoCal.
            float calTime() const;

            //Function: completionFlag
            //    Gets the <WirelessTypes::AutoCalCompletionFlag> of the AutoCal operation.
            //
            //Returns:
            //    The <WirelessTypes::AutoCalCompletionFlag> of the AutoCal operation.
            WirelessTypes::AutoCalCompletionFlag completionFlag() const;

            //Function: infoBytes
            //    Gets the information bytes returned from the AutoCal completion packet.
            //
            //Returns:
            //    The information <Bytes> from the AutoCal completion packet.
            const Bytes& infoBytes() const;

            //Function: match
            //    Checks if the <WirelessPacket> passed in matches the expected response pattern's bytes.
            //
            //Parameters:
            //    packet - The <WirelessPacket> in which to try to find the pattern
            //
            //Returns:
            //    true if the packet matches a response pattern, false otherwise
            virtual bool match(const WirelessPacket& packet) override;

        protected:
            //Function: match_nodeReceived
            //    Checks if the <WirelessPacket> passed in matches the "Node Received" packet.
            //
            //Parmeters:
            //    packet - The <WirelessPacket> to try to match.
            //
            //Returns:
            //    true if the packet matches the Node Received packet, false otherwise.
            bool match_nodeReceived(const WirelessPacket& packet);
        };

        class ShmResponse : public AutoCal::Response
        {
        public:
            //Constructor: ShmResponse
            //  Creates an SHM Autocal Response object
            //
            //Parameters:
            //  nodeAddress - The node address to check for.
            //  collector - The <ResponseCollector> used to register and unregister the response.
            ShmResponse(NodeAddress nodeAddress, std::weak_ptr<ResponseCollector> collector);

        protected:
            virtual bool matchSuccessResponse(const WirelessPacket& packet) override;
        };

        class Shm201Response: public AutoCal::Response
        {
        public:
            //Constructor: Shm201Response
            //  Creates an SHM-Link-201 Autocal Response object
            //
            //Parameters:
            //  nodeAddress - The node address to check for.
            //  collector - The <ResponseCollector> used to register and unregister the response.
            Shm201Response(NodeAddress nodeAddress, std::weak_ptr<ResponseCollector> collector);

        protected:
            virtual bool matchSuccessResponse(const WirelessPacket& packet) override;
        };

        class ShuntCalResponse : public AutoCal::Response
        {
        public:
            //Constructor: ShuntCalResponse
            //  Creates a Shunt Cal Autocal Response object
            //
            //Parameters:
            //  nodeAddress - The node address to check for.
            //  collector - The <ResponseCollector> used to register and unregister the response.
            //  channelNumber - The channel number to match in the response
            ShuntCalResponse(NodeAddress nodeAddress, std::weak_ptr<ResponseCollector> collector, uint8 channelNumber);

        private:
            //Variable: m_channelNumber
            //  The channel number to match in the response.
            uint8 m_channelNumber;

        protected:
            virtual bool matchSuccessResponse(const WirelessPacket& packet) override;
        };
    };
}