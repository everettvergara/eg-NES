#include "m6502_ins_lda.h"
#include "m6502_generic.h"

namespace eg::m6502
{
	auto test_LDA_reg_check(const reg& t, byte val) -> bool
	{
		return t.AC == val and
			t.SR.Z == (val == 0 ? 1 : 0) and
			t.SR.N == (val & 0b10000000) > 0 ? 1 : 0;
	}

	auto test_LDA_IM(byte val) -> bool
	{
		m6502_generic cpu(RESET_VECTOR_ADDRESS, RESET_ROUTINE_ADDRESS);

		cpu.reset();

		mem data;
		data[RESET_VECTOR_ADDRESS] = LDA_IM;
		data[RESET_VECTOR_ADDRESS + 1] = val;

		cpu.test_load_mem(std::move(data));
		cpu.exec();

		return test_LDA_reg_check(cpu.get_reg(), val);
	}

	auto test_LDA_ZP(byte val) -> bool
	{
		m6502_generic cpu(RESET_VECTOR_ADDRESS, RESET_ROUTINE_ADDRESS);

		cpu.reset();

		mem data;
		data[RESET_VECTOR_ADDRESS] = LDA_ZP;
		data[RESET_VECTOR_ADDRESS + 1] = 0x05;
		data[0x0005] = val;

		cpu.test_load_mem(std::move(data));
		cpu.exec();

		return test_LDA_reg_check(cpu.get_reg(), val);
	}

	auto test_LDA_ZPX(byte val) -> bool
	{
		m6502_generic cpu(RESET_VECTOR_ADDRESS, RESET_ROUTINE_ADDRESS);

		cpu.reset();

		mem data;

		data[RESET_VECTOR_ADDRESS] = LDA_ZPX;
		data[RESET_VECTOR_ADDRESS + 1] = 0x05;
		data[0x00f5] = val;

		cpu.test_load_mem(std::move(data));
		cpu.test_load_reg_X(0xf0);
		cpu.exec();

		return test_LDA_reg_check(cpu.get_reg(), val);
	}

	auto test_LDA_ABS(byte val) -> bool
	{
		m6502_generic cpu(RESET_VECTOR_ADDRESS, RESET_ROUTINE_ADDRESS);

		cpu.reset();

		mem data;

		data[RESET_VECTOR_ADDRESS] = LDA_ABS;
		data[RESET_VECTOR_ADDRESS + 1] = 0x02;
		data[RESET_VECTOR_ADDRESS + 2] = 0x01;
		data[0x0102] = val;

		cpu.test_load_mem(std::move(data));
		cpu.exec();

		return test_LDA_reg_check(cpu.get_reg(), val);
	}

	auto test_LDA_IM_nzero_nneg() -> bool { return test_LDA_IM('A'); }
	auto test_LDA_IM_zero_nneg() -> bool { return test_LDA_IM(0); }
	auto test_LDA_IM_nzero_neg() -> bool { return test_LDA_IM(235); }
	auto test_LDA_ZP_nzero_nneg() -> bool { return test_LDA_ZP('A'); }
	auto test_LDA_ZP_zero_nneg() -> bool { return test_LDA_ZP(0); }
	auto test_LDA_ZP_nzero_neg() -> bool { return test_LDA_ZP(235); }
	auto test_LDA_ZPX_nzero_nneg() -> bool { return test_LDA_ZPX('A'); }
	auto test_LDA_ZPX_zero_nneg() -> bool { return test_LDA_ZPX(0); }
	auto test_LDA_ZPX_nzero_neg() -> bool { return test_LDA_ZPX(235); }
	auto test_LDA_ABS_nzero_nneg() -> bool { return test_LDA_ABS('A'); }
	auto test_LDA_ABS_zero_nneg() -> bool { return test_LDA_ABS(0); }
	auto test_LDA_ABS_nzero_neg() -> bool { return test_LDA_ABS(235); }
}
