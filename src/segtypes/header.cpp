#include "segtypes/header.h"

namespace Splat::Segtypes {

void Header::Extract() {}

void Header::Export() {}

SegmentType Header::GetSegmentType() const {
    return SegmentType::HeaderSegment;
}

std::string Header::GetSegmentTypeName() const {
    return "header";
}

std::string Header::GetDefaultName() const {
    return GetSegmentTypeName();
}

} // namespace Splat::Segtypes
