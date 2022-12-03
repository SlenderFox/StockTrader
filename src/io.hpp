#pragma once
#include "Enums.hpp"
#include <string>
#include "Company.hpp"

namespace io
{
	void Flush() noexcept;

	void DrawGraph(
		Company* inCompanies,
		const uint8 inSelected,
		const uint32 inMaxValue
	) noexcept;

	void DrawInfo(
		const Company* inCompanies,
		const uint16 inDay,
		const int32 inMoney
	) noexcept;

	void DrawConsole(
		const GameState inState,
		const std::string inInvalidMsg
	) noexcept;

	_NODISCARD
	bool EndGame(
		const Company* inCompanies,
		const int32 inMoney
	) noexcept;

	std::string ConvertToCash(int32 pMoney) noexcept;
}
