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
	}
}
