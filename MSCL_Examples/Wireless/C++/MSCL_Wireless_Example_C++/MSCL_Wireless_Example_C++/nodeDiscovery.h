#include <mscl/MicroStrain/Wireless/WirelessNode.h>
#include <mscl/MicroStrain/Wireless/Features/ChannelGroup.h>
#include <mscl/MicroStrain/Wireless/Features/NodeFeatures.h>
#include <iostream>
#include <chrono>
#include <thread>


// possible rates from the enum
std::vector<mscl::WirelessTypes::WirelessSampleRate> allRates = {
    mscl::WirelessTypes::WirelessSampleRate::sampleRate_1Hz,
    mscl::WirelessTypes::WirelessSampleRate::sampleRate_4Hz,
    mscl::WirelessTypes::WirelessSampleRate::sampleRate_8Hz,
    mscl::WirelessTypes::WirelessSampleRate::sampleRate_16Hz,
    mscl::WirelessTypes::WirelessSampleRate::sampleRate_32Hz,
    mscl::WirelessTypes::WirelessSampleRate::sampleRate_64Hz,
    mscl::WirelessTypes::WirelessSampleRate::sampleRate_128Hz,
    mscl::WirelessTypes::WirelessSampleRate::sampleRate_256Hz,
    mscl::WirelessTypes::WirelessSampleRate::sampleRate_512Hz,
    // etc, depending on what MSCL version/your node supports
};

static void nodeDiscovery(mscl::BaseStation& base_station)
{
    base_station.getNodeDiscoveries(); 

    printf("Discovering nodes...\n"); 
    printf("Press enter to continue...");
    getchar();

    mscl::NodeDiscoveries discoveries = base_station.getNodeDiscoveries(); 

    if (discoveries.size() == 0)
        std::cout << "No nodes discovered." << std::endl;
    else 
        for (const mscl::NodeDiscovery& nodes_discovered : discoveries)// Print discovered node information
        {
            //
            //  Channel Information 
            //

            std::cout << "\n-------------OpenDaq Channel Info--------------\n" << std::endl;
            std::cout << "Node Address: " << nodes_discovered.nodeAddress() << std::endl;
            std::cout << "Model: " << nodes_discovered.model() << std::endl;
            std::cout << "Serial: " << nodes_discovered.serialNumber() << std::endl;
            std::cout << "RSSI: " << nodes_discovered.baseRssi() << " dBm" << std::endl;
            std::cout << "Frequency: " << nodes_discovered.frequency() << std::endl;

            //
            //  Signal Informaion 
            //

            mscl::WirelessNode node(nodes_discovered.nodeAddress(), base_station);  // Create Node Object 
            const mscl::NodeFeatures& features = node.features();                   // Create NodeFeatures Object
            const mscl::ChannelGroups chGroups = node.features().channelGroups();   // Create ChannelGroups Object 
            const mscl::WirelessChannels channels = node.features().channels();     // Create WirelessChannels Object 

            std::cout << "\n-------------OpenDaq Signal Info--------------\n" << std::endl;
            std::cout << "Channel Count: " << channels.size() << std::endl << std::endl;
            
            for (uint8_t ch = 0; ch < channels.size(); ++ch)
            {
                std::cout << "Channel Group " << (int)ch+1 << ": ";
                std::cout << chGroups[ch].name() << std::endl;

                const mscl::WirelessTypes::ChannelGroupSettings groupSettings = chGroups[ch].settings();

                // Iterate over each setting for this group
                for (const mscl::WirelessTypes::ChannelGroupSetting& setting : groupSettings)
                {
                    // If the group contains the linear equation setting
                    if (setting == mscl::WirelessTypes::chSetting_linearEquation)
                    {
                        // We can now pass the channel mask (group.channels()) for this group to the node.getLinearEquation function.
                        // Note: once this channel mask is known for a specific node (+ fw version), it should never change
                        mscl::LinearEquation le = node.getLinearEquation(chGroups[ch].channels());
                        printf("Slope: %000.03f\n", le.slope());
                        printf("Offset: %000.03f\n\n", le.offset());
                    }
                }
            }
        }
}
