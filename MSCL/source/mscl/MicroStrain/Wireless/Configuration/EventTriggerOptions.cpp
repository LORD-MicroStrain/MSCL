/*******************************************************************************
Copyright(c) 2015-2020 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/
#include "stdafx.h"

#include "EventTriggerOptions.h"

namespace mscl
{
    Trigger::Trigger():
        m_channelNumber(1),
        m_type(WirelessTypes::eventTrigger_floor),
        m_value(0.0f)
    {
    }

    Trigger::Trigger(uint8 channelNumber, WirelessTypes::EventTriggerType triggerType, float triggerValue):
        m_channelNumber(channelNumber),
        m_type(triggerType),
        m_value(triggerValue)
    {
    }

    uint8 Trigger::channelNumber() const
    {
        return m_channelNumber;
    }

    void Trigger::channelNumber(uint8 channelNum)
    {
        m_channelNumber = channelNum;
    }

    WirelessTypes::EventTriggerType Trigger::triggerType() const
    {
        return m_type;
    }

    void Trigger::triggerType(WirelessTypes::EventTriggerType type)
    {
        m_type = type;
    }

    float Trigger::triggerValue() const
    {
        return m_value;
    }

    void Trigger::triggerValue(float value)
    {
        m_value = value;
    }



    EventTriggerOptions::EventTriggerOptions():
        m_triggerMask(0),
        m_preDuration(0),
        m_postDuration(0)
    {
    }

    const BitMask& EventTriggerOptions::triggerMask() const
    {
        return m_triggerMask;
    }

    void EventTriggerOptions::triggerMask(const BitMask& mask)
    {
        m_triggerMask = mask;
    }

    bool EventTriggerOptions::anyTriggersEnabled() const
    {
        return (m_triggerMask.enabledCount() > 0);
    }

    bool EventTriggerOptions::triggerEnabled(uint8 triggerIndex) const
    {
        return m_triggerMask.enabled(triggerIndex);
    }

    void EventTriggerOptions::enableTrigger(uint8 triggerIndex, bool enable)
    {
        m_triggerMask.enable(triggerIndex, enable);
    }

    uint32 EventTriggerOptions::preDuration() const
    {
        return m_preDuration;
    }

    void EventTriggerOptions::preDuration(uint32 duration)
    {
        m_preDuration = duration;
    }

    uint32 EventTriggerOptions::postDuration() const
    {
        return m_postDuration;
    }

    void EventTriggerOptions::postDuration(uint32 duration)
    {
        m_postDuration = duration;
    }

    void EventTriggerOptions::trigger(uint8 triggerIndex, const Trigger& trigger)
    {
        m_triggers[triggerIndex] = trigger;
    }

    const Trigger& EventTriggerOptions::trigger(uint8 triggerIndex) const
    {
        try
        {
            return m_triggers.at(triggerIndex);
        }
        catch(std::out_of_range&)
        {
            throw Error_NoData("No Trigger exists for the given triggerIndex.");
        }
    }

    const Triggers& EventTriggerOptions::triggers() const
    {
        return m_triggers;
    }
}