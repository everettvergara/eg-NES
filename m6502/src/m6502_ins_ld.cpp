#include "m6502.h"
#include <cassert>

namespace eg::m6502
{
	auto m6502::exec_LD_set_ZN_(byte value) -> void
	{
		reg_.SR.Z = (value == 0);
		reg_.SR.N = (value & 0b10000000) > 0;
	}
}
