NDSummary.OnToolTipsLoaded("CClass:DataBuffer",{9814:"<div class=\"NDToolTip TClass LC\"><div class=\"NDClassPrototype\" id=\"NDClassPrototype9814\"><div class=\"CPEntry TClass Current\"><div class=\"CPName\">DataBuffer</div></div></div><div class=\"TTSummary\">A buffer of bytes extending from the ByteStream class that is used for holding bytes read in from the connection</div></div>",9816:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype9816\" class=\"NDPrototype NoParameterForm\">ByteStream m_data</div><div class=\"TTSummary\">The underlying ByteStream that holds the data</div></div>",9817:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype9817\" class=\"NDPrototype NoParameterForm\">std::size_t m_appendPosition</div><div class=\"TTSummary\">The current position to use when appending data to the buffer</div></div>",9818:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype9818\" class=\"NDPrototype NoParameterForm\">std::size_t m_readPosition</div><div class=\"TTSummary\">The current position in the buffer for reading data</div></div>",9820:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype9820\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">explicit</span> DataBuffer(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PType first\"><span class=\"SHKeyword\">uint32</span>&nbsp;</td><td class=\"PName last\">size</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Constructor to create a DataBuffer object</div></div>",9821:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype9821\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">explicit</span> DataBuffer(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PModifierQualifier first\"><span class=\"SHKeyword\">const</span>&nbsp;</td><td class=\"PType\">Bytes&nbsp;</td><td class=\"PNamePrefix\">&amp;</td><td class=\"PName last\">data</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Constructor to create a DataBuffer object given existing data as Bytes</div></div>",9822:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype9822\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">explicit</span> DataBuffer(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PModifierQualifier first\"><span class=\"SHKeyword\">const</span>&nbsp;</td><td class=\"PType\">ByteStream&nbsp;</td><td class=\"PNamePrefix\">&amp;</td><td class=\"PName last\">data</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Constructor to create a DataBuffer given an existing ByteStream</div></div>",9823:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype9823\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">virtual</span> ~DataBuffer()</div><div class=\"TTSummary\">Default destructor for the DataBuffer object</div></div>",9824:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype9824\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">uint8</span> peekByte()</div><div class=\"TTSummary\">Gets the next byte from the buffer without moving the read position</div></div>",9825:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype9825\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">void</span> skipBytes(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PModifierQualifier first\">std::</td><td class=\"PType\">size_t&nbsp;</td><td class=\"PName last\">numBytesToSkip</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Moves the read pointer forward the requested number of bytes</div></div>",9826:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype9826\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">int8</span> read_int8()</div><div class=\"TTSummary\">Reads the next 1-byte signed integer from the buffer</div></div>",9827:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype9827\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">uint8</span> read_uint8()</div><div class=\"TTSummary\">Reads the next 1-byte unsigned integer from the buffer</div></div>",9828:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype9828\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">int16</span> read_int16()</div><div class=\"TTSummary\">Reads the next 2-byte signed integer from the buffer</div></div>",9829:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype9829\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">uint16</span> read_uint16()</div><div class=\"TTSummary\">Reads the next 2-byte unsigned integer from the buffer</div></div>",9830:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype9830\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">uint32</span> read_uint32()</div><div class=\"TTSummary\">Reads the next 4-byte unsigned integer from the buffer</div></div>",9831:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype9831\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">uint64</span> read_uint64()</div><div class=\"TTSummary\">Reads the next 8-byte unsigned integer from the buffer</div></div>",9832:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype9832\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">float</span> read_float()</div><div class=\"TTSummary\">Reads the next 4-byte float from the buffer</div></div>",9833:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype9833\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">double</span> read_double()</div><div class=\"TTSummary\">Reads the next 8-byte double from the buffer</div></div>",9834:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype9834\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\">std::<span class=\"SHKeyword\">string</span> read_string(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PModifierQualifier first\">std::</td><td class=\"PType\">size_t&nbsp;</td><td class=\"PName last\">length</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Reads a string of the specified length from the buffer</div></div>",9835:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype9835\" class=\"NDPrototype NoParameterForm\">std::size_t size() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Gets the amount of bytes in the DataBuffer</div></div>",9837:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype9837\" class=\"NDPrototype NoParameterForm\">std::size_t appendPosition() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Gets the append position of the buffer.</div></div>",9838:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype9838\" class=\"NDPrototype NoParameterForm\">std::size_t readPosition() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Gets the read position of the buffer.</div></div>",9839:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype9839\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">bool</span> moreToRead() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Gets whether or not there are more bytes to be read in the DataBuffer</div></div>",9840:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype9840\" class=\"NDPrototype NoParameterForm\">std::size_t shiftExtraToStart()</div><div class=\"TTSummary\">Copies any unparsed data in the DataBuffer to the front of the buffer.&nbsp; Also resets the readPosition and moves the appendPosition to immediately after the data that was moved.</div></div>",9841:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype9841\" class=\"NDPrototype NoParameterForm\">BufferWriter getBufferWriter()</div><div class=\"TTSummary\">Creates a BufferWriter object based on this DataBuffer.</div></div>",9842:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype9842\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">void</span> resetBuffer()</div><div class=\"TTSummary\">Resets the append and read positions in the buffer back to 0.</div></div>",9843:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype9843\" class=\"NDPrototype NoParameterForm\">Bytes bytesToRead() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Gets a copy of the underlying bytes in this DataBuffer from the read position to the appendPosition.</div></div>",9844:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype9844\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\">Bytes bytesToRead(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PModifierQualifier first\">std::</td><td class=\"PType\">size_t&nbsp;</td><td class=\"PName last\">startPos,</td></tr><tr><td class=\"PModifierQualifier first\">std::</td><td class=\"PType\">size_t&nbsp;</td><td class=\"PName last\">size</td></tr></table></td><td class=\"PAfterParameters\">) <span class=\"SHKeyword\">const</span></td></tr></table></div><div class=\"TTSummary\">Gets a copy of the underlying bytes in this DataBuffer from the given start position, for the given size.</div></div>"});