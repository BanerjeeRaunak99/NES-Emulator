#include "Bus.h"

namespace nes
{
	Bus::Bus() : ram{}
	{}

	Bus::~Bus()
	{

	}

	void Bus::write(const uint16_t addr, const uint8_t data)
	{
		ram[addr] = data;
	}

	uint8_t Bus::read(const uint16_t addr) const
	{
		return ram[addr];
	}

}
