NDSummary.OnToolTipsLoaded("CClass:Position",{2108:"<div class=\"NDToolTip TStruct LC\"><div class=\"TTSummary\">Defines a geographic position.</div></div>",2110:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype2110\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">static</span> Position PositionLLH(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PType first\"><span class=\"SHKeyword\">double</span>&nbsp;</td><td class=\"PName last\">lat_init,</td></tr><tr><td class=\"PType first\"><span class=\"SHKeyword\">double</span>&nbsp;</td><td class=\"PName last\">long_init,</td></tr><tr><td class=\"PType first\"><span class=\"SHKeyword\">double</span>&nbsp;</td><td class=\"PName last\">alt_init</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Creates a Position object with the reference frame set to LLH</div></div>",2111:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype2111\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">static</span> Position PositionECEF(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PType first\"><span class=\"SHKeyword\">double</span>&nbsp;</td><td class=\"PName last\">x_init,</td></tr><tr><td class=\"PType first\"><span class=\"SHKeyword\">double</span>&nbsp;</td><td class=\"PName last\">y_init,</td></tr><tr><td class=\"PType first\"><span class=\"SHKeyword\">double</span>&nbsp;</td><td class=\"PName last\">z_init</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Creates a Position object with the reference frame set to ECEF</div></div>",2112:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype2112\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\">Position(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PType first\"><span class=\"SHKeyword\">double</span>&nbsp;</td><td class=\"PName\">lat_init,</td><td></td><td class=\"last\"></td></tr><tr><td class=\"PType first\"><span class=\"SHKeyword\">double</span>&nbsp;</td><td class=\"PName\">long_init,</td><td></td><td class=\"last\"></td></tr><tr><td class=\"PType first\"><span class=\"SHKeyword\">double</span>&nbsp;</td><td class=\"PName\">alt_init,</td><td></td><td class=\"last\"></td></tr><tr><td class=\"PType first\">PositionVelocityReferenceFrame&nbsp;</td><td class=\"PName\">ref&nbsp;</td><td class=\"PDefaultValueSeparator\">=&nbsp;</td><td class=\"PDefaultValue last\">PositionVelocityReferenceFrame::LLH_NED</td></tr></table></td><td class=\"PAfterParameters\">) : position_0(lat_init), position_1(long_init), position_2(alt_init), referenceFrame(<span class=\"SHKeyword\">ref</span>)</td></tr></table></div><div class=\"TTSummary\">Creates a Position object.</div></div>",2113:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype2113\" class=\"NDPrototype NoParameterForm\">Position() : position_0(<span class=\"SHNumber\">0</span>), position_1(<span class=\"SHNumber\">0</span>), position_2(<span class=\"SHNumber\">0</span>), referenceFrame(PositionVelocityReferenceFrame::LLH_NED)</div><div class=\"TTSummary\">Creates a zero-filled Position object.&nbsp; Default reference frame: LLH</div></div>",2114:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype2114\" class=\"NDPrototype NoParameterForm\">~Position()</div><div class=\"TTSummary\">Destroys a TimeUpdate object.</div></div>",2116:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype2116\" class=\"NDPrototype NoParameterForm\">PositionVelocityReferenceFrame referenceFrame</div><div class=\"TTSummary\">The &lt;PositionVelocityReferenceFrame&gt; of this position.&nbsp; Default: LLH</div></div>",2118:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype2118\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">double</span> latitude() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Only valid if referenceFrame is LLH_NED</div></div>",2119:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype2119\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">double</span> longitude() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Only valid if referenceFrame is LLH_NED</div></div>",2120:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype2120\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">double</span> altitude() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Only valid if referenceFrame is LLH_NED</div></div>",2121:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype2121\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">double</span> x() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Only valid if referenceFrame is ECEF</div></div>",2122:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype2122\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">double</span> y() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Only valid if referenceFrame is ECEF</div></div>",2123:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype2123\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">double</span> z() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Only valid if referenceFrame is ECEF</div></div>",2125:"<div class=\"NDToolTip TVariable LC\"><div class=\"TTSummary\">The position values</div></div>"});