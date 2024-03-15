#include "segtypes/n64/gfx.h"

namespace Splat::Segtypes::N64 {

void GfxSegment::Extract() {
    // TODO
}

void GfxSegment::Export() {
    // TODO
}

bool GfxSegment::ParseYaml(const YAML::Node& node) {
    if (!Segment::ParseYaml(node))
        return false;

    if (node.IsMap()) {
        data_only = node["data_only"].as<bool>(false);
        in_segment = node["in_segment"].as<bool>(true);
    }

    return true;
}

SegmentType GfxSegment::GetSegmentType() const {
    return SegmentType::N64Gfx;
}

std::string GfxSegment::GetSegmentTypeName() const {
    return "gfx";
}

} // namespace Splat::Segtypes::N64
