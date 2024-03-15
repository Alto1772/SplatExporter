#include "splat_segment.h"
#include <ios>
#include <optional>
#include <sstream>
#include "context.h"
#include "segtypes/null.h"

namespace Splat {

static std::variant<uint32_t, SegmentAutoType> ParseSegmentStart(const YAML::Node& node) {
    const YAML::Node& start = node.IsMap() ? node["start"] : node[0];

    if (start.Scalar() == "auto" || start.Scalar() == "...")
        return SegmentAuto;
    else
        return start.as<uint32_t>();
}

static std::optional<std::string> ParseSegmentType(const YAML::Node& node) {
    switch (node.Type()) {
    case YAML::NodeType::Sequence:
        return node[1].Scalar();
        break;
    case YAML::NodeType::Map:
        return node["type"].Scalar();
        break;
    default:
        return std::nullopt;
    }
}

std::string Segment::GetDefaultName() const {
    if (std::holds_alternative<SegmentAutoType>(start))
        return "";

    std::stringstream ss;
    ss << std::uppercase << std::hex << std::get<uint32_t>(start);
    return ss.str();
}

std::filesystem::path Segment::GetOutPath() const {
    std::filesystem::path assets_path = Context::GetInstance()->GetSplatConfig()->GetOptions().assets_path;

    return assets_path / dir.value_or("") / name;
}

static std::optional<std::string> ParseSegmentName(const YAML::Node& node) {
    if (node.IsMap() && node["name"].IsDefined())
        return node["name"].Scalar();
    else if (node.IsMap() && node["dir"].IsDefined())
        return node["dir"].Scalar();
    else if (node.IsSequence() && node.size() >= 3)
        return node[2].Scalar();
    else
        return std::nullopt;
}

bool Segment::ParseYaml(const YAML::Node& node) {
    start = ParseSegmentStart(node);
    auto oName = ParseSegmentName(node);
    name = oName ? oName.value() : GetDefaultName();

    if (node.IsMap()) {
        if (node["dir"].IsDefined())
            dir = node["dir"].Scalar();
        if (node["vram"].IsDefined())
            vram = node["vram"].as<uint32_t>();
        if (node["align"].IsDefined())
            align = node["align"].as<int>();

        subalign = node["subalign"].as<int>(Context::GetInstance()->GetSplatConfig()->GetOptions().subalign);
    }

    return true;
}

void Segment::LinkSegments(const std::weak_ptr<Segment>& nParent, std::weak_ptr<Segment>& neighbor, bool isBehind) {
    if (!nParent.expired())
        parent = nParent;

    if (!neighbor.expired()) {
        auto shared_neighbor = neighbor.lock();

        if (!isBehind) {
            next = std::move(neighbor);
            shared_neighbor->prev = weak_from_this();
        } else {
            prev = std::move(neighbor);
            shared_neighbor->next = weak_from_this();
        }
    }
}

void Segment::ParseSegments(const std::weak_ptr<Segment>& parent, std::vector<std::shared_ptr<Segment>>& segments,
                            const YAML::Node& segmentListRaw) {
    std::weak_ptr<Segment> lastSegment;
    for (const auto& segmentRaw : segmentListRaw) {
        std::shared_ptr<Segment> segment;

        if (segmentRaw.size() > 1) {
            segment = Context::GetInstance()->GetSegmentRegistry()->InvokeSegmentFactory(
                ParseSegmentType(segmentRaw).value(), segmentRaw, parent);
        } else {
            auto nullseg = std::make_shared<Segtypes::NullSegment>();
            nullseg->start = ParseSegmentStart(segmentRaw);
            segment = std::static_pointer_cast<Segment>(nullseg);
        }

        segments.push_back(segment);
        segment->LinkSegments(parent, lastSegment);
        segment->Check();
        lastSegment = segment;
    }
}

void Segment::Check() const {
    if (canNotHaveStartAsAuto && std::holds_alternative<SegmentAutoType>(start)) {
        throw UnexpectedStartAuto(*this);
    }
}

} // namespace Splat