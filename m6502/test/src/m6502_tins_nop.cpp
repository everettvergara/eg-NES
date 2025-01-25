#include "m6502_tins_nop.h"
#include "m6502_generic.h"

namespace eg::m6502
{
	auto test_NOP_IMP() -> bool
	{
		m6502_generic cpu(TRESET_VECTOR_ADDRESS, TRESET_ROUTINE_ADDRESS);

		cpu.reset();

		mem data;
		data[TRESET_VECTOR_ADDRESS] = NOP_IMP;

		const auto t = cpu.test_load_rnd_reg();
		cpu.test_load_mem(std::move(data));
		cpu.exec();
		const auto n = cpu.get_reg();

		return (n.PC == TRESET_VECTOR_ADDRESS + 1) and
			(t.AC == n.AC) and
			(t.X == n.X) and
			(t.Y == n.Y) and
			(t.SP == n.SP) and
			(t.SR.B == n.SR.B) and
			(t.SR.C == n.SR.C) and
			(t.SR.D == n.SR.D) and
			(t.SR.I == n.SR.I) and
			(t.SR.N == n.SR.N) and
			(t.SR.V == n.SR.V) and
			(t.SR.Z == n.SR.Z) and
			(t.SR._ == n.SR._);
	}
}
