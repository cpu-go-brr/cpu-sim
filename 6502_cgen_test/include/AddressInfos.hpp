#pragma once
#include "AddressInfo.hpp"
const AddressInfo PC{0, 0, 16};
const AddressInfo AC{2, 0, 8};
const AddressInfo XX{3, 0, 8};
const AddressInfo YY{4, 0, 8};
const AddressInfo SR{5, 0, 8};
const AddressInfo NF{5, 0, 1};
const AddressInfo VF{5, 1, 1};
const AddressInfo IGF{5, 2, 1};
const AddressInfo BF{5, 3, 1};
const AddressInfo DF{5, 4, 1};
const AddressInfo IF{5, 5, 1};
const AddressInfo ZF{5, 6, 1};
const AddressInfo CF{5, 7, 1};
const AddressInfo SP{6, 0, 8};
