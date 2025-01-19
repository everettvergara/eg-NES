#include "mem.h"

namespace eg::m6502
{
	mem::mem() :
		data(MAX_MEM, '\0')
	{
	}
	auto mem::operator[](word address) const->byte
	{
		return data[address];
	}

	auto mem::operator[](word address)->byte&
	{
		return data[address];
	}

	auto mem::reset() -> void
	{
		std::memset(data.data(), '\0', data.size());
	}
}
