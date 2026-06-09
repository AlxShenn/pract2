#include "headers/rsa.h"
#include "headers/axmodp.h"
#include "headers/egcd.h"
#include <iomanip>

using namespace std;

string getTextFromFile() {
    string text;
    string filename;
    cout << "Введите имя файла: ";
    getline(cin, filename);
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Ошибка: не удалось открыть файл " << filename << endl;
        return "";
    }

    text.assign((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    file.close();
    if (text.empty()) {
        cout << "Файл пуст." << endl;
    } else {
        cout << "Текст успешно загружен из файла. Длина: " << text.size() << " символов." << endl;
    }
    return text;
}

uint64_t gcd(uint64_t a, uint64_t b) { 
    while (b) {
        uint64_t temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

vector<uint64_t> encryption(string text, uint64_t openKey, uint64_t N) {
    vector<uint64_t> res;
    cout << "Символ" << "\t" << "Номер" << "\t" << "Результат шифрования" << endl;
    cout << "------------------------------------------" << endl;
    for (int i = 0; i < text.size(); i++) {
        uint64_t encryptedNumber = (unsigned char)text[i];
        uint64_t encryptedChar = modBinary(encryptedNumber, openKey, N);

        cout << text[i] << "\t" << encryptedNumber << "\t" << encryptedChar << endl;
        res.push_back(encryptedChar);
    }

    return res;
}

string decryption(vector<uint64_t> text, uint64_t privateKey, uint64_t N) {
    string res;
    cout << "Номер" << "\t" << "Расшифровка" << "\t" << "Символ" << endl;
    cout << "---------------------------------" << endl;
    for (int i = 0; i < text.size(); i++) {
        uint64_t decryptedNumber = modBinary(text[i], privateKey, N);
        char decryptedChar = (char)decryptedNumber;

        cout << text[i] << "\t" << decryptedNumber << "\t" << decryptedChar << endl;
        res.push_back(decryptedChar);
    }

    return res;
}
