/*******************************************************************************
Copyright(c) 2015-2016 LORD Corporation. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#pragma once

#include "mscl/Types.h"
#include "mscl/Version.h"
#include "mscl/MicroStrain/ByteStream.h"
#include "mscl/MicroStrain/ResponsePattern.h"
#include "mscl/MicroStrain/Wireless/WirelessModels.h"
#include "mscl/MicroStrain/Wireless/WirelessTypes.h"

namespace mscl
{
    class WirelessPacket;
    struct ShuntCalCmdInfo;

    //Class: AutoCal
    //    Contains logic for the AutoCal Node command.
    class AutoCal
    {
    private:
        AutoCal();                              //default constructor disabled
        AutoCal(const AutoCal&);                //copy constructor disabled
        AutoCal& operator=(const AutoCal&);     //assignment operator disabled

    public:
        //Enum: AutoCalType
        //  The types of autocal that are available.
        enum AutoCalType
        {
            calType_shm = 0,
            calType_shunt = 1
        };

    public:
        //Function: buildCommand_shmLink
        //    Builds the AutoCal command packet for the SHM-Link node.
        //
        //Parameters:
        //    nodeAddress - The address of the Node to build the command for.
        //
        //Returns:
        //    A <ByteStream> containing the command packet.
        static ByteStream buildCommand_shmLink(NodeAddress nodeAddress);

        //Function: buildCommand_shuntCal
        //  Builds the AutoCal command packet for shunt calibration.
        //
        //Parameters:
        //  nodeAddress - The address of the Node to build the command for.
        //  info - The <ShuntCalCmdInfo> containing all the data for the command.
        //
        //Returns:
        //    A <ByteStream> containing the command packet.
        static ByteStream buildCommand_shuntCal(NodeAddress nodeAddress, const ShuntCalCmdInfo& info, uint8 chNum, WirelessModels::NodeModel nodeType, WirelessTypes::ChannelType chType);

        //Class: Response
        //    Handles the response to the LongPing Node command
        class Response : public ResponsePattern
        {
        public:
            //Constructor: Response
            //    Creates a AutoCal Response object
            //
            //Parameters:
            //    nodeAddress - The node address to check for.
            //    collector - The <ResponseCollector> used to register and unregister the response.
            Response(NodeAddress nodeAddress, std::weak_ptr<ResponseCollector> collector, AutoCalType type);

        protected:
            //Variable: m_nodeAddress
            //    The node address to look for in the response.
            NodeAddress m_nodeAddress;

            //Variable: m_calType
            //  The type of autocal we are performing.
            AutoCalType m_calType;

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

            //Function: match_nodeReceived
            //    Checks if the <WirelessPacket> passed in matches the "Node Received" packet.
            //
            //Parmeters:
            //    packet - The <WirelessPacket> to try to match.
            //
            //Returns:
            //    true if the packet matches the Node Received packet, false otherwise.
            bool match_nodeReceived(const WirelessPacket& packet);

        protected:
            virtual bool match_shmLink(const WirelessPacket& packet);
            virtual bool match_shuntCal(const WirelessPacket& packet);
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
            virtual bool match_shmLink(const WirelessPacket& packet) override;
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
            virtual bool match_shuntCal(const WirelessPacket& packet) override;
        };
    };
}