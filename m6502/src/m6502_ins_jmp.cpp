#include "m6502.h" 

namespace eg::m6502
{
	auto m6502::exec_JMP_ABS_() -> void
	{
		const word address = read_mem_by_wpc();

		reg_.PC = address;
		//cycles_.simulate();
	}

	auto m6502::exec_JMP_IND_() -> void
	{
		const word iaddress = read_mem_by_wpc();
		const word address = [this, iaddress]() -> word {	if (extra_.has_JMP_IND_bug and (iaddress & 0x00ff) == 0x00ff)
															{
																// mem_[0x2000] = JMP_IND
																// mem_[0x2001] = 0xff
																// mem_[0x2002] = 0x30
																// ...
																// 
																// mem_[0x3000] = 0x66
																// mem_[0x30ff] = 0x11
																// mem_[0x3051] = 0x55 <-- will not be read
																// ...	
																// mem_[0x6611] = <---- reg_.PC
			
																const byte low_add = read_mem_by_wadd(iaddress);
																const byte high_add = read_mem_by_wadd(iaddress & 0xff00);
																const word bug_address = (high_add << 8) | low_add;
																return bug_address;
															}
															else
															{
																// mem_[0x2000] = JMP_IND
																// mem_[0x2001] = 0x50
																// mem_[0x2002] = 0x30
																// ...
																// 
																// mem_[0x3050] = 0x11
																// mem_[0x3051] = 0x55
																// ...	
																// mem_[0x5511] = <---- reg_.PC

																const byte low_add = read_mem_by_wadd(iaddress);
																const byte high_add = read_mem_by_wadd(iaddress + 1);
																const word new_address = (high_add << 8) | low_add;
																return new_address;
															}
														} ();
		reg_.PC = address;
	}
}