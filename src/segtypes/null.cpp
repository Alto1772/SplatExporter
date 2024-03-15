#include "segtypes/null.h"

namespace Splat::Segtypes {

void NullSegment::Extract() {}

void NullSegment::Export() {}

SegmentType NullSegment::GetSegmentType() const {
    return SegmentType::NullSegment;
}

std::string NullSegment::GetSegmentTypeName() const {
    return "";
}

} // namespace Splat::Segtypes