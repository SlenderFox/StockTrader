#pragma once
#include "company.hpp"

namespace io
{
	void flush() noexcept;

	void drawGraph(
		company* inCompanies,
		const uint8 inSelected,
		const uint32 inMaxValue
	) noexcept;

	void drawInfo(
		const company* inCompanies,
		const uint16 inDay,
		const int32 inMoney
	) noexcept;

	void drawConsole(
		const gameState inState,
		const std::string inInvalidMsg
	) noexcept;

	_NODISCARD
	bool endGame(
		const company* inCompanies,
		const int32 inMoney
	) noexcept;

	std::string convertToCash(int32 inMoney) noexcept;
}
