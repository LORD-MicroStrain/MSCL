#include "stdafx.h"
#include "mscl/MicroStrain/Inertial/Commands/GenericInertialCommand.h"
#include "mscl/MicroStrain/Inertial/Commands/InertialCommand.h"
#include "mscl/MicroStrain/ResponseCollector.h"

namespace mscl
{
                /////  InertialCommand  /////

InertialCommand::InertialCommand()
{
}
    
std::shared_ptr<GenericInertialCommand::Response> InertialCommand::createResponse(std::weak_ptr<ResponseCollector> collector)
{
    std::shared_ptr<GenericInertialCommand::Response> responseToSend(new GenericInertialCommand::Response(commandType(),
        collector, true, responseExpected(), commandName(), fieldDataByte()));
    return responseToSend;
}

}  // namespace mscl