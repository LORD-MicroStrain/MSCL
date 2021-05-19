NDSummary.OnToolTipsLoaded("CClass:SyncNetworkInfo",{6703:"<div class=\"NDToolTip TClass LC\"><div class=\"NDClassPrototype\" id=\"NDClassPrototype6703\"><div class=\"CPEntry TClass Current\"><div class=\"CPName\">SyncNetworkInfo</div></div></div><div class=\"TTSummary\">Contains network information for a WirelessNode that has been added to the Sync Sampling Network.</div></div>",6705:"<div class=\"NDToolTip TEnumeration LC\"><div class=\"TTSummary\">The status of an individual node.</div></div>",6711:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype6711\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\">SyncNetworkInfo(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PType first\">WirelessNode&nbsp;</td><td class=\"PNamePrefix\">&amp;</td><td class=\"PName last\">node</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Creates a SyncNetworkInfo object</div></div>",6713:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype6713\" class=\"NDPrototype NoParameterForm\">WirelessNode m_node</div><div class=\"TTSummary\">The WirelessNode that this info belongs to</div></div>",6714:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype6714\" class=\"NDPrototype NoParameterForm\">NodeAddress m_nodeAddress</div><div class=\"TTSummary\">The NodeAddress of the Node that this info belongs to.</div></div>",6715:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype6715\" class=\"NDPrototype NoParameterForm\">WirelessModels::NodeModel m_model</div><div class=\"TTSummary\">The WirelessModels::NodeModel of the Node that this info belongs to.</div></div>",6716:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype6716\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">float</span> m_percentBandwidth</div><div class=\"TTSummary\">The standard percent of bandwidth that this node takes up</div></div>",6717:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype6717\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">float</span> m_percentBandwidth_optimized</div><div class=\"TTSummary\">The space-optimized percent of bandwidth that this node takes up</div></div>",6718:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype6718\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">uint32</span> m_tdmaAddress</div><div class=\"TTSummary\">The TDMA address that was found for this node</div></div>",6719:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype6719\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">uint16</span> m_slotSize</div><div class=\"TTSummary\">The number of individual slots that the node takes up per transmission</div></div>",6720:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype6720\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">uint32</span> m_maxTdmaAddress</div><div class=\"TTSummary\">The maximum TDMA address that can be assigned for the node</div></div>",6721:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype6721\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">uint32</span> m_txPerGroup</div><div class=\"TTSummary\">The number of transmissions per group</div></div>",6722:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype6722\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">uint32</span> m_groupSize</div><div class=\"TTSummary\">The size of the group</div></div>",6723:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype6723\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">uint32</span> m_bytesPerSweep</div><div class=\"TTSummary\">The number of bytes per data sweep.</div></div>",6724:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype6724\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">uint32</span> m_bytesPerBurst</div><div class=\"TTSummary\">The number of bytes per burst (only valid if in Burst mode).</div></div>",6725:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype6725\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">uint32</span> m_maxBytesPerPacket</div><div class=\"TTSummary\">The maximum number of bytes per packet.</div></div>",6726:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype6726\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">double</span> m_bytesPerSecond</div><div class=\"TTSummary\">The number of bytes per second (continuous sampling).</div></div>",6727:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype6727\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">uint32</span> m_maxRetxPerBurst</div><div class=\"TTSummary\">The number of maximum retransmissions per burst (if burst)</div></div>",6728:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype6728\" class=\"NDPrototype NoParameterForm\">NodeStatus m_status</div><div class=\"TTSummary\">The status of the node</div></div>",6729:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype6729\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">uint8</span> m_syncSamplingVersion</div><div class=\"TTSummary\">The version of the Sync Sampling formulas to use.</div></div>",6730:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype6730\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">bool</span> m_optimized</div><div class=\"TTSummary\">Whether or not this node has attempted optimization</div></div>",6731:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype6731\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">bool</span> m_configApplied</div><div class=\"TTSummary\">Whether or not the configuration has been applied for this node</div></div>",6732:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype6732\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">bool</span> m_startedSampling</div><div class=\"TTSummary\">Whether or not the Node has been send the Start Sync Sampling command.</div></div>",6733:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype6733\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">bool</span> m_hasPendingConfig</div><div class=\"TTSummary\">Whether or not there is a &quot;pending&quot; configuration set for this Node.</div></div>",6734:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype6734\" class=\"NDPrototype NoParameterForm\">WirelessNodeConfig m_pendingConfig</div><div class=\"TTSummary\">A WirelessNodeConfig set to be used in all sync network calculations, without actually being applied to the Node.</div></div>",6736:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype6736\" class=\"NDPrototype NoParameterForm\">NodeStatus status() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Gets the node\'s network status.</div></div>",6737:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype6737\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">bool</span> startedSampling() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Checks whether a Node has successfully started sampling.&nbsp; Note: if this returns false, its not 100% gauranteed that the Node isn\'t sampling. It\'s possible the node was successfully started, but that the response never got to the BaseStation.</div></div>",6738:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype6738\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">bool</span> configurationApplied() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Gets whether or not the network configuration has been successfully applied to this node.</div></div>",6739:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype6739\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">float</span> percentBandwidth() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Gets the node\'s individual percent of bandwidth in the network.</div></div>",6740:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype6740\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">uint32</span> tdmaAddress() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Gets the TDMA address that was found and assigned to the node.</div></div>",6741:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype6741\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">uint32</span> maxTdmaAddress() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Gets the maximum TDMA address that can be assigned to this node. (Advanced)</div></div>",6742:"<div class=\"NDToolTip TFunction LC\"><div class=\"TTSummary\">Gets the number of transmissions per group for this node. (Advanced)</div></div>",6743:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype6743\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">uint32</span> groupSize() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Gets the group size for this node. (Advanced)</div></div>",6744:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype6744\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">uint8</span> syncSamplingVersion() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">The version of the Sync Sampling formulas to use.</div></div>",6745:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype6745\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">float</span> dutyCycle() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Gets the duty cycle currently set (for Event Driven).</div></div>",6746:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype6746\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">void</span> dutyCycle(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PType first\"><span class=\"SHKeyword\">float</span>&nbsp;</td><td class=\"PName last\">percent</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div></div>",6747:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype6747\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">bool</span> hasPendingConfig() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Gets whether or not this network info has a pending configuration set.</div></div>",6748:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype6748\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">void</span> setPendingConfig(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PModifierQualifier first\"><span class=\"SHKeyword\">const</span>&nbsp;</td><td class=\"PType\">WirelessNodeConfig&nbsp;</td><td class=\"PNamePrefix\">&amp;</td><td class=\"PName last\">config</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Sets a pending configuration for the Node in this network info.&nbsp; This is a configuration that is not actually applied to the Node, but should be used in all sync network calculations.</div></div>",6749:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype6749\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">const</span> WirelessNodeConfig&amp; getPendingConfig() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Gets the current pending configuration that is set.</div></div>",6750:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype6750\" class=\"NDPrototype NoParameterForm\">ChannelGroups channelGroups() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Gets the ChannelGroups for the Wireless Node.</div></div>"});