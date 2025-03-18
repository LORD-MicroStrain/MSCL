/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "mscl/MicroStrain/Wireless/Packets/DiagnosticPacket.h"

#include "mscl/MicroStrain/Wireless/DataSweep.h"
#include "mscl/MicroStrain/Wireless/NodeCommTimes.h"

namespace mscl
{
    DiagnosticPacket::DiagnosticPacket(const WirelessPacket& packet)
    {
        //construct the data packet from the wireless packet passed in
        m_nodeAddress              = packet.nodeAddress();
        m_deliveryStopFlags        = packet.deliveryStopFlags();
        m_type                     = packet.type();
        m_nodeRSSI                 = WirelessTypes::UNKNOWN_RSSI;
        m_baseRSSI                 = packet.baseRSSI();
        m_frequency                = packet.frequency();
        m_payload                  = packet.payload();

        //parse the data sweeps in the packet
        parseSweeps();
    }

    void DiagnosticPacket::parseSweeps()
    {
        DataBuffer payload(m_payload);
        m_numSweeps = 1;

        //build the 1 sweep that we need to add
        DataSweep sweep;
        sweep.samplingType(DataSweep::samplingType_Diagnostic);
        sweep.frequency(m_frequency);
        sweep.nodeAddress(m_nodeAddress);

        //use this for the current PC time
        sweep.timestamp(Timestamp::timeNow());

        //get this sweep's node and base rssi values
        sweep.nodeRssi(m_nodeRSSI);
        sweep.baseRssi(m_baseRSSI);

        sweep.calApplied(true);

        //get the packet interval (in seconds)
        uint16 packetInterval = payload.read_uint16();

        sweep.tick(payload.read_uint16());
        sweep.sampleRate(SampleRate::Seconds(packetInterval));

        size_t numInfoItemBytes = payload.size() - 4;
        size_t infoByteCounter = 0;

        ChannelData chData;
        uint8 infoLen = 0;
        uint8 infoId = 0;

        //iterate over all the info bytes
        while(infoByteCounter < numInfoItemBytes)
        {
            infoLen = payload.read_uint8();

            infoId = payload.read_uint8();

            addDataPoint(chData, payload, infoLen - 1, infoId, m_nodeAddress);

            infoByteCounter += infoLen + 1;
        }

        //add the channel data to the sweep
        sweep.data(chData);

        //add the sweep to the container of sweeps
        addSweep(sweep);
    }

    void DiagnosticPacket::addDataPoint(ChannelData& container, DataBuffer& payload, uint8 infoLength, uint8 infoId, NodeAddress nodeAddress)
    {
        switch(infoId)
        {
            //Current State
            case 0x00:
            {
                uint8 val = payload.read_uint8();
                NodeCommTimes::updateDeviceState(nodeAddress, static_cast<DeviceState>(val));
                container.emplace_back(WirelessChannel::channel_diag_state, 0, valueType_uint8, anyType(val));
                break;
            }

            //Run Time
            case 0x01:
                //idle time
                container.emplace_back(WirelessChannel::channel_diag_runtime_idle, 0, valueType_uint32, anyType(payload.read_uint32()));

                //sleep time
                container.emplace_back(WirelessChannel::channel_diag_runtime_sleep, 0, valueType_uint32, anyType(payload.read_uint32()));

                //active run time
                container.emplace_back(WirelessChannel::channel_diag_runtime_activeRun, 0, valueType_uint32, anyType(payload.read_uint32()));

                //inactive run time
                container.emplace_back(WirelessChannel::channel_diag_runtime_inactiveRun, 0, valueType_uint32, anyType(payload.read_uint32()));
                break;

            //Reset Counter
            case 0x02:
                container.emplace_back(WirelessChannel::channel_diag_resetCounter, 0, valueType_uint16, anyType(payload.read_uint16()));
                break;

            //Battery flag
            case 0x03:
                container.emplace_back(WirelessChannel::channel_diag_lowBatteryFlag, 0, valueType_uint8, anyType(payload.read_uint8()));
                break;

            //Sample info
            case 0x04:
                //sweep index
                container.emplace_back(WirelessChannel::channel_diag_sweepIndex, 0, valueType_uint32, anyType(payload.read_uint32()));

                //bad sweep count
                container.emplace_back(WirelessChannel::channel_diag_badSweepCount, 0, valueType_uint32, anyType(payload.read_uint32()));
                break;

            //Transmit info
            case 0x05:
                //total transmissions
                container.emplace_back(WirelessChannel::channel_diag_totalTx, 0, valueType_uint32, anyType(payload.read_uint32()));

                //total retransmissions
                container.emplace_back(WirelessChannel::channel_diag_totalReTx, 0, valueType_uint32, anyType(payload.read_uint32()));

                //total dropped packets
                container.emplace_back(WirelessChannel::channel_diag_totalDroppedPackets, 0, valueType_uint32, anyType(payload.read_uint32()));
                break;

            //Built-in-Test result
            case 0x06:
                //BIT
                container.emplace_back(WirelessChannel::channel_diag_builtInTestResult, 0, valueType_uint32, anyType(payload.read_uint32()));
                break;

            //Event Trigger index
            case 0x07:
                container.emplace_back(WirelessChannel::channel_diag_eventIndex, 0, valueType_uint16, anyType(payload.read_uint16()));
                break;

            //External power
            case 0x08:
                container.emplace_back(WirelessChannel::channel_diag_externalPower, 0, valueType_uint8, anyType(payload.read_uint8()));
                break;

            //Internal Temperature (C)
            case 0x09:
                container.emplace_back(WirelessChannel::channel_diag_internalTemp, 0, valueType_int16, anyType(static_cast<int16>(payload.read_int8())));
                break;

            //LXRS Synchronization Info
            case 0x0A:
                //total transmissions
                container.emplace_back(WirelessChannel::channel_diag_syncAttempts, 0, valueType_uint32, anyType(payload.read_uint32()));

                //total retransmissions
                container.emplace_back(WirelessChannel::channel_diag_syncFailures, 0, valueType_uint32, anyType(payload.read_uint32()));

                //total dropped packets
                container.emplace_back(WirelessChannel::channel_diag_secsSinceLastSync, 0, valueType_uint32, anyType(payload.read_uint32()));
                break;

            //Internal Temperature (C)
            case 0x0B:
                //this field is just an updated version of the previous Internal Temperature (0x09) field
                container.emplace_back(WirelessChannel::channel_diag_internalTemp, 0, valueType_float, anyType(static_cast<float>(payload.read_int16() / 100.0f)));
                break;

            //% Datalogging Memory Full
            case 0x0C:
                container.emplace_back(WirelessChannel::channel_diag_memoryFull, 0, valueType_float, anyType(static_cast<float>(payload.read_uint16() / 100.0f)));
                break;

            //Unknown info
            default:
            {
                //read past the bytes we don't know about
                payload.skipBytes(infoLength);
            }
            break;
        }
    }

    bool DiagnosticPacket::integrityCheck(const WirelessPacket& packet)
    {
        WirelessPacket::Payload payload = packet.payload();

        //verify the minimum payload size
        if(payload.size() < 7)
        {
            return false;
        }

        //verify the delivery stop flags are what we expected
        if(!packet.deliveryStopFlags().pc)
        {
            //packet not intended for the PC
            return false;
        }

        //verify the packet type is correct
        if(packet.type() != packetType_diagnostic)
        {
            //packet is not an LDC packet
            return false;
        }

        //verify packet interval
        if(payload.read_uint16(2) == 0)
        {
            //packet interval should never be 0 (invalid payload)
            return false;
        }

        DataBuffer bytes(payload);

        //skip the sample rate and tick bytes
        bytes.skipBytes(4);

        //verify the payload is correct
        while(bytes.moreToRead())
        {
            uint8 infoLen = bytes.read_uint8();

            if(infoLen == 0)
            {
                //no info length should be 0 (invalid payload)
                return false;
            }

            //verify we can read all the bytes in the length described
            if(bytes.bytesRemaining() < infoLen)
            {
                //can't read all the bytes (invalid payload)
                return false;
            }

            //skip passed the bytes being asked to read
            bytes.skipBytes(infoLen);
        }

        //packet looks valid
        return true;
    }

    UniqueWirelessPacketId DiagnosticPacket::getUniqueId(const WirelessPacket& packet)
    {
        //return the tick value
        return packet.payload().read_uint16(2);
    }
}
