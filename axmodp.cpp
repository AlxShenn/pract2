#include "headers/axmodp.h"

bool conditions(uint64_t base, uint64_t modulo) {
    if (base < 1) return false;
    if (modulo == 2) return true;
    if (modulo < 2 || modulo % 2 == 0) return false;
    
    for (uint64_t div = 3; div <= sqrt(modulo); div += 2) {
        if (modulo % div == 0) return false;
    }
    return true;
}

uint64_t modFermat(uint64_t base, uint64_t power, uint64_t modulo) {
    base %= modulo;
    power %= modulo - 1;
    uint64_t res = 1;

    for (int i = 0; i < power; ++i) {
        res *= base;
        res %= modulo;
    }
    return res;
}

uint64_t modBinary(uint64_t base, uint64_t power, uint64_t modulo) {
    base %= modulo;
    power %= modulo - 1;
    uint64_t res = 1;

    while (power > 0) {
        if (power & 1) {
            res = (res * base) % modulo;
        }

        base = (base * base) % modulo;
        power >>= 1;
    }
    return res;
}
