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

		auto write_mem_by_badd(byte address, byte value) -> void;
		auto write_mem_by_wadd(word address, byte value) -> void;

		auto get_reg() const->const reg&;
		auto get_mem() const->const mem&;

	protected:

		const word reset_vector_addr_;
		const word reset_routine_addr_;

		cycle cycles_;
		reg reg_;
		mem mem_;

		auto set_ZN_(byte value) -> void;

		// LDA
		auto exec_LDA_IM_() -> void;
		auto exec_LDA_ZP_() -> void;
		auto exec_LDA_ZPX_() -> void;
		auto exec_LDA_ABS_() -> void;
		auto exec_LDA_ABSX_() -> void;
		auto exec_LDA_ABSY_() -> void;
		auto exec_LDA_INDX_() -> void;
		auto exec_LDA_INDY_() -> void;

		// LDX
		auto exec_LDX_IM_() -> void;
		auto exec_LDX_ZP_() -> void;
		auto exec_LDX_ZPY_() -> void;
		auto exec_LDX_ABS_() -> void;
		auto exec_LDX_ABSY_() -> void;

		// LDY
		auto exec_LDY_IM_() -> void;
		auto exec_LDY_ZP_() -> void;
		auto exec_LDY_ZPX_() -> void;
		auto exec_LDY_ABS_() -> void;
		auto exec_LDY_ABSX_() -> void;

		// NOP
		auto exec_NOP_IMP_() -> void;

		// INC
		auto exec_INC_ZP_() -> void;
		auto exec_INC_ZPX_() -> void;
		auto exec_INC_ABS_() -> void;
		auto exec_INC_ABSX_() -> void;
	};
}
