#pragma once

#include "m6502.h"

namespace eg::m6502
{
	class m6502_generic : public m6502
	{
	public:

		m6502_generic(word reset_vector_add, word reset_routine_addr);
		auto reset() -> void final;
	};
}
