#include "segtypes/n64/palette.h"

namespace Splat::Segtypes::N64 {

bool Palette::ParseYaml(const YAML::Node& node) {
    if (!Segment::ParseYaml(node)) {
        return false;
    }

    if (node.IsMap()) {
        if (node["size"].IsDefined()) {
            size = node["size"].as<int>();
        } else if (!std::holds_alternative<uint32_t>(start)) {
            size = 0x20;
        }
    }

    return true;
}
void Palette::Extract() {
    // TODO
}

void Palette::Export() {
    // TODO
}

SegmentType Palette::GetSegmentType() const {
    return SegmentType::N64ImgPalette;
}
std::string Palette::GetSegmentTypeName() const {
    return "palette";
}

} // namespace Splat::Segtypes::N64
