NDSummary.OnToolTipsLoaded("File:MicroStrain/Wireless/Commands/GetDatalogSessionInfo.h",{4912:"<div class=\"NDToolTip TClass LC\"><div class=\"NDClassPrototype\" id=\"NDClassPrototype4912\"><div class=\"CPEntry TClass Current\"><div class=\"CPName\">GetDatalogSessionInfo</div></div></div><div class=\"TTSummary\">Contains logic for the Get Datalog Session Info Node command.</div></div>",4914:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype4914\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">static</span> ByteStream buildCommand(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PModifierQualifier first\">WirelessPacket::</td><td class=\"PType\">AsppVersion&nbsp;</td><td class=\"PName last\">asppVer,</td></tr><tr><td class=\"first\"></td><td class=\"PType\">NodeAddress&nbsp;</td><td class=\"PName last\">nodeAddress</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Builds the GetDatalogSessionInfo command packet.</div></div>",4915:"<div class=\"NDToolTip TClass LC\"><div class=\"NDClassPrototype\" id=\"NDClassPrototype4915\"><div class=\"CPEntry TClass Current\"><div class=\"CPName\">Response</div></div></div><div class=\"TTSummary\">Handles the response to the GetDatalogSessionInfo Node command.</div></div>",4917:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype4917\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\">Response(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"first\"></td><td class=\"PType\">NodeAddress&nbsp;</td><td class=\"PName last\">nodeAddress,</td></tr><tr><td class=\"PModifierQualifier first\">std::</td><td class=\"PType\">weak_ptr&lt;ResponseCollector&gt;&nbsp;</td><td class=\"PName last\">collector</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Creates a GetDatalogSessionInfo Response object.</div></div>",4919:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype4919\" class=\"NDPrototype NoParameterForm\">NodeAddress m_nodeAddress</div><div class=\"TTSummary\">The node address to look for in the response.</div></div>",4920:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype4920\" class=\"NDPrototype NoParameterForm\">DatalogSessionInfoResult m_result</div><div class=\"TTSummary\">The DatalogSessionInfoResult to hold the result on success.</div></div>",4922:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype4922\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">bool</span> matchSuccessResponse(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PModifierQualifier first\"><span class=\"SHKeyword\">const</span>&nbsp;</td><td class=\"PType\">WirelessPacket&nbsp;</td><td class=\"PNamePrefix\">&amp;</td><td class=\"PName last\">packet</td></tr></table></td><td class=\"PAfterParameters\">) <span class=\"SHKeyword\">override</span></td></tr></table></div><div class=\"TTSummary\">Checks if the WirelessPacket passed in matches the success response pattern\'s bytes</div></div>",4923:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype4923\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">bool</span> matchFailResponse(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PModifierQualifier first\"><span class=\"SHKeyword\">const</span>&nbsp;</td><td class=\"PType\">WirelessPacket&nbsp;</td><td class=\"PNamePrefix\">&amp;</td><td class=\"PName last\">packet</td></tr></table></td><td class=\"PAfterParameters\">) <span class=\"SHKeyword\">override</span></td></tr></table></div><div class=\"TTSummary\">Checks if the WirelessPacket passed in matches the failure response pattern\'s bytes</div></div>",4924:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype4924\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">const</span> DatalogSessionInfoResult&amp; result() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Gets the DatalogSessionInfoResult from a successful response.</div></div>"});