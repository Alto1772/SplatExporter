#include "segtypes/section_bins.h"

namespace Splat::Segtypes {

// -- TextBinSegment

SegmentType TextBinSegment::GetSegmentType() const {
    return SegmentType::BinarySectionText;
}
std::string TextBinSegment::GetSegmentTypeName() const {
    return "textbin";
}

// -- DataBinSegment

SegmentType DataBinSegment::GetSegmentType() const {
    return SegmentType::BinarySectionData;
}
std::string DataBinSegment::GetSegmentTypeName() const {
    return "databin";
}

// -- RodataBinSegment

SegmentType RodataBinSegment::GetSegmentType() const {
    return SegmentType::BinarySectionRodata;
}
std::string RodataBinSegment::GetSegmentTypeName() const {
    return "rodatabin";
}

} // namespace Splat::Segtypes
