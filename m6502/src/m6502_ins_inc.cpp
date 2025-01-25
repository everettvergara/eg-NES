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

	auto m6502::exec_INC_ZPX_() -> void
	{
		const byte badd = read_mem_by_bpc() + reg_.X;
		cycles_.simulate(); // For adding X

		byte value = read_mem_by_badd(badd);

		++value;
		cycles_.simulate();

		write_mem_by_badd(badd, value);
		set_ZN_(value);
	}

	auto m6502::exec_INC_ABS_() -> void
	{
		// 1 Cycle - ins
		const word wadd = read_mem_by_wpc(); // 2
		byte value = read_mem_by_wadd(wadd); // 1

		++value;
		cycles_.simulate();	// 1

		write_mem_by_wadd(wadd, value); // 1
		set_ZN_(value);
	}

	auto m6502::exec_INC_ABSX_() -> void
	{
		// 1 Cycle - ins
		const word wadd = read_mem_by_wpc() + reg_.X; // 3
		cycles_.simulate();	// for adding x

		byte value = read_mem_by_wadd(wadd); // 1

		++value;
		cycles_.simulate();	// 1

		write_mem_by_wadd(wadd, value); // 1
		set_ZN_(value);
	}
}
