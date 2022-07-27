#pragma once

#include "../../ethKernel/low_level.h"
#include "../../include/types.h"

uint16_t pciConfigReadWord(uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset);