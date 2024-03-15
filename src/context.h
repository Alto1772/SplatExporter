#pragma once
#include <filesystem>
#include <memory>
#include "segment_registry.h"
#include "splat_config.h"
#include "yaml-cpp/yaml.h"

namespace Splat {

// A Context class for global general usage
class Context {
private:
    static std::weak_ptr<Context> mInstance;

    std::shared_ptr<SegmentRegistry> mSegmentRegistry;
    std::shared_ptr<SplatConfig> mSplatConfig;

public:
    Context();
    ~Context();
    static std::shared_ptr<Context> GetInstance();
    static std::shared_ptr<Context> NewInstance();

    std::shared_ptr<SplatConfig> ReadSplatConfig(const std::filesystem::path&);
    void InitSegmentManager();
    static void SetLoggerSettings();

    std::shared_ptr<SegmentRegistry> GetSegmentRegistry();
    std::shared_ptr<SplatConfig> GetSplatConfig();
};

} // namespace Splat