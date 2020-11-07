#pragma once

#include "stdafx.h"

namespace NES
{
	class CPU
	{
	public:
		CPU();
		~CPU();

		bool LoadRom(const char* path);

	private:
		// memory 2K
		uint8_t m_memory[2048];

		// general purpose registers
		uint8_t m_a;
		uint8_t m_x;
		uint8_t m_y;

		// status register
		uint8_t m_p;

		// Stack pointer
		uint8_t m_sp;

		// Program counter
		uint16_t m_pc;
	};
}


