NDSummary.OnToolTipsLoaded("File:MicroStrain/ResponseCollector.h",{9168:"<div class=\"NDToolTip TClass LC\"><div class=\"NDClassPrototype\" id=\"NDClassPrototype9168\"><div class=\"CPEntry TClass Current\"><div class=\"CPName\">ResponseCollector</div></div></div><div class=\"TTSummary\">Stores all the expected command responses</div></div>",9170:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype9170\" class=\"NDPrototype NoParameterForm\">std::vector&lt;ResponseInfo&gt; m_expectedResponses</div><div class=\"TTSummary\">Holds the response patterns that, if matched, belong to this collector</div></div>",9171:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype9171\" class=\"NDPrototype NoParameterForm\">std::mutex m_responseMutex</div><div class=\"TTSummary\">A mutex used for thread safety when accessing/modifying the m_expectedResponses vector</div></div>",9172:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype9172\" class=\"NDPrototype NoParameterForm\">Connection* m_connection</div><div class=\"TTSummary\">The Connection pointer to use for retrieving byte information.</div></div>",9174:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype9174\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">void</span> setConnection(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PType first\">Connection&nbsp;</td><td class=\"PNamePrefix\">*</td><td class=\"PName last\">connection</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Sets the connection points to use for retrieving byte information.</div></div>",9175:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype9175\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">void</span> registerResponse(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PType first\">ResponsePattern&nbsp;</td><td class=\"PNamePrefix\">*</td><td class=\"PName last\">response</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Registers a ResponsePattern with this collector</div></div>",9176:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype9176\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">void</span> unregisterResponse(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PType first\">ResponsePattern&nbsp;</td><td class=\"PNamePrefix\">*</td><td class=\"PName last\">response</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Unregisters a ResponsePattern that is within this collector</div></div>",9177:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype9177\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">bool</span> waitingForResponse()</div><div class=\"TTSummary\">Gets whether or not this response collector currently has any response patterns to match</div></div>",9178:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype9178\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">bool</span> matchExpected(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PType first\">DataBuffer&nbsp;</td><td class=\"PNamePrefix\">&amp;</td><td class=\"PName last\">data</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Checks to see if the byte(s) passed in match any of the expected responses</div></div>",9179:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype9179\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">bool</span> matchExpected(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PModifierQualifier first\"><span class=\"SHKeyword\">const</span>&nbsp;</td><td class=\"PType\">WirelessPacket&nbsp;</td><td class=\"PNamePrefix\">&amp;</td><td class=\"PName last\">packet,</td></tr><tr><td class=\"PModifierQualifier first\">std::</td><td class=\"PType\">size_t&nbsp;</td><td></td><td class=\"PName last\">lastReadPos</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Checks to see if the wireless packet passed in matches any of the expected responses</div></div>",9180:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype9180\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">bool</span> matchExpected(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PType first\">MipDataField&nbsp;</td><td class=\"PNamePrefix\">&amp;</td><td class=\"PName last\">field</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Checks to see if the MipDataField passed in matches any of the expected responses</div></div>"});