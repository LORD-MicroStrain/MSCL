NDSummary.OnToolTipsLoaded("File:MicroStrain/ResponsePattern.h",{9709:"<div class=\"NDToolTip TClass LC\"><div class=\"NDClassPrototype\" id=\"NDClassPrototype9709\"><div class=\"CPEntry TClass Current\"><div class=\"CPName\">ResponsePattern</div></div></div><div class=\"TTSummary\">A pattern matching the expected response from a device command (Base Class).</div></div>",9717:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype9717\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">explicit</span> ResponsePattern(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PModifierQualifier first\">std::</td><td class=\"PType\">weak_ptr&lt;ResponseCollector&gt;&nbsp;</td><td class=\"PName last\">collector</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Creates a ResponsePattern attached to a collector.</div></div>",9718:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype9718\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">virtual</span> ~ResponsePattern()</div><div class=\"TTSummary\">Destroys the ResponsePattern and unregisters this response from its ResponseCollector</div></div>",9719:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype9719\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">void</span> setResponseCollector(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PModifierQualifier first\">std::</td><td class=\"PType\">weak_ptr&lt;ResponseCollector&gt;&nbsp;</td><td class=\"PName last\">collector</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Sets the ResponseCollector for this pattern, and registers this pattern with the collector.</div></div>",9721:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype9721\" class=\"NDPrototype NoParameterForm\">std::weak_ptr&lt;ResponseCollector&gt; m_collector</div><div class=\"TTSummary\">The ResponseCollector that holds this response pattern</div></div>",9722:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype9722\" class=\"NDPrototype NoParameterForm\">TimedCondition m_matchCondition</div><div class=\"TTSummary\">The TimedCondition for matching the response pattern</div></div>",9723:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype9723\" class=\"NDPrototype NoParameterForm\">mutable std::mutex m_parsingMutex</div><div class=\"TTSummary\">A mutex used for parsing data, which may modify the fullMatched and success flags</div></div>",9724:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype9724\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">bool</span> m_fullyMatched</div><div class=\"TTSummary\">Whether or not the ResponsePattern has been fully matched.&nbsp; Some commands have multiple parts to their response. This will not be true until all required parts have been matched.</div></div>",9725:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype9725\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">bool</span> m_success</div><div class=\"TTSummary\">Whether or not the command was a success (a success response was matched).</div></div>",9727:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype9727\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">void</span> throwIfFailed(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PModifierQualifier first\"><span class=\"SHKeyword\">const</span> std::</td><td class=\"PType\"><span class=\"SHKeyword\">string</span>&nbsp;</td><td class=\"PNamePrefix\">&amp;</td><td class=\"PName last\">commandName</td></tr></table></td><td class=\"PAfterParameters\">) <span class=\"SHKeyword\">const</span></td></tr></table></div><div class=\"TTSummary\">Throws an Error if the command has failed (if m_success is false).&nbsp; Otherwise, no action is taken.</div></div>",9728:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype9728\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">virtual bool</span> match(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PType first\">DataBuffer&nbsp;</td><td class=\"PNamePrefix\">&amp;</td><td class=\"PName last\">data</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Checks if the bytes passed in match the response pattern from their current read position.&nbsp; If data was matched, the read position in the DataBuffer will be updated to be passed the bytes read.</div></div>",9729:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype9729\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">virtual bool</span> match(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PModifierQualifier first\"><span class=\"SHKeyword\">const</span>&nbsp;</td><td class=\"PType\">WirelessPacket&nbsp;</td><td class=\"PNamePrefix\">&amp;</td><td class=\"PName last\">packet</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Checks if the WirelessPacket passed in matches the response pattern\'s bytes</div></div>",9730:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype9730\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">virtual bool</span> match(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PModifierQualifier first\"><span class=\"SHKeyword\">const</span>&nbsp;</td><td class=\"PType\">MipDataField&nbsp;</td><td class=\"PNamePrefix\">&amp;</td><td class=\"PName last\">field</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Checks if the MipDataField passed in matches the response pattern\'s bytes</div></div>",9731:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype9731\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">virtual bool</span> wait(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PType first\"><span class=\"SHKeyword\">uint64</span>&nbsp;</td><td class=\"PName last\">timeout</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Waits for a certain amount of time for the response pattern to be matched</div></div>",9732:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype9732\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">bool</span> fullyMatched() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Checks whether the response pattern has been fully matched.&nbsp; Some commands have multiple parts to their response. This checks whether all responses have been satisfied.</div></div>",9733:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype9733\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">bool</span> success() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Gets whether or not the command was a success (a success response was matched).</div></div>"});