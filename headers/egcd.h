#ifndef EGCD_H
#define EGCD_H
#include <iostream>
#include <cstdint>
#include <locale>

uint64_t egcd(uint64_t c, uint64_t m);
uint64_t inverseEgcd(uint64_t c, uint64_t m);

#endif