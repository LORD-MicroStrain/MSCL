#pragma once

#include "mscl/Value.h"
#include "mscl/MicroStrain/MIP/Commands/GenericMipCommand.h"

namespace mscl
{

class MipCommand
{
public:
    //Constructor: MipCommand
    //  Constructor to build MIP command based on Command ID and function selector
    MipCommand(MipTypes::Command cmdId, MipTypes::FunctionSelector fn) :
        m_commandId(cmdId),
        m_functionSelector(fn)
    {};

    //Constructor: MipCommand
    //  Constructor to build MIP command based on Command ID and function selector with specified data
    MipCommand(MipTypes::Command cmdId, MipTypes::FunctionSelector fn, MipFieldValues vals) :
        m_commandId(cmdId),
        m_functionSelector(fn),
        m_data(vals)
    {};

    //Function: createResponse
    //  Converts this class to a ByteStream.
    //
    //Parameters:
    //    weak_ptr<ResponseCollector>
    //
    //Returns:
    //    std::shared_ptr<GenericMipCommand::Response> - the response to be filled in with data from the device.
    virtual std::shared_ptr<GenericMipCommand::Response> createResponse(std::weak_ptr<ResponseCollector> collector);

    //Function: operator ByteStream
    //  Converts this class to a ByteStream.
    virtual operator ByteStream() const;

    //Function: getGenericResponseData
    //
    //Parameter:
    //    response - The <GenericMipCmdResponse> object from which to get formatted data.
    //
    //Returns:
    //    <MipFieldValues> - A <MipFieldValues> object with the values returned from the device.
    MipFieldValues getGenericResponseData(const GenericMipCmdResponse& response);

    //Function: commandName
    //
    //Returns:
    //    std::string - the string name for this class.
    virtual std::string commandName() const;

    //Function: supportedFunctionSelectors
    //
    //Returns:
    // <MipFunctionSelectors> - list of function selectors supported for the given command.
    static MipFunctionSelectors supportedFunctionSelectors(MipTypes::Command cmd);

    //Function: supportsFunctionSelector
    //
    //Returns:
    // bool - indicates whether or not the function selector is supported by the specified command.
    static bool supportsFunctionSelector(MipTypes::Command cmd, MipTypes::FunctionSelector fn);

protected:
    // Constructor
    MipCommand() {};

    //Function: commandType
    //
    //Returns:
    //    MipTypes::Command - the command ID.
    virtual MipTypes::Command commandType() const { return m_commandId; };

    //Function: fieldDataByte
    //
    //Returns:
    //    uint8 - the byte ID for field data in the reply.
    virtual uint8 fieldDataByte() const;

    //Function: responseExpected
    //
    //Returns:
    //    bool - True indicates that a response should return from the device.
    virtual bool responseExpected() const;

private:
    MipTypes::Command m_commandId;

    MipTypes::FunctionSelector m_functionSelector;

    MipFieldValues m_data;

    static std::string getCommandName(MipTypes::Command id);

    static uint8 getFieldDataByte(MipTypes::Command id);

    static MipFieldFormat getResponseFieldFormat(MipTypes::Command id);
};

}
