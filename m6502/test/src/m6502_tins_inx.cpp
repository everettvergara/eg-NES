#include "m6502_tins_inx.h"

namespace eg::m6502
{
	auto test_INX_reg_check(const reg& r, byte val, word pc_add) -> bool
	{
		return
			(r.X == val) and
			(r.SR.Z == (val == 0 ? 1 : 0)) and
			(r.SR.N == ((val & 0b10000000) > 0 ? 1 : 0)) and
			(r.PC == pc_add);
	}

	auto test_INX_IMP(byte val) -> bool
	{
		m6502_generic cpu(TRESET_VECTOR_ADDRESS, TRESET_ROUTINE_ADDRESS);

		cpu.reset();

		mem data;
		data[TRESET_VECTOR_ADDRESS] = INX_IMP;

		cpu.test_load_mem(std::move(data));
		cpu.test_load_reg_X(val);
		cpu.exec();

		return test_INX_reg_check(cpu.get_reg(), val + 1, TRESET_VECTOR_ADDRESS + 1);
	}

	auto test_INX_IMP_nzero_nneg() -> bool { return test_INX_IMP('A'); }
	auto test_INX_IMP_zero_nneg() -> bool { return test_INX_IMP(255); }
	auto test_INX_IMP_nzero_neg() -> bool { return test_INX_IMP(235); }
}
