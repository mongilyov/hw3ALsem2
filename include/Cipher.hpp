// Copyright 2023 Mongilyov Andrey


#ifndef INCLUDE_CIPHER_HPP_
#define INCLUDE_CIPHER_HPP_

#include <fstream>
#include <iostream>

class Cipher {
public:
    virtual void cipher() = 0;
    virtual void decipher() = 0;
};

class BlockCipher : public Cipher {
public:
    BlockCipher(std::string&& key, std::string&& input, std::string&& output) :
    _key(std::move(key)), _input(std::move(input)), _output(std::move(output)) {}
    void cipher() override;
    void decipher() override;
private:
    std::string _key;
    std::string _input;
    std::string _output;
};

class StreamCipher : public Cipher {
public:
    StreamCipher(std::string&& input, std::string&& output) :
    _input(std::move(input)), _output(std::move(output)) {}
    void cipher() override;
    void decipher() override;
private:
    std::string _input;
    std::string _output;
};

#endif // INCLUDE_CIPHER_HPP_
