#pragma once

#include <cstdint>

namespace eg
{
	using byte = uint8_t;
	using word = uint16_t;

	struct status_reg
	{
		byte C : 1;		// Carry flag
		byte Z : 1;		// Zero flag
		byte I : 1;		// Interrupt disable
		byte D : 1;		// Decimal mode
		byte B : 1;		// Break command
		byte _ : 1;		// Unused
		byte V : 1;		// Overflow flag
		byte N : 1;		// Negative flag

		auto reset() -> void
		{
			C = Z = I = D = B = _ = V = N = 0;
		}
	};

	struct reg
	{
		word PC;		// Program counter(16 bit)
		byte AC;		// Accumulator	(8 bit)
		byte X;			// X register	(8 bit)
		byte Y;			// Y register	(8 bit)
		status_reg SR;	// Status register(8 bit)
		byte SP;		// Stack pointer(8 bit)
	};

	struct mem
	{
	private:
		static constexpr size_t MAX_MEM = 1024 * 64;

	public:
		byte data[MAX_MEM];

		auto reset() -> void
		{
			std::memset(data, 0, MAX_MEM);
		}
	};

	class computer
	{
	public:

		computer(word RESET_VECTOR_ADDRESS, word RESET_ROUTINE_ADDRESS) :
			RESET_VECTOR_ADDRESS_(RESET_VECTOR_ADDRESS), RESET_ROUTINE_ADDRESS_(RESET_ROUTINE_ADDRESS) {
		}

		computer(const computer&) = delete;
		computer& operator=(const computer&) = delete;
		computer(computer&&) = delete;
		computer& operator=(computer&&) = delete;
		virtual ~computer() {}
		virtual auto reset() -> void = 0;

	private:
		word RESET_VECTOR_ADDRESS_;
		word RESET_ROUTINE_ADDRESS_;
		reg R_;
		mem M_;
	};

	class generic_6502 : public computer
	{
	public:

		generic_6502() :
			computer(0xFFFC, 0x0000)
		{
		}

		~generic_6502()
		{
		}

		auto reset() -> void override
		{
		}
	};
}
