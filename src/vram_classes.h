#pragma once
#include <cstdint>
#include <string>
#include <vector>
#include "yaml-cpp/yaml.h"

namespace Splat {

class VramClass {
public:
    std::string name;
    uint32_t vram;
    std::string vram_symbol;
    std::vector<std::string> follows_classes;

    YAML::Node ToYaml() const;
    bool FromYaml(const YAML::Node&);
};
} // namespace Splat

namespace YAML {
template <>
struct convert<Splat::VramClass> {
    inline static Node encode(const Splat::VramClass& rhs) {
        return rhs.ToYaml();
    };
    inline static bool decode(const Node& node, Splat::VramClass& rhs) {
        return rhs.FromYaml(node);
    }
};

} // namespace YAML