NDSummary.OnToolTipsLoaded("CClass:InertialNode",{280:"<div class=\"NDToolTip TClass LC\"><div class=\"NDClassPrototype\" id=\"NDClassPrototype280\"><div class=\"CPEntry TClass Current\"><div class=\"CPName\">InertialNode</div></div></div><div class=\"TTSummary\">A class representing a MicroStrain Inertial Node</div></div>",281:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype281\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">explicit</span> InertialNode(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PType first\">Connection&nbsp;</td><td class=\"PName last\">connection</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Creates an InertialNode object.</div></div>",282:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype282\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">static</span> std::<span class=\"SHKeyword\">string</span> deviceName(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PModifierQualifier first\"><span class=\"SHKeyword\">const</span> std::</td><td class=\"PType\"><span class=\"SHKeyword\">string</span>&nbsp;</td><td class=\"PNamePrefix\">&amp;</td><td class=\"PName last\">serial</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Static function for creating the universal sensor name that should be used for SensorCloud.</div></div>",283:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype283\" class=\"NDPrototype NoParameterForm\">Connection&amp; connection()</div><div class=\"TTSummary\">Gets the Connection object that this InertialNode is using.</div></div>",284:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype284\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">const</span> MipNodeFeatures&amp; features()</div><div class=\"TTSummary\">Gets a reference to the MipNodeFeatures for this device.&nbsp; Note: This will be invalid when the InertialNode is destroyed.</div></div>",285:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype285\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">const</span> Timestamp&amp; lastCommunicationTime() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Gets the Timestamp for the last time MSCL communicated with the InertialNode.</div></div>",286:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype286\" class=\"NDPrototype NoParameterForm\">Version firmwareVersion() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Gets the firmware Version of the InertialNode.</div></div>",287:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype287\" class=\"NDPrototype NoParameterForm\">InertialModels::NodeModel model() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Gets the InertialModels::NodeModel of the InertialNode.</div></div>",288:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype288\" class=\"NDPrototype NoParameterForm\">std::<span class=\"SHKeyword\">string</span> modelName() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Gets the model name of the InertialNode (ie. &quot;3DM-GX3-45&quot;).</div></div>",289:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype289\" class=\"NDPrototype NoParameterForm\">std::<span class=\"SHKeyword\">string</span> modelNumber() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Gets the model number of the InertialNode (ie. &quot;6225-4220&quot;).</div></div>",290:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype290\" class=\"NDPrototype NoParameterForm\">std::<span class=\"SHKeyword\">string</span> serialNumber() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Gets the serial number of the InertialNode (ie. &quot;6225-01319&quot;).</div></div>",291:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype291\" class=\"NDPrototype NoParameterForm\">std::<span class=\"SHKeyword\">string</span> lotNumber() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Gets the lot number of the InertialNode (ie. &quot;I042Y&quot;).</div></div>",292:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype292\" class=\"NDPrototype NoParameterForm\">std::<span class=\"SHKeyword\">string</span> deviceOptions() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Gets the device options of the InertialNode (ie. &quot;5g, 300d/s&quot;).</div></div>",293:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype293\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\">MipDataPackets getDataPackets(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PType first\"><span class=\"SHKeyword\">uint32</span>&nbsp;</td><td class=\"PName\">timeout&nbsp;</td><td class=\"PDefaultValueSeparator\">=&nbsp;</td><td class=\"PDefaultValue last\"><span class=\"SHNumber\">0</span>,</td></tr><tr><td class=\"PType first\"><span class=\"SHKeyword\">uint32</span>&nbsp;</td><td class=\"PName\">maxPackets&nbsp;</td><td class=\"PDefaultValueSeparator\">=&nbsp;</td><td class=\"PDefaultValue last\"><span class=\"SHNumber\">0</span></td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Gets up to the requested amount of data packets that have been collected.</div></div>",294:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype294\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">uint32</span> totalPackets()</div><div class=\"TTSummary\">Gets the total number of data packets that are currently in the buffer.</div></div>",295:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype295\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">void</span> timeout(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PType first\"><span class=\"SHKeyword\">uint64</span>&nbsp;</td><td class=\"PName last\">timeout</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Sets the timeout to use when waiting for responses from Inertial commands.</div></div>",296:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype296\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">uint64</span> timeout() <span class=\"SHKeyword\">const</span></div><div class=\"TTSummary\">Gets the timeout to use when waiting for responses from Inertial commands.</div></div>",297:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype297\" class=\"NDPrototype NoParameterForm\">std::<span class=\"SHKeyword\">string</span> name()</div><div class=\"TTSummary\">Gets the name of the InertialNode. This is the universal sensor name that should be used for uploading to SensorCloud.&nbsp; This is the same as calling InertialNode::deviceName.</div></div>",298:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype298\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">bool</span> ping()</div><div class=\"TTSummary\">Pings the Node to check for communication.&nbsp; Sends the &quot;Ping&quot; command to the device.</div></div>",299:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype299\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">void</span> setToIdle()</div><div class=\"TTSummary\">Suspends streaming (if enabled) or wakes the device from sleep (if sleeping), putting the device in an idle mode.&nbsp; After this command is used, the resume command may be used to put the Node back into the mode it was previously in before setToIdle was called.</div></div>",300:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype300\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">bool</span> cyclePower()</div><div class=\"TTSummary\">Performs the &quot;Device Reset&quot; Inertial command.&nbsp; Note: This is essentially the same as unplugging and plugging the device back in.</div></div>",301:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype301\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">void</span> resume()</div><div class=\"TTSummary\">Places the Node back in the mode it was in before issuing the setToIdle command.&nbsp; If the setToIdle command was not issued, then the device is placed in default mode.</div></div>",302:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype302\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">void</span> saveSettingsAsStartup()</div><div class=\"TTSummary\">Saves all of the current settings as the Node\'s startup settings.&nbsp; Note: A brief data disturbance may occur when calling this command.</div></div>",303:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype303\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">void</span> loadStartupSettings()</div><div class=\"TTSummary\">Loads the saved startup settings onto the Node as its current settings.&nbsp; This function is useful if you have powered on the Node, made changes to its settings, and want to get back to its startup settings.</div></div>",304:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype304\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">void</span> loadFactoryDefaultSettings()</div><div class=\"TTSummary\">Loads the factory default settings onto the Node as its current settings.</div></div>",305:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype305\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">uint16</span> getDataRateBase(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PModifierQualifier first\">MipTypes::</td><td class=\"PType\">DataClass&nbsp;</td><td class=\"PName last\">category</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Gets the Data decimation base for the data rate calculations of the specified &lt;InertialType&gt;.</div></div>",306:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype306\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\">MipChannels getActiveChannelFields(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PModifierQualifier first\">MipTypes::</td><td class=\"PType\">DataClass&nbsp;</td><td class=\"PName last\">category</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Gets the current active channel fields for the specified MipTypes::DataClass.</div></div>",307:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype307\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">void</span> setActiveChannelFields(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PModifierQualifier first\">MipTypes::</td><td class=\"PType\">DataClass&nbsp;</td><td></td><td class=\"PName last\">category,</td></tr><tr><td class=\"PModifierQualifier first\"><span class=\"SHKeyword\">const</span>&nbsp;</td><td class=\"PType\">MipChannels&nbsp;</td><td class=\"PNamePrefix\">&amp;</td><td class=\"PName last\">channels</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Sets the current active channel fields for the specified MipTypes::DataClass.&nbsp; Note that this function does not add to the existing message format (active channels), but overwrites it entirely.</div></div>",308:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype308\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">uint8</span> getCommunicationMode()</div><div class=\"TTSummary\">Gets the current communication mode that the node is in.</div></div>",309:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype309\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">void</span> setCommunicationMode(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PType first\"><span class=\"SHKeyword\">uint8</span>&nbsp;</td><td class=\"PName last\">communicationMode</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Sets the communication mode for the node.&nbsp; Note: The node info will be reset when doing this and therefore will require being fetched again the next time it is requested.</div></div>",310:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype310\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">void</span> enableDataStream(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PModifierQualifier first\">MipTypes::</td><td class=\"PType\">DataClass&nbsp;</td><td class=\"PName\">category,</td><td></td><td class=\"last\"></td></tr><tr><td class=\"first\"></td><td class=\"PType\"><span class=\"SHKeyword\">bool</span>&nbsp;</td><td class=\"PName\">enable&nbsp;</td><td class=\"PDefaultValueSeparator\">=&nbsp;</td><td class=\"PDefaultValue last\"><span class=\"SHKeyword\">true</span></td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Enables or disables continuous data streaming for the node.</div></div>",311:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype311\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">void</span> resetFilter()</div><div class=\"TTSummary\">Resets the filter to the initialize state.&nbsp; Note: If the auto-initialization feature is disabled, the initial attitude or heading must be set in order to enter the run state after a reset.</div></div>",312:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype312\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">bool</span> getAutoInitialization()</div><div class=\"TTSummary\">Gets the state of the automatic initialization upon device startup.</div></div>",313:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype313\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">void</span> setAutoInitialization(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PType first\"><span class=\"SHKeyword\">bool</span>&nbsp;</td><td class=\"PName last\">enable</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Sets the state of the automatic initialization upon device startup.</div></div>",314:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype314\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">void</span> setInitialAttitude(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PModifierQualifier first\"><span class=\"SHKeyword\">const</span>&nbsp;</td><td class=\"PType\">EulerAngles&nbsp;</td><td class=\"PNamePrefix\">&amp;</td><td class=\"PName last\">attitude</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Sets the initial attitude.&nbsp; Node: This command can only be issues in the &quot;INIT&quot; state and should be used with a good estimate of the vehicle attitude.</div></div>",315:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype315\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">void</span> setInitialHeading(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PType first\"><span class=\"SHKeyword\">float</span>&nbsp;</td><td class=\"PName last\">heading</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Sets the initial heading.&nbsp; Node: This command can only be issues in the &quot;INIT&quot; state and should be used with a good estimate of heading. The device will use this value in conjunction with the output of the accelerometers to determine the initial attitude estimate.</div></div>",316:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype316\" class=\"NDPrototype NoParameterForm\">EulerAngles getSensorToVehicleTransformation()</div><div class=\"TTSummary\">Gets the sensor to vehicle frame transformation matrix using roll, pitch, and yaw Euler angles.&nbsp; These angles define the rotation from the sensor body from to the fixed vehicle frame.</div></div>",317:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype317\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">void</span> setSensorToVehicleTransformation(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PModifierQualifier first\"><span class=\"SHKeyword\">const</span>&nbsp;</td><td class=\"PType\">EulerAngles&nbsp;</td><td class=\"PNamePrefix\">&amp;</td><td class=\"PName last\">angles</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Sets the sensor to vehicle frame transformation matrix using roll, pitch, and yaw Euler angles (in radians).&nbsp; These angles define the rotation from the sensor body from to the fixed vehicle frame.</div></div>",318:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype318\" class=\"NDPrototype NoParameterForm\">PositionOffset getSensorToVehicleOffset()</div><div class=\"TTSummary\">Gets the sensor to vehicle frame offset, expressed in the sensor frame.</div></div>",319:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype319\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">void</span> setSensorToVehicleOffset(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PModifierQualifier first\"><span class=\"SHKeyword\">const</span>&nbsp;</td><td class=\"PType\">PositionOffset&nbsp;</td><td class=\"PNamePrefix\">&amp;</td><td class=\"PName last\">offset</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Sets the sensor to vehicle frame offset, expressed in the sensor frame.</div></div>",320:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype320\" class=\"NDPrototype NoParameterForm\">PositionOffset getAntennaOffset()</div><div class=\"TTSummary\">Gets the antenna offset, expressed in the sensor frame.</div></div>",321:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype321\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">void</span> setAntennaOffset(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PModifierQualifier first\"><span class=\"SHKeyword\">const</span>&nbsp;</td><td class=\"PType\">PositionOffset&nbsp;</td><td class=\"PNamePrefix\">&amp;</td><td class=\"PName last\">offset</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Sets the antenna offset, expressed in the sensor frame.</div></div>",322:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype322\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">bool</span> getGNSSAssistedFixControl()</div><div class=\"TTSummary\">Gets the GNSS Assisted Fix Control.</div></div>",323:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype323\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">void</span> setGNSSAssistedFixControl(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PType first\"><span class=\"SHKeyword\">bool</span>&nbsp;</td><td class=\"PName last\">enableAssistedFix</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Sets the GNSS Assisted Fix Control.</div></div>",324:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype324\" class=\"NDPrototype NoParameterForm\">TimeUpdate getGNSSAssistTimeUpdate()</div><div class=\"TTSummary\">Gets the GNSS Assisted Time Update.</div></div>",325:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype325\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">void</span> setGNSSAssistTimeUpdate(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PModifierQualifier first\"><span class=\"SHKeyword\">const</span>&nbsp;</td><td class=\"PType\">TimeUpdate&nbsp;</td><td class=\"PNamePrefix\">&amp;</td><td class=\"PName last\">timeUpdate</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Sets the GNSS Assist Time Update.</div></div>",326:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype326\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\">mscl::<span class=\"SHKeyword\">uint32</span> getGPSTimeUpdate(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PModifierQualifier first\">MipTypes::</td><td class=\"PType\">TimeFrame&nbsp;</td><td class=\"PName last\">timeFrame</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Gets the GPS time update.</div></div>",327:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype327\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">void</span> setGPSTimeUpdate(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"first\"></td><td></td><td class=\"PName last\">MipTypes::TimeFrame,</td></tr><tr><td class=\"PModifierQualifier first\">mscl::</td><td class=\"PType\"><span class=\"SHKeyword\">uint32</span>&nbsp;</td><td class=\"PName last\">timeData</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Sets the GPS Time Update.</div></div>",328:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype328\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">void</span> setConstellationSettings(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PModifierQualifier first\"><span class=\"SHKeyword\">const</span>&nbsp;</td><td class=\"PType\">ConstellationSettingsData&nbsp;</td><td class=\"PNamePrefix\">&amp;</td><td class=\"PName last\">dataToUse</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Sets the GNSS Constellation Settings.</div></div>",329:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype329\" class=\"NDPrototype NoParameterForm\">ConstellationSettingsData getConstellationSettings()</div><div class=\"TTSummary\">Gets the GNSS Constellation Settings.</div></div>",330:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype330\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">void</span> setSBASSettings(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PModifierQualifier first\"><span class=\"SHKeyword\">const</span>&nbsp;</td><td class=\"PType\">SBASSettingsData&nbsp;</td><td class=\"PNamePrefix\">&amp;</td><td class=\"PName last\">dataToUse</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Sets the GNSS SBAS Settings.</div></div>",331:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype331\" class=\"NDPrototype NoParameterForm\">SBASSettingsData getSBASSettings()</div><div class=\"TTSummary\">Gets the GNSS SBAS Settings.</div></div>",332:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype332\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">void</span> setAccelerometerBias(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PModifierQualifier first\"><span class=\"SHKeyword\">const</span>&nbsp;</td><td class=\"PType\">GeometricVector&nbsp;</td><td class=\"PNamePrefix\">&amp;</td><td class=\"PName last\">biasVector</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Sets the Accelerometer Bias.</div></div>",333:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype333\" class=\"NDPrototype NoParameterForm\">GeometricVector getAccelerometerBias()</div><div class=\"TTSummary\">Gets the Accelerometer Bias.</div></div>",334:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype334\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">void</span> setGyroBias(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PModifierQualifier first\"><span class=\"SHKeyword\">const</span>&nbsp;</td><td class=\"PType\">GeometricVector&nbsp;</td><td class=\"PNamePrefix\">&amp;</td><td class=\"PName last\">biasVector</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Sets the Gyro Bias.</div></div>",335:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype335\" class=\"NDPrototype NoParameterForm\">GeometricVector getGyroBias()</div><div class=\"TTSummary\">Gets the Gyro Bias vector.</div></div>",336:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype336\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\">GeometricVector captureGyroBias(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PModifierQualifier first\"><span class=\"SHKeyword\">const</span>&nbsp;</td><td class=\"PType\"><span class=\"SHKeyword\">uint16</span>&nbsp;</td><td class=\"PNamePrefix\">&amp;</td><td class=\"PName last\">samplingTime</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Runs the Gyro Bias capture routine on the inertial device.</div></div>",337:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype337\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">void</span> setMagnetometerSoftIronMatrix(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PModifierQualifier first\"><span class=\"SHKeyword\">const</span>&nbsp;</td><td class=\"PType\">Matrix_3x3&nbsp;</td><td class=\"PNamePrefix\">&amp;</td><td class=\"PName last\">matrix</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Sets the Magnetometer Soft Iron matrix.</div></div>",338:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype338\" class=\"NDPrototype NoParameterForm\">Matrix_3x3 getMagnetometerSoftIronMatrix()</div><div class=\"TTSummary\">Gets the Magnetometer Soft Iron matrix.</div></div>",339:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype339\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">void</span> setMagnetometerHardIronOffset(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PModifierQualifier first\"><span class=\"SHKeyword\">const</span>&nbsp;</td><td class=\"PType\">GeometricVector&nbsp;</td><td class=\"PNamePrefix\">&amp;</td><td class=\"PName last\">offsetVector</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Sets the magnetometer hard iron offset vector.</div></div>",340:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype340\" class=\"NDPrototype NoParameterForm\">GeometricVector getMagnetometerHardIronOffset()</div><div class=\"TTSummary\">Gets the magnetometer hard iron offset vector.</div></div>",341:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype341\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">void</span> setConingAndScullingEnable(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PType first\"><span class=\"SHKeyword\">bool</span>&nbsp;</td><td class=\"PName last\">enable</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Enables/disables coning and sculling.</div></div>",342:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype342\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">bool</span> getConingAndScullingEnable()</div><div class=\"TTSummary\">determines whether coning and sculling are enabled.</div></div>",343:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype343\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">void</span> setUARTBaudRate(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PType first\"><span class=\"SHKeyword\">uint32</span>&nbsp;</td><td class=\"PName last\">baudRate</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Sets the baud rate.&nbsp; The device can be unresponsive for as much as 250 ms following this command.</div></div>",344:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype344\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">uint32</span> getUARTBaudRate()</div><div class=\"TTSummary\">Gets the current baud rate for the inertial device.</div></div>",345:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype345\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">void</span> setAdvancedLowPassFilterSettings(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PModifierQualifier first\"><span class=\"SHKeyword\">const</span>&nbsp;</td><td class=\"PType\">AdvancedLowPassFilterData&nbsp;</td><td class=\"PNamePrefix\">&amp;</td><td class=\"PName last\">data</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Sets the advanced low-pass filter settings.</div></div>",346:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype346\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\">AdvancedLowPassFilterData getAdvancedLowPassFilterSettings(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PModifierQualifier first\"><span class=\"SHKeyword\">const</span>&nbsp;</td><td class=\"PType\">AdvancedLowPassFilterData&nbsp;</td><td class=\"PNamePrefix\">&amp;</td><td class=\"PName last\">data</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Gets the current advanced low-pass filter settings.</div></div>",347:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype347\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">void</span> setComplementaryFilterSettings(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PModifierQualifier first\"><span class=\"SHKeyword\">const</span>&nbsp;</td><td class=\"PType\">ComplementaryFilterData&nbsp;</td><td class=\"PNamePrefix\">&amp;</td><td class=\"PName last\">data</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Sets the complementary filter settings.</div></div>",348:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype348\" class=\"NDPrototype NoParameterForm\">ComplementaryFilterData getComplementaryFilterSettings()</div><div class=\"TTSummary\">Gets the current complementary filter settings.</div></div>",349:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype349\" class=\"NDPrototype NoParameterForm\">DeviceStatusData getBasicDeviceStatus()</div><div class=\"TTSummary\">Gets the basic device status.</div></div>",350:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype350\" class=\"NDPrototype NoParameterForm\">DeviceStatusData getDiagnosticDeviceStatus()</div><div class=\"TTSummary\">Gets the diagnostic device status.</div></div>",351:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype351\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">void</span> sendRawRTCM_2_3Message(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PModifierQualifier first\"><span class=\"SHKeyword\">const</span>&nbsp;</td><td class=\"PType\">RTCMMessage&nbsp;</td><td class=\"PNamePrefix\">&amp;</td><td class=\"PName last\">theMessage</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Sends a raw RTCM 2.3 message.</div></div>",352:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype352\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">void</span> setVehicleDynamicsMode(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PModifierQualifier first\"><span class=\"SHKeyword\">const</span> InertialTypes::</td><td class=\"PType\">VehicleModeType&nbsp;</td><td class=\"PNamePrefix\">&amp;</td><td class=\"PName last\">mode</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Sets the vehicle dynamics mode.</div></div>",353:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype353\" class=\"NDPrototype NoParameterForm\">InertialTypes::VehicleModeType getVehicleDynamicsMode()</div><div class=\"TTSummary\">Gets the vehicle dynamics mode.</div></div>",354:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype354\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">void</span> setEstimationControlFlags(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PModifierQualifier first\"><span class=\"SHKeyword\">const</span>&nbsp;</td><td class=\"PType\"><span class=\"SHKeyword\">uint16</span>&nbsp;</td><td class=\"PNamePrefix\">&amp;</td><td class=\"PName last\">flags</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Sets the estimation control flags.</div></div>",355:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype355\" class=\"NDPrototype NoParameterForm\"><span class=\"SHKeyword\">uint16</span> getEstimationControlFlags()</div><div class=\"TTSummary\">Gets the estimation control flags.</div></div>",356:"<div class=\"NDToolTip TFunction LC\"><div class=\"TTSummary\">Sets the estimation control flags.</div></div>",357:"<div class=\"NDToolTip TFunction LC\"><div class=\"TTSummary\">Gets the estimation control flags.</div></div>",358:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype358\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">void</span> sendExternalGNSSUpdate(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PModifierQualifier first\"><span class=\"SHKeyword\">const</span>&nbsp;</td><td class=\"PType\">ExternalGNSSUpdateData&nbsp;</td><td class=\"PNamePrefix\">&amp;</td><td class=\"PName last\">gnssUpdateData</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">sends the external GNSS update command.</div></div>",359:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype359\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">void</span> setHeadingUpdateControl(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PModifierQualifier first\"><span class=\"SHKeyword\">const</span>&nbsp;</td><td class=\"PType\">HeadingUpdateOptions&nbsp;</td><td class=\"PNamePrefix\">&amp;</td><td class=\"PName last\">headingUpdateOptions</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">Sets the heading update control flags.</div></div>",360:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype360\" class=\"NDPrototype NoParameterForm\">HeadingUpdateOptions getHeadingUpdateControl()</div><div class=\"TTSummary\">Gets the heading update control flags.</div></div>",361:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype361\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">void</span> sendExternalHeadingUpdate(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PModifierQualifier first\"><span class=\"SHKeyword\">const</span>&nbsp;</td><td class=\"PType\">HeadingData&nbsp;</td><td class=\"PNamePrefix\">&amp;</td><td class=\"PName last\">headingData</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">sends the external heading update command.</div></div>",362:"<div class=\"NDToolTip TFunction LC\"><div id=\"NDPrototype362\" class=\"NDPrototype WideForm CStyle\"><table><tr><td class=\"PBeforeParameters\"><span class=\"SHKeyword\">void</span> sendExternalHeadingUpdate(</td><td class=\"PParametersParentCell\"><table class=\"PParameters\"><tr><td class=\"PModifierQualifier first\"><span class=\"SHKeyword\">const</span>&nbsp;</td><td class=\"PType\">HeadingData&nbsp;</td><td class=\"PNamePrefix\">&amp;</td><td class=\"PName last\">headingData,</td></tr><tr><td class=\"PModifierQualifier first\"><span class=\"SHKeyword\">const</span>&nbsp;</td><td class=\"PType\">TimeUpdate&nbsp;</td><td class=\"PNamePrefix\">&amp;</td><td class=\"PName last\">timestamp</td></tr></table></td><td class=\"PAfterParameters\">)</td></tr></table></div><div class=\"TTSummary\">sends the external heading update command.</div></div>"});