#include "m6502_ins_ldy.h"
#include "m6502_tester.h"

namespace eg::m6502
{
	auto test_LDY_reg_check(const reg& t, byte val, word pc_add) -> bool
	{
		return (t.Y == val) and
			(t.SR.Z == (val == 0 ? 1 : 0)) and
			(t.SR.N == ((val & 0b10000000) > 0 ? 1 : 0)) and
			(t.PC == pc_add);
	}

	auto test_LDY_IM(byte val) -> bool
	{
		m6502_generic cpu(RESET_VECTOR_ADDRESS, RESET_ROUTINE_ADDRESS);

		cpu.reset();

		mem data;
		data[RESET_VECTOR_ADDRESS] = LDY_IM;
		data[RESET_VECTOR_ADDRESS + 1] = val;

		cpu.test_load_mem(std::move(data));
		cpu.exec();

		return test_LDY_reg_check(cpu.get_reg(), val, RESET_VECTOR_ADDRESS + 2);
	}

	auto test_LDY_ZP(byte val) -> bool
	{
		m6502_generic cpu(RESET_VECTOR_ADDRESS, RESET_ROUTINE_ADDRESS);

		cpu.reset();

		mem data;
		data[RESET_VECTOR_ADDRESS] = LDY_ZP;
		data[RESET_VECTOR_ADDRESS + 1] = 0x05;
		data[0x0005] = val;

		cpu.test_load_mem(std::move(data));
		cpu.exec();

		return test_LDY_reg_check(cpu.get_reg(), val, RESET_VECTOR_ADDRESS + 2);
	}

	auto test_LDY_ZPX(byte val) -> bool
	{
		m6502_generic cpu(RESET_VECTOR_ADDRESS, RESET_ROUTINE_ADDRESS);

		cpu.reset();

		mem data;

		data[RESET_VECTOR_ADDRESS] = LDY_ZPX;
		data[RESET_VECTOR_ADDRESS + 1] = 0x05;
		data[0x00f5] = val;

		cpu.test_load_mem(std::move(data));
		cpu.test_load_reg_X(0xf0);
		cpu.exec();

		return test_LDY_reg_check(cpu.get_reg(), val, RESET_VECTOR_ADDRESS + 2);
	}

	auto test_LDY_ABS(byte val) -> bool
	{
		m6502_generic cpu(RESET_VECTOR_ADDRESS, RESET_ROUTINE_ADDRESS);

		cpu.reset();

		mem data;

		data[RESET_VECTOR_ADDRESS] = LDY_ABS;
		data[RESET_VECTOR_ADDRESS + 1] = 0x02;
		data[RESET_VECTOR_ADDRESS + 2] = 0x01;
		data[0x0102] = val;

		cpu.test_load_mem(std::move(data));
		cpu.exec();

		return test_LDY_reg_check(cpu.get_reg(), val, RESET_VECTOR_ADDRESS + 3);
	}

	auto test_LDY_ABSX(byte val, byte X) -> bool
	{
		m6502_generic cpu(RESET_VECTOR_ADDRESS, RESET_ROUTINE_ADDRESS);

		cpu.reset();

		mem data;

		data[RESET_VECTOR_ADDRESS] = LDY_ABSX;
		data[RESET_VECTOR_ADDRESS + 1] = 0x02;
		data[RESET_VECTOR_ADDRESS + 2] = 0x01;

		//const byte baddr = (0x02 + Y);		// truncate to byte
		const word waddr = 0x0102 + X;

		data[waddr] = val;

		cpu.test_load_mem(std::move(data));
		cpu.test_load_reg_X(X);
		cpu.exec();

		return test_LDY_reg_check(cpu.get_reg(), val, RESET_VECTOR_ADDRESS + 3);
	}

	auto test_LDY_IM_nzero_nneg() -> bool { return test_LDY_IM('A'); }
	auto test_LDY_IM_zero_nneg() -> bool { return test_LDY_IM(0); }
	auto test_LDY_IM_nzero_neg() -> bool { return test_LDY_IM(235); }
	auto test_LDY_ZP_nzero_nneg() -> bool { return test_LDY_ZP('A'); }
	auto test_LDY_ZP_zero_nneg() -> bool { return test_LDY_ZP(0); }
	auto test_LDY_ZP_nzero_neg() -> bool { return test_LDY_ZP(235); }
	auto test_LDY_ZPX_nzero_nneg() -> bool { return test_LDY_ZPX('A'); }
	auto test_LDY_ZPX_zero_nneg() -> bool { return test_LDY_ZPX(0); }
	auto test_LDY_ZPX_nzero_neg() -> bool { return test_LDY_ZPX(235); }
	auto test_LDY_ABS_nzero_nneg() -> bool { return test_LDY_ABS('A'); }
	auto test_LDY_ABS_zero_nneg() -> bool { return test_LDY_ABS(0); }
	auto test_LDY_ABS_nzero_neg() -> bool { return test_LDY_ABS(235); }
	auto test_LDY_ABSX_nzero_nneg_ncarry() -> bool { return test_LDY_ABSX('A', 0x80); }
	auto test_LDY_ABSX_zero_nneg_ncarry() -> bool { return test_LDY_ABSX(0, 0x80); }
	auto test_LDY_ABSX_nzero_neg_ncarry() -> bool { return test_LDY_ABSX(235, 0x80); }
	auto test_LDY_ABSX_nzero_nneg_carry() -> bool { return test_LDY_ABSX('A', 0xff); }
	auto test_LDY_ABSX_zero_nneg_carry() -> bool { return test_LDY_ABSX(0, 0xff); }
	auto test_LDY_ABSX_nzero_neg_carry() -> bool { return test_LDY_ABSX(235, 0xff); }
}
