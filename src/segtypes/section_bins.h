#pragma once
#include "segtypes/binary.h"
#include "splat_segment.h"

namespace Splat::Segtypes {
class TextBinSegment : public BinarySegment {
public:
    virtual SegmentType GetSegmentType() const override;
    virtual std::string GetSegmentTypeName() const override;
};

class DataBinSegment : public BinarySegment {
public:
    virtual SegmentType GetSegmentType() const override;
    virtual std::string GetSegmentTypeName() const override;
};

class RodataBinSegment : public BinarySegment {
public:
    virtual SegmentType GetSegmentType() const override;
    virtual std::string GetSegmentTypeName() const override;
};

} // namespace Splat::Segtypes
