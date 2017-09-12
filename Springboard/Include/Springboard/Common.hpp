/*****************************************
 * Copyright 2017 - Craig Sacco
 *****************************************/

#pragma once

#include <sbconf.h>
#include <ch.h>
#include <cstdint>

//! \section Assertion checking
#define ASSERT(cond)                chDbgAssert(cond, #cond)
#define ASSERT_MSG(cond, msg)       chDbgAssert(cond, msg)
