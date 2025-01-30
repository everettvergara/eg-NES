#pragma once

#include "types.h"
#include "reg.h"
#include "m6502_tins_common.h"
#include "m6502_generic.h"

namespace eg::m6502
{
	auto test_INX_reg_check(const reg& r, byte val, word pc_add) -> bool;

	auto test_INX_IMP(byte val) -> bool;

	auto test_INX_IMP_nzero_nneg() -> bool;
	auto test_INX_IMP_zero_nneg() -> bool;
	auto test_INX_IMP_nzero_neg() -> bool;
}
