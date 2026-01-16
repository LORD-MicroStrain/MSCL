%include "MSCL_Exceptions.i" //our MSCL Exceptions interface file

%include "stdint.i"         // SWIG file needed for standard fixed-width types
%include "std_string.i"     // SWIG file needed for std::string
%include "std_vector.i"     // SWIG file needed for std::vector
%include "std_map.i"        // SWIG file needed for std::map
%include "std_pair.i"       // SWIG file needed for std::pair
%include "std_shared_ptr.i" // SWIG file needed for std::shared_ptr
%include "std_array.i"      // SWIG file needed for std::array

%define DISABLE_WARNING_BOOST_START %enddef
%define DISABLE_WARNING_BOOST_END %enddef

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
#include "mscl/stdafx.h"
#include "mscl/Exceptions.h"
#include "mscl/Bin.h"
#include "mscl/BitMask.h"
#include "mscl/Histogram.h"
#include "mscl/LibVersion.h"
#include "mscl/Timestamp.h"
#include "mscl/TimeSpan.h"
#include "mscl/Types.h"
#include "mscl/Version.h"
#include "mscl/Value.h"
#include "mscl/Utils.h"
#include "mscl/Communication/Devices.h"
#include "mscl/Communication/ConnectionDebugData.h"
#include "mscl/Communication/Connection.h"
#ifdef _WIN32
#include "mscl/Communication/WsdaFinder.h"
#endif // _WIN32
#include "mscl/MicroStrain/SampleRate.h"
#include "mscl/MicroStrain/DataPoint.h"
#include "mscl/MicroStrain/Matrix.h"
#include "mscl/MicroStrain/Vector.h"
#include "mscl/MicroStrain/Bitfield.h"
#include "mscl/MicroStrain/Wireless/ChannelMask.h"
#include "mscl/MicroStrain/Wireless/ArmedDataloggingNetwork.h"
#include "mscl/MicroStrain/Wireless/Configuration/BaseStationConfig.h"
#include "mscl/MicroStrain/Wireless/BaseStationAnalogPair.h"
#include "mscl/MicroStrain/Wireless/BaseStationButton.h"
#include "mscl/MicroStrain/Wireless/BaseStationInfo.h"
#include "mscl/MicroStrain/Wireless/Commands/SetToIdleStatus.h"
#include "mscl/MicroStrain/Wireless/BaseStation.h"
#include "mscl/MicroStrain/Wireless/Configuration/BaseStationEepromMap.h"
#include "mscl/MicroStrain/Wireless/Configuration/ConfigIssue.h"
#include "mscl/MicroStrain/Wireless/Configuration/ActivitySense.h"
#include "mscl/MicroStrain/Wireless/Configuration/FatigueOptions.h"
#include "mscl/MicroStrain/Wireless/Configuration/HistogramOptions.h"
#include "mscl/MicroStrain/Wireless/Configuration/InputRange.h"
#include "mscl/MicroStrain/Wireless/Configuration/EventTriggerOptions.h"
#include "mscl/MicroStrain/Wireless/Configuration/TempSensorOptions.h"
#include "mscl/MicroStrain/Wireless/DataSweep.h"
#include "mscl/MicroStrain/LinearEquation.h"
#include "mscl/MicroStrain/Wireless/WirelessChannel.h"
#include "mscl/MicroStrain/Wireless/CalCoefficients.h"
#include "mscl/MicroStrain/Wireless/DatalogDownloader.h"
#include "mscl/MicroStrain/Wireless/LoggedDataSweep.h"
#include "mscl/MicroStrain/Wireless/NodeDiscovery.h"
#include "mscl/MicroStrain/Wireless/Configuration/NodeEepromMap.h"
#include "mscl/MicroStrain/Wireless/RadioFeatures.h"
#include "mscl/MicroStrain/Wireless/Configuration/WirelessNodeConfig.h"
#include "mscl/MicroStrain/Wireless/WirelessTypes.h"
#include "mscl/MicroStrain/Wireless/WirelessModels.h"
#include "mscl/MicroStrain/Wireless/WirelessNode.h"
#include "mscl/MicroStrain/Wireless/WirelessDataPoint.h"
#include "mscl/MicroStrain/Wireless/SyncNetworkInfo.h"
#include "mscl/MicroStrain/Wireless/SyncSamplingNetwork.h"
#include "mscl/MicroStrain/Wireless/StructuralHealth.h"
#include "mscl/MicroStrain/Wireless/Commands/AutoBalanceResult.h"
#include "mscl/MicroStrain/Wireless/Commands/AutoCalInfo.h"
#include "mscl/MicroStrain/Wireless/Commands/AutoCalResult.h"
#include "mscl/MicroStrain/Wireless/Commands/BeaconStatus.h"
#include "mscl/MicroStrain/Wireless/Commands/PingResponse.h"
#include "mscl/MicroStrain/Wireless/Features/ChannelGroup.h"
#include "mscl/MicroStrain/Wireless/Features/NodeFeatures.h"
#include "mscl/MicroStrain/Wireless/Features/NodeInfo.h"
#include "mscl/MicroStrain/Wireless/Features/BaseStationFeatures.h"
#include "mscl/MicroStrain/Inertial/EulerAngles.h"
#include "mscl/MicroStrain/Inertial/PositionVelocity.h"
#include "mscl/MicroStrain/MIP/MipModels.h"
#include "mscl/MicroStrain/Displacement/DisplacementModels.h"
#include "mscl/MicroStrain/MIP/MipTypes.h"
#include "mscl/MicroStrain/Inertial/ExposedInertialTypes.h"
#include "mscl/MicroStrain/MIP/MipChannel.h"
#include "mscl/MicroStrain/MIP/MipDataField.h"
#include "mscl/MicroStrain/MIP/Packets/MipDataPacket.h"
#include "mscl/Communication/RawBytePacket.h"
#include "mscl/MicroStrain/MIP/MipDataPoint.h"
#include "mscl/MicroStrain/MIP/MipBuiltInTest.h"
#include "mscl/MicroStrain/MIP/Packets/MipSharedDataFields.h"
#include "mscl/MicroStrain/MIP/MipNodeFeatures.h"
#include "mscl/MicroStrain/MIP/MipNode.h"
#include "mscl/MicroStrain/Inertial/InertialNode.h"
#include "mscl/MicroStrain/Displacement/DisplacementNode.h"
#include "mscl/MicroStrain/RTK/RTKNode.h"
#include "mscl/MicroStrain/MIP/Packets/MipPacket.h"
%}

// Need to tell SWIG that the following classes are not abstract (thinks they are by default and doesn't generate constructors)
//%feature("notabstract") SamplingConfig;

//include the files that you want to have built into language-specific code here (note the %)
//Note: these files must be defined in a certain order. Ex. If FileA needs to include FileB, FileB must be "%include"-ed before FileA
//DO NOT CHANGE THE ORDER OF THESE!!!
%include "mscl/Types.h"
%include "mscl/BitMask.h"
%include "mscl/MicroStrain/Wireless/ChannelMask.h"
%include "mscl/Value.h"
%include "mscl/Bin.h"
%include "mscl/Histogram.h"
%include "mscl/Timestamp.h"
%include "mscl/TimeSpan.h"
%include "mscl/Version.h"
%include "mscl/LibVersion.h"
%include "mscl/Utils.h"
%include "mscl/Communication/Devices.h"
%include "mscl/Communication/ConnectionDebugData.h"
%include "mscl/Communication/Connection.h"
#ifdef _WIN32
%include "mscl/Communication/WsdaFinder.h"
#endif // _WIN32
%include "mscl/MicroStrain/Wireless/WirelessTypes.h"
%include "mscl/MicroStrain/SampleRate.h"
%include "mscl/MicroStrain/Matrix.h"
%include "mscl/MicroStrain/Vector.h"
%include "mscl/MicroStrain/Bitfield.h"
%include "mscl/MicroStrain/Wireless/StructuralHealth.h"
%include "mscl/MicroStrain/DataPoint.h"
%include "mscl/MicroStrain/Wireless/Configuration/ConfigIssue.h"
%include "mscl/MicroStrain/Wireless/Configuration/ActivitySense.h"
%include "mscl/MicroStrain/Wireless/Configuration/EventTriggerOptions.h"
%include "mscl/MicroStrain/Wireless/Configuration/FatigueOptions.h"
%include "mscl/MicroStrain/Wireless/Configuration/HistogramOptions.h"
%include "mscl/MicroStrain/Wireless/Configuration/InputRange.h"
%include "mscl/MicroStrain/Wireless/Configuration/TempSensorOptions.h"
%include "mscl/MicroStrain/Wireless/WirelessModels.h"
%include "mscl/MicroStrain/Wireless/NodeDiscovery.h"
%include "mscl/MicroStrain/LinearEquation.h"
%include "mscl/MicroStrain/Wireless/WirelessChannel.h"
%include "mscl/MicroStrain/Wireless/CalCoefficients.h"
%include "mscl/MicroStrain/Wireless/Features/ChannelGroup.h"
%include "mscl/MicroStrain/Wireless/WirelessDataPoint.h"
%include "mscl/MicroStrain/Wireless/DataSweep.h"
%include "mscl/MicroStrain/Wireless/BaseStationAnalogPair.h"
%include "mscl/MicroStrain/Wireless/BaseStationButton.h"
%include "mscl/MicroStrain/Wireless/Configuration/BaseStationConfig.h"
%include "mscl/MicroStrain/Wireless/Commands/BeaconStatus.h"
%include "mscl/MicroStrain/Wireless/BaseStationInfo.h"
%include "mscl/MicroStrain/Wireless/Commands/SetToIdleStatus.h"
%include "mscl/MicroStrain/Wireless/BaseStation.h"
%include "mscl/MicroStrain/Wireless/LoggedDataSweep.h"
%include "mscl/MicroStrain/Wireless/RadioFeatures.h"
%include "mscl/MicroStrain/Wireless/Configuration/WirelessNodeConfig.h"
%include "mscl/MicroStrain/Wireless/Commands/AutoBalanceResult.h"
%include "mscl/MicroStrain/Wireless/Commands/AutoCalInfo.h"
%include "mscl/MicroStrain/Wireless/Commands/AutoCalResult.h"
%include "mscl/MicroStrain/Wireless/Commands/PingResponse.h"
%include "mscl/MicroStrain/Wireless/Features/NodeInfo.h"
%include "mscl/MicroStrain/Wireless/WirelessNode.h"
%include "mscl/MicroStrain/Wireless/DatalogDownloader.h"
%include "mscl/MicroStrain/Wireless/ArmedDataloggingNetwork.h"
%include "mscl/MicroStrain/Wireless/SyncNetworkInfo.h"
%include "mscl/MicroStrain/Wireless/SyncSamplingNetwork.h"
%include "mscl/MicroStrain/Wireless/Features/NodeFeatures.h"
%include "mscl/MicroStrain/Wireless/Features/BaseStationFeatures.h"
%include "mscl/MicroStrain/Inertial/EulerAngles.h"
%include "mscl/MicroStrain/Inertial/PositionVelocity.h"
%include "mscl/MicroStrain/MIP/MipModels.h"
%include "mscl/MicroStrain/Displacement/DisplacementModels.h"
%include "mscl/MicroStrain/MIP/MipTypes.h"
%include "mscl/MicroStrain/Inertial/ExposedInertialTypes.h"
%include "mscl/MicroStrain/MIP/MipChannel.h"
%include "mscl/MicroStrain/MIP/MipDataField.h"
%include "mscl/MicroStrain/MIP/Packets/MipPacket.h"
%include "mscl/MicroStrain/MIP/MipDataPoint.h"
%include "mscl/MicroStrain/MIP/MipBuiltInTest.h"
%include "mscl/MicroStrain/MIP/Packets/MipSharedDataFields.h"
%include "mscl/MicroStrain/MIP/Packets/MipDataPacket.h"
%include "mscl/Communication/RawBytePacket.h"
%include "mscl/MicroStrain/MIP/MipNodeFeatures.h"
%include "mscl/MicroStrain/MIP/MipNode.h"
%include "mscl/MicroStrain/Inertial/InertialNode.h"
%include "mscl/MicroStrain/Displacement/DisplacementNode.h"
%include "mscl/MicroStrain/RTK/RTKNode.h"

namespace std
{
    %template(ChannelData)                      vector<mscl::WirelessDataPoint>;
    %template(MipDataPoints)                    vector<mscl::MipDataPoint>;
    %template(Bytes)                            vector<unsigned char>;
    %template(BytesCollection)                  vector<vector<unsigned char>>;
    %template(DeviceList)                       map<string, mscl::DeviceInfo>;
    %template(NodeDiscoveries)                  vector<mscl::NodeDiscovery>;
    %template(DataSweeps)                       vector<mscl::DataSweep>;
    %template(LoggedDataSweeps)                 vector<mscl::LoggedDataSweep>;
    %template(MipDataPackets)                   vector<mscl::MipDataPacket>;
    %template(RawBytePackets)                   vector<mscl::RawBytePacket>;
    %template(MipChannels)                      vector<mscl::MipChannel>;
    %template(DataCollectionMethods)            vector<mscl::WirelessTypes::DataCollectionMethod>;
    %template(DataFormats)                      vector<mscl::WirelessTypes::DataFormat>;
    %template(WirelessSampleRates)              vector<mscl::WirelessTypes::WirelessSampleRate>;
    %template(SamplingModes)                    vector<mscl::WirelessTypes::SamplingMode>;
    %template(DefaultModes)                     vector<mscl::WirelessTypes::DefaultMode>;
    %template(TransmitPowers)                   vector<mscl::WirelessTypes::TransmitPower>;
    %template(ChannelGroupSettings)             vector<mscl::WirelessTypes::ChannelGroupSetting>;
    %template(FatigueModes)                     vector<mscl::WirelessTypes::FatigueMode>;
    %template(Filters)                          vector<mscl::WirelessTypes::Filter>;
    %template(HighPassFilters)                  vector<mscl::WirelessTypes::HighPassFilter>;
    %template(StorageLimitModes)                vector<mscl::WirelessTypes::StorageLimitMode>;
    %template(InputRanges)                      vector<mscl::InputRangeEntry>;
    %template(DataModes)                        vector<mscl::WirelessTypes::DataMode>;
    %template(CommProtocols)                    vector<mscl::WirelessTypes::CommProtocol>;
    %template(Voltages)                         vector<mscl::WirelessTypes::Voltage>;
    %template(SensorOutputModes)                vector<mscl::WirelessTypes::SensorOutputMode>;
    %template(CfcFilters)                       vector<mscl::WirelessTypes::ChannelFrequencyClass>;
    %template(TransducerTypes)                  vector<mscl::WirelessTypes::TransducerType>;
    %template(EepromMap)                        map<uint16_t, uint16_t>;
    %template(DerivedChannelMasks)              map<enum mscl::WirelessTypes::DerivedCategory, mscl::ChannelMask>;
    %template(DeviceStatusMap)                  map<enum mscl::DeviceStatusValues, std::string>;
    %template(DeviceStatusValueMap)             map<enum mscl::DeviceStatusValues, mscl::Value>;
    %template(SampleRates)                      vector<mscl::SampleRate>;
    %template(ConfigIssues)                     vector<mscl::ConfigIssue>;
    %template(MipChannelFields)                 vector<enum mscl::MipTypes::ChannelField>;
    %template(MipCommands)                      vector<mscl::MipTypes::Command>;
    %template(MipDataClasses)                   vector<enum mscl::MipTypes::DataClass>;
    %template(MipChannelIdentifiers)            vector<mscl::MipChannelIdentifier>;
    %template(MipCommandSet)                    vector<mscl::MipCommandBytes>;
    %template(MipFieldValues)                   vector<mscl::Value>;
    %template(MipCommandParamPair)              pair<mscl::MipTypes::Command, vector<mscl::Value>>;
    %template(MipCommandParameters)             vector<pair<mscl::MipTypes::Command, vector<mscl::Value>>>;
    %template(ChannelIndex)                     pair<enum mscl::MipTypes::ChannelQualifier, uint8_t>;
    %template(ChannelIndices)                   vector<pair<enum mscl::MipTypes::ChannelQualifier, uint8_t>>;
    %template(ChannelFieldQualifiers)           map<enum mscl::MipTypes::ChannelField, vector<pair<enum mscl::MipTypes::ChannelQualifier, uint8_t>>>;
    %template(GnssReceivers)                    vector<mscl::GnssReceiverInfo>;
    %template(SensorRanges)                     vector<mscl::SensorRange>;
    %template(SensorRangeOptions)               map<enum mscl::SensorRange::Type, vector<mscl::SensorRange>>;
    %template(CommPortInfo)                     vector<mscl::DeviceCommPort>;
    %template(EventTriggerStatus)               vector<mscl::EventTriggerInfo>;
    %template(EventActionStatus)                vector<mscl::EventActionInfo>;
    %template(ChannelGroups)                    vector<mscl::ChannelGroup>;
    %template(WirelessChannels)                 vector<mscl::WirelessChannel>;
    %template(DamageAngles)                     map<uint8_t, float>;
    %template(SnCurveSegments)                  map<uint8_t, mscl::SnCurveSegment>;
    %template(RfSweep)                          map<uint32_t, int16_t>;
    %template(Triggers)                         map<uint8_t, mscl::Trigger>;
    %template(ChannelCalMap)                    map<enum mscl::WirelessChannel::ChannelId, mscl::CalCoefficients>;
    %template(WirelessPollData)                 map<enum mscl::WirelessChannel::ChannelId, float>;
    %template(ConnectionDebugDataVec)           vector<mscl::ConnectionDebugData>;
    %template(SatellitePRNs)                    vector<uint16_t>;
    %template(Constellations)                   vector<mscl::Constellation>;
    %template(HeadingUpdateOptionsList)         vector<mscl::HeadingUpdateOptions>;
    %template(AdaptiveMeasurementModes)         vector<mscl::InertialTypes::AdaptiveMeasurementMode>;
    %template(GeometricVectors)                 vector<mscl::GeometricVector>;
    %template(Matrix_3x3s)                      vector<mscl::Matrix_3x3>;
    %template(StatusSelectors)                  vector<mscl::DeviceStatusData::StatusSelector>;
    %template(VehicleModeTypes)                 vector<mscl::InertialTypes::VehicleModeType>;
    %template(AdaptiveFilterLevels)             vector<mscl::InertialTypes::AutoAdaptiveFilteringLevel>;
    %template(LowPassFilterConfig)              vector<mscl::LowPassFilterData>;
    %template(AidingMeasurementSourceOptions)   vector<mscl::InertialTypes::AidingMeasurementSource>;
    %template(PpsSourceOptions)                 vector<mscl::InertialTypes::PpsSource>;
    %template(GeographicSources)                vector<mscl::InertialTypes::GeographicSourceOption>;
    %template(GnssSources)                      vector<mscl::InertialTypes::GNSS_Source>;
    %template(GnssSignalConfigOptions)          map<mscl::MipChannelIdentifier::GnssConstellationIds, std::vector<uint8_t>>;
    %template(NmeaMessageFormats)               vector<mscl::NmeaMessageFormat>;
    %template(GpioPinModeOptions)               vector<mscl::GpioConfiguration::PinModes>;
    %template(GpioBehaviorModes)                map<uint8_t, vector<mscl::GpioConfiguration::PinModes>>;
    %template(GpioFeatureBehaviors)             map<enum mscl::GpioConfiguration::Feature, map<uint8_t, vector<mscl::GpioConfiguration::PinModes>>>;
    %template(GpioPinOptions)                   map<uint8_t, map<enum mscl::GpioConfiguration::Feature, map<uint8_t, vector<mscl::GpioConfiguration::PinModes>>>>;
    %template(EventInputTriggers)               array<uint8_t, mscl::EventTriggerCombinationParameter::MAX_INPUT_TRIGGERS>;
    %template(EventTypes)                       vector<mscl::EventTypeInfo>;
    %template(MeasurementReferenceFrames)       map<uint8_t, mscl::MeasurementReferenceFrame>;


#ifdef _WIN32
    %template(WsdaMap)                  map<string, mscl::WsdaInfo>;
#endif // _WIN32

    %ignore vector<mscl::Bin>::vector(size_type);   //no default constructor
    %ignore vector<mscl::Bin>::resize;              //no default constructor
    %template(Bins) vector<mscl::Bin>;
};

//C# should not create classes for the Exceptions classes.
//The exceptions need to be created by hand in the Exceptions.cs file
#ifndef SWIGCSHARP
%include "mscl/Exceptions.h"
#endif
