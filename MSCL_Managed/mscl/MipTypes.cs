//------------------------------------------------------------------------------
// <auto-generated />
//
// This file was automatically generated by SWIG (http://www.swig.org).
// Version 4.0.0
//
// Do not make changes to this file unless you know what you are doing--modify
// the SWIG interface file instead.
//------------------------------------------------------------------------------

namespace mscl {

public class MipTypes : global::System.IDisposable {
  private global::System.Runtime.InteropServices.HandleRef swigCPtr;
  protected bool swigCMemOwn;

  internal MipTypes(global::System.IntPtr cPtr, bool cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = new global::System.Runtime.InteropServices.HandleRef(this, cPtr);
  }

  internal static global::System.Runtime.InteropServices.HandleRef getCPtr(MipTypes obj) {
    return (obj == null) ? new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero) : obj.swigCPtr;
  }

  ~MipTypes() {
    Dispose(false);
  }

  public void Dispose() {
    Dispose(true);
    global::System.GC.SuppressFinalize(this);
  }

  protected virtual void Dispose(bool disposing) {
    lock(this) {
      if (swigCPtr.Handle != global::System.IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          msclPINVOKE.delete_MipTypes(swigCPtr);
        }
        swigCPtr = new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero);
      }
    }
  }

  public static string channelName(MipTypes.ChannelField field, MipTypes.ChannelQualifier qualifier) {
    string ret = msclPINVOKE.MipTypes_channelName((int)field, (int)qualifier);
    if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public static MipChannelFields getChannelFields_allDataClasses(MipTypes.ChannelField chField) {
    MipChannelFields ret = new MipChannelFields(msclPINVOKE.MipTypes_getChannelFields_allDataClasses((int)chField), true);
    if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public static MipTypes.ChannelField getChannelField_baseDataClass(MipTypes.ChannelField chField) {
    MipTypes.ChannelField ret = (MipTypes.ChannelField)msclPINVOKE.MipTypes_getChannelField_baseDataClass((int)chField);
    if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public static MipTypes.ChannelField getChannelField_toDataClass(MipTypes.ChannelField chField, MipTypes.DataClass dataClass) {
    MipTypes.ChannelField ret = (MipTypes.ChannelField)msclPINVOKE.MipTypes_getChannelField_toDataClass((int)chField, (int)dataClass);
    if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public static string getChannelNamePrependText(MipTypes.ChannelField chField) {
    string ret = msclPINVOKE.MipTypes_getChannelNamePrependText((int)chField);
    if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public static string getChannelNameAppendText(MipTypes.ChannelField chField) {
    string ret = msclPINVOKE.MipTypes_getChannelNameAppendText((int)chField);
    if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public static bool isGnssChannelField(MipTypes.ChannelField chField) {
    bool ret = msclPINVOKE.MipTypes_isGnssChannelField((int)chField);
    if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public static bool isSharedChannelField(MipTypes.ChannelField chField) {
    bool ret = msclPINVOKE.MipTypes_isSharedChannelField((int)chField);
    if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public MipTypes() : this(msclPINVOKE.new_MipTypes(), true) {
    if (msclPINVOKE.SWIGPendingException.Pending) throw msclPINVOKE.SWIGPendingException.Retrieve();
  }

  public enum DataClass {
    CLASS_AHRS_IMU = 0x80,
    CLASS_GNSS = 0x81,
    CLASS_ESTFILTER = 0x82,
    CLASS_DISPLACEMENT = 0x90,
    CLASS_GNSS1 = 0x91,
    CLASS_GNSS2 = 0x92,
    CLASS_GNSS3 = 0x93,
    CLASS_RTK = 0x93,
    CLASS_GNSS4 = 0x94,
    CLASS_GNSS5 = 0x95
  }

  public enum FunctionSelector {
    USE_NEW_SETTINGS = 0x01,
    READ_BACK_CURRENT_SETTINGS = 0x02,
    SAVE_CURRENT_SETTINGS = 0x03,
    LOAD_STARTUP_SETTINGS = 0x04,
    RESET_TO_DEFAULT = 0x05,
    USE_NEW_SETTINGS_NO_ACKNACK = 0x06
  }

  public enum EnableSetting {
    DISABLED = 0,
    ENABLED = 1
  }

  public enum TimeFrame {
    TIME_FRAME_WEEKS = 0,
    TIME_FRAME_SECONDS = 1
  }

  public enum Command {
    CMD_PING = 0x0101,
    CMD_SET_IDLE = 0x0102,
    CMD_GET_DEVICE_INFO = 0x0103,
    CMD_GET_DESCRIPTOR_SETS = 0x0104,
    CMD_BUILT_IN_TEST = 0x0105,
    CMD_RESUME = 0x0106,
    CMD_GET_EXT_DESCRIPTOR_SETS = 0x0107,
    CMD_COMM_PORT_SPEED = 0x0109,
    CMD_GPS_TIME_UPDATE = 0x0172,
    CMD_RESET = 0x017E,
    CMD_POLL_SENSOR_DATA = 0x0C01,
    CMD_POLL_GNSS_DATA = 0x0C02,
    CMD_POLL_EF_DATA = 0x0C03,
    CMD_GET_SENSOR_RATE_BASE = 0x0C06,
    CMD_GET_GNSS_RATE_BASE = 0x0C07,
    CMD_GET_EF_RATE_BASE = 0x0C0B,
    CMD_SENSOR_MESSAGE_FORMAT = 0x0C08,
    CMD_GNSS_MESSAGE_FORMAT = 0x0C09,
    CMD_EF_MESSAGE_FORMAT = 0x0C0A,
    CMD_POLL = 0x0C0D,
    CMD_GET_BASE_RATE = 0x0C0E,
    CMD_MESSAGE_FORMAT = 0x0C0F,
    CMD_FACTORY_STREAMING = 0x0C10,
    CMD_CONTINUOUS_DATA_STREAM = 0x0C11,
    CMD_RAW_RTCM_2_3_MESSAGE = 0x0C20,
    CMD_GNSS_CONSTELLATION_SETTINGS = 0x0C21,
    CMD_GNSS_SBAS_SETTINGS = 0x0C22,
    CMD_GNSS_ASSIST_FIX_CONTROL = 0x0C23,
    CMD_GNSS_ASSIST_TIME_UPDATE = 0x0C24,
    CMD_PPS_SOURCE = 0x0C28,
    CMD_EVENT_CONTROL = 0x0C2B,
    CMD_EVENT_TRIGGER_CONFIGURATION = 0x0C2E,
    CMD_SAVE_STARTUP_SETTINGS = 0x0C30,
    CMD_EF_SENS_VEHIC_FRAME_TRANSFORM_EULER = 0x0C31,
    CMD_EF_SENS_VEHIC_FRAME_TRANSFORM_QUAT = 0x0C32,
    CMD_EF_SENS_VEHIC_FRAME_TRANSFORM_DCM = 0x0C33,
    CMD_GPS_DYNAMICS_MODE = 0x0C34,
    CMD_SENSOR_SIG_COND_SETTINGS = 0x0C35,
    CMD_SENSOR_TIMESTAMP = 0x0C36,
    CMD_ACCEL_BIAS = 0x0C37,
    CMD_GYRO_BIAS = 0x0C38,
    CMD_CAP_GYRO_BIAS = 0x0C39,
    CMD_MAG_HARD_IRON_OFFSET = 0x0C3A,
    CMD_MAG_SOFT_IRON_MATRIX = 0x0C3B,
    CMD_CF_REALIGN_UP = 0x0C3C,
    CMD_CF_REALIGN_NORTH = 0x0C3D,
    CMD_CONING_SCULLING = 0x0C3E,
    CMD_UART_BAUD_RATE = 0x0C40,
    CMD_GPIO_CONFIGURATION = 0x0C41,
    CMD_GPIO_STATE = 0x0C42,
    CMD_ODOMETER_SETTINGS = 0x0C43,
    CMD_LOWPASS_FILTER_SETTINGS = 0x0C50,
    CMD_COMPLEMENTARY_FILTER_SETTINGS = 0x0C51,
    CMD_SENSOR_RANGE = 0x0C52,
    CMD_SUPPORTED_SENSOR_RANGES = 0x0C53,
    CMD_DATA_STREAM_FORMAT = 0x0C60,
    CMD_POWER_STATES = 0x0C61,
    CMD_GPS_STARTUP_SETTINGS = 0x0C62,
    CMD_DEVICE_STATUS = 0x0C64,
    CMD_EF_RESET_FILTER = 0x0D01,
    CMD_EF_INIT_ATTITUDE = 0x0D02,
    CMD_EF_INIT_HEADING = 0x0D03,
    CMD_EF_INIT_ATTITUDE_FROM_AHRS = 0x0D04,
    CMD_EF_RUN_FILTER = 0x0D05,
    CMD_EF_VEHIC_DYNAMICS_MODE = 0x0D10,
    CMD_EF_SENS_VEHIC_FRAME_ROTATION_EULER = 0x0D11,
    CMD_EF_SENS_VEHIC_FRAME_OFFSET = 0x0D12,
    CMD_EF_ANTENNA_OFFSET = 0x0D13,
    CMD_EF_BIAS_EST_CTRL = 0x0D14,
    CMD_EF_GNSS_SRC_CTRL = 0x0D15,
    CMD_EF_EXTERN_GNSS_UPDATE = 0x0D16,
    CMD_EF_EXTERN_HEADING_UPDATE = 0x0D17,
    CMD_EF_HEADING_UPDATE_CTRL = 0x0D18,
    CMD_EF_AUTO_INIT_CTRL = 0x0D19,
    CMD_EF_ACCEL_WHT_NSE_STD_DEV = 0x0D1A,
    CMD_EF_GYRO_WHT_NSE_STD_DEV = 0x0D1B,
    CMD_EF_ACCEL_BIAS_MODEL_PARAMS = 0x0D1C,
    CMD_EF_GYRO_BIAS_MODEL_PARAMS = 0x0D1D,
    CMD_EF_ZERO_VEL_UPDATE_CTRL = 0x0D1E,
    CMD_EF_EXT_HEADING_UPDATE_TS = 0x0D1F,
    CMD_EF_ZERO_ANG_RATE_UPDATE_CTRL = 0x0D20,
    CMD_EF_TARE_ORIENT = 0x0D21,
    CMD_EF_CMDED_ZERO_VEL_UPDATE = 0x0D22,
    CMD_EF_CMDED_ZERO_ANG_RATE_UPDATE = 0x0D23,
    CMD_EF_SET_REF_POSITION = 0x0D26,
    CMD_EF_MAG_CAPTURE_AUTO_CAL = 0x0D27,
    CMD_EF_GRAVITY_NOISE_STD_DEV = 0x0D28,
    CMD_EF_PRESS_ALT_NOISE_STD_DEV = 0x0D29,
    CMD_EF_GRAVITY_NOISE_MINIMUM = 0x0D2A,
    CMD_EF_HARD_IRON_OFFSET_PROCESS_NOISE = 0x0D2B,
    CMD_EF_SOFT_IRON_OFFSET_PROCESS_NOISE = 0x0D2C,
    CMD_EF_ENABLE_DISABLE_MEASUREMENTS = 0x0D41,
    CMD_EF_MAG_NOISE_STD_DEV = 0x0D42,
    CMD_EF_DECLINATION_SRC = 0x0D43,
    CMD_EF_GRAV_MAGNITUDE_ERR_ADAPT_MEASURE = 0x0D44,
    CMD_EF_MAG_MAGNITUDE_ERR_ADAPT_MEASURE = 0x0D45,
    CMD_EF_MAG_DIP_ANGLE_ERR_ADAPT_MEASURE = 0x0D46,
    CMD_EF_ALTITUDE_AID_CTRL = 0x0D47,
    CMD_EF_PITCH_ROLL_AID_CTRL = 0x0D4B,
    CMD_EF_INCLINATION_SRC = 0x0D4C,
    CMD_EF_FIELD_MAGNITUDE_SRC = 0x0D4D,
    CMD_EF_SENS_VEHIC_FRAME_ROTATION_DCM = 0x0D4E,
    CMD_EF_SENS_VEHIC_FRAME_ROTATION_QUAT = 0x0D4F,
    CMD_EF_AIDING_MEASUREMENT_ENABLE = 0x0D50,
    CMD_EF_INITIALIZATION_CONFIG = 0x0D52,
    CMD_EF_ADAPTIVE_FILTER_OPTIONS = 0x0D53,
    CMD_EF_MULTI_ANTENNA_OFFSET = 0x0D54,
    CMD_EF_RELATIVE_POSITION_REF = 0x0D55,
    CMD_EF_EXTERN_SPEED_UPDATE = 0x0D60,
    CMD_EF_SPEED_MEASUREMENT_OFFSET = 0x0D61,
    CMD_EF_VERTICAL_GYRO_CONSTRAINT = 0x0D62,
    CMD_EF_WHEELED_VEHICLE_CONSTRAINT = 0x0D63,
    CMD_EF_GNSS_ANTENNA_LEVER_ARM_CAL = 0x0D64,
    CMD_GNSS_RECEIVER_INFO = 0x0E01,
    CMD_GNSS_SIGNAL_CONFIG = 0x0E02,
    CMD_GNSS_RTK_CONFIG = 0x0E10,
    CMD_COMMUNICATION_MODE = 0x7F10,
    CMD_HARDWARE_CTRL = 0x7F11,
    CMD_GET_ANALOG_DISPLACEMENT_CALS = 0x1101,
    CMD_DISPLACEMENT_OUTPUT_RATE = 0x1102,
    CMD_DISPLACEMENT_DEVICE_TIME = 0x1104,
    CMD_RTK_DEVICE_STATUS_FLAGS = 0x0F01,
    CMD_RTK_ACTIVATION_CODE = 0x0F07
  }

  public enum ChannelField {
    CH_FIELD_SENSOR_RAW_ACCEL_VEC = 0x8001,
    CH_FIELD_SENSOR_RAW_GYRO_VEC = 0x8002,
    CH_FIELD_SENSOR_RAW_MAG_VEC = 0x8003,
    CH_FIELD_SENSOR_SCALED_ACCEL_VEC = 0x8004,
    CH_FIELD_SENSOR_SCALED_GYRO_VEC = 0x8005,
    CH_FIELD_SENSOR_SCALED_MAG_VEC = 0x8006,
    CH_FIELD_SENSOR_DELTA_THETA_VEC = 0x8007,
    CH_FIELD_SENSOR_DELTA_VELOCITY_VEC = 0x8008,
    CH_FIELD_SENSOR_ORIENTATION_MATRIX = 0x8009,
    CH_FIELD_SENSOR_ORIENTATION_QUATERNION = 0x800A,
    CH_FIELD_SENSOR_ORIENTATION_UPDATE_MATRIX = 0x800B,
    CH_FIELD_SENSOR_EULER_ANGLES = 0x800C,
    CH_FIELD_SENSOR_INTERNAL_TIMESTAMP = 0x800E,
    CH_FIELD_SENSOR_BEACONED_TIMESTAMP = 0x800F,
    CH_FIELD_SENSOR_STABILIZED_MAG_VEC = 0x8010,
    CH_FIELD_SENSOR_STABILIZED_ACCEL_VEC = 0x8011,
    CH_FIELD_SENSOR_GPS_CORRELATION_TIMESTAMP = 0x8012,
    CH_FIELD_SENSOR_TEMPERATURE_STATISTICS = 0x8014,
    CH_FIELD_SENSOR_RAW_AMBIENT_PRESSURE = 0x8016,
    CH_FIELD_SENSOR_SCALED_AMBIENT_PRESSURE = 0x8017,
    CH_FIELD_SENSOR_ODOMETER_DATA = 0x8040,
    CH_FIELD_SENSOR_SHARED_TICKS = 0x80D1,
    CH_FIELD_SENSOR_SHARED_DELTA_TICKS = 0x80D2,
    CH_FIELD_SENSOR_SHARED_GPS_TIMESTAMP = 0x80D3,
    CH_FIELD_SENSOR_SHARED_DELTA_TIMESTAMP = 0x80D4,
    CH_FIELD_GNSS_LLH_POSITION = 0x8103,
    CH_FIELD_GNSS_ECEF_POSITION = 0x8104,
    CH_FIELD_GNSS_NED_VELOCITY = 0x8105,
    CH_FIELD_GNSS_ECEF_VELOCITY = 0x8106,
    CH_FIELD_GNSS_DOP = 0x8107,
    CH_FIELD_GNSS_UTC_TIME = 0x8108,
    CH_FIELD_GNSS_GPS_TIME = 0x8109,
    CH_FIELD_GNSS_CLOCK_INFO = 0x810A,
    CH_FIELD_GNSS_FIX_INFO = 0x810B,
    CH_FIELD_GNSS_SPACE_VEHICLE_INFO = 0x810C,
    CH_FIELD_GNSS_HARDWARE_STATUS = 0x810D,
    CH_FIELD_GNSS_DGNSS_INFO = 0x810E,
    CH_FIELD_GNSS_DGNSS_CHANNEL_STATUS = 0x810F,
    CH_FIELD_GNSS_CLOCK_INFO_2 = 0x8110,
    CH_FIELD_GNSS_GPS_LEAP_SECONDS = 0x8111,
    CH_FIELD_GNSS_SATELLITE_STATUS = 0x8120,
    CH_FIELD_GNSS_RAW_OBSERVATION = 0x8122,
    CH_FIELD_GNSS_STATION_INFO = 0x8130,
    CH_FIELD_GNSS_RTK_CORRECTIONS_STATUS = 0x8131,
    CH_FIELD_GNSS_GPS_EPHEMERIS = 0x8161,
    CH_FIELD_GNSS_GLONASS_EPHEMERIS = 0x8162,
    CH_FIELD_GNSS_GALILEO_EPHEMERIS = 0x8163,
    CH_FIELD_GNSS_GPS_IONOSPHERIC_CORRECTION = 0x8171,
    CH_FIELD_GNSS_GALILEO_IONOSPHERIC_CORRECTION = 0x8173,
    CH_FIELD_GNSS_SHARED_TICKS = 0x81D1,
    CH_FIELD_GNSS_SHARED_DELTA_TICKS = 0x81D2,
    CH_FIELD_GNSS_SHARED_GPS_TIMESTAMP = 0x81D3,
    CH_FIELD_GNSS_SHARED_DELTA_TIMESTAMP = 0x81D4,
    CH_FIELD_ESTFILTER_ESTIMATED_LLH_POS = 0x8201,
    CH_FIELD_ESTFILTER_ESTIMATED_NED_VELOCITY = 0x8202,
    CH_FIELD_ESTFILTER_ESTIMATED_ORIENT_QUATERNION = 0x8203,
    CH_FIELD_ESTFILTER_ESTIMATED_ORIENT_MATRIX = 0x8204,
    CH_FIELD_ESTFILTER_ESTIMATED_ORIENT_EULER = 0x8205,
    CH_FIELD_ESTFILTER_ESTIMATED_GYRO_BIAS = 0x8206,
    CH_FIELD_ESTFILTER_ESTIMATED_ACCEL_BIAS = 0x8207,
    CH_FIELD_ESTFILTER_ESTIMATED_LLH_UNCERT = 0x8208,
    CH_FIELD_ESTFILTER_ESTIMATED_NED_UNCERT = 0x8209,
    CH_FIELD_ESTFILTER_ESTIMATED_ATT_UNCERT_EULER = 0x820A,
    CH_FIELD_ESTFILTER_ESTIMATED_GYRO_BIAS_UNCERT = 0x820B,
    CH_FIELD_ESTFILTER_ESTIMATED_ACCEL_BIAS_UNCERT = 0x820C,
    CH_FIELD_ESTFILTER_ESTIMATED_LINEAR_ACCEL = 0x820D,
    CH_FIELD_ESTFILTER_ESTIMATED_ANGULAR_RATE = 0x820E,
    CH_FIELD_ESTFILTER_WGS84_LOC_GRAV_MAGNITUDE = 0x820F,
    CH_FIELD_ESTFILTER_FILTER_STATUS = 0x8210,
    CH_FIELD_ESTFILTER_GPS_TIMESTAMP = 0x8211,
    CH_FIELD_ESTFILTER_ESTIMATED_ATT_UNCERT_QUAT = 0x8212,
    CH_FIELD_ESTFILTER_ESTIMATED_GRAVITY_VECTOR = 0x8213,
    CH_FIELD_ESTFILTER_HEADING_UPDATE_SOURCE = 0x8214,
    CH_FIELD_ESTFILTER_MAGNETIC_MODEL_SLN = 0x8215,
    CH_FIELD_ESTFILTER_ESTIMATED_GYRO_SCALE_FACTOR = 0x8216,
    CH_FIELD_ESTFILTER_ACCEL_SCALE_FACTOR = 0x8217,
    CH_FIELD_ESTFILTER_GYRO_SCALE_FACTOR_UNCERT = 0x8218,
    CH_FIELD_ESTFILTER_ACCEL_SCALE_FACTOR_UNCERT = 0x8219,
    CH_FIELD_ESTFILTER_MAG_BIAS = 0x821A,
    CH_FIELD_ESTFILTER_MAG_BIAS_UNCERT = 0x821B,
    CH_FIELD_ESTFILTER_COMPENSATED_ACCEL = 0x821C,
    CH_FIELD_ESTFILTER_STD_ATMOSPHERE_MODEL = 0x8220,
    CH_FIELD_ESTFILTER_PRESSURE_ALTITUDE = 0x8221,
    CH_FIELD_ESTFILTER_MAG_AUTO_HARD_IRON_OFFSET = 0x8225,
    CH_FIELD_ESTFILTER_MAG_AUTO_SOFT_IRON_MATRIX = 0x8226,
    CH_FIELD_ESTFILTER_MAG_AUTO_HARD_IRON_OFFSET_UNCERT = 0x8228,
    CH_FIELD_ESTFILTER_MAG_AUTO_SOFT_IRON_MATRIX_UNCERT = 0x8229,
    CH_FIELD_ESTFILTER_MAG_COVARIANCE_MATRIX = 0x822A,
    CH_FIELD_ESTFILTER_MAG_RESIDUAL_VECTOR = 0x822C,
    CH_FIELD_ESTFILTER_GNSS_ANTENNA_CORRECTION = 0x8230,
    CH_FIELD_ESTFILTER_GNSS_ANTENNA_CORRECTION_UNCERT = 0x8231,
    CH_FIELD_ESTFILTER_GNSS_CLOCK_CORRECTION = 0x8232,
    CH_FIELD_ESTFILTER_GNSS_CLOCK_CORRECTION_UNCERT = 0x8233,
    CH_FIELD_ESTFILTER_GNSS_MULTI_ANTENNA_CORRECTION = 0x8234,
    CH_FIELD_ESTFILTER_GNSS_MULTI_ANTENNA_CORRECTION_UNCERT = 0x8235,
    CH_FIELD_ESTFILTER_ECEF_POS_UNCERT = 0x8236,
    CH_FIELD_ESTFILTER_ECEF_VEL_UNCERT = 0x8237,
    CH_FIELD_ESTFILTER_ECEF_POS = 0x8240,
    CH_FIELD_ESTFILTER_ECEF_VEL = 0x8241,
    CH_FIELD_ESTFILTER_NED_RELATIVE_POS = 0x8242,
    CH_FIELD_ESTFILTER_POSITION_AIDING_STATUS = 0x8243,
    CH_FIELD_ESTFILTER_ATTITUDE_AIDING_STATUS = 0x8244,
    CH_FIELD_ESTFILTER_AIDING_MEASURE_SUMMARY = 0x8246,
    CH_FIELD_ESTFILTER_ODOMETER_SCALE_FACTOR_ERROR = 0x8247,
    CH_FIELD_ESTFILTER_ODOMETER_SCALE_FACTOR_ERROR_UNCERT = 0X8248,
    CH_FIELD_ESTFILTER_GNSS_DUAL_ANTENNA_STATUS = 0x8249,
    CH_FIELD_ESTFILTER_SHARED_TICKS = 0x82D1,
    CH_FIELD_ESTFILTER_SHARED_DELTA_TICKS = 0x82D2,
    CH_FIELD_ESTFILTER_SHARED_GPS_TIMESTAMP = 0x82D3,
    CH_FIELD_ESTFILTER_SHARED_DELTA_TIMESTAMP = 0x82D4,
    CH_FIELD_DISP_DISPLACEMENT_RAW = 0x9001,
    CH_FIELD_DISP_DISPLACEMENT_MM = 0x9002,
    CH_FIELD_DISP_DISPLACEMENT_TS = 0x9004,
    CH_FIELD_GNSS_1_LLH_POSITION = 0x9103,
    CH_FIELD_GNSS_1_ECEF_POSITION = 0x9104,
    CH_FIELD_GNSS_1_NED_VELOCITY = 0x9105,
    CH_FIELD_GNSS_1_ECEF_VELOCITY = 0x9106,
    CH_FIELD_GNSS_1_DOP = 0x9107,
    CH_FIELD_GNSS_1_UTC_TIME = 0x9108,
    CH_FIELD_GNSS_1_GPS_TIME = 0x9109,
    CH_FIELD_GNSS_1_CLOCK_INFO = 0x910A,
    CH_FIELD_GNSS_1_FIX_INFO = 0x910B,
    CH_FIELD_GNSS_1_SPACE_VEHICLE_INFO = 0x910C,
    CH_FIELD_GNSS_1_HARDWARE_STATUS = 0x910D,
    CH_FIELD_GNSS_1_DGNSS_INFO = 0x910E,
    CH_FIELD_GNSS_1_DGNSS_CHANNEL_STATUS = 0x910F,
    CH_FIELD_GNSS_1_CLOCK_INFO_2 = 0x9110,
    CH_FIELD_GNSS_1_GPS_LEAP_SECONDS = 0x9111,
    CH_FIELD_GNSS_1_SATELLITE_STATUS = 0x9120,
    CH_FIELD_GNSS_1_RAW_OBSERVATION = 0x9122,
    CH_FIELD_GNSS_1_STATION_INFO = 0x9130,
    CH_FIELD_GNSS_1_RTK_CORRECTIONS_STATUS = 0x9131,
    CH_FIELD_GNSS_1_GPS_EPHEMERIS = 0x9161,
    CH_FIELD_GNSS_1_GLONASS_EPHEMERIS = 0x9162,
    CH_FIELD_GNSS_1_GALILEO_EPHEMERIS = 0x9163,
    CH_FIELD_GNSS_1_GPS_IONOSPHERIC_CORRECTION = 0x9171,
    CH_FIELD_GNSS_1_GALILEO_IONOSPHERIC_CORRECTION = 0x9173,
    CH_FIELD_GNSS_1_SHARED_TICKS = 0x91D1,
    CH_FIELD_GNSS_1_SHARED_DELTA_TICKS = 0x91D2,
    CH_FIELD_GNSS_1_SHARED_GPS_TIMESTAMP = 0x91D3,
    CH_FIELD_GNSS_1_SHARED_DELTA_TIMESTAMP = 0x91D4,
    CH_FIELD_GNSS_2_LLH_POSITION = 0x9203,
    CH_FIELD_GNSS_2_ECEF_POSITION = 0x9204,
    CH_FIELD_GNSS_2_NED_VELOCITY = 0x9205,
    CH_FIELD_GNSS_2_ECEF_VELOCITY = 0x9206,
    CH_FIELD_GNSS_2_DOP = 0x9207,
    CH_FIELD_GNSS_2_UTC_TIME = 0x9208,
    CH_FIELD_GNSS_2_GPS_TIME = 0x9209,
    CH_FIELD_GNSS_2_CLOCK_INFO = 0x920A,
    CH_FIELD_GNSS_2_FIX_INFO = 0x920B,
    CH_FIELD_GNSS_2_SPACE_VEHICLE_INFO = 0x920C,
    CH_FIELD_GNSS_2_HARDWARE_STATUS = 0x920D,
    CH_FIELD_GNSS_2_DGNSS_INFO = 0x920E,
    CH_FIELD_GNSS_2_DGNSS_CHANNEL_STATUS = 0x920F,
    CH_FIELD_GNSS_2_CLOCK_INFO_2 = 0x9210,
    CH_FIELD_GNSS_2_GPS_LEAP_SECONDS = 0x9211,
    CH_FIELD_GNSS_2_SATELLITE_STATUS = 0x9220,
    CH_FIELD_GNSS_2_RAW_OBSERVATION = 0x9222,
    CH_FIELD_GNSS_2_STATION_INFO = 0x9230,
    CH_FIELD_GNSS_2_RTK_CORRECTIONS_STATUS = 0x9231,
    CH_FIELD_GNSS_2_GPS_EPHEMERIS = 0x9261,
    CH_FIELD_GNSS_2_GLONASS_EPHEMERIS = 0x9262,
    CH_FIELD_GNSS_2_GALILEO_EPHEMERIS = 0x9263,
    CH_FIELD_GNSS_2_GPS_IONOSPHERIC_CORRECTION = 0x9271,
    CH_FIELD_GNSS_2_GALILEO_IONOSPHERIC_CORRECTION = 0x9273,
    CH_FIELD_GNSS_2_SHARED_TICKS = 0x92D1,
    CH_FIELD_GNSS_2_SHARED_DELTA_TICKS = 0x92D2,
    CH_FIELD_GNSS_2_SHARED_GPS_TIMESTAMP = 0x92D3,
    CH_FIELD_GNSS_2_SHARED_DELTA_TIMESTAMP = 0x92D4,
    CH_FIELD_GNSS_3_LLH_POSITION = 0x9303,
    CH_FIELD_GNSS_3_ECEF_POSITION = 0x9304,
    CH_FIELD_GNSS_3_NED_VELOCITY = 0x9305,
    CH_FIELD_GNSS_3_ECEF_VELOCITY = 0x9306,
    CH_FIELD_GNSS_3_DOP = 0x9307,
    CH_FIELD_GNSS_3_UTC_TIME = 0x9308,
    CH_FIELD_GNSS_3_GPS_TIME = 0x9309,
    CH_FIELD_GNSS_3_CLOCK_INFO = 0x930A,
    CH_FIELD_GNSS_3_FIX_INFO = 0x930B,
    CH_FIELD_GNSS_3_SPACE_VEHICLE_INFO = 0x930C,
    CH_FIELD_GNSS_3_HARDWARE_STATUS = 0x930D,
    CH_FIELD_GNSS_3_DGNSS_INFO = 0x930E,
    CH_FIELD_GNSS_3_DGNSS_CHANNEL_STATUS = 0x930F,
    CH_FIELD_GNSS_3_CLOCK_INFO_2 = 0x9310,
    CH_FIELD_GNSS_3_GPS_LEAP_SECONDS = 0x9311,
    CH_FIELD_GNSS_3_SATELLITE_STATUS = 0x9320,
    CH_FIELD_GNSS_3_RAW_OBSERVATION = 0x9322,
    CH_FIELD_GNSS_3_STATION_INFO = 0x9330,
    CH_FIELD_GNSS_3_RTK_CORRECTIONS_STATUS = 0x9331,
    CH_FIELD_GNSS_3_GPS_EPHEMERIS = 0x9361,
    CH_FIELD_GNSS_3_GLONASS_EPHEMERIS = 0x9362,
    CH_FIELD_GNSS_3_GALILEO_EPHEMERIS = 0x9363,
    CH_FIELD_GNSS_3_GPS_IONOSPHERIC_CORRECTION = 0x9371,
    CH_FIELD_GNSS_3_GALILEO_IONOSPHERIC_CORRECTION = 0x9373,
    CH_FIELD_GNSS_3_SHARED_TICKS = 0x93D1,
    CH_FIELD_GNSS_3_SHARED_DELTA_TICKS = 0x93D2,
    CH_FIELD_GNSS_3_SHARED_GPS_TIMESTAMP = 0x93D3,
    CH_FIELD_GNSS_3_SHARED_DELTA_TIMESTAMP = 0x93D4,
    CH_FIELD_GNSS_4_LLH_POSITION = 0x9403,
    CH_FIELD_GNSS_4_ECEF_POSITION = 0x9404,
    CH_FIELD_GNSS_4_NED_VELOCITY = 0x9405,
    CH_FIELD_GNSS_4_ECEF_VELOCITY = 0x9406,
    CH_FIELD_GNSS_4_DOP = 0x9407,
    CH_FIELD_GNSS_4_UTC_TIME = 0x9408,
    CH_FIELD_GNSS_4_GPS_TIME = 0x9409,
    CH_FIELD_GNSS_4_CLOCK_INFO = 0x940A,
    CH_FIELD_GNSS_4_FIX_INFO = 0x940B,
    CH_FIELD_GNSS_4_SPACE_VEHICLE_INFO = 0x940C,
    CH_FIELD_GNSS_4_HARDWARE_STATUS = 0x940D,
    CH_FIELD_GNSS_4_DGNSS_INFO = 0x940E,
    CH_FIELD_GNSS_4_DGNSS_CHANNEL_STATUS = 0x940F,
    CH_FIELD_GNSS_4_CLOCK_INFO_2 = 0x9410,
    CH_FIELD_GNSS_4_GPS_LEAP_SECONDS = 0x9411,
    CH_FIELD_GNSS_4_SATELLITE_STATUS = 0x9420,
    CH_FIELD_GNSS_4_RAW_OBSERVATION = 0x9422,
    CH_FIELD_GNSS_4_STATION_INFO = 0x9430,
    CH_FIELD_GNSS_4_RTK_CORRECTIONS_STATUS = 0x9431,
    CH_FIELD_GNSS_4_GPS_EPHEMERIS = 0x9461,
    CH_FIELD_GNSS_4_GLONASS_EPHEMERIS = 0x9462,
    CH_FIELD_GNSS_4_GALILEO_EPHEMERIS = 0x9463,
    CH_FIELD_GNSS_4_GPS_IONOSPHERIC_CORRECTION = 0x9471,
    CH_FIELD_GNSS_4_GALILEO_IONOSPHERIC_CORRECTION = 0x9473,
    CH_FIELD_GNSS_4_SHARED_TICKS = 0x94D1,
    CH_FIELD_GNSS_4_SHARED_DELTA_TICKS = 0x94D2,
    CH_FIELD_GNSS_4_SHARED_GPS_TIMESTAMP = 0x94D3,
    CH_FIELD_GNSS_4_SHARED_DELTA_TIMESTAMP = 0x94D4,
    CH_FIELD_GNSS_5_LLH_POSITION = 0x9503,
    CH_FIELD_GNSS_5_ECEF_POSITION = 0x9504,
    CH_FIELD_GNSS_5_NED_VELOCITY = 0x9505,
    CH_FIELD_GNSS_5_ECEF_VELOCITY = 0x9506,
    CH_FIELD_GNSS_5_DOP = 0x9507,
    CH_FIELD_GNSS_5_UTC_TIME = 0x9508,
    CH_FIELD_GNSS_5_GPS_TIME = 0x9509,
    CH_FIELD_GNSS_5_CLOCK_INFO = 0x950A,
    CH_FIELD_GNSS_5_FIX_INFO = 0x950B,
    CH_FIELD_GNSS_5_SPACE_VEHICLE_INFO = 0x950C,
    CH_FIELD_GNSS_5_HARDWARE_STATUS = 0x950D,
    CH_FIELD_GNSS_5_DGNSS_INFO = 0x950E,
    CH_FIELD_GNSS_5_DGNSS_CHANNEL_STATUS = 0x950F,
    CH_FIELD_GNSS_5_CLOCK_INFO_2 = 0x9510,
    CH_FIELD_GNSS_5_GPS_LEAP_SECONDS = 0x9511,
    CH_FIELD_GNSS_5_SATELLITE_STATUS = 0x9520,
    CH_FIELD_GNSS_5_RAW_OBSERVATION = 0x9522,
    CH_FIELD_GNSS_5_STATION_INFO = 0x9530,
    CH_FIELD_GNSS_5_RTK_CORRECTIONS_STATUS = 0x9531,
    CH_FIELD_GNSS_5_GPS_EPHEMERIS = 0x9561,
    CH_FIELD_GNSS_5_GLONASS_EPHEMERIS = 0x9562,
    CH_FIELD_GNSS_5_GALILEO_EPHEMERIS = 0x9563,
    CH_FIELD_GNSS_5_GPS_IONOSPHERIC_CORRECTION = 0x9571,
    CH_FIELD_GNSS_5_GALILEO_IONOSPHERIC_CORRECTION = 0x9573,
    CH_FIELD_GNSS_5_SHARED_TICKS = 0x95D1,
    CH_FIELD_GNSS_5_SHARED_DELTA_TICKS = 0x95D2,
    CH_FIELD_GNSS_5_SHARED_GPS_TIMESTAMP = 0x95D3,
    CH_FIELD_GNSS_5_SHARED_DELTA_TIMESTAMP = 0x95D4
  }

  public enum ChannelQualifier {
    CH_UNKNOWN = 0,
    CH_X = 1,
    CH_Y = 2,
    CH_Z = 3,
    CH_MATRIX = 4,
    CH_QUATERNION = 5,
    CH_ROLL = 6,
    CH_PITCH = 7,
    CH_YAW = 8,
    CH_TICK = 9,
    CH_TIMESTAMP = 10,
    CH_STATUS = 11,
    CH_TIME_OF_WEEK = 12,
    CH_WEEK_NUMBER = 13,
    CH_LATITUDE = 14,
    CH_LONGITUDE = 15,
    CH_HEIGHT_ABOVE_ELLIPSOID = 16,
    CH_HEIGHT_ABOVE_MSL = 17,
    CH_HORIZONTAL_ACCURACY = 18,
    CH_VERTICAL_ACCURACY = 19,
    CH_POSITION_ACCURACY = 20,
    CH_NORTH = 21,
    CH_EAST = 22,
    CH_DOWN = 23,
    CH_SPEED = 24,
    CH_GROUND_SPEED = 25,
    CH_HEADING = 26,
    CH_SPEED_ACCURACY = 27,
    CH_HEADING_ACCURACY = 28,
    CH_VELOCITY_ACCURACY = 29,
    CH_GEOMETRIC_DOP = 30,
    CH_POSITION_DOP = 31,
    CH_HORIZONTAL_DOP = 32,
    CH_VERTICAL_DOP = 33,
    CH_TIME_DOP = 34,
    CH_NORTHING_DOP = 35,
    CH_EASTING_DOP = 36,
    CH_FLAGS = 37,
    CH_BIAS = 38,
    CH_DRIFT = 39,
    CH_ACCURACY_ESTIMATE = 40,
    CH_FIX_TYPE = 41,
    CH_SV_COUNT = 42,
    CH_CHANNEL = 43,
    CH_ID = 44,
    CH_CARRIER_TO_NOISE_RATIO = 45,
    CH_AZIMUTH = 46,
    CH_ELEVATION = 47,
    CH_SENSOR_STATE = 48,
    CH_ANTENNA_STATE = 49,
    CH_ANTENNA_POWER = 50,
    CH_FILTER_STATE = 51,
    CH_DYNAMICS_MODE = 52,
    CH_MAGNITUDE = 53,
    CH_HEADING_UNCERTAINTY = 54,
    CH_SOURCE = 55,
    CH_INCLINATION = 56,
    CH_DECLINATION = 57,
    CH_PRESSURE = 58,
    CH_AGE = 59,
    CH_NUM_CHANNELS = 60,
    CH_CORRECTION = 61,
    CH_RATE_CORRECTION = 62,
    CH_GEOMETRIC_ALTITUDE = 63,
    CH_GEOPOTENTIAL_ALTITUDE = 64,
    CH_TEMPERATURE = 65,
    CH_DENSITY = 66,
    CH_ALTITUDE = 67,
    CH_DISPLACEMENT = 68,
    CH_MAX_TEMP = 69,
    CH_MIN_TEMP = 70,
    CH_MEAN_TEMP = 71,
    CH_BIAS_ACCURACY_ESTIMATE = 72,
    CH_DRIFT_ACCURACY_ESTIMATE = 73,
    CH_SECONDS = 74,
    CH_NUM_PACKETS = 76,
    CH_GPS_CORRECTION_LATENCY = 77,
    CH_GLONASS_CORRECTION_LATENCY = 78,
    CH_GALILEO_CORRECTION_LATENCY = 79,
    CH_BEIDOU_CORRECTION_LATENCY = 80,
    CH_HEIGHT = 81,
    CH_HEALTH = 82,
    CH_INDEX = 83,
    CH_COUNT = 84,
    CH_SIGNAL_STRENGTH = 85,
    CH_SIGNAL_QUALITY = 86,
    CH_RANGE = 87,
    CH_RANGE_UNC = 88,
    CH_ALPHA = 90,
    CH_BETA = 91,
    CH_DISTURBANCE_FLAGS = 92,
    CH_CARRIER_PHASE = 93,
    CH_CARRIER_PHASE_UNC = 94,
    CH_DOPPLER = 95,
    CH_DOPPLER_UNC = 96,
    CH_DELTA_TIME = 97,
    CH_DELTA_TICK = 98,
    CH_ERROR = 99,
    CH_ERROR_UNC = 100
  }

}

}
