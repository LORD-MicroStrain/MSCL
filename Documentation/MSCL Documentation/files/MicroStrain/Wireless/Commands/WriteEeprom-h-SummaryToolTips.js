NDSummary.OnToolTipsLoaded("File:MicroStrain/Wireless/Commands/WriteEeprom.h",{2061:"<div class=\"NDToolTip TClass LC\"><div class=\"NDClassPrototype\" id=\"NDClassPrototype2061\"><div class=\"CPEntry TClass Current\"><div class=\"CPName\">WriteEeprom</div></div></div><div class=\"TTSummary\">Contains logic for the WriteEeprom Node command</div></div>",2063:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype2063\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">static</span> ByteStream buildCommand(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PType first\">NodeAddress&nbsp;</td><td class=\"PName last\">nodeAddress,</td></tr><tr><td class=\"PType first\"><span class=\"SHKeyword\">uint16</span>&nbsp;</td><td class=\"PName last\">eepromAddress,</td></tr><tr><td class=\"PType first\"><span class=\"SHKeyword\">uint16</span>&nbsp;</td><td class=\"PName last\">valueToWrite</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Builds the WriteEeprom command packet</div></div>",2064:"<div class=\"NDToolTip TClass LC\"><div class=\"NDClassPrototype\" id=\"NDClassPrototype2064\"><div class=\"CPEntry TClass Current\"><div class=\"CPName\">Response</div></div></div><div class=\"TTSummary\">Handles the response to the WriteEeprom Node command</div></div>",2066:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype2066\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\">Response(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"first\"></td><td class=\"PType\">NodeAddress&nbsp;</td><td class=\"PName last\">nodeAddress,</td></tr><tr><td class=\"PModifierQualifier first\">std::</td><td class=\"PType\">weak_ptr&lt;ResponseCollector&gt;&nbsp;</td><td class=\"PName last\">collector</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Creates a WriteEeprom Response object</div></div>",2068:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype2068\" class=\"NDPrototype NoParameterForm\">NodeAddress m_nodeAddress</div><div class=\"TTSummary\">The node address to look for in the WriteEeprom response</div></div>",2070:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype2070\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">virtual bool</span> matchSuccessResponse(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PModifierQualifier first\"><span class=\"SHKeyword\">const</span>&nbsp;</td><td class=\"PType\">WirelessPacket&nbsp;</td><td class=\"PNamePrefix\">&amp;</td><td class=\"PName last\">packet</td></tr></table></td><td class=\"PAfterParameters\">) <span class=\"SHKeyword\">override</span></td></tr></table></div><div class=\"TTSummary\">Checks if the WirelessPacket passed in matches the expected response pattern\'s bytes</div></div>"});