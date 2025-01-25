#include "m6502_ins_lda.h"
#include "m6502_tester.h"

namespace eg::m6502
{
	auto test_LDA_reg_check(const reg& t, byte val) -> bool
	{
		auto r = (t.AC == val) and
			(t.SR.Z == (val == 0 ? 1 : 0)) and
			(t.SR.N == ((val & 0b10000000) > 0 ? 1 : 0));
		return r;
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

	auto test_LDA_ABSX(byte val, byte X) -> bool
	{
		m6502_generic cpu(RESET_VECTOR_ADDRESS, RESET_ROUTINE_ADDRESS);

		cpu.reset();

		mem data;

		data[RESET_VECTOR_ADDRESS] = LDA_ABSX;
		data[RESET_VECTOR_ADDRESS + 1] = 0x02;
		data[RESET_VECTOR_ADDRESS + 2] = 0x01;

		//const byte baddr = (0x02 + X);
		const word waddr = 0x0102 + X;

		data[waddr] = val;

		cpu.test_load_mem(std::move(data));
		cpu.test_load_reg_X(X);
		cpu.exec();

		return test_LDA_reg_check(cpu.get_reg(), val);
	}

	auto test_LDA_ABSY(byte val, byte Y) -> bool
	{
		m6502_generic cpu(RESET_VECTOR_ADDRESS, RESET_ROUTINE_ADDRESS);

		cpu.reset();

		mem data;

		data[RESET_VECTOR_ADDRESS] = LDA_ABSY;
		data[RESET_VECTOR_ADDRESS + 1] = 0x02;
		data[RESET_VECTOR_ADDRESS + 2] = 0x01;

		//const byte baddr = (0x02 + Y);		// truncate to byte
		const word waddr = 0x0102 + Y;

		data[waddr] = val;

		cpu.test_load_mem(std::move(data));
		cpu.test_load_reg_Y(Y);
		cpu.exec();

		return test_LDA_reg_check(cpu.get_reg(), val);
	}

	auto test_LDA_INDX(byte val, byte X) -> bool
	{
		m6502_generic cpu(RESET_VECTOR_ADDRESS, RESET_ROUTINE_ADDRESS);

		cpu.reset();

		mem data;

		data[RESET_VECTOR_ADDRESS] = LDA_INDX;
		data[RESET_VECTOR_ADDRESS + 1] = 0x01;

		const byte baddr = (0x01 + X);		// truncate to byte
		const word waddr = 0x0000 + baddr;

		data[waddr] = 0x02;
		data[waddr + 1] = 0x01;
		data[0x0102] = val;

		cpu.test_load_mem(std::move(data));
		cpu.test_load_reg_X(X);
		cpu.exec();

		return test_LDA_reg_check(cpu.get_reg(), val);
	}

	auto test_LDA_INDY(byte val, byte Y) -> bool
	{
		m6502_generic cpu(RESET_VECTOR_ADDRESS, RESET_ROUTINE_ADDRESS);

		cpu.reset();

		mem data;

		data[RESET_VECTOR_ADDRESS] = LDA_INDY;
		data[RESET_VECTOR_ADDRESS + 1] = 0x0e;
		data[0x000e] = 0x02;
		data[0x000f] = 0x01;

		const word waddr = 0x0100 + 0x0002 + Y;

		data[waddr] = val;

		cpu.test_load_mem(std::move(data));
		cpu.test_load_reg_Y(Y);
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
	auto test_LDA_ABSX_nzero_nneg_ncarry() -> bool { return test_LDA_ABSX('A', 0x80); }
	auto test_LDA_ABSX_zero_nneg_ncarry() -> bool { return test_LDA_ABSX(0, 0x80); }
	auto test_LDA_ABSX_nzero_neg_ncarry() -> bool { return test_LDA_ABSX(235, 0x80); }
	auto test_LDA_ABSX_nzero_nneg_carry() -> bool { return test_LDA_ABSX('A', 0xff); }
	auto test_LDA_ABSX_zero_nneg_carry() -> bool { return test_LDA_ABSX(0, 0xff); }
	auto test_LDA_ABSX_nzero_neg_carry() -> bool { return test_LDA_ABSX(235, 0xff); }
	auto test_LDA_ABSY_nzero_nneg_ncarry() -> bool { return test_LDA_ABSY('A', 0x80); }
	auto test_LDA_ABSY_zero_nneg_ncarry() -> bool { return test_LDA_ABSY(0, 0x80); }
	auto test_LDA_ABSY_nzero_neg_ncarry() -> bool { return test_LDA_ABSY(235, 0x80); }
	auto test_LDA_ABSY_nzero_nneg_carry() -> bool { return test_LDA_ABSY('A', 0xff); }
	auto test_LDA_ABSY_zero_nneg_carry() -> bool { return test_LDA_ABSY(0, 0xff); }
	auto test_LDA_ABSY_nzero_neg_carry() -> bool { return test_LDA_ABSY(235, 0xff); }
	auto test_LDA_INDX_nzero_nneg_ncarry() -> bool { return test_LDA_INDX('A', 0x80); }
	auto test_LDA_INDX_zero_nneg_ncarry() -> bool { return test_LDA_INDX(0, 0x80); }
	auto test_LDA_INDX_nzero_neg_ncarry() -> bool { return test_LDA_INDX(235, 0x80); }
	auto test_LDA_INDX_nzero_nneg_carry() -> bool { return test_LDA_INDX('A', 0xff); }
	auto test_LDA_INDX_zero_nneg_carry() -> bool { return test_LDA_INDX(0, 0xff); }
	auto test_LDA_INDX_nzero_neg_carry() -> bool { return test_LDA_INDX(235, 0xff); }
	auto test_LDA_INDY_nzero_nneg_ncarry() -> bool { return test_LDA_INDY('A', 0x80); }
	auto test_LDA_INDY_zero_nneg_ncarry() -> bool { return test_LDA_INDY(0, 0x80); }
	auto test_LDA_INDY_nzero_neg_ncarry() -> bool { return test_LDA_INDY(235, 0x80); }
	auto test_LDA_INDY_nzero_nneg_carry() -> bool { return test_LDA_INDY('A', 0xff); }
	auto test_LDA_INDY_zero_nneg_carry() -> bool { return test_LDA_INDY(0, 0xff); }
	auto test_LDA_INDY_nzero_neg_carry() -> bool { return test_LDA_INDY(235, 0xff); }
}
