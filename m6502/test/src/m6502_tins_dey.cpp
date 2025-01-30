#include "m6502_tins_dey.h"

namespace eg::m6502
{
	auto test_DEY_reg_check(const reg& r, byte val, word pc_add) -> bool
	{
		return
			(r.Y == val) and
			(r.SR.Z == (val == 0 ? 1 : 0)) and
			(r.SR.N == ((val & 0b10000000) > 0 ? 1 : 0)) and
			(r.PC == pc_add);
	}

	auto test_DEY_IMP(byte val) -> bool
	{
		m6502_generic cpu(TRESET_VECTOR_ADDRESS, TRESET_ROUTINE_ADDRESS);

		cpu.reset();

		mem data;
		data[TRESET_VECTOR_ADDRESS] = DEY_IMP;

		cpu.test_load_mem(std::move(data));
		cpu.test_load_reg_Y(val);
		cpu.exec();

		return test_DEY_reg_check(cpu.get_reg(), val - 1, TRESET_VECTOR_ADDRESS + 1);
	}

	auto test_DEY_IMP_nzero_nneg() -> bool { return test_DEY_IMP('B'); }
	auto test_DEY_IMP_zero_nneg() -> bool { return test_DEY_IMP(1); }
	auto test_DEY_IMP_nzero_neg() -> bool { return test_DEY_IMP(235); }
}
