NDSummary.OnToolTipsLoaded("File:MicroStrain/Wireless/DeliveryStopFlags.h",{6074:"<div class=\"NDToolTip TClass LC\"><div class=\"NDClassPrototype\" id=\"NDClassPrototype6074\"><div class=\"CPEntry TClass Current\"><div class=\"CPName\">DeliveryStopFlags</div></div></div><div class=\"TTSummary\">The delivery stop flags indicate which stops on the pipeline act on the application data</div></div>",6076:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype6076\" class=\"NDPrototype NoParameterForm\">DeliveryStopFlags()</div><div class=\"TTSummary\">Initializes a DeliveryStopFlags object</div></div>",6077:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype6077\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\">DeliveryStopFlags(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PType first\"><span class=\"SHKeyword\">bool</span>&nbsp;</td><td class=\"PName last\">pc,</td></tr><tr><td class=\"PType first\"><span class=\"SHKeyword\">bool</span>&nbsp;</td><td class=\"PName last\">appBoard,</td></tr><tr><td class=\"PType first\"><span class=\"SHKeyword\">bool</span>&nbsp;</td><td class=\"PName last\">linkBoard,</td></tr><tr><td class=\"PType first\"><span class=\"SHKeyword\">bool</span>&nbsp;</td><td class=\"PName last\">baseStation</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Initializes a DeliveryStopFlags object given specific values</div></div>",6079:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype6079\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">bool</span> pc: <span class=\"SHNumber\">1</span></div><div class=\"TTSummary\">A stop flag representing the pc</div></div>",6080:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype6080\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">bool</span> appBoard: <span class=\"SHNumber\">1</span></div><div class=\"TTSummary\">A stop flag representing the appBoard</div></div>",6081:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype6081\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">bool</span> linkBoard: <span class=\"SHNumber\">1</span></div><div class=\"TTSummary\">A stop flag representing the linkBoard</div></div>",6082:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype6082\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">bool</span> baseStation: <span class=\"SHNumber\">1</span></div><div class=\"TTSummary\">A stop flag representing the baseStation</div></div>",6084:"<div class=\"NDToolTip TOperator LC\"><div class=\"TTSummary\">Checks that two DeliveryStopFlags objects are equal</div></div>",6085:"<div class=\"NDToolTip TOperator LC\"><div class=\"TTSummary\">Checks that two DeliveryStopFlags objects are not equal</div></div>",6087:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype6087\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">bool</span> compare(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PModifierQualifier first\"><span class=\"SHKeyword\">const</span>&nbsp;</td><td class=\"PType\">DeliveryStopFlags&nbsp;</td><td class=\"PNamePrefix\">&amp;</td><td class=\"PName last\">src</td></tr></table></td><td class=\"PAfterParameters\">) <span class=\"SHKeyword\">const</span></td></tr></table></div><div class=\"TTSummary\">Checks that two DeliveryStopFlags are identical</div></div>",6088:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype6088\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">static</span> DeliveryStopFlags fromInvertedByte(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PType first\"><span class=\"SHKeyword\">uint8</span>&nbsp;</td><td class=\"PName last\">dsf</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Sets all the stop flags based on the inverted (ASPP v1) byte value passed in</div></div>",6089:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype6089\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">static</span> DeliveryStopFlags fromByte(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PType first\"><span class=\"SHKeyword\">uint8</span>&nbsp;</td><td class=\"PName last\">dsf</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Sets all the stop flags based on the byte value passed in</div></div>",6090:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype6090\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">uint8</span> toInvertedByte() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Gets the inverted (ASPP v1) delivery stop flag byte value based on the current stop flags set</div></div>",6091:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype6091\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">uint8</span> toByte() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Gets the delivery stop flag byte value based on the current stop flags set</div></div>"});