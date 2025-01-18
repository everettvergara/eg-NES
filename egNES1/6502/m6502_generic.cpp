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

		// LDA_ZPX
		//reg_.X = 0x80;
		//mem_[reset_vector_addr_] = LDA_ZPX;
		//mem_[reset_vector_addr_ + 1] = 0x0f;
		//mem_[0x008f] = 'A';

		// LDA_ABS
		//mem_[reset_vector_addr_] = LDA_ABS;

		//// value: 257
		//mem_[reset_vector_addr_ + 1] = 0x02;
		//mem_[reset_vector_addr_ + 2] = 0x01;
		//mem_[0x0102] = 'A';

		// LDA_ABSX - no carry
		//reg_.X = 0x80;
		//mem_[reset_vector_addr_] = LDA_ABSX;
		//mem_[reset_vector_addr_ + 1] = 0x02;
		//mem_[reset_vector_addr_ + 2] = 0x01;
		//mem_[0x0182] = 'A';

		// LDA_ABSX - with carry
		//reg_.X = 0xff;
		//mem_[reset_vector_addr_] = LDA_ABSX;
		//mem_[reset_vector_addr_ + 1] = 0x02;
		//mem_[reset_vector_addr_ + 2] = 0x01;
		//mem_[0x0201] = 'A';

		// LDA_ABSy - no carry
		//reg_.Y = 0x80;
		//mem_[reset_vector_addr_] = LDA_ABSY;
		//mem_[reset_vector_addr_ + 1] = 0x02;
		//mem_[reset_vector_addr_ + 2] = 0x01;
		//mem_[0x0182] = 'A';

		//// LDA_ABSX - with carry
		//reg_.Y = 0xff;
		//mem_[reset_vector_addr_] = LDA_ABSY;
		//mem_[reset_vector_addr_ + 1] = 0x02;
		//mem_[reset_vector_addr_ + 2] = 0x01;
		//mem_[0x0201] = 'A';

		// LDA_INDX
		reg_.X = 0x80;
		mem_[reset_vector_addr_] = LDA_INDX;
		mem_[reset_vector_addr_ + 1] = 0x0f;
		mem_[0x008f] = 0x02;
		mem_[0x0090] = 0x01;
		mem_[0x0102] = 'A';
	}
}
