#include "io.hpp"
#include <memory.h>

namespace stockTrader
{
	io::buffer::buffer()
	{
		memset(&raw, ' ', sizeof(raw));
	}

	io::io() noexcept
	{
		// Start by loading bufferA
		swapBuffers();
	}

	io::~io() noexcept
	{
	}

	io *io::get() noexcept
	{
		static io* inst = new io();
		return inst;
	}

	void io::swapBuffers() noexcept
	{
		if (activeBuffer == bufferA.raw || !activeBuffer) { activeBuffer = bufferA.raw; }
		if (activeBuffer == bufferA.raw)  { activeBuffer = bufferB.raw; }
	}
}
