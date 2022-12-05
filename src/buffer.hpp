#pragma once
#include "typeDefines.hpp"

namespace stockTrader
{
	class buffer_proxy
	{
		char* m_entry;

	public:
		buffer_proxy(char *_entry) noexcept;

		char& operator[](uint64 _col) noexcept;
	};

	class buffer
	{
		friend class buffer_proxy;

		char *m_data;
		uint64 m_rows, m_cols;

	public:
		buffer(
			uint64 _rows,
			uint64 _cols
		) noexcept;

		~buffer() noexcept;

		_NODISCARD
		char at(
			uint64 _row,
			uint64 _col
		) noexcept;

		_NODISCARD
		uint64 getRows() noexcept;

		_NODISCARD
		uint64 getCols() noexcept;

		buffer_proxy operator[](uint64 _row) noexcept;
	};
}
