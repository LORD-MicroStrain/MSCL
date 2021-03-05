/*******************************************************************************
Copyright(c) 2015-2021 Parker Hannifin Corp. All rights reserved.

MIT Licensed. See the included LICENSE.txt for a copy of the full MIT License.
*******************************************************************************/

#pragma once

#include "mscl/Types.h"
#include "mscl/Version.h"
#include "mscl/MicroStrain/ByteStream.h"
#include "mscl/MicroStrain/ResponsePattern.h"
#include "mscl/MicroStrain/Wireless/WirelessModels.h"
#include "mscl/MicroStrain/Wireless/WirelessTypes.h"

namespace mscl
{
    class WirelessPacket;

    //API Class: AutoCalResult
    //    Abstract base class for AutoCal result classes.
    class AutoCalResult
    {
        friend class BaseStation_Impl;

    public:
        AutoCalResult();
        virtual ~AutoCalResult() {};

        //API Function: completionFlag
        //    Gets the <WirelessTypes::AutoCalCompletionFlag> of the AutoCal operation result.
        WirelessTypes::AutoCalCompletionFlag completionFlag() const;

    protected:
        //Function: parse
        //    Parses the auto cal info bytes sent in the successful response packet.
        //
        //Parameters:
        //    autoCalInfo - The bytes from a successful auto cal command.
        virtual void parse(const Bytes& autoCalInfo) = 0;

        //Variable: m_completionFlag
        //    The <WirelessTypes::AutoCalCompletionFlag> of the AutoCal operation.
        WirelessTypes::AutoCalCompletionFlag m_completionFlag;
    };

    //API Class: AutoCalResult_shmLink
    //    Holds the result information from an autoCal_shmLink command.
    class AutoCalResult_shmLink : public AutoCalResult
    {
    private:
        //Variable: m_errorFlagCh1
        //    The <WirelessTypes::AutoCalErrorFlag> for the channel 1 strain sensor.
        WirelessTypes::AutoCalErrorFlag m_errorFlagCh1;

        //Variable: m_errorFlagCh2
        //    The <WirelessTypes::AutoCalErrorFlag> for the channel 2 strain sensor.
        WirelessTypes::AutoCalErrorFlag m_errorFlagCh2;

        //Variable: m_errorFlagCh3
        //    The <WirelessTypes::AutoCalErrorFlag> for the channel 3 strain sensor.
        WirelessTypes::AutoCalErrorFlag m_errorFlagCh3;

        //Variable: m_offsetCh1
        //    The offset applied for the channel 1 strain sensor.
        float m_offsetCh1;

        //Variable: m_offsetCh2
        //    The offset applied for the channel 2 strain sensor.
        float m_offsetCh2;

        //Variable: m_offsetCh3
        //    The offset applied for the channel 3 strain sensor.
        float m_offsetCh3;

        //Variable: m_temperature
        //    The temperature at the time of calibration.
        float m_temperature;

    public:
        AutoCalResult_shmLink();
        virtual ~AutoCalResult_shmLink() {};

        //API Function: errorFlagCh1
        //    Gets the <WirelessTypes::AutoCalErrorFlag> for the channel 1 strain sensor.
        WirelessTypes::AutoCalErrorFlag errorFlagCh1() const;

        //API Function: errorFlagCh2
        //    Gets the <WirelessTypes::AutoCalErrorFlag> for the channel 2 strain sensor.
        WirelessTypes::AutoCalErrorFlag errorFlagCh2() const;

        //API Function: errorFlagCh3
        //    Gets the <WirelessTypes::AutoCalErrorFlag> for the channel 3 strain sensor.
        WirelessTypes::AutoCalErrorFlag errorFlagCh3() const;

        //API Function: offsetCh1
        //    Gets the offset applied for the channel 1 strain sensor.
        float offsetCh1() const;

        //API Function: offsetCh2
        //    Gets the offset applied for the channel 2 strain sensor.
        float offsetCh2() const;

        //API Function: offsetCh3
        //    Gets the offset applied for the channel 3 strain sensor.
        float offsetCh3() const;

        //API Function: temperature
        //    Gets the temperature (in °C) at the time of the calibration.
        float temperature() const;

    protected:
        //Function: parse
        //    Parses the auto cal info bytes for the shm-link.
        virtual void parse(const Bytes& autoCalInfo) final;
    };

    //API Class: AutoCalResult_shmLink201
    //    Holds the result information from an autoCal_shmLink201 command.
    class AutoCalResult_shmLink201: public AutoCalResult
    {
    private:
        //Variable: m_errorFlagCh1
        //    The <WirelessTypes::AutoCalErrorFlag> for the channel 1 strain sensor.
        WirelessTypes::AutoCalErrorFlag m_errorFlagCh1;

        //Variable: m_errorFlagCh2
        //    The <WirelessTypes::AutoCalErrorFlag> for the channel 2 strain sensor.
        WirelessTypes::AutoCalErrorFlag m_errorFlagCh2;

        //Variable: m_errorFlagCh3
        //    The <WirelessTypes::AutoCalErrorFlag> for the channel 3 strain sensor.
        WirelessTypes::AutoCalErrorFlag m_errorFlagCh3;

        //Variable: m_slopeCh1
        //    The slope applied for channel 1.
        float m_slopeCh1;

        //Variable: m_offsetCh1
        //    The offset applied for channel 1.
        float m_offsetCh1;

        //Variable: m_slopeCh2
        //    The slope applied for channel 2.
        float m_slopeCh2;

        //Variable: m_offsetCh2
        //    The offset applied for channel 2.
        float m_offsetCh2;

        //Variable: m_slopeCh3
        //    The slope applied for channel 3.
        float m_slopeCh3;

        //Variable: m_offsetCh3
        //    The offset applied for channel 3.
        float m_offsetCh3;

        //Variable: m_temperature
        //    The temperature at the time of calibration.
        float m_temperature;

    public:
        AutoCalResult_shmLink201();
        virtual ~AutoCalResult_shmLink201() {};

        //API Function: errorFlagCh1
        //    Gets the <WirelessTypes::AutoCalErrorFlag> for the channel 1 strain sensor.
        WirelessTypes::AutoCalErrorFlag errorFlagCh1() const;

        //API Function: errorFlagCh2
        //    Gets the <WirelessTypes::AutoCalErrorFlag> for the channel 2 strain sensor.
        WirelessTypes::AutoCalErrorFlag errorFlagCh2() const;

        //API Function: errorFlagCh3
        //    Gets the <WirelessTypes::AutoCalErrorFlag> for the channel 3 strain sensor.
        WirelessTypes::AutoCalErrorFlag errorFlagCh3() const;

        //API Function: slopeCh1
        //    Gets the slope applied for channel 1.
        float slopeCh1() const;

        //API Function: offsetCh1
        //    Gets the offset applied for channel 1.
        float offsetCh1() const;

        //API Function: slopeCh2
        //    Gets the slope applied for channel 2.
        float slopeCh2() const;

        //API Function: offsetCh2
        //    Gets the offset applied for channel 2.
        float offsetCh2() const;

        //API Function: slopeCh3
        //    Gets the slope applied for channel 3.
        float slopeCh3() const;

        //API Function: offsetCh3
        //    Gets the offset applied for channel 3.
        float offsetCh3() const;

        //API Function: temperature
        //    Gets the temperature (in °C) at the time of the calibration.
        float temperature() const;

    protected:
        //Function: parse
        //    Parses the auto cal info bytes for the shm-link.
        virtual void parse(const Bytes& autoCalInfo) final;
    };

    //API Class: AutoShuntCalResult
    //    Holds the result information from an autoCal_shunt command.
    class AutoShuntCalResult: public AutoCalResult
    {
    private:
        //Variable: m_errorFlag
        //  The <WirelessTypes::AutoCalErrorFlag> for the shunt calibration.
        WirelessTypes::AutoCalErrorFlag m_errorFlag;

        //Variable: m_slope
        //  The slope result of the shunt calibration.
        float m_slope;

        //Variable: m_offset
        //  The offset result of the shunt calibration
        float m_offset;

        //Variable: m_baseMedian
        //  The median of the baseline data sampled during the shunt calibration.
        float m_baseMedian;
        
        //Variable: m_baseMin
        //  The minimum of the baseline data sampled during the shunt calibration.
        float m_baseMin;
        
        //Variable: m_baseMax
        //  The maximum of the baseline data sampled during the shunt calibration.
        float m_baseMax;
        
        //Variable: m_shuntMedian
        //  The median of the shunted data sampled during the shunt calibration.
        float m_shuntMedian;
        
        //Variable: m_shuntMin
        //  The minimum of the shunted data sampled during the shunt calibration.
        float m_shuntMin;
        
        //Variable: m_shuntMax
        //  The maximum of the shunted data sampled during the shunt calibration.
        float m_shuntMax;

    public:
        AutoShuntCalResult();
        virtual ~AutoShuntCalResult() {};

        //API Function: errorFlag
        //  Gets the <WirelessTypes::AutoCalErrorFlag> for the shunt calibration.
        WirelessTypes::AutoCalErrorFlag errorFlag() const;

        //API Function: slope
        //  Gets the slope result of the shunt calibration.
        //  Note: This value was not applied to the Node. You will need to manually apply if desired.
        float slope() const;

        //API Function: offset
        //  Gets the offset result of the shunt calibration.
        //  Note: This value was not applied to the Node. You will need to manually apply if desired.
        float offset() const;
        
        //API Function: baseMedian
        //  Gets the median of the baseline data sampled during the shunt calibration.
        float baseMedian() const;
        
        //API Function: 
        //  Gets the minimum of the baseline data sampled during the shunt calibration.
        float baseMin() const;
        
        //API Function: 
        //  Gets the maximum of the baseline data sampled during the shunt calibration.
        float baseMax() const;
        
        //API Function: 
        //  Gets the median of the shunted data sampled during the shunt calibration.
        float shuntMedian() const;
        
        //API Function: 
        //  Gets the minimum of the shunted data sampled during the shunt calibration.
        float shuntMin() const;
        
        //API Function: 
        //  Gets the maximum of the shunted data sampled during the shunt calibration.
        float shuntMax() const;

    protected:
        //Function: parse
        //    Parses the auto cal info bytes for the shm-link.
        virtual void parse(const Bytes& autoCalInfo) final;
    };
}