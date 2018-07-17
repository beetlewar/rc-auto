#pragma once

typedef union {
    float value;
    uint8_t binary[sizeof(float)];
} binaryFloat;

typedef union {
    unsigned long value;
    uint8_t binary[sizeof(unsigned long)];
} binaryULong;

typedef union {
    uint16_t value;
    uint8_t binary[sizeof(uint16_t)];
} binaryShort;