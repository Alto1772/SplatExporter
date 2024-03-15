#pragma once
#include "segtypes/binary.h"
#include "splat_segment.h"

namespace Splat::Segtypes::N64 {

class GfxSegment : public BinarySegment {
public:
    bool data_only = false;
    bool in_segment = true;

    virtual bool ParseYaml(const YAML::Node&) override;
    virtual void Extract() override;
    virtual void Export() override;
    virtual SegmentType GetSegmentType() const override;
    virtual std::string GetSegmentTypeName() const override;
};

} // namespace Splat::Segtypes::N64
