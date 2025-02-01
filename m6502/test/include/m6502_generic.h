#pragma once

#include "m6502.h"

namespace eg::m6502
{
	class m6502_generic : public m6502
	{
	public:

		m6502_generic(word reset_vector_add, word reset_routine_addr, extra extra = {});
		auto reset() -> void final;

		auto test_loader() -> void;
		auto test_load_mem(mem m) -> void;
		auto test_load_reg_X(byte X) -> void;
		auto test_load_reg_Y(byte Y) -> void;
		auto test_load_rnd_reg() -> reg;
	};
}
