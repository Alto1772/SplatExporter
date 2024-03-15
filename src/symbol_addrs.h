#pragma once
#include <iostream>
#include <optional>
#include <string>
#include <unordered_map>

namespace Splat {

enum class SymbolDefineType {
    Generated,   // symbols generated from the splatfile
    UserDefined, // symbols defined from symbol_addrs.txt
    Explicit,    // symbols that came from command line or anything else
};

struct Symbol {
    std::string name;
    SymbolDefineType defineType;
    uint32_t addr;
    std::optional<size_t> size;
};

class SymbolAddressTable {
public:
    SymbolAddressTable() = default;

    void ParseFromStream(std::istream&);

    std::unordered_map<std::string, Symbol> addresses;
};

} // namespace Splat
