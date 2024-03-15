#pragma once
#include <vector>
#include "segtypes/binary.h"
#include "splat_segment.h"

namespace Splat::Segtypes::N64 {

enum class ImageType {
    I1,
    I4,
    I8,
    IA4,
    IA8,
    IA16,
    RGBA16,
    RGBA32,
    CI4,
    CI8,
};

class ImageSegment : public BinarySegment {
public:
    bool flip_x = false;
    bool flip_y = false;
    uint32_t width, height;
    std::vector<uint8_t> data;

    ImageSegment();
    virtual bool ParseYaml(const YAML::Node&) override;
    virtual void Extract() override;
    virtual void Export() override;
    virtual std::filesystem::path GetOutPath() const override;
    uint32_t CalculateSize() const;

    [[nodiscard]] virtual ImageType GetImageType() const = 0;
    [[nodiscard]] virtual int GetImageTypeBpp() const = 0;
    [[nodiscard]] virtual std::string GetImageTypeName() const = 0;
};

} // namespace Splat::Segtypes::N64
