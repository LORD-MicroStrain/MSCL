#include "stdafx.h"
#include "mscl/MicroStrain/MIP/Commands/GenericMipCommand.h"
#include "MipCommand.h"
#include "mscl/MicroStrain/ResponseCollector.h"

namespace mscl
{
                /////  MipCommand  /////

MipCommand::MipCommand()
{
}
    
std::shared_ptr<GenericMipCommand::Response> MipCommand::createResponse(std::weak_ptr<ResponseCollector> collector)
{
    std::shared_ptr<GenericMipCommand::Response> responseToSend(new GenericMipCommand::Response(commandType(),
        collector, true, responseExpected(), commandName(), fieldDataByte()));
    return responseToSend;
}

}  // namespace mscl