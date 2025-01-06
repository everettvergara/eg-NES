#include "m6502.h"

namespace eg::m6502
{
	m6502::m6502(word reset_vector_add, word reset_routine_addr) :
		reset_vector_addr_(reset_vector_add),
		reset_routine_addr_(reset_routine_addr)
	{
	}

	auto m6502::execute() -> void
	{
		auto [op_code, cycles] = peek_instruction();
		cycles_.start_and_simulate(cycles);

		switch (op_code)
		{
		case LDA_IM:
			exec_LDA_IM_();
			break;

		default:
			break;
		}
	}

	auto m6502::peek_instruction() -> std::array<byte, 2>
	{
		byte op_code = mem_[reg_.PC];

		auto cycles = ins[op_code].cycles;

		++reg_.PC;

		return { op_code, cycles };
	}

	auto m6502::read_byte() -> byte
	{
		return mem_[reg_.PC++];
	}

	auto m6502::exec_LDA_IM_() -> void
	{
		byte value = read_byte();
		reg_.AC = value;
		reg_.SR.Z = (value == 0);
		reg_.SR.N = (value & 0b10000000) > 0;

		cycles_.simulate();
	}
}
