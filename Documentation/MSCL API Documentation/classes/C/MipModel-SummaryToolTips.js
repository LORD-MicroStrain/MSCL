NDSummary.OnToolTipsLoaded("CClass:MipModel",{2031:"<div class=\"NDToolTip TClass LC\"><div class=\"NDClassPrototype\" id=\"NDClassPrototype2031\"><div class=\"CPEntry TClass Current\"><div class=\"CPName\">MipModel</div></div></div><div class=\"TTSummary\">Contains the model information of MIP devices.</div></div>",2032:"<div class=\"NDToolTip TConstant LC\"><div class=\"TTSummary\">Constant MipModel object definitions for each known MIP device.&nbsp; Most models have 9999 placeholder modifier values because there is no significant interface difference between the different versions of the same base model.&nbsp; This placeholder value will match to any modifier value read from the device when comparing MipModel objects.</div></div>",2033:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype2033\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\">MipModel(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PModifierQualifier first\"><span class=\"SHKeyword\">const</span> std::</td><td class=\"PType\"><span class=\"SHKeyword\">string</span>&nbsp;</td><td class=\"PNamePrefix\">&amp;</td><td class=\"PName last\">modelNumberStr</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Creates a MipModel object from the model string read from a MIP device (inertial, RTK)</div></div>",2034:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype2034\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\">MipModel(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PModifierQualifier first\"><span class=\"SHKeyword\">const</span>&nbsp;</td><td class=\"PType\">MipModel&nbsp;</td><td class=\"PNamePrefix\">&amp;</td><td class=\"PName last\">copy</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Creates a MipModel object based on another MipModel object</div></div>",2035:"<div class=\"NDToolTip TOperator LC\"><div class=\"TTSummary\">Define == behavior when comparing two MipModel objects (functionally the same as MipModel::equals()).</div></div>",2036:"<div class=\"NDToolTip TOperator LC\"><div class=\"TTSummary\">Define != behavior when comparing two MipModel objects (functionally the same as MipModel::equals()).</div></div>",2037:"<div class=\"NDToolTip TOperator LC\"><div class=\"TTSummary\">Define == behavior when comparing two MipModel objects (functionally the same as MipModel::equals()).</div></div>",2038:"<div class=\"NDToolTip TOperator LC\"><div class=\"TTSummary\">Define != behavior when comparing two MipModel objects (functionally the same as MipModel::equals()).</div></div>",2039:"<div class=\"NDToolTip TOperator LC\"><div class=\"TTSummary\">Define behavior when casting a MipModel to std::string (funtionally the same as MipModel::str()).</div></div>",2040:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype2040\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">bool</span> equals(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PModifierQualifier first\"><span class=\"SHKeyword\">const</span>&nbsp;</td><td class=\"PType\">MipModel&nbsp;</td><td class=\"PNamePrefix\">&amp;</td><td class=\"PName last\">compare</td></tr></table></td><td class=\"PAfterParameters\">) <span class=\"SHKeyword\">const</span></td></tr></table></div><div class=\"TTSummary\">Function to compare two MipModel objects for equality (functionally the same as overloaded == operator).</div></div>",2041:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype2041\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">const</span> std::<span class=\"SHKeyword\">string</span> str() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Get the model string formatted as it would be read from the device (ex: 6284-4220) (funtionally the same as std::string overloaded operator).</div></div>",2042:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype2042\" class=\"NDPrototype NoParameterForm\">MipModels::NodeModel nodeModel() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Get the NodeModel value for this model number. Ex: str: &quot;6284-4220&quot;, nodeModel: 6284</div></div>",2043:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype2043\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">uint32</span> modifier() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Get the modifier value for this model number. Ex: str: &quot;6284-4220&quot;, modifier: 4220 Note: most actual modifier values are not defined in the Modifier enum - actual value read from the device likely won\'t match.</div></div>",2044:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype2044\" class=\"NDPrototype NoParameterForm\">MipModels::ModelNumber modelNumber() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Get the full ModelNumber value for this model number. Ex: str: &quot;6284-4220&quot;, modelNumber: 62844220 Note: most values in the ModelNumber enum use the placeholder modifier - actual value read from the device likely won\'t match.</div></div>",2045:"<div class=\"NDToolTip TOperator LC\"><div class=\"TTSummary\">Define == behavior when comparing a MipModels::ModelNumber enum value and MipModel object (functionally the same as comparing the MipModel::modelNumber() value with MipModels::modelNumbersEqual()).</div></div>",2046:"<div class=\"NDToolTip TOperator LC\"><div class=\"TTSummary\">Define != behavior when comparing a MipModels::ModelNumber enum value and MipModel object (functionally the same as comparing the MipModel::modelNumber() value with MipModels::modelNumbersEqual()).</div></div>"});