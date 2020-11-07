#include "CPU.h"
#include "stdafx.h"

namespace NES
{
	CPU::CPU()
		: m_memory{}, m_a(0), m_x(0), m_y(0), m_p(0), m_sp(0), m_pc(0)
	{

	}

	CPU::~CPU()
	{}

	bool CPU::LoadRom(const char* path)
	{
		return false;
	}

}
