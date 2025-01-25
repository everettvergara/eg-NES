#include "m6502_ins_ldx.h"
#include "m6502_tester.h"

namespace eg::m6502
{
	auto test_LDX_reg_check(const reg& t, byte val, word pc_add) -> bool
	{
		return (t.X == val) and
			(t.SR.Z == (val == 0 ? 1 : 0)) and
			(t.SR.N == ((val & 0b10000000) > 0 ? 1 : 0)) and
			(t.PC == pc_add);
	}

	auto test_LDX_IM(byte val) -> bool
	{
		m6502_generic cpu(RESET_VECTOR_ADDRESS, RESET_ROUTINE_ADDRESS);

		cpu.reset();

		mem data;
		data[RESET_VECTOR_ADDRESS] = LDX_IM;
		data[RESET_VECTOR_ADDRESS + 1] = val;

		cpu.test_load_mem(std::move(data));
		cpu.exec();

		return test_LDX_reg_check(cpu.get_reg(), val, RESET_VECTOR_ADDRESS + 2);
	}

	auto test_LDX_ZP(byte val) -> bool
	{
		m6502_generic cpu(RESET_VECTOR_ADDRESS, RESET_ROUTINE_ADDRESS);

		cpu.reset();

		mem data;
		data[RESET_VECTOR_ADDRESS] = LDX_ZP;
		data[RESET_VECTOR_ADDRESS + 1] = 0x05;
		data[0x0005] = val;

		cpu.test_load_mem(std::move(data));
		cpu.exec();

		return test_LDX_reg_check(cpu.get_reg(), val, RESET_VECTOR_ADDRESS + 2);
	}

	auto test_LDX_ZPY(byte val) -> bool
	{
		m6502_generic cpu(RESET_VECTOR_ADDRESS, RESET_ROUTINE_ADDRESS);

		cpu.reset();

		mem data;

		data[RESET_VECTOR_ADDRESS] = LDX_ZPY;
		data[RESET_VECTOR_ADDRESS + 1] = 0x05;
		data[0x00f5] = val;

		cpu.test_load_mem(std::move(data));
		cpu.test_load_reg_Y(0xf0);
		cpu.exec();

		return test_LDX_reg_check(cpu.get_reg(), val, RESET_VECTOR_ADDRESS + 2);
	}

	auto test_LDX_ABS(byte val) -> bool
	{
		m6502_generic cpu(RESET_VECTOR_ADDRESS, RESET_ROUTINE_ADDRESS);

		cpu.reset();

		mem data;

		data[RESET_VECTOR_ADDRESS] = LDX_ABS;
		data[RESET_VECTOR_ADDRESS + 1] = 0x02;
		data[RESET_VECTOR_ADDRESS + 2] = 0x01;
		data[0x0102] = val;

		cpu.test_load_mem(std::move(data));
		cpu.exec();

		return test_LDX_reg_check(cpu.get_reg(), val, RESET_VECTOR_ADDRESS + 3);
	}

	auto test_LDX_ABSY(byte val, byte Y) -> bool
	{
		m6502_generic cpu(RESET_VECTOR_ADDRESS, RESET_ROUTINE_ADDRESS);

		cpu.reset();

		mem data;

		data[RESET_VECTOR_ADDRESS] = LDX_ABSY;
		data[RESET_VECTOR_ADDRESS + 1] = 0x02;
		data[RESET_VECTOR_ADDRESS + 2] = 0x01;

		//const byte baddr = (0x02 + Y);		// truncate to byte
		const word waddr = 0x0102 + Y;

		data[waddr] = val;

		cpu.test_load_mem(std::move(data));
		cpu.test_load_reg_Y(Y);
		cpu.exec();

		return test_LDX_reg_check(cpu.get_reg(), val, RESET_VECTOR_ADDRESS + 3);
	}

	auto test_LDX_IM_nzero_nneg() -> bool { return test_LDX_IM('A'); }
	auto test_LDX_IM_zero_nneg() -> bool { return test_LDX_IM(0); }
	auto test_LDX_IM_nzero_neg() -> bool { return test_LDX_IM(235); }
	auto test_LDX_ZP_nzero_nneg() -> bool { return test_LDX_ZP('A'); }
	auto test_LDX_ZP_zero_nneg() -> bool { return test_LDX_ZP(0); }
	auto test_LDX_ZP_nzero_neg() -> bool { return test_LDX_ZP(235); }
	auto test_LDX_ZPY_nzero_nneg() -> bool { return test_LDX_ZPY('A'); }
	auto test_LDX_ZPY_zero_nneg() -> bool { return test_LDX_ZPY(0); }
	auto test_LDX_ZPY_nzero_neg() -> bool { return test_LDX_ZPY(235); }
	auto test_LDX_ABS_nzero_nneg() -> bool { return test_LDX_ABS('A'); }
	auto test_LDX_ABS_zero_nneg() -> bool { return test_LDX_ABS(0); }
	auto test_LDX_ABS_nzero_neg() -> bool { return test_LDX_ABS(235); }
	auto test_LDX_ABSY_nzero_nneg_ncarry() -> bool { return test_LDX_ABSY('A', 0x80); }
	auto test_LDX_ABSY_zero_nneg_ncarry() -> bool { return test_LDX_ABSY(0, 0x80); }
	auto test_LDX_ABSY_nzero_neg_ncarry() -> bool { return test_LDX_ABSY(235, 0x80); }
	auto test_LDX_ABSY_nzero_nneg_carry() -> bool { return test_LDX_ABSY('A', 0xff); }
	auto test_LDX_ABSY_zero_nneg_carry() -> bool { return test_LDX_ABSY(0, 0xff); }
	auto test_LDX_ABSY_nzero_neg_carry() -> bool { return test_LDX_ABSY(235, 0xff); }
}
