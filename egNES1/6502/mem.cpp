#include "mem.h"

namespace eg::m6502
{
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
		data.fill(0);
	}
}
