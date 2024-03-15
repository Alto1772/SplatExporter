#include "segtypes/n64/img.h"
#include "context.h"

namespace Splat::Segtypes::N64 {

ImageSegment::ImageSegment() {
    canNotHaveStartAsAuto = false;
}

bool ImageSegment::ParseYaml(const YAML::Node& node) {
    if (!Segment::ParseYaml(node))
        return false;

    if (node.IsSequence()) {
        width = node[3].as<uint32_t>();
        height = node[4].as<uint32_t>();
    } else if (node.IsMap()) {
        width = node["width"].as<uint32_t>();
        height = node["height"].as<uint32_t>();

        flip_x = node["flip_x"].as<bool>(false);
        flip_y = node["flip_y"].as<bool>(false);
    }

    return true;
}

void ImageSegment::Extract() {
    // TODO
}

void ImageSegment::Export() {
    // TODO
}

std::filesystem::path ImageSegment::GetOutPath() const {
    std::filesystem::path p = Context::GetInstance()->GetSplatConfig()->GetOptions().assets_path;

    return p / dir.value_or("") / (name + "." + GetImageTypeName());
}

uint32_t ImageSegment::CalculateSize() const {
    return (uint32_t)(width * height * (GetImageTypeBpp() / 8.f));
}

} // namespace Splat::Segtypes::N64
