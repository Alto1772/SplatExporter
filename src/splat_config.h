#pragma once
#include <filesystem>
#include <memory>
#include <string>
#include "options.h"
#include "rom.h"
#include "segment_registry.h"
#include "splat_segment.h"
#include "vram_classes.h"
#include "yaml-cpp/yaml.h"

namespace Splat {

class SplatConfig {
private:
    YAML::Node mSplatConfigRaw;
    std::filesystem::path mFilePath;
    std::vector<std::shared_ptr<Segment>> mSegments;
    std::map<std::string, VramClass> mVramClasses;
    std::shared_ptr<const BinaryRom> mBinaryRom;
    SplatOptions mOptions;

    bool Done = false;

    SplatConfig() = default;

public:
    SplatConfig(const std::filesystem::path&);

    void ParseConfig();
    std::shared_ptr<const BinaryRom> OpenBinaryRom(std::filesystem::path = "");

    bool IsDone() const;
    const YAML::Node& GetConfigRaw() const;
    std::map<std::string, VramClass>& GetVramClassList();
    std::vector<std::shared_ptr<Segment>>& GetSegmentTable();
    const std::filesystem::path& GetConfigPath() const;
    std::shared_ptr<const BinaryRom> GetBinaryRom() const;
    const SplatOptions& GetOptions() const;

    std::string name;
    std::string sha1 = "";
};

} // namespace Splat