#pragma once

#include "Includes.h"

typedef union {
    float floatingPoint;
    uint8_t binary[4];
} binaryFloat;

typedef union {
    uint16_t shortValue;
    uint8_t binary[2];
} binaryShort;