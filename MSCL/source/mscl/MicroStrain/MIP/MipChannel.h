/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/

#pragma once

#include "MipTypes.h"
#include "mscl/MicroStrain/SampleRate.h"

namespace mscl
{
    //API Title: MipChannel

    class InertialNode;

    //API Class: MipChannel
    //    Represents a single "channel" or data descriptors that can make up an Inertial Device's message format
    class MipChannel
    {
    public:
        //API Constructor: MipChannel
        //    Creates a MipChannel object.
        //
        //Parameters:
        //    channelField - The <MipTypes::ChannelField> for the channel.
        //    sampleRate - The <SampleRate> for the channel.
        MipChannel(MipTypes::ChannelField channelField, const SampleRate& sampleRate);

        //Default Constuctor: MipChannel
        //    Creates a default MipChannel object.
        MipChannel();

    private:
        //Variable: m_channelField
        //    The <MipTypes::ChannelField> for this channel.
        MipTypes::ChannelField m_channelField;

        //Variable: m_sampleRate
        //    The <SampleRate> of the inertial channel.
        SampleRate m_sampleRate;

    public:
        //API Function: channelField
        //    Gets the <MipTypes::ChannelField> for this channel.
        //
        //Returns:
        //    An <MipTypes::ChannelField> that is set for this channel.
        MipTypes::ChannelField channelField() const;

        //API Function: sampleRate
        //    Gets the <SampleRate> set for this channel.
        //
        //Returns:
        //    The <SampleRate> that is set for this channel.
        const SampleRate& sampleRate() const;

        //API Function: rateDecimation
        //    Gets the rate decimation that is used to determine the sample rate (sample rate = sampleratebase / rate decimation).
        //
        //Returns:
        //    The rate decimation that is used to determine the sample rate
        uint16 rateDecimation(uint16 sampleRateBase) const;

#ifndef SWIG
        //Function: fieldDescriptor
        //    Gets the field descriptor byte of the Inertial Channel.
        //
        //Returns:
        //    The field descriptor byte of the Inertial Channel.
        uint8 fieldDescriptor() const;

        //Function: descriptorSet
        //    Gets the descriptor set byte of the Inertial Channel.
        //
        //Returns:
        //    The descriptor set byte of the Inertial Channel.
        uint8 descriptorSet() const;
#endif
    };

    //API Typedef: MipChannels
    //    typedef for a vector of <MipChannel> objects
    typedef std::vector<MipChannel> MipChannels;
}