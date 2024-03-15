#include "rom.h"
#include <openssl/sha.h>
#include <utility>
#include "util/file.h"
#include "util/string.h"

namespace Splat {

BinaryRom::BinaryRom(const std::vector<uint8_t>& nData) : data(nData) {}

BinaryRom::BinaryRom(const std::vector<uint8_t>& nData, const std::filesystem::path& nRomPath)
    : data(nData), romPath{nRomPath} {}

BinaryRom* BinaryRom::FromPath(const std::filesystem::path& nRomPath) {
    auto data = File::ReadFileBinary(std::filesystem::absolute(nRomPath).string());

    if (data.size() == 0) {
        std::exit(EXIT_FAILURE);
    }

    BinaryRom* bin = new BinaryRom(data, nRomPath);
    return bin;
}

BinaryRom* BinaryRom::FromData(const std::vector<uint8_t>& nData) {
    BinaryRom* bin = new BinaryRom(nData);
    return bin;
}

bool BinaryRom::ValidateRom(const std::string& sha1Hash) const {
    unsigned char hash[SHA_DIGEST_LENGTH];

    // Faster calculation from OpenSSL's SHA1 algo
    SHA1(data.data(), data.size(), hash);
    std::string ourHash = StringHelper::StrhexFromBytes(hash, SHA_DIGEST_LENGTH);

    return StringHelper::CompareCaseInsensitive(ourHash, sha1Hash);
}

const std::vector<uint8_t>& BinaryRom::GetRomData() const {
    return data;
}

const std::filesystem::path& BinaryRom::GetRomPath() const {
    return romPath;
}

} // namespace Splat