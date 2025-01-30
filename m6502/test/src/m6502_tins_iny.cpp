#include "m6502_tins_iny.h"

namespace eg::m6502
{
	auto test_INY_reg_check(const reg& r, byte val, word pc_add) -> bool
	{
		return
			(r.Y == val) and
			(r.SR.Z == (val == 0 ? 1 : 0)) and
			(r.SR.N == ((val & 0b10000000) > 0 ? 1 : 0)) and
			(r.PC == pc_add);
	}

	auto test_INY_IMP(byte val) -> bool
	{
		m6502_generic cpu(TRESET_VECTOR_ADDRESS, TRESET_ROUTINE_ADDRESS);

		cpu.reset();

		mem data;
		data[TRESET_VECTOR_ADDRESS] = INY_IMP;

		cpu.test_load_mem(std::move(data));
		cpu.test_load_reg_Y(val);
		cpu.exec();

		return test_INY_reg_check(cpu.get_reg(), val + 1, TRESET_VECTOR_ADDRESS + 1);
	}

	auto test_INY_IMP_nzero_nneg() -> bool { return test_INY_IMP('A'); }
	auto test_INY_IMP_zero_nneg() -> bool { return test_INY_IMP(255); }
	auto test_INY_IMP_nzero_neg() -> bool { return test_INY_IMP(235); }
}
