NDSummary.OnToolTipsLoaded("File:Timestamp.h",{8595:"<div class=\"NDToolTip TClass LC\"><div class=\"NDClassPrototype\" id=\"NDClassPrototype8595\"><div class=\"CPEntry TClass Current\"><div class=\"CPName\">Timestamp</div></div></div><div class=\"TTSummary\">Represents a date/time object</div></div>",8597:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype8597\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">explicit</span> Timestamp(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PType first\"><span class=\"SHKeyword\">uint64</span>&nbsp;</td><td class=\"PName\">nanoseconds</td><td class=\"PDefaultValueSeparator\">=&nbsp;</td><td class=\"PDefaultValue last\"><span class=\"SHNumber\">0</span></td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Creates a Timestamp object based on the nanoseconds parameter</div></div>",8598:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype8598\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\">Timestamp(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PType first\"><span class=\"SHKeyword\">uint16</span>&nbsp;</td><td class=\"PName last\">year,</td></tr><tr><td class=\"PType first\"><span class=\"SHKeyword\">uint16</span>&nbsp;</td><td class=\"PName last\">month,</td></tr><tr><td class=\"PType first\"><span class=\"SHKeyword\">uint16</span>&nbsp;</td><td class=\"PName last\">day,</td></tr><tr><td class=\"PType first\"><span class=\"SHKeyword\">uint16</span>&nbsp;</td><td class=\"PName last\">hour,</td></tr><tr><td class=\"PType first\"><span class=\"SHKeyword\">uint16</span>&nbsp;</td><td class=\"PName last\">minute,</td></tr><tr><td class=\"PType first\"><span class=\"SHKeyword\">uint16</span>&nbsp;</td><td class=\"PName last\">second,</td></tr><tr><td class=\"PType first\"><span class=\"SHKeyword\">uint32</span>&nbsp;</td><td class=\"PName last\">milli</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Creates a Timestamp object from the given year, month, day, hour, minute, second, millisecond parameters</div></div>",8600:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype8600\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">uint64</span> m_nanoseconds</div><div class=\"TTSummary\">The number of nanoseconds since the unix epoch</div></div>",8601:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype8601\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">static uint8</span> s_gpsLeapSeconds</div><div class=\"TTSummary\">The (hardcoded) number of leap seconds since Jan 1 1980, used in converting GPS timestamps to UTC timestamps.</div></div>",8603:"<div class=\"NDToolTip TOperator LC\"><div class=\"TTSummary\">Gets the TimeSpan representing the distance (always positive) between two Timestamps.</div></div>",8604:"<div class=\"NDToolTip TOperator LC\"><div class=\"TTSummary\">Equal operator for comparing Timestamps.</div></div>",8605:"<div class=\"NDToolTip TOperator LC\"><div class=\"TTSummary\">Not Equal operator for comparing Timestamps.</div></div>",8606:"<div class=\"NDToolTip TOperator LC\"><div class=\"TTSummary\">Less Than operator for comparing Timestamps.</div></div>",8607:"<div class=\"NDToolTip TOperator LC\"><div class=\"TTSummary\">Less Than or Equal To operator for comparing Timestamps.</div></div>",8608:"<div class=\"NDToolTip TOperator LC\"><div class=\"TTSummary\">Greater Than operator for comparing Timestamps.</div></div>",8609:"<div class=\"NDToolTip TOperator LC\"><div class=\"TTSummary\">Greater Than or Equal To operator for comparing Timestamps.</div></div>",8611:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype8611\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">uint64</span> nanoseconds() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Gets the number of nanoseconds since the unix epoch</div></div>",8612:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype8612\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">uint64</span> seconds() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Gets the number of seconds since the unix epoch</div></div>",8613:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype8613\" class=\"NDPrototype NoParameterForm\">std::<span class=\"SHKeyword\">string</span> str() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Gets a string representation of the Timestamp object in ISO 8601 Date/Time format.</div></div>",8614:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype8614\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">void</span> setTime(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PType first\"><span class=\"SHKeyword\">uint64</span>&nbsp;</td><td class=\"PName last\">nanosSinceEpoch</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Updates the Timestamp to the given number of nanoseconds since the unix epoch.</div></div>",8615:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype8615\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">void</span> setTimeNow()</div><div class=\"TTSummary\">Sets the Timestamp object to the current system time in UTC</div></div>",8616:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype8616\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">static</span> Timestamp timeNow()</div><div class=\"TTSummary\">Creates a timestamp using the current system time</div></div>",8617:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype8617\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">static void</span> setLeapSeconds(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PType first\"><span class=\"SHKeyword\">uint8</span>&nbsp;</td><td class=\"PName last\">gpsLeapSeconds</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Adjusts the hardcoded number of leap seconds since Jan 1 1980, used in converting GPS timestamps to UTC timestamps.&nbsp; Note: New releases of MSCL should be available when the leap seconds change. You can also adjust this value yourself to correct your current version of MSCL without updating.</div></div>",8618:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype8618\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">static uint8</span> getLeapSeconds()</div><div class=\"TTSummary\">Gets the current number of leap seconds since Jan 1 1980, used in converting GPS timestamps to UTC timestamps.</div></div>",8619:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype8619\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">static uint64</span> gpsTimeToUtcTime(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PType first\"><span class=\"SHKeyword\">double</span>&nbsp;</td><td class=\"PName last\">timeOfWeek,</td></tr><tr><td class=\"PType first\"><span class=\"SHKeyword\">uint16</span>&nbsp;</td><td class=\"PName last\">weekNumber</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Converts the gps time into the UTC time in nanoseconds since the unix epoch.&nbsp; Note: this uses the value stored in &lt;Utils::gpsLeapSeconds&gt; in its conversion.</div></div>"});