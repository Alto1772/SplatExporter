#pragma once
#include <optional>
#include "segtypes/n64/img.h"
#include "splat_segment.h"

namespace Splat::Segtypes::N64 {

class Palette : public Segment {
public:
    std::vector<uint8_t> data;

    virtual bool ParseYaml(const YAML::Node&) override;
    virtual void Extract() override;
    virtual void Export() override;
    virtual SegmentType GetSegmentType() const override;
    virtual std::string GetSegmentTypeName() const override;
};

} // namespace Splat::Segtypes::N64
