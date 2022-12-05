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
		if (activeBuffer == bufferB)
		{
			activeBuffer = bufferA;
			inactiveBuffer = bufferB;
		}
		if (activeBuffer == bufferA)
		{
			activeBuffer = bufferB;
			inactiveBuffer = bufferA;
		}
	}

	void io::draw() noexcept
	{
		for (uint64 y = 0; y < buffVertical; ++y)
		{
			std::cout << 'V' << y;
			for (uint64 x = 0; x < buffHorizontal; ++x)
			{
				std::cout << 'H' << x << (*bufferA)[y][x];
			}
			std::cout << '\n';
		}
		std::cout.flush();
	}

	void io::update() noexcept
	{
		//static int place = 0;
	}
}
