#include "buffer.hpp"
#include "memory.h"

namespace stockTrader
{
	buffer_proxy::buffer_proxy(char *_entry) noexcept
	: m_entry(_entry)
	{}

	char& buffer_proxy::operator[](uint64 _col) noexcept
	{ return m_entry[_col]; }

	buffer::buffer(
		uint64 _cols,
		uint64 _rows
	) noexcept
		: m_rows(_rows)
		, m_cols(_cols)
	{
		m_data = new char[m_rows * m_cols];
		memset(m_data, ' ', sizeof(char) * m_rows * m_cols);
	}

	buffer::~buffer() noexcept
	{ delete[] m_data; }

	char buffer::at(
		uint64 _row,
		uint64 _col
	) noexcept
	{
		if (_row > m_rows) _row = m_rows;
		if (_col > m_cols) _col = m_cols;
		return m_data[(_row * m_cols) + _col];
	}

	uint64 buffer::getCols() noexcept
	{ return m_cols; }

	uint64 buffer::getRows() noexcept
	{ return m_rows; }

	buffer_proxy buffer::operator[](uint64 _row) noexcept
	{
		return buffer_proxy(m_data + (_row * m_cols));
	}
}
