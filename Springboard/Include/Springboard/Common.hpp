#pragma once

#include <cstdint>
#include <sbconf.h>
#include <ch.h>

//! \section Assertion checking
#define ASSERT(cond)                chDbgAssert(cond, #cond)
#define ASSERT_MSG(cond, msg)       chDbgAssert(cond, msg)
