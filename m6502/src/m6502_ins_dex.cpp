#include "m6502.h" 

namespace eg::m6502
{

	auto m6502::exec_DEX_IMP_() -> void
	{
		--reg_.X;
		cycles_.simulate();

		set_ZN_(reg_.X);
	}
}