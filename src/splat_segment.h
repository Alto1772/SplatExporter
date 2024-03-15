#pragma once
#include <cstdint>
#include <exception>
#include <filesystem>
#include <functional>
#include <map>
#include <memory>
#include <optional>
#include <sstream>
#include <string>
#include <type_traits>
#include <variant>
#include <vector>
#include "segtypes.h"
#include "yaml-cpp/yaml.h"

namespace Splat {
// Dummy class for unknown start offsets
struct SegmentAutoType {};
inline constexpr SegmentAutoType SegmentAuto{SegmentAutoType()};

// A Splat Segment Class, inspired from ZAPD's ZResource
// Attributes are populated by the yaml-cpp convert feature
class Segment : public std::enable_shared_from_this<Segment> {
public:
    std::variant<uint32_t, SegmentAutoType> start = SegmentAuto;
    std::optional<size_t> size;
    std::string name;
    std::optional<std::filesystem::path> dir;
    std::optional<uint32_t> vram;
    bool isOffsetAuto = false;
    int subalign;
    std::optional<int> align;

    std::weak_ptr<Segment> parent, next, prev;
    std::vector<std::shared_ptr<Segment>> siblings;

    static void ParseSegments(const std::weak_ptr<Segment>&, std::vector<std::shared_ptr<Segment>>&, const YAML::Node&);

    virtual bool ParseYaml(const YAML::Node&);
    [[nodiscard]] virtual void Extract() = 0;
    [[nodiscard]] virtual void Export() = 0;
    [[nodiscard]] virtual SegmentType GetSegmentType() const = 0;
    [[nodiscard]] virtual std::string GetSegmentTypeName() const = 0;
    virtual void Check() const;
    virtual std::string GetDefaultName() const;
    virtual std::filesystem::path GetOutPath() const;

    void LinkSegments(const std::weak_ptr<Segment>&, std::weak_ptr<Segment>&, bool = true);

protected:
    bool canHaveSubsegments = false;
    bool canExport = false;
    bool canNotHaveStartAsAuto = false;
};

class SegmentException : public std::runtime_error {
private:
    const std::string& msg;
    const Segment& seg;

public:
    SegmentException(const SegmentException&) = default;
    SegmentException(const Segment& nSeg, const std::string& nMsg)
        : std::runtime_error(build_what(nSeg, nMsg)), seg{nSeg}, msg{nMsg} {}

    static const std::string build_what(const Segment& nSeg, const std::string& nMsg) {
        std::stringstream ss;

        ss << "Error at segment " << nSeg.name << ": " << nMsg;

        return ss.str();
    }
};

class UnexpectedStartAuto : public SegmentException {
public:
    UnexpectedStartAuto(const Segment& nSeg) : SegmentException(nSeg, "Starting offset must not be auto") {}
};

} // namespace Splat
