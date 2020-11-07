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
		uint8_t read(const uint16_t address) const;
		void write(const uint16_t address, const uint8_t data);

	private:
		// The main bus
		Bus* m_bus = nullptr;

		// Memory 2K
		uint8_t m_memory[2048];

		// General purpose registers
		uint8_t m_a;
		uint8_t m_x;
		uint8_t m_y;

		// Status register
		uint8_t m_p;

		// Stack pointer
		uint8_t m_sp;

		// Program counter
		uint16_t m_pc;
	};
}


