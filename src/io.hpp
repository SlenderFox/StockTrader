#pragma once
#include "typeDefines.hpp"

namespace stockTrader
{
	class io
	{
		static constexpr uint8 buffVertical = 53;
		static constexpr uint8 buffHorizontal = 70;

		/**One buffer represents the current state of the screen.
		 * The other buffer is the one current being written to.
		 * The buffers are compared and the differences are drawn to screen
		 */
		union buffer
		{
			char raw[buffVertical * buffHorizontal];
			char grid[buffVertical][buffHorizontal];
			buffer();
		};

		buffer bufferA = buffer();
		buffer bufferB = buffer();

		// Reference pointer
		char *activeBuffer = nullptr;

		io() noexcept;

	public:
		static io *get() noexcept;

		~io() noexcept;

		void swapBuffers() noexcept;
	};
}
