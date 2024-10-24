NDFramePage.OnPageTitleLoaded("CClass:BaseStation_Impl","BaseStation_Impl");NDSummary.OnSummaryLoaded("CClass:BaseStation_Impl",[["C/C++","C"]],[["Classes","Class"],["Functions","Function"],["Groups","Group"],["Variables","Variable"]],[[9379,0,0,"BaseStation_Impl"],[9380,0,2,"Functions","Functions"],[9381,0,1,"BaseStation_Impl","BaseStation_Impl"],[9382,0,1,"~BaseStation_Impl","~BaseStation_Impl"],[9383,0,2,"Variables","Variables"],[9384,0,3,"m_connection","m_connection"],[9385,0,3,"m_packetCollector","m_packetCollector"],[9386,0,3,"m_responseCollector","m_responseCollector"],[9387,0,3,"m_rawBytePacketCollector","m_rawBytePacketCollector"],[9388,0,3,"m_parser","m_parser"],[9389,0,3,"m_baseCommandsTimeout","m_baseCommandsTimeout"],[9390,0,3,"m_nodeCommandsTimeout","m_nodeCommandsTimeout"],[9391,0,3,"m_frequency","m_frequency"],[9392,0,3,"m_commProtocol","m_commProtocol"],[9393,0,3,"m_eeprom","m_eeprom"],[9394,0,3,"m_eepromHelper","m_eepromHelper"],[9395,0,3,"m_features","m_features"],[9396,0,3,"m_protocolMutex","m_protocolMutex"],[9397,0,3,"m_protocol_lxrs","m_protocol_lxrs"],[9398,0,3,"m_protocol_lxrsPlus","m_protocol_lxrsPlus"],[9399,0,3,"m_lastCommTime","m_lastCommTime"],[9400,0,2,"Functions","Functions(2)"],[9401,0,1,"getTimeForBeacon","getTimeForBeacon"],[9402,0,1,"parseData","parseData"],[9403,0,1,"determineProtocols","determineProtocols"],[9404,0,1,"eeHelper","eeHelper"],[9405,0,1,"doCommand","doCommand"],[9406,0,1,"connection","connection"],[9407,0,1,"features","features"],[9408,0,1,"protocol","protocol"],[9409,0,1,"lastCommunicationTime","lastCommunicationTime"],[9410,0,1,"read","read"],[9411,0,1,"write","write"],[9412,0,1,"setReadWriteRetries","setReadWriteRetries"],[9413,0,1,"getReadWriteRetries","getReadWriteRetries"],[9414,0,1,"useEepromCache","useEepromCache"],[9415,0,1,"clearEepromCache","clearEepromCache"],[9416,0,1,"frequency","frequency"],[9417,0,1,"communicationProtocol","communicationProtocol"],[9418,0,1,"regionCode","regionCode"],[9419,0,1,"firmwareVersion","firmwareVersion"],[9420,0,1,"model","model"],[9421,0,1,"serial","serial"],[9422,0,1,"microcontroller","microcontroller"],[9423,0,1,"getData","getData"],[9424,0,1,"getRawBytePackets","getRawBytePackets"],[9425,0,1,"totalData","totalData"],[9426,0,1,"getNodeDiscoveries","getNodeDiscoveries"],[9427,0,1,"timeout","timeout"],[9428,0,1,"timeout","timeout(2)"],[9429,0,1,"ping","ping"],[9430,0,1,"readEeprom","readEeprom"],[9431,0,1,"readEeprom","readEeprom(2)"],[9432,0,1,"writeEeprom","writeEeprom"],[9433,0,1,"writeEeprom","writeEeprom(2)"],[9434,0,1,"enableBeacon","enableBeacon"],[9435,0,1,"enableBeacon","enableBeacon(2)"],[9436,0,1,"disableBeacon","disableBeacon"],[9437,0,1,"beaconStatus","beaconStatus"],[9438,0,1,"startRfSweepMode","startRfSweepMode"],[9439,0,1,"startRfSweepMode","startRfSweepMode(2)"],[9440,0,1,"cyclePower","cyclePower"],[9441,0,1,"resetRadio","resetRadio"],[9442,0,1,"changeFrequency","changeFrequency"],[9443,0,1,"verifyConfig","verifyConfig"],[9444,0,1,"applyConfig","applyConfig"],[9445,0,1,"getTransmitPower","getTransmitPower"],[9446,0,1,"getButtonLongPress","getButtonLongPress"],[9447,0,1,"getButtonShortPress","getButtonShortPress"],[9448,0,1,"getAnalogPairingEnabled","getAnalogPairingEnabled"],[9449,0,1,"getAnalogTimeoutTime","getAnalogTimeoutTime"],[9450,0,1,"getAnalogTimeoutVoltage","getAnalogTimeoutVoltage"],[9451,0,1,"getAnalogExceedanceEnabled","getAnalogExceedanceEnabled"],[9452,0,1,"getAnalogPair","getAnalogPair"],[9453,0,1,"doBaseCommand","doBaseCommand"],[9454,0,1,"doNodeCommand","doNodeCommand"],[9455,0,1,"protocol_ping_v1","protocol_ping_v1"],[9456,0,1,"protocol_ping_v2","protocol_ping_v2"],[9457,0,1,"protocol_hardReset_v2","protocol_hardReset_v2"],[9458,0,1,"protocol_softReset_v2","protocol_softReset_v2"],[9459,0,1,"protocol_read_v1","protocol_read_v1"],[9460,0,1,"protocol_read_v2","protocol_read_v2"],[9461,0,1,"protocol_write_v1","protocol_write_v1"],[9462,0,1,"protocol_write_v2","protocol_write_v2"],[9463,0,1,"protocol_enableBeacon_v1","protocol_enableBeacon_v1"],[9464,0,1,"protocol_enableBeacon_v2","protocol_enableBeacon_v2"],[9465,0,1,"protocol_beaconStatus_v1","protocol_beaconStatus_v1"],[9466,0,1,"protocol_startRfSweepMode_v1","protocol_startRfSweepMode_v1"],[9467,0,1,"protocol_node_pageDownload_v1","protocol_node_pageDownload_v1"],[9468,0,1,"protocol_node_datalogInfo_v1","protocol_node_datalogInfo_v1"],[9469,0,1,"protocol_node_getDatalogData_v1","protocol_node_getDatalogData_v1"],[9470,0,1,"protocol_node_longPing_v1","protocol_node_longPing_v1"],[9471,0,1,"protocol_node_hardReset_v2","protocol_node_hardReset_v2"],[9472,0,1,"protocol_node_softReset_v2","protocol_node_softReset_v2"],[9473,0,1,"protocol_node_sleep_v1","protocol_node_sleep_v1"],[9474,0,1,"protocol_node_sleep_v2","protocol_node_sleep_v2"],[9475,0,1,"protocol_node_setToIdle_v1","protocol_node_setToIdle_v1"],[9476,0,1,"protocol_node_setToIdle_v2","protocol_node_setToIdle_v2"],[9477,0,1,"protocol_node_readEeprom_v1","protocol_node_readEeprom_v1"],[9478,0,1,"protocol_node_readEeprom_v2","protocol_node_readEeprom_v2"],[9479,0,1,"protocol_node_writeEeprom_v1","protocol_node_writeEeprom_v1"],[9480,0,1,"protocol_node_writeEeprom_v2","protocol_node_writeEeprom_v2"],[9481,0,1,"protocol_node_autoBalance_v1","protocol_node_autoBalance_v1"],[9482,0,1,"protocol_node_autoBalance_v2","protocol_node_autoBalance_v2"],[9483,0,1,"protocol_node_autocal_shm_v1","protocol_node_autocal_shm_v1"],[9484,0,1,"protocol_node_autocal_shm201_v1","protocol_node_autocal_shm201_v1"],[9485,0,1,"protocol_node_autoshuntcal_v1","protocol_node_autoshuntcal_v1"],[9486,0,1,"protocol_node_getDiagnosticInfo_v1","protocol_node_getDiagnosticInfo_v1"],[9487,0,1,"protocol_node_erase_v1","protocol_node_erase_v1"],[9488,0,1,"protocol_node_erase_v2","protocol_node_erase_v2"],[9489,0,1,"protocol_node_startSync_v1","protocol_node_startSync_v1"],[9490,0,1,"protocol_node_startNonSync_v1","protocol_node_startNonSync_v1"],[9491,0,1,"protocol_node_startNonSync_v2","protocol_node_startNonSync_v2"],[9492,0,1,"protocol_node_batchEepromRead_v1","protocol_node_batchEepromRead_v1"],[9493,0,1,"protocol_node_testCommProtocol","protocol_node_testCommProtocol"],[9494,0,1,"protocol_node_poll","protocol_node_poll"],[9495,0,1,"node_ping","node_ping"],[9496,0,1,"node_hardReset","node_hardReset"],[9497,0,1,"node_softReset","node_softReset"],[9498,0,1,"node_sleep","node_sleep"],[9499,0,1,"node_setToIdle","node_setToIdle"],[9500,0,1,"node_readEeprom","node_readEeprom"],[9501,0,1,"node_writeEeprom","node_writeEeprom"],[9502,0,1,"node_pageDownload","node_pageDownload"],[9503,0,1,"node_batchEepromRead","node_batchEepromRead"],[9504,0,1,"node_getDatalogSessionInfo","node_getDatalogSessionInfo"],[9505,0,1,"node_getDatalogData","node_getDatalogData"],[9506,0,1,"node_erase","node_erase"],[9507,0,1,"node_startSyncSampling","node_startSyncSampling"],[9508,0,1,"node_startNonSyncSampling","node_startNonSyncSampling"],[9509,0,1,"node_armForDatalogging","node_armForDatalogging"],[9510,0,1,"node_triggerArmedDatalogging","node_triggerArmedDatalogging"],[9511,0,1,"node_autoBalance","node_autoBalance"],[9512,0,1,"node_autocal_shm","node_autocal_shm"],[9513,0,1,"node_autocal_shm201","node_autocal_shm201"],[9514,0,1,"node_autoShuntCal","node_autoShuntCal"],[9515,0,1,"node_readSingleSensor","node_readSingleSensor"],[9516,0,1,"node_getDiagnosticInfo","node_getDiagnosticInfo"],[9517,0,1,"node_testCommProtocol","node_testCommProtocol"],[9518,0,1,"node_poll","node_poll"],[9519,0,1,"node_autocal","node_autocal"]]);