// References:
// https://www.c64-wiki.com
// https://www.masswerk.at/6502/6502_instruction_set.html
// https://www.nesdev.org/obelisk-6502-guide/reference.html#LDA
// https://github.com/catchorg/Catch2

//#include <iostream>
#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include "m6502_ins_lda.h"
#include "m6502_ins_ldx.h"
#include "m6502_ins_ldy.h"
#include "m6502_ins_nop.h"

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
}
