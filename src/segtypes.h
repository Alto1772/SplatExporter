#pragma once
#include <cstdint>

namespace Splat {
enum class SegmentType : uint16_t {
    NullSegment,
    HeaderSegment,
    CodeGroupSegment,
    GroupSegment,
    BinarySegment,

    DataSectionGroup,
    RodataSectionGroup,
    BssSectionGroup,

    BinarySectionText,
    BinarySectionData,
    BinarySectionRodata,

    CCode,
    CppCode,
    AsmCode,
    HasmCode,

    // N64 Types
    N64Gfx,
    N64Vtx,
    N64ImgI1,
    N64ImgI4,
    N64ImgI8,
    N64ImgIA4,
    N64ImgIA8,
    N64ImgIA16,
    N64ImgCI4,
    N64ImgCI8,
    N64ImgRGBA16,
    N64ImgRGBA32,
    N64ImgPalette,

    CustomSegment = 256,
};
}