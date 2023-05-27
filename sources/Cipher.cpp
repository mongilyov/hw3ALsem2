// Copyright 2023 Mongilyov Andrey

#include <Cipher.hpp>

// Block Cipher
void BlockCipher::cipher() {
    std::ifstream inputFile(_input, std::ios::binary);
    std::ifstream keyFile(_key, std::ios::binary);
    std::string key = {};
    char c;
    while (!keyFile.eof()) {
        c = keyFile.get();
        if (c == -1) {
            break;
        }
        key += c;
    }
    std::ofstream outputFile(_output, std::ios::binary);
    char tempChar;
    size_t keyIndex = 0;
    while (!inputFile.eof()) {
        tempChar = inputFile.get();
        if (tempChar == -1) {
            break;
        }
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
    std::ifstream inputFile(_input, std::ios::binary);
    std::ifstream keyFile(_key, std::ios::binary);
    std::string key = {};
    char c;
    while (!keyFile.eof()) {
        c = keyFile.get();
        if (c == -1) {
            break;
        }
        key += c;
    }
    std::ofstream outputFile(_output, std::ios::binary);
    char tempChar;
    size_t keyIndex = 0;
    while (!inputFile.eof()) {
        tempChar = inputFile.get();
        if (tempChar == -1) {
            break;
        }
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
// End of Block Cipher

// Stream Cipher
void StreamCipher::cipher() {
    std::ifstream inputFile(_input, std::ios::binary);
    std::ofstream outputFile(_output, std::ios::binary);
    std::string keyInformation = {};
    char prevKeyChar;
    char curKeyChar;
    char tempKeyChar;
    prevKeyChar = inputFile.get();
    keyInformation += prevKeyChar;
    while (!inputFile.eof()) {
        tempKeyChar = inputFile.get();
        if (tempKeyChar == -1) {
            break;
        }
        curKeyChar = (prevKeyChar * 13) % 256;
        keyInformation += curKeyChar;
        prevKeyChar = curKeyChar;
    }
    inputFile.close();
    inputFile.open(_input);
    std::string keyName = _input;
    keyName += "KEY";
    std::ofstream keyFile(keyName, std::ios::binary);
    for (char ch : keyInformation) {
        keyFile << ch;
        tempKeyChar = inputFile.get();
        if (tempKeyChar == -1) {
            break;
        }
        char c = ch ^ tempKeyChar;
        outputFile << c;
    }
    inputFile.close();
    outputFile.close();
    keyFile.close();
}

void StreamCipher::decipher() {
    std::ifstream inputFile(_input, std::ios::binary);
    std::ofstream outputFile(_output, std::ios::binary);
    std::ifstream keyFile(_key, std::ios::binary);
    std::string keyInformation = {};
    char inputChar;
    char keyChar;
    while (!keyFile.eof()) {
        inputChar = inputFile.get();
        keyChar = keyFile.get();
        if (inputChar == -1 && keyChar == -1) {
            break;
        }
        char ch = inputChar ^ keyChar;
        outputFile << ch;
    }
    inputFile.close();
    outputFile.close();
    keyFile.close();
}
// End of Stream Cipher
