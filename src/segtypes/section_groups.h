#pragma once
#include "segtypes/group.h"
#include "splat_segment.h"

namespace Splat::Segtypes {

class CodeGroupSegment : public GroupTypeSegment {
public:
    virtual bool ParseYaml(const YAML::Node&) override;
    virtual SegmentType GetSegmentType() const override;
    virtual std::string GetSegmentTypeName() const override;
    // virtual void Extract() override;
    // virtual void Export() override;
};

// A Data section used for the linker script to indicate where it should be placed.
// It's jointly linked to a C-labeled code type, and can have resources stored inside.
class DataSectionGroup : public GroupTypeSegment {
public:
    virtual SegmentType GetSegmentType() const override;
    virtual std::string GetSegmentTypeName() const override;
    // virtual void Extract() override;
    // virtual void Export() override;
};

// Read-only data section, mostly the same functionality as its Data section counterpart.
class RodataSectionGroup : public DataSectionGroup {
public:
    virtual SegmentType GetSegmentType() const override;
    virtual std::string GetSegmentTypeName() const override;
};

// A BSS section group, highly unlikely to have subsegments even if it belongs to the group class
class BssSectionGroup : public DataSectionGroup {
public:
    virtual SegmentType GetSegmentType() const override;
    virtual std::string GetSegmentTypeName() const override;
};

} // namespace Splat::Segtypes
