#include "m6502_ins_lda.h"
#include "m6502_generic.h"

namespace eg::m6502
{
	auto test_LDA_IM_nzero_nneg() -> bool
	{
		m6502_generic cpu(RESET_VECTOR_ADDRESS, RESET_ROUTINE_ADDRESS);

		cpu.reset();

		mem data;
		data[RESET_VECTOR_ADDRESS] = LDA_IM;
		data[RESET_VECTOR_ADDRESS + 1] = 'A';

		cpu.test_load_mem(std::move(data));
		cpu.exec();

		if (const reg t = cpu.get_reg();

			t.AC == 'A' and
			t.SR.Z == 0 and
			t.SR.N == 0)
		{
			return true;
		}

		return false;
	}

	auto test_LDA_IM_zero_nneg() -> bool
	{
		m6502_generic cpu(RESET_VECTOR_ADDRESS, RESET_ROUTINE_ADDRESS);

		cpu.reset();

		mem data;
		data[RESET_VECTOR_ADDRESS] = LDA_IM;
		data[RESET_VECTOR_ADDRESS + 1] = 0;

		cpu.test_load_mem(std::move(data));
		cpu.exec();

		if (const reg t = cpu.get_reg();

			t.AC == 0 and
			t.SR.Z == 1 and
			t.SR.N == 0)
		{
			return true;
		}

		return false;
	}

	auto test_LDA_IM_nzero_neg() -> bool
	{
		m6502_generic cpu(RESET_VECTOR_ADDRESS, RESET_ROUTINE_ADDRESS);
		cpu.reset();

		mem data;
		data[RESET_VECTOR_ADDRESS] = LDA_IM;
		data[RESET_VECTOR_ADDRESS + 1] = 235;

		cpu.test_load_mem(std::move(data));
		cpu.exec();

		if (const reg t = cpu.get_reg();
			t.AC == 235 and
			t.SR.Z == 0 and
			t.SR.N == 1)
		{
			return true;
		}

		return false;
	}

	auto test_LDA_ZP_nzero_nneg() -> bool
	{
		m6502_generic cpu(RESET_VECTOR_ADDRESS, RESET_ROUTINE_ADDRESS);

		cpu.reset();

		mem data;
		data[RESET_VECTOR_ADDRESS] = LDA_ZP;
		data[RESET_VECTOR_ADDRESS + 1] = 0x05;
		data[0x0005] = 'A';

		cpu.test_load_mem(std::move(data));
		cpu.exec();

		if (const reg t = cpu.get_reg();

			t.AC == 'A' and
			t.SR.Z == 0 and
			t.SR.N == 0)
		{
			return true;
		}

		return false;
	}

	auto test_LDA_ZP_zero_nneg() -> bool
	{
		m6502_generic cpu(RESET_VECTOR_ADDRESS, RESET_ROUTINE_ADDRESS);

		cpu.reset();

		mem data;
		data[RESET_VECTOR_ADDRESS] = LDA_ZP;
		data[RESET_VECTOR_ADDRESS + 1] = 0x05;
		data[0x0005] = 0;

		cpu.test_load_mem(std::move(data));
		cpu.exec();

		if (const reg t = cpu.get_reg();

			t.AC == 0 and
			t.SR.Z == 1 and
			t.SR.N == 0)
		{
			return true;
		}

		return false;
	}

	auto test_LDA_ZP_nzero_neg() -> bool
	{
		m6502_generic cpu(RESET_VECTOR_ADDRESS, RESET_ROUTINE_ADDRESS);
		cpu.reset();

		mem data;
		data[RESET_VECTOR_ADDRESS] = LDA_ZP;
		data[RESET_VECTOR_ADDRESS + 1] = 0x05;
		data[0x0005] = 235;

		cpu.test_load_mem(std::move(data));
		cpu.exec();

		if (const reg t = cpu.get_reg();
			t.AC == 235 and
			t.SR.Z == 0 and
			t.SR.N == 1)
		{
			return true;
		}

		return false;
	}

	auto test_LDA_ZPX_nzero_nneg() -> bool
	{
		m6502_generic cpu(RESET_VECTOR_ADDRESS, RESET_ROUTINE_ADDRESS);

		cpu.reset();

		mem data;

		data[RESET_VECTOR_ADDRESS] = LDA_ZPX;
		data[RESET_VECTOR_ADDRESS + 1] = 0x05;
		data[0x00f5] = 'A';

		cpu.test_load_mem(std::move(data));
		cpu.test_load_reg_X(0xf0);
		cpu.exec();

		if (const reg t = cpu.get_reg();

			t.AC == 'A' and
			t.SR.Z == 0 and
			t.SR.N == 0)
		{
			return true;
		}

		return false;
	}

	auto test_LDA_ZPX_zero_nneg() -> bool
	{
		m6502_generic cpu(RESET_VECTOR_ADDRESS, RESET_ROUTINE_ADDRESS);

		cpu.reset();

		mem data;

		data[RESET_VECTOR_ADDRESS] = LDA_ZPX;
		data[RESET_VECTOR_ADDRESS + 1] = 0x05;
		data[0x00f5] = 0;

		cpu.test_load_mem(std::move(data));
		cpu.test_load_reg_X(0xf0);
		cpu.exec();

		if (const reg t = cpu.get_reg();

			t.AC == 0 and
			t.SR.Z == 1 and
			t.SR.N == 0)
		{
			return true;
		}

		return false;
	}

	auto test_LDA_ZPX_nzero_neg() -> bool
	{
		m6502_generic cpu(RESET_VECTOR_ADDRESS, RESET_ROUTINE_ADDRESS);
		cpu.reset();

		mem data;

		data[RESET_VECTOR_ADDRESS] = LDA_ZPX;
		data[RESET_VECTOR_ADDRESS + 1] = 0x05;
		data[0x00f5] = 235;

		cpu.test_load_mem(std::move(data));
		cpu.test_load_reg_X(0xf0);
		cpu.exec();

		if (const reg t = cpu.get_reg();
			t.AC == 235 and
			t.SR.Z == 0 and
			t.SR.N == 1)
		{
			return true;
		}

		return false;
	}
}
