#pragma once

#include <array>
#include "reg.h"
#include "ins.h"
#include "cycle.h"
#include "mem.h"

namespace eg::m6502
{
	class m6502
	{
	public:

		m6502(word reset_vector_add, word reset_routine_addr);

		m6502(const m6502&) = delete;
		m6502& operator=(const m6502&) = delete;
		m6502(m6502&&) = delete;
		m6502& operator=(m6502&&) = delete;

		virtual ~m6502() = default;
		virtual auto reset() -> void = 0;

		auto execute() -> void;

		auto read_mem_by_badd(byte address) -> byte;
		auto read_mem_by_wadd(word address) -> byte;
		auto read_mem_by_pc() -> byte;
		auto read_instruction() -> byte;

	protected:

		const word reset_vector_addr_;
		const word reset_routine_addr_;

		cycle cycles_;
		reg reg_;
		mem mem_;

		auto exec_LDA_IM_() -> void;
		auto exec_LDA_ZP_() -> void;
		auto exec_LDA_set_AZN(byte value) -> void;
	};
}
