#pragma once

#include <vector>
#include "types.h"

namespace eg::m6502
{
	inline constexpr size_t MAX_MEM = 1024 * 64;

	class mem
	{
	public:
		mem();
		auto operator[](word address) const->byte;
		auto operator[](word address)->byte&;
		auto reset() -> void;

		struct iterator
		{
			iterator(byte* ptr) : ptr_(ptr) {}
			auto operator->() -> byte* { return ptr_; }
			auto operator*() -> byte& { return *ptr_; }
			auto operator++() -> iterator& { ++ptr_; return *this; }
			auto operator!=(const iterator& other) -> bool { return ptr_ != other.ptr_; }
		private:
			byte* ptr_;
		};

		auto begin() -> iterator { return iterator(data_.data()); }
		auto end() -> iterator { return iterator(data_.data() + data_.size()); }

	private:
		std::vector<byte> data_;
	};
}
