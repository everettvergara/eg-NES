#pragma once

#include <vector>
#include "types.h"

namespace eg::m6502
{
	inline constexpr size_t MAX_MEM = 1024 * 64;

	class mem
	{
		std::vector<byte> data;

	public:
		mem();
		auto operator[](word address) const->byte;
		auto operator[](word address)->byte&;
		auto reset() -> void;
	};
}
