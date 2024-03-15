#pragma once
#include <memory>
#include <vector>
#include "splat_segment.h"

namespace Splat::Segtypes {

// Abstract class for all code, .data, .rodata segments
class GroupTypeSegment : public Segment {
public:
    GroupTypeSegment();

    virtual bool ParseYaml(const YAML::Node&) override;
    [[nodiscard]] virtual void Extract() override;
    [[nodiscard]] virtual void Export() override;
    virtual SegmentType GetSegmentType() const override;
    virtual std::string GetSegmentTypeName() const override;
};

} // namespace Splat::Segtypes