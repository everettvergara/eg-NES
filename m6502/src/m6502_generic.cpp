#pragma once

#include "m6502_generic.h"

namespace eg::m6502
{
	m6502_generic::m6502_generic(word reset_vector_add, word reset_routine_addr) :
		m6502(reset_vector_add, reset_routine_addr)
	{
	}

	auto m6502_generic::reset() -> void
	{
		reg_.PC = reset_vector_addr_;
	}

	auto m6502_generic::test_load_mem(mem m) -> void
	{
		mem_ = std::move(m);
	}

	auto m6502_generic::test_load_reg_X(byte X) -> void
	{
		reg_.X = X;
	}

	auto m6502_generic::test_load_reg_Y(byte Y) -> void
	{
		reg_.Y = Y;
	}

	auto m6502_generic::test_loader() -> void
	{
		// LDA_INDY - no carry
		reg_.Y = 0x80;
		mem_[reset_vector_addr_] = LDA_INDY;
		mem_[reset_vector_addr_ + 1] = 0x0e;
		mem_[0x000e] = 0x02;
		mem_[0x000f] = 0x01;
		mem_[0x0182] = 'A';
	}
}
