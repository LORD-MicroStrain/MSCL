from distutils.core import setup, Extension
import sys, os

if os.name == 'nt':
	extra_compile_args = [	'/EHsc', 
							'/MT',
							'/D', 'WIN32', '/D', 'NDEBUG', '/D', '_WINDOWS', '/D', '_USRDLL',
							'/D', '_WIN32_WINNT=0x0501', '/D', '_WINDLL',
							'/W3', '/WX', '/wd4290',
							'/I"source"'
							]
							
	extra_link_args = [ '/MANIFEST' ]
else:
	currentPath = os.path.abspath(os.path.dirname(sys.argv[0]))
	
	sourceDir = "-I" + currentPath + "/../../../source"
	msclDir = "-I" + currentPath + "/../../../../MSCL"
	
	extra_compile_args = [
							sourceDir,
							msclDir
							]
							
	extra_link_args = [ 
						'-s',
						'-lboost_system',
						'-lboost_thread',
						'-lboost_filesystem',
						'-lpthread',
						]
	

mscl_module = Extension('_mscl',
						 sources=[
									'source/mscl/Wrapper/MSCL_Main_Interface_wrap.cxx', 

                                    'source/mscl/Histogram.cpp',
									'source/mscl/LibVersion.cpp',
									'source/mscl/TimedCondition.cpp',
									'source/mscl/TimeSpan.cpp',
									'source/mscl/Timestamp.cpp',
									'source/mscl/Utils.cpp',
									'source/mscl/Value.cpp',
									'source/mscl/Version.cpp',
									'source/mscl/WMI_Helper.cpp',
									
									'source/mscl/Communication/Connection.cpp',
									'source/mscl/Communication/Devices.cpp',
									'source/mscl/Communication/SerialConnection.cpp',
                                    'source/mscl/Communication/TcpIpConnection.cpp',

									'source/mscl/MicroStrain/ByteStream.cpp',
									'source/mscl/MicroStrain/ChecksumBuilder.cpp',
									'source/mscl/MicroStrain/DataBuffer.cpp',
									'source/mscl/MicroStrain/DataPoint.cpp',
									'source/mscl/MicroStrain/Matrix.cpp',
									'source/mscl/MicroStrain/ResponseCollector.cpp',
									'source/mscl/MicroStrain/ResponsePattern.cpp',
									'source/mscl/MicroStrain/SampleRate.cpp',
									'source/mscl/MicroStrain/SampleUtils.cpp',
									'source/mscl/MicroStrain/Vector.cpp',

									'source/mscl/MicroStrain/Wireless/ActiveChannels.cpp',
									'source/mscl/MicroStrain/Wireless/BaseStation.cpp',
									'source/mscl/MicroStrain/Wireless/BaseStation_Impl.cpp',
                                    'source/mscl/MicroStrain/Wireless/BaseStationEeprom.cpp',
									'source/mscl/MicroStrain/Wireless/BaseStationEepromMap.cpp',
                                    'source/mscl/MicroStrain/Wireless/ConfigIssue.cpp',
									'source/mscl/MicroStrain/Wireless/DataSweep.cpp',
									'source/mscl/MicroStrain/Wireless/DeliveryStopFlags.cpp',
                                    'source/mscl/MicroStrain/Wireless/Eeprom.cpp',
									'source/mscl/MicroStrain/Wireless/EepromLocation.cpp',
									'source/mscl/MicroStrain/Wireless/FirmwareFeatures.cpp',
									'source/mscl/MicroStrain/Wireless/HardwareGain.cpp',
									'source/mscl/MicroStrain/Wireless/NodeDiscovery.cpp',
                                    'source/mscl/MicroStrain/Wireless/NodeEeprom.cpp',
									'source/mscl/MicroStrain/Wireless/NodeEepromHelper.cpp',
									'source/mscl/MicroStrain/Wireless/NodeEepromMap.cpp',
									'source/mscl/MicroStrain/Wireless/NodeInfo.cpp',
									'source/mscl/MicroStrain/Wireless/RadioFeatures.cpp',
									'source/mscl/MicroStrain/Wireless/SamplingConfig.cpp',
                                    'source/mscl/MicroStrain/Wireless/StructuralHealth.cpp',
									'source/mscl/MicroStrain/Wireless/SyncNetworkInfo.cpp',
									'source/mscl/MicroStrain/Wireless/SyncNodeConfig.cpp',
									'source/mscl/MicroStrain/Wireless/SyncSamplingFormulas.cpp',
									'source/mscl/MicroStrain/Wireless/SyncSamplingNetwork.cpp',
									'source/mscl/MicroStrain/Wireless/WirelessChannel.cpp',
									'source/mscl/MicroStrain/Wireless/WirelessDataPoint.cpp',
									'source/mscl/MicroStrain/Wireless/WirelessModels.cpp',
									'source/mscl/MicroStrain/Wireless/WirelessNode.cpp',
									'source/mscl/MicroStrain/Wireless/WirelessNode_Impl.cpp',
									'source/mscl/MicroStrain/Wireless/WirelessParser.cpp',
									
									'source/mscl/MicroStrain/Wireless/Commands/BaseStation_Ping.cpp',
									'source/mscl/MicroStrain/Wireless/Commands/BaseStation_ReadEeprom.cpp',
									'source/mscl/MicroStrain/Wireless/Commands/BaseStation_SetBeacon.cpp',
									'source/mscl/MicroStrain/Wireless/Commands/BaseStation_WriteEeprom.cpp',
									'source/mscl/MicroStrain/Wireless/Commands/LongPing.cpp',
									'source/mscl/MicroStrain/Wireless/Commands/PageDownload.cpp',
									'source/mscl/MicroStrain/Wireless/Commands/ReadEeprom.cpp',
									'source/mscl/MicroStrain/Wireless/Commands/ShortPing.cpp',
                                    'source/mscl/MicroStrain/Wireless/Commands/Sleep.cpp',
                                    'source/mscl/MicroStrain/Wireless/Commands/StartNonSyncSampling.cpp',
									'source/mscl/MicroStrain/Wireless/Commands/StartSyncSampling.cpp',
									'source/mscl/MicroStrain/Wireless/Commands/StopNode.cpp',
									'source/mscl/MicroStrain/Wireless/Commands/StopNodeStatus.cpp',
									'source/mscl/MicroStrain/Wireless/Commands/WriteEeprom.cpp',

									'source/mscl/MicroStrain/Wireless/Devices/SGLink.cpp',
									'source/mscl/MicroStrain/Wireless/Devices/SGLink8ch.cpp',
									'source/mscl/MicroStrain/Wireless/Devices/SGLinkRgd.cpp',
									'source/mscl/MicroStrain/Wireless/Devices/SHMLink.cpp',
									'source/mscl/MicroStrain/Wireless/Devices/VLink.cpp',

									'source/mscl/MicroStrain/Wireless/Features/AvailableSampleRates.cpp',
									'source/mscl/MicroStrain/Wireless/Features/NodeFeatures.cpp',
									'source/mscl/MicroStrain/Wireless/Features/NodeFeatures_dvrtlink.cpp',
                                    'source/mscl/MicroStrain/Wireless/Features/NodeFeatures_envlinkMini.cpp',
                                    'source/mscl/MicroStrain/Wireless/Features/NodeFeatures_envlinkPro.cpp',
									'source/mscl/MicroStrain/Wireless/Features/NodeFeatures_glink.cpp',
									'source/mscl/MicroStrain/Wireless/Features/NodeFeatures_glink2External.cpp',
									'source/mscl/MicroStrain/Wireless/Features/NodeFeatures_glink2Internal.cpp',
									'source/mscl/MicroStrain/Wireless/Features/NodeFeatures_iepeLink.cpp',
                                    'source/mscl/MicroStrain/Wireless/Features/NodeFeatures_rtdlink.cpp',
									'source/mscl/MicroStrain/Wireless/Features/NodeFeatures_sglink.cpp',
									'source/mscl/MicroStrain/Wireless/Features/NodeFeatures_sglink8ch.cpp',
									'source/mscl/MicroStrain/Wireless/Features/NodeFeatures_sglinkoem.cpp',
									'source/mscl/MicroStrain/Wireless/Features/NodeFeatures_sglinkoemHermetic.cpp',
									'source/mscl/MicroStrain/Wireless/Features/NodeFeatures_sglinkoemNoXR.cpp',
									'source/mscl/MicroStrain/Wireless/Features/NodeFeatures_sglinkrgd.cpp',
									'source/mscl/MicroStrain/Wireless/Features/NodeFeatures_shmlink.cpp',
                                    'source/mscl/MicroStrain/Wireless/Features/NodeFeatures_tclink1ch.cpp',
                                    'source/mscl/MicroStrain/Wireless/Features/NodeFeatures_tclink3ch.cpp',
                                    'source/mscl/MicroStrain/Wireless/Features/NodeFeatures_tclink6ch.cpp',
									'source/mscl/MicroStrain/Wireless/Features/NodeFeatures_vlink.cpp',

									'source/mscl/MicroStrain/Wireless/Packets/AsyncDigitalPacket.cpp',
									'source/mscl/MicroStrain/Wireless/Packets/AsyncDigitalAnalogPacket.cpp',
									'source/mscl/MicroStrain/Wireless/Packets/BufferedLdcPacket.cpp',
									'source/mscl/MicroStrain/Wireless/Packets/BufferedLdcPacket_16ch.cpp',
									'source/mscl/MicroStrain/Wireless/Packets/LdcPacket.cpp',
									'source/mscl/MicroStrain/Wireless/Packets/LdcPacket_16ch.cpp',
									'source/mscl/MicroStrain/Wireless/Packets/NodeDiscoveryPacket.cpp',
                                    'source/mscl/MicroStrain/Wireless/Packets/ShmPacket.cpp',
									'source/mscl/MicroStrain/Wireless/Packets/SyncSamplingPacket.cpp',
									'source/mscl/MicroStrain/Wireless/Packets/SyncSamplingPacket_16ch.cpp',
									'source/mscl/MicroStrain/Wireless/Packets/WirelessDataPacket.cpp',
									'source/mscl/MicroStrain/Wireless/Packets/WirelessPacket.cpp',
									'source/mscl/MicroStrain/Wireless/Packets/WirelessPacketCollector.cpp',
									'source/mscl/MicroStrain/Wireless/Packets/WirelessPacketUtils.cpp',

									'source/mscl/MicroStrain/Inertial/InertialChannel.cpp',
									'source/mscl/MicroStrain/Inertial/InertialDataField.cpp',
									'source/mscl/MicroStrain/Inertial/InertialDataPoint.cpp',
									'source/mscl/MicroStrain/Inertial/InertialNode.cpp',
									'source/mscl/MicroStrain/Inertial/InertialNode_Impl.cpp',
									'source/mscl/MicroStrain/Inertial/InertialNodeInfo.cpp',
									'source/mscl/MicroStrain/Inertial/InertialParser.cpp',

									'source/mscl/MicroStrain/Inertial/Packets/InertialDataPacket.cpp',
									'source/mscl/MicroStrain/Inertial/Packets/InertialFieldParser.cpp',
									'source/mscl/MicroStrain/Inertial/Packets/InertialFieldParser_Sensor.cpp',
									'source/mscl/MicroStrain/Inertial/Packets/InertialFieldParser_GPS.cpp',
									'source/mscl/MicroStrain/Inertial/Packets/InertialFieldParser_EstFilter.cpp',
									'source/mscl/MicroStrain/Inertial/Packets/InertialPacket.cpp',
									'source/mscl/MicroStrain/Inertial/Packets/InertialPacketBuilder.cpp',
									'source/mscl/MicroStrain/Inertial/Packets/InertialPacketCollector.cpp',

									'source/mscl/MicroStrain/Inertial/Commands/Sensor_Commands.cpp',
									'source/mscl/MicroStrain/Inertial/Commands/System_Commands.cpp',
									'source/mscl/MicroStrain/Inertial/Commands/GenericInertialCommand.cpp',
									'source/mscl/MicroStrain/Inertial/Commands/GetDeviceDescriptorSets.cpp',
									'source/mscl/MicroStrain/Inertial/Commands/GetDeviceInfo.cpp',
									'source/mscl/MicroStrain/Inertial/Commands/GPS_Commands.cpp',
									'source/mscl/MicroStrain/Inertial/Commands/InertialCmdResponse.cpp',
									'source/mscl/MicroStrain/Inertial/Commands/Inertial_Commands.cpp',
									'source/mscl/MicroStrain/Inertial/Commands/EstFilter_Commands.cpp',
									'source/mscl/MicroStrain/Inertial/Commands/Ping.cpp'
								 ],
						 extra_compile_args = extra_compile_args,
						 extra_link_args = extra_link_args
						 )
setup (name = 'mscl',
	   version = '0.13.7',   #update with each release
	   author = "LORD MicroStrain Sensing Systems",
	   description = """MSCL Python Extension Module""",
	   ext_modules = [mscl_module], 
	   py_modules = ["mscl"]
	   )
