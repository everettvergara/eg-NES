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

	auto m6502_generic::test_loader() -> void
	{
		// LDA_IM
		// --

		//mem_[0xfffc] = LDA_IM;
		//mem_[0xfffd] = 'A';

		//mem_[0xfffc] = LDA_IM;
		//mem_[0xfffd] = -20;

		//mem_[0xfffc] = LDA_IM;
		//mem_[0xfffd] = 0;

		// LDA_ZP
		// --

		//mem_[0xfffc] = LDA_ZP;
		//mem_[0xfffd] = 0x00;
		//mem_[0x0000] = 'A';

		//mem_[0xfffc] = LDA_ZP;
		//mem_[0xfffd] = 0x00;
		//mem_[0x0000] = -20;

		//mem_[0xfffc] = LDA_ZP;
		//mem_[0xfffd] = 0x00;
		//mem_[0x0000] = 0;
	}
}
