#include "reg.h"

namespace eg::m6502
{
	reg::reg() :
		PC(0),
		AC(0),
		X(0),
		Y(0),
		SP(0),
		SR()
	{
	}
}