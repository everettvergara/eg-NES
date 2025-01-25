#include "m6502.h"
#include <cassert>

namespace eg::m6502
{
	// LDX_IM: Immediate
	//
	// Immediate addressing allows the programmer to directly specify an 8 bit constant within the instruction.
	//
	// Operation:
	// 0xfffc: {LDX_IM}
	// 0xfffd: 'A'
	//
	// exec();
	// reg_.PC = 0xfffe
	// reg_.X = 'A'
	// reg_.Z = 1, if X == 0 else 0
	// reg_.N = 1, if |X| > 127 else 0

	auto m6502::exec_LDX_IM_() -> void
	{
		const byte value = read_mem_by_bpc();
		reg_.X = value;
		exec_LD_set_ZN_(value);
	}

	// LDX_ZP: Zero Page
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
	//
	// Operation:
	//
	// 0x0005: 'A' <-------+
	// ...                 |
	// 0xfffc: {LDX_ZP}    |
	// 0xfffd: 0x05 -------+
	//
	// reg_.PC = 0xfffe
	// reg_.X = 'A'
	// reg_.Z = 1, if X == 0 else 0
	// reg_.N = 1, if |X| > 127 else 0

	auto m6502::exec_LDX_ZP_() -> void
	{
		const byte badd = read_mem_by_bpc();
		const byte value = read_mem_by_badd(badd);
		reg_.X = value;
		exec_LD_set_ZN_(value);
	}

	// LDX_ZPY: Zero Page Indexed with Y
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
	//
	// Operation:
	// 0x0085: 'A' <--------------------------------------------+
	// ...                                                      |
	// 0xfffc: {LDX_ZPY}                                        |
	// 0xfffd: 0x05 -------> + reg_.X (0x80) & 0x00ff = 0x85 ---+
	//
	// reg_.PC = 0xfffe
	// reg_.Y = 'A'
	// reg_.Z = 1, if Y == 0 else 0
	// reg_.N = 1, if |Y| > 127 else 0

	auto m6502::exec_LDX_ZPY_() -> void
	{
		const byte badd = read_mem_by_bpc() + reg_.Y;

		// Why adding Y to the base address requires 1 cycle?
		// (per chatgpt) --
		// Add the Y register to the base address: This requires reading the base address, adding the value of Y, and
		// performing a modulo-256 operation to keep the result in the zero-page range.
		// The addition and wrapping are handled in hardware and cost 1 cycle.

		cycles_.simulate();
		const byte value = read_mem_by_badd(badd);
		reg_.X = value;
		exec_LD_set_ZN_(value);
	}

	// LDX_ABS: Absolute
	//
	// Instructions using absolute addressing contain a full 16 bit address to identify the target location.
	//
	// Operation:
	// 0x2001: 'A' <---------------+
	// ...                         |
	// 0xfffc: {LDX_ABS}           |
	// 0xfffd: 0x01 ---------------+ (LSB)
	// 0xfffe: 0x20 ---------------+ (MSB)
	//
	// reg_.PC = 0xffff
	// reg_.X = 'A'
	// reg_.Z = 1, if X == 0 else 0
	// reg_.N = 1, if |X| > 127 else 0

	auto m6502::exec_LDX_ABS_() -> void
	{
		const word wadd = read_mem_by_wpc();
		const byte value = read_mem_by_wadd(wadd);
		reg_.X = value;
		exec_LD_set_ZN_(value);
	}

	// LDX_ABSY: Absolute Indexed with Y
	//
	// Operation:
	// 0x2001: 'A' <--------------------------------------------+
	// ...                                                      |
	// 0xfffc: {LDX_ABSY}                                       |
	// 0xfffd: 0x01 -------> + reg_.Y (0x80) = 0x81 ------------+ (LSB)
	// 0xfffe: 0x20 --------------------------------------------+ (MSB)
	//

	auto m6502::exec_LDX_ABSY_() -> void
	{
		// 1 cycle - ins
		const word wadd = read_mem_by_wpc(); // 2 cycles for read_mem_by_wpc
		const word wadd_y = wadd + reg_.Y;

		// 1 cycle - for cross page boundary
		if ((wadd_y & 0xFF00) not_eq (wadd & 0xFF00))
		{
			cycles_.add(1);
			cycles_.simulate();
		}

		const byte value = read_mem_by_wadd(wadd_y); // 1
		reg_.X = value;
		exec_LD_set_ZN_(value);
	}
}
