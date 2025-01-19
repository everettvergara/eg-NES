#include "mem.h"

namespace eg::m6502
{
	mem::mem() :
		data_(MAX_MEM, '\0')
	{
	}
	auto mem::operator[](word address) const->byte
	{
		return data_[address];
	}

	auto mem::operator[](word address)->byte&
	{
		return data_[address];
	}

	auto mem::reset() -> void
	{
		std::memset(data_.data(), '\0', data_.size());
	}
}
