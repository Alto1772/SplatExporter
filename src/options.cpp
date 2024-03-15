#include "options.h"
#include <algorithm>
#include <ranges>

namespace Splat {

YAML::Node SplatOptions::ToYaml() const {
    YAML::Node options;

    options["base_path"] = base_path.string();
    options["src_path"] = src_path.string();
    options["asm_path"] = asm_path.string();
    options["assets_path"] = assets_path.string();
    options["target_path"] = target_path.string();
    options["extensions_path"] = extensions_path.string();
    options["ld_script_path"] = ld_script_path.string();
    options["ld_symbol_header_path"] = ld_symbol_header_path.string();

    if (symbol_addrs_path.size() > 1) {
        std::vector<std::string> paths;

        std::ranges::transform(symbol_addrs_path, std::back_inserter(paths),
                               [](const std::filesystem::path& p) -> std::string { return p.string(); });

        options["symbol_addrs_path"] = paths;
    } else {
        options["symbol_addrs_path"] = symbol_addrs_path.at(0).string();
    }
    options["elf_path"] = elf_path.string();
    options["platform"] = platform.string();
    options["gfx_ucode"] = gfx_ucode;

    options["subalign"] = subalign;

    return options;
}

bool SplatOptions::FromYaml(const YAML::Node& options) {
    base_path = options["base_path"].as<std::string>(".");
    src_path = options["src_path"].as<std::string>("src");
    asm_path = options["asm_path"].as<std::string>("asm");
    assets_path = options["assets_path"].as<std::string>("assets");
    target_path = options["target_path"].as<std::string>("game.z64");
    extensions_path = options["extensions_path"].as<std::string>("tools/splat_ext");
    ld_script_path = options["ld_script_path"].as<std::string>("game.ld");
    ld_symbol_header_path = options["ld_symbol_header_path"].as<std::string>("build/include/ld_addrs.h");

    const auto& symAddrsPathsRaw = options["symbol_addrs_path"];
    if (symAddrsPathsRaw.IsSequence()) {
        symbol_addrs_path.clear();

        std::ranges::transform(symAddrsPathsRaw, std::back_inserter(symbol_addrs_path),
                               [](const YAML::Node& n) -> std::filesystem::path { return n.as<std::string>(); });
    } else {
        symbol_addrs_path = {symAddrsPathsRaw.as<std::string>("symbol_addrs.txt")};
    }

    elf_path = options["elf_path"].as<std::string>("");
    platform = options["platform"].as<std::string>("n64");
    gfx_ucode = options["gfx_ucode"].as<std::string>("f3dex2");

    subalign = options["subalign"].as<int>(8);

    return true;
}

} // namespace Splat
