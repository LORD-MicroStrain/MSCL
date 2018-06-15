NDSummary.OnToolTipsLoaded("CClass:SyncNetworkInfo",{5448:"<div class=\"NDToolTip TClass LC\"><div class=\"NDClassPrototype\" id=\"NDClassPrototype5448\"><div class=\"CPEntry TClass Current\"><div class=\"CPName\">SyncNetworkInfo</div></div></div><div class=\"TTSummary\">Contains network information for a WirelessNode that has been added to the Sync Sampling Network.</div></div>",5450:"<div class=\"NDToolTip TEnumeration LC\"><div class=\"TTSummary\">The status of an individual node.</div></div>",5456:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype5456\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\">SyncNetworkInfo(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PType first\">WirelessNode&nbsp;</td><td class=\"PNamePrefix\">&amp;</td><td class=\"PName last\">node</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Creates a SyncNetworkInfo object</div></div>",5458:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype5458\" class=\"NDPrototype NoParameterForm\">WirelessNode m_node</div><div class=\"TTSummary\">The WirelessNode that this info belongs to</div></div>",5459:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype5459\" class=\"NDPrototype NoParameterForm\">NodeAddress m_nodeAddress</div><div class=\"TTSummary\">The NodeAddress of the Node that this info belongs to.</div></div>",5460:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype5460\" class=\"NDPrototype NoParameterForm\">WirelessModels::NodeModel m_model</div><div class=\"TTSummary\">The WirelessModels::NodeModel of the Node that this info belongs to.</div></div>",5461:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype5461\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">float</span> m_percentBandwidth</div><div class=\"TTSummary\">The standard percent of bandwidth that this node takes up</div></div>",5462:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype5462\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">float</span> m_percentBandwidth_optimized</div><div class=\"TTSummary\">The space-optimized percent of bandwidth that this node takes up</div></div>",5463:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype5463\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">uint32</span> m_tdmaAddress</div><div class=\"TTSummary\">The TDMA address that was found for this node</div></div>",5464:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype5464\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">uint16</span> m_slotSize</div><div class=\"TTSummary\">The number of individual slots that the node takes up per transmission</div></div>",5465:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype5465\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">uint32</span> m_maxTdmaAddress</div><div class=\"TTSummary\">The maximum TDMA address that can be assigned for the node</div></div>",5466:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype5466\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">uint32</span> m_txPerGroup</div><div class=\"TTSummary\">The number of transmissions per group</div></div>",5467:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype5467\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">uint32</span> m_groupSize</div><div class=\"TTSummary\">The size of the group</div></div>",5468:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype5468\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">uint32</span> m_bytesPerSweep</div><div class=\"TTSummary\">The number of bytes per data sweep.</div></div>",5469:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype5469\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">uint32</span> m_bytesPerBurst</div><div class=\"TTSummary\">The number of bytes per burst (only valid if in Burst mode).</div></div>",5470:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype5470\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">uint32</span> m_maxBytesPerPacket</div><div class=\"TTSummary\">The maximum number of bytes per packet.</div></div>",5471:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype5471\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">double</span> m_bytesPerSecond</div><div class=\"TTSummary\">The number of bytes per second (continuous sampling).</div></div>",5472:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype5472\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">uint32</span> m_maxRetxPerBurst</div><div class=\"TTSummary\">The number of maximum retransmissions per burst (if burst)</div></div>",5473:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype5473\" class=\"NDPrototype NoParameterForm\">NodeStatus m_status</div><div class=\"TTSummary\">The status of the node</div></div>",5474:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype5474\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">uint8</span> m_syncSamplingVersion</div><div class=\"TTSummary\">The version of the Sync Sampling formulas to use.</div></div>",5475:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype5475\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">bool</span> m_optimized</div><div class=\"TTSummary\">Whether or not this node has attempted optimization</div></div>",5476:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype5476\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">bool</span> m_configApplied</div><div class=\"TTSummary\">Whether or not the configuration has been applied for this node</div></div>",5477:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype5477\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">bool</span> m_startedSampling</div><div class=\"TTSummary\">Whether or not the Node has been send the Start Sync Sampling command.</div></div>",5478:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype5478\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">bool</span> m_hasPendingConfig</div><div class=\"TTSummary\">Whether or not there is a &quot;pending&quot; configuration set for this Node.</div></div>",5479:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype5479\" class=\"NDPrototype NoParameterForm\">WirelessNodeConfig m_pendingConfig</div><div class=\"TTSummary\">A WirelessNodeConfig set to be used in all sync network calculations, without actually being applied to the Node.</div></div>",5481:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype5481\" class=\"NDPrototype NoParameterForm\">NodeStatus status() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Gets the node\'s network status.</div></div>",5482:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype5482\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">bool</span> configurationApplied() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Gets whether or not the network configuration has been successfully applied to this node.</div></div>",5483:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype5483\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">float</span> percentBandwidth() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Gets the node\'s individual percent of bandwidth in the network.</div></div>",5484:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype5484\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">uint32</span> tdmaAddress() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Gets the TDMA address that was found and assigned to the node.</div></div>",5485:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype5485\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">uint32</span> maxTdmaAddress() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Gets the maximum TDMA address that can be assigned to this node. (Advanced)</div></div>",5486:"<div class=\"NDToolTip TFunction LC\"><div class=\"TTSummary\">Gets the number of transmissions per group for this node. (Advanced)</div></div>",5487:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype5487\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">uint32</span> groupSize() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Gets the group size for this node. (Advanced)</div></div>",5488:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype5488\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">uint8</span> syncSamplingVersion() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">The version of the Sync Sampling formulas to use.</div></div>",5489:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype5489\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">float</span> dutyCycle() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Gets the duty cycle currently set (for Event Driven).</div></div>",5490:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype5490\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">void</span> dutyCycle(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PType first\"><span class=\"SHKeyword\">float</span>&nbsp;</td><td class=\"PName last\">percent</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div></div>",5491:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype5491\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">bool</span> hasPendingConfig() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Gets whether or not this network info has a pending configuration set.</div></div>",5492:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype5492\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">void</span> setPendingConfig(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PModifierQualifier first\"><span class=\"SHKeyword\">const</span>&nbsp;</td><td class=\"PType\">WirelessNodeConfig&nbsp;</td><td class=\"PNamePrefix\">&amp;</td><td class=\"PName last\">config</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Sets a pending configuration for the Node in this network info.&nbsp; This is a configuration that is not actually applied to the Node, but should be used in all sync network calculations.</div></div>",5493:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype5493\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">const</span> WirelessNodeConfig&amp; getPendingConfig() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Gets the current pending configuration that is set.</div></div>",5494:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype5494\" class=\"NDPrototype NoParameterForm\">ChannelGroups channelGroups() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Gets the ChannelGroups for the Wireless Node.</div></div>"});