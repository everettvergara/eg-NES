#pragma once

#include <cstdint>
#include <chrono>
#include <thread>
#include "types.h"

namespace eg::m6502
{
	constexpr auto MICRO_SEC_PER_CYCLE = std::chrono::microseconds(1);

	class cycle
	{
	public:

		cycle() = default;

		auto has_bug() const -> bool;
		auto start_and_simulate(byte cycles) -> void;
		auto simulate() -> void;

	private:

		std::chrono::time_point<std::chrono::steady_clock> start_;
		byte cycles_;

		bool bug_ = false;
	};
}
