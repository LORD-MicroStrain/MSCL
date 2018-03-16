#pragma once

#include "mscl/Types.h"
#include "mscl/MicroStrain/MIP/Commands/GenericMipCommand.h"

namespace mscl
{

class MipCommand
{
public:
    // Constructor
    MipCommand();

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
    virtual operator ByteStream() const = 0;

    //Function: commandName
    //
    //Returns:
    //    std::string - the string name for this class.
    virtual std::string commandName() const = 0;

protected:
    //Function: commandType
    //
    //Returns:
    //    MipTypes::Command - the command ID.
    virtual MipTypes::Command commandType() const = 0;

    //Function: fieldDataByte
    //
    //Returns:
    //    uint8 - the byte ID for field data in the reply.
    virtual uint8 fieldDataByte() const = 0;

    //Function: responseExpected
    //
    //Returns:
    //    bool - True indicates that a response should return from the device.
    virtual bool responseExpected() const = 0;

};

}
