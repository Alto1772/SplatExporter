#pragma once
#include <fstream>
#include <string>
#include <vector>
#include "spdlog/spdlog.h"

class File {
public:
    static std::vector<uint8_t> ReadFileBinary(const std::string& filePath) {
        using namespace Splat;

        std::ifstream file(filePath, std::ios::in | std::ios::binary | std::ios::ate);
        if (!file) {
            SPDLOG_ERROR("Cannot open file {}", filePath);
            return {};
        }

        std::streamsize fileSize = file.tellg();
        file.seekg(0, std::ios::beg);
        std::vector<uint8_t> buffer(fileSize);

        if (!file.read(reinterpret_cast<char*>(buffer.data()), fileSize)) {
            SPDLOG_ERROR("Error reading file {}", filePath);
            return {};
        }
        file.close();
        return buffer;
    }

    static bool IfExists(const std::string& filePath) {
        std::ifstream file(filePath, std::ios::in | std::ios::binary | std::ios::ate);
        return file.good();
    }
};