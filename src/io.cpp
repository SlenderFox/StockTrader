#include "io.hpp"
#include <iostream>

namespace stockTrader
{
	io::io() noexcept
	{
		bufferA = new buffer(buffVertical, buffHorizontal);
		bufferB = new buffer(buffVertical, buffHorizontal);
	}

	io::~io() noexcept
	{
		delete bufferA;
		delete bufferB;
	}

	io* io::get() noexcept
	{
		static io* inst = new io();
		return inst;
	}

	void io::swapBuffers() noexcept
	{
		if (activeBuffer == &bufferB)
		{
			activeBuffer = &bufferA;
			inactiveBuffer = &bufferB;
		}
		if (activeBuffer == &bufferA)
		{
			activeBuffer = &bufferB;
			inactiveBuffer = &bufferA;
		}
	}

	void io::draw() noexcept
	{
		static bool whichPrint = false;
		whichPrint = !whichPrint;
		if (whichPrint) std::cout << "Printing bufferA\n";
		else std::cout << "Printing bufferB\n";
		for (uint64 y = 0; y < buffVertical; ++y)
		{
			for (uint64 x = 0; x < buffHorizontal; ++x)
			{
				std::cout << y << x << (*inactiveBuffer)->at(y, x);
			}
			std::cout << '\n';
		}
		std::cout.flush();
	}

	void io::update(uint64 _val) noexcept
	{
		uint64 row = (uint64)((double)_val / (double)buffHorizontal);
		uint64 col = _val % buffHorizontal;
		std::cout << "Updating [" << row << "][" << col << "]\n";
		//(**activeBuffer)[row][col] = 'x';
		(*activeBuffer)->set(row, col, 'x');
		//++_val;
	}
}
