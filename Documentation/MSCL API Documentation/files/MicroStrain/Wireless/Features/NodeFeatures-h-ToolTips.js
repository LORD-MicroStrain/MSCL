NDContentPage.OnToolTipsLoaded({2648:"<div class=\"NDToolTip TClass LC\"><div class=\"NDClassPrototype\" id=\"NDClassPrototype2648\"><div class=\"CPEntry TClass Current\"><div class=\"CPName\">HistogramOptions</div></div></div><div class=\"TTSummary\">Contains all of the Histogram options that can be configured for a WirelessNode.</div></div>",2664:"<div class=\"NDToolTip TClass LC\"><div class=\"NDClassPrototype\" id=\"NDClassPrototype2664\"><div class=\"CPEntry TClass Current\"><div class=\"CPName\">FatigueOptions</div></div></div><div class=\"TTSummary\">Contains all of the fatigue options that can be configured for a WirelessNode.</div></div>",2796:"<div class=\"NDToolTip TClass LC\"><div class=\"NDClassPrototype\" id=\"NDClassPrototype2796\"><div class=\"CPEntry TClass Current\"><div class=\"CPName\">ActivitySense</div></div></div><div class=\"TTSummary\">Contains all of the ActivitySense options that can be configured for a WirelessNode.&nbsp; Activity Sense is a power saving feature that allows a Node to be in a low-power state when no activity is suspected, and then immediately jump to its normal sampling state when a certain activity threshold is reached.</div></div>",2983:"<div class=\"NDToolTip TClass LC\"><div class=\"NDClassPrototype\" id=\"NDClassPrototype2983\"><div class=\"CPEntry TClass Current\"><div class=\"CPName\">ChannelGroup</div></div></div><div class=\"TTSummary\">Represents a group of channels that have combined settings.</div></div>",3086:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype3086\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">virtual</span> TimeSpan minTimeBetweenBursts(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PModifierQualifier first\">WirelessTypes::</td><td class=\"PType\">DataMode&nbsp;</td><td></td><td class=\"PName last\">dataMode,</td></tr><tr><td class=\"PModifierQualifier first\">WirelessTypes::</td><td class=\"PType\">DataFormat&nbsp;</td><td></td><td class=\"PName last\">dataFormat,</td></tr><tr><td class=\"PModifierQualifier first\"><span class=\"SHKeyword\">const</span>&nbsp;</td><td class=\"PType\">ChannelMask&nbsp;</td><td class=\"PNamePrefix\">&amp;</td><td class=\"PName last\">rawChannels,</td></tr><tr><td class=\"PModifierQualifier first\">WirelessTypes::</td><td class=\"PType\">DerivedChannelMasks&nbsp;</td><td></td><td class=\"PName last\">derivedChannelMasks,</td></tr><tr><td class=\"PModifierQualifier first\"><span class=\"SHKeyword\">const</span>&nbsp;</td><td class=\"PType\">SampleRate&nbsp;</td><td class=\"PNamePrefix\">&amp;</td><td class=\"PName last\">rawSampleRate,</td></tr><tr><td class=\"first\"></td><td class=\"PType\"><span class=\"SHKeyword\">uint32</span>&nbsp;</td><td></td><td class=\"PName last\">sweepsPerBurst,</td></tr><tr><td class=\"PModifierQualifier first\">WirelessTypes::</td><td class=\"PType\">CommProtocol&nbsp;</td><td></td><td class=\"PName last\">commProtocol</td></tr></table></td><td class=\"PAfterParameters\">) <span class=\"SHKeyword\">const</span></td></tr></table></div><div class=\"TTSummary\">Gets the minimum time that can be assigned for a Burst Sync Sampling session.</div></div>",3100:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype3100\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">virtual const</span> WirelessTypes::WirelessSampleRates sampleRates(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PModifierQualifier first\">WirelessTypes::</td><td class=\"PType\">SamplingMode&nbsp;</td><td class=\"PName last\">samplingMode,</td></tr><tr><td class=\"PModifierQualifier first\">WirelessTypes::</td><td class=\"PType\">DataCollectionMethod&nbsp;</td><td class=\"PName last\">dataCollectionMethod,</td></tr><tr><td class=\"PModifierQualifier first\">WirelessTypes::</td><td class=\"PType\">DataMode&nbsp;</td><td class=\"PName last\">dataMode</td></tr></table></td><td class=\"PAfterParameters\">) <span class=\"SHKeyword\">const</span></td></tr></table></div><div class=\"TTSummary\">Gets a list of the WirelessTypes::WirelessSampleRates that are supported by this Node for the given sampling mode.</div></div>",3113:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype3113\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">virtual const</span> InputRanges inputRanges(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PModifierQualifier first\"><span class=\"SHKeyword\">const</span>&nbsp;</td><td class=\"PType\">ChannelMask&nbsp;</td><td class=\"PNamePrefix\">&amp;</td><td class=\"PName last\">channels</td></tr></table></td><td class=\"PAfterParameters\">) <span class=\"SHKeyword\">const</span></td></tr></table></div><div class=\"TTSummary\">Gets a list of InputRanges that are supported by this Node for the specified channel mask.</div></div>",3141:"<div class=\"NDToolTip TEnumeration LC\"><div class=\"TTSummary\">Represents the types of data collection methods that can be performed on the Node.</div></div>",3145:"<div class=\"NDToolTip TEnumeration LC\"><div class=\"TTSummary\">Represents the types of data formats that Nodes can be configured to send when sampling.</div></div>",3155:"<div class=\"NDToolTip TEnumeration LC\"><div class=\"TTSummary\">Represents the types of sampling modes the Node can be in.</div></div>",3162:"<div class=\"NDToolTip TEnumeration LC\"><div class=\"TTSummary\">Represents the types of default modes the Node can have.&nbsp; This is the mode the Node starts in, as well as the mode the node goes into after an inactivity timeout.</div></div>",3186:"<div class=\"NDToolTip TEnumeration LC\"><div class=\"TTSummary\">Represents the transmit powers that can be used for Wireless Devices.</div></div>",3317:"<div class=\"NDToolTip TEnumeration LC\"><div class=\"TTSummary\">Represents the types of channels on Wireless Nodes.</div></div>",3330:"<div class=\"NDToolTip TEnumeration LC\"><div class=\"TTSummary\">Represents the possible voltage input types</div></div>",3333:"<div class=\"NDToolTip TEnumeration LC\"><div class=\"TTSummary\">Represents the settling times used for thermocouple and voltage inputs on some Wireless Nodes.</div></div>",3346:"<div class=\"NDToolTip TEnumeration LC\"><div class=\"TTSummary\">Represents the Transducer types supported by some Wireless Nodes.</div></div>",3381:"<div class=\"NDToolTip TEnumeration LC\"><div class=\"TTSummary\">The possible sample rates that are available for Wireless Nodes.</div></div>",3436:"<div class=\"NDToolTip TEnumeration LC\"><div class=\"TTSummary\">The possible settings for ChannelGroups.</div></div>",3483:"<div class=\"NDToolTip TEnumeration LC\"><div class=\"TTSummary\">The different modes a Fatigue Node can operate in.</div></div>",3490:"<div class=\"NDToolTip TEnumeration LC\"><div class=\"TTSummary\">The filter options (used for anti-aliasing and low-pass filter)</div></div>",3530:"<div class=\"NDToolTip TEnumeration LC\"><div class=\"TTSummary\">The channel frequency class filter options.</div></div>",3534:"<div class=\"NDToolTip TEnumeration LC\"><div class=\"TTSummary\">The options available for configuring what happens when the storage limit is reached when logging to a Node.</div></div>",3537:"<div class=\"NDToolTip TEnumeration LC\"><div class=\"TTSummary\">The options available for input range on supported Nodes.</div></div>",3674:"<div class=\"NDToolTip TEnumeration LC\"><div class=\"TTSummary\">Available Data Modes.</div></div>",3679:"<div class=\"NDToolTip TEnumeration LC\"><div class=\"TTSummary\">Available Derived Channel Categories for configuration.</div></div>",3693:"<div class=\"NDToolTip TEnumeration LC\"><div class=\"TTSummary\">Available Communication Protocol types.</div></div>",3696:"<div class=\"NDToolTip TEnumeration LC\"><div class=\"TTSummary\">Available Voltages.</div></div>",3706:"<div class=\"NDToolTip TEnumeration LC\"><div class=\"TTSummary\">Available Sensor Output Modes.</div></div>",3723:"<div class=\"NDToolTip TType LC\"><div class=\"TTSummary\">Typedef for a map of &lt;DerivedChannelOption&gt; to ChannelMask pairs.</div></div>",3726:"<div class=\"NDToolTip TClass LC\"><div class=\"NDClassPrototype\" id=\"NDClassPrototype3726\"><div class=\"CPEntry TClass Current\"><div class=\"CPName\">WirelessNode</div></div></div><div class=\"TTSummary\">A class representing a MicroStrain wireless node</div></div>",3961:"<div class=\"NDToolTip TClass LC\"><div class=\"NDClassPrototype\" id=\"NDClassPrototype3961\"><div class=\"CPEntry TClass Current\"><div class=\"CPName\">WirelessChannel</div></div></div><div class=\"TTSummary\">Represents a channel on a WirelessNode. This can be used to gain information about the channel, view current settings that are applied, and update settings on the Node.</div></div>",4298:"<div class=\"NDToolTip TClass LC\"><div class=\"NDClassPrototype\" id=\"NDClassPrototype4298\"><div class=\"CPEntry TClass Current\"><div class=\"CPName\">ChannelMask</div></div></div><div class=\"TTSummary\">Represents the channel mask (active and inactive channels) for a WirelessNode.</div></div>",4364:"<div class=\"NDToolTip TClass LC\"><div class=\"NDClassPrototype\" id=\"NDClassPrototype4364\"><div class=\"CPEntry TClass Current\"><div class=\"CPName\">SampleRate</div></div></div><div class=\"TTSummary\">Represents a MicroStrain sample rate (rate at which data is sampling)</div></div>",4556:"<div class=\"NDToolTip TClass LC\"><div class=\"NDClassPrototype\" id=\"NDClassPrototype4556\"><div class=\"CPEntry TClass Current\"><div class=\"CPName\">TimeSpan</div></div></div><div class=\"TTSummary\">Represents a range of time</div></div>",4594:"<div class=\"NDToolTip TClass LC\"><div class=\"NDClassPrototype\" id=\"NDClassPrototype4594\"><div class=\"CPEntry TClass Current\"><div class=\"CPName\">Error_NotSupported</div></div></div><div class=\"TTSummary\">A command/feature was attempted to be used that was not supported.</div></div>",2982:"<div class=\"NDToolTip TClass LC\"><div class=\"NDClassPrototype\" id=\"NDClassPrototype2982\"><div class=\"CPEntry TClass Current\"><div class=\"CPName\">NodeFeatures_200series</div></div></div><div class=\"TTSummary\">Contains information on which features are supported by a 200-series WirelessNode.&nbsp; Inherits from NodeFeatures.</div></div>"});