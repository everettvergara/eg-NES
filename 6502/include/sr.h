#pragma once

#include "types.h"

namespace eg::m6502
{
	struct sr
	{
		byte C : 1;		// Carry flag
		byte Z : 1;		// Zero flag
		byte I : 1;		// Interrupt disable
		byte D : 1;		// Decimal mode
		byte B : 1;		// Break command
		byte _ : 1;		// Unused
		byte V : 1;		// Overflow flag
		byte N : 1;		// Negative flag

		sr();
	};
}
