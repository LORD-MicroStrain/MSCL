#include "stdafx.h"
#include "mscl/MicroStrain/Inertial/Commands/GenericInertialCommand.h"
#include "InertialReturnTypes.h"
#include "InertialTypes.h"

namespace mscl
{
                /////  TimeUpdate  /////
TimeUpdate::TimeUpdate(double timeOfWeek, uint16 weekNumber, float timeAccuracy) :
    m_timeOfWeek(timeOfWeek),
    m_weekNumber(weekNumber),
    m_timeAccuracy(timeAccuracy)
{ }

TimeUpdate::~TimeUpdate()
{
}


}  // namespace mscl