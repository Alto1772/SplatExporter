#pragma once
#include "segtypes/n64/img.h"
#include "splat_segment.h"

namespace Splat::Segtypes::N64 {

class CI : public ImageSegment {};

class CI8 : public CI {};

class CI4 : public CI {};

} // namespace Splat::Segtypes::N64
