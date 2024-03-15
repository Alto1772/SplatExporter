#pragma once
#include <filesystem>
#include <vector>
#include "yaml-cpp/yaml.h"

namespace Splat {

class SplatOptions {
public:
    std::filesystem::path base_path = ".";
    std::filesystem::path src_path = "src";
    std::filesystem::path asm_path = "asm";
    std::filesystem::path assets_path = "assets";
    std::filesystem::path target_path = "game.z64";
    std::filesystem::path extensions_path = "tools/splat_ext";
    std::filesystem::path ld_script_path = "game.ld";
    std::filesystem::path ld_symbol_header_path = "build/include/ld_addrs.h";
    std::vector<std::filesystem::path> symbol_addrs_path = {"symbol_addrs.txt"};
    std::filesystem::path elf_path = "";
    std::filesystem::path platform = "n64";
    std::string gfx_ucode = "f3dex2";
    bool image_type_in_extension = false;

    // ld-dependent, might be needing these sometime later
    int subalign = 8;

    YAML::Node ToYaml() const;
    bool FromYaml(const YAML::Node&);
};

} // namespace Splat

namespace YAML {
template <>
struct convert<Splat::SplatOptions> {
    inline static Node encode(const Splat::SplatOptions& rhs) {
        return rhs.ToYaml();
    };
    inline static bool decode(const Node& node, Splat::SplatOptions& rhs) {
        return rhs.FromYaml(node);
    }
};

} // namespace YAML