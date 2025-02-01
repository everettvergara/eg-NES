// References:
// https://www.c64-wiki.com
// https://www.masswerk.at/6502/6502_instruction_set.html
// https://www.nesdev.org/obelisk-6502-guide/reference.html#LDA
// https://github.com/catchorg/Catch2

//#include <iostream>
#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include "m6502_tins_lda.h"
#include "m6502_tins_ldx.h"
#include "m6502_tins_ldy.h"
#include "m6502_tins_nop.h"
#include "m6502_tins_inc.h"
#include "m6502_tins_dec.h"
#include "m6502_tins_inx.h"
#include "m6502_tins_iny.h"
#include "m6502_tins_dex.h"
#include "m6502_tins_dey.h"
#include "m6502_tins_jmp.h"


using namespace eg::m6502;
TEST_CASE("m6502 Instructions:")
{

	SECTION("LDA")
	{
		REQUIRE_NOTHROW([]() {CHECK(test_LDA_IM_nzero_nneg()); }());
		REQUIRE_NOTHROW([]() {CHECK(test_LDA_IM_zero_nneg()); }());
		REQUIRE_NOTHROW([]() {CHECK(test_LDA_IM_nzero_nneg()); }());
		REQUIRE_NOTHROW([]() {CHECK(test_LDA_ZP_nzero_nneg()); }());
		REQUIRE_NOTHROW([]() {CHECK(test_LDA_ZP_zero_nneg()); }());
		REQUIRE_NOTHROW([]() {CHECK(test_LDA_ZP_nzero_neg()); }());
		REQUIRE_NOTHROW([]() {CHECK(test_LDA_ZPX_nzero_nneg()); }());
		REQUIRE_NOTHROW([]() {CHECK(test_LDA_ZPX_zero_nneg()); }());
		REQUIRE_NOTHROW([]() {CHECK(test_LDA_ZPX_nzero_neg()); }());
		REQUIRE_NOTHROW([]() {CHECK(test_LDA_ABS_nzero_nneg()); }());
		REQUIRE_NOTHROW([]() {CHECK(test_LDA_ABS_zero_nneg()); }());
		REQUIRE_NOTHROW([]() {CHECK(test_LDA_ABS_nzero_neg()); }());
		REQUIRE_NOTHROW([]() {CHECK(test_LDA_ABSX_nzero_nneg_ncarry()); }());
		REQUIRE_NOTHROW([]() {CHECK(test_LDA_ABSX_zero_nneg_ncarry()); }());
		REQUIRE_NOTHROW([]() {CHECK(test_LDA_ABSX_nzero_neg_ncarry()); }());
		REQUIRE_NOTHROW([]() {CHECK(test_LDA_ABSX_nzero_nneg_carry()); }());
		REQUIRE_NOTHROW([]() {CHECK(test_LDA_ABSX_zero_nneg_carry()); }());
		REQUIRE_NOTHROW([]() {CHECK(test_LDA_ABSX_nzero_neg_carry()); }());
		REQUIRE_NOTHROW([]() {CHECK(test_LDA_ABSY_nzero_nneg_ncarry()); }());
		REQUIRE_NOTHROW([]() {CHECK(test_LDA_ABSY_zero_nneg_ncarry()); }());
		REQUIRE_NOTHROW([]() {CHECK(test_LDA_ABSY_nzero_neg_ncarry()); }());
		REQUIRE_NOTHROW([]() {CHECK(test_LDA_ABSY_nzero_nneg_carry()); }());
		REQUIRE_NOTHROW([]() {CHECK(test_LDA_ABSY_zero_nneg_carry()); }());
		REQUIRE_NOTHROW([]() {CHECK(test_LDA_ABSY_nzero_neg_carry()); }());
		REQUIRE_NOTHROW([]() {CHECK(test_LDA_INDX_nzero_nneg_ncarry()); }());
		REQUIRE_NOTHROW([]() {CHECK(test_LDA_INDX_zero_nneg_ncarry()); }());
		REQUIRE_NOTHROW([]() {CHECK(test_LDA_INDX_nzero_neg_ncarry()); }());
		REQUIRE_NOTHROW([]() {CHECK(test_LDA_INDX_nzero_nneg_carry()); }());
		REQUIRE_NOTHROW([]() {CHECK(test_LDA_INDX_zero_nneg_carry()); }());
		REQUIRE_NOTHROW([]() {CHECK(test_LDA_INDX_nzero_neg_carry()); }());
		REQUIRE_NOTHROW([]() {CHECK(test_LDA_INDY_nzero_nneg_ncarry()); }());
		REQUIRE_NOTHROW([]() {CHECK(test_LDA_INDY_zero_nneg_ncarry()); }());
		REQUIRE_NOTHROW([]() {CHECK(test_LDA_INDY_nzero_neg_ncarry()); }());
		REQUIRE_NOTHROW([]() {CHECK(test_LDA_INDY_nzero_nneg_carry()); }());
		REQUIRE_NOTHROW([]() {CHECK(test_LDA_INDY_zero_nneg_carry()); }());
		REQUIRE_NOTHROW([]() {CHECK(test_LDA_INDY_nzero_neg_carry()); }());
	}

	SECTION("LDX")
	{
		REQUIRE_NOTHROW([]() {CHECK(test_LDX_IM_nzero_nneg()); }());
		REQUIRE_NOTHROW([]() {CHECK(test_LDX_IM_zero_nneg()); }());
		REQUIRE_NOTHROW([]() {CHECK(test_LDX_IM_nzero_nneg()); }());
		REQUIRE_NOTHROW([]() {CHECK(test_LDX_ZP_nzero_nneg()); }());
		REQUIRE_NOTHROW([]() {CHECK(test_LDX_ZP_zero_nneg()); }());
		REQUIRE_NOTHROW([]() {CHECK(test_LDX_ZP_nzero_neg()); }());
		REQUIRE_NOTHROW([]() {CHECK(test_LDX_ZPY_nzero_nneg()); }());
		REQUIRE_NOTHROW([]() {CHECK(test_LDX_ZPY_zero_nneg()); }());
		REQUIRE_NOTHROW([]() {CHECK(test_LDX_ZPY_nzero_neg()); }());
		REQUIRE_NOTHROW([]() {CHECK(test_LDX_ABS_nzero_nneg()); }());
		REQUIRE_NOTHROW([]() {CHECK(test_LDX_ABS_zero_nneg()); }());
		REQUIRE_NOTHROW([]() {CHECK(test_LDX_ABS_nzero_neg()); }());
		REQUIRE_NOTHROW([]() {CHECK(test_LDX_ABSY_nzero_nneg_ncarry()); }());
		REQUIRE_NOTHROW([]() {CHECK(test_LDX_ABSY_zero_nneg_ncarry()); }());
		REQUIRE_NOTHROW([]() {CHECK(test_LDX_ABSY_nzero_neg_ncarry()); }());
		REQUIRE_NOTHROW([]() {CHECK(test_LDX_ABSY_nzero_nneg_carry()); }());
		REQUIRE_NOTHROW([]() {CHECK(test_LDX_ABSY_zero_nneg_carry()); }());
		REQUIRE_NOTHROW([]() {CHECK(test_LDX_ABSY_nzero_neg_carry()); }());
	}

	SECTION("LDY")
	{
		REQUIRE_NOTHROW([]() {CHECK(test_LDY_IM_nzero_nneg()); }());
		REQUIRE_NOTHROW([]() {CHECK(test_LDY_IM_zero_nneg()); }());
		REQUIRE_NOTHROW([]() {CHECK(test_LDY_IM_nzero_nneg()); }());
		REQUIRE_NOTHROW([]() {CHECK(test_LDY_ZP_nzero_nneg()); }());
		REQUIRE_NOTHROW([]() {CHECK(test_LDY_ZP_zero_nneg()); }());
		REQUIRE_NOTHROW([]() {CHECK(test_LDY_ZP_nzero_neg()); }());
		REQUIRE_NOTHROW([]() {CHECK(test_LDY_ZPX_nzero_nneg()); }());
		REQUIRE_NOTHROW([]() {CHECK(test_LDY_ZPX_zero_nneg()); }());
		REQUIRE_NOTHROW([]() {CHECK(test_LDY_ZPX_nzero_neg()); }());
		REQUIRE_NOTHROW([]() {CHECK(test_LDY_ABS_nzero_nneg()); }());
		REQUIRE_NOTHROW([]() {CHECK(test_LDY_ABS_zero_nneg()); }());
		REQUIRE_NOTHROW([]() {CHECK(test_LDY_ABS_nzero_neg()); }());
		REQUIRE_NOTHROW([]() {CHECK(test_LDY_ABSX_nzero_nneg_ncarry()); }());
		REQUIRE_NOTHROW([]() {CHECK(test_LDY_ABSX_zero_nneg_ncarry()); }());
		REQUIRE_NOTHROW([]() {CHECK(test_LDY_ABSX_nzero_neg_ncarry()); }());
		REQUIRE_NOTHROW([]() {CHECK(test_LDY_ABSX_nzero_nneg_carry()); }());
		REQUIRE_NOTHROW([]() {CHECK(test_LDY_ABSX_zero_nneg_carry()); }());
		REQUIRE_NOTHROW([]() {CHECK(test_LDY_ABSX_nzero_neg_carry()); }());
	}

	SECTION("NOP")
	{
		REQUIRE_NOTHROW([]() {CHECK(test_NOP_IMP()); }());
	}

	SECTION("INC")
	{
		REQUIRE_NOTHROW([]() {CHECK(test_INC_ZP_nzero_nneg()); }());
		REQUIRE_NOTHROW([]() {CHECK(test_INC_ZP_zero_nneg()); }());
		REQUIRE_NOTHROW([]() {CHECK(test_INC_ZP_nzero_neg()); }());
		REQUIRE_NOTHROW([]() {CHECK(test_INC_ZPX_nzero_nneg_ncarry()); }());
		REQUIRE_NOTHROW([]() {CHECK(test_INC_ZPX_zero_nneg_ncarry()); }());
		REQUIRE_NOTHROW([]() {CHECK(test_INC_ZPX_nzero_neg_ncarry()); }());
		REQUIRE_NOTHROW([]() {CHECK(test_INC_ZPX_nzero_nneg_carry()); }());
		REQUIRE_NOTHROW([]() {CHECK(test_INC_ZPX_zero_nneg_carry()); }());
		REQUIRE_NOTHROW([]() {CHECK(test_INC_ZPX_nzero_neg_carry()); }());
		REQUIRE_NOTHROW([]() {CHECK(test_INC_ABS_nzero_nneg()); }());
		REQUIRE_NOTHROW([]() {CHECK(test_INC_ABS_zero_nneg()); }());
		REQUIRE_NOTHROW([]() {CHECK(test_INC_ABS_nzero_neg()); }());

		REQUIRE_NOTHROW([]() {CHECK(test_INC_ABSX_nzero_nneg_ncarry()); }());
		REQUIRE_NOTHROW([]() {CHECK(test_INC_ABSX_zero_nneg_ncarry()); }());
		REQUIRE_NOTHROW([]() {CHECK(test_INC_ABSX_nzero_neg_ncarry()); }());
		REQUIRE_NOTHROW([]() {CHECK(test_INC_ABSX_nzero_nneg_carry()); }());
		REQUIRE_NOTHROW([]() {CHECK(test_INC_ABSX_zero_nneg_carry()); }());
		REQUIRE_NOTHROW([]() {CHECK(test_INC_ABSX_nzero_neg_carry()); }());
	}

	SECTION("DEC")
	{
		REQUIRE_NOTHROW([]() {CHECK(test_DEC_ZP_nzero_nneg()); }());
		REQUIRE_NOTHROW([]() {CHECK(test_DEC_ZP_zero_nneg()); }());
		REQUIRE_NOTHROW([]() {CHECK(test_DEC_ZP_nzero_neg()); }());
		REQUIRE_NOTHROW([]() {CHECK(test_DEC_ZPX_nzero_nneg_ncarry()); }());
		REQUIRE_NOTHROW([]() {CHECK(test_DEC_ZPX_zero_nneg_ncarry()); }());
		REQUIRE_NOTHROW([]() {CHECK(test_DEC_ZPX_nzero_neg_ncarry()); }());
		REQUIRE_NOTHROW([]() {CHECK(test_DEC_ZPX_nzero_nneg_carry()); }());
		REQUIRE_NOTHROW([]() {CHECK(test_DEC_ZPX_zero_nneg_carry()); }());
		REQUIRE_NOTHROW([]() {CHECK(test_DEC_ZPX_nzero_neg_carry()); }());
		REQUIRE_NOTHROW([]() {CHECK(test_DEC_ABS_nzero_nneg()); }());
		REQUIRE_NOTHROW([]() {CHECK(test_DEC_ABS_zero_nneg()); }());
		REQUIRE_NOTHROW([]() {CHECK(test_DEC_ABS_nzero_neg()); }());

		REQUIRE_NOTHROW([]() {CHECK(test_DEC_ABSX_nzero_nneg_ncarry()); }());
		REQUIRE_NOTHROW([]() {CHECK(test_DEC_ABSX_zero_nneg_ncarry()); }());
		REQUIRE_NOTHROW([]() {CHECK(test_DEC_ABSX_nzero_neg_ncarry()); }());
		REQUIRE_NOTHROW([]() {CHECK(test_DEC_ABSX_nzero_nneg_carry()); }());
		REQUIRE_NOTHROW([]() {CHECK(test_DEC_ABSX_zero_nneg_carry()); }());
		REQUIRE_NOTHROW([]() {CHECK(test_DEC_ABSX_nzero_neg_carry()); }());
	}

	SECTION("INX")
	{
		REQUIRE_NOTHROW([]() {CHECK(test_INX_IMP_nzero_nneg()); }());
		REQUIRE_NOTHROW([]() {CHECK(test_INX_IMP_zero_nneg()); }());
		REQUIRE_NOTHROW([]() {CHECK(test_INX_IMP_nzero_neg()); }());
	}

	SECTION("INY")
	{
		REQUIRE_NOTHROW([]() {CHECK(test_INY_IMP_nzero_nneg()); }());
		REQUIRE_NOTHROW([]() {CHECK(test_INY_IMP_zero_nneg()); }());
		REQUIRE_NOTHROW([]() {CHECK(test_INY_IMP_nzero_neg()); }());
	}

	SECTION("DEX")
	{
		REQUIRE_NOTHROW([]() {CHECK(test_DEX_IMP_nzero_nneg()); }());
		REQUIRE_NOTHROW([]() {CHECK(test_DEX_IMP_zero_nneg()); }());
		REQUIRE_NOTHROW([]() {CHECK(test_DEX_IMP_nzero_neg()); }());
	}

	SECTION("DEY")
	{
		REQUIRE_NOTHROW([]() {CHECK(test_DEY_IMP_nzero_nneg()); }());
		REQUIRE_NOTHROW([]() {CHECK(test_DEY_IMP_zero_nneg()); }());
		REQUIRE_NOTHROW([]() {CHECK(test_DEY_IMP_nzero_neg()); }());
	}

	SECTION("JMP")
	{
		REQUIRE_NOTHROW([]() {CHECK(test_JMP_ABS(0x50, 0x30)); }());
		REQUIRE_NOTHROW([]() {CHECK(test_JMP_IND(0x60)); }());
		REQUIRE_NOTHROW([]() {CHECK(test_JMP_IND_bug(0x60)); }());
	}
}
