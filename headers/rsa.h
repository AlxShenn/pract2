#ifndef RSA_H
#define RSA_H
#include <vector>
#include <string>
#include <cstdint>
#include <iostream>
#include <locale>
#include <fstream>   

std::string getTextFromFile();
uint64_t gcd(uint64_t a, uint64_t b);
std::vector<uint64_t> encryption(std::string text, uint64_t openKey, uint64_t N);
std::string decryption(std::vector<uint64_t> text, uint64_t privateKey, uint64_t N);

#endif
