// References:
// https://www.c64-wiki.com
// https://www.masswerk.at/6502/6502_instruction_set.html
// https://www.nesdev.org/obelisk-6502-guide/reference.html#LDA
// https://github.com/catchorg/Catch2

//#include <iostream>
#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include "m6502_ins_lda.h"


TEST_CASE("m6502 Instructions:")
{ 
	SECTION("LDA")
	{
		REQUIRE(eg::m6502::test_LDA_IM_nzero_nneg());
		REQUIRE(eg::m6502::test_LDA_IM_zero_nneg());
		REQUIRE(eg::m6502::test_LDA_IM_nzero_nneg());

		REQUIRE(eg::m6502::test_LDA_ZP_nzero_nneg());
		REQUIRE(eg::m6502::test_LDA_ZP_zero_nneg());
		REQUIRE(eg::m6502::test_LDA_ZP_nzero_neg());
	}
}
