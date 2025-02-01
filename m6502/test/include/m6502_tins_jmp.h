#pragma once

#include "types.h"
#include "reg.h"
#include "m6502_tins_common.h"
#include "m6502_generic.h"

namespace eg::m6502
{
	auto test_JMP_reg_check(const reg& reg_orig, const reg& reg_new, word pc_add) -> bool;

	auto test_JMP_ABS(byte low_add, byte high_add) -> bool;
	auto test_JMP_IND(byte high_add) -> bool;
	auto test_JMP_IND_bug(byte high_add) -> bool;
}
