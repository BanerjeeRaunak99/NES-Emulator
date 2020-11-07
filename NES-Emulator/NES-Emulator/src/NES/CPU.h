#pragma once

// TODO: Implement CPU functionality
#include <stdint.h>

namespace NES
{
	class CPU
	{
	public:
		CPU();
		~CPU();

	private:
		[[nodiscard]] constexpr bool get() { return false; }

		/*memory 2K*/
		uint8_t memory[2048];


		/*general purpose registers*/
		uint8_t a;
		uint8_t x;
		uint8_t y;
		
		/*status register*/
		uint8_t p;

		/*Stack pointer*/
		uint8_t sp;

		/* Program counter */
		uint16_t pc;


	};
}


