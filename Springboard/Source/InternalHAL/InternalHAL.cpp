/*****************************************
 * Copyright 2017 - Craig Sacco
 *****************************************/

#include <Springboard/InternalHAL/InternalHAL.hpp>
#include <hal.h>

namespace Springboard {
namespace InternalHAL {

void Initialise()
{
    halInit();
}

}  // namespace InternalHAL
}  // namespace Springboard
