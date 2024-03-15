#include "segment_registry.h"
#include <utility>
#include "context.h"
#include "segtypes/binary.h"
#include "segtypes/c_asm_codes.h"
#include "segtypes/header.h"
#include "segtypes/n64/gfx.h"
#include "segtypes/n64/palette.h"
#include "segtypes/section_bins.h"
#include "segtypes/section_groups.h"
#include "spdlog/spdlog.h"

namespace Splat {

SegmentRegistry::SegmentRegistry() {}

void SegmentRegistry::RegisterSegmentFactory(const std::string& typeName, const SegmentFactoryFunc func) {
    factories.emplace(typeName, func);
}

std::shared_ptr<Segment> SegmentRegistry::InvokeSegmentFactory(const std::string& typeName, const YAML::Node& node,
                                                               const std::weak_ptr<Segment>& parent) {
    auto func = factories.find(typeName);

    if (func == factories.end()) {
        SPDLOG_ERROR("Failed to parse splatfile. Segment type \"{}\" is either invalid or unimplemented. (at line "
                     "{:d}, column {:d})",
                     typeName, node.Mark().line + 1, node.Mark().column + 1);
        std::terminate();
        // std::exit(EXIT_FAILURE);
    }

    return (func->second)(node, parent);
}

void SegmentRegistry::RegisterGlobalSegmentFactories() {
    using namespace Segtypes;

    RegisterSegmentFactory("code", SegmentFactory<CodeGroupSegment>::GetFunc());
    RegisterSegmentFactory("header", SegmentFactory<Header>::GetFunc());
    RegisterSegmentFactory("c", SegmentFactory<CCode>::GetFunc());
    RegisterSegmentFactory("cpp", SegmentFactory<CppCode>::GetFunc());
    RegisterSegmentFactory("asm", SegmentFactory<AsmCode>::GetFunc());
    RegisterSegmentFactory("hasm", SegmentFactory<HasmCode>::GetFunc());
    RegisterSegmentFactory(".data", SegmentFactory<DataSectionGroup>::GetFunc());
    RegisterSegmentFactory(".rodata", SegmentFactory<RodataSectionGroup>::GetFunc());
    RegisterSegmentFactory(".bss", SegmentFactory<BssSectionGroup>::GetFunc());

    // Exportable segments
    RegisterSegmentFactory("bin", SegmentFactory<BinarySegment>::GetFunc());
    RegisterSegmentFactory("textbin", SegmentFactory<TextBinSegment>::GetFunc());
    RegisterSegmentFactory("databin", SegmentFactory<DataBinSegment>::GetFunc());
    RegisterSegmentFactory("rodatabin", SegmentFactory<RodataBinSegment>::GetFunc());
    RegisterSegmentFactory("gfx", SegmentFactory<N64::GfxSegment>::GetFunc());
    RegisterSegmentFactory("palette", SegmentFactory<N64::Palette>::GetFunc());

    // NOTE: do we really need to add these ones?
    // they only appear on incomplete decomp projects afaik...
    RegisterSegmentFactory("data", SegmentFactory<DataSectionGroup>::GetFunc());
    RegisterSegmentFactory("rodata", SegmentFactory<RodataSectionGroup>::GetFunc());
    RegisterSegmentFactory("bss", SegmentFactory<BssSectionGroup>::GetFunc());
}

} // namespace Splat
