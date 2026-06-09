#include "headers/continuedfraction.h"
#include "headers/rsa.h"

using namespace std;

vector<uint64_t> continuedFraction(uint64_t A, uint64_t B) {
    vector<uint64_t> quanity;

    while (B != 0) {
        quanity.push_back(A / B);

        uint64_t temp = B;
        B = A % B;
        A = temp;
    }

    return quanity;
}

void solveEquation(uint64_t A, uint64_t B, int64_t D) {
    uint64_t g = gcd(A, B);

    cout << "НОД(" << A << ", " << B << ") = " << g << "\n";

    if (D % (int64_t)g != 0) {
        cout << "Решений в целых числах нет!\n";
        return;
    }

    uint64_t A1 = A / g;
    uint64_t B1 = B / g;
    int64_t D1 = D / (int64_t)g;

    vector<uint64_t> quanity = continuedFraction(A1, B1);

    cout << "Цепная дробь для " << A1 << "/" << B1 << ": [";
    for (int i = 0; i < (int)quanity.size(); i++) {
        if (i == 0) cout << quanity[i];
        else if (i == 1) cout << "; " << quanity[i];
        else cout << ", " << quanity[i];
    }
    cout << "]\n";

    // подходящие дроби P_i / Q_i
    uint64_t Pm2 = 0, Pm1 = 1;
    uint64_t Qm2 = 1, Qm1 = 0;

    vector<uint64_t> P, Q;

    for (int i = 0; i < (int)quanity.size(); i++) {
        uint64_t Pi = quanity[i] * Pm1 + Pm2;
        uint64_t Qi = quanity[i] * Qm1 + Qm2;

        P.push_back(Pi);
        Q.push_back(Qi);

        Pm2 = Pm1;
        Pm1 = Pi;
        Qm2 = Qm1;
        Qm1 = Qi;
    }

    int n = (int)quanity.size() - 1;

    int64_t solutionA, solutionB;

    if (n == 0) {
        // если дробь состоит из одного элемента, то B1 = 1
        solutionA = 0;
        solutionB = D1;
    } else {
        uint64_t Pprev = P[n - 1];
        uint64_t Qprev = Q[n - 1];

        // A1 * Q_{n-1} - B1 * P_{n-1} = (-1)^(n-1)
        int64_t sign = (n % 2 == 1) ? 1 : -1;

        solutionA = sign * (int64_t)Qprev * D1;
        solutionB = -sign * (int64_t)Pprev * D1;
    }

    cout << "Частное решение:\n";
    cout << "a0 = " << solutionA << "\n";
    cout << "b0 = " << solutionB << "\n";

    cout << "Проверка: " << A << " * " << solutionA << " + " << B << " * " << solutionB;
    cout << " = " << (int64_t)A * solutionA + (int64_t)B * solutionB << "\n";
}
