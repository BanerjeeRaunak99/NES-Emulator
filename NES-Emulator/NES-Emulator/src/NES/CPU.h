#pragma once

#include "stdafx.h"
#include "Bus.h"

namespace NES
{
	class CPU
	{
	public:
		CPU();
		~CPU() = default;

		inline void ConnectBus(Bus* bus) { m_bus = bus; }

	private:
		// The main bus
		Bus* m_bus = nullptr;

		// Memory 2K
		uint8_t m_memory[2048];

		// Status flags enum
		enum FLAGS
		{
			C = (1 << 0),
			Z = (1 << 1),
			I = (1 << 2),
			D = (1 << 3),	// This one has no effect on the NES
			B0 = (1 << 4),	// LSB of the B flag
			B1 = (1 << 5),	// MSB of the B flag
			V = (1 << 6),
			N = (1 << 7),
		};

		// Stack pointer
		uint8_t m_sp;

		// Program counter
		uint16_t m_pc;

		// General purpose registers
		uint8_t m_a;
		uint8_t m_x;
		uint8_t m_y;

		// Status register
		uint8_t m_status;

		//Adressing Modes
		uint8_t IMP();	
		uint8_t IMM();
		uint8_t ZP0();	
		uint8_t ZPX();
		uint8_t ZPY();	
		uint8_t REL();
		uint8_t ABS();	
		uint8_t ABX();
		uint8_t ABY();	
		uint8_t IND();
		uint8_t IZX();	
		uint8_t IZY();

		//opcodes
		uint8_t ADC();	uint8_t AND();	uint8_t ASL();	uint8_t BCC();
		uint8_t BCS();	uint8_t BEQ();	uint8_t BIT();	uint8_t BMI();
		uint8_t BNE();	uint8_t BPL();	uint8_t BRK();	uint8_t BVC();
		uint8_t BVS();	uint8_t CLC();	uint8_t CLD();	uint8_t CLI();
		uint8_t CLV();	uint8_t CMP();	uint8_t CPX();	uint8_t CPY();
		uint8_t DEC();	uint8_t DEX();	uint8_t DEY();	uint8_t EOR();
		uint8_t INC();	uint8_t INX();	uint8_t INY();	uint8_t JMP();
		uint8_t JSR();	uint8_t LDA();	uint8_t LDX();	uint8_t LDY();
		uint8_t LSR();	uint8_t NOP();	uint8_t ORA();	uint8_t PHA();
		uint8_t PHP();	uint8_t PLA();	uint8_t PLP();	uint8_t ROL();
		uint8_t ROR();	uint8_t RTI();	uint8_t RTS();	uint8_t SBC();
		uint8_t SEC();	uint8_t SED();	uint8_t SEI();	uint8_t STA();
		uint8_t STX();	uint8_t STY();	uint8_t TAX();	uint8_t TAY();
		uint8_t TSX();	uint8_t TXA();	uint8_t TXS();	uint8_t TYA();

		// Function handling Illegal opcodes
		uint8_t XXX();

		//External signals
		void clock(); //clock signal
		void reset(); //reset signal
		void irq(); // interupt resquest signal
		void nmi(); // non maskable interupt request signal

		//methods used to fetch data
		uint8_t fetch();
		uint8_t m_fetched;

		// Variables to store absoulte and relative addresses
		uint8_t m_addr_abs;
		uint8_t m_addr_rel;

		//variable for current opcode
		uint8_t m_opcode;

		//variable for number of cycles required
		uint8_t m_cycles;

		// Methods to read from and write to the bus
		uint8_t read(const uint16_t address) const;
		void write(const uint16_t address, const uint8_t data) const;

		// Methods for the status register
		uint8_t GetFlag(const FLAGS flags) const;
		void SetFlag(FLAGS flags, bool value);

		//struct to handle instructions
		struct INSTRUCTION 
		{
			std::string name;
			uint8_t(CPU::*operate)(void) = nullptr;
			uint8_t(CPU::*addrmode)(void) = nullptr;
			uint8_t cycles = 0;

		};
		std::vector<INSTRUCTION> lookup
	};
}


