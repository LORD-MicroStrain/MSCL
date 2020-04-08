#include "stdafx.h"
#include "mscl/MicroStrain/MIP/Commands/GenericMipCommand.h"
#include "MipCommand.h"
#include "mscl/MicroStrain/ResponseCollector.h"

namespace mscl
{
                /////  MipCommand  /////
        
    std::shared_ptr<GenericMipCommand::Response> MipCommand::createResponse(std::weak_ptr<ResponseCollector> collector)
    {
        std::shared_ptr<GenericMipCommand::Response> responseToSend(new GenericMipCommand::Response(commandType(),
            collector, true, responseExpected(), commandName(), fieldDataByte()));
        return responseToSend;
    }

    MipCommand::operator ByteStream() const
    {
        ByteStream command;
        command.append_uint8(static_cast<uint8>(m_functionSelector));

        for (Value val : m_data)
        {
            ValueType type = val.storedAs();
            switch (type)
            {
            case valueType_bool:
                command.append_uint8((val.as_bool() ? 1 : 0));
                break;
            case valueType_uint8:
                command.append_uint8(val.as_uint8());
                break;
            case valueType_uint16:
                command.append_uint16(val.as_uint16());
                break;
            case valueType_uint32:
                command.append_uint32(val.as_uint32());
                break;
            case valueType_float:
                command.append_float(val.as_float());
                break;
            case valueType_double:
                command.append_double(val.as_double());
                break;
            default:
                break;
            }
        }

        return GenericMipCommand::buildCommand(commandType(), command.data());
    }

    MipFieldValues MipCommand::getGenericResponseData(const GenericMipCmdResponse& response)
    {
        MipFieldFormat responseFormat = MipCommand::getResponseFieldFormat(m_commandId);
        DataBuffer buffer(response.data());
        MipFieldValues data;

        for (ValueType type : responseFormat)
        {
            switch (type)
            {
            case valueType_bool:
                data.push_back(Value::BOOL((buffer.read_uint8() > 0)));
                break;
            case valueType_uint8:
                data.push_back(Value::UINT8(buffer.read_uint8()));
                break;
            case valueType_uint16:
                data.push_back(Value::UINT16(buffer.read_uint16()));
                break;
            case valueType_uint32:
                data.push_back(Value::UINT32(buffer.read_uint32()));
                break;
            case valueType_float:
                data.push_back(Value::FLOAT(buffer.read_float()));
                break;
            case valueType_double:
                data.push_back(Value::DOUBLE(buffer.read_double()));
                break;
            default:
                break;
            }
        }

        return data;
    }

    std::string MipCommand::commandName() const
    {
        return MipCommand::getCommandName(m_commandId);
    }

    MipFunctionSelectors MipCommand::supportedFunctionSelectors(MipTypes::Command cmd)
    {
        switch (cmd)
        {
        case MipTypes::CMD_EF_AIDING_MEASUREMENT_ENABLE:
        case MipTypes::CMD_EF_KINEMATIC_CONSTRAINT:
        case MipTypes::CMD_EF_ADAPTIVE_FILTER_OPTIONS:
        case MipTypes::CMD_EF_MULTI_ANTENNA_OFFSET:
            return {
                MipTypes::FunctionSelector::USE_NEW_SETTINGS,
                MipTypes::FunctionSelector::READ_BACK_CURRENT_SETTINGS,
                MipTypes::FunctionSelector::SAVE_CURRENT_SETTINGS,
                MipTypes::FunctionSelector::LOAD_STARTUP_SETTINGS,
                MipTypes::FunctionSelector::RESET_TO_DEFAULT
            };
        default:
            return {};
        }
    }

    bool MipCommand::supportsFunctionSelector(MipTypes::Command cmd, MipTypes::FunctionSelector fn)
    {
        MipFunctionSelectors fns = MipCommand::supportedFunctionSelectors(cmd);
        return std::find(fns.begin(), fns.end(), fn) != fns.end();
    }

    uint8 MipCommand::fieldDataByte() const
    {
        return MipCommand::getFieldDataByte(m_commandId);
    }

    bool MipCommand::responseExpected() const
    {
        return m_functionSelector == MipTypes::READ_BACK_CURRENT_SETTINGS;
    }

    std::string MipCommand::getCommandName(MipTypes::Command id)
    {
        switch (id)
        {
        case MipTypes::CMD_EF_AIDING_MEASUREMENT_ENABLE:
            return "AidingMeasurementEnable";
        case MipTypes::CMD_EF_KINEMATIC_CONSTRAINT:
            return "KinematicConstraint";
        case MipTypes::CMD_EF_ADAPTIVE_FILTER_OPTIONS:
            return "AdaptiveFilterOptions";
        case MipTypes::CMD_EF_MULTI_ANTENNA_OFFSET:
            return "MultiAntennaOffset";
        default:
            return "";
        }
    }

    uint8 MipCommand::getFieldDataByte(MipTypes::Command id)
    {
        switch (id)
        {
        case MipTypes::CMD_EF_AIDING_MEASUREMENT_ENABLE:
            return 0xD0;
        case MipTypes::CMD_EF_KINEMATIC_CONSTRAINT:
            return 0xD1;
        case MipTypes::CMD_EF_ADAPTIVE_FILTER_OPTIONS:
            return 0xD3;
        case MipTypes::CMD_EF_MULTI_ANTENNA_OFFSET:
            return 0xD4;
        default:
            return 0;
        }
    }

    MipFieldFormat MipCommand::getResponseFieldFormat(MipTypes::Command id)
    {
        switch (id)
        {
        case MipTypes::CMD_EF_AIDING_MEASUREMENT_ENABLE:
            return {
                ValueType::valueType_uint16,
                ValueType::valueType_bool
            };
        case MipTypes::CMD_EF_KINEMATIC_CONSTRAINT:
            return {
                ValueType::valueType_uint8,
                ValueType::valueType_uint8,
                ValueType::valueType_uint8
            };
        case MipTypes::CMD_EF_ADAPTIVE_FILTER_OPTIONS:
            return {
                ValueType::valueType_uint8,
                ValueType::valueType_uint16
            };
        case MipTypes::CMD_EF_MULTI_ANTENNA_OFFSET:
            return {
                ValueType::valueType_uint8,
                ValueType::valueType_float,
                ValueType::valueType_float,
                ValueType::valueType_float
            };
        default:
            return MipFieldFormat(0);
        }
    }
}  // namespace mscl