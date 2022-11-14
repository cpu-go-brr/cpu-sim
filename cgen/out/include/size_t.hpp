#pragma once
#include "settings.hpp"

#include <stdint.h>

#ifdef C_ONLY
#define SIZE_T uint32_t
#else

#include <cstddef>
#define SIZE_T std::size_t
#endif
