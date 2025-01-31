#include "m6502.h" 

namespace eg::m6502
{
	auto m6502::exec_JMP_ABS_() -> void
	{
		const word address = read_mem_by_wpc();

		reg_.PC = address;
		cycles_.simulate();
	}

	auto m6502::exec_JMP_IND_() -> void
	{
		const word iaddress = read_mem_by_wpc();
		word address = read_mem_by_wadd(iaddress);

		if (reg_.has_JMP_IND_bug and (iaddress & 0x00ff) == 0x00ff)
		{
			address = read_mem_by_wadd(iaddress & 0xff00);
		}
		else
		{
			address = read_mem_by_wadd(iaddress);
		}

		reg_.PC = address;
		cycles_.simulate();
	}
}