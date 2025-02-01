#include "m6502_tins_dex.h"

namespace eg::m6502
{
	auto test_JMP_reg_check(const reg& reg_orig, const reg& reg_new, word pc_add) -> bool
	{
		return reg_new.AC == reg_orig.AC and 
			reg_new.X == reg_orig.X and
			reg_new.Y == reg_orig.Y and
			reg_new.SP == reg_orig.SP and
			reg_new.SR.B == reg_orig.SR.B and
			reg_new.SR.C == reg_orig.SR.C and
			reg_new.SR.D == reg_orig.SR.D and
			reg_new.SR.I == reg_orig.SR.I and
			reg_new.SR.N == reg_orig.SR.N and
			reg_new.SR.V == reg_orig.SR.V and
			reg_new.SR.Z == reg_orig.SR.Z and
			reg_new.SR._ == reg_orig.SR._ and
			reg_new.PC == pc_add;
	}

	auto test_JMP_ABS(byte low_add, byte high_add) -> bool
	{
		m6502_generic cpu(TRESET_VECTOR_ADDRESS, TRESET_ROUTINE_ADDRESS);
		
		cpu.reset();
		mem data;
		
		data[TRESET_VECTOR_ADDRESS] = JMP_ABS;
		data[TRESET_VECTOR_ADDRESS + 1] = low_add;
		data[TRESET_VECTOR_ADDRESS + 2] = high_add;
		
		const auto full_add = (high_add << 8) | low_add;

		cpu.test_load_mem(std::move(data));
		const auto reg_orig = cpu.get_reg();
		cpu.exec();
		const auto reg_new = cpu.get_reg();

		return test_JMP_reg_check(reg_orig, reg_new, full_add);
	}

	auto test_JMP_IND(byte high_add) -> bool
	{
		extra xtra{ .has_JMP_IND_bug = false };
		m6502_generic cpu(TRESET_VECTOR_ADDRESS, TRESET_ROUTINE_ADDRESS, xtra);

		cpu.reset();
		mem data;

		const byte low_add = 0xff;
		data[TRESET_VECTOR_ADDRESS] = JMP_IND;
		data[TRESET_VECTOR_ADDRESS + 1] = low_add;
		data[TRESET_VECTOR_ADDRESS + 2] = high_add;

		const auto full_add = (high_add << 8) | low_add;
		data[full_add] = 0x50;
		data[full_add + 1] = 0x30;

		cpu.test_load_mem(std::move(data));
		const auto reg_orig = cpu.get_reg();
		cpu.exec();
		const auto reg_new = cpu.get_reg();

		return test_JMP_reg_check(reg_orig, reg_new, 0x3050);
	}

	auto test_JMP_IND_bug(byte high_add) -> bool
	{
		extra xtra{ .has_JMP_IND_bug = true };
		m6502_generic cpu(TRESET_VECTOR_ADDRESS, TRESET_ROUTINE_ADDRESS, xtra);

		cpu.reset();
		mem data;

		const byte low_add = 0xff;
		data[TRESET_VECTOR_ADDRESS] = JMP_IND;
		data[TRESET_VECTOR_ADDRESS + 1] = low_add;
		data[TRESET_VECTOR_ADDRESS + 2] = high_add;

		const auto full_add = (high_add << 8) | low_add;
		data[full_add] = 0x50;
		data[full_add + 1] = 0x30;
		data[(high_add << 8 | 0x00)] = 0x20;

		cpu.test_load_mem(std::move(data));
		const auto reg_orig = cpu.get_reg();
		cpu.exec();
		const auto reg_new = cpu.get_reg();

		return test_JMP_reg_check(reg_orig, reg_new, 0x2050);
	}
}
