/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/

//Note: You can include this header file to include all of the headers for the public interface.

#pragma once

#include "Bin.h"
#include "BitMask.h"
#include "Exceptions.h"
#include "Histogram.h"
#include "LibVersion.h"
#include "TimeSpan.h"
#include "Timestamp.h"
#include "Types.h"
#include "Value.h"
#include "Version.h"
#include "Utils.h"


#include "Communication/Connection.h"
#include "Communication/ConnectionDebugData.h"
#include "Communication/Devices.h"

//uncomment for UPnP WSDA-Pro finder
//#include "Communication/WsdaFinder.h"

#include "MicroStrain/DataPoint.h"
#include "MicroStrain/LinearEquation.h"
#include "MicroStrain/Matrix.h"
#include "MicroStrain/SampleRate.h"
#include "MicroStrain/Vector.h"

#include "MicroStrain/Displacement/DisplacementModels.h"
#include "MicroStrain/Displacement/DisplacementNode.h"

#include "MicroStrain/RTK/RTKNode.h"

#include "MicroStrain/Inertial/EulerAngles.h"
#include "MicroStrain/Inertial/PositionOffset.h"
#include "MicroStrain/Inertial/ExposedInertialTypes.h"
#include "MicroStrain/Inertial/InertialNode.h"

#include "MicroStrain/MIP/MipModels.h"
#include "MicroStrain/MIP/MipChannel.h"
#include "MicroStrain/MIP/MipDataField.h"
#include "MicroStrain/MIP/MipDataPoint.h"
#include "MicroStrain/MIP/MipNodeFeatures.h"
#include "MicroStrain/MIP/MipTypes.h"

#include "MicroStrain/MIP/Packets/MipDataPacket.h"
#include "MicroStrain/MIP/Packets/MipPacket.h"

#include "MicroStrain/Wireless/ArmedDataloggingNetwork.h"
#include "MicroStrain/Wireless/BaseStation.h"
#include "MicroStrain/Wireless/BaseStationAnalogPair.h"
#include "MicroStrain/Wireless/BaseStationButton.h"
#include "MicroStrain/Wireless/BaseStationInfo.h"
#include "MicroStrain/Wireless/CalCoefficients.h"
#include "MicroStrain/Wireless/ChannelMask.h"
#include "MicroStrain/Wireless/DatalogDownloader.h"
#include "MicroStrain/Wireless/DataSweep.h"
#include "MicroStrain/Wireless/LoggedDataSweep.h"
#include "MicroStrain/Wireless/NodeDiscovery.h"
#include "MicroStrain/Wireless/RadioFeatures.h"
#include "MicroStrain/Wireless/StructuralHealth.h"
#include "MicroStrain/Wireless/SyncNetworkInfo.h"
#include "MicroStrain/Wireless/SyncSamplingNetwork.h"
#include "MicroStrain/Wireless/WirelessChannel.h"
#include "MicroStrain/Wireless/WirelessDataPoint.h"
#include "MicroStrain/Wireless/WirelessModels.h"
#include "MicroStrain/Wireless/WirelessNode.h"
#include "MicroStrain/Wireless/WirelessTypes.h"

#include "MicroStrain/Wireless/Commands/AutoBalanceResult.h"
#include "MicroStrain/Wireless/Commands/AutoCalInfo.h"
#include "MicroStrain/Wireless/Commands/AutoCalResult.h"
#include "MicroStrain/Wireless/Commands/BeaconStatus.h"
#include "MicroStrain/Wireless/Commands/PingResponse.h"
#include "MicroStrain/Wireless/Commands/SetToIdleStatus.h"

#include "MicroStrain/Wireless/Configuration/ActivitySense.h"
#include "MicroStrain/Wireless/Configuration/BaseStationConfig.h"
#include "MicroStrain/Wireless/Configuration/BaseStationEepromMap.h"
#include "MicroStrain/Wireless/Configuration/ConfigIssue.h"
#include "MicroStrain/Wireless/Configuration/EventTriggerOptions.h"
#include "MicroStrain/Wireless/Configuration/FatigueOptions.h"
#include "MicroStrain/Wireless/Configuration/HistogramOptions.h"
#include "MicroStrain/Wireless/Configuration/InputRange.h"
#include "MicroStrain/Wireless/Configuration/NodeEepromMap.h"
#include "MicroStrain/Wireless/Configuration/TempSensorOptions.h"
#include "MicroStrain/Wireless/Configuration/WirelessNodeConfig.h"

#include "MicroStrain/Wireless/Features/BaseStationFeatures.h"
#include "MicroStrain/Wireless/Features/ChannelGroup.h"
#include "MicroStrain/Wireless/Features/NodeInfo.h"
#include "MicroStrain/Wireless/Features/NodeFeatures.h"