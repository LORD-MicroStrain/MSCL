%include "MSCL_Exceptions.i" //our MSCL Exceptions interface file

%include "stdint.i"				// SWIG file needed for standard fixed-width types
%include "std_string.i"			// SWIG file needed for std::string
%include "std_vector.i"			// SWIG file needed for std::vector
%include "std_map.i"			// SWIG file needed for std::map
%include "std_shared_ptr.i"		// SWIG file needed for std::shared_ptr

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
#include "../Histogram.h"
#include "../LibVersion.h"
#include "../Timestamp.h"
#include "../TimeSpan.h"
#include "../Types.h"
#include "../Version.h"
#include "../Value.h"
#include "../Utils.h"
#include "../Communication/Devices.h"
#include "../Communication/Connection.h"
#include "../MicroStrain/SampleRate.h"
#include "../MicroStrain/DataPoint.h"
#include "../MicroStrain/Vector.h"
#include "../MicroStrain/Matrix.h"
#include "../MicroStrain/Wireless/ChannelMask.h"
#include "../MicroStrain/Wireless/ArmedDataloggingNetwork.h"
#include "../MicroStrain/Wireless/Configuration/BaseStationConfig.h"
#include "../MicroStrain/Wireless/BaseStationAnalogPair.h"
#include "../MicroStrain/Wireless/BaseStationButton.h"
#include "../MicroStrain/Wireless/BaseStation.h"
#include "../MicroStrain/Wireless/Configuration/BaseStationEepromMap.h"
#include "../MicroStrain/Wireless/Configuration/ConfigIssue.h"
#include "../MicroStrain/Wireless/Configuration/FatigueOptions.h"
#include "../MicroStrain/Wireless/Configuration/HistogramOptions.h"
#include "../MicroStrain/Wireless/DatalogDownloader.h"
#include "../MicroStrain/Wireless/DataSweep.h"
#include "../MicroStrain/Wireless/LinearEquation.h"
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
#include "../MicroStrain/Wireless/Commands/AutoCal.h"
#include "../MicroStrain/Wireless/Commands/BaseStation_BeaconStatus.h"
#include "../MicroStrain/Wireless/Commands/LongPing.h"
#include "../MicroStrain/Wireless/Commands/SetToIdleStatus.h"
#include "../MicroStrain/Wireless/Features/ChannelGroup.h"
#include "../MicroStrain/Wireless/Features/NodeFeatures.h"
#include "../MicroStrain/Wireless/Features/BaseStationFeatures.h"
#include "../MicroStrain/Inertial/InertialModels.h"
#include "../MicroStrain/Inertial/InertialTypes.h"
#include "../MicroStrain/Inertial/InertialChannel.h"
#include "../MicroStrain/Inertial/InertialDataField.h"
#include "../MicroStrain/Inertial/Packets/InertialDataPacket.h"
#include "../MicroStrain/Inertial/InertialDataPoint.h"
#include "../MicroStrain/Inertial/InertialNodeInfo.h"
#include "../MicroStrain/Inertial/InertialNode.h"
#include "../MicroStrain/Inertial/Packets/InertialPacket.h"
%}

// Need to tell SWIG that the following classes are not abstract (thinks they are by default and doesn't generate constructors)
//%feature("notabstract") SamplingConfig;

//include the files that you want to have built into language-specific code here (note the %)
//Note: these files must be defined in a certain order. Ex. If FileA needs to include FileB, FileB must be "%include"-ed before FileA
//DO NOT CHANGE THE ORDER OF THESE!!!
%include "../Types.h"
%include "../LibVersion.h"
%include "../Value.h"
%include "../Histogram.h"
%include "../Timestamp.h"
%include "../TimeSpan.h"
%include "../Version.h"
%include "../Utils.h"
%include "../Communication/Devices.h"
%include "../Communication/Connection.h"
%include "../MicroStrain/Wireless/WirelessTypes.h"
%include "../MicroStrain/SampleRate.h"
%include "../MicroStrain/Vector.h"
%include "../MicroStrain/Matrix.h"
%include "../MicroStrain/Wireless/StructuralHealth.h"
%include "../MicroStrain/DataPoint.h"
%include "../MicroStrain/Wireless/ChannelMask.h"
%include "../MicroStrain/Wireless/Configuration/ConfigIssue.h"
%include "../MicroStrain/Wireless/Configuration/FatigueOptions.h"
%include "../MicroStrain/Wireless/Configuration/HistogramOptions.h"
%include "../MicroStrain/Wireless/WirelessModels.h"
%include "../MicroStrain/Wireless/NodeDiscovery.h"
%include "../MicroStrain/Wireless/LinearEquation.h"
%include "../MicroStrain/Wireless/Features/ChannelGroup.h"
%include "../MicroStrain/Wireless/WirelessChannel.h"
%include "../MicroStrain/Wireless/WirelessDataPoint.h"
%include "../MicroStrain/Wireless/DataSweep.h"
%include "../MicroStrain/Wireless/BaseStationAnalogPair.h"
%include "../MicroStrain/Wireless/BaseStationButton.h"
%include "../MicroStrain/Wireless/Configuration/BaseStationConfig.h"
%include "../MicroStrain/Wireless/Commands/BaseStation_BeaconStatus.h"
%include "../MicroStrain/Wireless/BaseStation.h"
%include "../MicroStrain/Wireless/LoggedDataSweep.h"
%include "../MicroStrain/Wireless/RadioFeatures.h"
%include "../MicroStrain/Wireless/Configuration/WirelessNodeConfig.h"
%include "../MicroStrain/Wireless/Commands/AutoCal.h"
%include "../MicroStrain/Wireless/Commands/LongPing.h"
%include "../MicroStrain/Wireless/Commands/SetToIdleStatus.h"
%include "../MicroStrain/Wireless/WirelessNode.h"
%include "../MicroStrain/Wireless/DatalogDownloader.h"
%include "../MicroStrain/Wireless/ArmedDataloggingNetwork.h"
%include "../MicroStrain/Wireless/SyncNetworkInfo.h"
%include "../MicroStrain/Wireless/SyncSamplingNetwork.h"
%include "../MicroStrain/Wireless/Features/NodeFeatures.h"
%include "../MicroStrain/Wireless/Features/BaseStationFeatures.h"
%include "../MicroStrain/Inertial/InertialModels.h"
%include "../MicroStrain/Inertial/InertialTypes.h"
%include "../MicroStrain/Inertial/InertialChannel.h"
%include "../MicroStrain/Inertial/InertialDataField.h"
%include "../MicroStrain/Inertial/Packets/InertialPacket.h"
%include "../MicroStrain/Inertial/InertialDataPoint.h"
%include "../MicroStrain/Inertial/Packets/InertialDataPacket.h"
%include "../MicroStrain/Inertial/InertialNodeInfo.h"
%include "../MicroStrain/Inertial/InertialNode.h"

namespace std
{
	%template(ChannelData)				vector<mscl::WirelessDataPoint>;
	%template(InertialDataPoints)		vector<mscl::InertialDataPoint>;
	%template(Bytes)					vector<unsigned char>;
	%template(DeviceList)				map<string, mscl::DeviceInfo>;
	%template(NodeDiscoveries)			vector<mscl::NodeDiscovery>;
	%template(DataSweeps)				vector<mscl::DataSweep>;
	%template(LoggedDataSweeps)			vector <mscl::LoggedDataSweep>;
	%template(InertialDataPackets)		vector<mscl::InertialDataPacket>;
	%template(InertialChannels)			vector<mscl::InertialChannel>;
	%template(DataCollectionMethods)	vector<mscl::WirelessTypes::DataCollectionMethod>;
	%template(DataFormats)				vector<mscl::WirelessTypes::DataFormat>;
	%template(WirelessSampleRates)		vector<mscl::WirelessTypes::WirelessSampleRate>;
	%template(SamplingModes)			vector<mscl::WirelessTypes::SamplingMode>;
	%template(DefaultModes)				vector<mscl::WirelessTypes::DefaultMode>;
	%template(TransmitPowers)			vector<mscl::WirelessTypes::TransmitPower>;
	%template(ChannelGroupSettings)		vector<mscl::WirelessTypes::ChannelGroupSetting>;
	%template(SampleRates)				vector<mscl::SampleRate>;
	%template(ConfigIssues)				vector<mscl::ConfigIssue>;
	%template(ChannelFields)			vector<mscl::InertialTypes::ChannelField>;
	%template(ChannelMasks)				vector<mscl::ChannelMask>;
	%template(ChannelGroups)			vector<mscl::ChannelGroup>;
	%template(WirelessChannels)			vector<mscl::WirelessChannel>;
	%template(DamageAngles)				map<uint8_t, float>;
	%template(SnCurveSegments)			map<uint8_t, mscl::SnCurveSegment>;


	%ignore vector<mscl::Bin>::vector(size_type);				//no default constructor
	%ignore vector<mscl::Bin>::resize;							//no default constructor
	%template(Bins) vector<mscl::Bin>;
};

//C# should not create classes for the Exceptions classes. 
//The exceptions need to be created by hand in the Exceptions.cs file
#ifndef SWIGCSHARP
%include "../Exceptions.h"
#endif
