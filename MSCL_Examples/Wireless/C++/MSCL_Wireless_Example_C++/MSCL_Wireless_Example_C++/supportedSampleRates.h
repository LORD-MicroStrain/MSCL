#include <mscl/MicroStrain/Wireless/WirelessNode.h>
#include <mscl/MicroStrain/Wireless/Features/ChannelGroup.h>
#include <mscl/MicroStrain/Wireless/Features/NodeFeatures.h>
#include <iostream>
#include <chrono>
#include <thread>

// possible rates from the enum
std::vector<mscl::WirelessTypes::WirelessSampleRate> sampleRates = {
        mscl::WirelessTypes::sampleRate_1Hz,
        mscl::WirelessTypes::sampleRate_2Hz,
        mscl::WirelessTypes::sampleRate_4Hz,
        mscl::WirelessTypes::sampleRate_8Hz,
        mscl::WirelessTypes::sampleRate_16Hz,
        mscl::WirelessTypes::sampleRate_32Hz,
        mscl::WirelessTypes::sampleRate_64Hz,
        mscl::WirelessTypes::sampleRate_128Hz,
        mscl::WirelessTypes::sampleRate_256Hz,
        mscl::WirelessTypes::sampleRate_512Hz,
        mscl::WirelessTypes::sampleRate_1024Hz,
        mscl::WirelessTypes::sampleRate_2048Hz,
        mscl::WirelessTypes::sampleRate_4096Hz,
        // Add more if supported
};

std::string sampleRateEnumName(mscl::WirelessTypes::WirelessSampleRate rate)
{
    switch (rate)
    {
    case 113:     return "sampleRate_1Hz";
    case 112:     return "sampleRate_2Hz";
    case 111:     return "sampleRate_4Hz";
    case 110:     return "sampleRate_8Hz";
    case 109:     return "sampleRate_16Hz";
    case 108:     return "sampleRate_32Hz";
    case 107:     return "sampleRate_64Hz";
    case 106:     return "sampleRate_128Hz";
    case 105:     return "sampleRate_256Hz";
    case 104:     return "sampleRate_512Hz";
    case 103:     return "sampleRate_1024Hz";
    case 102:     return "sampleRate_2048Hz";
    case 101:     return "sampleRate_4096Hz";

    default:                 return "unknown";
    }
}

mscl::WirelessTypes::SamplingMode samplingMode = mscl::WirelessTypes::samplingMode_sync;
mscl::WirelessTypes::DataCollectionMethod collectionMethod = mscl::WirelessTypes::collectionMethod_transmitOnly;
mscl::WirelessTypes::DataMode dataMode = mscl::WirelessTypes::dataMode_raw;

static void supportedSampleRates(mscl::WirelessNode& node)
{
    const mscl::NodeFeatures& features = node.features();                   // Create NodeFeatures Object
    const mscl::ChannelGroups chGroups = node.features().channelGroups();   // Create ChannelGroups Object 
    const mscl::WirelessChannels channels = node.features().channels();     // Create WirelessChannels Object 

    std::cout << "\n-------------OpenDaq Signal Info--------------\n" << std::endl;
    std::cout << "Channel Count: " << channels.size() << std::endl << std::endl;

    for (uint8_t ch = 0; ch < channels.size(); ++ch)
    {
        std::cout << "Channel Group " << (int)ch + 1 << ": ";
        std::cout << chGroups[ch].name() << std::endl;

        std::cout << "  Supported Sample Rates:\n";
        for (const auto& rate : sampleRates)
        {
            if (features.supportsSampleRate(rate, samplingMode, collectionMethod, dataMode))
            {
                std::cout << sampleRateEnumName(rate) << "\n";
            }
        }

        std::cout << std::endl;
    }
}
