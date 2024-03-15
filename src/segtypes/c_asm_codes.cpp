#include "segtypes/c_asm_codes.h"

namespace Splat::Segtypes {

//
// C-labeled code type
//

void CCode::Extract() {}
void CCode::Export() {}
SegmentType CCode::GetSegmentType() const {
    return SegmentType::CCode;
}
std::string CCode::GetSegmentTypeName() const {
    return "c";
}

//
// C++-labeled code type
//

SegmentType CppCode::GetSegmentType() const {
    return SegmentType::CppCode;
}
std::string CppCode::GetSegmentTypeName() const {
    return "cpp";
}

//
// ASM code type
//

void AsmCode::Extract() {}
void AsmCode::Export() {}
SegmentType AsmCode::GetSegmentType() const {
    return SegmentType::AsmCode;
}
std::string AsmCode::GetSegmentTypeName() const {
    return "asm";
}

//
// Hand-written ASM variant type
//

SegmentType HasmCode::GetSegmentType() const {
    return SegmentType::HasmCode;
}
std::string HasmCode::GetSegmentTypeName() const {
    return "hasm";
}

} // namespace Splat::Segtypes
