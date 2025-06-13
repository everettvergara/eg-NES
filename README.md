# eg-NES
Another 6502 Emulator for NES written in Modern C++.

## Roadmap
- m6502 Emulator
	* Registers
	* Instruction set
	* Interrupts
	* Memory access
- PPU 
- APU
- Cartridge
- Input

## Co-Maintainers
Looking for co-maintainer, email me at everettvergara@gmail.com;

## Logs
### 2025-02-01:
m6502 Emulator: Implementation and Unit Test - JMP_ABS, JMP_IND

### 2025-01-30:
m6502 Emulator: Implementation and Unit Test - DEC_ZP, DEC_ZPX, DEC_ABS, DEC_ABSX
m6502 Emulator: Implementation and Unit Test - DEX_IMP
m6502 Emulator: Implementation and Unit Test - DEY_IMP
m6502 Emulator: Implementation and Unit Test - INX_IMP
m6502 Emulator: Implementation and Unit Test - INY_IMP

### 2025-01-25:
m6502 Emulator: Implementation and Unit Test - LDX_IM, LDX_ZP, LDX_ZPY, LDX_ABS,  LDX_ABSY
m6502 Emulator: Implementation and Unit Test - LDY_IM, LDY_ZP, LDY_ZPX, LDY_ABS,  LDY_ABSX
m6502 Emulator: Implementation and Unit Test - NOP
m6502 Emulator: Implementation and Unit Test - INC_ZP, INC_ZPX, INC_ABS, INC_ABSX

### 2025-01-19:
Reorg Files and Added CMake

## 2025-01-18:
m6502 Emulator: Implementation and Unit Test - LDA_IM, LDA_ZP, LDA_ZPX, LDA_ABS, LDA_ABSX, LDA_ABSY, LDA_INDX, LDA_INDY
Added base class for m6502