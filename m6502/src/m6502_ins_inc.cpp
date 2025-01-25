#include "m6502.h"
#include <cassert>

namespace eg::m6502
{
	auto m6502::exec_INC_ZP_() -> void
	{
		const byte badd = read_mem_by_bpc();
		byte value = read_mem_by_badd(badd);

		++value;
		cycles_.simulate();

		write_mem_by_badd(badd, value);
		set_ZN_(value);
	}
}
