NDSummary.OnToolTipsLoaded("File:MicroStrain/Wireless/Commands/BaseStation_ReadEeprom.h",{4065:"<div class=\"NDToolTip TClass LC\"><div class=\"NDClassPrototype\" id=\"NDClassPrototype4065\"><div class=\"CPEntry TClass Current\"><div class=\"CPName\">BaseStation_ReadEeprom</div></div></div><div class=\"TTSummary\">Contains logic for the base station read eeprom command</div></div>",4067:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype4067\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">static</span> ByteStream buildCommand(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PType first\"><span class=\"SHKeyword\">uint16</span>&nbsp;</td><td class=\"PName last\">eepromAddress</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Builds the eeprom read command packet</div></div>",4068:"<div class=\"NDToolTip TClass LC\"><div class=\"NDClassPrototype\" id=\"NDClassPrototype4068\"><div class=\"CPEntry TClass Current\"><div class=\"CPName\">Response</div></div></div><div class=\"TTSummary\">Handles the response to the base station read eeprom command</div></div>",4070:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype4070\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\">Response(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PModifierQualifier first\">std::</td><td class=\"PType\">weak_ptr&lt;ResponseCollector&gt;&nbsp;</td><td class=\"PName last\">collector</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Creates a read eeprom Response object</div></div>",4072:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype4072\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">uint16</span> m_result</div><div class=\"TTSummary\">The result value of the read eeprom command.</div></div>",4074:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype4074\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">uint16</span> result() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Gets the result value of the response.</div></div>",4075:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype4075\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">bool</span> matchSuccessResponse(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PType first\">DataBuffer&nbsp;</td><td class=\"PNamePrefix\">&amp;</td><td class=\"PName last\">data</td></tr></table></td><td class=\"PAfterParameters\">) <span class=\"SHKeyword\">override</span></td></tr></table></div><div class=\"TTSummary\">Checks if the bytes passed in match the success response pattern from their current read position</div></div>",4076:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype4076\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">bool</span> matchFailResponse(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PType first\">DataBuffer&nbsp;</td><td class=\"PNamePrefix\">&amp;</td><td class=\"PName last\">data</td></tr></table></td><td class=\"PAfterParameters\">) <span class=\"SHKeyword\">override</span></td></tr></table></div><div class=\"TTSummary\">Checks if the bytes passed in match the failure response pattern from their current read position</div></div>"});