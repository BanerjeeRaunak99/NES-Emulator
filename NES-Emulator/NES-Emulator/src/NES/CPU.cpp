#include "CPU.h"
#include "stdafx.h"

namespace NES
{
	CPU::CPU()
		: m_memory{}, m_a(0x00), m_x(0x00), m_y(0x00), m_status(0x00), m_sp(0x00), m_pc(0x00)
	{}

	CPU::~CPU()
	{}

	uint8_t CPU::read(const uint16_t address) const
	{
		return m_bus->read(address);
	}

	void CPU::write(const uint16_t address, const uint8_t data) const
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

}
