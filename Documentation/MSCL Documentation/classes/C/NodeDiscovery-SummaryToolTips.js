NDSummary.OnToolTipsLoaded("CClass:NodeDiscovery",{5870:"<div class=\"NDToolTip TClass LC\"><div class=\"NDClassPrototype\" id=\"NDClassPrototype5870\"><div class=\"CPEntry TClass Current\"><div class=\"CPName\">NodeDiscovery</div></div></div><div class=\"TTSummary\">Represents 1 node discovery, which is created when a Wireless Node Discovery packet is sent from a Node.&nbsp; Note: There are multiple versions of Node Discovery packets which have been developed over time.&nbsp; Each version has added more useful information. If an earlier version of the Node Discovery packet is heard, this NodeDiscovery object will have some information be invalid (set to default values).</div></div>",5872:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype5872\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">explicit</span> NodeDiscovery(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PModifierQualifier first\"><span class=\"SHKeyword\">const</span>&nbsp;</td><td class=\"PType\">WirelessPacket&nbsp;</td><td class=\"PNamePrefix\">&amp;</td><td class=\"PName last\">packet</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Creates a NodeDiscovery object from a WirelessPacket</div></div>",5874:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype5874\" class=\"NDPrototype NoParameterForm\">WirelessTypes::EepromMap m_eepromMap</div><div class=\"TTSummary\">Contains an eeprom map to use for updating a WirelessNode\'s eeprom cache with the Node Discovery info, if desired.</div></div>",5875:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype5875\" class=\"NDPrototype NoParameterForm\">NodeAddress m_nodeAddress</div><div class=\"TTSummary\">The node address of the node that sent the Node Discovery packet.</div></div>",5876:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype5876\" class=\"NDPrototype NoParameterForm\">WirelessTypes::Frequency m_radioChannel</div><div class=\"TTSummary\">The radio channel (WirelessTypes::Frequency) that the node was on that sent the Node Discovery packet.</div></div>",5877:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype5877\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">uint16</span> m_panId</div><div class=\"TTSummary\">The PAN id of the Node that send the Node Discovery packet.</div></div>",5878:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype5878\" class=\"NDPrototype NoParameterForm\">WirelessModels::NodeModel m_model</div><div class=\"TTSummary\">The model of the node that sent the Node Discovery packet.</div></div>",5879:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype5879\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">uint32</span> m_serialNumber</div><div class=\"TTSummary\">The serial number of the node that sent the Node Discovery packet.</div></div>",5880:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype5880\" class=\"NDPrototype NoParameterForm\">Version m_firmwareVersion</div><div class=\"TTSummary\">The firmware version of the node that sent the Node Discovery packet.</div></div>",5881:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype5881\" class=\"NDPrototype NoParameterForm\">WirelessTypes::DefaultMode m_defaultMode</div><div class=\"TTSummary\">The WirelessTypes::DefaultMode of the node that sent the Node Discovery packet.</div></div>",5882:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype5882\" class=\"NDPrototype NoParameterForm\">WirelessTypes::CommProtocol m_commProtocol</div><div class=\"TTSummary\">The WirelessTypes::CommProtocol of the node that sent the Node Discovery packet.</div></div>",5883:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype5883\" class=\"NDPrototype NoParameterForm\">Version m_asppVersionLxrs</div><div class=\"TTSummary\">The ASPP Version of the node when in LXRS mode.</div></div>",5884:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype5884\" class=\"NDPrototype NoParameterForm\">Version m_asppVersionLxrsPlus</div><div class=\"TTSummary\">The ASPP Version of the node when in LXRS+ mode.</div></div>",5885:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype5885\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">uint32</span> m_bitResult</div><div class=\"TTSummary\">The Built In Test result that was sent in the packet.</div></div>",5886:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype5886\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">int16</span> m_baseRssi</div><div class=\"TTSummary\">The Base Station RSSI that identifies the received signal strength at the Base Station.</div></div>",5887:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype5887\" class=\"NDPrototype NoParameterForm\">Timestamp m_timestamp</div><div class=\"TTSummary\">The Timestamp of when the NodeDiscovery packet was received by MSCL.</div></div>",5889:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype5889\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">void</span> initFromPacket_v1(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PModifierQualifier first\"><span class=\"SHKeyword\">const</span>&nbsp;</td><td class=\"PType\">WirelessPacket&nbsp;</td><td class=\"PNamePrefix\">&amp;</td><td class=\"PName last\">packet</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Initializes the NodeDiscovery object from a version 1 Node Discovery packet.</div></div>",5890:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype5890\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">void</span> initFromPacket_v2(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PModifierQualifier first\"><span class=\"SHKeyword\">const</span>&nbsp;</td><td class=\"PType\">WirelessPacket&nbsp;</td><td class=\"PNamePrefix\">&amp;</td><td class=\"PName last\">packet</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Initializes the NodeDiscovery object from a version 2 Node Discovery packet.</div></div>",5891:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype5891\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">void</span> initFromPacket_v3(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PModifierQualifier first\"><span class=\"SHKeyword\">const</span>&nbsp;</td><td class=\"PType\">WirelessPacket&nbsp;</td><td class=\"PNamePrefix\">&amp;</td><td class=\"PName last\">packet</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Initializes the NodeDiscovery object from a version 3 Node Discovery packet.</div></div>",5892:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype5892\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">void</span> initFromPacket_v4(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PModifierQualifier first\"><span class=\"SHKeyword\">const</span>&nbsp;</td><td class=\"PType\">WirelessPacket&nbsp;</td><td class=\"PNamePrefix\">&amp;</td><td class=\"PName last\">packet</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Initializes the NodeDiscovery object from a version 4 Node Discovery packet.</div></div>",5893:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype5893\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">void</span> initFromPacket_v5(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PModifierQualifier first\"><span class=\"SHKeyword\">const</span>&nbsp;</td><td class=\"PType\">WirelessPacket&nbsp;</td><td class=\"PNamePrefix\">&amp;</td><td class=\"PName last\">packet</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Initializes the NodeDiscovery object from a version 5 Node Discovery packet.</div></div>",5894:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype5894\" class=\"NDPrototype NoParameterForm\">NodeAddress nodeAddress() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Gets the node address of the discovered Node.</div></div>",5895:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype5895\" class=\"NDPrototype NoParameterForm\">WirelessTypes::Frequency frequency() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Gets the WirelessTypes::Frequency of the discovered Node.</div></div>",5896:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype5896\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">uint16</span> panId() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Gets the PAN Id of the discovered Node.&nbsp; Note: Returns 0 if not present in the packet.</div></div>",5897:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype5897\" class=\"NDPrototype NoParameterForm\">WirelessModels::NodeModel model() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Gets the model of the discovered Node.</div></div>",5898:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype5898\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">uint32</span> serialNumber() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Gets the serial number of the discovered Node.&nbsp; Note: Returns 0 if not present in the packet.</div></div>",5899:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype5899\" class=\"NDPrototype NoParameterForm\">Version firmwareVersion() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Gets the firmware version of the discovered Node.&nbsp; Note: Returns 0.0.0 if not present in the packet.</div></div>",5900:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype5900\" class=\"NDPrototype NoParameterForm\">WirelessTypes::DefaultMode defaultMode() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Gets the WirelessTypes::DefaultMode of the discovered Node.&nbsp; Note: Returns 999 if not present in the packet.</div></div>",5901:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype5901\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">uint32</span> builtInTestResult() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Gets the result bitmask of the built in test.</div></div>",5902:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype5902\" class=\"NDPrototype NoParameterForm\">WirelessTypes::CommProtocol communicationProtocol() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Gets the WirelessTypes::CommProtocol of the discovered Node.</div></div>",5903:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype5903\" class=\"NDPrototype NoParameterForm\">Version asppVersion_lxrs() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Gets the ASPP protocol Version of the Node when it is in LXRS RadioMode.</div></div>",5904:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype5904\" class=\"NDPrototype NoParameterForm\">Version asppVersion_lxrsPlus() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Gets the ASPP protocol Version of the Node when it is in LXRS+ RadioMode.</div></div>",5905:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype5905\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">int16</span> baseRssi() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Gets the base station rssi of the discovered Node.</div></div>",5906:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype5906\" class=\"NDPrototype NoParameterForm\">Timestamp timestamp() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Gets the Timestamp of when the NodeDiscovery packet was received by MSCL.</div></div>",5908:"<div class=\"NDToolTip TType LC\"><div class=\"TTSummary\">typedef for a vector of NodeDiscovery objects</div></div>"});