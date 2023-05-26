// Copyright 2023 Mongilyov Andrey

#include <Cipher.hpp>

// Block Cipher
void BlockCipher::cipher() {
    std::ifstream inputFile(_input);
    std::ifstream keyFile(_key);
    std::string key = {};
    char c;
    while (keyFile >> c) {
        key += c;
    }
    std::ofstream outputFile(_output);
    char tempChar;
    size_t keyIndex = 0;
    while (inputFile >> tempChar) {
        tempChar ^= key[keyIndex];
        outputFile << tempChar;
        ++keyIndex;
        if (keyIndex == key.size()) {
            keyIndex = 0;
        }
    }
    inputFile.close();
    outputFile.close();
    keyFile.close();
}

void BlockCipher::decipher() {
    std::ifstream inputFile(_input);
    std::ifstream keyFile(_key);
    std::string key = {};
    char c;
    while (keyFile >> c) {
        key += c;
    }
    std::ofstream outputFile(_output);
    char tempChar;
    size_t keyIndex = 0;
    while (inputFile >> tempChar) {
        tempChar ^= key[keyIndex];
        if (tempChar == '\\') {
            outputFile << ' ';
        } else {
            outputFile << tempChar;
        }
        ++keyIndex;
        if (keyIndex == key.size()) {
            keyIndex = 0;
        }
    }
    inputFile.close();
    outputFile.close();
    keyFile.close();
}
// End of Block Cipher

// Stream Cipher
void StreamCipher::cipher() {
    std::ifstream inputFile(_input);
    std::ofstream outputFile(_output);
    std::string keyInformation = {};
    char prevKeyChar;
    char curKeyChar;
    char tempKeyChar;
    inputFile >> prevKeyChar;
    keyInformation += prevKeyChar;
    while (inputFile >> tempKeyChar) {
        curKeyChar = (prevKeyChar * 13) % 256;
        keyInformation += curKeyChar;
        prevKeyChar = curKeyChar;
    }
    inputFile.close();
    inputFile.open(_input);

    for (char ch : keyInformation) {
        inputFile >> tempKeyChar;
        outputFile << (ch ^ tempKeyChar);
    }
    inputFile.close();
    outputFile.close();
}

void StreamCipher::decipher() {
    std::ifstream inputFile(_input);
    std::ofstream outputFile(_output);
    std::string keyInformation = {};
    char prevKeyChar;
    char curKeyChar;
    char tempKeyChar;
    inputFile >> prevKeyChar;
    keyInformation += prevKeyChar;
    while (inputFile >> tempKeyChar) {
        curKeyChar = (prevKeyChar * 13) % 256;
        keyInformation += curKeyChar;
        prevKeyChar = curKeyChar;
    }
    inputFile.close();
    inputFile.open(_input);

    for (char ch : keyInformation) {
        inputFile >> tempKeyChar;
        outputFile << (ch ^ tempKeyChar);
    }
    inputFile.close();
    outputFile.close();
}
// End of Stream Cipher
