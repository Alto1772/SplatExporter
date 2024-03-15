#include "splat_config.h"
#include <algorithm>
#include <ranges>
#include <utility>
#include "context.h"
#include "options.h"
#include "segtypes/section_groups.h"
#include "spdlog/spdlog.h"
#include "vram_classes.h"

namespace Splat {
SplatConfig::SplatConfig(const std::filesystem::path& path) : mFilePath(path) {}

void SplatConfig::ParseConfig() {
    if (!std::filesystem::exists(GetConfigPath())) {
        SPDLOG_ERROR("{} does not exist!", GetConfigPath().string());
        std::exit(EXIT_FAILURE);
    }

    SPDLOG_INFO("Reading file \"{}\"", GetConfigPath().string());

    try {
        mSplatConfigRaw = YAML::LoadFile(GetConfigPath().string());
    } catch (const ::YAML::BadFile& e) {
        (void)e;
        SPDLOG_ERROR("Exception occured while trying to load file {}. The file may not be exist or is inaccessible.",
                     GetConfigPath().string());
        std::exit(EXIT_FAILURE);
    } catch (const ::YAML::ParserException& e) {
        SPDLOG_ERROR("Error scanning \"{}\":\n    {}", GetConfigPath().string(), e.what());
        std::exit(EXIT_FAILURE);
    }

    try {
        const auto& config = GetConfigRaw();

        name = config["name"].as<std::string>();
        sha1 = config["sha1"].as<std::string>("");

        mOptions = config["options"].as<SplatOptions>(SplatOptions());

        const auto& vramClasses = config["vram_classes"];
        if (vramClasses.IsDefined()) {
            // POUTANGENA SI OPTIMUM PRIDE BABE OH!!1!!11!  *ÜRR ÜRR AE AE AE*
            std::ranges::transform(vramClasses, std::inserter(mVramClasses, mVramClasses.end()),
                                   [](const YAML::Node& node) -> std::pair<std::string, VramClass> {
                                       VramClass vclass = node.as<VramClass>();
                                       return std::make_pair(vclass.name, vclass);
                                   });
        }

        Segment::ParseSegments(std::shared_ptr<Segment>(nullptr), GetSegmentTable(), config["segments"]);
        Done = true;

    } catch (const ::YAML::Exception& e) {
        SPDLOG_ERROR("Error parsing through \"{}\" ({})", GetConfigPath().string(), e.what());
        std::exit(EXIT_FAILURE);
    }
}

const YAML::Node& SplatConfig::GetConfigRaw() const {
    return mSplatConfigRaw;
}

const std::filesystem::path& SplatConfig::GetConfigPath() const {
    return mFilePath;
}

bool SplatConfig::IsDone() const {
    return Done;
}

std::map<std::string, VramClass>& SplatConfig::GetVramClassList() {
    return mVramClasses;
}

std::vector<std::shared_ptr<Segment>>& SplatConfig::GetSegmentTable() {
    return mSegments;
}

std::shared_ptr<const BinaryRom> SplatConfig::GetBinaryRom() const {
    return mBinaryRom;
}

const SplatOptions& SplatConfig::GetOptions() const {
    return mOptions;
}

std::shared_ptr<const BinaryRom> SplatConfig::OpenBinaryRom(std::filesystem::path rom) {
    if (rom == "") {
        rom = GetOptions().target_path;
    }

    mBinaryRom = std::shared_ptr<const BinaryRom>(BinaryRom::FromPath(rom));

    if (sha1 == "") {
        SPDLOG_WARN("{}: Missing 'sha1' attribute to verify the target Rom.", GetConfigPath().string());
    } else {
        if (GetBinaryRom()->ValidateRom(sha1)) {
            SPDLOG_INFO("{}: OK", std::filesystem::absolute(rom).string());
        } else {
            SPDLOG_ERROR("Malformed ROM given at '{}' (expected hash: '{}')", rom.string(), sha1);
            std::exit(EXIT_FAILURE);
        }
    }

    return GetBinaryRom();
}
} // namespace Splat