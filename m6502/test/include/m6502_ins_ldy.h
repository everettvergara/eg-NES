#pragma once

#include "types.h"
#include "reg.h"
#include "m6502_ins_common.h"

namespace eg::m6502
{
	auto test_LDY_reg_check(const reg& t, byte val, word pc_add) -> bool;

	auto test_LDY_IM(byte val) -> bool;
	auto test_LDY_ZP(byte val) -> bool;
	auto test_LDY_ZPY(byte val) -> bool;
	auto test_LDY_ABS(byte val) -> bool;
	auto test_LDY_ABSX(byte val, byte X) -> bool;

	auto test_LDY_IM_nzero_nneg() -> bool;
	auto test_LDY_IM_zero_nneg() -> bool;
	auto test_LDY_IM_nzero_neg() -> bool;
	auto test_LDY_ZP_nzero_nneg() -> bool;
	auto test_LDY_ZP_zero_nneg() -> bool;
	auto test_LDY_ZP_nzero_neg() -> bool;
	auto test_LDY_ZPX_nzero_nneg() -> bool;
	auto test_LDY_ZPX_zero_nneg() -> bool;
	auto test_LDY_ZPX_nzero_neg() -> bool;
	auto test_LDY_ABS_nzero_nneg() -> bool;
	auto test_LDY_ABS_zero_nneg() -> bool;
	auto test_LDY_ABS_nzero_neg() -> bool;
	auto test_LDY_ABSX_nzero_nneg_ncarry() -> bool;
	auto test_LDY_ABSX_zero_nneg_ncarry() -> bool;
	auto test_LDY_ABSX_nzero_neg_ncarry() -> bool;
	auto test_LDY_ABSX_nzero_nneg_carry() -> bool;
	auto test_LDY_ABSX_zero_nneg_carry() -> bool;
	auto test_LDY_ABSX_nzero_neg_carry() -> bool;
}
