#include "io.hpp"
#include <iostream>

namespace stockTrader
{
	io::io() noexcept
	{
		buffer_a = new buffer(s_buffer_vertical, s_buffer_horizontal);
		buffer_b = new buffer(s_buffer_vertical, s_buffer_horizontal);
	}

	io::~io() noexcept
	{
		delete buffer_a;
		delete buffer_b;
	}

	io* io::get() noexcept
	{
		static io* inst = new io();
		return inst;
	}

	void io::swap_buffers() noexcept
	{
		if (active_buffer == &buffer_b)
		{
			active_buffer = &buffer_a;
			inactive_buffer = &buffer_b;
		}
		if (active_buffer == &buffer_a)
		{
			active_buffer = &buffer_b;
			inactive_buffer = &buffer_a;
		}
	}

	void io::draw() noexcept
	{
		static bool whichPrint = false;
		whichPrint = !whichPrint;
		if (whichPrint) std::cout << "Printing buffer_a\n";
		else std::cout << "Printing bufferB\n";
		for (uint64 y = 0; y < s_buffer_vertical; ++y)
		{
			for (uint64 x = 0; x < s_buffer_horizontal; ++x)
			{
				std::cout << y << x << (*inactive_buffer)->at(y, x);
			}
			std::cout << '\n';
		}
		std::cout.flush();
	}

	void io::update(uint64 _val) noexcept
	{
		uint64 row = (uint64)((double)_val / (double)s_buffer_horizontal);
		uint64 col = _val % s_buffer_horizontal;
		std::cout << "Updating [" << row << "][" << col << "]\n";
		//(**active_buffer)[row][col] = 'x';
		(*active_buffer)->set(row, col, 'x');
		//++_val;
	}
}
