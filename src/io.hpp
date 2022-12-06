#pragma once
#include "typeDefines.hpp"
#include "buffer.hpp"

namespace stockTrader
{
	class io
	{
		static constexpr uint64 s_buffer_vertical = 5;
		static constexpr uint64 s_buffer_horizontal = 5;

		/**One buffer represents the current state of the screen.
		 * The other buffer is the one current being written to.
		 * The buffers are compared and the differences are drawn to screen */

		// Memory pointers
		buffer *buffer_a = nullptr;
		buffer *buffer_b = nullptr;

		// Reference pointer
		buffer **active_buffer = &buffer_a;
		buffer **inactive_buffer = &buffer_b;

		io() noexcept;

	public:
		static io* get() noexcept;

		~io() noexcept;

		void swap_buffers() noexcept;
		void draw() noexcept;
		void update(uint64 _val) noexcept;
	};
}
