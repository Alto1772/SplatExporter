#include <filesystem>
#include "context.h"
#include "spdlog/spdlog.h"

int main(int argc, char* argv[]) {
    if (argc < 1)
        return 1;

    const std::filesystem::path splatConfig = argv[1];

    auto Splatodeon = Splat::Context::NewInstance();

    auto config = Splatodeon->ReadSplatConfig(splatConfig);
    // std::filesystem::current_path(config->base_path);
    config->OpenBinaryRom();

    return 0;
}