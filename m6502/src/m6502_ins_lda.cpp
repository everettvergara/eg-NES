#include "m6502.h"
#include <cassert>

namespace eg::m6502
{
	// LDA_IM: Immediate
	//
	// Immediate addressing allows the programmer to directly specify an 8 bit constant within the instruction.
	//
	// Operation:
	// 0xfffc: {LDA_IM}
	// 0xfffd: 'A'
	//
	// exec();
	// reg_.PC = 0xfffe
	// reg_.AC = 'A'
	// reg_.Z = 1, if AC == 0 else 0
	// reg_.N = 1, if |AC| > 127 else 0

	auto m6502::exec_LDA_IM_() -> void
	{
		const byte value = read_mem_by_bpc();
		reg_.AC = value;
		set_ZN_(value);
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
	//
	// Operation:
	//
	// 0x0005: 'A' <-------+
	// ...                 |
	// 0xfffc: {LDA_ZP}    |
	// 0xfffd: 0x05 -------+
	//
	// reg_.PC = 0xfffe
	// reg_.AC = 'A'
	// reg_.Z = 1, if AC == 0 else 0
	// reg_.N = 1, if |AC| > 127 else 0

	auto m6502::exec_LDA_ZP_() -> void
	{
		const byte badd = read_mem_by_bpc();
		const byte value = read_mem_by_badd(badd);
		reg_.AC = value;
		set_ZN_(value);
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
	//
	// Operation:
	// 0x0085: 'A' <--------------------------------------------+
	// ...                                                      |
	// 0xfffc: {LDA_ZPX}                                        |
	// 0xfffd: 0x05 -------> + reg_.X (0x80) & 0x00ff = 0x85 ---+
	//
	// reg_.PC = 0xfffe
	// reg_.AC = 'A'
	// reg_.Z = 1, if AC == 0 else 0
	// reg_.N = 1, if |AC| > 127 else 0

	auto m6502::exec_LDA_ZPX_() -> void
	{
		const byte badd = read_mem_by_bpc() + reg_.X;

		// Why adding X to the base address requires 1 cycle?
		// (per chatgpt) --
		// Add the X register to the base address: This requires reading the base address, adding the value of X, and
		// performing a modulo-256 operation to keep the result in the zero-page range.
		// The addition and wrapping are handled in hardware and cost 1 cycle.

		cycles_.simulate();
		const byte value = read_mem_by_badd(badd);
		reg_.AC = value;
		set_ZN_(value);
	}

	// LDA_ABS: Absolute
	//
	// Instructions using absolute addressing contain a full 16 bit address to identify the target location.
	//
	// Operation:
	// 0x2001: 'A' <---------------+
	// ...                         |
	// 0xfffc: {LDA_ABS}           |
	// 0xfffd: 0x01 ---------------+ (LSB)
	// 0xfffe: 0x20 ---------------+ (MSB)
	//
	// reg_.PC = 0xffff
	// reg_.AC = 'A'
	// reg_.Z = 1, if AC == 0 else 0
	// reg_.N = 1, if |AC| > 127 else 0

	auto m6502::exec_LDA_ABS_() -> void
	{
		const word wadd = read_mem_by_wpc();
		const byte value = read_mem_by_wadd(wadd);
		reg_.AC = value;
		set_ZN_(value);
	}

	// LDA_ABSX: Absolute Indexed with X
	//
	// The address to be accessed by an instruction using X register indexed absolute addressing is
	// computed by taking the 16 bit address from the instruction and added the contents of the X register.
	//
	// For example if X contains $92 then an STA $2000,X instruction will store the accumulator
	// at $2092 (e.g. $2000 + $92).
	//
	// Operation:
	// 0x2001: 'A' <--------------------------------------------+
	// ...                                                      |
	// 0xfffc: {LDA_ABSX}                                       |
	// 0xfffd: 0x01 -------> + reg_.X (0x80) = 0x81 ------------+ (LSB)
	// 0xfffe: 0x20 --------------------------------------------+ (MSB)
	//

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
		reg_.AC = value;
		set_ZN_(value);
	}

	// LDA_ABSY: Absolute Indexed with Y
	//
	// Same as LDA_ABSX but with Y register
	//
	// Operation:
	// 0x2001: 'A' <--------------------------------------------+
	// ...                                                      |
	// 0xfffc: {LDA_ABSY}                                       |
	// 0xfffd: 0x01 -------> + reg_.Y (0x80) = 0x81 ------------+ (LSB)
	// 0xfffe: 0x20 --------------------------------------------+ (MSB)
	//

	auto m6502::exec_LDA_ABSY_() -> void
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
		reg_.AC = value;
		set_ZN_(value);
	}

	// LDA_INDX: Indirect Indexed with X
	//
	// Operation:
	// 0x0085: 0x01 -----+ (LSB) <------------------------+
	// 0x0086: 0x02	-----+ (MSB)						  |
	// ...               |                                |
	// 0x0201: 'A'	<----+								  |
	// ...                                                |
	// 0xfffc: {LDA_INDX}                                 |
	// 0xfffd: 0x05 -------> + reg_.X (0x80) & 0xff00 ----+
	//
	// reg_.PC = 0xfffe
	// reg_.AC = 'A'
	// reg_.Z = 1, if AC == 0 else 0
	// reg_.N = 1, if |AC| > 127 else 0

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
		reg_.AC = value;
		set_ZN_(value);
	}

	// LDA_INDY: Indirect Indexed with Y
	//
	// Operation:
	// 0x000e: 0x02 -----+ (LSB) <------------------------+
	// 0x000f: 0x01	-----+ (MSB)						  |
	//				     | + reg_.Y (0x80) = 0x0182	      |
	// ...               |                                |
	// 0x0182: 'A'	<----+								  |
	// ...                                                |
	// 0xfffc: {LDA_INDY}                                 |
	// 0xfffd: 0x0e --------------------------------------+

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
		reg_.AC = value;
		set_ZN_(value);
	}

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
}
