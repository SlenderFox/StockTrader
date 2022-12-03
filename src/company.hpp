#pragma once
#include "enums.hpp"
#include <string>

class company
{
	// The type of company, determining how the value changes over time
	companyType m_type = companyType::undefined;
	// The name of the company
	std::string m_name = "undefined";
	// The amount of stocks owned in the current company
	uint32 m_ownedStocks = 0;
	// The current value of the company
	uint32 m_currentValue = 0;
	// An array of previous values used to generate the graph (the width is correct)
	uint32 m_companyData[WIDTH - 1] = {};

public:
	company();
	~company() {}

	// Starts up the company with default values
	void initialiseCompany(
		companyType inType,
		std::string inName,
		uint32 inStartValue
	);

	// Updates the value of the company
	void updateCompanyValue(
		float inMin,
		float inMax
	);

	char getDataFromArray(
		const uint32 inMaxValue,
		const uint8 inHorizontal,
		uint8 inVertical
	) noexcept;

	// Adds or removes owned stocks
	void modifyOwnedStocks(uint32 inDifference);
	// Returns the type of company
	companyType getType() const;
	// Returns the name of the company
	std::string getName() const;
	// Returns the company data array
	uint32 *getCompanyData();
	// Returns the value of the company
	uint32 getCurrentValue() const;
	// Returns the amount of stocks currently owned in the company
	uint32 getOwnedStocks() const;
};
