#include "m6502_tins_inc.h"

namespace eg::m6502
{
	auto test_DEC_cpu_check(const m6502_generic& cpu, word wadd, byte val, word pc_add) -> bool
	{
		const auto& t = cpu.get_reg();
		const auto& m = cpu.get_mem();

		return
			(m[wadd] == val) and
			(t.SR.Z == (val == 0 ? 1 : 0)) and
			(t.SR.N == ((val & 0b10000000) > 0 ? 1 : 0)) and
			(t.PC == pc_add);
	}

	auto test_DEC_ZP(byte val) -> bool
	{
		m6502_generic cpu(TRESET_VECTOR_ADDRESS, TRESET_ROUTINE_ADDRESS);

		cpu.reset();

		mem data;
		data[TRESET_VECTOR_ADDRESS] = DEC_ZP;

		byte baddr = 0x05;
		data[TRESET_VECTOR_ADDRESS + 1] = baddr;
		data[baddr] = val;

		cpu.test_load_mem(std::move(data));
		cpu.exec();

		return test_DEC_cpu_check(cpu, static_cast<word>(baddr), val - 1, TRESET_VECTOR_ADDRESS + 2);
	}

	auto test_DEC_ZPX(byte val, byte X) -> bool
	{
		m6502_generic cpu(TRESET_VECTOR_ADDRESS, TRESET_ROUTINE_ADDRESS);

		cpu.reset();

		mem data;

		data[TRESET_VECTOR_ADDRESS] = DEC_ZPX;

		const byte baddr = 0x05;
		const byte new_baddr = baddr + X;
		data[TRESET_VECTOR_ADDRESS + 1] = baddr;
		data[new_baddr] = val;

		cpu.test_load_mem(std::move(data));
		cpu.test_load_reg_X(X);
		cpu.exec();

		return test_DEC_cpu_check(cpu, static_cast<word>(new_baddr), val - 1, TRESET_VECTOR_ADDRESS + 2);
	}

	auto test_DEC_ABS(byte val) -> bool
	{
		m6502_generic cpu(TRESET_VECTOR_ADDRESS, TRESET_ROUTINE_ADDRESS);

		cpu.reset();

		mem data;

		data[TRESET_VECTOR_ADDRESS] = DEC_ABS;
		data[TRESET_VECTOR_ADDRESS + 1] = 0x02;
		data[TRESET_VECTOR_ADDRESS + 2] = 0x01;
		data[0x0102] = val;

		cpu.test_load_mem(std::move(data));
		cpu.exec();

		return test_DEC_cpu_check(cpu, 0x0102, val - 1, TRESET_VECTOR_ADDRESS + 3);
	}

	auto test_DEC_ABSX(byte val, byte X) -> bool
	{
		m6502_generic cpu(TRESET_VECTOR_ADDRESS, TRESET_ROUTINE_ADDRESS);

		cpu.reset();

		mem data;

		data[TRESET_VECTOR_ADDRESS] = DEC_ABSX;
		data[TRESET_VECTOR_ADDRESS + 1] = 0x02;
		data[TRESET_VECTOR_ADDRESS + 2] = 0x01;

		const word waddr = 0x0102 + X;

		data[waddr] = val;

		cpu.test_load_mem(std::move(data));
		cpu.test_load_reg_X(X);
		cpu.exec();

		return test_DEC_cpu_check(cpu, waddr, val - 1, TRESET_VECTOR_ADDRESS + 3);
	}

	auto test_DEC_ZP_nzero_nneg() -> bool { return test_DEC_ZP('B'); }
	auto test_DEC_ZP_zero_nneg() -> bool { return test_DEC_ZP(1); }
	auto test_DEC_ZP_nzero_neg() -> bool { return test_DEC_ZP(235); }
	auto test_DEC_ZPX_nzero_nneg_ncarry() -> bool { return test_DEC_ZPX('B', 0x80); }
	auto test_DEC_ZPX_zero_nneg_ncarry() -> bool { return test_DEC_ZPX(1, 0x80); }
	auto test_DEC_ZPX_nzero_neg_ncarry() -> bool { return test_DEC_ZPX(235, 0x80); }
	auto test_DEC_ZPX_nzero_nneg_carry() -> bool { return test_DEC_ZPX('B', 0xff); }
	auto test_DEC_ZPX_zero_nneg_carry() -> bool { return test_DEC_ZPX(1, 0xff); }
	auto test_DEC_ZPX_nzero_neg_carry() -> bool { return test_DEC_ZPX(235, 0xff); }
	auto test_DEC_ABS_nzero_nneg() -> bool { return test_DEC_ABS('B'); }
	auto test_DEC_ABS_zero_nneg() -> bool { return test_DEC_ABS(1); }
	auto test_DEC_ABS_nzero_neg() -> bool { return test_DEC_ABS(235); }
	auto test_DEC_ABSX_nzero_nneg_ncarry() -> bool { return test_DEC_ABSX('B', 0x80); }
	auto test_DEC_ABSX_zero_nneg_ncarry() -> bool { return test_DEC_ABSX(1, 0x80); }
	auto test_DEC_ABSX_nzero_neg_ncarry() -> bool { return test_DEC_ABSX(235, 0x80); }
	auto test_DEC_ABSX_nzero_nneg_carry() -> bool { return test_DEC_ABSX('B', 0xFF); }
	auto test_DEC_ABSX_zero_nneg_carry() -> bool { return test_DEC_ABSX(1, 0xff); }
	auto test_DEC_ABSX_nzero_neg_carry() -> bool { return test_DEC_ABSX(235, 0xff); }
}
