#include "headers/egcd.h"

using namespace std;

uint64_t inverseEgcd(uint64_t base, uint64_t module) {
    int64_t u1 = 0, u2 = 1, u3;
    uint64_t startModule = module;
    base = base % module;
    uint64_t preRemain;
    uint64_t quanity = module / base;
    uint64_t remain = module % base;

    cout << "\t" << "remain" << "\t" << "u" << "\t" << "quanity" << endl;
    cout << "\t" << module << "\t" << u1 << "\t" << "-" << endl;
    cout << "\t" << base << "\t" << u2 << "\t" << "-" << endl;

    while (remain > 0) {
        preRemain = remain;
        u3 = u1 - u2 * quanity;
        cout << "\t" << remain << "\t" << u3 << "\t" << quanity << endl;

        module = base; base = remain;
        u1 = u2; u2 = u3;
        quanity = module / base;
        remain = module % base;
    }

    if (preRemain != 1) {
        cout << "Ошибка: base и module должны быть взаимно простыми!" << endl;
    }

    uint64_t result = (u3 > 0)? u3: u3 + startModule;
    
    return result;
}
