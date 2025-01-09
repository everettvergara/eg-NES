#include <cassert>
#include "cycle.h"

namespace eg::m6502
{
	auto cycle::start_and_simulate(byte cycles) -> void
	{
		cycles_ = cycles;
		start_ = std::chrono::steady_clock::now();

		simulate();
	}

	auto cycle::simulate() -> void
	{
		assert(cycles_ > 0);

		--cycles_;

		const auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - start_);

		if (elapsed < MICRO_SEC_PER_CYCLE)
		{
			std::this_thread::sleep_for(MICRO_SEC_PER_CYCLE - elapsed);
		}
	}
};
