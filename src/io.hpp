#pragma once
#include "typeDefines.hpp"
#include "buffer.hpp"

namespace stockTrader
{
	class io
	{
		static constexpr uint64 buffVertical = 40;
		static constexpr uint64 buffHorizontal = 62;

		/**One buffer represents the current state of the screen.
		 * The other buffer is the one current being written to.
		 * The buffers are compared and the differences are drawn to screen */

		//char grid[buffVertical][buffHorizontal];

		// Memory pointers
		buffer *bufferA = nullptr;
		buffer *bufferB = nullptr;

		// Reference pointer
		buffer *activeBuffer = nullptr;
		buffer *inactiveBuffer = nullptr;

		io() noexcept;

	public:
		static io* get() noexcept;

		~io() noexcept;

		void swapBuffers() noexcept;
		void draw() noexcept;
		void update() noexcept;
	};
}
