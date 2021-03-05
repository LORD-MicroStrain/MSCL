/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/

#pragma once

#include <string>
#include <vector>
#include "mscl/MicroStrain/Wireless/ChannelMask.h"

namespace mscl
{
    //API Class: ConfigIssue
    //    Holds information on a specific configuration issue.
    class ConfigIssue
    {
    public:
        //API Enums: ConfigOption
        //  Configuration Options for Wireless Nodes and BaseStations that can be issues.
        //
        //  CONFIG_SAMPLING_MODE                - 0 - Sampling Mode
        //  CONFIG_ACTIVE_CHANNELS              - 1 - Active Channels
        //  CONFIG_SAMPLE_RATE                  - 2 - Sample Rate
        //  CONFIG_SWEEPS                       - 3 - Number of Sweeps
        //  CONFIG_UNLIMITED_DURATION           - 4 - Unlimited Duration
        //  CONFIG_DATA_FORMAT                  - 5 - Data Format
        //  CONFIG_DATA_COLLECTION_METHOD       - 6 - Data Collection Method
        //  CONFIG_TIME_BETWEEN_BURSTS          - 7 - Time Between Bursts
        //  CONFIG_THERMOCOUPLE_TYPE            - 8 - Thermocouple Type
        //  CONFIG_FILTER_SETTLING_TIME         - 9  - Filter Settling Time
        //  CONFIG_BUTTON                       - 10 - Button configuration (BaseStation)
        //  CONFIG_ANALOG_PAIR                  - 11 - Analog pairing (BaseStation)
        //  CONFIG_INPUT_RANGE                  - 12 - Input Range
        //  CONFIG_INACTIVITY_TIMEOUT           - 13 - Inactivity Timeout
        //  CONFIG_CHECK_RADIO_INTERVAL         - 14 - Check Radio Interval
        //  CONFIG_LOST_BEACON_TIMEOUT          - 15 - Lost Beacon Timeout
        //  CONFIG_DEFAULT_MODE                 - 16 - Default Mode
        //  CONFIG_TRANSMIT_POWER               - 17 - Transmit Power
        //  CONFIG_LINEAR_EQUATION              - 18 - Linear Equation
        //  CONFIG_FATIGUE                      - 19 - Fatigue Options
        //  CONFIG_FATIGUE_MODE                 - 20 - Fatigue Options - Fatigue Mode
        //  CONFIG_FATIGUE_ANGLE_ID             - 21 - Fatigue Options - Angle ID
        //  CONFIG_FATIGUE_SN_CURVE             - 22 - Fatigue Options - SN Curve Segment
        //  CONFIG_FATIGUE_DIST_NUM_ANGLES      - 23 - Fatigue Options - Number of Distributed Angles
        //  CONFIG_FATIGUE_DIST_ANGLE           - 24 - Fatigue Options - Low/Upper Distributed Angle
        //  CONFIG_HISTOGRAM                    - 25 - Histogram Options
        //  CONFIG_HISTOGRAM_TX_RATE            - 26 - Histogram Transmit Rate
        //  CONFIG_HARDWARE_OFFSET              - 27 - Hardware Offset
        //  CONFIG_ACTIVITY_SENSE               - 28 - Activity Sense
        //  CONFIG_GAUGE_FACTOR                 - 29 - Gauge Factor
        //  CONFIG_EVENT_TRIGGER                - 30 - Event Trigger
        //  CONFIG_EVENT_TRIGGER_DURATION       - 31 - Event Trigger - Total Duration
        //  CONFIG_EVENT_TRIGGER_MASK           - 32 - Event Trigger - Trigger Mask
        //  CONFIG_DIAGNOSTIC_INTERVAL          - 33 - Diagnostic Info Interval
        //  CONFIG_ANTI_ALIASING_FILTER         - 34 - Anti-Aliasing Filter
        //  CONFIG_STORAGE_LIMIT_MODE           - 35 - Storage Limit Mode
        //  CONFIG_SENSOR_DELAY                 - 36 - Sensor Delay
        //  CONFIG_LOW_PASS_FILTER              - 37 - Low Pass Filter
        //  CONFIG_DATA_MODE                    - 38 - Data Mode
        //  CONFIG_DERIVED_DATA_RATE            - 39 - Derived Data Rate
        //  CONFIG_DERIVED_MASK_RMS             - 40 - Derived RMS Mask
        //  CONFIG_DERIVED_MASK_P2P             - 41 - Derived Peak to Peak Mask
        //  CONFIG_DERIVED_MASK_IPS             - 42 - Derived IPS Mask
        //  CONFIG_DERIVED_MASK_CREST_FACTOR    - 43 - Derived Crest Factor Mask
        //  CONFIG_HIGH_PASS_FILTER             - 44 - High Pass Filter
        //  CONFIG_DERIVED_MASK                 - 45 - Derived Mask (all masks issue)
        //  CONFIG_COMM_PROTOCOL                - 46 - Communication Protocol
        //  CONFIG_DERIVED_MASK_MEAN            - 47 - Derived Mean Mask
        //  CONFIG_GAUGE_RESISTANCE             - 48 - Gauge Resistance
        //  CONFIG_NUM_ACTIVE_GAUGES            - 49 - Number of Active Gauges
        //  CONFIG_TEMP_SENSOR_OPTS             - 50 - Temp Sensor Options
        //  CONFIG_DEBOUNCE_FILTER              - 51 - Debounce Filter
        //  CONFIG_PULLUP_RESISTOR              - 52 - Pull-up Resistor
        //  CONFIG_EXCITATION_VOLTAGE           - 53 - Excitation Voltage
        //  CONFIG_DERIVED_UNIT                 - 54 - Derived Unit
        //  CONFIG_SENSOR_OUTPUT_MODE           - 55 - Sensor Output Mode
        //  CONFIG_LOW_BATTERY_THRESHOLD        - 56 - Low Battery Threshold
        enum ConfigOption
        {
            CONFIG_SAMPLING_MODE                = 0,
            CONFIG_ACTIVE_CHANNELS              = 1,
            CONFIG_SAMPLE_RATE                  = 2,
            CONFIG_SWEEPS                       = 3,
            CONFIG_UNLIMITED_DURATION           = 4,
            CONFIG_DATA_FORMAT                  = 5,
            CONFIG_DATA_COLLECTION_METHOD       = 6,
            CONFIG_TIME_BETWEEN_BURSTS          = 7,
            CONFIG_THERMOCOUPLE_TYPE            = 8,
            CONFIG_FILTER_SETTLING_TIME         = 9,
            CONFIG_BUTTON                       = 10,
            CONFIG_ANALOG_PAIR                  = 11,
            CONFIG_INPUT_RANGE                  = 12,
            CONFIG_INACTIVITY_TIMEOUT           = 13,
            CONFIG_CHECK_RADIO_INTERVAL         = 14,
            CONFIG_LOST_BEACON_TIMEOUT          = 15,
            CONFIG_DEFAULT_MODE                 = 16,
            CONFIG_TRANSMIT_POWER               = 17,
            CONFIG_LINEAR_EQUATION              = 18,
            CONFIG_FATIGUE                      = 19,
            CONFIG_FATIGUE_MODE                 = 20,
            CONFIG_FATIGUE_ANGLE_ID             = 21,
            CONFIG_FATIGUE_SN_CURVE             = 22,
            CONFIG_FATIGUE_DIST_NUM_ANGLES      = 23,
            CONFIG_FATIGUE_DIST_ANGLE           = 24,
            CONFIG_HISTOGRAM                    = 25,
            CONFIG_HISTOGRAM_TX_RATE            = 26,
            CONFIG_HARDWARE_OFFSET              = 27,
            CONFIG_ACTIVITY_SENSE               = 28,
            CONFIG_GAUGE_FACTOR                 = 29,
            CONFIG_EVENT_TRIGGER                = 30,
            CONFIG_EVENT_TRIGGER_DURATION       = 31,
            CONFIG_EVENT_TRIGGER_MASK           = 32,
            CONFIG_DIAGNOSTIC_INTERVAL          = 33,
            CONFIG_ANTI_ALIASING_FILTER         = 34,
            CONFIG_STORAGE_LIMIT_MODE           = 35,
            CONFIG_SENSOR_DELAY                 = 36,
            CONFIG_LOW_PASS_FILTER              = 37,
            CONFIG_DATA_MODE                    = 38,
            CONFIG_DERIVED_DATA_RATE            = 39,
            CONFIG_DERIVED_MASK_RMS             = 40,
            CONFIG_DERIVED_MASK_P2P             = 41,
            CONFIG_DERIVED_MASK_IPS             = 42,
            CONFIG_DERIVED_MASK_CREST_FACTOR    = 43,
            CONFIG_HIGH_PASS_FILTER             = 44,
            CONFIG_DERIVED_MASK                 = 45,
            CONFIG_COMM_PROTOCOL                = 46,
            CONFIG_DERIVED_MASK_MEAN            = 47,
            CONFIG_GAUGE_RESISTANCE             = 48,
            CONFIG_NUM_ACTIVE_GAUGES            = 49,
            CONFIG_TEMP_SENSOR_OPTS             = 50,
            CONFIG_DEBOUNCE_FILTER              = 51,
            CONFIG_PULLUP_RESISTOR              = 52,
            CONFIG_EXCITATION_VOLTAGE           = 53,
            CONFIG_DERIVED_UNIT                 = 54,
            CONFIG_SENSOR_OUTPUT_MODE           = 55,
            CONFIG_LOW_BATTERY_THRESHOLD        = 56,
            CONFIG_CFC_FILTER                   = 57
        };

        ConfigIssue();    //default constructor

        //API Constructor: ConfigIssue
        //    Creates a ConfigIssue object.
        //
        //Parameters:
        //    optionId - The <ConfigOption> identifying the configuration option for which the issue occurred.
        //    description - A description of the issue.
        ConfigIssue(ConfigIssue::ConfigOption optionId, const std::string& description);

        //API Constructor: ConfigIssue
        //    Creates a ConfigIssue object.
        //
        //Parameters:
        //    optionId - The <ConfigOption> identifying the configuration option for which the issue occurred.
        //    description - A description of the issue.
        //    mask - The <ChannelMask> that this issue applies to, if this is a channel group issue.
        ConfigIssue(ConfigIssue::ConfigOption optionId, const std::string& description, const ChannelMask& mask);

    private:
        //Variable: m_optionId
        //    The <ConfigOption> identifying the configuration option for which the issue occurred.
        ConfigOption m_optionId;
        
        //Variable: m_description
        //    The description of the issue.
        std::string m_description;

        //Variable: m_isChannelGroupIssue
        //    Whether this issue applies to a channel group (true) or the entire Node (false).
        bool m_isChannelGroupIssue;

        //Variable: m_channelMask
        //    The <ChannelMask> that this issue applies to, if this is a channel group issue.
        ChannelMask m_channelMask;

    public:
        //API Function: id
        //    Gets the <ConfigOption> identifying the configuration option for which the issue occurred.
        //
        //Returns:
        //    A <ConfigOption> identifying the configuration option for which the issue occurred.
        ConfigIssue::ConfigOption id() const;
        
        //API Function: description
        //    Gets a description of the issue.
        //
        //Returns:
        //    A string description of the issue.
        const std::string& description() const;

        //API Function: isChannelGroupIssue
        //    Gets whether the issue applies to a channel group (true) or the entire Node (false).
        //
        //Returns:
        //    true if the issue applies to a channel group, false if the issue is for a global Node setting.
        bool isChannelGroupIssue() const;

        //API Function: channelMask
        //    The <ChannelMask> that the issue applies to, if this issue is a channel group issue.
        //
        //Returns:
        //    The <ChannelMask> that the issue applies to. If this issue is for a global Node setting, this will be a default (all disabled) mask.
        const ChannelMask& channelMask() const;
    };

    //API Typedef: ConfigIssues
    //    typedef for a vector of <ConfigIssue> objects.
    typedef std::vector<ConfigIssue> ConfigIssues;
}