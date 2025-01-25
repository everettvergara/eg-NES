#pragma once
#if not defined(_WIN32) and not defined(_WIN64) and not defined(__APPLE__) and not defined(__MACH__) and not defined(__linux__)
#error ERROR: Only support little endian architecture
#endif

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

		auto exec() -> void;

		auto read_mem_by_badd(byte address) -> byte;
		auto read_mem_by_wadd(word address) -> byte;
		auto read_mem_by_bpc() -> byte;
		auto read_mem_by_wpc() -> word;
		auto read_instruction() -> byte;

		auto get_reg() const->const reg&;

	protected:

		const word reset_vector_addr_;
		const word reset_routine_addr_;

		cycle cycles_;
		reg reg_;
		mem mem_;

		auto exec_LDA_IM_() -> void;
		auto exec_LDA_ZP_() -> void;
		auto exec_LDA_ZPX_() -> void;
		auto exec_LDA_ABS_() -> void;
		auto exec_LDA_ABSX_() -> void;
		auto exec_LDA_ABSY_() -> void;
		auto exec_LDA_INDX_() -> void;
		auto exec_LDA_INDY_() -> void;
		auto exec_LD_set_ZN_(byte value) -> void;
		auto exec_set_ZN_(byte value) -> void;
	};
}
