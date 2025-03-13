/*****************************************************************************************
**          Copyright(c) 2015-2025 MicroStrain by HBK. All rights reserved.             **
**                                                                                      **
**    MIT Licensed. See the included LICENSE file for a copy of the full MIT License.   **
*****************************************************************************************/

#include "stdafx.h"
#include "GeographicSource.h"
#include "mscl/MicroStrain/MIP/MipDataField.h"
#include "mscl/MicroStrain/MIP/Packets/MipPacketBuilder.h"
#include "mscl/MicroStrain/MIP/MipTypes.h"
#include "mscl/MicroStrain/MIP/Commands/MIP_Commands.h"

namespace mscl
{
    GeographicSource::GeographicSource(MipTypes::FunctionSelector function_selector, const GeographicSourceOptions& dataToUse) :
        m_functionSelector(function_selector),
        m_sourceOptions(dataToUse)
    { }

    GeographicSource::GeographicSource(MipTypes::FunctionSelector function_selector) :
        m_functionSelector(function_selector)
    {
        if (function_selector == MipTypes::USE_NEW_SETTINGS)
            throw Error_NoData("Data must be passed in for a set command.");
    }

    GeographicSource GeographicSource::MakeSetCommand(const GeographicSourceOptions& dataToUse)
    {
        return GeographicSource(MipTypes::USE_NEW_SETTINGS, dataToUse);
    }

    GeographicSource GeographicSource::MakeGetCommand()
    {
        GeographicSourceOptions dataToUse;  // The data won't get used for a get command.
        return GeographicSource(MipTypes::READ_BACK_CURRENT_SETTINGS, dataToUse);
    }

    bool GeographicSource::responseExpected() const
    {
        return (m_functionSelector == MipTypes::READ_BACK_CURRENT_SETTINGS) ? true : false;
    }

    GeographicSourceOptions GeographicSource::getResponseData(const GenericMipCmdResponse& response)
    {
        DataBuffer dataBuffer(response.data());
        InertialTypes::GeographicSourceOption returnData;
        returnData = static_cast<InertialTypes::GeographicSourceOption>(dataBuffer.read_uint8());

        float fixedValue = dataBuffer.read_float();

        return GeographicSourceOptions(returnData, fixedValue);
    }

    GeographicSource::operator ByteStream() const
    {
        ByteStream byteCommand;
        byteCommand.append_uint8(static_cast<uint8>(m_functionSelector));

        // Only fill in data if set command is being sent.
        if (m_functionSelector == MipTypes::USE_NEW_SETTINGS)
        {
            byteCommand.append_uint8(static_cast<uint8>(m_sourceOptions.source));
            byteCommand.append_float(m_sourceOptions.manual);
        }
        return GenericMipCommand::buildCommand(commandType(), byteCommand.data());
    }


    // InclinationSource
    InclinationSource::InclinationSource(MipTypes::FunctionSelector function_selector, const GeographicSourceOptions& dataToUse) :
        GeographicSource(function_selector, dataToUse)
    {
        m_commandName = "InclinationSource";
        m_commandType = MipTypes::CMD_EF_INCLINATION_SRC;
        m_fieldDataByte = 0xBC;
    }

    InclinationSource::InclinationSource(MipTypes::FunctionSelector function_selector) :
        GeographicSource(function_selector)
    {
        m_commandName = "InclinationSource";
        m_commandType = MipTypes::CMD_EF_INCLINATION_SRC;
        m_fieldDataByte = 0xBC;
    }

    GeographicSource InclinationSource::MakeSetCommand(const GeographicSourceOptions& dataToUse)
    {
        return InclinationSource(MipTypes::USE_NEW_SETTINGS, dataToUse);
    }

    GeographicSource InclinationSource::MakeGetCommand()
    {
        GeographicSourceOptions dataToUse;  // The data won't get used for a get command.
        return InclinationSource(MipTypes::READ_BACK_CURRENT_SETTINGS, dataToUse);
    }


    // DeclinationSource
    DeclinationSource::DeclinationSource(MipTypes::FunctionSelector function_selector, const GeographicSourceOptions& dataToUse) :
        GeographicSource(function_selector, dataToUse)
    {
        m_commandName = "DeclinationSource";
        m_commandType = MipTypes::CMD_EF_DECLINATION_SRC;
        m_fieldDataByte = 0xB2;
    }

    DeclinationSource::DeclinationSource(MipTypes::FunctionSelector function_selector) :
        GeographicSource(function_selector)
    {
        m_commandName = "DeclinationSource";
        m_commandType = MipTypes::CMD_EF_DECLINATION_SRC;
        m_fieldDataByte = 0xB2;
    }

    GeographicSource DeclinationSource::MakeSetCommand(const GeographicSourceOptions& dataToUse)
    {
        return DeclinationSource(MipTypes::USE_NEW_SETTINGS, dataToUse);
    }

    GeographicSource DeclinationSource::MakeGetCommand()
    {
        GeographicSourceOptions dataToUse;  // The data won't get used for a get command.
        return DeclinationSource(MipTypes::READ_BACK_CURRENT_SETTINGS, dataToUse);
    }


    // MagneticFieldMagnitudeSource
    MagneticFieldMagnitudeSource::MagneticFieldMagnitudeSource(MipTypes::FunctionSelector function_selector, const GeographicSourceOptions& dataToUse) :
        GeographicSource(function_selector, dataToUse)
    {
        m_commandName = "MagneticFieldMagnitudeSource";
        m_commandType = MipTypes::CMD_EF_FIELD_MAGNITUDE_SRC;
        m_fieldDataByte = 0xBD;
    }

    MagneticFieldMagnitudeSource::MagneticFieldMagnitudeSource(MipTypes::FunctionSelector function_selector) :
        GeographicSource(function_selector)
    {
        m_commandName = "MagneticFieldMagnitudeSource";
        m_commandType = MipTypes::CMD_EF_FIELD_MAGNITUDE_SRC;
        m_fieldDataByte = 0xBD;
    }

    GeographicSource MagneticFieldMagnitudeSource::MakeSetCommand(const GeographicSourceOptions& dataToUse)
    {
        return MagneticFieldMagnitudeSource(MipTypes::USE_NEW_SETTINGS, dataToUse);
    }

    GeographicSource MagneticFieldMagnitudeSource::MakeGetCommand()
    {
        GeographicSourceOptions dataToUse;  // The data won't get used for a get command.
        return MagneticFieldMagnitudeSource(MipTypes::READ_BACK_CURRENT_SETTINGS, dataToUse);
    }

}
