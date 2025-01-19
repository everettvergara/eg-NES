#pragma once

#include "types.h"
#include "sr.h"

namespace eg::m6502
{
	struct reg
	{
		word PC;		// Program counter(16 bit)
		byte AC;		// Accumulator	(8 bit)
		byte X;			// X register	(8 bit)
		byte Y;			// Y register	(8 bit)
		byte SP;		// Stack pointer(8 bit)
		sr SR;			// Status register(8 bit)

		//reg();
	};
}
