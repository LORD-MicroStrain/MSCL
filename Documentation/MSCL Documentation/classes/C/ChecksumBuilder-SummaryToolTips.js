NDSummary.OnToolTipsLoaded("CClass:ChecksumBuilder",{9326:"<div class=\"NDToolTip TClass LC\"><div class=\"NDClassPrototype\" id=\"NDClassPrototype9326\"><div class=\"CPEntry TClass Current\"><div class=\"CPName\">ChecksumBuilder</div></div></div><div class=\"TTSummary\">A class used to simply perform checksums on data</div></div>",9328:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype9328\" class=\"NDPrototype NoParameterForm\">ByteStream m_bytes</div><div class=\"TTSummary\">The ByteStream that holds the data that needs checksummed</div></div>",9330:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype9330\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">void</span> append_uint8(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PType first\"><span class=\"SHKeyword\">uint8</span>&nbsp;</td><td class=\"PName last\">value</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Appends a 1-byte unsigned integer to the ChecksumBuilder</div></div>",9331:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype9331\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">void</span> append_uint16(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PType first\"><span class=\"SHKeyword\">uint16</span>&nbsp;</td><td class=\"PName last\">value</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Appends a 2-byte unsigned integer to the ChecksumBuilder</div></div>",9332:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype9332\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">void</span> append_uint32(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PType first\"><span class=\"SHKeyword\">uint32</span>&nbsp;</td><td class=\"PName last\">value</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Appends a 4-byte unsigned integer to the ChecksumBuilder</div></div>",9333:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype9333\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">void</span> appendBytes(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PModifierQualifier first\"><span class=\"SHKeyword\">const</span>&nbsp;</td><td class=\"PType\">Bytes&nbsp;</td><td class=\"PNamePrefix\">&amp;</td><td class=\"PName last\">bytes</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Appends a vector of bytes to the end of the current ChecksumBuilder</div></div>",9334:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype9334\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">void</span> appendByteStream(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PModifierQualifier first\"><span class=\"SHKeyword\">const</span>&nbsp;</td><td class=\"PType\">ByteStream&nbsp;</td><td class=\"PNamePrefix\">&amp;</td><td class=\"PName last\">otherStream</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Appends the entire contents of a ByteStream to the end of the current ChecksumBuilder</div></div>",9335:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype9335\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">uint16</span> simpleChecksum() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Returns a simple checksum of all the bytes in the ChecksumBuilder</div></div>",9336:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype9336\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">uint16</span> fletcherChecksum() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Returns the Fletcher checksum of all the bytes in the ChecksumBuilder</div></div>",9337:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype9337\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">uint32</span> crcChecksum() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Returns the 32-bit CRC with polynomial 0x04C11DB7, an initial value of 0xFFFFFFFF, and inverted output.</div></div>"});