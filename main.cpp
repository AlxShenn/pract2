#include "headers/axmodp.h"
#include "headers/continuedfraction.h"
#include "headers/egcd.h"
#include "headers/rsa.h"

using namespace std;

enum class Solutions {
    AX_MOD_P,
    EGCD,
    INVERSE_EGCD,
    RSA,
    CONTINUED_FRACTION,
    UNKNOWN
};

Solutions getSolutions(const string& Solutions) {
    if (Solutions == "1") return Solutions::AX_MOD_P;
    if (Solutions == "2") return Solutions::EGCD;
    if (Solutions == "3") return Solutions::INVERSE_EGCD;
    if (Solutions == "4") return Solutions::RSA;
    if (Solutions == "5") return Solutions::CONTINUED_FRACTION;
    return Solutions::UNKNOWN;
}

void printHelp() {
    cout << "ПРАКТИЧЕСКАЯ РАБОТА №2" << endl;
    cout << "Введите номер задания:" << endl;
    cout << "1) Возведение в степень по модулю;" << endl;
    cout << "2) Расширенный алгоритм Евклида;" << endl;
    cout << "3) Обратный расширенный алгоритм Евклида;" << endl;
    cout << "4) Преобразование текста с помощью RSA;" << endl;
    cout << "5) Цепная дробь и решение уравнения." << endl;
    return;
}

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");

    string solutionNumber;
    printHelp();
    while (cin >> solutionNumber) {
        Solutions solution = getSolutions(solutionNumber);
        switch (solution) {
            case Solutions::AX_MOD_P: {
                cout << "1) Возведение в степень по модулю" << endl;
                uint64_t base, power, modulo;
                cout << "Введите основание base:" << endl << ">>> ";
                cin >> base;
                cout << "Введите степень power:" << endl << ">>> ";
                cin >> power;
                cout << "Введите модуль modulo:" << endl << ">>> ";
                cin >> modulo;

                if (conditions(base, modulo) == false) {
                    cout << "Ошибка: основание или модуль некорректны!" << endl;
                    continue;
                }
                cout << "Ферма: " << base << "^" << power << " mod" << modulo << 
                    " = " << modFermat(base, power, modulo) << endl;
                cout << "Бинарный алгоритм: " << base << "^" << power << " mod" << modulo << 
                    " = " << modBinary(base, power, modulo) << endl;
                break;
            }
            case Solutions::EGCD: {
                cout << "2) Расширенный алгоритм Евклида" << endl;
                uint64_t base, module;
                cout << "Расширенный алгоритм Евклида для c * d = 1 mod m" << endl;
                cout << "Введите c: " << endl; cout << ">>> ";
                cin >> base;
                cout << "Введите m: " << endl; cout << ">>> ";
                cin >> module;

                uint64_t d = egcd(base, module);
                cout << "d = " << d << endl;
                cout << base << " * " << d << " = " << base * d << " = " << 
                    ((base *d ) / module) * module << " + 1" <<" = 1 mod " << module << endl;
                break;
            }
            case Solutions::INVERSE_EGCD: {
                cout << "3) Обратный расширенный алгоритм Евклида" << endl;
                uint64_t base, module;
                cout << "Вычисление c^(-1) mod m" << endl;
                cout << "Введите c: ";
                cin >> base;
                cout << "Введите m: ";
                cin >> module;
                uint64_t result = inverseEgcd(base, module);
                if (!result) continue;
                cout << "d = " << result << endl;
                cout << base << "^(-1) mod " << module << " = " << result << endl;
                break;
            }
            case Solutions::RSA: {
                cout << "4) Преобразование текста с помощью RSA" << endl;
                uint64_t p, q;
                cout << "=== Криптопротокол RSA === " << endl;
                cout << " - Генерация открытого ключа - " << endl;
                cout << "Введите простые числа p и q: " << endl << ">>> ";
                cin >> p >> q;
                uint64_t N = p * q;
                cout << "N = p * q = " << N << endl;

                uint64_t phi = (p - 1) * (q - 1);
                cout << "Вычисление функции Эйлера для N: phi(N) = (p - 1) * (q - 1) = " << phi << endl;
                cout << "Введите публичный ключ openKey: " << endl << ">>> ";
                uint64_t openKey;
                cin >> openKey;
                cin.ignore();
                if (gcd(openKey, phi) != 1) {
                    cout << "Ошибка: публичный ключ openKey и фунукция Эйлера phi(N) должны быть взаимно простыми!" << endl;
                    continue;
                }

                cout << "Вычисление закрытого ключа: openKey^(-1) mod phi = privateKey" << endl;
                uint64_t privateKey = inverseEgcd(openKey, phi);
                cout << openKey << "^(-1) mod " << phi << " = " << privateKey << endl;

                cout << "\nОткрытый ключ (d, N): (" << openKey << ", " << N << ")" << endl;
                cout << "Закрытый ключ (c, N): (" << privateKey << ", " << N << ")" << endl;

                int sourceChoice;
                cout << "\nВыберите способ ввода текста:\n";
                cout << "\t1) - ввод с консоли\n";
                cout << "\t2) - чтение из файла\n";
                cout << "Ваш выбор: ";
                cin >> sourceChoice;
                cin.ignore();

                string text;
                if (sourceChoice == 1) {
                    cout << "Введите текст: ";
                    getline(cin, text);
                } else if (sourceChoice == 2) {
                    text = getTextFromFile();
                    if (text.empty()) continue;
                } else {
                    cout << "Неверный выбор. Завершение программы задания" << endl;
                    continue;
                }

                vector<uint64_t> encrypted = encryption(text, openKey, N);

                cout << "\nЗашифрованный текст:\n";
                for (const auto& ch : encrypted) {
                    cout << ch << " ";
                }
                cout << endl;

                string decrypted = decryption(encrypted, privateKey, N);

                cout << "\nРасшифрованный текст:\n";
                cout << decrypted << endl;
                
                cout << "Завершение программы " << endl;
                break;
            }
            case Solutions::CONTINUED_FRACTION: {
                cout << "5) Цепная дробь и решение уравнения" << endl;
                uint64_t A, B;
                int64_t D;

                cout << "Введите A: " << endl << ">>> ";
                cin >> A;

                cout << "Введите B: " << endl << ">>> ";
                cin >> B;

                cout << "Введите D: " << endl << ">>> ";
                cin >> D;

                cout << "\nУравнение: " << A << "a + " << B << "b = " << D << "\n\n";

                uint64_t generalDivisor = gcd(A, B);
                cout << "НОД(" << A << ", " << B << ") = " << generalDivisor << "\n";

                cout << "\nЦепная дробь:\n";
                vector<uint64_t> q = continuedFraction(A / generalDivisor, B / generalDivisor);

                cout << A / generalDivisor << "/" << B / generalDivisor << " = [";
                for (int i = 0; i < (int)q.size(); i++) {
                    if (i == 0) cout << q[i];
                    else if (i == 1) cout << "; " << q[i];
                    else cout << ", " << q[i];
                }
                cout << "]\n";

                solveEquation(A, B, D);
                break;
            }
            default: {
                cout << "Неверный номер задания!!!" << endl;
                break;
            }
        }
    }

    return 0;
}
