#include "buffer.hpp"
#include "memory.h"

namespace stockTrader
{
	buffer_proxy::buffer_proxy(char *_entry) noexcept
	: m_entry(_entry)
	{}

	char& buffer_proxy::operator[](uint64 _column) noexcept
	{ return m_entry[_column]; }

	buffer::buffer(
		uint64 _columns,
		uint64 _rows
	) noexcept
		: m_rows(_rows)
		, m_columns(_columns)
	{
		m_data = new char[m_rows * m_columns];
		memset(m_data, ' ', sizeof(char) * m_rows * m_columns);
	}

	buffer::~buffer() noexcept
	{ delete[] m_data; }

	void buffer::set(
		uint64 _row,
		uint64 _column,
		char _val
	) noexcept
	{
		if (_row >= m_rows) _row = m_rows-1;
		if (_column >= m_columns) _column = m_columns-1;
		m_data[(_row * m_columns) + _column] = _val;
	}

	char buffer::at(
		uint64 _row,
		uint64 _column
	) noexcept
	{
		if (_row >= m_rows) _row = m_rows-1;
		if (_column >= m_columns) _column = m_columns-1;
		return m_data[(_row * m_columns) + _column];
	}

	uint64 buffer::get_columns() noexcept
	{ return m_columns; }

	uint64 buffer::get_rows() noexcept
	{ return m_rows; }

	buffer_proxy buffer::operator[](uint64 _row) noexcept
	{ return buffer_proxy(m_data + (_row * m_columns)); }
}
