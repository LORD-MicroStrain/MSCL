NDSummary.OnToolTipsLoaded("CClass:MipChannelIdentifier",{950:"<div class=\"NDToolTip TClass LC\"><div class=\"NDClassPrototype\" id=\"NDClassPrototype950\"><div class=\"CPEntry TClass Current\"><div class=\"CPName\">MipChannelIdentifier</div></div></div><div class=\"TTSummary\">A single additional identifier for a MipDataPoint. Contains a uint value with an identifier type specifier.</div></div>",951:"<div class=\"NDToolTip TEnumeration LC\"><div class=\"TTSummary\">Identifier type options, indicates what the MipChannelIdentifier::id value represents.</div></div>",959:"<div class=\"NDToolTip TEnumeration LC\"><div class=\"TTSummary\">ID definitions when Type is MipChannelIdentifier::AIDING_MEASUREMENT_TYPE</div></div>",966:"<div class=\"NDToolTip TEnumeration LC\"><div class=\"TTSummary\">ID definitions when Type is MipChannelIdentifier::GNSS_CONSTELLATION</div></div>",972:"<div class=\"NDToolTip TEnumeration LC\"><div class=\"TTSummary\">ID definitions when Type is MipChannelIdentifier::GNSS_SIGNAL_ID</div></div>",1038:"<div class=\"NDToolTip TEnumeration LC\"><div class=\"TTSummary\">ID definitions when Type is MipChannelIdentifier::GNSS_RF_BAND</div></div>",1043:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype1043\" class=\"NDPrototype NoParameterForm\">MipChannelIdentifier()</div><div class=\"TTSummary\">Default constructor</div></div>",1044:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype1044\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\">MipChannelIdentifier(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PType first\">Type&nbsp;</td><td class=\"PName last\">identifierType,</td></tr><tr><td class=\"PType first\"><span class=\"SHKeyword\">uint32</span>&nbsp;</td><td class=\"PName last\">id</td></tr></table></td><td class=\"PAfterParameters\">) : m_type(identifierType), m_id(id)</td></tr></table></div><div class=\"TTSummary\">Construct MipChannelIdentifier object with specified MipChannelIdentifier::Type and ID values.</div></div>",1045:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype1045\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\">MipChannelIdentifier(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PType first\">Type&nbsp;</td><td class=\"PName last\">identifierType,</td></tr><tr><td class=\"PType first\"><span class=\"SHKeyword\">uint32</span>&nbsp;</td><td class=\"PName last\">id,</td></tr><tr><td class=\"PType first\"><span class=\"SHKeyword\">uint32</span>&nbsp;</td><td class=\"PName last\">specifier</td></tr></table></td><td class=\"PAfterParameters\">) : m_type(identifierType), m_id(id), m_specifier(specifier)</td></tr></table></div><div class=\"TTSummary\">Construct MipChannelIdentifier object with specified MipChannelIdentifier::Type and ID values.</div></div>",1046:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype1046\" class=\"NDPrototype NoParameterForm\">Type identifierType() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Returns the MipChannelIdentifier::Type specifier of this identifier.</div></div>",1047:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype1047\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">uint32</span> id() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Returns the identifier value.</div></div>",1048:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype1048\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">bool</span> hasSpecifier() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Indicates whether this identifier has an optional additional specifier.</div></div>",1049:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype1049\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">uint32</span> specifier() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Returns the optional additional specifier value.</div></div>",1050:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype1050\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\">std::<span class=\"SHKeyword\">string</span> name(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PType first\"><span class=\"SHKeyword\">bool</span>&nbsp;</td><td class=\"PName\">standardizedFormat&nbsp;</td><td class=\"PDefaultValueSeparator\">=&nbsp;</td><td class=\"PDefaultValue last\"><span class=\"SHKeyword\">true</span></td></tr></table></td><td class=\"PAfterParameters\">) <span class=\"SHKeyword\">const</span></td></tr></table></div><div class=\"TTSummary\">Returns the string representation of this identifier based on type and value.</div></div>",1051:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype1051\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">bool</span> hasSpecifier(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PModifierQualifier first\">std::</td><td class=\"PType\"><span class=\"SHKeyword\">string</span>&nbsp;</td><td class=\"PNamePrefix\">&amp;</td><td class=\"PName last\">specifierName</td></tr></table></td><td class=\"PAfterParameters\">) <span class=\"SHKeyword\">const</span></td></tr></table></div><div class=\"TTSummary\">Indicates whether this identifier has an optional additional specifier.&nbsp; Parameters: specifierName - string reference that is set to the specifier name if found</div></div>",1052:"<div class=\"NDToolTip TType LC\"><div class=\"TTSummary\">A vector of MipChannelIdentifier values, used to assign additional identifiers to a MipDataPoint</div></div>"});