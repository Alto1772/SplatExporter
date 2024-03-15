#pragma once
#include "splat_segment.h"

namespace Splat::Segtypes {

// C-labeled code type
class CCode : public Segment {
public:
    virtual void Extract() override;
    virtual void Export() override;
    virtual SegmentType GetSegmentType() const override;
    virtual std::string GetSegmentTypeName() const override;
};

// C++-labeled code type
class CppCode : public CCode {
public:
    virtual SegmentType GetSegmentType() const override;
    virtual std::string GetSegmentTypeName() const override;
};

// ASM code type
class AsmCode : public Segment {
public:
    virtual void Extract() override;
    virtual void Export() override;
    virtual SegmentType GetSegmentType() const override;
    virtual std::string GetSegmentTypeName() const override;
};

// Hand-written ASM variant type
class HasmCode : public AsmCode {
public:
    virtual SegmentType GetSegmentType() const override;
    virtual std::string GetSegmentTypeName() const override;
};

} // namespace Splat::Segtypes
