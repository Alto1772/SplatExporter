#include "segtypes/section_groups.h"
#include <utility>
#include "spdlog/spdlog.h"

namespace Splat::Segtypes {

SegmentType CodeGroupSegment::GetSegmentType() const {
    return SegmentType::CodeGroupSegment;
}

std::string CodeGroupSegment::GetSegmentTypeName() const {
    return "code";
}

bool CodeGroupSegment::ParseYaml(const YAML::Node& node) {
    if (!node["subsegments"].IsDefined()) {
        SPDLOG_ERROR("Required 'subsegment' attribute for code types.");
        return false;
    }

    if (!GroupTypeSegment::ParseYaml(node)) {
        return false;
    }

    align = align.value_or(16);
    return true;
}

SegmentType DataSectionGroup::GetSegmentType() const {
    return SegmentType::DataSectionGroup;
}
std::string DataSectionGroup::GetSegmentTypeName() const {
    return ".data";
}

SegmentType RodataSectionGroup::GetSegmentType() const {
    return SegmentType::RodataSectionGroup;
}
std::string RodataSectionGroup::GetSegmentTypeName() const {
    return ".rodata";
}

SegmentType BssSectionGroup::GetSegmentType() const {
    return SegmentType::BssSectionGroup;
}
std::string BssSectionGroup::GetSegmentTypeName() const {
    return ".bss";
}

} // namespace Splat::Segtypes
