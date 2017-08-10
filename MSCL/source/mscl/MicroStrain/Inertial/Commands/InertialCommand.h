#pragma once

#include "mscl/Types.h"
//#include "InertialTypes.h"
#include "mscl/MicroStrain/Inertial/Commands/GenericInertialCommand.h"

namespace mscl
{

class InertialCommand
{
public:
    // Constructor
    InertialCommand();

    //Function: createResponse
    //  Converts this class to a ByteStream.
    //
    //Parameters:
    //    weak_ptr<ResponseCollector>
    //
    //Returns:
    //    std::shared_ptr<GenericInertialCommand::Response> - the response to be filled in with data from the inertial device.
    virtual std::shared_ptr<GenericInertialCommand::Response> createResponse(std::weak_ptr<ResponseCollector> collector);

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
    //    InertialTypes::Command - the command ID.
    virtual InertialTypes::Command commandType() const = 0;

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
