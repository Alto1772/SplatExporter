#pragma once
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>
#include "spdlog/spdlog.h"
#include "splat_segment.h"
#include "yaml-cpp/yaml.h"

namespace Splat {

using SegmentFactoryFunc = std::function<std::shared_ptr<Segment>(const YAML::Node&, const std::weak_ptr<Segment>&)>;

template <typename T>
class SegmentFactory {
private:
    static std::shared_ptr<Segment> ParseYaml(const YAML::Node& node, const std::weak_ptr<Segment>& parent) {
        auto segment = std::make_shared<T>();
        std::weak_ptr<Segment> _null;
        segment->LinkSegments(parent, _null);
        if (!segment->ParseYaml(node)) {
            SPDLOG_ERROR("Parse error for {} [{}] at line {:d}, column {:d}", segment->name,
                         segment->GetSegmentTypeName(), node.Mark().line + 1, node.Mark().column + 1);
            std::exit(EXIT_FAILURE);
        }

        return std::static_pointer_cast<Segment>(segment);
    }

public:
    constexpr static SegmentFactoryFunc GetFunc() {
        return &ParseYaml;
    }
};

class SegmentRegistry {
private:
    std::unordered_map<std::string, const SegmentFactoryFunc> factories;

public:
    SegmentRegistry();

    void RegisterSegmentFactory(const std::string& typeName, const SegmentFactoryFunc func);
    void RegisterGlobalSegmentFactories();
    std::shared_ptr<Segment> InvokeSegmentFactory(const std::string& typeName, const YAML::Node& node,
                                                  const std::weak_ptr<Segment>& parent);
};

} // namespace Splat