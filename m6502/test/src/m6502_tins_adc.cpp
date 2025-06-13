#include "m6502_tins_dex.h"

namespace eg::m6502
{

	auto test_ADC_reg_check(const reg& r, byte A, byte val, bool carry, word pc_add, bool expected_C, bool expected_V) -> bool
	{
		const word result = A + val + (carry ? 1 : 0);
		const byte byte_result = static_cast<byte>(result);
		const bool C = result > 0xff;
		const bool V = (~(A ^ val) & (A ^ byte_result) & 0x80) > 0;

		return
			(r.AC == byte_result) and
			(r.SR.C == C) and
			(r.SR.V == V) and

			(r.SR.C == expected_C) and // Manual/Double check. Can be removed if the above fomula is confirmed
			(r.SR.V == expected_V) and // Manual/Double check. Can be removed if the above fomula is confirmed

			(r.SR.Z == (byte_result == 0 ? 1 : 0)) and
			(r.SR.N == ((byte_result & 0b10000000) > 0 ? 1 : 0)) and
			(r.PC == pc_add);
	}

	auto test_ADC_IM(byte A, byte val, bool carry, bool expected_C, bool expected_V) -> bool
	{
		m6502_generic cpu(TRESET_VECTOR_ADDRESS, TRESET_ROUTINE_ADDRESS);
		
		cpu.reset();
		
		mem data;
		data[TRESET_VECTOR_ADDRESS] = ADC_IM;
		data[TRESET_VECTOR_ADDRESS + 1] = val;
		
		cpu.test_load_mem(std::move(data));
		cpu.test_load_reg_A(A);
		cpu.test_load_reg_SR_C(carry);
		cpu.exec();
		
		return test_ADC_reg_check(cpu.get_reg(), A, val, carry, TRESET_VECTOR_ADDRESS + 2, expected_C, expected_V);
	}

	auto test_ADC_IM_nzero_nneg_ncarry_noverflow() -> bool 
	{ 
		if (not test_ADC_IM(65, 1, false, false, false))
			return false;

		if (not test_ADC_IM(65, -35, false, true, false))
			return false;

		return test_ADC_IM(65, 1, true, false, false);
	}

	auto test_ADC_IM_zero_nneg_ncarry_noverflow() -> bool 
	{ 
		if (not test_ADC_IM(255, -255, false, false, false))
			return false;

		return test_ADC_IM(0, 0, false, false, false);
	}

	auto test_ADC_IM_nzero_nneg_carry_noverflow() -> bool 
	{ 
		if (not test_ADC_IM(255, 1, false, true, true))
			return false;

		return test_ADC_IM(255, 1, true, true, true);
	}

	auto test_ADC_IM_nzero_neg_ncarry_noverflow() -> bool
	{
		if (not test_ADC_IM(-65, 1, false, false, false))
			return false;

		if (not test_ADC_IM(-65, -35, false, false, false))
			return false;

		if (not test_ADC_IM(-65, -35, true, false, false))
			return false;

		if (not test_ADC_IM(-255, 0, true, false, false))
			return false;

		return test_ADC_IM(-65, 1, true, false, false);
	}

	//auto test_ADC_IM_nzero_neg_ncarry_overflow_positive() -> bool
	//{
	//	return test_ADC_IM(-255, -255, true);
	//}

	//auto test_ADC_IM_nzero_neg_ncarry_overflow_positive() -> bool
	//{
	//	return test_ADC_IM(255, 255, true);
	//}
}
