#include "m6502.h"
#include "m6502.h"
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
		case LDA_ABS: exec_LDA_ABS_(); break;
		case LDA_ABSX: exec_LDA_ABSX_(); break;
		case LDA_ABSY: exec_LDA_ABSY_(); break;
		case LDA_INDX: exec_LDA_INDX_(); break;
		case LDA_INDY: exec_LDA_INDY_(); break;
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

	auto m6502::get_reg() const -> const reg&
	{
		return reg_;
	}

	// LDA_IM: Immediate
	//
	// Immediate addressing allows the programmer to directly specify an 8 bit constant within the instruction.
	// It is indicated by a '#' symbol followed by an numeric expression. For example:
	// LDA #10

	auto m6502::exec_LDA_IM_() -> void
	{
		byte value = read_mem_by_bpc();
		exec_LDA_set_AZN_(value);
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
		const byte badd = read_mem_by_bpc();
		byte value = read_mem_by_badd(badd);
		exec_LDA_set_AZN_(value);
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
		const byte badd = read_mem_by_bpc() + reg_.X;

		// Why adding X to the base address requires 1 cycle?
		// (per chatgpt) --
		// Add the X register to the base address: This requires reading the base address, adding the value of X, and
		// performing a modulo-256 operation to keep the result in the zero-page range.
		// The addition and wrapping are handled in hardware and cost 1 cycle.
		cycles_.simulate();
		byte value = read_mem_by_badd(badd);
		exec_LDA_set_AZN_(value);
	}

	// LDA_ABS: Absolute
	//
	// Instructions using absolute addressing contain a full 16 bit address to identify the target location.

	auto m6502::exec_LDA_ABS_() -> void
	{
		const word wadd = read_mem_by_wpc();
		byte value = read_mem_by_wadd(wadd);
		exec_LDA_set_AZN_(value);
	}

	// LDA_ABSX: Absolute Indexed with X
	//
	// The address to be accessed by an instruction using X register indexed absolute addressing is
	// computed by taking the 16 bit address from the instruction and added the contents of the X register.
	//
	// For example if X contains $92 then an STA $2000,X instruction will store the accumulator
	// at $2092 (e.g. $2000 + $92).

	auto m6502::exec_LDA_ABSX_() -> void
	{
		// 1 cycle - ins
		const word wadd = read_mem_by_wpc(); // 2 cycles for read_mem_by_wpc
		const word wadd_x = wadd + reg_.X;

		// 1 cycle - for cross page boundary
		if ((wadd_x & 0xFF00) not_eq (wadd & 0xFF00))
		{
			cycles_.add(1);
			cycles_.simulate();
		}

		byte value = read_mem_by_wadd(wadd_x); // 1
		exec_LDA_set_AZN_(value);
	}

	// LDA_ABSY: Absolute Indexed with Y
	//
	// Same as LDA_ABSX but with Y register

	auto m6502::exec_LDA_ABSY_() -> void
	{
		// 1 cycle - ins
		const word wadd = read_mem_by_wpc(); // 2 cycles for read_mem_by_wpc
		const word wadd_x = wadd + reg_.Y;

		// 1 cycle - for cross page boundary
		if ((wadd_x & 0xFF00) not_eq (wadd & 0xFF00))
		{
			cycles_.add(1);
			cycles_.simulate();
		}

		const byte value = read_mem_by_wadd(wadd_x); // 1
		exec_LDA_set_AZN_(value);
	}

	// LDA_INDX: Indirect Indexed with X
	//
	//

	auto m6502::exec_LDA_INDX_() -> void
	{
		// 1 cycle - ins
		const byte badd = read_mem_by_bpc() + reg_.X; // 1 cycle for read_mem_by_bpc

		// Why adding X to the base address requires 1 cycle?
		// (per chatgpt) --
		// Add the X register to the base address: This requires reading the base address, adding the value of X, and
		// performing a modulo-256 operation to keep the result in the zero-page range.
		// The addition and wrapping are handled in hardware and cost 1 cycle.
		cycles_.simulate();

		const byte ladd = read_mem_by_badd(badd); // 1 cycle
		const byte hadd = read_mem_by_badd(badd + 1); // 1 cycle
		const word wadd = ladd | (hadd << 8);

		const byte value = read_mem_by_wadd(wadd); // 1 cycle
		exec_LDA_set_AZN_(value);
	}

	auto m6502::exec_LDA_INDY_() -> void
	{
		// 1 cycle - ins
		const byte badd = read_mem_by_bpc(); // 1 cycle for read_mem_by_bpc

		const byte ladd = read_mem_by_badd(badd); // 1 cycle
		const byte hadd = read_mem_by_badd(badd + 1); // 1 cycle
		const word wadd = ladd | (hadd << 8);
		const word wadd_y = wadd + reg_.Y;

		if ((wadd_y & 0xFF00) not_eq (wadd & 0xFF00))
		{
			cycles_.add(1);
			cycles_.simulate();
		}

		const byte value = read_mem_by_wadd(wadd_y); // 1 cycle
		exec_LDA_set_AZN_(value);
	}

	auto m6502::exec_LDA_set_AZN_(byte value) -> void
	{
		reg_.AC = value;
		reg_.SR.Z = (value == 0);
		reg_.SR.N = (value & 0b10000000) > 0;
	}
}
