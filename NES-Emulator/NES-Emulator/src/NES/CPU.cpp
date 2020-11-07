#include "CPU.h"
#include "stdafx.h"

namespace NES
{
	CPU::CPU()
		: m_memory{}, m_a(0), m_x(0), m_y(0), m_p(0), m_sp(0), m_pc(0)
	{}

	CPU::~CPU()
	{}

	uint8_t CPU::read(const uint16_t address) const
	{
		return bus->read(address);
	}

	void CPU::write(const uint16_t address, const uint8_t data)
	{
		bus->write(address, data);
	}

}
