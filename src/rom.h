#pragma once
#include <filesystem>
#include <string>
#include <vector>

namespace Splat {

class BinaryRom {
private:
    const std::vector<uint8_t> data;
    const std::filesystem::path romPath;

public:
    BinaryRom(const std::vector<uint8_t>&);
    BinaryRom(const std::vector<uint8_t>&, const std::filesystem::path&);

    static BinaryRom* FromPath(const std::filesystem::path&);
    static BinaryRom* FromData(const std::vector<uint8_t>&);
    bool ValidateRom(const std::string&) const;
    const std::vector<uint8_t>& GetRomData() const;
    const std::filesystem::path& GetRomPath() const;
};

} // namespace Splat