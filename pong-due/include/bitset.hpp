#pragma once

#include "settings.hpp"

#ifdef FBITSET
#include "fbitset.hpp"
typedef fbitset bitset;
#endif
#ifdef ABITSET
#include "abitset.hpp"
typedef abitset bitset;
#endif

#include "AddressInfo.hpp"