%include "MSCL_Exceptions.i" //our MSCL Exceptions interface file

%include "stdint.i"         // SWIG file needed for standard fixed-width types
%include "std_string.i"     // SWIG file needed for std::string
%include "std_vector.i"     // SWIG file needed for std::vector
%include "std_map.i"        // SWIG file needed for std::map
%include "std_shared_ptr.i" // SWIG file needed for std::shared_ptr
//%include "std_array.i"      // SWIG file needed for std::array

#ifdef SWIGCSHARP
//fix operator functions for C#
%rename(__eq__) mscl::Version::operator==;
%rename(__ne__) mscl::Version::operator!=;
%rename(__lt__) mscl::Version::operator<;
%rename(__le__) mscl::Version::operator<=;
%rename(__gt__) mscl::Version::operator>;
%rename(__ge__) mscl::Version::operator>=;
%typemap(cscode) mscl::Version 
%{ 
    public override bool Equals(object obj){Version other = obj as Version; return this.__eq__(other);}
    public override int GetHashCode(){ return (int)(majorPart() ^ minorPart() ^ patchPart()); }
    public static bool operator<(Version v1, Version v2){return v1.__lt__(v2);} 
    public static bool operator<=(Version v1, Version v2){return v1.__le__(v2);} 
    public static bool operator>(Version v1, Version v2){return v1.__gt__(v2);} 
    public static bool operator>=(Version v1, Version v2){return v1.__ge__(v2);} 
%}

%rename(__eq__) mscl::BitMask::operator==;
%rename(__ne__) mscl::BitMask::operator!=;
%rename(__lt__) mscl::BitMask::operator<;
%rename(__gt__) mscl::BitMask::operator>;
%typemap(cscode) mscl::BitMask
%{
    public override bool Equals(object obj) { BitMask other = obj as BitMask; return this.__eq__(other); }
    public override int GetHashCode() { return (int)(toMask()); }
    public static bool operator<(BitMask v1, BitMask v2) { return v1.__lt__(v2); }
    public static bool operator>(BitMask v1, BitMask v2) { return v1.__gt__(v2); }
%}

%rename(__eq__) mscl::ChannelMask::operator==;
%rename(__ne__) mscl::ChannelMask::operator!=;
%rename(__lt__) mscl::ChannelMask::operator<;
%rename(__gt__) mscl::ChannelMask::operator>;
%typemap(cscode) mscl::ChannelMask 
%{ 
    public override bool Equals(object obj){ChannelMask other = obj as ChannelMask; return this.__eq__(other);}
    public override int GetHashCode(){ return (int)(toMask()); } 
    public static bool operator<(ChannelMask v1, ChannelMask v2) { return v1.__lt__(v2); }
    public static bool operator>(ChannelMask v1, ChannelMask v2) { return v1.__gt__(v2); }
%}

//functions that take/return a reference need to tell C# how to wrap them
%typemap(cstype) float& "ref float"
%typemap(csin) float& %{ref $csinput%}
%typemap(imtype) float& "ref float"
%typemap(cstype) unsigned short& "ref ushort"
%typemap(csin) unsigned short& %{ref $csinput%}
%typemap(imtype) unsigned short& "ref ushort"

//change the "str()" functions to "ToString()" functions for C#
%rename("ToString") str;
%typemap(cstype) std::string str() "override string"
#endif

#ifdef SWIGPYTHON
//rename operator functions to Python specific operators
%rename(__eq__) Version::operator ==;
%rename(__ne__) Version::operator !=;
%rename(__lt__) Version::operator <;
%rename(__le__) Version::operator <=;
%rename(__gt__) Version::operator >;
%rename(__ge__) Version::operator >=;

//change the "str()" functions to "__str__" functions for Python
%rename(__str__) str;
#endif



%module mscl
%{
// Put headers and other declarations here
#include "../Exceptions.h"
#include "../Bin.h"
#include "../BitMask.h"
#include "../Histogram.h"
#include "../LibVersion.h"
#include "../Timestamp.h"
#include "../TimeSpan.h"
#include "../Types.h"
#include "../Version.h"
#include "../Value.h"
#include "../Utils.h"
#include "../Communication/Devices.h"
#include "../Communication/ConnectionDebugData.h"
#include "../Communication/Connection.h"
#ifndef UNIX_BUILD
#include "../Communication/WsdaFinder.h"
#endif
#include "../MicroStrain/SampleRate.h"
#include "../MicroStrain/DataPoint.h"
#include "../MicroStrain/Matrix.h"
#include "../MicroStrain/Vector.h"
#include "../MicroStrain/Wireless/ChannelMask.h"
#include "../MicroStrain/Wireless/ArmedDataloggingNetwork.h"
#include "../MicroStrain/Wireless/Configuration/BaseStationConfig.h"
#include "../MicroStrain/Wireless/BaseStationAnalogPair.h"
#include "../MicroStrain/Wireless/BaseStationButton.h"
#include "../MicroStrain/Wireless/BaseStationInfo.h"
#include "../MicroStrain/Wireless/BaseStation.h"
#include "../MicroStrain/Wireless/Configuration/BaseStationEepromMap.h"
#include "../MicroStrain/Wireless/Configuration/ConfigIssue.h"
#include "../MicroStrain/Wireless/Configuration/ActivitySense.h"
#include "../MicroStrain/Wireless/Configuration/FatigueOptions.h"
#include "../MicroStrain/Wireless/Configuration/HistogramOptions.h"
#include "../MicroStrain/Wireless/Configuration/InputRange.h"
#include "../MicroStrain/Wireless/Configuration/EventTriggerOptions.h"
#include "../MicroStrain/Wireless/Configuration/TempSensorOptions.h"
#include "../MicroStrain/Wireless/DataSweep.h"
#include "../MicroStrain/LinearEquation.h"
#include "../MicroStrain/Wireless/CalCoefficients.h"
#include "../MicroStrain/Wireless/DatalogDownloader.h"
#include "../MicroStrain/Wireless/LoggedDataSweep.h"
#include "../MicroStrain/Wireless/NodeDiscovery.h"
#include "../MicroStrain/Wireless/Configuration/NodeEepromMap.h"
#include "../MicroStrain/Wireless/RadioFeatures.h"
#include "../MicroStrain/Wireless/Configuration/WirelessNodeConfig.h"
#include "../MicroStrain/Wireless/WirelessTypes.h"
#include "../MicroStrain/Wireless/WirelessModels.h"
#include "../MicroStrain/Wireless/WirelessNode.h"
#include "../MicroStrain/Wireless/WirelessDataPoint.h"
#include "../MicroStrain/Wireless/WirelessChannel.h"
#include "../MicroStrain/Wireless/SyncNetworkInfo.h"
#include "../MicroStrain/Wireless/SyncSamplingNetwork.h"
#include "../MicroStrain/Wireless/StructuralHealth.h"
#include "../MicroStrain/Wireless/Commands/AutoBalanceResult.h"
#include "../MicroStrain/Wireless/Commands/AutoCalInfo.h"
#include "../MicroStrain/Wireless/Commands/AutoCalResult.h"
#include "../MicroStrain/Wireless/Commands/BeaconStatus.h"
#include "../MicroStrain/Wireless/Commands/PingResponse.h"
#include "../MicroStrain/Wireless/Commands/SetToIdleStatus.h"
#include "../MicroStrain/Wireless/Features/ChannelGroup.h"
#include "../MicroStrain/Wireless/Features/NodeFeatures.h"
#include "../MicroStrain/Wireless/Features/NodeInfo.h"
#include "../MicroStrain/Wireless/Features/BaseStationFeatures.h"
#include "../MicroStrain/Inertial/ExposedInertialTypes.h"
#include "../MicroStrain/Inertial/EulerAngles.h"
#include "../MicroStrain/Inertial/PositionOffset.h"
#include "../MicroStrain/Inertial/InertialModels.h"
#include "../MicroStrain/Displacement/DisplacementModels.h"
#include "../MicroStrain/MIP/MipTypes.h"
#include "../MicroStrain/MIP/MipChannel.h"
#include "../MicroStrain/MIP/MipDataField.h"
#include "../MicroStrain/MIP/Packets/MipDataPacket.h"
#include "../MicroStrain/MIP/MipDataPoint.h"
#include "../MicroStrain/MIP/MipNodeFeatures.h"
#include "../MicroStrain/Inertial/InertialNode.h"
#include "../MicroStrain/Displacement/DisplacementNode.h"
#include "../MicroStrain/MIP/Packets/MipPacket.h"
%}

// Need to tell SWIG that the following classes are not abstract (thinks they are by default and doesn't generate constructors)
//%feature("notabstract") SamplingConfig;

//include the files that you want to have built into language-specific code here (note the %)
//Note: these files must be defined in a certain order. Ex. If FileA needs to include FileB, FileB must be "%include"-ed before FileA
//DO NOT CHANGE THE ORDER OF THESE!!!
%include "../Types.h"
%include "../BitMask.h"
%include "../MicroStrain/Wireless/ChannelMask.h"
%include "../Value.h"
%include "../Bin.h"
%include "../Histogram.h"
%include "../Timestamp.h"
%include "../TimeSpan.h"
%include "../Version.h"
%include "../LibVersion.h"
%include "../Utils.h"
%include "../Communication/Devices.h"
%include "../Communication/ConnectionDebugData.h"
%include "../Communication/Connection.h"
#ifndef UNIX_BUILD
    %include "../Communication/WsdaFinder.h"
#endif
%include "../MicroStrain/Wireless/WirelessTypes.h"
%include "../MicroStrain/SampleRate.h"
%include "../MicroStrain/Matrix.h"
%include "../MicroStrain/Vector.h"
%include "../MicroStrain/Wireless/StructuralHealth.h"
%include "../MicroStrain/DataPoint.h"
%include "../MicroStrain/Wireless/Configuration/ConfigIssue.h"
%include "../MicroStrain/Wireless/Configuration/ActivitySense.h"
%include "../MicroStrain/Wireless/Configuration/EventTriggerOptions.h"
%include "../MicroStrain/Wireless/Configuration/FatigueOptions.h"
%include "../MicroStrain/Wireless/Configuration/HistogramOptions.h"
%include "../MicroStrain/Wireless/Configuration/InputRange.h"
%include "../MicroStrain/Wireless/Configuration/TempSensorOptions.h"
%include "../MicroStrain/Wireless/WirelessModels.h"
%include "../MicroStrain/Wireless/NodeDiscovery.h"
%include "../MicroStrain/LinearEquation.h"
%include "../MicroStrain/Wireless/CalCoefficients.h"
%include "../MicroStrain/Wireless/Features/ChannelGroup.h"
%include "../MicroStrain/Wireless/WirelessChannel.h"
%include "../MicroStrain/Wireless/WirelessDataPoint.h"
%include "../MicroStrain/Wireless/DataSweep.h"
%include "../MicroStrain/Wireless/BaseStationAnalogPair.h"
%include "../MicroStrain/Wireless/BaseStationButton.h"
%include "../MicroStrain/Wireless/Configuration/BaseStationConfig.h"
%include "../MicroStrain/Wireless/Commands/BeaconStatus.h"
%include "../MicroStrain/Wireless/BaseStationInfo.h"
%include "../MicroStrain/Wireless/BaseStation.h"
%include "../MicroStrain/Wireless/LoggedDataSweep.h"
%include "../MicroStrain/Wireless/RadioFeatures.h"
%include "../MicroStrain/Wireless/Configuration/WirelessNodeConfig.h"
%include "../MicroStrain/Wireless/Commands/AutoBalanceResult.h"
%include "../MicroStrain/Wireless/Commands/AutoCalInfo.h"
%include "../MicroStrain/Wireless/Commands/AutoCalResult.h"
%include "../MicroStrain/Wireless/Commands/PingResponse.h"
%include "../MicroStrain/Wireless/Commands/SetToIdleStatus.h"
%include "../MicroStrain/Wireless/Features/NodeInfo.h"
%include "../MicroStrain/Wireless/WirelessNode.h"
%include "../MicroStrain/Wireless/DatalogDownloader.h"
%include "../MicroStrain/Wireless/ArmedDataloggingNetwork.h"
%include "../MicroStrain/Wireless/SyncNetworkInfo.h"
%include "../MicroStrain/Wireless/SyncSamplingNetwork.h"
%include "../MicroStrain/Wireless/Features/NodeFeatures.h"
%include "../MicroStrain/Wireless/Features/BaseStationFeatures.h"
%include "../MicroStrain/Inertial/ExposedInertialTypes.h"
%include "../MicroStrain/Inertial/EulerAngles.h"
%include "../MicroStrain/Inertial/PositionOffset.h"
%include "../MicroStrain/Inertial/InertialModels.h"
%include "../MicroStrain/Displacement/DisplacementModels.h"
%include "../MicroStrain/MIP/MipTypes.h"
%include "../MicroStrain/MIP/MipChannel.h"
%include "../MicroStrain/MIP/MipDataField.h"
%include "../MicroStrain/MIP/Packets/MipPacket.h"
%include "../MicroStrain/MIP/MipDataPoint.h"
%include "../MicroStrain/MIP/Packets/MipDataPacket.h"
%include "../MicroStrain/MIP/MipNodeFeatures.h"
%include "../MicroStrain/Inertial/InertialNode.h"
%include "../MicroStrain/Displacement/DisplacementNode.h"

namespace std
{
    %template(ChannelData)              vector<mscl::WirelessDataPoint>;
    %template(MipDataPoints)            vector<mscl::MipDataPoint>;
    %template(Bytes)                    vector<unsigned char>;
    %template(BytesCollection)          vector<vector<unsigned char>>;
    %template(DeviceList)               map<string, mscl::DeviceInfo>;
    %template(NodeDiscoveries)          vector<mscl::NodeDiscovery>;
    %template(DataSweeps)               vector<mscl::DataSweep>;
    %template(LoggedDataSweeps)         vector<mscl::LoggedDataSweep>;
    %template(MipDataPackets)           vector<mscl::MipDataPacket>;
    %template(MipChannels)              vector<mscl::MipChannel>;
    %template(DataCollectionMethods)    vector<mscl::WirelessTypes::DataCollectionMethod>;
    %template(DataFormats)              vector<mscl::WirelessTypes::DataFormat>;
    %template(WirelessSampleRates)      vector<mscl::WirelessTypes::WirelessSampleRate>;
    %template(SamplingModes)            vector<mscl::WirelessTypes::SamplingMode>;
    %template(DefaultModes)             vector<mscl::WirelessTypes::DefaultMode>;
    %template(TransmitPowers)           vector<mscl::WirelessTypes::TransmitPower>;
    %template(ChannelGroupSettings)     vector<mscl::WirelessTypes::ChannelGroupSetting>;
    %template(FatigueModes)             vector<mscl::WirelessTypes::FatigueMode>;
    %template(Filters)                  vector<mscl::WirelessTypes::Filter>;
    %template(HighPassFilters)          vector<mscl::WirelessTypes::HighPassFilter>;
    %template(StorageLimitModes)        vector<mscl::WirelessTypes::StorageLimitMode>;
    %template(InputRanges)              vector<mscl::InputRangeEntry>;
    %template(DataModes)                vector<mscl::WirelessTypes::DataMode>;
    %template(CommProtocols)            vector<mscl::WirelessTypes::CommProtocol>;
    %template(Voltages)                 vector<mscl::WirelessTypes::Voltage>;
    %template(SensorOutputModes)        vector<mscl::WirelessTypes::SensorOutputMode>;
    %template(TransducerTypes)          vector<mscl::WirelessTypes::TransducerType>;
    %template(EepromMap)                map<uint16_t, uint16_t>;
    %template(DerivedChannelMasks)      map<mscl::WirelessTypes::DerivedCategory, mscl::ChannelMask>;
    %template(SampleRates)              vector<mscl::SampleRate>;
    %template(ConfigIssues)             vector<mscl::ConfigIssue>;
    %template(MipChannelFields)         vector<mscl::MipTypes::ChannelField>;
    %template(MipCommands)              vector<mscl::MipTypes::Command>;
    %template(MipCommandSet)            vector<mscl::MipCommandBytes>;
    %template(ChannelGroups)            vector<mscl::ChannelGroup>;
    %template(WirelessChannels)         vector<mscl::WirelessChannel>;
    %template(DamageAngles)             map<uint8_t, float>;
    %template(SnCurveSegments)          map<uint8_t, mscl::SnCurveSegment>;
    %template(RfSweep)                  map<uint32_t, int16_t>;
    %template(Triggers)                 map<uint8_t, mscl::Trigger>;
    %template(ChannelCalMap)            map<mscl::WirelessChannel::ChannelId, mscl::CalCoefficients>;
    %template(ConnectionDebugDataVec)   vector<mscl::ConnectionDebugData>;
    %template(SatellitePRNs)            vector<uint16_t>;
    %template(Constellations)           vector<mscl::Constellation>;
    %template(HeadingUpdateOptionsList) vector<mscl::HeadingUpdateOptions>;
    %template(AdaptiveMeasurementModes) vector<mscl::InertialTypes::AdaptiveMeasurementMode>;
    %template(GeometricVectors)         vector<mscl::GeometricVector>;
    %template(Matrix_3x3s)              vector<mscl::Matrix_3x3>;
    %template(VehicleModeTypes)         vector<mscl::InertialTypes::VehicleModeType>;
    %template(AdvancedLowPassFilterConfig)vector<mscl::AdvancedLowPassFilterData>;
    

#ifndef UNIX_BUILD
    %template(WsdaMap)                  map<string, mscl::WsdaInfo>;
#endif

    %ignore vector<mscl::Bin>::vector(size_type);   //no default constructor
    %ignore vector<mscl::Bin>::resize;              //no default constructor
    %template(Bins) vector<mscl::Bin>;
};

//C# should not create classes for the Exceptions classes. 
//The exceptions need to be created by hand in the Exceptions.cs file
#ifndef SWIGCSHARP
%include "../Exceptions.h"
#endif