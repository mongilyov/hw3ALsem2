// Copyright 2023 Mongilyov Andrey

#ifndef INCLUDE_HANDLEFUNCTIONS_HPP_
#define INCLUDE_HANDLEFUNCTIONS_HPP_

#include <Cipher.hpp>

#include <boost/program_options.hpp>

#include <iostream>
#include <unordered_map>
#include <string>

namespace po = boost::program_options;

inline int getParamsBlock(po::variables_map& vm, std::unordered_map<std::string, std::string>& map) {
    std::string key, inputFile, outputFile;
    try {
        map["key"] = vm["key"].as<std::string>();
    } catch (...) {
        std::cerr << "Key is not specified" << std::endl;
        return -1;
    }
    try {
        map["inputFile"] = vm["file"].as<std::string>();
    } catch (...) {
        std::cerr << "Input file is not specified" << std::endl;
        return -1;
    }
    try {
        map["outputFile"] = vm["output"].as<std::string>();
    } catch (...) {
        map["outputFile"] = "output";
    }
    return 0;
}

inline int getParamsCipher(po::variables_map& vm, std::unordered_map<std::string, std::string>& map) {
    std::string inputFile, outputFile;
    try {
        map["inputFile"] = vm["file"].as<std::string>();
    } catch (...) {
        std::cerr << "Input file is not specified" << std::endl;
        return -1;
    }
    try {
        map["outputFile"] = vm["output"].as<std::string>();
    } catch (...) {
        map["outputFile"] = "output";
    }
    return 0;
}

inline int handleBlockCipher(po::variables_map& vm) {
    std::unordered_map<std::string, std::string> variablesMap = {};
    if (getParamsBlock(vm, variablesMap) == -1) {
        return -1;
    }
    BlockCipher blockCipher(std::move(variablesMap["key"]),
                            std::move(variablesMap["inputFile"]),
                            std::move(variablesMap["outputFile"]));
    blockCipher.cipher();
    return 0;
}

inline int handleStreamCipher(po::variables_map& vm) {
    std::unordered_map<std::string, std::string> variablesMap = {};
    if (getParamsCipher(vm, variablesMap) == -1) {
        return -1;
    }
    StreamCipher streamCipher("", std::move(variablesMap["inputFile"]),
                              std::move(variablesMap["outputFile"]));
    streamCipher.cipher();
    return 0;
}

inline int handleBlockDecipher(po::variables_map& vm) {
    std::unordered_map<std::string, std::string> variablesMap = {};
    if (getParamsBlock(vm, variablesMap) == -1) {
        return -1;
    }
    BlockCipher blockCipher(std::move(variablesMap["key"]),
                            std::move(variablesMap["inputFile"]),
                            std::move(variablesMap["outputFile"]));
    blockCipher.decipher();
    return 0;
}

inline int handleStreamDecipher(po::variables_map& vm) {
    std::unordered_map<std::string, std::string> variablesMap = {};
    if (getParamsBlock(vm, variablesMap) == -1) {
        return -1;
    }
    StreamCipher streamCipher(std::move(variablesMap["key"]), std::move(variablesMap["inputFile"]),
                              std::move(variablesMap["outputFile"]));
    streamCipher.decipher();
    return 0;
}

#endif // INCLUDE_HANDLEFUNCTIONS_HPP_
