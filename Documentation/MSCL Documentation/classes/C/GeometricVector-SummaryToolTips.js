NDSummary.OnToolTipsLoaded("CClass:GeometricVector",{1843:"<div class=\"NDToolTip TClass LC\"><div class=\"NDClassPrototype\" id=\"NDClassPrototype1843\"><div class=\"CPEntry TClass Current\"><div class=\"CPName\">GeometricVector</div></div></div><div class=\"TTSummary\">Defines a 3 dimensional, spatial vector.</div></div>",1845:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype1845\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">static</span> GeometricVector VectorECEF(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PType first\"><span class=\"SHKeyword\">float</span>&nbsp;</td><td class=\"PName last\">x_init,</td></tr><tr><td class=\"PType first\"><span class=\"SHKeyword\">float</span>&nbsp;</td><td class=\"PName last\">y_init,</td></tr><tr><td class=\"PType first\"><span class=\"SHKeyword\">float</span>&nbsp;</td><td class=\"PName last\">z_init</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Initializes and returns a new vector with the reference frame set to Earth-Centered, Earth-Fixed</div></div>",1846:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype1846\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">static</span> GeometricVector VectorNED(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PType first\"><span class=\"SHKeyword\">float</span>&nbsp;</td><td class=\"PName last\">north,</td></tr><tr><td class=\"PType first\"><span class=\"SHKeyword\">float</span>&nbsp;</td><td class=\"PName last\">east,</td></tr><tr><td class=\"PType first\"><span class=\"SHKeyword\">float</span>&nbsp;</td><td class=\"PName last\">down</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Initializes and returns a new vector with the reference frame set to North-East-Down</div></div>",1847:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype1847\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\">GeometricVector(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PType first\"><span class=\"SHKeyword\">float</span>&nbsp;</td><td class=\"PName\">x_init,</td><td></td><td class=\"last\"></td></tr><tr><td class=\"PType first\"><span class=\"SHKeyword\">float</span>&nbsp;</td><td class=\"PName\">y_init,</td><td></td><td class=\"last\"></td></tr><tr><td class=\"PType first\"><span class=\"SHKeyword\">float</span>&nbsp;</td><td class=\"PName\">z_init,</td><td></td><td class=\"last\"></td></tr><tr><td class=\"PType first\">PositionVelocityReferenceFrame&nbsp;</td><td class=\"PName\">ref&nbsp;</td><td class=\"PDefaultValueSeparator\">=&nbsp;</td><td class=\"PDefaultValue last\">PositionVelocityReferenceFrame::ECEF</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Creates a GeometricVector object.</div></div>",1848:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype1848\" class=\"NDPrototype NoParameterForm\">GeometricVector()</div><div class=\"TTSummary\">Creates a zero-filled GeometricVector object.&nbsp; Default reference frame: ECEF</div></div>",1849:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype1849\" class=\"NDPrototype NoParameterForm\">~GeometricVector()</div><div class=\"TTSummary\">Destroys a TimeUpdate object.</div></div>",1851:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype1851\" class=\"NDPrototype NoParameterForm\">PositionVelocityReferenceFrame referenceFrame</div><div class=\"TTSummary\">The &lt;PositionVelocityReferenceFrame&gt; of this vector.&nbsp; Default: ECEF</div></div>",1853:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype1853\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">float</span> x() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Only valid if referenceFrame is ECEF</div></div>",1854:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype1854\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">float</span> y() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Only valid if referenceFrame is ECEF</div></div>",1855:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype1855\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">float</span> z() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Only valid if referenceFrame is ECEF</div></div>",1856:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype1856\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">float</span> north() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Only valid if referenceFrame is LLH_NED</div></div>",1857:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype1857\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">float</span> east() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Only valid if referenceFrame is LLH_NED</div></div>",1858:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype1858\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">float</span> down() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Only valid if referenceFrame is LLH_NED</div></div>",1860:"<div class=\"NDToolTip TVariable LC\"><div class=\"TTSummary\">The vector values.</div></div>",1862:"<div class=\"NDToolTip TType LC\"><div class=\"TTSummary\">A vector of GeometricVector objects</div></div>"});