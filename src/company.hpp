#pragma once
#include "enums.hpp"
#include <string>

namespace stockTrader
{
	class company
	{
		companyType m_type = companyType::undefined;
		std::string m_name = "undefined";
		uint32 m_ownedStocks = 0;
		uint32 m_currentValue = 0;
		// An array of previous values used to generate the graph (the width is correct)
		uint32 m_companyData[WIDTH - 1] = {};

	public:
		company();
		~company() {}

		/** Starts up the company with default values */
		void initialiseCompany(
			companyType inType,
			std::string inName,
			uint32 inStartValue
		);

		void updateCompanyValue(
			float inMin,
			float inMax
		);

		char getDataFromArray(
			const uint32 inMaxValue,
			const uint8 inHorizontal,
			uint8 inVertical
		) noexcept;

		/** Adds or removes owned stocks */
		void modifyOwnedStocks(uint32 inDifference);
		companyType getType() const;
		std::string getName() const;
		uint32 getOwnedStocks() const;
		uint32 getCurrentValue() const;
		/** Returns the company data array */
		uint32 *getCompanyData();
	};
}
