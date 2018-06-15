NDSummary.OnToolTipsLoaded("File:MicroStrain/Inertial/Commands/GNSS_SourceControl.h",{369:"<div class=\"NDToolTip TClass LC\"><div class=\"NDClassPrototype\" id=\"NDClassPrototype369\"><div class=\"CPEntry TClass Current\"><div class=\"CPName\">GNSS_SourceControl</div></div></div><div class=\"TTSummary\">Contains the logic for the Inertial GNSS_SourceControl command.</div></div>",371:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype371\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">virtual</span> std::<span class=\"SHKeyword\">string</span> commandName() <span class=\"SHKeyword\">const</span></div></div>",372:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype372\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">static</span> GNSS_SourceControl MakeSetCommand(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PModifierQualifier first\"><span class=\"SHKeyword\">const</span> InertialTypes::</td><td class=\"PType\">GNSS_Source&nbsp;</td><td class=\"PNamePrefix\">&amp;</td><td class=\"PName last\">dataToUse</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Parameter: dataToUse The GNSS_Source object to set.</div></div>",373:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype373\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">static</span> GNSS_SourceControl MakeGetCommand()</div></div>",374:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype374\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">static</span> InertialTypes::GNSS_Source getResponseData(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PModifierQualifier first\"><span class=\"SHKeyword\">const</span>&nbsp;</td><td class=\"PType\">GenericMipCmdResponse&nbsp;</td><td class=\"PNamePrefix\">&amp;</td><td class=\"PName last\">response</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div></div>",375:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype375\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">operator</span> ByteStream() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Converts this class to a ByteStream.</div></div>",376:"<div class=\"NDToolTip TFunction LC\"><div class=\"TTSummary\">Private constructor creates a GNSS_SourceControl object.&nbsp; Use Make___Command methods to create an object.</div></div>",377:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype377\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">virtual</span> MipTypes::Command commandType() <span class=\"SHKeyword\">const</span></div></div>",378:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype378\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">virtual uint8</span> fieldDataByte() <span class=\"SHKeyword\">const</span></div></div>",379:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype379\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">virtual bool</span> responseExpected() <span class=\"SHKeyword\">const</span></div></div>",381:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype381\" class=\"NDPrototype NoParameterForm\">MipTypes::FunctionSelector m_functionSelector</div><div class=\"TTSummary\">The FunctionSelector type of command to send, get/set, reset to factory defaults, et al.</div></div>",382:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype382\" class=\"NDPrototype NoParameterForm\">InertialTypes::GNSS_Source m_gnssSource</div><div class=\"TTSummary\">The GNSS_Source to send to the device.</div></div>"});