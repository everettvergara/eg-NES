#include "m6502.h" 

namespace eg::m6502
{
	auto m6502::exec_ADC_IM_() -> void
	{
		const byte val = read_mem_by_bpc();	// Read immediate value
		const word result = reg_.AC + val + (reg_.SR.C ? 1 : 0);
		const byte byte_result = static_cast<byte>(result);

		//reg_.SR.V = (~(reg_.AC ^ val) & (reg_.AC ^ static_cast<byte>(byte_result)) & 0x80) > 0;

		// Overflow cannot occur with different sign 
		// because the result will be close to zero (0)
		// --
		// 
		// reg_.AC ^ val, check if it has same bit 7. If it does then result of bit 7 will be 0
		// 
		// 1000 0000
		// 0000 0000 ^
		// 1000 0000 <-- Bit 7 is 1,

		reg_.SR.C = result > 0xff;
		reg_.SR.V = (~(reg_.AC ^ val) & (reg_.AC ^ byte_result) & 0x80) > 0;
		reg_.AC = byte_result;

		set_ZN_(result);

	}
}