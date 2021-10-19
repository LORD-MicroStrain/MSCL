NDSummary.OnToolTipsLoaded("CClass:MipDataPacket",{2421:"<div class=\"NDToolTip TClass LC\"><div class=\"NDClassPrototype\" id=\"NDClassPrototype2421\"><div class=\"CPEntry TClass Current\"><div class=\"CPName\">MipDataPacket</div></div></div><div class=\"TTSummary\">A Mip Data Packet that contains both valid and invalid data from a MIP Device.</div></div>",2423:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype2423\" class=\"NDPrototype NoParameterForm\">MipDataPacket()</div><div class=\"TTSummary\">Creates a default constructed MipDataPacket</div></div>",2424:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype2424\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">explicit</span> MipDataPacket(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PModifierQualifier first\"><span class=\"SHKeyword\">const</span>&nbsp;</td><td class=\"PType\">MipPacket&nbsp;</td><td class=\"PNamePrefix\">&amp;</td><td class=\"PName last\">packet</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Creates a MipDataPacket object</div></div>",2426:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype2426\" class=\"NDPrototype NoParameterForm\">MipDataFields m_dataFields</div><div class=\"TTSummary\">The MipDataFields that are contained within this packet</div></div>",2427:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype2427\" class=\"NDPrototype NoParameterForm\">MipDataPoints m_points</div><div class=\"TTSummary\">The MipDataPoints within this packet</div></div>",2428:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype2428\" class=\"NDPrototype NoParameterForm\">Timestamp m_collectedTime</div><div class=\"TTSummary\">The Timestamp of when this packet was received</div></div>",2429:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype2429\" class=\"NDPrototype NoParameterForm\">Timestamp m_deviceTime</div><div class=\"TTSummary\">The timestamp that was provided by the Node in the data packet</div></div>",2430:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype2430\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">bool</span> m_hasDeviceTime</div><div class=\"TTSummary\">Whether the device timestamp was included in the data packet.</div></div>",2431:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype2431\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">bool</span> m_deviceTimeValid</div><div class=\"TTSummary\">Whether the device timestamp is valid or not (based on flags and/or it being a reasonable timestamp)</div></div>",2432:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype2432\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">uint16</span> m_deviceTimeFlags</div><div class=\"TTSummary\">The flags value that the device timestamp was transmitted with.</div></div>",2434:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype2434\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">void</span> parseDataFields()</div><div class=\"TTSummary\">Parses the passed in MipPacket for all the field information and adds a data field to the MipDataFields container Also parses out all the MipDataPoints in the fields that were created and adds them to m_points</div></div>",2435:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype2435\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">void</span> parsePointsInField(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PModifierQualifier first\"><span class=\"SHKeyword\">const</span>&nbsp;</td><td class=\"PType\">MipDataField&nbsp;</td><td class=\"PNamePrefix\">&amp;</td><td class=\"PName last\">field</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Parses an MipDataField for MipDataPoints and puts them into m_points</div></div>",2436:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype2436\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">void</span> parseTimeStamp(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PModifierQualifier first\"><span class=\"SHKeyword\">const</span>&nbsp;</td><td class=\"PType\">MipDataField&nbsp;</td><td class=\"PNamePrefix\">&amp;</td><td class=\"PName last\">field</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Parses a MIP timestamp field, and sets the device time member variables.</div></div>",2437:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype2437\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">bool</span> timestampWithinRange(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PModifierQualifier first\"><span class=\"SHKeyword\">const</span>&nbsp;</td><td class=\"PType\">Timestamp&nbsp;</td><td class=\"PNamePrefix\">&amp;</td><td class=\"PName last\">timestamp</td></tr></table></td><td class=\"PAfterParameters\">) <span class=\"SHKeyword\">const</span></td></tr></table></div><div class=\"TTSummary\">Checks if the given timestamp is within range of the collectedTimestamp.</div></div>",2438:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype2438\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">const</span> MipDataPoints&amp; data() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Gets all the MipDataPoints that are contained within this packet.</div></div>",2439:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype2439\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">const</span> Timestamp&amp; collectedTimestamp() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Gets the Timestamp representing when the packet was collected by MSCL.</div></div>",2440:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype2440\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">const</span> Timestamp&amp; deviceTimestamp() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Gets the Timestamp which was transmitted in the Mip Data Packet as a channel field.&nbsp; Note: This will return a Timestamp of 0 if deviceTimeValid returns false.</div></div>",2441:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype2441\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">bool</span> hasDeviceTime() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Whether the data packet had a Timestamp field included in it.</div></div>",2442:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype2442\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">bool</span> deviceTimeValid() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Whether the Timestamp field sent from the device is valid or not.</div></div>",2443:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype2443\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">uint16</span> deviceTimeFlags() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Gets the timestamp flags that were transmitted in the Mip Data Packet.&nbsp; Note: This will return 0 if deviceTimeValid returns false.</div></div>",2445:"<div class=\"NDToolTip TType LC\"><div class=\"TTSummary\">Typedef for a vector of MipDataPacket objects.</div></div>"});