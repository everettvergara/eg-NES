#pragma once

#include <array>
#include "types.h"

namespace eg::m6502
{
	inline constexpr size_t MAX_MEM = 1024 * 64;

	class mem
	{
		std::array<byte, MAX_MEM> data;

	public:
		auto operator[](word address) const->byte;
		auto operator[](word address)->byte&;
		auto reset() -> void;
	};
}
