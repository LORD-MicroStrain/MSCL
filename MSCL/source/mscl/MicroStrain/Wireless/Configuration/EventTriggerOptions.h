/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/

#pragma once

#include "mscl/MicroStrain/Wireless/WirelessTypes.h"
#include "mscl/BitMask.h"
#include "mscl/Types.h"
#include <map>

namespace mscl
{
    class Trigger
    {
    public:
        //API Default Constructor: Trigger
        //  Creates a default constructed Trigger object.
        Trigger();

        //API Constructor: Trigger
        //  Creates a Trigger object with the provided values.
        //
        //Parameters:
        //  channelNumber - The Wireless Node channel number that the trigger is applied to.
        //  triggerType - The <WirelessTypes::EventTriggerType> for the trigger.
        //  triggerValue - The value to use for the trigger, in whatever unit the channel is calibrated for. (Ex. 4 G's if slope and offset calibrated for G's).
        Trigger(uint8 channelNumber, WirelessTypes::EventTriggerType triggerType, float triggerValue);

    private:
        //Variable: m_channelNumber
        //  The channel number for the trigger.
        uint8 m_channelNumber;

        //Variable: m_type
        //  The <WirelessTypes::EventTriggerType> for the trigger.
        WirelessTypes::EventTriggerType m_type;

        //Variable: m_value
        //  The value for the trigger (in whatever unit the channel is calibrated for).
        float m_value;

    public:
        //API Function: channelNumber
        //  Gets the Wireless Node channel number that the trigger is applied to.
        uint8 channelNumber() const;

        //API Function: channelNumber
        //  Sets the Wireless Node channel number for the trigger.
        void channelNumber(uint8 channelNum);

        //API Function: triggerType
        //  Gets the <WirelessTypes::EventTriggerType> currently set.
        WirelessTypes::EventTriggerType triggerType() const;

        //API Function: triggerType
        //  Sets the <WirelessTypes::EventTriggerType> for the trigger.
        void triggerType(WirelessTypes::EventTriggerType type);

        //API Function: triggerValue
        //  Gets the trigger value currently set, in whatever unit the channel is calibrated for.
        //  (Ex. If triggering on channel 1, and channel 1 is calibrated for G's, a value of 4 for this triggerValue would be 4 G's).
        float triggerValue() const;

        //API Function: triggerValue
        //  Sets the trigger value for the trigger, in whatever unit the channel is calibrated for.
        //  (Ex. If triggering on channel 1, and channel 1 is calibrated for G's, a value of 4 for this triggerValue would be 4 G's).
        void triggerValue(float value);
    };

    //API Typedef: Triggers
    //  Typedef for a map of trigger IDs (uint8) to <Trigger> objects.
    typedef std::map<uint8, Trigger> Triggers;

    //API Class: EventTriggerOptions
    //  Contains all of the Event Trigger options that can be configured for a WirelessNode.
    class EventTriggerOptions
    {
    public:
        //API Default Constructor: EventTriggerOptions
        //  Creates a default constructed EventTriggerOptions object.
        EventTriggerOptions();

    private:
        //Variable: m_triggerMask
        //  The <BitMask> for enabling and disabling triggers.
        BitMask m_triggerMask;

        //Variable: m_preDuration
        //  The pre event duration (in milliseconds).
        uint32 m_preDuration;

        //Variable: m_postDuration
        //  The post event duration ( in milliseconds).
        uint32 m_postDuration;

        //Variable: m_triggers
        //  The <Triggers>.
        Triggers m_triggers;

    public:
        //API Function: triggerMask
        //  Gets the actual <BitMask> that represents the active and inactive triggers.
        //
        //Returns:
        //  The <BitMak> that represents the active and inactive triggers.
        const BitMask& triggerMask() const;

        //API Function: triggerMask
        //  Sets the <BitMask> that represents the active and inactive triggers.
        //
        //Parameters:
        //  The <BitMask> to set.
        void triggerMask(const BitMask& mask);

        //API Function: anyTriggersEnabled
        //  Checks if any triggers are enabled.
        //
        //Returns:
        //  true if at least 1 trigger is enabled, false if all triggers are disabled.
        bool anyTriggersEnabled() const;

        //API Function: triggerEnabled
        //  Checks if a specific trigger is enabled.
        //
        //Parameters:
        //  triggerIndex - The index of the trigger to check.
        //
        //Returns:
        //  true if the trigger is enabled, false if the trigger is disabled.
        bool triggerEnabled(uint8 triggerIndex) const;

        //API Function: enableTrigger
        //  Enables or disables a specific trigger.
        //
        //Parameters:
        //  triggerIndex - The index of the trigger to check.
        //  enable - Whether to enable (true) or disable (false) the trigger (defaults to true).
        void enableTrigger(uint8 triggerIndex, bool enable = true);

        //API Function: preDuration
        //  Gets the pre event duration in milliseconds.
        uint32 preDuration() const;

        //API Function: preDuration
        //  Sets the pre event duration in milliseconds.
        //
        //Parameters:
        //  duration - The duration to set (in milliseconds).
        void preDuration(uint32 duration);

        //API Function: postDuration
        //  Gets the post event duration in milliseconds.
        uint32 postDuration() const;

        //API Function: postDuration
        //  Sets the post event duration in milliseconds.
        //
        //Parameters:
        //  duration - The duration to set (in milliseconds).
        void postDuration(uint32 duration);

        //API Function: trigger
        //  Sets the <Trigger> in this options object, for the trigger trigger index.
        //
        //Parameters:
        //  triggerIndex - The index of the trigger to set.
        //  trigger - The <Trigger> to set.
        void trigger(uint8 triggerIndex, const Trigger& trigger);

        //API Function: trigger
        //  Gets the <Trigger> for the given trigger index.
        //
        //Parameters:
        //  triggerIndex - The index for the Trigger to get.
        //
        //Returns:
        //  The <Trigger> for the given index.
        //
        //Exceptions:
        //    <Error_NoData> - The given trigger index was not set in this object.
        const Trigger& trigger(uint8 triggerIndex) const;

        //API Function: triggers
        //  Gets the <Triggers> that are currently set in this object.
        //
        //Returns:
        //  The <Triggers> as they are currently set.
        const Triggers& triggers() const;
    };
}