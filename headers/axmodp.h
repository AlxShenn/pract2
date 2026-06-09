#ifndef AXMODP_H
#define AXMODP_H
#include <vector>
#include <cstdint>
#include <iostream>
#include <clocale>
#include <cmath>

bool conditions(uint64_t base, uint64_t modulo);
uint64_t modFermat(uint64_t base, uint64_t power, uint64_t modulo);
uint64_t modBinary(uint64_t base, uint64_t power, uint64_t modulo);

#endif
