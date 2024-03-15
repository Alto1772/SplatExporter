#pragma once
#include <algorithm>
#include <cctype>
#include <iomanip>
#include <ios>
#include <sstream>
#include <string>
#include <string_view>


class StringHelper {
public:
    static std::string StrhexFromBytes(const unsigned char* data, size_t len) {
        std::stringstream ss;
        ss << std::hex;

        for (int i = 0; i < len; i++) {
            ss << std::setw(2) << std::setfill('0') << (int)data[i];
        }

        return ss.str();
    }

    static bool CompareCaseInsensitive(std::string_view lhs, std::string_view rhs) {
        return std::ranges::equal(lhs, rhs, [](const auto& a, const auto& b) {
            return std::tolower(static_cast<unsigned char>(a)) == std::tolower(static_cast<unsigned char>(b));
        });
    }
};