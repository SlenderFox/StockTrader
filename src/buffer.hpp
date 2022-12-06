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
		uint64 m_rows, m_columns;

	public:
		buffer(
			uint64 _rows,
			uint64 _columns
		) noexcept;

		~buffer() noexcept;

		void set(
			uint64 _row,
			uint64 _column,
			char _val
		) noexcept;

		_NODISCARD
		char at(
			uint64 _row,
			uint64 _column
		) noexcept;

		_NODISCARD
		uint64 get_rows() noexcept;

		_NODISCARD
		uint64 get_columns() noexcept;

		buffer_proxy operator[](uint64 _row) noexcept;
	};
}
