/*****************************************
 * Copyright 2017 - Craig Sacco
 *****************************************/

#include <Springboard/Kernel/Kernel.hpp>
#include <ch.h>

namespace Springboard {
namespace Kernel {

void Initialise()
{
    chSysInit();
}

}  // namespace Kernel
}  // namespace Springboard
