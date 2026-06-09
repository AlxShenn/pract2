#include "headers/egcd.h"

using namespace std;

uint64_t egcd(uint64_t c, uint64_t m) {
    int v1 = 1, v2 = 0, v3;
    int u1 = 0, u2 = 1, u3;
    uint64_t m0 = m;
    uint64_t r0;
    uint64_t q = c / m;
    uint64_t r = c % m;

    cout << "\t" << "r" << "\t" << "u" << "\t" << "v" << "\t" << "q" << endl;
    cout << "\t" << c << "\t" << u1 << "\t" << v1 << "\t" << "-" << endl;
    cout << "\t" << m << "\t" << u2 << "\t" << v2 << "\t" << "-" << endl;

    while (r > 0) {
        r0 = r;
        u3 = u1 - u2 * q; v3 = v1 - v2 * q;
        cout << "\t" << r << "\t" << u3 << "\t" << v3 << "\t" << q << endl;

        c = m; m = r;
        u1 = u2; u2 = u3; v1 = v2; v2 = v3;
        q = c / m;
        r = c % m;
    }

    if (r0 != 1) {
        cout << "Ошибка: c и m должны быть взаимно простыми!" << endl;
    }

    uint64_t d = (v3 > 0)? v3: v3 + m0;

	return d;
}
