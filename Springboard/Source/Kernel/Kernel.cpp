#include <Springboard/Kernel/Kernel.hpp>
#include <ch.h>

namespace Springboard {
namespace Kernel {

void Initialise()
{
    chSysInit();
}

}
}
