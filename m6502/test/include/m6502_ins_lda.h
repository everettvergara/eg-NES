#pragma once

#include "types.h"

namespace eg::m6502
{
	inline constexpr word RESET_VECTOR_ADDRESS = 0xfffc;
	inline constexpr word RESET_ROUTINE_ADDRESS = 0x0000;

	auto test_LDA_IM_nzero_nneg() -> bool;
	auto test_LDA_IM_zero_nneg() -> bool;
	auto test_LDA_IM_nzero_neg() -> bool;

	auto test_LDA_ZP_nzero_nneg() -> bool;
	auto test_LDA_ZP_zero_nneg() -> bool;
	auto test_LDA_ZP_nzero_neg() -> bool;

}