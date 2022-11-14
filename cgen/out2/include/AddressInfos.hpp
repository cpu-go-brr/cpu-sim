#pragma once
#include "AddressInfo.hpp"
#include <map>

const AddressInfo ACC{0, 0, 4};


const AddressInfo CY{0, 4, 1};


const AddressInfo REGISTER{0, 5, 64};
const AddressInfo P0{0, 5, 8};
const AddressInfo R1{0, 5, 4};
const AddressInfo R0{1, 1, 4};
const AddressInfo P1{1, 5, 8};
const AddressInfo R3{1, 5, 4};
const AddressInfo R2{2, 1, 4};
const AddressInfo P2{2, 5, 8};
const AddressInfo R5{2, 5, 4};
const AddressInfo R4{3, 1, 4};
const AddressInfo P3{3, 5, 8};
const AddressInfo R7{3, 5, 4};
const AddressInfo R6{4, 1, 4};
const AddressInfo P4{4, 5, 8};
const AddressInfo R9{4, 5, 4};
const AddressInfo R8{5, 1, 4};
const AddressInfo P5{5, 5, 8};
const AddressInfo R11{5, 5, 4};
const AddressInfo R10{6, 1, 4};
const AddressInfo P6{6, 5, 8};
const AddressInfo R13{6, 5, 4};
const AddressInfo R12{7, 1, 4};
const AddressInfo P7{7, 5, 8};
const AddressInfo R15{7, 5, 4};
const AddressInfo R14{8, 1, 4};


const AddressInfo PC{8, 5, 12};
const AddressInfo PL{8, 5, 4};
const AddressInfo PM{9, 1, 4};
const AddressInfo PH{9, 5, 4};


const AddressInfo CM{10, 1, 4};


const AddressInfo STACK{10, 5, 36};
const AddressInfo STACK0{10, 5, 12};
const AddressInfo STACK1{12, 1, 12};
const AddressInfo STACK2{13, 5, 12};


const AddressInfo SRC{15, 1, 8};
const AddressInfo X2{15, 1, 4};
const AddressInfo SRC_CHIP{15, 1, 2};
const AddressInfo SRC_REG{15, 3, 2};
const AddressInfo X3{15, 5, 4};
const AddressInfo SRC_ADDR{15, 5, 4};


const AddressInfo TEST{16, 1, 1};


[[maybe_unused]] const auto mems = {ACC,CY,REGISTER,P0,R1,R0,P1,R3,R2,P2,R5,R4,P3,R7,R6,P4,R9,R8,P5,R11,R10,P6,R13,R12,P7,R15,R14,PC,PL,PM,PH,CM,STACK,STACK0,STACK1,STACK2,SRC,X2,SRC_CHIP,SRC_REG,X3,SRC_ADDR,TEST,};

inline std::map<std::string, AddressInfo> addresses = {
{"ACC", ACC},
{"CY", CY},
{"REGISTER", REGISTER},
{"P0", P0},
{"R1", R1},
{"R0", R0},
{"P1", P1},
{"R3", R3},
{"R2", R2},
{"P2", P2},
{"R5", R5},
{"R4", R4},
{"P3", P3},
{"R7", R7},
{"R6", R6},
{"P4", P4},
{"R9", R9},
{"R8", R8},
{"P5", P5},
{"R11", R11},
{"R10", R10},
{"P6", P6},
{"R13", R13},
{"R12", R12},
{"P7", P7},
{"R15", R15},
{"R14", R14},
{"PC", PC},
{"PL", PL},
{"PM", PM},
{"PH", PH},
{"CM", CM},
{"STACK", STACK},
{"STACK0", STACK0},
{"STACK1", STACK1},
{"STACK2", STACK2},
{"SRC", SRC},
{"X2", X2},
{"SRC_CHIP", SRC_CHIP},
{"SRC_REG", SRC_REG},
{"X3", X3},
{"SRC_ADDR", SRC_ADDR},
{"TEST", TEST},
};

