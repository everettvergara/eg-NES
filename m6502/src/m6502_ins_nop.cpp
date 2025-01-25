#include "m6502.h"
#include <cassert>

namespace eg::m6502
{
	auto m6502::exec_NOP_IMP_() -> void
	{
		cycles_.simulate();
	}
}
