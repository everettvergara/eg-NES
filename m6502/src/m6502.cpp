#include "m6502.h"
#include <cassert>

namespace eg::m6502
{
	m6502::m6502(word reset_vector_add, word reset_routine_addr) :
		reset_vector_addr_(reset_vector_add),
		reset_routine_addr_(reset_routine_addr)
	{
	}

	auto m6502::exec() -> void
	{
		switch (const auto op_code = read_instruction(); op_code)
		{
		case LDA_IM: exec_LDA_IM_(); break;
		case LDA_ZP: exec_LDA_ZP_(); break;
		case LDA_ZPX: exec_LDA_ZPX_(); break;
		case LDA_ABS: exec_LDA_ABS_(); break;
		case LDA_ABSX: exec_LDA_ABSX_(); break;
		case LDA_ABSY: exec_LDA_ABSY_(); break;
		case LDA_INDX: exec_LDA_INDX_(); break;
		case LDA_INDY: exec_LDA_INDY_(); break;

		case LDX_IM: exec_LDX_IM_(); break;
		case LDX_ZP: exec_LDX_ZP_(); break;
		case LDX_ZPY: exec_LDX_ZPY_(); break;
		case LDX_ABS: exec_LDX_ABS_(); break;
		case LDX_ABSY: exec_LDX_ABSY_(); break;

		case LDY_IM: exec_LDY_IM_(); break;
		case LDY_ZP: exec_LDY_ZP_(); break;
		case LDY_ZPX: exec_LDY_ZPX_(); break;
		case LDY_ABS: exec_LDY_ABS_(); break;
		case LDY_ABSX: exec_LDY_ABSX_(); break;

		case NOP_IMP: exec_NOP_IMP_(); break;

		case INC_ZP: exec_INC_ZP_(); break;
		case INC_ZPX: exec_INC_ZPX_(); break;
		case INC_ABS: exec_INC_ABS_(); break;
		case INC_ABSX: exec_INC_ABSX_(); break;

		default:
			assert(false);
			break;
		}

		assert(cycles_.is_zero());
	}

	// DOES NOT increments PC
	auto m6502::read_mem_by_badd(byte address) -> byte
	{
		cycles_.simulate();
		return mem_[address];
	}

	// DOES NOT increments PC
	auto m6502::read_mem_by_wadd(word address) -> byte
	{
		cycles_.simulate();
		return mem_[address];
	}

	// Increments PC
	auto m6502::read_mem_by_bpc() -> byte
	{
		cycles_.simulate();
		return mem_[reg_.PC++];
	}

	// Increments PC+2
	auto m6502::read_mem_by_wpc() -> word
	{
		//cycles_.simulate();
		const word value = mem_[reg_.PC] | (mem_[reg_.PC + 1] << 8);

		++reg_.PC;
		cycles_.simulate();

		++reg_.PC;
		cycles_.simulate();

		return value;
	}

	// Increments PC
	auto m6502::read_instruction() -> byte
	{
		const byte op_code = mem_[reg_.PC++];
		assert(op_code > 0);

		cycles_.start_and_simulate(ins[op_code].cycles);
		return op_code;
	}

	auto m6502::write_mem_by_badd(byte address, byte value) -> void
	{
		cycles_.simulate();
		mem_[address] = value;
	}

	auto m6502::write_mem_by_wadd(word address, byte value) -> void
	{
		cycles_.simulate();
		mem_[address] = value;
	}

	auto m6502::get_reg() const -> const reg&
	{
		return reg_;
	}

	auto m6502::set_ZN_(byte value) -> void
	{
		reg_.SR.Z = (value == 0);
		reg_.SR.N = (value & 0b10000000) > 0;
	}
}
