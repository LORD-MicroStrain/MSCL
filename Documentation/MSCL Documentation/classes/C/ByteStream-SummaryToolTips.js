NDSummary.OnToolTipsLoaded("CClass:ByteStream",{9405:"<div class=\"NDToolTip TClass LC\"><div class=\"NDClassPrototype\" id=\"NDClassPrototype9405\"><div class=\"CPEntry TClass Current\"><div class=\"CPName\">ByteStream</div></div></div><div class=\"TTSummary\">A stream of bytes that is used to easily store and retrieve data</div></div>",9407:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype9407\" class=\"NDPrototype NoParameterForm\">ByteStream()</div><div class=\"TTSummary\">Default constructor to create a ByteStream object</div></div>",9408:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype9408\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">explicit</span> ByteStream(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PType first\">Bytes&nbsp;</td><td class=\"PName last\">bytesToCopy</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Constructor to create a ByteStream object, passing in the bytes to store in the stream</div></div>",9409:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype9409\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">virtual</span> ~ByteStream()</div><div class=\"TTSummary\">Default destructor for the ByteStream object</div></div>",9411:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype9411\" class=\"NDPrototype NoParameterForm\">Bytes m_bytes</div><div class=\"TTSummary\">The data stream object that holds all the bytes</div></div>",9413:"<div class=\"NDToolTip TOperator LC\"><div class=\"TTSummary\">Accesses a single byte of the ByteStream</div></div>",9414:"<div class=\"NDToolTip TOperator LC\"><div class=\"TTSummary\">Checks that two ByteStream objects are equal by comparing their data vectors</div></div>",9416:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype9416\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">void</span> append_uint8(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PType first\"><span class=\"SHKeyword\">uint8</span>&nbsp;</td><td class=\"PName last\">value</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Appends a 1-byte unsigned integer to the byte stream</div></div>",9417:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype9417\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">void</span> append_int8(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PType first\"><span class=\"SHKeyword\">int8</span>&nbsp;</td><td class=\"PName last\">value</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Appends a 1-byte signed integer to the byte stream</div></div>",9418:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype9418\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">void</span> append_int16(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"first\"></td><td class=\"PType\"><span class=\"SHKeyword\">int16</span>&nbsp;</td><td class=\"PName\">value,</td><td></td><td class=\"last\"></td></tr><tr><td class=\"PModifierQualifier first\">Utils::</td><td class=\"PType\">Endianness&nbsp;</td><td class=\"PName\">endian</td><td class=\"PDefaultValueSeparator\">=&nbsp;</td><td class=\"PDefaultValue last\">Utils::bigEndian</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Appends a 2-byte signed integer to the byte stream</div></div>",9419:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype9419\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">void</span> append_uint16(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"first\"></td><td class=\"PType\"><span class=\"SHKeyword\">uint16</span>&nbsp;</td><td class=\"PName\">value,</td><td></td><td class=\"last\"></td></tr><tr><td class=\"PModifierQualifier first\">Utils::</td><td class=\"PType\">Endianness&nbsp;</td><td class=\"PName\">endian&nbsp;</td><td class=\"PDefaultValueSeparator\">=&nbsp;</td><td class=\"PDefaultValue last\">Utils::bigEndian</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Appends a 2-byte unsigned integer to the byte stream</div></div>",9420:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype9420\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">void</span> append_uint32(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"first\"></td><td class=\"PType\"><span class=\"SHKeyword\">uint32</span>&nbsp;</td><td class=\"PName\">value,</td><td></td><td class=\"last\"></td></tr><tr><td class=\"PModifierQualifier first\">Utils::</td><td class=\"PType\">Endianness&nbsp;</td><td class=\"PName\">endian&nbsp;</td><td class=\"PDefaultValueSeparator\">=&nbsp;</td><td class=\"PDefaultValue last\">Utils::bigEndian</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Appends a 4-byte unsigned integer to the byte stream</div></div>",9421:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype9421\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">void</span> append_uint64(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"first\"></td><td class=\"PType\"><span class=\"SHKeyword\">uint64</span>&nbsp;</td><td class=\"PName\">value,</td><td></td><td class=\"last\"></td></tr><tr><td class=\"PModifierQualifier first\">Utils::</td><td class=\"PType\">Endianness&nbsp;</td><td class=\"PName\">endian&nbsp;</td><td class=\"PDefaultValueSeparator\">=&nbsp;</td><td class=\"PDefaultValue last\">Utils::bigEndian</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Appends an 8-byte unsigned integer to the byte stream</div></div>",9422:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype9422\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">void</span> append_float(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"first\"></td><td class=\"PType\"><span class=\"SHKeyword\">float</span>&nbsp;</td><td class=\"PName\">value,</td><td></td><td class=\"last\"></td></tr><tr><td class=\"PModifierQualifier first\">Utils::</td><td class=\"PType\">Endianness&nbsp;</td><td class=\"PName\">endian&nbsp;</td><td class=\"PDefaultValueSeparator\">=&nbsp;</td><td class=\"PDefaultValue last\">Utils::bigEndian</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Appends a 4-byte float to the byte stream</div></div>",9423:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype9423\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">void</span> append_double(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"first\"></td><td class=\"PType\"><span class=\"SHKeyword\">double</span>&nbsp;</td><td class=\"PName\">value,</td><td></td><td class=\"last\"></td></tr><tr><td class=\"PModifierQualifier first\">Utils::</td><td class=\"PType\">Endianness&nbsp;</td><td class=\"PName\">endian&nbsp;</td><td class=\"PDefaultValueSeparator\">=&nbsp;</td><td class=\"PDefaultValue last\">Utils::bigEndian</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Appends an 8-byte double to the byte stream</div></div>",9424:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype9424\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">void</span> append_string(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PModifierQualifier first\"><span class=\"SHKeyword\">const</span> std::</td><td class=\"PType\"><span class=\"SHKeyword\">string</span>&nbsp;</td><td class=\"PNamePrefix\">&amp;</td><td class=\"PName last\">str</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Appends a string to the byte stream.</div></div>",9425:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype9425\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">void</span> appendBytes(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PModifierQualifier first\"><span class=\"SHKeyword\">const</span>&nbsp;</td><td class=\"PType\">Bytes&nbsp;</td><td class=\"PNamePrefix\">&amp;</td><td class=\"PName last\">bytes</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Appends a vector of bytes (uint8) to the end of the current ByteStream</div></div>",9426:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype9426\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">void</span> appendByteStream(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PModifierQualifier first\"><span class=\"SHKeyword\">const</span>&nbsp;</td><td class=\"PType\">ByteStream&nbsp;</td><td class=\"PNamePrefix\">&amp;</td><td class=\"PName last\">otherStream</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Appends the entire contents of a ByteStream to the end of the current ByteStream</div></div>",9427:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype9427\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">int8</span> read_int8(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PModifierQualifier first\">std::</td><td class=\"PType\">size_t&nbsp;</td><td class=\"PName last\">position</td></tr></table></td><td class=\"PAfterParameters\">) <span class=\"SHKeyword\">const</span></td></tr></table></div><div class=\"TTSummary\">Reads a 1-byte signed integer from the byte stream</div></div>",9428:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype9428\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">uint8</span> read_uint8(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PModifierQualifier first\">std::</td><td class=\"PType\">size_t&nbsp;</td><td class=\"PName last\">position</td></tr></table></td><td class=\"PAfterParameters\">) <span class=\"SHKeyword\">const</span></td></tr></table></div><div class=\"TTSummary\">Reads a 1-byte unsigned integer from the byte stream</div></div>",9429:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype9429\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">int16</span> read_int16(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PModifierQualifier first\">std::</td><td class=\"PType\">size_t&nbsp;</td><td class=\"PName\">position,</td><td></td><td class=\"last\"></td></tr><tr><td class=\"PModifierQualifier first\">Utils::</td><td class=\"PType\">Endianness&nbsp;</td><td class=\"PName\">endian&nbsp;</td><td class=\"PDefaultValueSeparator\">=&nbsp;</td><td class=\"PDefaultValue last\">Utils::bigEndian</td></tr></table></td><td class=\"PAfterParameters\">) <span class=\"SHKeyword\">const</span></td></tr></table></div><div class=\"TTSummary\">Reads a 2-byte signed integer from the byte stream</div></div>",9430:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype9430\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">uint16</span> read_uint16(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PModifierQualifier first\">std::</td><td class=\"PType\">size_t&nbsp;</td><td class=\"PName\">position,</td><td></td><td class=\"last\"></td></tr><tr><td class=\"PModifierQualifier first\">Utils::</td><td class=\"PType\">Endianness&nbsp;</td><td class=\"PName\">endian&nbsp;</td><td class=\"PDefaultValueSeparator\">=&nbsp;</td><td class=\"PDefaultValue last\">Utils::bigEndian</td></tr></table></td><td class=\"PAfterParameters\">) <span class=\"SHKeyword\">const</span></td></tr></table></div><div class=\"TTSummary\">Reads a 2-byte unsigned integer from the byte stream</div></div>",9431:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype9431\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">uint32</span> read_uint24(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PModifierQualifier first\">std::</td><td class=\"PType\">size_t&nbsp;</td><td class=\"PName\">position,</td><td></td><td class=\"last\"></td></tr><tr><td class=\"PModifierQualifier first\">Utils::</td><td class=\"PType\">Endianness&nbsp;</td><td class=\"PName\">endian&nbsp;</td><td class=\"PDefaultValueSeparator\">=&nbsp;</td><td class=\"PDefaultValue last\">Utils::bigEndian</td></tr></table></td><td class=\"PAfterParameters\">) <span class=\"SHKeyword\">const</span></td></tr></table></div><div class=\"TTSummary\">Reads a 3-byte unsigned integer from the byte stream</div></div>",9432:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype9432\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">int32</span> read_int24(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PModifierQualifier first\">std::</td><td class=\"PType\">size_t&nbsp;</td><td class=\"PName\">position,</td><td></td><td class=\"last\"></td></tr><tr><td class=\"PModifierQualifier first\">Utils::</td><td class=\"PType\">Endianness&nbsp;</td><td class=\"PName\">endian&nbsp;</td><td class=\"PDefaultValueSeparator\">=&nbsp;</td><td class=\"PDefaultValue last\">Utils::bigEndian</td></tr></table></td><td class=\"PAfterParameters\">) <span class=\"SHKeyword\">const</span></td></tr></table></div><div class=\"TTSummary\">Reads a 3-byte signed integer from the byte stream</div></div>",9433:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype9433\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">uint32</span> read_uint32(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PModifierQualifier first\">std::</td><td class=\"PType\">size_t&nbsp;</td><td class=\"PName\">position,</td><td></td><td class=\"last\"></td></tr><tr><td class=\"PModifierQualifier first\">Utils::</td><td class=\"PType\">Endianness&nbsp;</td><td class=\"PName\">endian&nbsp;</td><td class=\"PDefaultValueSeparator\">=&nbsp;</td><td class=\"PDefaultValue last\">Utils::bigEndian</td></tr></table></td><td class=\"PAfterParameters\">) <span class=\"SHKeyword\">const</span></td></tr></table></div><div class=\"TTSummary\">Reads a 4-byte unsigned integer from the byte stream</div></div>",9434:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype9434\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">uint64</span> read_uint64(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PModifierQualifier first\">std::</td><td class=\"PType\">size_t&nbsp;</td><td class=\"PName\">position,</td><td></td><td class=\"last\"></td></tr><tr><td class=\"PModifierQualifier first\">Utils::</td><td class=\"PType\">Endianness&nbsp;</td><td class=\"PName\">endian&nbsp;</td><td class=\"PDefaultValueSeparator\">=&nbsp;</td><td class=\"PDefaultValue last\">Utils::bigEndian</td></tr></table></td><td class=\"PAfterParameters\">) <span class=\"SHKeyword\">const</span></td></tr></table></div><div class=\"TTSummary\">Reads an 8-byte unsigned integer from the byte stream</div></div>",9435:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype9435\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">float</span> read_float(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PModifierQualifier first\">std::</td><td class=\"PType\">size_t&nbsp;</td><td class=\"PName\">position,</td><td></td><td class=\"last\"></td></tr><tr><td class=\"PModifierQualifier first\">Utils::</td><td class=\"PType\">Endianness&nbsp;</td><td class=\"PName\">endian&nbsp;</td><td class=\"PDefaultValueSeparator\">=&nbsp;</td><td class=\"PDefaultValue last\">Utils::bigEndian</td></tr></table></td><td class=\"PAfterParameters\">) <span class=\"SHKeyword\">const</span></td></tr></table></div><div class=\"TTSummary\">Reads a 4-byte float from the byte stream</div></div>",9436:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype9436\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">double</span> read_double(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PModifierQualifier first\">std::</td><td class=\"PType\">size_t&nbsp;</td><td class=\"PName\">position,</td><td></td><td class=\"last\"></td></tr><tr><td class=\"PModifierQualifier first\">Utils::</td><td class=\"PType\">Endianness&nbsp;</td><td class=\"PName\">endian&nbsp;</td><td class=\"PDefaultValueSeparator\">=&nbsp;</td><td class=\"PDefaultValue last\">Utils::bigEndian</td></tr></table></td><td class=\"PAfterParameters\">) <span class=\"SHKeyword\">const</span></td></tr></table></div><div class=\"TTSummary\">Reads an 8-byte double from the byte stream</div></div>",9437:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype9437\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\">std::<span class=\"SHKeyword\">string</span> read_string(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PModifierQualifier first\">std::</td><td class=\"PType\">size_t&nbsp;</td><td class=\"PName last\">position,</td></tr><tr><td class=\"PModifierQualifier first\">std::</td><td class=\"PType\">size_t&nbsp;</td><td class=\"PName last\">length</td></tr></table></td><td class=\"PAfterParameters\">) <span class=\"SHKeyword\">const</span></td></tr></table></div><div class=\"TTSummary\">Reads a string of the specified length from the byte stream</div></div>",9438:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype9438\" class=\"NDPrototype NoParameterForm\">Bytes&amp; data()</div><div class=\"TTSummary\">Gets the byte stream as a vector of bytes (Bytes)</div></div>",9439:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype9439\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">const</span> Bytes&amp; data() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Gets the byte stream as a vector of bytes (Bytes)</div></div>",9440:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype9440\" class=\"NDPrototype NoParameterForm\">std::size_t size() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Gets the size of the byte stream (equivalent of std::vector.size())</div></div>",9441:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype9441\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">void</span> clear()</div><div class=\"TTSummary\">Clears the byte stream (equivalent of std::vector.clear())</div></div>",9442:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype9442\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">bool</span> empty() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Checks whether the vector is empty. (equivalent of std::vector::empty())</div></div>",9443:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype9443\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">void</span> resize(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PModifierQualifier first\">std::</td><td class=\"PType\">size_t&nbsp;</td><td class=\"PName last\">size</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Resizes the byte stream (equivalent of std::vector.resize())</div></div>",9444:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype9444\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">void set</span>(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PModifierQualifier first\"><span class=\"SHKeyword\">const</span>&nbsp;</td><td class=\"PType\">Bytes&nbsp;</td><td class=\"PNamePrefix\">&amp;</td><td class=\"PName last\">bytes</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Sets the underlying bytes to the given Bytes.</div></div>",9445:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype9445\" class=\"NDPrototype NoParameterForm\">Bytes::iterator begin()</div><div class=\"TTSummary\">Gets an iterator referring to the first element in the ByteStream (equivalent of std::vector::begin())</div></div>",9446:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype9446\" class=\"NDPrototype NoParameterForm\">Bytes::const_iterator begin() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Gets a constant iterator referring to the first element in the ByteStream (equivalent of std::vector::cbegin())</div></div>",9447:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype9447\" class=\"NDPrototype NoParameterForm\">Bytes::iterator end()</div><div class=\"TTSummary\">Gets an iterator referring to the &quot;past-the-end&quot; element in the ByteStream. (equivalent of std::vector::end())</div></div>",9448:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype9448\" class=\"NDPrototype NoParameterForm\">Bytes::const_iterator end() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Gets an iterator referring to the &quot;past-the-end&quot; element in the ByteStream. (equivalent of std::vector::cend())</div></div>",9449:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype9449\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">uint16</span> calculateSimpleChecksum(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PModifierQualifier first\">std::</td><td class=\"PType\">size_t&nbsp;</td><td class=\"PName last\">from,</td></tr><tr><td class=\"PModifierQualifier first\">std::</td><td class=\"PType\">size_t&nbsp;</td><td class=\"PName last\">to</td></tr></table></td><td class=\"PAfterParameters\">) <span class=\"SHKeyword\">const</span></td></tr></table></div><div class=\"TTSummary\">Calculates the simple checksum (simple addition of bytes)on the ByteStream</div></div>",9450:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype9450\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">uint16</span> calculateFletcherChecksum(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PModifierQualifier first\">std::</td><td class=\"PType\">size_t&nbsp;</td><td class=\"PName last\">from,</td></tr><tr><td class=\"PModifierQualifier first\">std::</td><td class=\"PType\">size_t&nbsp;</td><td class=\"PName last\">to</td></tr></table></td><td class=\"PAfterParameters\">) <span class=\"SHKeyword\">const</span></td></tr></table></div><div class=\"TTSummary\">Calculates the Fletcher checksum (position dependent checksum) on the ByteStream</div></div>",9451:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype9451\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">uint32</span> calculateCrcChecksum(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PModifierQualifier first\">std::</td><td class=\"PType\">size_t&nbsp;</td><td class=\"PName last\">from,</td></tr><tr><td class=\"PModifierQualifier first\">std::</td><td class=\"PType\">size_t&nbsp;</td><td class=\"PName last\">to</td></tr></table></td><td class=\"PAfterParameters\">) <span class=\"SHKeyword\">const</span></td></tr></table></div><div class=\"TTSummary\">Calculates the 32-bit CRC with polynomial 0x04C11DB7, an initial value of 0xFFFFFFFF, and inverted output.</div></div>",9452:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype9452\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">uint32</span> calculateCrcChecksum() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Calculates the 32-bit CRC with polynomial 0x04C11DB7, an initial value of 0xFFFFFFFF, and inverted output.</div></div>",9453:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype9453\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">void</span> verifyBytesInStream(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PModifierQualifier first\">std::</td><td class=\"PType\">size_t&nbsp;</td><td class=\"PName last\">position,</td></tr><tr><td class=\"PModifierQualifier first\">std::</td><td class=\"PType\">size_t&nbsp;</td><td class=\"PName last\">length</td></tr></table></td><td class=\"PAfterParameters\">) <span class=\"SHKeyword\">const</span></td></tr></table></div><div class=\"TTSummary\">Checks that the current bytestream can read the requested data</div></div>"});