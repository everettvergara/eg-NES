﻿// References:
// https://www.c64-wiki.com
// https://www.masswerk.at/6502/6502_instruction_set.html
// https://www.nesdev.org/obelisk-6502-guide/reference.html#LDA
// https://github.com/catchorg/Catch2

//#include <iostream>
#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include "m6502_ins_lda.h"

using namespace eg::m6502;
TEST_CASE("m6502 Instructions:")
{
	SECTION("LDA")
	{
		REQUIRE_NOTHROW(test_LDA_IM_nzero_nneg());
		REQUIRE_NOTHROW(test_LDA_IM_zero_nneg());
		REQUIRE_NOTHROW(test_LDA_IM_nzero_nneg());

		REQUIRE_NOTHROW(test_LDA_ZP_nzero_nneg());
		REQUIRE_NOTHROW(test_LDA_ZP_zero_nneg());
		REQUIRE_NOTHROW(test_LDA_ZP_nzero_neg());

		REQUIRE_NOTHROW(test_LDA_ZPX_nzero_nneg());
		REQUIRE_NOTHROW(test_LDA_ZPX_zero_nneg());
		REQUIRE_NOTHROW(test_LDA_ZPX_nzero_neg());

		REQUIRE_NOTHROW(test_LDA_ABS_nzero_nneg());
		REQUIRE_NOTHROW(test_LDA_ABS_zero_nneg());
		REQUIRE_NOTHROW(test_LDA_ABS_nzero_neg());
	}
}
