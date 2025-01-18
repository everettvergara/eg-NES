#include <cassert>
#include "m6502.h"

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
		default:
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
	auto m6502::read_mem_by_pc() -> byte
	{
		cycles_.simulate();
		return mem_[reg_.PC++];
	}

	// Increments PC
	auto m6502::read_instruction() -> byte
	{
		const byte op_code = mem_[reg_.PC++];
		assert(op_code > 0);

		cycles_.start_and_simulate(ins[op_code].cycles);
		return op_code;
	}

	// LDA_IM: Immediate
	//
	// Immediate addressing allows the programmer to directly specify an 8 bit constant within the instruction.
	// It is indicated by a '#' symbol followed by an numeric expression. For example:
	// LDA #10
	auto m6502::exec_LDA_IM_() -> void
	{
		byte value = read_mem_by_pc();
		exec_LDA_set_AZN(value);
	}

	// LDA_ZP: Zero Page
	//
	// An instruction using zero page addressing mode has only an 8 bit address operand.
	// This limits it to addressing only the first 256 bytes of memory(e.g.$0000 to $00FF) where
	// the most significant byte of the address is always zero.
	//
	// In zero page mode only the least significant byte of the address is held in the instruction
	// making it shorter by one byte(important for space saving) and one less memory fetch during
	// execution(important for speed).
	//
	// An assembler will automatically select zero page addressing mode if the operand evaluates
	// to a zero page address and the instruction supports the mode(not all do).

	auto m6502::exec_LDA_ZP_() -> void
	{
		const byte badd = read_mem_by_pc();
		byte value = read_mem_by_badd(badd);
		exec_LDA_set_AZN(value);
	}

	// LDA_ZPX: Zero Page Indexed with X
	//
	// The address to be accessed by an instruction using indexed zero page addressing is calculated
	// by taking the 8 bit zero page address from the instruction and adding the current value of the X register
	// to it.
	//
	// For example if the X register contains $0F and the instruction LDA $80,X is executed then the accumulator
	// will be loaded from $008F (e.g. $80 + $0F => $8F).
	//
	// The address calculation wraps around if the sum of the base address and the register exceed $FF.
	// If we repeat the last example but with $FF in the X register then the accumulator will be
	// loaded from $007F(e.g.$80 + $FF = > $7F) and not $017F.

	auto m6502::exec_LDA_ZPX_() -> void
	{
		const byte badd = read_mem_by_pc() + reg_.X;

		cycles_.simulate(); // For adding X
		byte value = read_mem_by_badd(badd);
		exec_LDA_set_AZN(value);
	}

	auto m6502::exec_LDA_set_AZN(byte value) -> void
	{
		reg_.AC = value;
		reg_.SR.Z = (value == 0);
		reg_.SR.N = (value & 0b10000000) > 0;
	}
}
