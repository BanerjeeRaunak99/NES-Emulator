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

		// General purpose registers
		uint8_t m_a;
		uint8_t m_x;
		uint8_t m_y;

		// Status register
		uint8_t m_status;

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

		// Methods to read from and write to the bus
		uint8_t read(const uint16_t address) const;
		void write(const uint16_t address, const uint8_t data) const;

		// Methods for the status register
		uint8_t GetFlag(const FLAGS flags) const;
		void SetFlag(FLAGS flags, bool value);
	};
}


