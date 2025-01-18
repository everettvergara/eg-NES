// References:
// https://www.c64-wiki.com
// https://www.masswerk.at/6502/6502_instruction_set.html
// https://www.nesdev.org/obelisk-6502-guide/reference.html#LDA
// https://github.com/catchorg/Catch2

#include <iostream>
#include "m6502_generic.h"

auto main(int, char* []) -> int
{
	using namespace eg;

	m6502::m6502_generic nes(0xFFFC, 0x0000);

	nes.reset();
	nes.test_loader();
	nes.exec();
	return 0;
}
