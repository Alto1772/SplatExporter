#pragma once
#include "splat_segment.h"

namespace Splat::Segtypes {

class Header : public Segment {
public:
    virtual void Extract() override;
    virtual void Export() override;
    virtual SegmentType GetSegmentType() const override;
    virtual std::string GetSegmentTypeName() const override;
    virtual std::string GetDefaultName() const override;
};

} // namespace Splat::Segtypes
