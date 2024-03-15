#include "segtypes/binary.h"

namespace Splat::Segtypes {
BinarySegment::BinarySegment() : Segment() {
    canExport = true;
    canNotHaveStartAsAuto = true;
}

bool BinarySegment::ParseYaml(const YAML::Node& node) {
    if (!Segment::ParseYaml(node)) {
        return false;
    }
}

void BinarySegment::Extract() {
    if (!size.has_value()) {
        
    }
}

void BinarySegment::Export() {
    // TODO
}

SegmentType BinarySegment::GetSegmentType() const {
    return SegmentType::BinarySegment;
}

std::string BinarySegment::GetSegmentTypeName() const {
    return "bin";
}
} // namespace Splat::Segtypes
