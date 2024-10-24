NDSummary.OnToolTipsLoaded("File:MicroStrain/Inertial/PositionVelocity.h",{1415:"<div class=\"NDToolTip TVariable LC\"><div class=\"TTSummary\">The vector values.</div></div>",1417:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype1417\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\">Vec3f(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PType first\"><span class=\"SHKeyword\">float</span>&nbsp;</td><td class=\"PName last\">x,</td></tr><tr><td class=\"PType first\"><span class=\"SHKeyword\">float</span>&nbsp;</td><td class=\"PName last\">y,</td></tr><tr><td class=\"PType first\"><span class=\"SHKeyword\">float</span>&nbsp;</td><td class=\"PName last\">z</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Creates a Vec3f object.</div></div>",1418:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype1418\" class=\"NDPrototype NoParameterForm\">Vec3f()</div><div class=\"TTSummary\">Creates a zero-filled Vec3f object.</div></div>",1419:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype1419\" class=\"NDPrototype NoParameterForm\">~Vec3f()</div></div>",1420:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype1420\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">float</span> x() <span class=\"SHKeyword\">const</span></div></div>",1421:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype1421\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">float</span> y() <span class=\"SHKeyword\">const</span></div></div>",1422:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype1422\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">float</span> z() <span class=\"SHKeyword\">const</span></div></div>",1424:"<div class=\"NDToolTip TEnumeration LC\"><div class=\"TTSummary\">Enum representing position and velocity reference frame options.</div></div>",1429:"<div class=\"NDToolTip TClass LC\"><div class=\"NDClassPrototype\" id=\"NDClassPrototype1429\"><div class=\"CPEntry TClass Current\"><div class=\"CPName\">GeometricVector</div></div></div><div class=\"TTSummary\">Defines a 3 dimensional, spatial vector.</div></div>",1431:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype1431\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">static</span> GeometricVector VectorECEF(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PType first\"><span class=\"SHKeyword\">float</span>&nbsp;</td><td class=\"PName last\">x_init,</td></tr><tr><td class=\"PType first\"><span class=\"SHKeyword\">float</span>&nbsp;</td><td class=\"PName last\">y_init,</td></tr><tr><td class=\"PType first\"><span class=\"SHKeyword\">float</span>&nbsp;</td><td class=\"PName last\">z_init</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Initializes and returns a new vector with the reference frame set to Earth-Centered, Earth-Fixed</div></div>",1432:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype1432\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">static</span> GeometricVector VectorNED(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PType first\"><span class=\"SHKeyword\">float</span>&nbsp;</td><td class=\"PName last\">north,</td></tr><tr><td class=\"PType first\"><span class=\"SHKeyword\">float</span>&nbsp;</td><td class=\"PName last\">east,</td></tr><tr><td class=\"PType first\"><span class=\"SHKeyword\">float</span>&nbsp;</td><td class=\"PName last\">down</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Initializes and returns a new vector with the reference frame set to North-East-Down</div></div>",1433:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype1433\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\">GeometricVector(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PType first\"><span class=\"SHKeyword\">float</span>&nbsp;</td><td class=\"PName\">x_init,</td><td></td><td class=\"last\"></td></tr><tr><td class=\"PType first\"><span class=\"SHKeyword\">float</span>&nbsp;</td><td class=\"PName\">y_init,</td><td></td><td class=\"last\"></td></tr><tr><td class=\"PType first\"><span class=\"SHKeyword\">float</span>&nbsp;</td><td class=\"PName\">z_init,</td><td></td><td class=\"last\"></td></tr><tr><td class=\"PType first\">PositionVelocityReferenceFrame&nbsp;</td><td class=\"PName\">ref&nbsp;</td><td class=\"PDefaultValueSeparator\">=&nbsp;</td><td class=\"PDefaultValue last\">PositionVelocityReferenceFrame::ECEF</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Creates a GeometricVector object.</div></div>",1434:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype1434\" class=\"NDPrototype NoParameterForm\">GeometricVector()</div><div class=\"TTSummary\">Creates a zero-filled GeometricVector object.&nbsp; Default reference frame: ECEF</div></div>",1435:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype1435\" class=\"NDPrototype NoParameterForm\">~GeometricVector()</div><div class=\"TTSummary\">Destroys a TimeUpdate object.</div></div>",1437:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype1437\" class=\"NDPrototype NoParameterForm\">PositionVelocityReferenceFrame referenceFrame</div><div class=\"TTSummary\">The PositionVelocityReferenceFrame of this vector.&nbsp; Default: ECEF</div></div>",1439:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype1439\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">float</span> north() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Only valid if referenceFrame is LLH_NED</div></div>",1440:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype1440\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">float</span> east() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Only valid if referenceFrame is LLH_NED</div></div>",1441:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype1441\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">float</span> down() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Only valid if referenceFrame is LLH_NED</div></div>",1442:"<div class=\"NDToolTip TClass LC\"><div class=\"NDClassPrototype\" id=\"NDClassPrototype1442\"><div class=\"CPEntry TClass Current\"><div class=\"CPName\">PositionOffset</div></div></div><div class=\"TTSummary\">Represents a position offset (x, y, z).</div></div>",1443:"<div class=\"NDToolTip TClass LC\"><div class=\"NDClassPrototype\" id=\"NDClassPrototype1443\"><div class=\"CPEntry TClass Current\"><div class=\"CPName\">Velocity</div></div></div><div class=\"TTSummary\">Represents a velocity (x, y, z).</div></div>",1445:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype1445\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">static</span> Velocity ECEF(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PType first\"><span class=\"SHKeyword\">float</span>&nbsp;</td><td class=\"PName last\">x_init,</td></tr><tr><td class=\"PType first\"><span class=\"SHKeyword\">float</span>&nbsp;</td><td class=\"PName last\">y_init,</td></tr><tr><td class=\"PType first\"><span class=\"SHKeyword\">float</span>&nbsp;</td><td class=\"PName last\">z_init</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Creates a Velocity vectory with the reference frame set to Earth-Centered, Earth-Fixed</div></div>",1446:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype1446\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">static</span> Velocity NED(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PType first\"><span class=\"SHKeyword\">float</span>&nbsp;</td><td class=\"PName last\">north,</td></tr><tr><td class=\"PType first\"><span class=\"SHKeyword\">float</span>&nbsp;</td><td class=\"PName last\">east,</td></tr><tr><td class=\"PType first\"><span class=\"SHKeyword\">float</span>&nbsp;</td><td class=\"PName last\">down</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Creates a Velocity vector with the reference frame set to North-East-Down</div></div>",1447:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype1447\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">static</span> Velocity Vehicle(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PType first\"><span class=\"SHKeyword\">float</span>&nbsp;</td><td class=\"PName last\">x,</td></tr><tr><td class=\"PType first\"><span class=\"SHKeyword\">float</span>&nbsp;</td><td class=\"PName last\">y,</td></tr><tr><td class=\"PType first\"><span class=\"SHKeyword\">float</span>&nbsp;</td><td class=\"PName last\">z</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Creates a Velocity vector with the reference frame set to Vehicle</div></div>",1449:"<div class=\"NDToolTip TType LC\"><div class=\"TTSummary\">A vector of GeometricVector objects</div></div>",1450:"<div class=\"NDToolTip TStruct LC\"><div class=\"TTSummary\">Defines a geographic position.</div></div>",1452:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype1452\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">static</span> Position LLH(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PType first\"><span class=\"SHKeyword\">double</span>&nbsp;</td><td class=\"PName last\">lat_init,</td></tr><tr><td class=\"PType first\"><span class=\"SHKeyword\">double</span>&nbsp;</td><td class=\"PName last\">long_init,</td></tr><tr><td class=\"PType first\"><span class=\"SHKeyword\">double</span>&nbsp;</td><td class=\"PName last\">alt_init</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Creates a Position object with the reference frame set to LLH</div></div>",1453:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype1453\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">static</span> Position ECEF(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PType first\"><span class=\"SHKeyword\">double</span>&nbsp;</td><td class=\"PName last\">x_init,</td></tr><tr><td class=\"PType first\"><span class=\"SHKeyword\">double</span>&nbsp;</td><td class=\"PName last\">y_init,</td></tr><tr><td class=\"PType first\"><span class=\"SHKeyword\">double</span>&nbsp;</td><td class=\"PName last\">z_init</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Creates a Position object with the reference frame set to ECEF</div></div>",1454:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype1454\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\">Position(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PType first\"><span class=\"SHKeyword\">double</span>&nbsp;</td><td class=\"PName\">lat_init,</td><td></td><td class=\"last\"></td></tr><tr><td class=\"PType first\"><span class=\"SHKeyword\">double</span>&nbsp;</td><td class=\"PName\">long_init,</td><td></td><td class=\"last\"></td></tr><tr><td class=\"PType first\"><span class=\"SHKeyword\">double</span>&nbsp;</td><td class=\"PName\">alt_init,</td><td></td><td class=\"last\"></td></tr><tr><td class=\"PType first\">PositionVelocityReferenceFrame&nbsp;</td><td class=\"PName\">ref&nbsp;</td><td class=\"PDefaultValueSeparator\">=&nbsp;</td><td class=\"PDefaultValue last\">PositionVelocityReferenceFrame::LLH_NED</td></tr></table></td><td class=\"PAfterParameters\">) : position_0(lat_init), position_1(long_init), position_2(alt_init), referenceFrame(<span class=\"SHKeyword\">ref</span>)</td></tr></table></div><div class=\"TTSummary\">Creates a Position object.</div></div>",1455:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype1455\" class=\"NDPrototype NoParameterForm\">Position() : position_0(<span class=\"SHNumber\">0</span>), position_1(<span class=\"SHNumber\">0</span>), position_2(<span class=\"SHNumber\">0</span>), referenceFrame(PositionVelocityReferenceFrame::LLH_NED)</div><div class=\"TTSummary\">Creates a zero-filled Position object.&nbsp; Default reference frame: LLH</div></div>",1456:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype1456\" class=\"NDPrototype NoParameterForm\">~Position()</div><div class=\"TTSummary\">Destroys a TimeUpdate object.</div></div>",1458:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype1458\" class=\"NDPrototype NoParameterForm\">PositionVelocityReferenceFrame referenceFrame</div><div class=\"TTSummary\">The PositionVelocityReferenceFrame of this position.&nbsp; Default: LLH</div></div>",1460:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype1460\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">double</span> latitude() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Only valid if referenceFrame is LLH_NED</div></div>",1461:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype1461\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">double</span> longitude() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Only valid if referenceFrame is LLH_NED</div></div>",1462:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype1462\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">double</span> altitude() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Only valid if referenceFrame is LLH_NED</div></div>",1463:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype1463\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">double</span> height() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Only valid if referenceFrame is LLH_NED</div></div>",1464:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype1464\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">double</span> x() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Only valid if referenceFrame is ECEF</div></div>",1465:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype1465\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">double</span> y() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Only valid if referenceFrame is ECEF</div></div>",1466:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype1466\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">double</span> z() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Only valid if referenceFrame is ECEF</div></div>",1468:"<div class=\"NDToolTip TVariable LC\"><div class=\"TTSummary\">The position values</div></div>",1469:"<div class=\"NDToolTip TClass LC\"><div class=\"NDClassPrototype\" id=\"NDClassPrototype1469\"><div class=\"CPEntry TClass Current\"><div class=\"CPName\">GeometricUncertainty</div></div></div><div class=\"TTSummary\">Represents uncertainty values correlating to a position or velocity.</div></div>"});