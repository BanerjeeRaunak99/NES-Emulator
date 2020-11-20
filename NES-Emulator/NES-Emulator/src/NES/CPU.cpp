#include "CPU.h"
#include "stdafx.h"

namespace nes
{
	CPU::CPU()
		: m_memory{}, m_a(0x00), m_x(0x00), m_y(0x00), m_status(0x00), m_sp(0x00), m_pc(0x00)
	{
		using a = CPU;
		lookup =
		{
			{ "BRK", &a::BRK, &a::IMM, 7 },{ "ORA", &a::ORA, &a::IZX, 6 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 3 },{ "ORA", &a::ORA, &a::ZP0, 3 },{ "ASL", &a::ASL, &a::ZP0, 5 },{ "???", &a::XXX, &a::IMP, 5 },{ "PHP", &a::PHP, &a::IMP, 3 },{ "ORA", &a::ORA, &a::IMM, 2 },{ "ASL", &a::ASL, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::NOP, &a::IMP, 4 },{ "ORA", &a::ORA, &a::ABS, 4 },{ "ASL", &a::ASL, &a::ABS, 6 },{ "???", &a::XXX, &a::IMP, 6 },
			{ "BPL", &a::BPL, &a::REL, 2 },{ "ORA", &a::ORA, &a::IZY, 5 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 4 },{ "ORA", &a::ORA, &a::ZPX, 4 },{ "ASL", &a::ASL, &a::ZPX, 6 },{ "???", &a::XXX, &a::IMP, 6 },{ "CLC", &a::CLC, &a::IMP, 2 },{ "ORA", &a::ORA, &a::ABY, 4 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 7 },{ "???", &a::NOP, &a::IMP, 4 },{ "ORA", &a::ORA, &a::ABX, 4 },{ "ASL", &a::ASL, &a::ABX, 7 },{ "???", &a::XXX, &a::IMP, 7 },
			{ "JSR", &a::JSR, &a::ABS, 6 },{ "AND", &a::AND, &a::IZX, 6 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "BIT", &a::BIT, &a::ZP0, 3 },{ "AND", &a::AND, &a::ZP0, 3 },{ "ROL", &a::ROL, &a::ZP0, 5 },{ "???", &a::XXX, &a::IMP, 5 },{ "PLP", &a::PLP, &a::IMP, 4 },{ "AND", &a::AND, &a::IMM, 2 },{ "ROL", &a::ROL, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 2 },{ "BIT", &a::BIT, &a::ABS, 4 },{ "AND", &a::AND, &a::ABS, 4 },{ "ROL", &a::ROL, &a::ABS, 6 },{ "???", &a::XXX, &a::IMP, 6 },
			{ "BMI", &a::BMI, &a::REL, 2 },{ "AND", &a::AND, &a::IZY, 5 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 4 },{ "AND", &a::AND, &a::ZPX, 4 },{ "ROL", &a::ROL, &a::ZPX, 6 },{ "???", &a::XXX, &a::IMP, 6 },{ "SEC", &a::SEC, &a::IMP, 2 },{ "AND", &a::AND, &a::ABY, 4 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 7 },{ "???", &a::NOP, &a::IMP, 4 },{ "AND", &a::AND, &a::ABX, 4 },{ "ROL", &a::ROL, &a::ABX, 7 },{ "???", &a::XXX, &a::IMP, 7 },
			{ "RTI", &a::RTI, &a::IMP, 6 },{ "EOR", &a::EOR, &a::IZX, 6 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 3 },{ "EOR", &a::EOR, &a::ZP0, 3 },{ "LSR", &a::LSR, &a::ZP0, 5 },{ "???", &a::XXX, &a::IMP, 5 },{ "PHA", &a::PHA, &a::IMP, 3 },{ "EOR", &a::EOR, &a::IMM, 2 },{ "LSR", &a::LSR, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 2 },{ "JMP", &a::JMP, &a::ABS, 3 },{ "EOR", &a::EOR, &a::ABS, 4 },{ "LSR", &a::LSR, &a::ABS, 6 },{ "???", &a::XXX, &a::IMP, 6 },
			{ "BVC", &a::BVC, &a::REL, 2 },{ "EOR", &a::EOR, &a::IZY, 5 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 4 },{ "EOR", &a::EOR, &a::ZPX, 4 },{ "LSR", &a::LSR, &a::ZPX, 6 },{ "???", &a::XXX, &a::IMP, 6 },{ "CLI", &a::CLI, &a::IMP, 2 },{ "EOR", &a::EOR, &a::ABY, 4 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 7 },{ "???", &a::NOP, &a::IMP, 4 },{ "EOR", &a::EOR, &a::ABX, 4 },{ "LSR", &a::LSR, &a::ABX, 7 },{ "???", &a::XXX, &a::IMP, 7 },
			{ "RTS", &a::RTS, &a::IMP, 6 },{ "ADC", &a::ADC, &a::IZX, 6 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 3 },{ "ADC", &a::ADC, &a::ZP0, 3 },{ "ROR", &a::ROR, &a::ZP0, 5 },{ "???", &a::XXX, &a::IMP, 5 },{ "PLA", &a::PLA, &a::IMP, 4 },{ "ADC", &a::ADC, &a::IMM, 2 },{ "ROR", &a::ROR, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 2 },{ "JMP", &a::JMP, &a::IND, 5 },{ "ADC", &a::ADC, &a::ABS, 4 },{ "ROR", &a::ROR, &a::ABS, 6 },{ "???", &a::XXX, &a::IMP, 6 },
			{ "BVS", &a::BVS, &a::REL, 2 },{ "ADC", &a::ADC, &a::IZY, 5 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 4 },{ "ADC", &a::ADC, &a::ZPX, 4 },{ "ROR", &a::ROR, &a::ZPX, 6 },{ "???", &a::XXX, &a::IMP, 6 },{ "SEI", &a::SEI, &a::IMP, 2 },{ "ADC", &a::ADC, &a::ABY, 4 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 7 },{ "???", &a::NOP, &a::IMP, 4 },{ "ADC", &a::ADC, &a::ABX, 4 },{ "ROR", &a::ROR, &a::ABX, 7 },{ "???", &a::XXX, &a::IMP, 7 },
			{ "???", &a::NOP, &a::IMP, 2 },{ "STA", &a::STA, &a::IZX, 6 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 6 },{ "STY", &a::STY, &a::ZP0, 3 },{ "STA", &a::STA, &a::ZP0, 3 },{ "STX", &a::STX, &a::ZP0, 3 },{ "???", &a::XXX, &a::IMP, 3 },{ "DEY", &a::DEY, &a::IMP, 2 },{ "???", &a::NOP, &a::IMP, 2 },{ "TXA", &a::TXA, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 2 },{ "STY", &a::STY, &a::ABS, 4 },{ "STA", &a::STA, &a::ABS, 4 },{ "STX", &a::STX, &a::ABS, 4 },{ "???", &a::XXX, &a::IMP, 4 },
			{ "BCC", &a::BCC, &a::REL, 2 },{ "STA", &a::STA, &a::IZY, 6 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 6 },{ "STY", &a::STY, &a::ZPX, 4 },{ "STA", &a::STA, &a::ZPX, 4 },{ "STX", &a::STX, &a::ZPY, 4 },{ "???", &a::XXX, &a::IMP, 4 },{ "TYA", &a::TYA, &a::IMP, 2 },{ "STA", &a::STA, &a::ABY, 5 },{ "TXS", &a::TXS, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 5 },{ "???", &a::NOP, &a::IMP, 5 },{ "STA", &a::STA, &a::ABX, 5 },{ "???", &a::XXX, &a::IMP, 5 },{ "???", &a::XXX, &a::IMP, 5 },
			{ "LDY", &a::LDY, &a::IMM, 2 },{ "LDA", &a::LDA, &a::IZX, 6 },{ "LDX", &a::LDX, &a::IMM, 2 },{ "???", &a::XXX, &a::IMP, 6 },{ "LDY", &a::LDY, &a::ZP0, 3 },{ "LDA", &a::LDA, &a::ZP0, 3 },{ "LDX", &a::LDX, &a::ZP0, 3 },{ "???", &a::XXX, &a::IMP, 3 },{ "TAY", &a::TAY, &a::IMP, 2 },{ "LDA", &a::LDA, &a::IMM, 2 },{ "TAX", &a::TAX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 2 },{ "LDY", &a::LDY, &a::ABS, 4 },{ "LDA", &a::LDA, &a::ABS, 4 },{ "LDX", &a::LDX, &a::ABS, 4 },{ "???", &a::XXX, &a::IMP, 4 },
			{ "BCS", &a::BCS, &a::REL, 2 },{ "LDA", &a::LDA, &a::IZY, 5 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 5 },{ "LDY", &a::LDY, &a::ZPX, 4 },{ "LDA", &a::LDA, &a::ZPX, 4 },{ "LDX", &a::LDX, &a::ZPY, 4 },{ "???", &a::XXX, &a::IMP, 4 },{ "CLV", &a::CLV, &a::IMP, 2 },{ "LDA", &a::LDA, &a::ABY, 4 },{ "TSX", &a::TSX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 4 },{ "LDY", &a::LDY, &a::ABX, 4 },{ "LDA", &a::LDA, &a::ABX, 4 },{ "LDX", &a::LDX, &a::ABY, 4 },{ "???", &a::XXX, &a::IMP, 4 },
			{ "CPY", &a::CPY, &a::IMM, 2 },{ "CMP", &a::CMP, &a::IZX, 6 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "CPY", &a::CPY, &a::ZP0, 3 },{ "CMP", &a::CMP, &a::ZP0, 3 },{ "DEC", &a::DEC, &a::ZP0, 5 },{ "???", &a::XXX, &a::IMP, 5 },{ "INY", &a::INY, &a::IMP, 2 },{ "CMP", &a::CMP, &a::IMM, 2 },{ "DEX", &a::DEX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 2 },{ "CPY", &a::CPY, &a::ABS, 4 },{ "CMP", &a::CMP, &a::ABS, 4 },{ "DEC", &a::DEC, &a::ABS, 6 },{ "???", &a::XXX, &a::IMP, 6 },
			{ "BNE", &a::BNE, &a::REL, 2 },{ "CMP", &a::CMP, &a::IZY, 5 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 4 },{ "CMP", &a::CMP, &a::ZPX, 4 },{ "DEC", &a::DEC, &a::ZPX, 6 },{ "???", &a::XXX, &a::IMP, 6 },{ "CLD", &a::CLD, &a::IMP, 2 },{ "CMP", &a::CMP, &a::ABY, 4 },{ "NOP", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 7 },{ "???", &a::NOP, &a::IMP, 4 },{ "CMP", &a::CMP, &a::ABX, 4 },{ "DEC", &a::DEC, &a::ABX, 7 },{ "???", &a::XXX, &a::IMP, 7 },
			{ "CPX", &a::CPX, &a::IMM, 2 },{ "SBC", &a::SBC, &a::IZX, 6 },{ "???", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "CPX", &a::CPX, &a::ZP0, 3 },{ "SBC", &a::SBC, &a::ZP0, 3 },{ "INC", &a::INC, &a::ZP0, 5 },{ "???", &a::XXX, &a::IMP, 5 },{ "INX", &a::INX, &a::IMP, 2 },{ "SBC", &a::SBC, &a::IMM, 2 },{ "NOP", &a::NOP, &a::IMP, 2 },{ "???", &a::SBC, &a::IMP, 2 },{ "CPX", &a::CPX, &a::ABS, 4 },{ "SBC", &a::SBC, &a::ABS, 4 },{ "INC", &a::INC, &a::ABS, 6 },{ "???", &a::XXX, &a::IMP, 6 },
			{ "BEQ", &a::BEQ, &a::REL, 2 },{ "SBC", &a::SBC, &a::IZY, 5 },{ "???", &a::XXX, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 8 },{ "???", &a::NOP, &a::IMP, 4 },{ "SBC", &a::SBC, &a::ZPX, 4 },{ "INC", &a::INC, &a::ZPX, 6 },{ "???", &a::XXX, &a::IMP, 6 },{ "SED", &a::SED, &a::IMP, 2 },{ "SBC", &a::SBC, &a::ABY, 4 },{ "NOP", &a::NOP, &a::IMP, 2 },{ "???", &a::XXX, &a::IMP, 7 },{ "???", &a::NOP, &a::IMP, 4 },{ "SBC", &a::SBC, &a::ABX, 4 },{ "INC", &a::INC, &a::ABX, 7 },{ "???", &a::XXX, &a::IMP, 7 },
		};
	}

	void CPU::ConnectBus(Bus* bus)
	{
		m_bus = bus;
	}

	uint8_t CPU::Read(const uint16_t address) const
	{
		return m_bus->read(address);
	}

	void CPU::Write(const uint16_t address, const uint8_t data) const
	{
		m_bus->write(address, data);
	}

	uint8_t CPU::GetFlag(const FLAGS flags) const
	{
		return ((m_status & flags) > 0) ? 1 : 0;
	}

	void CPU::SetFlag(FLAGS flags, bool value)
	{
		if ( value )
			m_status |= flags;
		else
			m_status &= ~flags;
	}
	void CPU::Clock()
	{
		if ( m_cycles == 0 )
		{
			m_opcode = Read(m_pc++);
			//extract number of cycles from lookup table
			m_cycles = lookup[m_opcode].cycles;
			uint8_t additionalcycle1 = (this->*lookup[m_opcode].addrmode)();
			uint8_t additionalcycle2 = (this->*lookup[m_opcode].operate)();
			m_cycles += (additionalcycle1 & additionalcycle2);
		}
		m_cycles--;
	}

	//Addressing modes
	uint8_t CPU::IMP()
	{
		m_fetched = m_a;
		return 0;
	}

	uint8_t CPU::IMM()
	{
		m_addr_abs = m_pc++;
		return 0;
	}

	uint8_t CPU::ZP0()
	{
		m_addr_abs = Read(m_pc);
		return 0;
	}

	uint8_t CPU::ZPX()
	{
		m_addr_abs = Read(m_pc) + m_x;
		m_pc++;
		m_addr_abs &= 0x00FF;
		return 0;
	}

	uint8_t CPU::ZPY()
	{
		m_addr_abs = Read(m_pc) + m_y;
		m_pc++;
		m_addr_abs &= 0x00FF;
		return 0;
	}

	uint8_t CPU::ABS()
	{
		uint8_t low = Read(m_pc++);
		uint8_t high = Read(m_pc++);
		m_addr_abs = (high << 8) | low;
		return 0;

	}

	uint8_t CPU::ABX()
	{
		uint8_t low = Read(m_pc++);
		uint8_t high = Read(m_pc++);
		m_addr_abs = (high << 8) | low;
		m_addr_abs += m_x;
		if ( (m_addr_abs & 0xFF00) != (high << 8) )
			return 1;
		else
			return 0;

	}

	uint8_t CPU::ABY()
	{
		uint8_t low = Read(m_pc++);
		uint8_t high = Read(m_pc++);
		m_addr_abs = (high << 8) | low;
		m_addr_abs += m_y;
		if ( (m_addr_abs & 0xFF00) != (high << 8) )
			return 1;
		else
			return 0;

	}

	uint8_t CPU::IND()
	{
		uint8_t ptr_low = Read(m_pc++);
		uint8_t ptr_high = Read(m_pc++);
		uint16_t ptr = (ptr_high << 8) | ptr_low;

		if ( ptr_low == 0x00FF ) //bug in hardware
		{
			m_addr_abs = (Read(ptr & 0xFF00) << 8) | Read(ptr + 0);
		}
		else
		{
			m_addr_abs = (Read(ptr + 1) << 8) | Read(ptr + 0);
		}

		return 0;
	}

	uint8_t CPU::IZX()
	{
		uint16_t ptr = Read(m_pc++);
		uint16_t low = Read((uint16_t)(ptr + (uint16_t)m_x) & 0x00FF);
		uint16_t high = Read((uint16_t)(ptr + (uint16_t)m_x + 1) & 0x00FF);

		m_addr_abs = (high << 8) | low;

		return 0;
	}

	uint8_t CPU::IZY()
	{
		uint16_t ptr = Read(m_pc++);
		uint16_t low = Read(ptr & 0x00FF);
		uint16_t high = Read((ptr + 1) & 0x00FF);

		m_addr_abs = (high << 8) | low;
		m_addr_abs += m_y;

		if ( (m_addr_abs & 0xFF00) != (high << 8) )
			return 1;
		else
			return 0;
	}

	uint8_t CPU::REL()
	{
		m_addr_rel = Read(m_pc++);
		if ( m_addr_rel & 0x80 )
			m_addr_rel |= 0xFF00;
		return 0;
	}

	//Fetching
	uint8_t CPU::fetch()
	{
		if ( !(lookup[m_opcode].addrmode == &CPU::IMP) )
			m_fetched = Read(m_addr_abs);
		return m_fetched;

	}
	//Opcodes

	// Branching 
	uint8_t CPU::BCS()
	{
		if ( GetFlag(C) == 1 )
		{
			m_cycles++;
			m_addr_abs = m_pc + m_addr_rel;
			if ( (m_addr_abs & 0xFF00) != (m_pc & 0xFF00) )
				m_cycles++;
			m_pc = m_addr_abs;
		}
		return 0;
	}
	uint8_t CPU::BCC()
	{
		if ( GetFlag(C) == 0 )
		{
			m_cycles++;
			m_addr_abs = m_pc + m_addr_rel;
			if ( (m_addr_abs & 0xFF00) != (m_pc & 0xFF00) )
				m_cycles++;
			m_pc = m_addr_abs;
		}
		return 0;
	}
	uint8_t CPU::BMI()
	{
		if ( GetFlag(N) == 1 )
		{
			m_cycles++;
			m_addr_abs = m_pc + m_addr_rel;
			if ( (m_addr_abs & 0xFF00) != (m_pc & 0xFF00) )
				m_cycles++;
			m_pc = m_addr_abs;
		}
		return 0;
	}
	uint8_t CPU::BPL()
	{
		if ( GetFlag(N) == 0 )
		{
			m_cycles++;
			m_addr_abs = m_pc + m_addr_rel;
			if ( (m_addr_abs & 0xFF00) != (m_pc & 0xFF00) )
				m_cycles++;
			m_pc = m_addr_abs;
		}
		return 0;
	}
	uint8_t CPU::BEQ()
	{
		if ( GetFlag(Z) == 1 )
		{
			m_cycles++;
			m_addr_abs = m_pc + m_addr_rel;
			if ( (m_addr_abs & 0xFF00) != (m_pc & 0xFF00) )
				m_cycles++;
			m_pc = m_addr_abs;
		}
		return 0;
	}
	uint8_t CPU::BNE()
	{
		if ( GetFlag(Z) == 0 )
		{
			m_cycles++;
			m_addr_abs = m_pc + m_addr_rel;
			if ( (m_addr_abs & 0xFF00) != (m_pc & 0xFF00) )
				m_cycles++;
			m_pc = m_addr_abs;
		}
		return 0;
	}
	uint8_t CPU::BVC()
	{
		if ( GetFlag(V) == 0 )
		{
			m_cycles++;
			m_addr_abs = m_pc + m_addr_rel;
			if ( (m_addr_abs & 0xFF00) != (m_pc & 0xFF00) )
				m_cycles++;
			m_pc = m_addr_abs;
		}
		return 0;
	}
	uint8_t CPU::BVS()
	{
		if ( GetFlag(V) == 1 )
		{
			m_cycles++;
			m_addr_abs = m_pc + m_addr_rel;
			if ( (m_addr_abs & 0xFF00) != (m_pc & 0xFF00) )
				m_cycles++;
			m_pc = m_addr_abs;
		}
		return 0;
	}
	//Register manipulations
	uint8_t CPU::CLC()
	{
		SetFlag(C, false);
		return 0;
	}

	uint8_t CPU::SEC()
	{
		SetFlag(C, true);
		return 0;
	}
	uint8_t CPU::CLD()
	{
		SetFlag(D, false);
		return 0;
	}
	uint8_t CPU::SED()
	{
		SetFlag(D, true);
		return 0;
	}
	uint8_t CPU::CLI()
	{
		SetFlag(I, false);
		return 0;
	}
	uint8_t CPU::SEI()
	{
		SetFlag(I, true);
		return 0;
	}

	uint8_t CPU::CLV()
	{
		SetFlag(V, false);
		return 0;
	}
	uint8_t CPU::CMP()
	{
		uint16_t res = (uint16_t)m_a - (uint16_t)m_fetched;
		SetFlag(C, m_a >= m_fetched);
		SetFlag(Z, (res & 0x00FF) == 0x0000);
		SetFlag(N, (res & 0x0080));
		return 0;
	}
	uint8_t CPU::CPX()
	{
		uint16_t res = (uint16_t)m_x - (uint16_t)m_fetched;
		SetFlag(C, m_x >= m_fetched);
		SetFlag(Z, (res & 0x00FF) == 0x0000);
		SetFlag(N, (res & 0x0080));
		return 0;
	}
	uint8_t CPU::CPY()
	{
		uint16_t res = (uint16_t)m_y - (uint16_t)m_fetched;
		SetFlag(C, m_y >= m_fetched);
		SetFlag(Z, (res & 0x00FF) == 0x0000);
		SetFlag(N, (res & 0x0080));
		return 0;
	}
	//storage
	uint8_t CPU::LDA()
	{
		fetch();
		m_a = m_fetched;
		SetFlag(Z, m_a == 0x00);
		SetFlag(N, m_a & 0x80);
		return 1;

	}
	uint8_t CPU::LDX()
	{
		fetch();
		m_x = m_fetched;
		SetFlag(Z, m_x == 0x00);
		SetFlag(N, m_x & 0x80);
		return 1;

	}
	uint8_t CPU::LDY()
	{
		fetch();
		m_y = m_fetched;
		SetFlag(Z, m_y == 0x00);
		SetFlag(N, m_y & 0x80);
		return 1;

	}
	uint8_t CPU::STA()
	{
		Write(m_addr_abs, m_a);
		return 0;
	}
	uint8_t CPU::STX()
	{
		Write(m_addr_abs, m_x);
		return 0;
	}
	uint8_t CPU::STY()
	{
		Write(m_addr_abs, m_y);
		return 0;
	}
	uint8_t CPU::TAX()
	{
		m_x = m_a;
		SetFlag(Z, m_x == 0x00);
		SetFlag(N, m_x & 0x80);
		return 0;
	}
	uint8_t CPU::TAY()
	{
		m_y = m_a;
		SetFlag(Z, m_y == 0x00);
		SetFlag(N, m_y & 0x80);
		return 0;
	}
	uint8_t CPU::TSX()
	{
		m_x = m_sp;
		SetFlag(Z, m_x == 0x00);
		SetFlag(N, m_x & 0x80);
		return 0;
	}
	uint8_t CPU::TXA()
	{
		m_a = m_x;
		SetFlag(Z, m_a == 0x00);
		SetFlag(N, m_a & 0x80);
		return 0;
	}
	uint8_t CPU::TXS()
	{
		m_sp = m_x;
		SetFlag(Z, m_sp == 0x00);
		SetFlag(N, m_sp & 0x80);
		return 0;
	}
	uint8_t CPU::TYA()
	{
		m_a = m_y;
		SetFlag(Z, m_a == 0x00);
		SetFlag(N, m_a & 0x80);
		return 0;
	}





	// Math operations
	uint8_t CPU::ADC()
	{
		fetch();
		uint16_t res = (uint16_t)m_a + (uint16_t)m_fetched + (uint16_t)GetFlag(C);
		SetFlag(C, res > 255);
		SetFlag(Z, (res & 0x00FF) == 0);
		SetFlag(V, (~((uint16_t)m_a ^ (uint16_t)m_fetched) & ((uint16_t)m_a ^ (uint16_t)res)) & 0x0080);
		SetFlag(N, res & 0x80);
		m_a = res & 0x00FF;

		return 1;
	}

	uint8_t CPU::DEC()
	{
		fetch();
		uint16_t res = m_fetched - 1;
		Write(m_addr_abs, res & 0x00FF);
		SetFlag(Z, (res & 0x00FF) == 0x0000);
		SetFlag(N, res & 0x0080);
		return 0;
	}

	uint8_t CPU::DEX()
	{
		m_x--;
		SetFlag(Z, m_x == 0x00);
		SetFlag(N, m_x & 0x80);
		return 0;
	}

	uint8_t CPU::DEY()
	{
		m_y--;
		SetFlag(Z, m_y == 0x00);
		SetFlag(N, m_y & 0x80);
		return 0;
	}

	uint8_t CPU::INC()
	{
		fetch();
		uint16_t res = m_fetched + 1;
		Write(m_addr_abs, res & 0x00FF);
		SetFlag(Z, (res & 0x00FF) == 0x0000);
		SetFlag(N, res & 0x0080);
		return 0;
	}

	uint8_t CPU::INX()
	{
		m_x++;
		SetFlag(Z, m_x == 0x00);
		SetFlag(N, m_x & 0x80);
		return 0;
	}

	uint8_t CPU::INY()
	{
		m_y++;
		SetFlag(Z, m_y == 0x00);
		SetFlag(N, m_y & 0x80);
		return 0;
	}

	uint8_t CPU::SBC()
	{
		fetch();
		uint16_t value = ((uint16_t)m_fetched) ^ 0x00FF;

		// Notice this is exactly the same as addition from here!
		uint16_t res = (uint16_t)m_a + value + (uint16_t)GetFlag(C);
		SetFlag(C, res & 0xFF00);
		SetFlag(Z, ((res & 0x00FF) == 0));
		SetFlag(V, (res ^ (uint16_t)m_a) & (res ^ value) & 0x0080);
		SetFlag(N, res & 0x0080);
		m_a = res & 0x00FF;
		return 1;
	}
	//Bitwise 
	uint8_t CPU::AND()
	{
		fetch();
		m_a = m_a & m_fetched;
		SetFlag(Z, m_a == 0x00);
		SetFlag(N, m_a & 0x80);
		return 1;
	}
	uint8_t CPU::ASL()
	{
		fetch();
		uint16_t temp = (uint16_t)m_fetched << 1;
		SetFlag(C, (temp & 0xFF00) > 0);
		SetFlag(Z, (temp & 0x00FF) == 0x00);
		SetFlag(N, (temp & 0x80));
		if ( lookup[m_opcode].addrmode == &CPU::IMP )
			m_a = temp & 0x00FF;
		else
			Write(m_addr_abs, temp & 0x00FF);
		return 0;
	}
	uint8_t CPU::LSR()
	{
		fetch();
		SetFlag(C, (m_fetched & 0x0001));
		uint8_t temp = m_fetched >> 1;
		SetFlag(Z, (temp & 0x00FF) == 0x00);
		SetFlag(N, (temp & 0x80));
		if ( lookup[m_opcode].addrmode == &CPU::IMP )
			m_a = temp & 0x00FF;
		else
			Write(m_addr_abs, temp & 0x00FF);
		return 0;
	}
	uint8_t CPU::EOR()
	{
		fetch();
		m_a = m_a ^ m_fetched;
		SetFlag(Z, m_a == 0x00);
		SetFlag(N, m_a & 0x80);
		return 1;
	}
	uint8_t CPU::ORA()
	{
		fetch();
		m_a = m_a | m_fetched;
		SetFlag(Z, m_a == 0x00);
		SetFlag(N, m_a & 0x80);
		return 1;
	}
	uint8_t CPU::BIT()
	{
		fetch();
		uint8_t temp = m_a & m_fetched;
		SetFlag(Z, (temp & 0x00FF) == 0x00);
		SetFlag(N, m_fetched & (1 << 7));
		SetFlag(V, m_fetched & (1 << 6));
		return 0;

	}
	uint8_t CPU::ROL()
	{
		fetch();
		uint16_t temp = ((uint16_t)m_fetched << 1) | GetFlag(C);
		SetFlag(C, (temp & 0xFF00) > 0);
		SetFlag(Z, (temp & 0x00FF) == 0x00);
		SetFlag(N, (temp & 0x0080));
		if ( lookup[m_opcode].addrmode == &CPU::IMP )
			m_a = temp & 0x00FF;
		else
			Write(m_addr_abs, temp & 0x00FF);
		return 0;
	}
	uint8_t CPU::ROL()
	{
		fetch();
		uint16_t temp = (uint16_t)(GetFlag(C) << 7) | (m_fetched >> 1);
		SetFlag(C, m_fetched & 0x01);
		SetFlag(Z, (temp & 0x00FF) == 0x00);
		SetFlag(N, (temp & 0x0080));
		if ( lookup[m_opcode].addrmode == &CPU::IMP )
			m_a = temp & 0x00FF;
		else
			Write(m_addr_abs, temp & 0x00FF);
		return 0;
	}
	//Stack
	uint8_t CPU::PHA()
	{
		Write(0x0100 + m_sp, m_a);
		m_sp--;
		return 0;

	}
	uint8_t CPU::PHP()
	{
		Write(0x0100 + m_sp, m_status | B0 | B1);
		SetFlag(B0, 0);
		SetFlag(B1, 0);
		m_sp--;
		return 0;
	}
	uint8_t CPU::PLA()
	{
		m_sp++;
		m_a = Read(0x0100 + m_sp);
		SetFlag(Z, m_a == 0x00);
		SetFlag(N, m_a & 0x80);
		return 0;

	}
	uint8_t CPU::PLP()
	{
		m_sp++;
		m_status = Read(0x0100 + m_sp);
		SetFlag(B1, 1);
		return 0;
	}


	// Jump opcodes
	uint8_t CPU::JMP()
	{
		m_pc = m_addr_abs;
		return 0;
	}

	uint8_t CPU::JSR()
	{
		m_pc--;
		Write(0x0100 + m_sp, (m_pc >> 8) & 0x00FF);
		m_sp--;
		Write(0x0100 + m_sp, m_pc & 0x00FF);
		m_sp--;

		m_pc = m_addr_abs;
		return 0;
	}

	uint8_t CPU::RTI()
	{
		m_sp++;
		m_status = Read(0x0100 + m_sp);
		m_status &= ~B0;
		m_status &= ~B1;

		m_sp++;
		m_pc = (uint16_t)Read(0x0100 + m_sp);
		m_sp++;
		m_pc |= (uint16_t)Read(0x0100 + m_sp) << 8;
		return 0;
	}

	uint8_t CPU::RTS()
	{
		m_sp++;
		m_pc = (uint16_t)Read(0x0100 + m_sp);
		m_sp++;
		m_pc |= (uint16_t)Read(0x0100 + m_sp) << 8;
		m_pc++;
		return 0;
	}

	// System Opcodes
	uint8_t CPU::BRK()
	{
		m_pc++;

		SetFlag(I, 1);
		Write(0x0100 + m_sp, (m_pc >> 8) & 0x00FF);
		m_sp--;
		Write(0x0100 + m_sp, m_pc & 0x00FF);
		m_sp--;

		SetFlag(B0, 1);
		Write(0x0100 + m_sp, m_status);
		m_sp--;
		SetFlag(B0, 0);

		m_pc = (uint16_t)Read(0xFFFE) | ((uint16_t)Read(0xFFFF) << 8);
		return 0;
	}

	uint8_t CPU::NOP()
	{
		switch ( m_opcode )
		{
			case 0x1C:
			case 0x3C:
			case 0x5C:
			case 0x7C:
			case 0xDC:
			case 0xFC:
				return 1;
				break;
		}
		return 0;
	}
}
