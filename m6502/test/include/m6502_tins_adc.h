#pragma once

#include "types.h"
#include "reg.h"
#include "m6502_tins_common.h"
#include "m6502_generic.h"

namespace eg::m6502
{
	auto test_ADC_reg_check(const reg& r, byte A, byte val, bool carry, word pc_add, bool expected_C, bool expected_V) -> bool;

	auto test_ADC_IM(byte A, byte val, bool carry) -> bool;


	auto test_ADC_IM_nzero_nneg_ncarry_noverflow() -> bool;
	auto test_ADC_IM_zero_nneg_ncarry_noverflow() -> bool;
	auto test_ADC_IM_nzero_nneg_carry_noverflow() -> bool;
	auto test_ADC_IM_nzero_neg_ncarry_noverflow() -> bool;
	//auto test_ADC_IM_nzero_nneg_ncarry_overflow_positive() -> bool;
	//auto test_ADC_IM_nzero_nneg_ncarry_overflow_negative() -> bool;

}
