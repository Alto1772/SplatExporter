#include "vram_classes.h"

namespace Splat {

YAML::Node VramClass::ToYaml() const {
    YAML::Node node;

    if (vram_symbol != "" || follows_classes.size() != 0) {
        node["name"] = name;
        node["vram"] = vram;

        if (vram_symbol != "") {
            node["vram_symbol"] = vram_symbol;
        }
        if (follows_classes.size() != 0) {
            node["follows_classes"] = follows_classes;
        }
    } else {
        node.push_back(name);
        node.push_back(vram);
    }

    return node;
}

bool VramClass::FromYaml(const YAML::Node& node) {
    switch (node.Type()) {
    case YAML::NodeType::Sequence:
        name = node[0].as<std::string>();
        vram = node[1].as<uint32_t>();
        break;
    case YAML::NodeType::Map: {
        name = node["name"].as<std::string>();
        vram = node["vram"].as<uint32_t>();
        vram_symbol = node["vram_symbol"].as<std::string>("");

        const auto& followsVramClasses = node["follows_classes"];
        if (followsVramClasses.IsDefined()) {
            follows_classes = followsVramClasses.as<std::vector<std::string>>();
        }
    } break;
    default:
        return false;
    }

    return true;
}

} // namespace Splat