#pragma once
#include "typeDefines.hpp"
#include "buffer.hpp"

namespace stockTrader
{
	class io
	{
		static constexpr uint64 buffVertical = 5;
		static constexpr uint64 buffHorizontal = 5;

		/**One buffer represents the current state of the screen.
		 * The other buffer is the one current being written to.
		 * The buffers are compared and the differences are drawn to screen */

		//char grid[buffVertical][buffHorizontal];

		// Memory pointers
		buffer *bufferA = nullptr;
		buffer *bufferB = nullptr;

		// Reference pointer
		buffer **activeBuffer = &bufferA;
		buffer **inactiveBuffer = &bufferB;

		io() noexcept;

	public:
		static io* get() noexcept;

		~io() noexcept;

		void swapBuffers() noexcept;
		void draw() noexcept;
		void update(uint64 _val) noexcept;
	};
}
