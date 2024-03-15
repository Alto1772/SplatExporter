#include "segtypes/group.h"

namespace Splat::Segtypes {

GroupTypeSegment::GroupTypeSegment() {
    canHaveSubsegments = true;
    canExport = true;
}

bool GroupTypeSegment::ParseYaml(const YAML::Node& node) {
    if (!Segment::ParseYaml(node))
        return false;

    if (node["subsegments"].IsDefined())
        Segment::ParseSegments(weak_from_this(), siblings, node["subsegments"]);
    return true;
}

void GroupTypeSegment::Extract() {
    for (auto seg : siblings) {
        seg->Extract();
    }
}

void GroupTypeSegment::Export() {
    for (auto seg : siblings) {
        seg->Export();
    }
}

SegmentType GroupTypeSegment::GetSegmentType() const {
    return SegmentType::GroupSegment;
}

std::string GroupTypeSegment::GetSegmentTypeName() const {
    return "group";
}

} // namespace Splat::Segtypes
