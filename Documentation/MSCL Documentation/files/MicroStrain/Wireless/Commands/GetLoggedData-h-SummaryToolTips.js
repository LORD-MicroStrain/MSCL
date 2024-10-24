NDSummary.OnToolTipsLoaded("File:MicroStrain/Wireless/Commands/GetLoggedData.h",{4878:"<div class=\"NDToolTip TClass LC\"><div class=\"NDClassPrototype\" id=\"NDClassPrototype4878\"><div class=\"CPEntry TClass Current\"><div class=\"CPName\">GetLoggedData</div></div></div><div class=\"TTSummary\">Contains logic for the Get Logged Data Node command.</div></div>",4880:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype4880\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">static</span> ByteStream buildCommand(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PModifierQualifier first\">WirelessPacket::</td><td class=\"PType\">AsppVersion&nbsp;</td><td class=\"PName last\">asppVer,</td></tr><tr><td class=\"first\"></td><td class=\"PType\">NodeAddress&nbsp;</td><td class=\"PName last\">nodeAddress,</td></tr><tr><td class=\"first\"></td><td class=\"PType\"><span class=\"SHKeyword\">uint32</span>&nbsp;</td><td class=\"PName last\">flashAddress</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Builds the GetLoggedData command packet.</div></div>",4881:"<div class=\"NDToolTip TClass LC\"><div class=\"NDClassPrototype\" id=\"NDClassPrototype4881\"><div class=\"CPEntry TClass Current\"><div class=\"CPName\">Response</div></div></div><div class=\"TTSummary\">Handles the response to the GetLoggedData Node command.</div></div>",4883:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype4883\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\">Response(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"first\"></td><td class=\"PType\">NodeAddress&nbsp;</td><td class=\"PName last\">nodeAddress,</td></tr><tr><td class=\"first\"></td><td class=\"PType\"><span class=\"SHKeyword\">uint32</span>&nbsp;</td><td class=\"PName last\">flashAddress,</td></tr><tr><td class=\"PModifierQualifier first\">std::</td><td class=\"PType\">weak_ptr&lt;ResponseCollector&gt;&nbsp;</td><td class=\"PName last\">collector</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Creates a GetLoggedData Response object.</div></div>",4885:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype4885\" class=\"NDPrototype NoParameterForm\">NodeAddress m_nodeAddress</div><div class=\"TTSummary\">The node address to look for in the response.</div></div>",4886:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype4886\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">uint32</span> m_flashAddress</div><div class=\"TTSummary\">The flash address to match in the response.</div></div>",4887:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype4887\" class=\"NDPrototype NoParameterForm\">ByteStream m_data</div><div class=\"TTSummary\">The ByteStream containing the resulting data on success.</div></div>",4889:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype4889\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">bool</span> matchSuccessResponse(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PModifierQualifier first\"><span class=\"SHKeyword\">const</span>&nbsp;</td><td class=\"PType\">WirelessPacket&nbsp;</td><td class=\"PNamePrefix\">&amp;</td><td class=\"PName last\">packet</td></tr></table></td><td class=\"PAfterParameters\">) <span class=\"SHKeyword\">override</span></td></tr></table></div><div class=\"TTSummary\">Checks if the WirelessPacket passed in matches the success response pattern\'s bytes</div></div>",4890:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype4890\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">bool</span> matchFailResponse(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PModifierQualifier first\"><span class=\"SHKeyword\">const</span>&nbsp;</td><td class=\"PType\">WirelessPacket&nbsp;</td><td class=\"PNamePrefix\">&amp;</td><td class=\"PName last\">packet</td></tr></table></td><td class=\"PAfterParameters\">) <span class=\"SHKeyword\">override</span></td></tr></table></div><div class=\"TTSummary\">Checks if the WirelessPacket passed in matches the failure response pattern\'s bytes</div></div>",4891:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype4891\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">const</span> ByteStream&amp; data() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Gets the ByteStream containing the data from a successful response.</div></div>"});