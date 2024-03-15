#pragma once
#include <vector>
#include "splat_segment.h"

namespace Splat::Segtypes {
class BinarySegment : public Segment {
public:
    std::vector<uint8_t> data;

    BinarySegment();

    virtual bool ParseYaml(const YAML::Node&) override;
    virtual void Extract() override;
    virtual void Export() override;
    virtual SegmentType GetSegmentType() const override;
    virtual std::string GetSegmentTypeName() const override;
};
} // namespace Splat::Segtypes
