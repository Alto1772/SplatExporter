#include "context.h"
#include <iostream>
#include "spdlog/spdlog.h"
#include "yaml-cpp/yaml.h"

namespace Splat {

std::weak_ptr<Context> Context::mInstance;

Context::Context() {
    SetLoggerSettings();
    InitSegmentManager();
}

Context::~Context() {
    SPDLOG_TRACE("Shutting down");

    mSegmentRegistry = nullptr;
    mSplatConfig = nullptr;
    spdlog::shutdown();
}

std::shared_ptr<SegmentRegistry> Context::GetSegmentRegistry() {
    return mSegmentRegistry;
}

std::shared_ptr<Context> Context::GetInstance() {
    return mInstance.lock();
}

std::shared_ptr<Context> Context::NewInstance() {
    if (mInstance.expired()) {
        auto newInstance = std::make_shared<Context>();
        mInstance = newInstance;
        return newInstance;
    }

    SPDLOG_WARN("Instance of Context already exists...");
    return GetInstance();
}

std::shared_ptr<SplatConfig> Context::ReadSplatConfig(const std::filesystem::path& filePath) {
    if (GetSplatConfig() != nullptr) {
        SPDLOG_WARN("A SplatConfig has already been loaded. Attempting to read a new configuration from '{}' will "
                    "replace the current one in this context.",
                    filePath.string());
    }

    mSplatConfig = std::make_shared<SplatConfig>(filePath);

    GetSplatConfig()->ParseConfig();
    return GetSplatConfig();
}

std::shared_ptr<SplatConfig> Context::GetSplatConfig() {
    return mSplatConfig;
}

void Context::InitSegmentManager() {
    mSegmentRegistry = std::make_shared<SegmentRegistry>();

    mSegmentRegistry->RegisterGlobalSegmentFactories();
}

void Context::SetLoggerSettings() {
#ifdef _DEBUG
    // spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%s:%#] [%l] %v");
    spdlog::set_pattern("[%l] %v");
    spdlog::set_level(spdlog::level::trace);
#else
    spdlog::set_pattern("[%L] %v");
    spdlog::set_level(spdlog::level::info);
#endif
}

} // namespace Splat