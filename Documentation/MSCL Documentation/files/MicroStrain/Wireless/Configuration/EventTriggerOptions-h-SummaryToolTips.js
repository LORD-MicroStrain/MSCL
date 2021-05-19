NDSummary.OnToolTipsLoaded("File:MicroStrain/Wireless/Configuration/EventTriggerOptions.h",{4691:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype4691\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\">Trigger(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"first\"></td><td class=\"PType\"><span class=\"SHKeyword\">uint8</span>&nbsp;</td><td class=\"PName last\">channelNumber,</td></tr><tr><td class=\"PModifierQualifier first\">WirelessTypes::</td><td class=\"PType\">EventTriggerType&nbsp;</td><td class=\"PName last\">triggerType,</td></tr><tr><td class=\"first\"></td><td class=\"PType\"><span class=\"SHKeyword\">float</span>&nbsp;</td><td class=\"PName last\">triggerValue</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Creates a Trigger object with the provided values.</div></div>",4693:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype4693\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">uint8</span> m_channelNumber</div><div class=\"TTSummary\">The channel number for the trigger.</div></div>",4694:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype4694\" class=\"NDPrototype NoParameterForm\">WirelessTypes::EventTriggerType m_type</div><div class=\"TTSummary\">The WirelessTypes::EventTriggerType for the trigger.</div></div>",4695:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype4695\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">float</span> m_value</div><div class=\"TTSummary\">The value for the trigger (in whatever unit the channel is calibrated for).</div></div>",4697:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype4697\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">uint8</span> channelNumber() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Gets the Wireless Node channel number that the trigger is applied to.</div></div>",4698:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype4698\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">void</span> channelNumber(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PType first\"><span class=\"SHKeyword\">uint8</span>&nbsp;</td><td class=\"PName last\">channelNum</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Sets the Wireless Node channel number for the trigger.</div></div>",4699:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype4699\" class=\"NDPrototype NoParameterForm\">WirelessTypes::EventTriggerType triggerType() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Gets the WirelessTypes::EventTriggerType currently set.</div></div>",4700:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype4700\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">void</span> triggerType(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PModifierQualifier first\">WirelessTypes::</td><td class=\"PType\">EventTriggerType&nbsp;</td><td class=\"PName last\">type</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Sets the WirelessTypes::EventTriggerType for the trigger.</div></div>",4701:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype4701\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">float</span> triggerValue() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Gets the trigger value currently set, in whatever unit the channel is calibrated for.&nbsp; (Ex. If triggering on channel 1, and channel 1 is calibrated for G\'s, a value of 4 for this triggerValue would be 4 G\'s).</div></div>",4702:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype4702\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">void</span> triggerValue(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PType first\"><span class=\"SHKeyword\">float</span>&nbsp;</td><td class=\"PName last\">value</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Sets the trigger value for the trigger, in whatever unit the channel is calibrated for.&nbsp; (Ex. If triggering on channel 1, and channel 1 is calibrated for G\'s, a value of 4 for this triggerValue would be 4 G\'s).</div></div>",4704:"<div class=\"NDToolTip TType LC\"><div class=\"TTSummary\">Typedef for a map of trigger IDs (uint8) to Trigger objects.</div></div>",4705:"<div class=\"NDToolTip TClass LC\"><div class=\"NDClassPrototype\" id=\"NDClassPrototype4705\"><div class=\"CPEntry TClass Current\"><div class=\"CPName\">EventTriggerOptions</div></div></div><div class=\"TTSummary\">Contains all of the Event Trigger options that can be configured for a WirelessNode.</div></div>",4707:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype4707\" class=\"NDPrototype NoParameterForm\">BitMask m_triggerMask</div><div class=\"TTSummary\">The BitMask for enabling and disabling triggers.</div></div>",4708:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype4708\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">uint32</span> m_preDuration</div><div class=\"TTSummary\">The pre event duration (in milliseconds).</div></div>",4709:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype4709\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">uint32</span> m_postDuration</div><div class=\"TTSummary\">The post event duration ( in milliseconds).</div></div>",4710:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype4710\" class=\"NDPrototype NoParameterForm\">Triggers m_triggers</div><div class=\"TTSummary\">The Triggers.</div></div>",4712:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype4712\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">const</span> BitMask&amp; triggerMask() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Gets the actual BitMask that represents the active and inactive triggers.</div></div>",4713:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype4713\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">void</span> triggerMask(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PModifierQualifier first\"><span class=\"SHKeyword\">const</span>&nbsp;</td><td class=\"PType\">BitMask&nbsp;</td><td class=\"PNamePrefix\">&amp;</td><td class=\"PName last\">mask</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Sets the BitMask that represents the active and inactive triggers.</div></div>",4714:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype4714\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">bool</span> anyTriggersEnabled() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Checks if any triggers are enabled.</div></div>",4715:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype4715\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">bool</span> triggerEnabled(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PType first\"><span class=\"SHKeyword\">uint8</span>&nbsp;</td><td class=\"PName last\">triggerIndex</td></tr></table></td><td class=\"PAfterParameters\">) <span class=\"SHKeyword\">const</span></td></tr></table></div><div class=\"TTSummary\">Checks if a specific trigger is enabled.</div></div>",4716:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype4716\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">void</span> enableTrigger(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PType first\"><span class=\"SHKeyword\">uint8</span>&nbsp;</td><td class=\"PName\">triggerIndex,</td><td></td><td class=\"last\"></td></tr><tr><td class=\"PType first\"><span class=\"SHKeyword\">bool</span>&nbsp;</td><td class=\"PName\">enable&nbsp;</td><td class=\"PDefaultValueSeparator\">=&nbsp;</td><td class=\"PDefaultValue last\"><span class=\"SHKeyword\">true</span></td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Enables or disables a specific trigger.</div></div>",4717:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype4717\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">uint32</span> preDuration() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Gets the pre event duration in milliseconds.</div></div>",4718:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype4718\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">void</span> preDuration(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PType first\"><span class=\"SHKeyword\">uint32</span>&nbsp;</td><td class=\"PName last\">duration</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Sets the pre event duration in milliseconds.</div></div>",4719:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype4719\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">uint32</span> postDuration() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Gets the post event duration in milliseconds.</div></div>",4720:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype4720\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">void</span> postDuration(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PType first\"><span class=\"SHKeyword\">uint32</span>&nbsp;</td><td class=\"PName last\">duration</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Sets the post event duration in milliseconds.</div></div>",4721:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype4721\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">void</span> trigger(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"first\"></td><td class=\"PType\"><span class=\"SHKeyword\">uint8</span>&nbsp;</td><td></td><td class=\"PName last\">triggerIndex,</td></tr><tr><td class=\"PModifierQualifier first\"><span class=\"SHKeyword\">const</span>&nbsp;</td><td class=\"PType\">Trigger&nbsp;</td><td class=\"PNamePrefix\">&amp;</td><td class=\"PName last\">trigger</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Sets the Trigger in this options object, for the trigger trigger index.</div></div>",4722:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype4722\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">const</span> Trigger&amp; trigger(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PType first\"><span class=\"SHKeyword\">uint8</span>&nbsp;</td><td class=\"PName last\">triggerIndex</td></tr></table></td><td class=\"PAfterParameters\">) <span class=\"SHKeyword\">const</span></td></tr></table></div><div class=\"TTSummary\">Gets the Trigger for the given trigger index.</div></div>",4723:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype4723\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">const</span> Triggers&amp; triggers() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Gets the Triggers that are currently set in this object.</div></div>"});