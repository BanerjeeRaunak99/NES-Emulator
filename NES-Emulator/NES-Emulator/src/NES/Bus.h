#pragma once

#include "CPU.h"

namespace nes
{
	class Bus
	{
	public:
		Bus();
		~Bus();

		void write(const uint16_t addr, const uint8_t data);
		uint8_t read(const uint16_t addr) const;

	private:
		std::array<uint16_t, 64 * 1024> ram;
	};
}

