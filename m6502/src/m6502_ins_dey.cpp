#include "m6502.h" 

namespace eg::m6502
{
	auto m6502::exec_DEY_IMP_() -> void
	{
		--reg_.Y;
		cycles_.simulate();

		set_ZN_(reg_.Y);
	}
}