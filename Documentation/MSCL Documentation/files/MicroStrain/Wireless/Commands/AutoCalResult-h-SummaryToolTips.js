NDSummary.OnToolTipsLoaded("File:MicroStrain/Wireless/Commands/AutoCalResult.h",{4117:"<div class=\"NDToolTip TClass LC\"><div class=\"NDClassPrototype\" id=\"NDClassPrototype4117\"><div class=\"CPEntry TClass Current\"><div class=\"CPName\">AutoCalResult</div></div></div><div class=\"TTSummary\">Abstract base class for AutoCal result classes.</div></div>",4119:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype4119\" class=\"NDPrototype NoParameterForm\">WirelessTypes::AutoCalCompletionFlag completionFlag() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Gets the WirelessTypes::AutoCalCompletionFlag of the AutoCal operation result.</div></div>",4120:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype4120\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">virtual void</span> parse(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PModifierQualifier first\"><span class=\"SHKeyword\">const</span>&nbsp;</td><td class=\"PType\">Bytes&nbsp;</td><td class=\"PNamePrefix\">&amp;</td><td class=\"PName last\">autoCalInfo</td></tr></table></td><td class=\"PAfterParameters\">) = <span class=\"SHNumber\">0</span></td></tr></table></div><div class=\"TTSummary\">Parses the auto cal info bytes sent in the successful response packet.</div></div>",4122:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype4122\" class=\"NDPrototype NoParameterForm\">WirelessTypes::AutoCalCompletionFlag m_completionFlag</div><div class=\"TTSummary\">The WirelessTypes::AutoCalCompletionFlag of the AutoCal operation.</div></div>",4123:"<div class=\"NDToolTip TClass LC\"><div class=\"NDClassPrototype\" id=\"NDClassPrototype4123\"><div class=\"CPEntry TClass Current\"><div class=\"CPName\">AutoCalResult_shmLink</div></div></div><div class=\"TTSummary\">Holds the result information from an autoCal_shmLink command.</div></div>",4125:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype4125\" class=\"NDPrototype NoParameterForm\">WirelessTypes::AutoCalErrorFlag m_errorFlagCh1</div><div class=\"TTSummary\">The WirelessTypes::AutoCalErrorFlag for the channel 1 strain sensor.</div></div>",4126:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype4126\" class=\"NDPrototype NoParameterForm\">WirelessTypes::AutoCalErrorFlag m_errorFlagCh2</div><div class=\"TTSummary\">The WirelessTypes::AutoCalErrorFlag for the channel 2 strain sensor.</div></div>",4127:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype4127\" class=\"NDPrototype NoParameterForm\">WirelessTypes::AutoCalErrorFlag m_errorFlagCh3</div><div class=\"TTSummary\">The WirelessTypes::AutoCalErrorFlag for the channel 3 strain sensor.</div></div>",4128:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype4128\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">float</span> m_offsetCh1</div><div class=\"TTSummary\">The offset applied for the channel 1 strain sensor.</div></div>",4129:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype4129\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">float</span> m_offsetCh2</div><div class=\"TTSummary\">The offset applied for the channel 2 strain sensor.</div></div>",4130:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype4130\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">float</span> m_offsetCh3</div><div class=\"TTSummary\">The offset applied for the channel 3 strain sensor.</div></div>",4131:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype4131\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">float</span> m_temperature</div><div class=\"TTSummary\">The temperature at the time of calibration.</div></div>",4133:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype4133\" class=\"NDPrototype NoParameterForm\">WirelessTypes::AutoCalErrorFlag errorFlagCh1() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Gets the WirelessTypes::AutoCalErrorFlag for the channel 1 strain sensor.</div></div>",4134:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype4134\" class=\"NDPrototype NoParameterForm\">WirelessTypes::AutoCalErrorFlag errorFlagCh2() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Gets the WirelessTypes::AutoCalErrorFlag for the channel 2 strain sensor.</div></div>",4135:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype4135\" class=\"NDPrototype NoParameterForm\">WirelessTypes::AutoCalErrorFlag errorFlagCh3() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Gets the WirelessTypes::AutoCalErrorFlag for the channel 3 strain sensor.</div></div>",4136:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype4136\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">float</span> offsetCh1() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Gets the offset applied for the channel 1 strain sensor.</div></div>",4137:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype4137\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">float</span> offsetCh2() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Gets the offset applied for the channel 2 strain sensor.</div></div>",4138:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype4138\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">float</span> offsetCh3() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Gets the offset applied for the channel 3 strain sensor.</div></div>",4139:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype4139\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">float</span> temperature() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Gets the temperature (in ?C) at the time of the calibration.</div></div>",4140:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype4140\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">virtual void</span> parse(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PModifierQualifier first\"><span class=\"SHKeyword\">const</span>&nbsp;</td><td class=\"PType\">Bytes&nbsp;</td><td class=\"PNamePrefix\">&amp;</td><td class=\"PName last\">autoCalInfo</td></tr></table></td><td class=\"PAfterParameters\">) <span class=\"SHKeyword\">final</span></td></tr></table></div><div class=\"TTSummary\">Parses the auto cal info bytes for the shm-link.</div></div>",4141:"<div class=\"NDToolTip TClass LC\"><div class=\"NDClassPrototype\" id=\"NDClassPrototype4141\"><div class=\"CPEntry TClass Current\"><div class=\"CPName\">AutoCalResult_shmLink201</div></div></div><div class=\"TTSummary\">Holds the result information from an autoCal_shmLink201 command.</div></div>",4143:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype4143\" class=\"NDPrototype NoParameterForm\">WirelessTypes::AutoCalErrorFlag m_errorFlagCh1</div><div class=\"TTSummary\">The WirelessTypes::AutoCalErrorFlag for the channel 1 strain sensor.</div></div>",4144:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype4144\" class=\"NDPrototype NoParameterForm\">WirelessTypes::AutoCalErrorFlag m_errorFlagCh2</div><div class=\"TTSummary\">The WirelessTypes::AutoCalErrorFlag for the channel 2 strain sensor.</div></div>",4145:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype4145\" class=\"NDPrototype NoParameterForm\">WirelessTypes::AutoCalErrorFlag m_errorFlagCh3</div><div class=\"TTSummary\">The WirelessTypes::AutoCalErrorFlag for the channel 3 strain sensor.</div></div>",4146:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype4146\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">float</span> m_slopeCh1</div><div class=\"TTSummary\">The slope applied for channel 1.</div></div>",4147:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype4147\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">float</span> m_offsetCh1</div><div class=\"TTSummary\">The offset applied for channel 1.</div></div>",4148:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype4148\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">float</span> m_slopeCh2</div><div class=\"TTSummary\">The slope applied for channel 2.</div></div>",4149:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype4149\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">float</span> m_offsetCh2</div><div class=\"TTSummary\">The offset applied for channel 2.</div></div>",4150:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype4150\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">float</span> m_slopeCh3</div><div class=\"TTSummary\">The slope applied for channel 3.</div></div>",4151:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype4151\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">float</span> m_offsetCh3</div><div class=\"TTSummary\">The offset applied for channel 3.</div></div>",4152:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype4152\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">float</span> m_temperature</div><div class=\"TTSummary\">The temperature at the time of calibration.</div></div>",4154:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype4154\" class=\"NDPrototype NoParameterForm\">WirelessTypes::AutoCalErrorFlag errorFlagCh1() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Gets the WirelessTypes::AutoCalErrorFlag for the channel 1 strain sensor.</div></div>",4155:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype4155\" class=\"NDPrototype NoParameterForm\">WirelessTypes::AutoCalErrorFlag errorFlagCh2() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Gets the WirelessTypes::AutoCalErrorFlag for the channel 2 strain sensor.</div></div>",4156:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype4156\" class=\"NDPrototype NoParameterForm\">WirelessTypes::AutoCalErrorFlag errorFlagCh3() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Gets the WirelessTypes::AutoCalErrorFlag for the channel 3 strain sensor.</div></div>",4157:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype4157\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">float</span> slopeCh1() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Gets the slope applied for channel 1.</div></div>",4158:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype4158\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">float</span> offsetCh1() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Gets the offset applied for channel 1.</div></div>",4159:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype4159\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">float</span> slopeCh2() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Gets the slope applied for channel 2.</div></div>",4160:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype4160\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">float</span> offsetCh2() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Gets the offset applied for channel 2.</div></div>",4161:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype4161\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">float</span> slopeCh3() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Gets the slope applied for channel 3.</div></div>",4162:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype4162\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">float</span> offsetCh3() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Gets the offset applied for channel 3.</div></div>",4163:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype4163\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">float</span> temperature() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Gets the temperature (in ?C) at the time of the calibration.</div></div>",4164:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype4164\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">virtual void</span> parse(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PModifierQualifier first\"><span class=\"SHKeyword\">const</span>&nbsp;</td><td class=\"PType\">Bytes&nbsp;</td><td class=\"PNamePrefix\">&amp;</td><td class=\"PName last\">autoCalInfo</td></tr></table></td><td class=\"PAfterParameters\">) <span class=\"SHKeyword\">final</span></td></tr></table></div><div class=\"TTSummary\">Parses the auto cal info bytes for the shm-link.</div></div>",4165:"<div class=\"NDToolTip TClass LC\"><div class=\"NDClassPrototype\" id=\"NDClassPrototype4165\"><div class=\"CPEntry TClass Current\"><div class=\"CPName\">AutoShuntCalResult</div></div></div><div class=\"TTSummary\">Holds the result information from an autoCal_shunt command.</div></div>",4167:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype4167\" class=\"NDPrototype NoParameterForm\">WirelessTypes::AutoCalErrorFlag m_errorFlag</div><div class=\"TTSummary\">The WirelessTypes::AutoCalErrorFlag for the shunt calibration.</div></div>",4168:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype4168\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">float</span> m_slope</div><div class=\"TTSummary\">The slope result of the shunt calibration.</div></div>",4169:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype4169\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">float</span> m_offset</div><div class=\"TTSummary\">The offset result of the shunt calibration</div></div>",4170:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype4170\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">float</span> m_baseMedian</div><div class=\"TTSummary\">The median of the baseline data sampled during the shunt calibration.</div></div>",4171:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype4171\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">float</span> m_baseMin</div><div class=\"TTSummary\">The minimum of the baseline data sampled during the shunt calibration.</div></div>",4172:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype4172\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">float</span> m_baseMax</div><div class=\"TTSummary\">The maximum of the baseline data sampled during the shunt calibration.</div></div>",4173:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype4173\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">float</span> m_shuntMedian</div><div class=\"TTSummary\">The median of the shunted data sampled during the shunt calibration.</div></div>",4174:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype4174\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">float</span> m_shuntMin</div><div class=\"TTSummary\">The minimum of the shunted data sampled during the shunt calibration.</div></div>",4175:"<div class=\"NDToolTip TVariable LC\"><div id=\"NDPrototype4175\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">float</span> m_shuntMax</div><div class=\"TTSummary\">The maximum of the shunted data sampled during the shunt calibration.</div></div>",4177:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype4177\" class=\"NDPrototype NoParameterForm\">WirelessTypes::AutoCalErrorFlag errorFlag() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Gets the WirelessTypes::AutoCalErrorFlag for the shunt calibration.</div></div>",4178:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype4178\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">float</span> slope() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Gets the slope result of the shunt calibration.&nbsp; Note: This value was not applied to the Node. You will need to manually apply if desired.</div></div>",4179:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype4179\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">float</span> offset() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Gets the offset result of the shunt calibration.&nbsp; Note: This value was not applied to the Node. You will need to manually apply if desired.</div></div>",4180:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype4180\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">float</span> baseMedian() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Gets the median of the baseline data sampled during the shunt calibration.</div></div>",4181:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype4181\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">virtual void</span> parse(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PModifierQualifier first\"><span class=\"SHKeyword\">const</span>&nbsp;</td><td class=\"PType\">Bytes&nbsp;</td><td class=\"PNamePrefix\">&amp;</td><td class=\"PName last\">autoCalInfo</td></tr></table></td><td class=\"PAfterParameters\">) <span class=\"SHKeyword\">final</span></td></tr></table></div><div class=\"TTSummary\">Parses the auto cal info bytes for the shm-link.</div></div>"});