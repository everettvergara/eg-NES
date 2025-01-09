#pragma once

#include <cstdint>
#include <chrono>
#include <thread>
#include "types.h"

namespace eg::m6502
{
	inline constexpr auto FREQUENCY_MHZ = 1'000'000;
	static constexpr auto CYCLES_PER_SEC = 1.0 / FREQUENCY_MHZ;
	inline constexpr auto MICRO_SEC_PER_CYCLE = std::chrono::microseconds(static_cast<long long>(CYCLES_PER_SEC * 1.0e+6));

	class cycle
	{
	public:

		cycle() = default;

		auto start_and_simulate(byte cycles) -> void;
		auto simulate() -> void;
		auto is_zero() const -> bool;

	private:

		std::chrono::time_point<std::chrono::steady_clock> start_;
		byte cycles_;
	};
}
