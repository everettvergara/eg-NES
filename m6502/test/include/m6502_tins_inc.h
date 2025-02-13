#pragma once

#include "types.h"
#include "reg.h"
#include "m6502_tins_common.h"
#include "m6502_generic.h"

namespace eg::m6502
{
	auto test_INC_cpu_check(const m6502_generic& cpu, word wadd, byte val, word pc_add) -> bool;

	auto test_INC_ZP(byte val) -> bool;
	auto test_INC_ZPX(byte val, byte X) -> bool;
	auto test_INC_ABS(byte val) -> bool;
	auto test_INC_ABSX(byte val) -> bool;

	auto test_INC_ZP_nzero_nneg() -> bool;
	auto test_INC_ZP_zero_nneg() -> bool;
	auto test_INC_ZP_nzero_neg() -> bool;
	auto test_INC_ZPX_nzero_nneg_ncarry() -> bool;
	auto test_INC_ZPX_zero_nneg_ncarry() -> bool;
	auto test_INC_ZPX_nzero_neg_ncarry() -> bool;
	auto test_INC_ZPX_nzero_nneg_carry() -> bool;
	auto test_INC_ZPX_zero_nneg_carry() -> bool;
	auto test_INC_ZPX_nzero_neg_carry() -> bool;
	auto test_INC_ABS_nzero_nneg() -> bool;
	auto test_INC_ABS_zero_nneg() -> bool;
	auto test_INC_ABS_nzero_neg() -> bool;
	auto test_INC_ABSX_nzero_nneg_ncarry() -> bool;
	auto test_INC_ABSX_zero_nneg_ncarry() -> bool;
	auto test_INC_ABSX_nzero_neg_ncarry() -> bool;
	auto test_INC_ABSX_nzero_nneg_carry() -> bool;
	auto test_INC_ABSX_zero_nneg_carry() -> bool;
	auto test_INC_ABSX_nzero_neg_carry() -> bool;
}
