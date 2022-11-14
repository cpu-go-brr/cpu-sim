#pragma once

#include "settings.hpp"

#ifdef C_ONLY
#include "fbitset.hpp"
typedef fbitset bitset;
#else 
#include "abitset.hpp"
typedef abitset bitset;
#endif

#include "AddressInfo.hpp"