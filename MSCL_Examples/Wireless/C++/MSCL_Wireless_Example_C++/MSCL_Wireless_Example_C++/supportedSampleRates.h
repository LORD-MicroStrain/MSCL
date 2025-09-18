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

mscl::WirelessTypes::SamplingMode setSampleMode(unsigned char choice) 
{
    switch (choice)                 // Function to set Sampling mode based on user input
    {
        case '1':  return mscl::WirelessTypes::samplingMode_sync; break; 
        case '2':  return mscl::WirelessTypes::samplingMode_syncBurst; break; 
        case '3':  return mscl::WirelessTypes::samplingMode_syncEvent; break; 
        case '4':  return mscl::WirelessTypes::samplingMode_nonSync; break; 
        case '5':  return mscl::WirelessTypes::samplingMode_nonSyncEvent; break; 
        case '6':  return mscl::WirelessTypes::samplingMode_armedDatalog; break; 

        default: return mscl::WirelessTypes::samplingMode_sync;  // if user inputs an invalid number default to sync
    }
}

mscl::WirelessTypes::DataCollectionMethod setDataCollectionMethod(unsigned char choice) 
{
    switch (choice)                 // Function to set data collection method based on user input
    {
        case '1':  return mscl::WirelessTypes::collectionMethod_logAndTransmit; break;
        case '2':  return mscl::WirelessTypes::collectionMethod_logOnly; break;
        case '3':  return mscl::WirelessTypes::collectionMethod_transmitOnly; break;

        default: return mscl::WirelessTypes::DataCollectionMethod::collectionMethod_logAndTransmit;  // if user inputs an invalid number default to log and transmit
    }
}

mscl::WirelessTypes::DataMode setDataMode(unsigned char choice) 
{
    switch (choice)                 // Function to set data mode based on user input
    {
        case '1':  return mscl::WirelessTypes::dataMode_derived; break; 
        case '2':  return mscl::WirelessTypes::dataMode_none; break; 
        case '3':  return mscl::WirelessTypes::dataMode_raw; break; 
        case '4':  return mscl::WirelessTypes::dataMode_raw_derived; break; 

        default: return mscl::WirelessTypes::dataMode_derived;  // if user inputs an invalid number default to data mode derived
    }
}

static void supportedSampleRates(mscl::WirelessNode& node)
{
    unsigned char sampleModeChoice;
    unsigned char dataCollectionMethodChoice;
    unsigned char dataModeChoice;

    mscl::WirelessTypes::SamplingMode samplingMode; 
    mscl::WirelessTypes::DataCollectionMethod collectionMethod; 
    mscl::WirelessTypes::DataMode dataMode; 

    // Input for Sample Mode Options
    std::cout << "Sampling Mode Options: " << std::endl;
    std::cout << "(1) Synchronized" << std::endl;
    std::cout << "(2) Sync Burst" << std::endl;
    std::cout << "(3) Sync Event" << std::endl;
    std::cout << "(4) Non Synchronized" << std::endl;
    std::cout << "(5) Non Synchronized Event" << std::endl;
    std::cout << "(6) Armed Data Log" << std::endl;
    std::cout << "Choice: ";
    std::cin >> sampleModeChoice;
    samplingMode = setSampleMode(sampleModeChoice); 

    // Input for Data Collection Options
    std::cout << "Sampling Mode Options: " << std::endl;
    std::cout << "(1) Log and Transmit" << std::endl;
    std::cout << "(2) Log Only" << std::endl;
    std::cout << "(3) Transmit Only" << std::endl;
    std::cout << "Choice: ";
    std::cin >> dataCollectionMethodChoice;
    collectionMethod = setDataCollectionMethod((int)dataCollectionMethodChoice); 

    // Input for Data Mode Options
    std::cout << "Sampling Mode Options: " << std::endl;
    std::cout << "(1) Derived" << std::endl;
    std::cout << "(2) None" << std::endl;
    std::cout << "(3) Raw" << std::endl;
    std::cout << "(4) Raw Derived" << std::endl;
    std::cout << "Choice: ";
    std::cin >> dataModeChoice;
    dataMode = setDataMode((int)dataModeChoice); 

    // In order to run the rest of this example, we need to read the configuration from the node.
    // To read the configuration from the node, it must first be set to idle, or it will not respond
    node.setToIdle(); // can only read node information when nodes idled 

    // Read the node configuration into a NodeFeatures object so we can look up things like channel groups, channels etc
    const mscl::NodeFeatures& features = node.features();                   // Create NodeFeatures Object
    const mscl::ChannelGroups chGroups = node.features().channelGroups();   // Create ChannelGroups Object 
    const mscl::WirelessChannels channels = node.features().channels();     // Create WirelessChannels Object 

    std::cout << "\n-------------Supported Sample Rates for OpenDaq Channel--------------\n" << std::endl;
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
