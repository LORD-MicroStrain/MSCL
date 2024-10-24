NDSummary.OnToolTipsLoaded("File:MicroStrain/Inertial/Commands/AccelBias.h",{1398:"<div class=\"NDToolTip TClass LC\"><div class=\"NDClassPrototype\" id=\"NDClassPrototype1398\"><div class=\"CPEntry TClass Current\"><div class=\"CPName\">AccelBias</div></div></div><div class=\"TTSummary\">Contains the logic for the Inertial GPSTimeUpdate command.</div></div>",1400:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype1400\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">virtual</span> std::<span class=\"SHKeyword\">string</span> commandName() <span class=\"SHKeyword\">const</span></div></div>",1401:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype1401\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">static</span> AccelBias MakeSetCommand(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PModifierQualifier first\"><span class=\"SHKeyword\">const</span>&nbsp;</td><td class=\"PType\">GeometricVector&nbsp;</td><td class=\"PNamePrefix\">&amp;</td><td class=\"PName last\">vectorToSet</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div></div>",1402:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype1402\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">static</span> AccelBias MakeGetCommand()</div></div>",1403:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype1403\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">static</span> GeometricVector getResponseData(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PModifierQualifier first\"><span class=\"SHKeyword\">const</span>&nbsp;</td><td class=\"PType\">GenericMipCmdResponse&nbsp;</td><td class=\"PNamePrefix\">&amp;</td><td class=\"PName last\">response</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div></div>",1404:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype1404\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">operator</span> ByteStream() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Converts this class to a ByteStream.</div></div>",1405:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype1405\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\">AccelBias(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PModifierQualifier first\">MipTypes::</td><td class=\"PType\">FunctionSelector&nbsp;</td><td></td><td class=\"PName last\">function_selector,</td></tr><tr><td class=\"PModifierQualifier first\"><span class=\"SHKeyword\">const</span>&nbsp;</td><td class=\"PType\">GeometricVector&nbsp;</td><td class=\"PNamePrefix\">&amp;</td><td class=\"PName last\">dataToUse</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Private constructor creates a GyroBias object.&nbsp; Use Make___Command methods to create an object.</div></div>",1406:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype1406\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">virtual</span> MipTypes::Command commandType() <span class=\"SHKeyword\">const</span></div></div>",1407:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype1407\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">virtual uint8</span> fieldDataByte() <span class=\"SHKeyword\">const</span></div></div>",1408:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype1408\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">virtual bool</span> responseExpected() <span class=\"SHKeyword\">const</span></div></div>",1410:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype1410\" class=\"NDPrototype NoParameterForm\">MipTypes::FunctionSelector m_functionSelector</div><div class=\"TTSummary\">The MipTypes::FunctionSelector type of command to send, get/set, reset to factory defaults, et al.</div></div>",1411:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype1411\" class=\"NDPrototype NoParameterForm\">GeometricVector m_accelerometerBiasVector</div><div class=\"TTSummary\">The ConstellationSettingsData to send to the device.</div></div>",1413:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype1413\" class=\"NDPrototype NoParameterForm\">~AccelBias()</div></div>"});