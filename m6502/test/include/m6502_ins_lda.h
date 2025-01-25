#pragma once

#include "types.h"
#include "reg.h"
#include "m6502_ins_common.h"

namespace eg::m6502
{
	auto test_LDA_reg_check(const reg& t, byte val, word pc_add) -> bool;

	auto test_LDA_IM(byte val) -> bool;
	auto test_LDA_ZP(byte val) -> bool;
	auto test_LDA_ZPX(byte val) -> bool;
	auto test_LDA_ABS(byte val) -> bool;
	auto test_LDA_ABSX(byte val, byte X) -> bool;
	auto test_LDA_ABSY(byte val, byte Y) -> bool;
	auto test_LDA_INDX(byte val, byte X) -> bool;
	auto test_LDA_INDY(byte val, byte Y) -> bool;

	auto test_LDA_IM_nzero_nneg() -> bool;
	auto test_LDA_IM_zero_nneg() -> bool;
	auto test_LDA_IM_nzero_neg() -> bool;
	auto test_LDA_ZP_nzero_nneg() -> bool;
	auto test_LDA_ZP_zero_nneg() -> bool;
	auto test_LDA_ZP_nzero_neg() -> bool;
	auto test_LDA_ZPX_nzero_nneg() -> bool;
	auto test_LDA_ZPX_zero_nneg() -> bool;
	auto test_LDA_ZPX_nzero_neg() -> bool;
	auto test_LDA_ABS_nzero_nneg() -> bool;
	auto test_LDA_ABS_zero_nneg() -> bool;
	auto test_LDA_ABS_nzero_neg() -> bool;
	auto test_LDA_ABSX_nzero_nneg_ncarry() -> bool;
	auto test_LDA_ABSX_zero_nneg_ncarry() -> bool;
	auto test_LDA_ABSX_nzero_neg_ncarry() -> bool;
	auto test_LDA_ABSX_nzero_nneg_carry() -> bool;
	auto test_LDA_ABSX_zero_nneg_carry() -> bool;
	auto test_LDA_ABSX_nzero_neg_carry() -> bool;
	auto test_LDA_ABSY_nzero_nneg_ncarry() -> bool;
	auto test_LDA_ABSY_zero_nneg_ncarry() -> bool;
	auto test_LDA_ABSY_nzero_neg_ncarry() -> bool;
	auto test_LDA_ABSY_nzero_nneg_carry() -> bool;
	auto test_LDA_ABSY_zero_nneg_carry() -> bool;
	auto test_LDA_ABSY_nzero_neg_carry() -> bool;
	auto test_LDA_INDX_nzero_nneg_ncarry() -> bool;
	auto test_LDA_INDX_zero_nneg_ncarry() -> bool;
	auto test_LDA_INDX_nzero_neg_ncarry() -> bool;
	auto test_LDA_INDX_nzero_nneg_carry() -> bool;
	auto test_LDA_INDX_zero_nneg_carry() -> bool;
	auto test_LDA_INDX_nzero_neg_carry() -> bool;
	auto test_LDA_INDY_nzero_nneg_ncarry() -> bool;
	auto test_LDA_INDY_zero_nneg_ncarry() -> bool;
	auto test_LDA_INDY_nzero_neg_ncarry() -> bool;
	auto test_LDA_INDY_nzero_nneg_carry() -> bool;
	auto test_LDA_INDY_zero_nneg_carry() -> bool;
	auto test_LDA_INDY_nzero_neg_carry() -> bool;
}
